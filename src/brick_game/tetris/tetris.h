#ifndef TETRIS_H
#define TETRIS_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../API.h"

#define MAX_SCORE_FILE "max_score_tetris.txt"
/**
 * @brief Game states for fsm
 *
 * Game states for fsm
 */
typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACHING,
  GAME_OVER
} GameState;

/**
 * @brief Info about current figure
 * This structure inclde information about
 * current figure, State, cycle start time,
 * cycle current time.
 * @param current - current figure(on field)
 * @param State - what stage
 * @param start_time - cycle start time
 * @param current_time - cycle current time
 */
typedef struct {
  figure *current;
  GameState State;
} All_info;

/**
 * @brief Game data struct
 *
 * Game logic data
 *
 * @param field Game field
 * @param next Next figure for preview
 * @param score Game score
 * @param high_score Game high score from file
 * @param level Gamel level, max 10
 * @param speed Game speed, max 28
 * @param pause Pause flag
 */

static const fig_loc pos[7][4][4] = {
    // I
    {{{1, 0}, {1, 1}, {1, 2}, {1, 3}},
     {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
     {{1, 0}, {1, 1}, {1, 2}, {1, 3}},
     {{0, 2}, {1, 2}, {2, 2}, {3, 2}}},
    // J
    {{{0, 0}, {1, 0}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {2, 1}},
     {{1, 0}, {1, 1}, {1, 2}, {2, 2}},
     {{0, 1}, {1, 1}, {2, 0}, {2, 1}}},
    // L
    {{{0, 2}, {1, 0}, {1, 1}, {1, 2}},
     {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
     {{1, 0}, {1, 1}, {1, 2}, {2, 0}},
     {{0, 0}, {0, 1}, {1, 1}, {2, 1}}},
    // O
    {{{0, 1}, {0, 2}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {1, 2}}},
    // S
    {{{0, 1}, {0, 2}, {1, 0}, {1, 1}},
     {{0, 1}, {1, 1}, {1, 2}, {2, 2}},
     {{0, 1}, {0, 2}, {1, 0}, {1, 1}},
     {{0, 1}, {1, 1}, {1, 2}, {2, 2}}},
    // T
    {{{0, 1}, {1, 0}, {1, 1}, {1, 2}},
     {{0, 1}, {1, 1}, {1, 2}, {2, 1}},
     {{1, 0}, {1, 1}, {1, 2}, {2, 1}},
     {{0, 1}, {1, 0}, {1, 1}, {2, 1}}},
    // Z
    {{{0, 0}, {0, 1}, {1, 1}, {1, 2}},
     {{0, 2}, {1, 1}, {1, 2}, {2, 1}},
     {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
     {{0, 2}, {1, 1}, {1, 2}, {2, 1}}},
};

/**
 * @brief Game loop
 *
 * The loop in which the game takes place
 */
void game_loop();
/**
 * @brief Returns GameInfo_t pointer
 *
 * Returns GameInfo_t pointer to a static structure
 * located inside a function
 *
 * @return GameInfo_t pointer
 */
GameInfo_t *game_info();

/**
 * @brief Returns All_info pointer
 *
 * Returns All_info pointer to a static structure
 * located inside a function
 *
 * @return All_info pointer
 */
All_info *all_info();

/**
 * @brief Update game state
 *
 * Designed to receive data for rendering in the interface
 *
 * @return Game info struct
 */
GameInfo_t updateCurrentState();

/**
 * @brief User input - moving figure
 *
 * Moving a figure based on user input
 *
 * @param action - User input
 * @param hold - Pressing a key
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Finite state machine
 *
 * Finite state machine:
 * switches game states
 */
void fsm(/*UserAction_t *action*/);

/**
 * @brief paste figure
 *
 * inserts a shape into the field
 *
 * @param current - current figure
 */
void paste_figure(figure *current);
/**
 * @brief Initializing game data
 *
 * Primary initializing game data:
 * allocate memory for arrays,
 * assign initial values
 *
 */
void init_game();

/**
 * @brief Generate next figure
 *
 * Generate random next figure,
 * writes to array 'next'
 */
void get_random_figure();

/**
 * @brief Remove lines from field
 *
 * Remove lines from field,
 * counting score, level and speed
 *
 */
void check_full_lines();

/**
 * @brief Generate next figure
 *
 * sets the coordinates of the
 * spawn of the current shape
 *
 * @param current - current figure.
 * @return End game flag
 */
bool spawn(figure *current);

/**
 * @brief auxiliary function
 *
 * This function helps you understand
 * whether the current shape
 * contains an x and y pixel
 *
 * @param current - current figure.
 * @param x - the coordinate X
 * @param y - the coordinate Y
 * @param a - action of function(for move piece down or left/right)
 * @return presence of pixel
 */
bool incurrent(figure *current, int x, int y, char a);

/**
 * @brief turn blocked
 *
 * this function helps to understand
 * whether it is possible
 * to rotate the figure
 *
 * @param current - current figure.
 * @param x - the coordinate X
 * @param y - the coordinate Y
 * @return permission
 */
bool blocked(figure *current, int x, int y);

/**
 * @brief Moving figure left
 *
 * Moving a figure left
 *
 * @param current - current figure.
 */
void move_left(figure *current);

/**
 * @brief Moving figure right
 *
 * Moving a figure right
 *
 * @param current - current figure.
 */
void move_right(figure *current);

/**
 * @brief Connection
 *
 * The function checks the
 * connection to the bottom.
 *
 * @param current - current figure.
 * @param State - a pointer to the state of the game
 *
 * @return connection status.
 */
bool connection(figure *current, GameState *State);
/**
 * @brief Moving figure down
 *
 * lowers the figure all the way down
 *
 * @param current - current figure.
 */
void move_down(figure *current);

/**
 * @brief turning the figure
 *
 * rotates the shape counterclockwise
 *
 * @param current - current figure.
 */
void rotate(figure *current);

/**
 * @brief The game is over
 *
 * a function that transfers the game
 * state to GAME_OVER and waits for a signal
 *
 * @param State - a pointer to the state of the game
 * @param action - User input
 */
void game_over(GameState *State, UserAction_t *action);

/**
 * @brief Clear field
 *
 * Clear array 'field'
 *
 * @param info Game data
 */
void clean_field();

/**
 * @brief Free allocated memory
 *
 * Free allocated memory
 */
void clean_memory();
void clean_other_memory();
#endif