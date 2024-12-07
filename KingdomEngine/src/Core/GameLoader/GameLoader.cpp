#include "KingdomEngine/Core/GameLoader/GameLoader.h"
#include "KingdomEngine/Core/Log.h"

namespace KE
{
    GameLoader& GameLoader::Get()
	{
		static GameLoader* instance = new GameLoader();
		return *instance;
	}

	void GameLoader::LoadGame(const std::string& gameLibPath)
	{
	    //load game lib
	    LOG_WARN("Loading project library");
        handle = SDL_LoadObject(gameLibPath.c_str());
        if (!handle)
        {
            LOG_FATAL("Error to loading game lib");
            return;
        }

        //load function that create game class
        LOG_WARN("Importing game class");
        LoadGameClass gameExportClassFunc = (LoadGameClass)SDL_LoadFunction(handle, "GameExport");
        if (!gameExportClassFunc)
        {
            LOG_FATAL("Error to load game export function: " + std::string(SDL_GetError()));
            SDL_UnloadObject(handle);
            return;
        }

        //instance the game
        LOG_WARN("Instancing game");
        loadedGame = gameExportClassFunc();
        if (!loadedGame)
        {
            LOG_FATAL("Error to instance the game");
            SDL_UnloadObject(handle);
            return;
        }
	}

    void GameLoader::UnloadGame()
    {
        LOG_WARN("Unloading Game");
        delete loadedGame;
        loadedGame = nullptr;
        SDL_UnloadObject(handle);
        handle = nullptr;
    }
}
