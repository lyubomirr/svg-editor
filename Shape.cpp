#include "Shape.h"
#include <algorithm>


bool Shape::isANumber(std::string value)
{

	if (value.empty())
	{
		return false;
	}

	if (value[0] != '-' && (value[0] < '0' || value[0] > '9'))
	{
		return false;
	}

	int size = value.size();
	for (int i = 1; i < size; i++)
	{
		if (value[i] < '0' || value[i] > '9')
		{
			return false;
		}
	}

	return true;
}

int Shape::stringToNumber(std::string value)
{
	int number = 0;
	bool isNegative = false;
	if (value[0] == '-')
	{
		isNegative = true;
		value.erase(0, 1);
	}

	int size = value.size();

	for (int i = 0; i < size; i++)
	{
		number *= 10;
		number += (value[i] - '0');
	}

	number = isNegative ? -number : number;

	return number;
}

void Shape::removeWhitespace(std::string & value)
{
	//Set of algorithms to remove an occurence of a character in a string.
	//We use it to remove the whitespace in the string.
	value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
	value.erase(std::remove(value.begin(), value.end(), '\n'), value.end());
	value.erase(std::remove(value.begin(), value.end(), '\r'), value.end());

}

Shape::Shape()
	:Shape(0,0,"", 0)
{
}

Shape::Shape(int x, int y, std::string stroke, int strokeWidth)

{
	this->x = x;
	this->y = y;
	this->stroke = stroke;
	this->strokeWidth = strokeWidth >= 0 ? strokeWidth : 1; /*If stroke width is negative number SVG sets it to one, 
															so we do it, not to log an error. */
}

Shape::~Shape()
{
}

int Shape::getX() const
{
	return x;
}

int Shape::getY() const
{
	return y;
}


int Shape::getStrokeWidth() const
{
	return strokeWidth;
}

std::string Shape::getStroke() const
{
	return stroke;
}

void Shape::setAttribute(std::string attribute, std::string &value)
{
	removeWhitespace(value);

	if (attribute == "stroke")
	{
		this->stroke = value;
		return;
	}

	if (isANumber(value))
	{

		if (attribute == "stroke-width")
		{
			this->strokeWidth = stringToNumber(value);
			return;
		}
	}
}

void Shape::translate(int dX, int dY)
{
	this->x += dX;
	this->y += dY;
}
