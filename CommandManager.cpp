#include "CommandManager.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>


void CommandManager::getCommand(std::string command, ShapeManager& manager)
{
	std::vector<std::string> args;
	splitWords(command, args);

	int argsSize = args.size();
	if (argsSize == 0)
	{
		return;
	}

	if (args[0] == "open")
	{
		//If the command is open, we get the next argument - the filename, and we ignore everything else.
		if (argsSize > 1)
		{
			readFile(args[1], manager);
		}
		else
		{
			std::cout << "Specify a file to open. \n";
		}

		return;
	}
	if (args[0] == "print")
	{
		manager.printShapes();
		return;
	}
	if (args[0] == "erase")
	{
		if (argsSize == 1)
		{
			std::cout << "Specify element. \n";
			return;
		}

		int index = std::atoi(args[1].c_str());
		if (index == 0)
		{
			std::cout << "Invalid value. \n";
			return;
		}

		manager.eraseShape(index);
		return;
	}
	if (args[0] == "close")
	{
		if (this->closeFile(manager))
		{
			std::cout << "Successfully closed " << currentFile << "\n";
			this->currentFile = "";
		}

		return;
	}
	if (args[0] == "translate")
	{
		int horizontal = 0;
		int vertical = 0;
		int shapeIndex = 0;

		this->extractTranslation(args, argsSize, horizontal, vertical, shapeIndex);

		if (horizontal != 0 || vertical != 0)
		{
			if (shapeIndex == 0)
			{
				manager.translate(vertical, horizontal);
			}
			else if (shapeIndex > 0)
			{
				manager.translate(vertical, horizontal, shapeIndex);
			}
		}
		else
		{
			std::cout << "Nothing translated! \n";
		}

		return;
	}
	if (args[0] == "save")
	{
		if (currentFile.empty())
		{
			std::cout << "No file opened. \n";
			return;
		}

		this->saveFile(manager);
		std::cout << "Successfully saved " << currentFile << std::endl;
		this->closeFile(manager);
		this->currentFile = "";

		return;
	}
	if (args[0] == "saveas")
	{
		if (argsSize == 1)
		{
			std::cout << "Specify path. \n";
			return;
		}

		if (currentFile.empty())
		{
			std::cout << "No file opened. \n";
			return;
		}

		this->saveFile(manager, args[1]);
		std::cout << "Sucessfully saved " << args[1] << std::endl;
		this->closeFile(manager);
		this->currentFile = "";
		return;

	}
	if (args[0] == "create")
	{
		if (currentFile.empty()) {
			std::cout << "No file opened! \n";
			return;
		}

		if (argsSize == 1)
		{
			std::cout << "Specify figure! \n";
			return;
		}

		
		Shape* newShape = this->createShape(args);
		manager.addShape(newShape);
		
		if (args[1] == "rectangle")
		{
			std::cout << "Successfully created rectangle (" << manager.getShapesCount() << ") \n";
		}

		if (args[1] == "circle")
		{
			std::cout << "Successfully created circle (" << manager.getShapesCount() << ") \n";
		}

		if (args[1] == "line")
		{
			std::cout << "Successfully created line (" << manager.getShapesCount() << ") \n";
		}

		return;
	}
	if (args[0] == "within")
	{
		if (currentFile.empty()) {
			std::cout << "No file opened! \n";
			return;
		}

		if (argsSize == 1)
		{
			std::cout << "Specify figure! \n";
			return;
		}

		Shape* newShape = this->createShape(args);

		//We check if the figure can be used with the command. 
		if (!dynamic_cast<IContainable*>(newShape))
		{
			std::cout << "Can't use this figure! \n";
			return;
		}
		
		//We cast the shape to IContainable in order to be passed to the function.
		if (!manager.checkWithin(dynamic_cast<IContainable*>(newShape)))
		{
			std::cout << "No figures within ";
			for (int i = 1; i < argsSize; i++)
			{
				std::cout << args[i] << " ";
			}
			std::cout << std::endl;
		}

		delete newShape;
		return;

	}

	std::cout << "Invalid command! \n";
	return;

}

//This function splits a string by space but doesn't split quoted text.
void CommandManager::splitWords(std::string source, std::vector<std::string>& words)
{
	std::string currentWord;

	int srcSize = source.size();
	bool inQuotes = false;

	for (int i = 0; i < srcSize; i++)
	{
		if (source[i] == '\"')
		{
			if (inQuotes)
			{
				inQuotes = false;
			}
			else
			{
				inQuotes = true;
				continue;
			}
		}
		if ((source[i] != ' ') || inQuotes) //If we are in quotes we push everything except the closing quote.
		{
			if (source[i] != '\"')
			{
				currentWord += source[i];
			}

			if (i == srcSize - 1)
			{
				words.push_back(currentWord);
				currentWord.clear();
			}
		}
		else if ((source[i] == ' ') && !currentWord.empty())
		{
			words.push_back(currentWord);
			currentWord.clear();
		}
	}
}


//We get the content from the file in a string.
std::string CommandManager::getContents()
{
	std::ifstream file(this->currentFile);
	if (!file.is_open())
	{
		this->currentFile = "";
		throw "Can't open the file. \n";
		
	}
	std::cout << "Sucessfully opened " << this->currentFile << "\n";

	std::stringstream buffer;
	buffer << file.rdbuf();

	file.close();

	return buffer.str();
}

//This function reads the file and populates the ShapeManager with the shapes from the file.
void CommandManager::readFile(std::string filename, ShapeManager& manager)
{
	this->currentFile = filename;
	std::string fileContent = this->getContents();
	std::vector<std::string> tags;

	getTags(fileContent, tags);
	pushTagsAsObjects(tags, manager);

}

void CommandManager::saveFile(const ShapeManager &manager)
{
	std::ofstream file(currentFile);

	file << "<?xml version=\"1.0\" standalone=\"no\"?>\n";
	file << "<!DOCTYPE svg PUBLIC \" -//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
	file << "<svg viewBox=\"0 0 1200 400\"  xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n";
	manager.saveShapesToFile(file);
	file << "</svg>";
	
	file.close();

}

void CommandManager::saveFile(const ShapeManager & manager, std::string filePath)
{
	std::ofstream file(filePath);
	file << "<?xml version=\"1.0\" standalone=\"no\"?>\n";
	file << "<!DOCTYPE svg PUBLIC \" -//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
	file << "<svg viewBox=\"0 0 1200 400\"  xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n";
	manager.saveShapesToFile(file);
	file << "</svg>";

	file.close();
}

//This fuction seperates every tag and puts it into the vector. 
void CommandManager::getTags(std::string fileContent, std::vector<std::string> &tags)
{
	int contentLength = fileContent.size();

	int svgStart = fileContent.find("<svg");
	int svgContentStart = fileContent.find('>', svgStart);
	int svgEnd = fileContent.find("</svg>");

	if (svgStart == -1)
	{
		throw "No svg tag in file \n";
	}
	if (svgEnd == -1)
	{
		throw "Svg tag not closed! \n";
	}
	
	int pos = svgContentStart + 1;
	while (pos != svgEnd)
	{
		if (fileContent[pos] == '<') //We check for opening tag
		{
			int endPosOfTag = fileContent.find("/>", pos); //We find the ending of the tag
			tags.push_back(fileContent.substr(pos, endPosOfTag + 2 - pos)); //We push the whole tag.
			pos = endPosOfTag + 1;
		}
		else pos++;
	}
	
}


void CommandManager::pushTagsAsObjects(const std::vector<std::string> &tags, ShapeManager & manager)
{
	std::vector<std::string> arguments;
	std::map<std::string, std::string> attributes; //We store the attributes in key-value pairs.
	ShapeFactory factory;

	for (std::vector<std::string>::const_iterator it = tags.begin(); it != tags.end(); ++it)
	{
		splitWords(*it, arguments);

		for (std::vector<std::string>::iterator it2 = arguments.begin() + 1; it2 != arguments.end(); ++it2)
		{
			int equalsPosition = (*it2).find("=");
			if (equalsPosition != -1)
			{
				//We split the argument by "=" and get the key and the value.
				std::string key = (*it2).substr(0, equalsPosition);
				std::string value = (*it2).substr(equalsPosition + 1, (*it2).size() - equalsPosition + 1);

				attributes[key] = value;
			}
		}

		if (arguments[0] == "<rect")
		{
			manager.addShape(factory.getShape("rectangle", attributes));
		}
		if (arguments[0] == "<circle")
		{
			manager.addShape(factory.getShape("circle", attributes));
		}
		if (arguments[0] == "<line")
		{
			manager.addShape(factory.getShape("line", attributes));
		}
	
		arguments.clear();
		attributes.clear();
	}
}

//We check all the valid command cases and we get the horizontal, vertical, and shape number if specified.
void CommandManager::extractTranslation(const std::vector<std::string> &args, int argsSize, int & horizontal, int & vertical, int &shapeIndex)
{
	switch (argsSize)
	{
		case 1:
		{
			std::cout << "Specify horizontal or/and vertical size. \n";
			break;
		}
		case 2: //Case "translate vertical=<value>" or "translate horizontal=<value>"
		{
			if (args[1].find("=") != -1)
			{
				int equalPos = args[1].find("=");
				std::string key = args[1].substr(0, equalPos);
				std::string value = args[1].substr(equalPos + 1, args[1].size() - equalPos + 1);
				if (key == "horizontal")
				{
					horizontal = atoi(value.c_str());
				}
				if (key == "vertical")
				{
					vertical = atoi(value.c_str());
				}
			}
			break;
		}
		case 3: //Case "translate vertical=<value> horizontal=<value>" or "translate horizontal=<value> vertical=<value>" or 
				//"translate vertical=<value> <shape-number>"
		{
			for (int i = 1; i < 3; i++)
			{
				if (args[i].find("=") != -1)
				{
					int equalPos = args[i].find("=");
					std::string key = args[i].substr(0, equalPos);
					std::string value = args[i].substr(equalPos + 1, args[i].size() - equalPos + 1);
					if (key == "horizontal")
					{
						horizontal = atoi(value.c_str());
					}
					if (key == "vertical")
					{
						vertical = atoi(value.c_str());
					}
				}

				if (atoi(args[2].c_str())) //If there is shape specified.
				{
					shapeIndex = atoi(args[2].c_str());
				}
			}

			break;
		}
		case 4: //Case "translate vertical=<value> horizontal=<value> <shape-number>" or 
				// "translate horizontal=<value> vertical=<value> <shape-number>"
		{
			for (int i = 1; i < 3; i++)
			{
				if (args[i].find("=") != -1)
				{
					int equalPos = args[i].find("=");
					std::string key = args[i].substr(0, equalPos);
					std::string value = args[i].substr(equalPos + 1, args[i].size() - equalPos + 1);
					if (key == "horizontal")
					{
						horizontal = atoi(value.c_str());
					}
					if (key == "vertical")
					{
						vertical = atoi(value.c_str());
					}
				}
			}
			if (atoi(args[3].c_str())) //If there is shape specified.
			{
				shapeIndex = atoi(args[3].c_str());
			}
			break;
		}
		default:
		{
			std::cout << "Too much arguments. \n";
		}
	}
}

Shape* CommandManager::createShape(const std::vector<std::string> &args)
{
	ShapeFactory factory;

		//We remove the command and the shape type.
		std::vector<std::string> values(args.begin() + 2, args.end());
		return factory.getShape(args[1], values);
}

bool CommandManager::closeFile(ShapeManager & manager)
{
	if (currentFile.empty())
	{
		std::cout << "No file opened! \n";
		return false;
	}

	manager.eraseAll();
	return true;
}

