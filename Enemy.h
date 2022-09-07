#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    virtual void tick(float deltaTime) override;
    void setTarget(Character* character);
    virtual Vector2 getScreenPos() override;
    Enemy createEnemy(  Vector2 pos = Vector2{}, 
                        Character* target = nullptr, 
                        Texture2D idle_texture = LoadTexture("characters/goblin_idle_spritesheet.png"),
                        Texture2D run_texture = LoadTexture("characters/goblin_run_spritesheet.png"));
    virtual void setScale(float newScale) override;

private:
    Character* target;
    float damagePersSec{10.f};
    float radius{25.f};
};

#endif