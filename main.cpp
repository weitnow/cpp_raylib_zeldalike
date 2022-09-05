#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prob.h"
#include "Enemy.h"
#include <string>

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
    Character knight{windowWidth, windowHeight};

    // create a prob array
    Prob props[2]{
        Prob{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prob{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};

    
    // create an array of enemies
    Enemy* enemies[3] {

    };

    // create an enemy
    Enemy goblin{
        Vector2{},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    // set target of enemy to player
    goblin.setTarget(&knight);

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

        if (!knight.getAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightsHealth{"Health: "};
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 3);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
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

        goblin.tick(GetFrameTime());

        // checking if attackrectangle overlap with enemie if mousebutton is pressed
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionRecs(goblin.getCollisionRec(), knight.getWeaponCollisionRec()))
            {
                goblin.setAlive(false);
            }
        }

        EndDrawing();
    }
    CloseWindow();
}