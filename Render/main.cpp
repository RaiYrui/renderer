#include<iostream>
#include<Windows.h>
#include"Application.h"
using namespace std;

//int WINAPI WinMain(_In_ HINSTANCE hInstance,   _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,_In_ int nCmdShow)
//{
//	Application* app = Application::getInstance();
//	if (app->Init())
//		app->Start();
//	else
//		cout << "Init Failed" << endl;
//	cout << "Hello CMake." << endl;
//
//	return 0;
//}
int main()
{
	RR::Application* app = RR::Application::getInstance();
	if (app->Init())
		app->Start();
	else 
		cout << "Init Failed" << endl;
	cout << "Hello CMake." << endl;
	return 0;
}
