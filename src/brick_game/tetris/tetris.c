#include "tetris.h"
GameInfo_t *game_info() {
  static GameInfo_t game = {0};
  return &game;
}
All_info *all_info() {
  static All_info info = {0};
  return &info;
}
GameInfo_t updateCurrentState() {
  GameInfo_t *info = game_info();
  return *info;
}

void init_game() {
  GameInfo_t *game = game_info();
  srand(time(NULL));
  FILE *fp = fopen(MAX_SCORE_FILE, "r");
  game->high_score = 0;
  if (fp) {
    int result = fscanf(fp, "%d\n", &game->high_score);
    if (result == EOF) {
      game->high_score = 0;
    }
    fclose(fp);
  } else {
    game->high_score = 0;
  }
  fp = fopen(MAX_SCORE_FILE, "w");
  if (fp) {
    fprintf(fp, "%d\n", game->high_score);
    fclose(fp);
  }
  game->field = (int **)calloc(HEIGHT, sizeof(int *));
  for (int i = 0; i < HEIGHT; i++) {
    game->field[i] = (int *)calloc(WIDTH, sizeof(int));
  }
  game->score = 0;
  game->level = 1;
  game->speed = 1;
  game->pause = 0;
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      game->field[i][j] = 0;
    }
  }
  game->next = (figure *)calloc(1, sizeof(figure));
  get_random_figure();
}

void userInput(UserAction_t action, bool hold) {
  All_info *info = all_info();
  if (action == Right) {
    move_right(info->current);
  } else if (action == Left) {
    move_left(info->current);
  } else if (action == Action) {
    rotate(info->current);
  } else if (action == Down) {
    while (!connection(info->current, &(info->State))) {
      move_down(info->current);
      paste_figure(info->current);
    }
  }
  if (action == Pause) {
    if (game_info()->pause == 0) {
      game_info()->pause = 1;
    } else if (game_info()->pause == 1) {
      game_info()->pause = 0;
    }
  }
  if (hold == true) {
    action = Terminate;
  }
  fsm();
  paste_figure(info->current);
}

void fsm() {
  All_info *info = all_info();
  if (info->State == START) {
    init_game();
    info->State = SPAWN;
  } else if (info->State == SPAWN) {
    free(info->current);
    info->current = NULL;
    check_full_lines();
    info->current = game_info()->next;
    game_info()->next = (figure *)calloc(1, sizeof(figure));
    get_random_figure();

    info->State = MOVING;
    if (spawn(info->current)) {
      info->State = GAME_OVER;
      game_info()->pause = 2;
    }
  } else if (info->State == GAME_OVER) {
    game_info()->pause = 2;
    // game_over(&(info->State), action);
  } else if (info->State == SHIFTING) {
    if (!connection(info->current, &(info->State))) {
      move_down(info->current);
      info->State = MOVING;
    }
  }
}

void get_random_figure() {
  GameInfo_t *game = game_info();
  game->next->turn = 0;
  game->next->type = rand() % 7;
  for (int i = 0; i < 4; i++) {
    game->next->fig[i].x = pos[game->next->type][game->next->turn][i].x;
    game->next->fig[i].y = pos[game->next->type][game->next->turn][i].y;
  }
}
bool spawn(figure *current) {
  bool game_over = false;
  for (int i = 0; i < 4; i++) {
    current->fig[i].x += 4;
    if (game_info()->field[current->fig[i].y][current->fig[i].x] == 1) {
      game_over = true;
    }
  }
  return game_over;
}
void paste_figure(figure *current) {
  GameInfo_t *game = game_info();
  for (int i = 0; i < 4; i++)
    game->field[current->fig[i].y][current->fig[i].x] = 1;
}

bool incurrent(figure *current, int x, int y, char a) {
  bool rez = false;
  if (a == 'd') {
    for (int i = 0; i < 4; i++) {
      if (current->fig[i].y == y && current->fig[i].x == x) rez = true;
    }
  } else if (a == 'r') {
    for (int i = 0; i < 4; i++) {
      if (current->fig[i].x == x && current->fig[i].y == y) rez = true;
    }
  }
  return rez;
}
bool blocked(figure *cur, int x, int y) {
  bool rez = false;
  GameInfo_t *game = game_info();
  for (int i = 0; i < 4; i++) {
    int new_y = pos[cur->type][cur->turn % 4][i].y + y;
    int new_x = pos[cur->type][cur->turn % 4][i].x + x;
    if (game->field[new_y][new_x] == 1 && !incurrent(cur, new_x, new_y, 'r')) {
      rez = true;
      cur->turn--;
      break;
    }
  }
  return rez;
}
void check_full_lines() {
  GameInfo_t *game = game_info();
  int global_total = 0;
  for (int i = 0; i < 20; i++) {
    int total = 0;
    for (int j = 0; j < 10; j++) {
      if (game->field[i][j] == 1) {
        total++;
      }
    }
    if (total == 10) {
      global_total++;
      for (int j = 0; j < 10; j++) {
        game->field[i][j] = 0;
      }
      for (int j = i; j >= 0; j--) {
        for (int k = 0; k < 10; k++) {
          if (j != 0) game->field[j][k] = game->field[j - 1][k];
        }
      }
    }
  }
  switch (global_total) {
    case 1:
      game->score += 100;
      break;
    case 2:
      game->score += 300;
      break;
    case 3:
      game->score += 700;
      break;
    case 4:
      game->score += 1500;
      break;
    default:
      break;
  }
  if (game->score > game->high_score) {
    game->high_score = game->score;
    FILE *file = fopen(MAX_SCORE_FILE, "w");
    fprintf(file, "%d\n", game->high_score);
    fclose(file);
  }
  if ((game->score >= game->level * 600) && game->level < 10) {
    game->level++;
  }
}
void move_left(figure *current) {
  GameInfo_t *game = game_info();
  bool left_stop = false;
  for (int i = 0; i < 4; i++) {
    if (current->fig[i].x < 1 ||
        (game->field[current->fig[i].y][current->fig[i].x - 1] == 1 &&
         !incurrent(current, current->fig[i].x - 1, current->fig[i].y, 'r'))) {
      left_stop = true;
    }
  }
  if (!left_stop) {
    for (int i = 0; i < 4; i++) {
      game->field[current->fig[i].y][current->fig[i].x] = 0;
      current->fig[i].x -= 1;
    }
  }
}
void move_right(figure *current) {
  GameInfo_t *game = game_info();
  bool right_stop = false;
  for (int i = 0; i < 4; i++) {
    if (current->fig[i].x > 8 ||
        (game->field[current->fig[i].y][current->fig[i].x + 1] == 1 &&
         !incurrent(current, current->fig[i].x + 1, current->fig[i].y, 'r'))) {
      right_stop = true;
    }
  }
  if (!right_stop) {
    for (int i = 0; i < 4; i++) {
      game->field[current->fig[i].y][current->fig[i].x] = 0;
      current->fig[i].x += 1;
    }
  }
}
bool connection(figure *current, GameState *State) {
  bool low = false;
  for (int i = 0; i < 4; i++) {
    if ((current->fig[i].y + 1 > HEIGHT - 1) ||
        (game_info()->field[current->fig[i].y + 1][current->fig[i].x] == 1 &&
         !incurrent(current, current->fig[i].x, current->fig[i].y + 1, 'd'))) {
      low = true;
      *State = SPAWN;
      break;
    }
  }
  return low;
}
void move_down(figure *current) {
  for (int i = 0; i < 4; i++) {
    game_info()->field[current->fig[i].y][current->fig[i].x] = 0;
    current->fig[i].y += 1;
  }
}
void rotate(figure *current) {
  GameInfo_t *game = game_info();
  int deductible = 0;
  bool in_borders = true;
  int x = current->fig[0].x - pos[current->type][(current->turn) % 4][0].x;
  int y = current->fig[0].y - pos[current->type][(current->turn) % 4][0].y;
  current->turn++;
  for (int i = 0; i < 4; i++) {
    if (WIDTH - (pos[current->type][(current->turn) % 4][i].x + x) < 1) {
      deductible++;
    } else if (pos[current->type][(current->turn) % 4][i].x + x < 0)
      deductible--;
    if (pos[current->type][(current->turn) % 4][i].y + y > HEIGHT - 1)
      in_borders = false;
  }
  x -= deductible;
  if (in_borders && !blocked(current, x, y)) {
    for (int i = 0; i < 4; i++) {
      game->field[current->fig[i].y][current->fig[i].x] = 0;
      current->fig[i].y = pos[current->type][(current->turn) % 4][i].y + y;
      current->fig[i].x = pos[current->type][(current->turn) % 4][i].x + x;
    }
  }
}
void clean_memory() {
  GameInfo_t *game = game_info();
  for (int i = 0; i < HEIGHT; i++) {
    free(game->field[i]);
  }
  free(game->field);
}
void clean_other_memory() {
  GameInfo_t *game = game_info();
  All_info *info = all_info();
  if (info->current != NULL) free(info->current);
  if (game->next != NULL) {
    free(game->next);
  }
}
void clean_field() {
  GameInfo_t *current = game_info();
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      current->field[i][j] = 0;
    }
  }
}