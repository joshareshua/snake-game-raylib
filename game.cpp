#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>  
#include <ctime>
#include "raylib.h"

using namespace std;


Color purple = {45, 0, 54, 255};


int main() {
    //initalizing the window 750x750 pixels
    cout<<"Starting the game..." << endl;
    InitWindow(750,750,"Snake Game");
    SetTargetFPS(60); //frames per second for how fast the game runs


    // Main game loop, if user presses escape or x then ends game loop.
    while(WindowShouldClose()==false){
        BeginDrawing();

        //drawing the background
        ClearBackground(purple);

        EndDrawing();
    }
    CloseWindow();
    return 0;
    
}
