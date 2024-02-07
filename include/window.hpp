#pragma once

#include "../subprojects/tgui/include/TGUI/TGUI.hpp"
#include "../subprojects/tgui/include/TGUI/Backend/SFML-Graphics.hpp"

#include "types.hpp"

namespace app
{
    class Window : public sf::RenderWindow
    {
        public:
            virtual void update(const Seconds elapsed_seconds);
    };
}