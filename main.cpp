#include <SFML/Graphics.hpp>
#include <iostream>
#include "SFMEngine/Engine.hpp"

using namespace sf;

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main(int argc, char* argv[])
{
	srand(time(0));
	Engine engine;
	engine.start();
	return 0;
}