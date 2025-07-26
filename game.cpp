#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>  
#include <ctime>
#include <deque>
#include "raylib.h"
#include <raymath.h>

using namespace std;


Color purple = {45, 0, 54, 255};
Color blueGlow = {0, 200, 255, 255};

int cellSize = 30;
int cellCount = 25;

double lastUpdateTime = 0;

bool eventTriggered(double interval){
    double currentTime = GetTime();
    if(currentTime-lastUpdateTime>=interval){
        lastUpdateTime=currentTime;
        return true;
    }
    return false;
}


//class for the actual snake, initializing it as 3 cells long
class Snake{
public:
    deque<Vector2> body = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};
    Vector2 direction = {1,0};



    void Draw(){
        for(unsigned int i = 0;i<body.size();i++){
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{x*cellSize, y*cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(segment, 0.5, 6, blueGlow);
        }

    }
    
    //handle the snake movements by just removing last cell and appending new cell in direction it's moving
    void Update(){
        body.pop_back();
        body.push_front(Vector2Add(body[0], direction));
    }


};


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

    Snake snake = Snake();
    

    // Main game loop, if user presses escape or x then ends game loop.
    while(WindowShouldClose()==false){
        BeginDrawing();
        if(eventTriggered(0.2)){
            snake.Update();
        }

        //drawing the background
        ClearBackground(purple);
        food.Draw();
        food1.Draw();
        food2.Draw();
        snake.Draw();

        EndDrawing();
    }
    CloseWindow();
    return 0;
    
}
