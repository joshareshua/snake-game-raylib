#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>  
#include <ctime>
#include "raylib.h"

using namespace std;


Color purple = {45, 0, 54, 255};
Color blueGlow = {0, 200, 255, 255};

int cellSize = 30;
int cellCount = 25;

//class for food objects
class Food{
public:
    Vector2 position = {6,9};

    void Draw(){
        DrawRectangle(position.x*cellSize,position.y*cellSize,cellSize,cellSize,blueGlow);
    }

};


int main() {
    //initalizing the window 750x750 pixels
    cout<<"Starting the game..." << endl;
    InitWindow(cellSize*cellCount, cellSize*cellCount,"Snake Game");
    SetTargetFPS(60); //frames per second for how fast the game runs

    //create food object to use in game loop
    Food food = Food();

    // Main game loop, if user presses escape or x then ends game loop.
    while(WindowShouldClose()==false){
        BeginDrawing();

        //drawing the background
        ClearBackground(purple);
        food.Draw();

        EndDrawing();
    }
    CloseWindow();
    return 0;
    
}
