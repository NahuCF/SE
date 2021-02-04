#include "Graphics/Window.h"

int main()
{
	SE::Window window("Game", 1280, 720);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	while(!window.Closed())
	{
		window.Clear();


		window.Update();
	}
}