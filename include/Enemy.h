#include "bn_sprite_items_zombie.h"
#include <bn_sprite_ptr.h>
#include <bn_fixed.h>
#include <bn_size.h>
#include <bn_rect.h>
#include "Player.h"

#pragma once

class Enemy
{

public:
    // create a sprite for the enemy (zombie that we made)
    bn::sprite_ptr sprite = bn::sprite_items::zombie.create_sprite();
    bn::fixed speed = 1;   // The speed of the players
    bn::size size;         // The width and height of the sprite
    bn::rect bounding_box; // The rectangle around the sprite for checking collision

    // Constructor
    Enemy(bn::fixed starting_x, bn::fixed starting_y, bn::size init_size);

    void update(Player &player);
};