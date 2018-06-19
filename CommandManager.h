#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <string>
#include <vector>

#include "ShapeManager.h"
#include "ShapeFactory.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"


class CommandManager
{
private:
	std::string currentFile;


	void splitWords(std::string source, std::vector<std::string> &words);
	std::string getContents();
	void readFile(std::string filename, ShapeManager& manager);
	void saveFile(const ShapeManager &manager);
	void saveFile(const ShapeManager &manager, std::string filePath);
	void getTags(std::string fileContent, std::vector<std::string> &tags);
	void pushTagsAsObjects(const std::vector<std::string> &tags, ShapeManager& manager);
	void extractTranslation(const std::vector<std::string> &args, int argsSize, int &horizontal, int &vertical, int &shapeIndex);
	Shape* createShape(const std::vector<std::string>& args);
	bool closeFile(ShapeManager& manager);

public:
	void getCommand(std::string command, ShapeManager& manager);
	
};

#endif