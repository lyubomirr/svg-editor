#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include "Shape.h"
#include <string>
#include <map>
#include <vector>

class ShapeFactory
{
public:

	ShapeFactory();
	~ShapeFactory();

	Shape* getShape(std::string type, std::map<std::string, std::string> attributes);
	Shape* getShape(std::string type, std::vector<std::string> values);


};

#endif