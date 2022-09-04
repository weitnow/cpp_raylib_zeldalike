#include "Prob.h"

Prob::Prob(Vector2 pos, Texture2D tex) :
    worldPos(pos),
    texture(tex)
{

}

void Prob::Render(Vector2 knightPos)
{
    screenPos = Vector2Subtract(worldPos, knightPos);

    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}