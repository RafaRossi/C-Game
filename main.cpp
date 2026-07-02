#include <SDL3/SDL.h>
#include <iostream>
#include "Core/Game/Game.h"
#include "Editor/Editor.h"

int main(int argc, char* argv[]) {

    //Game game;

    //game.Run();

    Editor editor(nullptr);
    editor.Run();
    return 0;
}
