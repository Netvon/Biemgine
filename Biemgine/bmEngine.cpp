#include "stdafx.h"
#include "bmEngine.h"
#include "sdlWindow.h"
#include "bmSceneManager.h"

bmEngine::bmEngine()
{
	SdlWindow window(
		"Biem Test 01",
		800, 600,
		SDL_WINDOW_OPENGL,
		SDL_RENDERER_ACCELERATED
	);

	bmSceneManager::instance()->setWindow(&window);
	bmSceneManager::instance()->changeScene(bmScene_menu);


	while (true) {

		// The engine should keep running until there is no next scene.
		if (!bmSceneManager::instance()->checkNextScene()) break;

	}

}