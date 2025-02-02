#include "../../brick_game/snake/controller.h"
extern "C" {
#include "front.h"
}

void GameLoop() {
  init();
  nodelay(stdscr, TRUE);
  srand(time(0));
  timeout(0);
  s21::Model snake;
  s21::Controller c(&snake);
  bool is_pressed;
  c.SetAction(Start);
  time_t start_time = clock();
  double elapsed_time = 0.0;
  while (1) {
    while (c.updateCurrentState()->pause == 2) {
      int ch = getch();
      if (ch == 27) {
        c.SetAction(Terminate);
        break;
      } else if (ch == 's' || ch == 'S') {
        c.InitGame();
        clear();
        c.SetAction(Start);
      }
    }
    time_t current_time = clock();
    elapsed_time = ((double)(current_time - start_time)) / CLOCKS_PER_SEC;
    if (*c.GetAction() == Start) {
      UserAction_t newAction =
          get_signal_snake(getch(), *c.GetAction(), &is_pressed);
      c.userInput(newAction, is_pressed);
      if (newAction == Action && is_pressed == false) {
        is_pressed = true;
      }
      if (c.updateCurrentState()->pause == 1 &&
          !(newAction == Pause || newAction == Terminate)) {
        c.userInput(Start, false);
      }
    }
    if (*c.GetAction() == Terminate) break;
    if (elapsed_time >=
            (0.3 - c.updateCurrentState()->level * 0.015 - 0.1 * is_pressed) &&
        c.updateCurrentState()->pause < 1) {
      c.SetState(s21::kShifting);
      if (c.updateCurrentState()->pause == 0) {
        start_time = current_time;
        clear();
      }
    }
    c.userInput(*c.GetAction(), false);
    draw(c.updateCurrentState());
    draw_next_apple();
  }
  endinit();
}
int main() {
  GameLoop();
  return 0;
}