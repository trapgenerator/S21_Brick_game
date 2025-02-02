#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../../API.h"
#include "model.h"
/**
 * @brief Info about class controller
 * This class inclde information about
 * statement of Model and current action
 * @param snake - Model class
 * @param action - current action
 */
namespace s21 {
class Controller {
 private:
  Model* snake;
  UserAction_t action;

 public:
  Controller(Model* model) : snake(model) {}
  ~Controller() = default;
  void SetAction(UserAction_t act);
  UserAction_t* GetAction();
  void SetState(GameStateS st);
  void InitGame();
  /**
   * @brief User input - function, that analyze user input
   *
   * @param action - User input
   * @param hold - Pressing a key
   */
  void userInput(UserAction_t action, bool hold);
  /**
   * @brief updateCurrentState - function, that return current game state
   */

  GameInfo_t* updateCurrentState();
};
}  // namespace s21
#endif