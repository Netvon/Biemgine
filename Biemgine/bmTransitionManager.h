#pragma once

class bmSceneManager;
class bmTransitionManager
{
public:
    bmTransitionManager(bmSceneManager* pSceneManager): sceneManager(pSceneManager) {};

    void gameOverTransition();

    void quitLevelTransition();
    void startLevelTransition();

private:
    bmSceneManager* sceneManager = nullptr;

};

