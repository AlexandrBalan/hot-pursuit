#include "Player.h"
#include "create_bounding_box.h"

#include <bn_keypad.h>
#include <bn_display.h>

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

static constexpr bn::size PLAYER_SIZE = {8, 8};

Player::Player(bn::fixed xPos,
               bn::fixed yPos,
               bn::fixed playerSpeed,
               bn::rect playerBounds)
{
    sprite.set_x(xPos);
    sprite.set_y(yPos);
    speed = playerSpeed;
    size = PLAYER_SIZE;
    bounding_box = playerBounds;
}

void Player::update()
{
    if (bn::keypad::right_held())
    {
        sprite.set_x(sprite.x() + speed);
    }

    if (this->sprite.x() < MIN_X)
    {
        this->sprite.set_x(MIN_X);
    }

    if (this->sprite.y() < MIN_Y)
    {
        this->sprite.set_y(MIN_Y);
    }

    if (this->sprite.x() > MAX_X)
    {
        this->sprite.set_x(MAX_X);
    }

    if (this->sprite.y() > MAX_Y)
    {
        this->sprite.set_y(MAX_Y);
    }

    if (bn::keypad::left_held())
    {
        sprite.set_x(sprite.x() - speed);
    }
    // TODO: Add logic for up and down

    if (bn::keypad::up_held())
    {
        sprite.set_y(sprite.y() - speed);
    }

    if (bn::keypad::down_held())
    {
        sprite.set_y(sprite.y() + speed);
    }

    bounding_box = create_bounding_box(sprite, size);
}