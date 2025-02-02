#ifndef MODEL_H
#define MODEL_H

#include <fstream>
#include <iostream>
#include <vector>

#include "../../API.h"
namespace s21 {
/**
 * @brief INITIAL_LENGTH - start length
 */
#define INITIAL_LENGTH 4
#define SNAKE_SCORE_FILE "max_score_snake.txt"

/**
 * @brief Game state enum
 */
typedef enum {
  kStart = 0,
  kSpawn,
  kMoving,
  kShifting,
  kEating,
  kGameOver,
  kWin
} GameStateS;

/**
 * @brief Model - main class with game logic
 */
class Model {
 private:
  /**
   * @brief info - struct, that include game state
   */
  GameInfo_t info;
  /**
   * @brief location - snake segments position
   */
  std::vector<fig_loc> location;
  /**
   * @brief apple - apple position
   */
  fig_loc apple;
  /**
   * @brief State - current state of the game
   */
  GameStateS State;

 public:
  /**
   * @brief Model - constructor for initializing the game model
   */
  Model();
  /**
   * @brief ~Model - destructor for cleaning up the resources used by the model
   */
  ~Model();
  /**
   * @brief init_game - initializes the game settings and state
   */
  GameStateS GetState();
  void SetState(GameStateS St);
  /**
   * @brief game_info - retrieves the current game state information
   * @return pointer to the current game state structure
   */
  GameInfo_t* GameInfo();
  /**
   * @brief init_game_snake - initializes the snake's starting position and
   * state
   */
  void InitGameSnake();
  void ResetGameStats();
  void ClearField();
  void LoadHighScore();
  void CreateHighScoreFile();
  /**
   * @brief fsm - processes user actions and updates the game state accordingly
   * @param action - reference to the user action that needs to be processed
   */
  void Fsm(UserAction_t* action);

 private:
  /**
   * @brief put_snake_field - renders the snake on the game field
   */
  void PutSnakeField();
  /**
   * @brief put_apple_field - renders the apple on the game field
   */
  void PutAppleField();
  /**
   * @brief spawn - generates a new snake segment
   */
  void Spawn();
  /**
   * @brief shift_snake - updates the position of the snake by moving all
   * segments
   */
  void ShiftSnake();
  /**
   * @brief spawn_apple - generates a new apple in a random position on the
   * field
   */
  void SpawnApple();
  /**
   * @brief clean_field - clears the game field
   */
  void CleanField();
  void Move(int dx, int dy);
  /**
   * @brief move_right - updates the snake's direction to the right
   */
  void MoveRight();
  /**
   * @brief move_left - updates the snake's direction to the left
   */
  void MoveLeft();
  /**
   * @brief move_down - updates the snake's direction downward
   */
  void MoveDown();
  /**
   * @brief move_up - updates the snake's direction upward
   */
  void MoveUp();
  /**
   * @brief add_tail - increases the snake's length by adding a new segment to
   * the tail
   */
  void AddTail();
  /**
   * @brief eating_tail - checks if the snake has collided with itself
   * @return true if the snake is eating its own tail, false otherwise
   */
  bool EatingTail();
  /**
   * @brief change_level - increases the game's difficulty level
   */
  void ChangeLevel();
  void CleanMemory();
};
}  // namespace s21
#endif