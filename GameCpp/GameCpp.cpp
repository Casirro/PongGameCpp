#include "raylib.h"

#include <ios>
#include <iostream>
#include <string>


const int screen_width = 800;
const int screen_height = 450;
Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};
struct Ball
{
    float x, y;
    float speedX, speedY;
    float radius;

    void Draw()
    {
        DrawCircle(static_cast<int>(x), static_cast<int>(y), radius, WHITE);
    }
};
struct Paddle
{
    float x, y;
    float speed;
    float width, height;

    Rectangle getRect() const
    {
        return Rectangle{x - width / 2, y - height /2, 10, 100};
    }

    void Draw() const
    {
        DrawRectangleRec(getRect(), WHITE);
    }
};


int main()
{
    InitWindow(screen_width, screen_height, "Pong Game");
    SetWindowState(FLAG_VSYNC_HINT);

    Ball ball;
    ball.x = GetScreenWidth() / 2.0f;
    ball.y = GetScreenHeight() / 2.0f;
    ball.radius = 5;
    ball.speedX = 300;
    ball.speedY = 300;

    Paddle leftPaddle;
    leftPaddle.x = 50;
    leftPaddle.y = GetScreenHeight() / 2;
    leftPaddle.width = 10;
    leftPaddle.height = 100;
    leftPaddle.speed = 500;

    Paddle rightPaddle;
    rightPaddle.x = GetScreenWidth() - 50;
    rightPaddle.y = GetScreenHeight() / 2;
    rightPaddle.width = 10;
    rightPaddle.height = 100;
    rightPaddle.speed = 500;

    const char* winnerText = nullptr;
    int leftPlayerScore = 0;
    int rightPlayerScore = 0;
    
    

    
    while (!WindowShouldClose())
    {
        ball.x += ball.speedX * GetFrameTime();
        ball.y += ball.speedY * GetFrameTime();

        if (ball.y < 0)
        {
            ball.y = 0;
            ball.speedY*= -1;
        }
        if (ball.y > GetScreenHeight())
        {
            ball.y = GetScreenHeight();
            ball.speedY *= -1;
        }

        if (IsKeyDown(KEY_W))
        {
            leftPaddle.y -= leftPaddle.speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_S))
        {
            leftPaddle.y += leftPaddle.speed * GetFrameTime();
        }

        if (IsKeyDown(KEY_UP))
        {
            rightPaddle.y -= rightPaddle.speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_DOWN))
        {
            rightPaddle.y += rightPaddle.speed * GetFrameTime();
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{
            leftPaddle.getRect()
        }))
        {
            if (ball.speedX < 0)
            {
                ball.speedX *= -1.1f;
                ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX;
            }
        }


        
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{
            rightPaddle.getRect()
        }))
        {
            if (ball.speedX > 0)
            {
                ball.speedX *= -1.1f;
                ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * ball.speedX;
            }
            
        }
        

        if (winnerText && IsKeyPressed(KEY_SPACE))
        {
            ball.x = GetScreenWidth() / 2.0f;
            ball.y = GetScreenHeight() / 2.0f;
            ball.speedX = 300;
            ball.speedY = 300;
            winnerText = nullptr;
            
            
        }

        if (ball.x < 0 && !winnerText)
        {
            rightPlayerScore++;
            winnerText = "Right Player Wins!";
        }
        if (ball.x > GetScreenWidth() && !winnerText)
        {
            leftPlayerScore++;
            winnerText = "Left Player Wins!";
        }

        
        BeginDrawing();
        ClearBackground(Dark_Green);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
        DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        DrawFPS(10, 10);
        
        ball.Draw();
        leftPaddle.Draw();
        rightPaddle.Draw();
        DrawText(TextFormat("%i", leftPlayerScore), GetScreenWidth() / 4 - 20, 20, 30, WHITE);
        DrawText(TextFormat("%i", rightPlayerScore), 3*GetScreenWidth() / 4 - 20, 20, 30, WHITE);
        if (winnerText)
        {
            const int textWidth = MeasureText(winnerText, 60);
            DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, BLACK);
            
        }
        
        
        EndDrawing();
    }
    

    CloseWindow();

    return 0;
}


