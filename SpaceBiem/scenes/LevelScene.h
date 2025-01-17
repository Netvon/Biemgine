#pragma once

#include "Biemgine.h"
#include "..\globals\Difficulty.h"

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

		LevelScene(StateManager& manager, bool newGame = true, Difficulty difficulty = Difficulty::NORMAL, string customLevel = "") :
			Scene(manager),
			newGame(newGame),
            difficulty(difficulty),
            customLevel(customLevel)
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
        int cheatId;
        int godModeId;
        int aibounceId;
		Entity * fpsEntity = nullptr;
		Entity * speedEntity = nullptr;
        Entity * cheatEntity = nullptr;
        Entity * godModeEntity = nullptr;
        Entity * aibounceEntity = nullptr;
		std::shared_ptr<AnimationComponent> fadeAnimation = nullptr;
		int timeout;
		float counter = 0;
		float totalDeltaTime = 0;

		void updateMenu();

		Difficulty difficulty;

        string customLevel;

		std::vector<Entity*> pauseMenuEntities;
	};
}
