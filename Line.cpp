#include "Line.h"
#include <iostream>
#include <sstream>


Line::Line()
	:Line(0,0,0,0,"",0)
{
}

Line::Line(int x1, int y1, int x2, int y2, std::string stroke, int strokeWidth)
	:Shape(x1, y1, stroke, strokeWidth)
{
	this->x2 = x2;
	this->y2 = y2;
}

int Line::getX2() const
{
	return x2;
}

int Line::getY2() const
{
	return y2;
}

void Line::translate(int dX, int dY)
{
	Shape::translate(dX, dY);
	
	this->x2 += dX;
	this->y2 += dY;
}

void Line::print() const
{
	std::cout << "line " << x << " " << y << " " << x2 << " " << y2 << " ";
	if (!stroke.empty()) //If there is no stroke there is no point in showing its width.
	{
		std::cout << stroke << " " << strokeWidth;
	}
	std::cout << std::endl;
}

std::string Line::exportAsTag() const
{
	std::stringstream stream;

	stream << "<line x1=\"" << x << "\" y1=\"" << y << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" ";
	if (!stroke.empty())
	{
		stream << "stroke=\"" << stroke << "\" ";
	}
	stream << "stroke-width=\"" << strokeWidth << "\"";
	stream << " />";


	return stream.str();
}

void Line::setAttribute(std::string attribute, std::string &value)
{
	Shape::setAttribute(attribute, value);

	if (isANumber(value))
	{

		if (attribute == "x1")
		{
			this->x = stringToNumber(value);
			return;
		}

		if (attribute == "y1")
		{
			this->y = stringToNumber(value);
			return;
		}

		if (attribute == "x2")
		{
			this->x2 = stringToNumber(value);
			return;
		}

		if (attribute == "y2")
		{
			this->y2 = stringToNumber(value);
			return;
		}
	}
}

bool Line::isWithin(const IContainable * shape) const
{
	return (shape->doesContainThePoint(x, y) && shape->doesContainThePoint(x2, y2));
}

