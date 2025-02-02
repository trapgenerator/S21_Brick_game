#include <check.h>

#include "../brick_game/tetris/tetris.h"
START_TEST(spawn_test) {
  GameInfo_t *game = game_info();
  All_info *info = all_info();
  init_game();
  info->current = game_info()->next;
  game_info()->next = (figure *)calloc(1, sizeof(figure));
  get_random_figure();
  spawn(info->current);
  GameInfo_t Check_info = updateCurrentState();
  ck_assert_ptr_eq(game->field, Check_info.field);
  ck_assert_ptr_eq(game->next, Check_info.next);
  free(info->current);
  free(game->next);
  clean_memory();
}
END_TEST

START_TEST(test_tetris_move_left) {
  GameInfo_t *info = game_info();
  All_info *figure_pos = all_info();
  init_game();
  figure_pos->current = game_info()->next;
  game_info()->next = (figure *)calloc(1, sizeof(figure));
  get_random_figure();
  spawn(figure_pos->current);
  paste_figure(figure_pos->current);
  GameInfo_t Check_info = {0};
  Check_info.field = (int **)calloc(HEIGHT, sizeof(int *));
  for (int i = 0; i < HEIGHT; i++) {
    Check_info.field[i] = (int *)calloc(WIDTH, sizeof(int));
  }
  for (int i = 0; i <= HEIGHT - 1; i++) {  // Copy
    for (int j = 0; j <= WIDTH - 1; j++) {
      if (info->field[i][j] == 1) {
        Check_info.field[i][j] = 1;
      }
    }
  }

  for (int i = 0; i <= HEIGHT - 1; i++) {  // left
    for (int j = 0; j <= WIDTH - 1; j++) {
      if (Check_info.field[i][j] == 1) {
        Check_info.field[i][j - 1] = 1;
        Check_info.field[i][j] = 0;
      }
    }
  }

  userInput(Left, false);
  paste_figure(figure_pos->current);

  for (int i = 0; i <= HEIGHT - 1; i++) {  // Equality check
    for (int j = 0; j <= WIDTH - 1; j++) {
      ck_assert_int_eq(info->field[i][j], Check_info.field[i][j]);
    }
  }
  for (int i = 0; i < HEIGHT; i++) {
    free(Check_info.field[i]);
  }
  free(Check_info.field);
  clean_memory();
  free(figure_pos->current);
  free(info->next);
}
END_TEST

START_TEST(test_tetris_move_right) {
  GameInfo_t *info = game_info();
  All_info *figure_pos = all_info();
  init_game();
  figure_pos->current = game_info()->next;
  game_info()->next = (figure *)calloc(1, sizeof(figure));
  get_random_figure();
  paste_figure(figure_pos->current);
  GameInfo_t Check_info = {0};
  Check_info.field = (int **)calloc(HEIGHT, sizeof(int *));
  for (int i = 0; i < HEIGHT; i++) {
    Check_info.field[i] = (int *)calloc(WIDTH, sizeof(int));
  }
  for (int i = 0; i <= HEIGHT - 1; i++) {  // Copy
    for (int j = 0; j <= WIDTH - 1; j++) {
      if (info->field[i][j] == 1) {
        Check_info.field[i][j] = 1;
      }
    }
  }

  for (int i = 0; i <= HEIGHT - 1; i++) {  // Right
    for (int j = WIDTH - 1; j >= 0; j--) {
      if (Check_info.field[i][j] == 1) {
        Check_info.field[i][j + 1] = 1;
        Check_info.field[i][j] = 0;
      }
    }
  }
  userInput(Right, false);
  paste_figure(figure_pos->current);

  for (int i = 0; i <= HEIGHT - 1; i++) {  // Equality check
    for (int j = 0; j <= WIDTH - 1; j++) {
      ck_assert_int_eq(info->field[i][j], Check_info.field[i][j]);
    }
  }
  for (int i = 0; i < HEIGHT; i++) {
    free(Check_info.field[i]);
  }
  free(Check_info.field);
  clean_memory();
  free(figure_pos->current);
  free(info->next);
}
END_TEST

START_TEST(test_tetris_move_down) {
  GameInfo_t *info = game_info();
  All_info *figure_pos = all_info();
  init_game();
  figure_pos->current = game_info()->next;
  game_info()->next = (figure *)calloc(1, sizeof(figure));
  get_random_figure();
  paste_figure(figure_pos->current);
  GameInfo_t Check_info = {0};
  Check_info.field = (int **)calloc(HEIGHT, sizeof(int *));
  for (int i = 0; i < HEIGHT; i++) {
    Check_info.field[i] = (int *)calloc(WIDTH, sizeof(int));
  }
  for (int i = 0; i <= HEIGHT - 1; i++) {  // Copy
    for (int j = 0; j <= WIDTH - 1; j++) {
      if (info->field[i][j] == 1) {
        Check_info.field[i][j] = 1;
      }
    }
  }

  for (int i = HEIGHT - 1; i >= 0; i--) {  // Down
    for (int j = 0; j <= WIDTH - 1; j++) {
      if (Check_info.field[i][j] == 1) {
        Check_info.field[i + 1][j] = 1;
        Check_info.field[i][j] = 0;
      }
    }
  }

  move_down(figure_pos->current);
  paste_figure(figure_pos->current);
  for (int i = 0; i <= HEIGHT - 1; i++) {  // Equality check
    for (int j = 0; j <= WIDTH - 1; j++) {
      ck_assert_int_eq(info->field[i][j], Check_info.field[i][j]);
    }
  }

  for (int i = 0; i < HEIGHT; i++) {
    free(Check_info.field[i]);
  }
  free(Check_info.field);

  void clean_memory();
  free(figure_pos->current);
  free(info->next);
}
END_TEST

// Rotation
START_TEST(test_tetris_rotation) {
  init_game();
  GameInfo_t *info = game_info();
  All_info *figure_pos = all_info();

  info->next->turn = 0;
  info->next->type = 0;
  for (int i = 0; i < 4; i++) {
    info->next->fig[i].x = pos[info->next->type][info->next->turn][i].x;
    info->next->fig[i].y = pos[info->next->type][info->next->turn][i].y;
  }

  figure_pos->current = game_info()->next;
  game_info()->next = (figure *)calloc(1, sizeof(figure));
  get_random_figure();
  spawn(figure_pos->current);
  paste_figure(figure_pos->current);

  userInput(Action, false);  // Rotate figure
  paste_figure(figure_pos->current);
  GameInfo_t Check_info = {0};
  Check_info.field = (int **)calloc(HEIGHT, sizeof(int *));
  for (int i = 0; i < HEIGHT; i++) {
    Check_info.field[i] = (int *)calloc(WIDTH, sizeof(int));
  }

  Check_info.field[2][4] = 1;
  Check_info.field[2][5] = 1;
  Check_info.field[2][6] = 1;
  Check_info.field[2][7] = 1;
  for (int i = 0; i <= HEIGHT - 1; i++) {  // Equality check
    for (int j = 0; j <= WIDTH - 1; j++) {
      ck_assert_int_eq(info->field[i][j], Check_info.field[i][j]);
    }
  }
  for (int i = 0; i < HEIGHT; i++) {
    free(Check_info.field[i]);
  }
  free(Check_info.field);

  void clean_memory();
  free(figure_pos->current);
  free(info->next);
}
END_TEST

START_TEST(test_tetris_action_down) {
  GameInfo_t *info = game_info();
  All_info *figure_pos = all_info();
  init_game();
  info->next->turn = 0;
  info->next->type = 0;
  for (int i = 0; i < 4; i++) {
    info->next->fig[i].x = pos[info->next->type][info->next->turn][i].x;
    info->next->fig[i].y = pos[info->next->type][info->next->turn][i].y;
  }
  figure_pos->current = game_info()->next;
  game_info()->next = (figure *)calloc(1, sizeof(figure));
  get_random_figure();
  spawn(figure_pos->current);
  paste_figure(figure_pos->current);
  GameInfo_t Check_info = {0};
  Check_info.field = (int **)calloc(HEIGHT, sizeof(int *));
  for (int i = 0; i < HEIGHT; i++) {
    Check_info.field[i] = (int *)calloc(WIDTH, sizeof(int));
  }
  Check_info.field[16][5] = 1;
  Check_info.field[17][5] = 1;
  Check_info.field[18][5] = 1;
  Check_info.field[19][5] = 1;

  userInput(Down, false);

  for (int i = 10; i <= HEIGHT - 1; i++) {  // Equality check
    for (int j = 0; j <= WIDTH - 1; j++) {
      ck_assert_int_eq(info->field[i][j], Check_info.field[i][j]);
    }
  }
  for (int i = 0; i < HEIGHT; i++) {
    free(Check_info.field[i]);
  }
  free(Check_info.field);
  clean_memory();
  free(figure_pos->current);
  free(info->next);
}
END_TEST

START_TEST(test_tetris_action_pause) {
  GameInfo_t *info = game_info();
  All_info *figure_pos = all_info();
  init_game();
  figure_pos->current = game_info()->next;
  UserAction_t action = Pause;
  paste_figure(figure_pos->current);
  userInput(action, false);

  ck_assert_int_eq(info->pause, 0);
  clean_memory();
  free(figure_pos->current);
}
END_TEST
START_TEST(test_tetris_fsm_spawn) {
  GameInfo_t *info = game_info();
  All_info *figure_pos = all_info();
  init_game();
  figure_pos->State = SPAWN;
  // UserAction_t action = Up;
  fsm();
  ck_assert_int_eq(figure_pos->State, 2);
  clean_memory();
  free(figure_pos->current);
  free(info->next);
}
END_TEST

// START_TEST(test_tetris_fsm_game_over){
//   GameInfo_t *info = game_info();
//   All_info *figure_pos = all_info();
//   init_game();
//   figure_pos->State = SPAWN;
//   UserAction_t action = Up;
//   fsm(&action);
//   figure_pos->State = GAME_OVER;
//   action = Start;
//   fsm(&action);
//   ck_assert_int_eq(figure_pos->State, 0);
//   clean_memory();
//   free(figure_pos->current);
//   free(info->next);
// }
// END_TEST

// START_TEST(test_tetris_get_signal) {
//   UserAction_t action;
//   get_signal(KEY_UP, &action);
//   ck_assert_int_eq(action, 5);
//   get_signal(KEY_DOWN, &action);
//   ck_assert_int_eq(action, 6);
//   get_signal(KEY_LEFT, &action);
//   ck_assert_int_eq(action, 3);
//   get_signal(KEY_RIGHT, &action);
//   ck_assert_int_eq(action, 4);
//   get_signal(27, &action);
//   ck_assert_int_eq(action, 2);
//   get_signal('s', &action);
//   ck_assert_int_eq(action, 0);
//   get_signal(' ', &action);
//   ck_assert_int_eq(action, 7);
//   get_signal('o', &action);
// }
// END_TEST

START_TEST(test_tetris_clean_field) {
  GameInfo_t *info = game_info();
  All_info *figure_pos = all_info();
  init_game();
  figure_pos->current = game_info()->next;
  game_info()->next = (figure *)calloc(1, sizeof(figure));
  get_random_figure();
  paste_figure(figure_pos->current);
  GameInfo_t Check_info = {0};
  Check_info.field = (int **)calloc(HEIGHT, sizeof(int *));
  for (int i = 0; i < HEIGHT; i++) {
    Check_info.field[i] = (int *)calloc(WIDTH, sizeof(int));
  }
  for (int i = 0; i <= HEIGHT - 1; i++) {  // Copy
    for (int j = 0; j <= WIDTH - 1; j++) {
      Check_info.field[i][j] = 0;
    }
  }
  clean_field();
  for (int i = 0; i <= HEIGHT - 1; i++) {  // Equality check
    for (int j = 0; j <= WIDTH - 1; j++) {
      ck_assert_int_eq(info->field[i][j], Check_info.field[i][j]);
    }
  }

  for (int i = 0; i < HEIGHT; i++) {
    free(Check_info.field[i]);
  }
  free(Check_info.field);
  clean_memory();
  free(figure_pos->current);
  free(info->next);
}
END_TEST

START_TEST(test_tetris_check_full_lines) {
  GameInfo_t *info = game_info();
  All_info *figure_pos = all_info();
  init_game();
  figure_pos->State = SPAWN;
  // UserAction_t action = Up;
  for (int j = 0; j <= WIDTH - 1; j++) {
    info->field[19][j] = 1;
  }
  fsm();
  ck_assert_int_eq(info->score, 100);

  clean_field();
  figure_pos->State = SPAWN;
  for (int j = 0; j <= WIDTH - 1; j++) {
    info->field[19][j] = 1;
    info->field[18][j] = 1;
  }
  fsm();
  ck_assert_int_eq(info->score, 400);

  clean_field();
  figure_pos->State = SPAWN;
  for (int j = 0; j <= WIDTH - 1; j++) {
    info->field[19][j] = 1;
    info->field[18][j] = 1;
    info->field[17][j] = 1;
  }
  fsm();
  ck_assert_int_eq(info->score, 1100);

  clean_field();
  figure_pos->State = SPAWN;
  for (int j = 0; j <= WIDTH - 1; j++) {
    info->field[19][j] = 1;
    info->field[18][j] = 1;
    info->field[17][j] = 1;
    info->field[16][j] = 1;
  }
  fsm();
  ck_assert_int_eq(info->score, 2600);

  clean_memory();
  free(figure_pos->current);
  free(info->next);
}
END_TEST

Suite *suite_test(void) {
  Suite *s = suite_create("test");
  TCase *tc_core = tcase_create("default");
  suite_add_tcase(s, tc_core);

  tcase_add_test(tc_core, spawn_test);
  tcase_add_test(tc_core, test_tetris_move_left);
  tcase_add_test(tc_core, test_tetris_move_right);
  tcase_add_test(tc_core, test_tetris_move_down);
  tcase_add_test(tc_core, test_tetris_rotation);
  tcase_add_test(tc_core, test_tetris_action_down);
  tcase_add_test(tc_core, test_tetris_action_pause);
  tcase_add_test(tc_core, test_tetris_fsm_spawn);
  tcase_add_test(tc_core, test_tetris_clean_field);
  tcase_add_test(tc_core, test_tetris_check_full_lines);
  // tcase_add_test(tc_core, test_tetris_fsm_game_over);

  return s;
}
int main() {
  Suite *case_ = suite_test();
  SRunner *runner = srunner_create(case_);
  srunner_run_all(runner, CK_NORMAL);
  srunner_free(runner);
  return 0;
}