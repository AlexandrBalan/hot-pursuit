
/**
 * Displays a score and high score.
 * 
 * Score starts a 0 and is increased each time update is called, and reset to 0 when resetScore is
 * called. High score tracks the highest score ever reached.
*/
class ScoreDisplay {
    public:
        ScoreDisplay() :
            score(0), // Start score at 0
            high_score(0), // Start high score at 0
            score_sprites(bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS>()), // Start with empty vector for score sprites
            text_generator(bn::sprite_text_generator(common::fixed_8x16_sprite_font)) // Use a new text generator
        {}

        /**
         * Increases score by 1 and updates high score if needed. Displays score and high score.
         */
        void update() {
            // increase score and update high score if this is the new highest
            score++;
            if(score > high_score) {
                high_score = score;
            }

            // Stop displaying previous scores
            score_sprites.clear();

            // Display new scores
            show_number(SCORE_X, SCORE_Y, score);
            show_number(HIGH_SCORE_X, HIGH_SCORE_Y, high_score);
        }

        /**
         * Displays a number at the given position
         */
        void show_number(int x, int y, int number) {
            // Convert number to a string and then display it
            bn::string<MAX_SCORE_CHARS> number_string = bn::to_string<MAX_SCORE_CHARS>(number);
            text_generator.generate(x, y, number_string, score_sprites);
        }

        /**
         * Sets score back to 0. Does NOT reset high score.
         */
        void resetScore() {
            score = 0;
        }

        int score; // current score
        int high_score; // best core
        bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS> score_sprites; // Sprites to display scores
        bn::sprite_text_generator text_generator; // Text generator for scores
};