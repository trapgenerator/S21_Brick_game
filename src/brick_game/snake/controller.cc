#include "controller.h"

namespace s21 {
void Controller::userInput(UserAction_t action, bool hold) {
  if (!hold) {
    this->action = action;
    snake->Fsm(&this->action);
  }
}
void Controller::SetAction(UserAction_t act) { this->action = act; }
UserAction_t* Controller::GetAction() { return &action; }
void Controller::SetState(GameStateS st) { snake->SetState(st); }
void Controller::InitGame() { snake->InitGameSnake(); }
GameInfo_t* Controller::updateCurrentState() { return snake->GameInfo(); }
}  // namespace s21