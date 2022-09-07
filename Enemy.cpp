#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;

    width = texture.width / maxFrames;
    height = texture.height;
    speed = 2.5f;
}

void Enemy::tick(float deltaTime)
{
    if (!getAlive())
        return;
    // get to target
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity) < radius)
        velocity = {};
    BaseCharacter::tick(deltaTime);

    // check if enemy is overlaping with player (target) and if so, damage player
    if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(damagePersSec * deltaTime);
    }
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}

Enemy Enemy::createEnemy(Vector2 pos, Character *target, Texture2D idle_texture, Texture2D run_texture)
{
    return Enemy(pos, idle_texture, run_texture);
}

void Enemy::setScale(float newScale)
{
    BaseCharacter::setScale(newScale);
    // adjust how close an enemy comes to a player before it stops moving acording its scalefactor
    radius = radius / 4 * newScale;
}

void Enemy::setTarget(Character *character)
{
    if (character == nullptr)
    {
        target = nullptr;
    }
    target = character;
}