#ifndef GAME_H
#define GAME_H

#include "KingdomEngine/Core/Event.h"

namespace KE
{
    class Game
    {
    public:
        virtual ~Game() = default;

        virtual void OnReady() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnEvent(Event e) = 0;

    };
}

#endif
