#ifndef  SHAPEMANAGER_H
#define SHAPEMANAGER_H
#include <vector>
#include "Shape.h"
#include "IContainable.h"

class ShapeManager
{
private:
	std::vector<Shape*> shapes;

public:
	ShapeManager();
	~ShapeManager();
	
	void addShape(Shape* newShape);
	void printShapes() const;
	void eraseShape(int index);
	void eraseAll();
	void translate(int vertical, int horizontal);
	void translate(int vertical, int horizontal, int shapeIndex);
	void saveShapesToFile(std::ofstream &file) const;
	int getShapesCount() const;
	bool checkWithin(const IContainable* shape) const;
};


#endif // ! SHAPEMANAGER_H



