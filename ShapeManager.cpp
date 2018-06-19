#include "ShapeManager.h"
#include <iostream>
#include <fstream>
#include <sstream>


ShapeManager::ShapeManager()
{
}


ShapeManager::~ShapeManager()
{
	for (std::vector<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it)
	{
		delete (*it);
	}
}

void ShapeManager::addShape(Shape * newShape)
{
	this->shapes.push_back(newShape);
}

void ShapeManager::printShapes() const
{
	if (shapes.begin() == shapes.end())
	{
		std::cout << "Nothing to print! \n";
	}
	for (std::vector<Shape*>::const_iterator it = shapes.begin(); it != shapes.end(); ++it)
	{
		std::cout << std::distance(shapes.begin(), it) + 1<<" ";
		(*it)->print();
	}
}

void ShapeManager::eraseShape(int index)
{
	for (std::vector<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it)
	{
		if (std::distance(shapes.begin(), it) + 1 == index)
		{
			delete *it;
			shapes.erase(it);
			std::cout << "Erased shape " << index << ". \n";
			return;
		}
	}

	std::cout << "No shape with number " << index << ". \n";
}

void ShapeManager::eraseAll()
{
	for (std::vector<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it)
	{
			delete *it;
	}

	shapes.clear();
	
}

void ShapeManager::translate(int vertical, int horizontal)
{
	for (std::vector<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it)
	{
		(*it)->translate(horizontal, vertical);
	}

	std::cout << "Translated all figures. \n";
}

void ShapeManager::translate(int vertical, int horizontal, int shapeIndex)
{
	for (std::vector<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it)
	{
		if (std::distance(shapes.begin(), it) + 1 == shapeIndex)
		{
			(*it)->translate(horizontal, vertical);
			std::cout << "Translated figure " << shapeIndex << std::endl;
			return;
		}
	}

}

void ShapeManager::saveShapesToFile(std::ofstream & file) const
{
	for (std::vector<Shape*>::const_iterator it = shapes.begin(); it != shapes.end(); ++it)
	{
		file << (*it)->exportAsTag() << std::endl;
	}
}

int ShapeManager::getShapesCount() const
{
	return this->shapes.size();
}

bool ShapeManager::checkWithin(const IContainable * shape) const
{
	bool isThere = false;

	for (std::vector<Shape*>::const_iterator it = shapes.begin(); it != shapes.end(); ++it)
	{
		if ((*it)->isWithin(shape))
		{
			std::cout << std::distance(shapes.begin(), it) + 1 << " ";
			(*it)->print();
			isThere = true;
		}
	}
	return isThere;
}
