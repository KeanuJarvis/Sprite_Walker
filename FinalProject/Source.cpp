#include "raylib.h"
#include <iostream> 
// Work done by Keanu, Haochen, Cylas 

class Stanley 
{
public:
    Stanley(const char* texturePath, const char* soundPath, int x, int y);
    ~Stanley();

    void Update();
    void Draw();

    Vector2 position;
    Sound sound;

private:
    Texture2D texture;
    Rectangle frameRec;
    int currentFrame; 
    int framesCounter; 
    int framesSpeed;
    int moveX;
};

Stanley::Stanley(const char* texturePath, const char* soundPath, int x, int y) 
{
    texture = LoadTexture(texturePath); 
    sound = LoadSound(soundPath);
    position = { (float)x, (float)y };
    // Only iterates between two locations while hiding the other three sprites on the screen
    frameRec = { 0.0f, 0.0f, (float)texture.width / 5, (float)texture.height };
    currentFrame = 0; // Initializes currentFrame at 0
    framesCounter = 0; // Initializes framesCounter at 0
    framesSpeed = 8; // Number of spritesheet frames shown by second - aka speed of Stanley
    moveX = 7; // Speed of which Stanley moves on the x-axis
}

Stanley::~Stanley() 
{
    UnloadTexture(texture);
    UnloadSound(sound);
}

void Stanley::Update() 
{
    framesCounter++; // This makes the walking animation possible

    if (IsKeyDown(KEY_RIGHT)) // If right key is pressed then Stanley moves right
    { 
        position.x += moveX;
        if (framesCounter >= (60 / framesSpeed)) 
        {
            framesCounter = 0;
            currentFrame++;
            if (currentFrame > 1) currentFrame = 0; // Switches between sprite 0 and sprite 1
            // This hides the other frames in the animation so that the walking looks natural
            frameRec.x = (float)currentFrame * (float)texture.width / 5;
            PlaySound(sound);
        }
    }
    if (IsKeyDown(KEY_LEFT)) // If left key is pressed then Stanley moves left
    { 
        position.x -= moveX;
        if (framesCounter >= (60 / framesSpeed)) 
        {
            framesCounter = 0;
            currentFrame++;
            if (currentFrame > 3) currentFrame = 2; // Switches between sprite 2 and sprite 3
            // This hides the other frames in the animation so that the walking looks natural
            frameRec.x = (float)currentFrame * (float)texture.width / 5; 
            PlaySound(sound);
        }
    }
}

void Stanley::Draw() 
{
    DrawTextureRec(texture, frameRec, position, WHITE);
}

int main(void) 
{
    const int screenWidth = 1920; // Location of Stanley when screen loads on x-axis (left and right) - 750 pixels from left 
    const int screenHeight = 1080; // Location of Stanley when screen loads on y-axis (up and down) - 300 pixels from the top
    InitWindow(screenWidth, screenHeight, "C++ Programming Final Project - Stanley Sprite");
    InitAudioDevice(); // Initializes sound
    // Location of Stanley when screen loads on x-axis and y-axis 
    SetTargetFPS(60); // Sets game to run at 60 frames-per-second
    Stanley stanley("Sprites/Stanley.png", "Sound/Footsteps.mp3", 750, 300);

    while (!WindowShouldClose()) // Detect window close button or ESC key
    { 
        stanley.Update();
        BeginDrawing();
        ClearBackground(RAYWHITE); // Removes the flickering effect of sprite and makes screen consistently white
        stanley.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}