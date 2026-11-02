#include <bn_sprite_ptr.h>
#include <bn_fixed.h>
#include <bn_size.h>
#include <bn_rect.h>
#include "bn_sprite_items_knight.h"

#pragma once

class Player
{
public:
    // Create the sprite. This will be moved to a constructor
    bn::sprite_ptr sprite = bn::sprite_items::knight.create_sprite();
    bn::fixed speed;       // The speed of the player
    bn::size size;         // The width and height of the sprite
    bn::rect bounding_box; // The rectangle around the sprite for checking collision

    /**
     * Update the position and bounding box of the player based on d-pad movement.
     */
    Player(bn::fixed xPos,
           bn::fixed yPos,
           bn::fixed playerSpeed,
           bn::rect playerBounds);

    void update();
};