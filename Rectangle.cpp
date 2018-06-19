#include "Rectangle.h"
#include <iostream>
#include <sstream>

Rectangle::Rectangle()
	:Rectangle(0, 0, 0, 0, "", 0, 0, "", 0)
{
}

Rectangle::Rectangle(int x, int y, int width, int height, std::string fill, int rx, int ry, std::string stroke, int strokeWidth)
	:Shape(x, y, stroke, strokeWidth)
{
	this->width = width >= 0 ? width : 0;
	this->height = height >= 0 ? height : 0;
	this->fill = fill.empty() ? "black" : fill; //If there is no color it is rendered as black. So we set it for clearness.
	this->rx = rx;
	this->ry = ry;

}


int Rectangle::getWidth() const
{
	return width;
}

int Rectangle::getHeight() const
{
	return height;
}

int Rectangle::getRX() const
{
	return rx;
}

int Rectangle::getRY() const
{
	return ry;
}

std::string Rectangle::getFill() const
{
	return fill;
}


void Rectangle::print() const
{
	std::cout << "rectangle " << x << " " << y << " " << width << " " << height << " " << fill<<" ";
	std::cout << rx << " " << ry << " ";

	if (!stroke.empty()) //If there is no stroke there is no point in showing its width.
	{
		std::cout << stroke << " " << strokeWidth;
	}
	std::cout << std::endl;

}

std::string Rectangle::exportAsTag() const
{
	std::stringstream stream;
	stream << "<rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << width << "\" height=\"" << height << "\" fill=\""<< fill<<"\" ";
	stream << "rx=\"" << rx << "\" ry=\"" << ry << "\" ";

	if (!stroke.empty())
	{
		stream << "stroke=\"" << stroke << "\" ";
	}

	stream << "stroke-width=\"" << strokeWidth << "\"";
	
	stream << " />";
	

	return stream.str();
}

void Rectangle::setAttribute(std::string attribute, std::string &value)
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
		if (attribute == "x")
		{
			this->x = stringToNumber(value);
			return;
		}

		if (attribute == "y")
		{
			this->y = stringToNumber(value);
			return;
		}

		if (attribute == "width")
		{
			this->width = stringToNumber(value);
			if (this->width < 0) this->width = 0;

			return;
		}

		if (attribute == "height")
		{
			this->height = stringToNumber(value);
			if (this->height < 0) this->height = 0;

			return;
		}

		if (attribute == "rx")
		{
			this->rx = stringToNumber(value);
			return;
		}

		if (attribute == "ry")
		{
			this->ry = stringToNumber(value);
			return;
		}
	}

}

bool Rectangle::doesContainThePoint(int x, int y) const
{
	return 
	(
		(this->x <= x && x <= this->x + this->width) && (this->y <= y && y <= this->y + this->height)
	);
}

bool Rectangle::isWithin(const IContainable * shape) const
{
	//We check if the 4 tips of the rectangle are in the shape.
	return
	(
		shape->doesContainThePoint(x, y) &&
		shape->doesContainThePoint(x, y + height) &&
		shape->doesContainThePoint(x + width, y) &&
		shape->doesContainThePoint(x + width, y + height)
	);
}



