#include "raylib.h"

class Prob
{
public:
    Prob(Vector2 pos, Texture2D tex);
    void Render(Vector2 knightPos);
    Rectangle getCollisionRect(Vector2 knightPos);
private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{4.f};

};