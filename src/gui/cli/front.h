#ifndef FRONT_H
#define FRONT_H
#include <ncurses.h>
#include <time.h>

#include "../../API.h"
/**
 * @brief Initializing gui
 *
 * Initialize ncurses windiw, settings, colors
 */
void init();

/**
 * @brief draw interface and field
 *
 * the main function that draws the playing field,
 * information about the course of the game,
 * the next figure and the record.
 */
void draw(GameInfo_t* game);
/**
 * @brief draw field
 *
 * This function is intended only for drawing field using Struct GameInfo
 * @param game Game data
 */
void draw_field(GameInfo_t* game);
/**
 * @brief Draw pause
 *
 * This funtion display on the screen pause window
 */
void draw_pause();
/**
 * @brief Draw pause
 *
 * this funtion display on the screen interactive menu that become after loss
 */
void draw_game_over();
/**
 * @brief Draw next figure
 *
 * Print next figure in
 * additional information field
 */
void draw_you_win();
void draw_next_apple();

void draw_next_figure(GameInfo_t* game);
/**
 * @brief Get user signal
 *
 * transfers the pressed key
 * to a user action enum variable
 *
 * @param user_input User input
 *
 * @return User signals enum UserAction_t
 */
void get_signal(int user_input, UserAction_t* action);
/**
 * @brief Close gui
 *
 * Print closing message
 * Close ncurses window
 */
UserAction_t get_signal_snake(int user_input, UserAction_t action, bool* press);
void endinit();
#endif