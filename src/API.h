#ifndef API_H
#define API_H
/**
 * @brief User signals
 *
 * User input, used as signals for fsm and userInput
 * to control the game
 */
#define WIDTH 10
#define HEIGHT 20

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/**
 * @brief coordinates of a point
 * coordinates of a point on the field
 *
 * @param x - The x-axis
 * @param y - The y-axis
 */
typedef struct {
  int x;
  int y;
} fig_loc;

/**
 * @brief figure information
 *
 * @param fig - The array points of figure
 * @param type - The type of figure(I, Z, T, O ...)
 * @param turn - turning the shape
 */
typedef struct {
  fig_loc fig[4];
  int type;
  int turn;
} figure;

typedef struct {
  int **field;
  figure *next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

#endif