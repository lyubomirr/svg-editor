#include "ShapeFactory.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "Rectangle.h"
#include "Circle.h"
#include <algorithm>



ShapeFactory::ShapeFactory()
{
}


ShapeFactory::~ShapeFactory()
{
}

Shape * ShapeFactory::getShape(std::string type, std::map<std::string, std::string> attributes)
{
	if (type == "rectangle")
	{
		Rectangle* newRectangle = new Rectangle;
		for (std::map<std::string, std::string>::iterator it = attributes.begin(); it != attributes.end(); it++)
		{
			newRectangle->setAttribute(it->first, it->second);
		}

		return newRectangle;
	}

	if (type == "circle")
	{
		Circle* newCircle = new Circle;
		for (std::map<std::string, std::string>::iterator it = attributes.begin(); it != attributes.end(); it++)
		{
			newCircle->setAttribute(it->first, it->second);
		}

		return newCircle;

	}

	if (type == "line")
	{
		Line* newLine = new Line;
		for (std::map<std::string, std::string>::iterator it = attributes.begin(); it != attributes.end(); it++)
		{
			newLine->setAttribute(it->first, it->second);
		}

		return newLine;
	}

	throw "Shape not supported! \n";
}

Shape * ShapeFactory::getShape(std::string type, std::vector<std::string> values)
{
	int attributesSpecifiedCount = 0;

	if (type == "rectangle")
	{
		std::vector<std::string> keys = { "x", "y", "width", "height", "fill", "rx", "ry", "stroke", "stroke-width" };

		//If values are more than keys we get only the one we need. If values are less we set only the keys we have specified.
		attributesSpecifiedCount = std::min(keys.size(), values.size());

		Rectangle* newRectangle = new Rectangle;
		for (int i=0; i < attributesSpecifiedCount; i++)
		{
			newRectangle->setAttribute(keys[i], values[i]);
		}

		return newRectangle;
	}

	if (type == "circle")
	{
		std::vector<std::string> keys = { "cx", "cy", "r", "fill", "stroke", "stroke-width" };

		//If values are more than keys we get only the one we need. If values are less we set only the keys we have specified.
		attributesSpecifiedCount = std::min(keys.size(), values.size());

		Circle* newCicle = new Circle;
		for (int i = 0; i < attributesSpecifiedCount; i++)
		{
			newCicle->setAttribute(keys[i], values[i]);
		}

		return newCicle;
	}

	if (type == "line")
	{
		std::vector<std::string> keys = { "x1", "y1", "x2", "y2", "stroke", "stroke-width" };

		//If values are more than keys we get only the one we need. If values are less we set only the keys we have specified.
		attributesSpecifiedCount = std::min(keys.size(), values.size());

		Line* newLine = new Line;
		for (int i = 0; i < attributesSpecifiedCount; i++)
		{
			newLine->setAttribute(keys[i], values[i]);
		}

		return newLine;
	}

	throw "Figure is not supported! \n";

}
