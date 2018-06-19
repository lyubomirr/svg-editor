#include <iostream>
#include <fstream>
#include "CommandManager.h"
#include "ShapeManager.h"

using namespace std;

int main()
{

	string command;
	getline(cin, command);

	ShapeManager shapes;
	CommandManager manager;
	
	while (command != "exit")
	{
		try
		{
			manager.getCommand(command, shapes);
			getline(cin, command);
		}
		catch (const char* ex)
		{
			std::cout << ex;
			getline(cin, command);
		}

	}



	system("pause");
	return 0;
}