#ifndef SHAPE_H
#define SHAPE_H

#include "IContainable.h"
#include <string>

class Shape
{
protected:

	int x;
	int y;
	std::string stroke;
	int strokeWidth;

	bool isANumber(std::string value);
	int stringToNumber(std::string value);
	void removeWhitespace(std::string &value);

public:
	Shape();
	Shape(int x, int y, std::string stroke, int strokeWidth);
	virtual ~Shape();
	
	int getX() const;
	int getY() const;

	int getStrokeWidth() const;
	std::string getStroke() const;

	virtual void setAttribute(std::string attribute, std::string &value);

	virtual void print() const = 0;
	virtual std::string exportAsTag() const = 0;
	virtual void translate(int dX, int dY);
	virtual bool isWithin(const IContainable* shape) const = 0;

};

#endif