#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

struct GameData
{

};

typedef std::shared_ptr<GameData> GameDataRef;

class GameManager
{

public:
	GameManager();
	int Initilise();
	void Run();

private:
	GLFWwindow* _window;
	GameDataRef _data = std::make_shared<GameData>();
};

