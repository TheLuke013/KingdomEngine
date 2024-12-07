#ifndef GAME_LOADER_H
#define GAME_LOADER_H

#include <SDL/SDL_loadso.h>
#include <string>
#include "KingdomEngine/Core/GameLoader/Game.h"

namespace KE
{
    typedef Game* (*LoadGameClass)();

    class GameLoader
    {
    public:
        static GameLoader& Get();

        void LoadGame(const std::string& gameLibPath);
        void UnloadGame();

        Game* GetLoadedGame() { return loadedGame; }

    private:
        GameLoader()
            : loadedGame(nullptr), handle(nullptr)
        {}

        Game* loadedGame;
        void* handle;

    };
}

#endif
