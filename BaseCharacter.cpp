#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{
    
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPostLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale 
    };
}
