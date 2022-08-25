#include "raylib.h"
#include "raymath.h"

int main()
{
    // window dimensions
    int windowDimension[2];
    windowDimension[0] = 384;
    windowDimension[1] = 384;

    // intialize the window
    InitWindow(windowDimension[0], windowDimension[1], "Little Knight");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};

    SetTargetFPS(60);

    // game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;
        if (Vector2Length(direction) != 0.0)
        {
            // set mapPos = mapPos - direction
            mapPos = Vector2Subtract(mapPos, Vector2Normalize(direction));
        }

        

        DrawTextureEx(map, direction, 0.0, 4.0, WHITE);

        EndDrawing();
    }
    CloseWindow();

}