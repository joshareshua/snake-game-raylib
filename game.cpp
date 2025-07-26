#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>  
#include <ctime>
#include <deque>
#include "raylib.h"

using namespace std;


Color purple = {45, 0, 54, 255};
Color blueGlow = {0, 200, 255, 255};

int cellSize = 30;
int cellCount = 25;

//class for the actual snake, initializing it as 3 cells long


//class for food objects
class Food{
public:
    Vector2 position = {6,9};
    Texture2D texture;

    //Loading actual image as the food object
    Food(){
        Image image = LoadImage("Graphics/food.png");
        texture  = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos();
    }
    //destructor for freeing memory after use
    ~Food(){
        UnloadTexture(texture);
    }

    void Draw(){
        DrawTexture(texture, position.x*cellSize, position.y*cellSize, WHITE);
    }
    //generate a random position for each food using these Raylib functions
    Vector2 GenerateRandomPos(){
        float x = GetRandomValue(0,cellCount-1);
        float y = GetRandomValue(0,cellCount-1);
        return Vector2{x,y};
    }

};


int main() {
    //initalizing the window 750x750 pixels
    cout<<"Starting the game..." << endl;
    InitWindow(cellSize*cellCount, cellSize*cellCount,"Snake Game");
    SetTargetFPS(60); //frames per second for how fast the game runs

    //create food object to use in game loop
    Food food = Food();
    Food food1 = Food();
    Food food2 = Food();
    

    // Main game loop, if user presses escape or x then ends game loop.
    while(WindowShouldClose()==false){
        BeginDrawing();

        //drawing the background
        ClearBackground(purple);
        food.Draw();
        food1.Draw();
        food2.Draw();

        EndDrawing();
    }
    CloseWindow();
    return 0;
    
}
