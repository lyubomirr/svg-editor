#ifndef  RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
#include "IContainable.h"
#include <string>

class Rectangle :
	public Shape,
	public IContainable
{
private:

	int width;
	int height;
	int rx;
	int ry;

	std::string fill;

public:
	Rectangle();
	Rectangle(int x, int y, int width, int height, std::string fill, int rx=0, int ry=0, std::string stroke="", int strokeWidth=0);

	int getWidth() const;
	int getHeight() const;

	int getRX() const;
	int getRY() const;

	std::string getFill() const;

	void print() const;
	std::string exportAsTag() const;

	void setAttribute(std::string attribute, std::string &value);

	bool doesContainThePoint(int x, int y) const;
	bool isWithin(const IContainable* shape) const;
};

#endif // ! RECTANGLE_H


