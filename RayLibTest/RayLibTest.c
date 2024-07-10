#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>

float generateRandomAccel() {
    float randomValue = (float)rand() / RAND_MAX;

    return -(randomValue - 1.0f);
}

int main()
{
    int textY = 0;
    double lastTime = GetTime();

    int positionX = 0;
    int positionY = 0;

    printf("Hello, World!\n");

    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(350, 200, "RayLib Test");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    // dvd movement

    float moveX = 1.0f;
    float moveY = 1.0f;
    float accelX = 0.1f;
    float accelY = 0.1f;
    float accelXDraw = 0.0f;
    float accelYDraw = 0.0f;

    SetWindowPosition(20, 20);

    int screenWidth = GetMonitorWidth(GetCurrentMonitor());
    int screenHeight = GetMonitorHeight(GetCurrentMonitor());

    while (!WindowShouldClose())
    {
        textY = 10;

        moveX += accelX;
        moveY += accelY;

        int nextX = (int)((float)positionX + moveX);
        int nextY = (int)((float)positionY + moveY);

        if (nextX < 0 || nextX + GetScreenWidth() > screenWidth) {
            moveX = -moveX;
            accelX = generateRandomAccel();
        }

        if (nextY < 0 || nextY + GetScreenHeight()> screenHeight) {
            moveY = -moveY;
            accelY = generateRandomAccel();
        }

        positionX += (int)moveX;
        positionY += (int)moveY;

        SetWindowPosition(positionX, positionY);

        BeginDrawing();

        ClearBackground(DARKGRAY);

        double currentTime = GetTime();
        if (currentTime - lastTime >= 0.1)  // Check if 1 second has passed
        {
            lastTime = currentTime;
            accelXDraw = accelX;
            accelYDraw = accelY;
        }

        DrawText(TextFormat("accelX: %f", accelXDraw), 10, textY, 20, BLACK);
        textY += 20;
        DrawText(TextFormat("accelY: %f", accelYDraw), 10, textY, 20, BLACK);
        textY += 20;

        DrawText(TextFormat("moveX: %f", moveX), 10, textY, 20, BLACK);
        textY += 20;
        DrawText(TextFormat("moveY: %f", moveY), 10, textY, 20, BLACK);
        textY += 20;

        // Draw "Hello World!" text at the bottom-left corner
        DrawText("Hello World!", 10, GetRenderHeight() - 30, 20, BLACK);

        // Draw FPS just below the "Hello World!" text
        DrawFPS(10, GetRenderHeight() - 50);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
