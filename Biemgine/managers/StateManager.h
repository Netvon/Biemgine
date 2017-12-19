#pragma once

#include "dlldef.h"
#include "..\core\Window.h"
#include "InputManager.h"
#include "..\entities\Entity.h"
#include "..\devices\audio\AudioDevice.h"
#include "..\devices\graphics\TextBoxDevice.h"

using std::string;

namespace biemgine
{
    class SceneManager;

    class BIEMGINE StateManager
    {
    public:
        StateManager( SceneManager& pSceneManager,const Window& pWindow);
        ~StateManager();

        int getWindowWidth() const;
        int getWindowHeight() const;

        void drawBackground(const string& backgroundPath);

        void setInputManager(const InputManager* manager) {
            inputManager = manager;
        }

        const InputManager* getInputManager() const
        {
            return inputManager;
        }

        AudioDevice& getAudioDevice() const
        {
            return *audioDevice;
        }

        TextBoxDevice& getTextBoxDevice() const
        {
            return *textBoxDevice;
        }

        template<class TScene, typename... TParams>
        void navigateTo(TParams&&... arguments);

        Entity * getEntity(int id) const;

        SceneManager & getSceneManager() const;

    private:
        SceneManager* sceneManager = nullptr;
        const InputManager* inputManager = nullptr;
        const Window* window = nullptr;
        AudioDevice* audioDevice;
        TextBoxDevice* textBoxDevice;
    };

    template<class TScene, typename... TParams>
    void StateManager::navigateTo(TParams&&... arguments)
    {
        sceneManager->navigateTo<TScene>(std::forward<TParams>(arguments)...);
    }
}
