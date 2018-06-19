#ifndef LINE_H
#define LINE_H
#include "Shape.h"
#include "IContainable.h"

class Line :
	public Shape
{
private:
	int x2;
	int y2;
public:
	Line();
	Line(int x1, int y1, int x2, int y2, std::string stroke, int strokeWidth);

	int getX2() const;
	int getY2() const;

	void translate(int dX, int dY);

	void print() const;
	std::string exportAsTag() const;

	void setAttribute(std::string attribute, std::string &value);
	bool isWithin(const IContainable* shape) const;
};

#endif