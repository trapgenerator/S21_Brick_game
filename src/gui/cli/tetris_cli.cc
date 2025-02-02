extern "C" {
#include "../../brick_game/tetris/tetris.h"
#include "front.h"
}
void game_loop() {
  init_game();
  init();
  All_info* info = all_info();
  info->State = SPAWN;
  UserAction_t action = Up;
  timeout(0);
  time_t start_time;
  time_t current_time;
  start_time = clock();
  double elapsed_time = 0.0;

  while (action != Terminate) {
    current_time = clock();
    elapsed_time = ((double)(current_time - start_time)) / CLOCKS_PER_SEC;
    action = Up;
    get_signal(getch(), &action);
    if (action == Terminate) break;
    if (elapsed_time >= (1.1 - game_info()->level * 0.1) &&
        game_info()->pause == 0) {
      info->State = SHIFTING;
      clear();
      start_time = current_time;
    }
    userInput(action, false);
    if (action == Down || action == Left || action == Right || action == Action)
      clear();
    if (game_info()->pause == 2 && action == Start) {
      clean_field();
      clean_memory();
      init_game();
      info->State = SPAWN;
    }
    draw(game_info());
    draw_next_figure(game_info());
  }
  clean_memory();
  clean_other_memory();
  endinit();
}
int main() {
  game_loop();
  return 0;
}