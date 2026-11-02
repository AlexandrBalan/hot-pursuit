#include "Enemy.h"
#include "Player.h"
#include "create_bounding_box.h"

Enemy::Enemy(bn::fixed starting_x, bn::fixed starting_y, bn::size init_size)
{
    sprite.set_x(starting_x);
    sprite.set_y(starting_y);
    this->size = init_size;
    this->bounding_box = create_bounding_box(this->sprite, this->size);
}

void Enemy::update(Player &player)
{
    if (this->sprite.y() > player.sprite.y())
    {
        this->sprite.set_y(this->sprite.y() - speed);
    }
    else if (this->sprite.y() < player.sprite.y())
    {
        this->sprite.set_y(this->sprite.y() + speed);
    }

    if (this->sprite.x() > player.sprite.x())
    {
        this->sprite.set_x(this->sprite.x() - speed);
    }
    else if (this->sprite.x() < player.sprite.x())
    {
        this->sprite.set_x(this->sprite.x() + speed);
    }

    this->bounding_box = create_bounding_box(this->sprite, this->size);
}