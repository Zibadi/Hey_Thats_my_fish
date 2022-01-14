#include "raylib.h"
#include "include/functions.h"

int main(void)
{
    const int width  = 1366;
    const int height = 768;

    InitWindow(width, height, "Hey, That's my fish!");

    SetTargetFPS(60);
   
    while (!WindowShouldClose())
    {
      
        BeginDrawing();

            ClearBackground(RAYWHITE);

            drawPlayground();
            
        EndDrawing();
       
    }
   
    CloseWindow();

    return 0;
}