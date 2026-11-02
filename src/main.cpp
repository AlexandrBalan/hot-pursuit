#include <bn_core.h>
#include <bn_display.h>
#include <bn_keypad.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_string.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>

#include "bn_sprite_items_square.h"
#include "bn_sprite_items_zombie.h"

#include "bn_random.h"

#include "bn_sound_items.h"

#include <bn_vector.h>

#include "ScoreDisplay.h"
#include "Player.h"
#include "create_bounding_box.h"

// Width and height of the the player bounding box

static constexpr bn::size ENEMY_SIZE = {8, 8};

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

// sprint 4
class Enemy
{

public:
    // create a sprite for the enemy (zombie that we made)
    bn::sprite_ptr sprite = bn::sprite_items::zombie.create_sprite();
    bn::fixed speed = 1;   // The speed of the players
    bn::size size;         // The width and height of the sprite
    bn::rect bounding_box; // The rectangle around the sprite for checking collision

    // Constructor
    Enemy(bn::fixed starting_x, bn::fixed starting_y, bn::size init_size)
    {
        sprite.set_x(starting_x);
        sprite.set_y(starting_y);
        this->size = init_size;
        this->bounding_box = create_bounding_box(this->sprite, this->size);
    }

    void update(Player &player)
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
};

int main()
{
    bn::core::init();

    bn::random rng;

    // Create a new score display
    ScoreDisplay scoreDisplay = ScoreDisplay();

    // Create a player and initialize it
    // TODO: we will move the initialization logic to a constructor.
    Player player = Player(44, 22, 1.5, create_bounding_box(player.sprite, player.size));

    bn::vector<Enemy, 16> enemyVec = {};
    enemyVec.push_back(Enemy(rng.get_int(MIN_X, MAX_X), rng.get_int(MIN_Y, MAX_Y), ENEMY_SIZE));

    int timer = 180;
    int timeDelay = 1;

    while (true)
    {
        player.update();

        for (Enemy &e : enemyVec)
        {
            e.update(player);

            // Reset the current score and player position if the player collides with enemy
            if (e.bounding_box.intersects(player.bounding_box))
            {
                scoreDisplay.resetScore();
                player.sprite.set_x(44);
                player.sprite.set_y(22);

                e.sprite.set_x(rng.get_int(MIN_X, MAX_X));
                e.sprite.set_y(rng.get_int(MIN_Y, MAX_Y));
            }
        }

        timer -= timeDelay;

        // If the timer reaches 0
        if (timer <= 0)
        {
            enemyVec.push_back(Enemy(rng.get_int(MIN_X, MAX_X), rng.get_int(MIN_Y, MAX_Y), ENEMY_SIZE));

            timer = 180;
        }

        // Update the scores and disaply them
        scoreDisplay.update();

        bn::core::update();
    }
}