#pragma once

#include "Biemgine.h"
#include "../globals/Difficulty.h"

using biemgine::AnimationComponent;
using biemgine::SpriteEntity;
using biemgine::Scene;
using biemgine::StateManager;
using biemgine::Entity;

namespace spacebiem
{
	class LevelScene :
		public Scene
	{
	public:
		void input() override;
		void update() override;
		void render(const float deltaTime) override;
		void created() override;
		void sceneEnd() override;
		void close() override;

		void resetFPScounters();

		void saveScore();

		void saveGame();

		LevelScene(StateManager& manager, bool newGame = true, Difficulty difficulty = Difficulty::NORMAL) :
			Scene(manager),
			newGame(newGame),
			difficulty(difficulty)
		{};

		~LevelScene() {}

	private:
		bool isHomeButtonDown = false;
		bool isPageUpButtonDown = false;
		bool isPageDownButtonDown = false;
		bool isPauseButtonDown = false;

		bool isPaused = false;
		bool newGame;
		int FPSId;
		int speedId;
        int inputId;
		Entity * fpsEntity = nullptr;
		Entity * speedEntity = nullptr;
        Entity * inputEntity = nullptr;
		std::shared_ptr<AnimationComponent> fadeAnimation = nullptr;
		int timeout;
		float counter = 0;
		float totalDeltaTime = 0;

        string inputText = "Test Input";

		void updateMenu();

		Difficulty difficulty;

		std::vector<Entity*> pauseMenuEntities;
	};
}
