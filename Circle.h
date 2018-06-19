#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include "IContainable.h"

class Circle :
	public Shape,
	public IContainable
{
private:
	int radius;
	std::string fill;

	double getDistanceFromCenterTo(int x, int y) const;

public:
	Circle();
	Circle(int cx, int cy, int radius, std::string fill, std::string stroke="", int strokeWidth=0);


	int getRadius() const;
	std::string getFill() const;

	void print() const;
	std::string exportAsTag() const;

	void setAttribute(std::string attribute, std::string &value);

	bool doesContainThePoint(int x, int y) const;
	bool isWithin(const IContainable* shape) const;
};

#endif