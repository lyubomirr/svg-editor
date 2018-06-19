#ifndef ICONTAINABLE
#define ICONTAINABLE

class IContainable
{
public:
	virtual bool doesContainThePoint(int x, int y) const = 0;
	virtual ~IContainable() {};
};

#endif