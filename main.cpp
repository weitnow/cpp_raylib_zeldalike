#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prob.h"

int main()
{
    // window dimensions
    int windowWidth{384};
    int windowHeight{384};

    // intialize the window
    InitWindow(windowWidth, windowHeight, "Little Knight");

    SetTargetFPS(60);

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    // create a knight instance
    Character knight(windowWidth, windowHeight);

    // create a prob instance
    Texture2D rock = LoadTexture("nature_tileset/Rock.png");
    Prob stone(Vector2{0.0,0.0}, rock);

    // game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // draw the stone
        stone.Render(knight.getWorldPos());

        // draw and update knight
        knight.tick(GetFrameTime());
        // check map bounds
        if (knight.getWorldPos().x < 0.f || 
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        EndDrawing();
    }
    CloseWindow();
}