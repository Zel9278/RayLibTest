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
    bool isDVD = false;

    int textTopY = 0;
    int textBottomY = 0;

    int positionX = 0;
    int positionY = 0;

    printf("Hello, World!\n");

    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(350, 200, "RayLib Test");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    float moveX = 1.0f;
    float moveY = 1.0f;
    float accelX = 0.1f;
    float accelY = 0.1f;
    float accelXDraw = 0.0f;
    float accelYDraw = 0.0f;

    SetWindowPosition(20, 20);

    int screenWidth = GetMonitorWidth(GetCurrentMonitor());
    int screenHeight = GetMonitorHeight(GetCurrentMonitor());

    Rectangle rect = { (GetScreenWidth() / 2) - (100 / 2), (GetScreenHeight() / 2) - (100 / 2), 100, 100};

    bool isHeightIncreasing = true;
    bool isWidthIncreasing = true;

    while (!WindowShouldClose())
    {
        textTopY = 10;
        textBottomY = GetRenderHeight() - 30;

        if (IsKeyPressed(KEY_D)) {
			isDVD = !isDVD;
            if (isDVD) {
				positionX = GetWindowPosition().x;
				positionY = GetWindowPosition().y;
                accelX = generateRandomAccel();
				accelY = generateRandomAccel();
			}
		}

        if (isDVD) {
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
        }

        BeginDrawing();

        ClearBackground(DARKGRAY);

        DrawRectangleRec(rect, RED);

        DrawText("Hello,", 10, textTopY, 20, BLACK);
        textTopY += 20;
        DrawText("Window.", 10, textTopY, 20, BLACK);
        textTopY += 20;
        DrawText(TextFormat("isDVD[D]: %s", isDVD ? "true" : "false"), 10, textTopY, 20, BLACK);

        DrawText("Hello World!", 10, textBottomY, 20, BLACK);
        textBottomY -= 20;
        DrawFPS(10, textBottomY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
