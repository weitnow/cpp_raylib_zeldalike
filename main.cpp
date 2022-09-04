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

    // create a prob array
    Prob props[2]{
        Prob{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prob{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}
    };

    // game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // draw the prob array
        for (auto prob : props) 
        {
            prob.Render(knight.getWorldPos());
        }


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
        
        // check for props collision
        for (auto prob : props)
        {
            if (CheckCollisionRecs(prob.getCollisionRect(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }


        EndDrawing();
    }
    CloseWindow();
}