#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>  
#include <ctime>
#include <deque>
#include "raylib.h"
#include <raymath.h>
#include <fstream>

using namespace std;


Color purple = {45, 0, 54, 255};
Color blueGlow = {0, 200, 255, 255};
Color dark = {61, 28, 30, 255};


//Updated the cellsize from 750x750 to 500x500 to fit on the screen
int cellSize = 25;
int cellCount = 25;
int offset = 75;


double lastUpdateTime = 0;

//To handle if the food generates again right in front of the snake body randomly in inside the body
bool ElementInDeque(Vector2 element, deque<Vector2> deque){
    for(unsigned int i = 0; i<deque.size();i++){
        if (Vector2Equals(deque[i],element)){
            return true;
        }
    }
    return false; 

}

//For frames per second adjustment
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
    bool addSegment = false;



    void Draw(){
        for(unsigned int i = 0;i<body.size();i++){
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{offset+ x*cellSize, offset+ y*cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(segment, 0.5, 6, blueGlow);
        }

    }
    
    //handle the snake movements by just removing last cell and appending new cell in direction it's moving
    void Update(){
        //Handle a snake eating food event to make its body bigger by adding another cell to its head
        body.push_front(Vector2Add(body[0],direction));
        if(addSegment == true){
           
            addSegment = false;

        }
        else{
            body.pop_back();
        }
    }

    void Reset(){
        body = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};
        direction = {1,0};
    }


};


//class for food objects
class Food{
public:
    Vector2 position = {6,9};
    Texture2D texture;

    //Loading actual image as the food object
    Food(deque<Vector2> snakeBody){
        Image image = LoadImage("Graphics/food.png");
        texture  = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos(snakeBody);
    }
    //destructor for freeing memory after use
    ~Food(){
        UnloadTexture(texture);
    }

    void Draw(){
        DrawTexture(texture, offset + position.x*cellSize, offset + position.y*cellSize, WHITE);
    }

    Vector2 GenerateRandomCell(){
        float x = GetRandomValue(0,cellCount-1);
        float y = GetRandomValue(0,cellCount-1);
        Vector2 position = {x,y};

        return Vector2{x,y};
    }

    //generate a random position for each food using these Raylib functions
    Vector2 GenerateRandomPos(deque<Vector2> snakeBody){
        
        Vector2 position = GenerateRandomCell();

        while(ElementInDeque(position,snakeBody)){
            position = GenerateRandomCell();
        }
        return position;
    }

};


class Game{
public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;
    int score = 0;
    int hiscore = score;
    Sound eatSound;
    Sound wallSound;
    Music backgroundMusic;

    Game(){
        InitAudioDevice();
        eatSound = LoadSound("Sound/eat.mp3");
        wallSound = LoadSound("Sound/wall.wav");
        backgroundMusic = LoadMusicStream("Sound/background.mp3");
        PlayMusicStream(backgroundMusic);
        
        LoadHighScore();
    }

    ~Game(){
        UnloadSound(eatSound);
        UnloadSound(wallSound);
        UnloadMusicStream(backgroundMusic);
        CloseAudioDevice();
    }

    void Draw(){
        food.Draw();
        snake.Draw();
    }

    void Update(){
        if(running){
            snake.Update();
            CheckCollisionWithFood();
            CheckCollisionWithEdges();
            CheckCollisionWithTail();
        }
    }

    void LoadHighScore(){
        ifstream file("hiscore.txt");
        if(file.is_open()){
            file >> hiscore;
            file.close();
        }
        else{
            hiscore = 0;
        }
    }

    void SaveHighScore(){
        ofstream file("hiscore.txt");
        if(file.is_open()){
            file<<hiscore;
            file.close();
        }
    }

    void CheckCollisionWithFood(){
        if(Vector2Equals(snake.body[0],food.position))
        {
            food.position = food.GenerateRandomPos(snake.body);
            snake.addSegment = true;
            score++;
            PlaySound(eatSound);
        }
    }


    void CheckCollisionWithEdges(){
        if(snake.body[0].x==cellCount||snake.body[0].x==-1){
            GameOver();
        }
        if(snake.body[0].y==cellCount||snake.body[0].y==-1){
            GameOver();
        }
    }

    void GameOver(){
        snake.Reset();
        food.position = food.GenerateRandomPos(snake.body);
        running = false;
        if(score>hiscore){
            hiscore = score;
            SaveHighScore();
        }
        score = 0;
        PlaySound(wallSound);
        
    }

    void CheckCollisionWithTail(){
        deque<Vector2> headlessBody = snake.body;
        headlessBody.pop_front();
        if(ElementInDeque(snake.body[0],headlessBody)){
            GameOver();
        }
        
    }


};

int main() {
    //initalizing the window 750x750 pixels
    cout<<"Starting the game..." << endl;
    InitWindow(2*offset + cellSize*cellCount, 2*offset + cellSize*cellCount,"Snake Game");
    SetTargetFPS(60); //frames per second for how fast the game runs

    Game game = Game();
    

    // Main game loop, if user presses escape or x then ends game loop.
    while(WindowShouldClose()==false){
        BeginDrawing();
        UpdateMusicStream(game.backgroundMusic);
        if(eventTriggered(0.13)){
            game.Update();
        }

        if(IsKeyPressed(KEY_UP) && game.snake.direction.y!=1){
            game.snake.direction = {0,-1};
            game.running = true;

        }
        if(IsKeyPressed(KEY_DOWN) && game.snake.direction.y!= -1){
            game.snake.direction = {0,1};
            game.running = true;

        }
        if(IsKeyPressed(KEY_LEFT) && game.snake.direction.x!=1){
            game.snake.direction = {-1,0};
            game.running = true;

        }
        if(IsKeyPressed(KEY_RIGHT) && game.snake.direction.x!=-1){
            game.snake.direction = {1,0};
            game.running = true;

        }

        //drawing the background
        ClearBackground(purple);
        DrawRectangleLinesEx(Rectangle{(float)offset-5, (float)offset-5,(float)cellSize*cellCount+10, 
            (float)cellSize*cellCount+10},5,blueGlow);

        DrawText("Juicy Snake",offset-5,20,40, blueGlow);
        DrawText(TextFormat("%i",game.score),offset-5, offset+cellSize*cellCount+10,40, blueGlow);
        DrawText(TextFormat("Hiscore: %i",game.hiscore),cellSize*cellCount-2*offset, 20 ,40, blueGlow);
        game.Draw();

        EndDrawing();
    }
    CloseWindow();
    return 0;
    
}
