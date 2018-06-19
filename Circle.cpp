#include "Circle.h"
#include <iostream>
#include <sstream>

double Circle::getDistanceFromCenterTo(int x, int y) const
{
	return sqrt((this->x - x)*(this->x - x) + (this->y - y)*(this->y - y));
}

Circle::Circle()
	:Circle(0,0,0,"","",0)
{
}

Circle::Circle(int cx, int cy, int radius, std::string fill, std::string stroke, int strokeWidth)
	:Shape(cx, cy, stroke, strokeWidth)
{
	this->radius = radius >= 0 ? radius : 0; //Negative radius is an error.
	this->fill = fill.empty() ? "black" : fill; //If there is no color it is rendered as black. So we set it for clearness.
}


int Circle::getRadius() const
{
	return this->radius;
}

std::string Circle::getFill() const
{
	return this->fill;
}

void Circle::print() const
{
	std::cout << "circle " << x << " " << y << " " << radius << " " << fill << " ";
	if (!stroke.empty()) //If there is no stroke there is no point in showing its width.
	{
		std::cout << stroke << " " << strokeWidth;
	}
	std::cout << std::endl;

}

std::string Circle::exportAsTag() const
{
	std::stringstream stream;
	stream << "<circle cx=\"" << x << "\" cy=\"" << y <<"\" r=\""<< radius << "\" fill=\"" << fill << "\" ";
	if (!stroke.empty())
	{
		stream << "stroke=\"" << stroke << "\" ";
	}

	stream << "stroke-width=\"" << strokeWidth << "\"";
	stream << " />";


	return stream.str();
}

void Circle::setAttribute(std::string attribute, std::string &value)
{
	Shape::setAttribute(attribute, value);

	if (attribute == "fill")
	{
		this->fill = value;
		if (fill.empty())
		{
			this->fill = "black";
		}
		return;
	}

	if (isANumber(value))
	{
		if (attribute == "cx")
		{
			this->x = stringToNumber(value);
			return;
		}

		if (attribute == "cy")
		{
			this->y = stringToNumber(value);
			return;
		}

		if (attribute == "r")
		{
			this->radius = stringToNumber(value);
			if (this->radius < 0) this->radius = 0;
			return;
		}
	}
}

bool Circle::doesContainThePoint(int x, int y) const
{
	return (this->getDistanceFromCenterTo(x, y) <= radius);
}

bool Circle::isWithin(const IContainable * shape) const
{
	//We check if the 4 tips of the circle are in the shape.
	return
	(
		shape->doesContainThePoint(x - radius, y) &&
		shape->doesContainThePoint(x + radius, y) &&
		shape->doesContainThePoint(x, y - radius) &&
		shape->doesContainThePoint(x, y + radius)
	);
}

