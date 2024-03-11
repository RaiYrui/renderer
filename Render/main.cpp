#include<iostream>
#include"Application.h"
using namespace std;

int main()
{
	Application* app = Application::getInstance();
	if (app->Init()) 
		app->Start();
	else 
		cout << "Init Failed" << endl;
	cout << "Hello CMake." << endl;
	return 0;
}
