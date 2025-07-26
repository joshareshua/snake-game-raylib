#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>  
#include <ctime>

using namespace std;

#include "raylib.h"

int main() {
    InitWindow(800, 600, "Hello Raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Welcome to Raylib on macOS!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
