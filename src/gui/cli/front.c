
#include "front.h"

void init() {
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_CYAN);
  init_pair(2, COLOR_BLACK, COLOR_BLUE);
  init_pair(3, COLOR_BLACK, COLOR_BLACK);
  init_pair(4, COLOR_BLACK, COLOR_GREEN);
}
void draw_pause() {
  attrset(COLOR_PAIR(3));
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      mvprintw(i + 1, j * 2 + 1, "  ");
    }
    mvprintw(i + 1, 1, "PAUSE");
    mvprintw(i + 1, 8, "PAUSE");
    mvprintw(i + 1, 15, "PAUSE");
  }
  attroff(COLOR_PAIR(3));
}
void draw(GameInfo_t* game) {
  attrset(COLOR_PAIR(1));
  for (int yy = 0; yy < HEIGHT + 2; yy++) {
    for (int xx = 0; xx < 2 * (WIDTH) + 15; xx++) {
      if (yy == 0 || yy == HEIGHT + 1 || xx == 0 || xx >= 2 * WIDTH + 1)
        mvaddch(yy, xx, ' ');
    }
  }
  move(1, 22);
  printw("HIGHT SCORE:");
  move(2, 22);
  printw("%d", game->high_score);

  move(4, 22);
  printw("SCORE:");
  move(5, 22);
  printw("%d", game->score);

  move(7, 22);
  printw("LEVEL:");
  move(8, 22);
  printw("%d", game->level);
  mvprintw(10, 22, "NEXT:");
  attroff(COLOR_PAIR(1));
  if (game->pause == 2) {
    draw_game_over();
  } else if (game->pause == 3) {
    draw_you_win();
  } else
    draw_field(game);
}
void draw_field(GameInfo_t* game) {
  if (game->pause == 0) {
    for (int i = 0; i < HEIGHT; ++i) {
      for (int j = 0; j < WIDTH; ++j) {
        if (game->field[i][j] == 1) {
          attrset(COLOR_PAIR(2));
          mvprintw(i + 1, j * 2 + 1, "  ");
          attroff(COLOR_PAIR(2));
        } else if (game->field[i][j] == 2) {
          attrset(COLOR_PAIR(4));
          mvprintw(i + 1, j * 2 + 1, "  ");
          attroff(COLOR_PAIR(4));
        }
      }
    }
  } else if (game->pause == 1) {
    draw_pause();
  }
}
void draw_game_over() {
  mvprintw(10, 5, "GAME OVER...");
  mvprintw(17, 6, "esc - exit");
  mvprintw(18, 6, "s - restart");
}
void draw_you_win() {
  mvprintw(10, 5, "GAME OVER...");
  mvprintw(11, 5, "YOU WIN!!!!!");
  mvprintw(17, 6, "esc - exit");
  mvprintw(18, 6, "s - restart");
}
void draw_next_figure(GameInfo_t* game) {
  attrset(COLOR_PAIR(3));
  for (int i = 0; i < 4; i++) mvprintw(11 + i, 24, "        ");
  attroff(COLOR_PAIR(3));
  attrset(COLOR_PAIR(2));
  for (int i = 0; i < 4; i++) {
    mvprintw(11 + game->next->fig[i].y, 26 + game->next->fig[i].x * 2, "  ");
  }
  attroff(COLOR_PAIR(2));
}
void draw_next_apple() {
  attrset(COLOR_PAIR(3));
  for (int i = 0; i < 4; i++) mvprintw(11 + i, 24, "        ");
  attroff(COLOR_PAIR(3));
  attrset(COLOR_PAIR(4));
  mvprintw(11 + 1, 26 + 2, "  ");
  attroff(COLOR_PAIR(4));
}
void get_signal(int user_input, UserAction_t* action) {
  switch (user_input) {
    case KEY_UP:
      *action = Up;
      break;
    case KEY_DOWN:
      *action = Down;
      break;
    case KEY_LEFT:
      *action = Left;
      break;
    case KEY_RIGHT:
      *action = Right;
      break;
    case 27:
      *action = Terminate;
      break;
    case 's':
      *action = Start;
      break;
    case 'p':
      *action = Pause;
      break;
    case 'P':
      *action = Pause;
      break;
    case ' ':
      *action = Action;
      break;
    default:
      break;
  }
}
UserAction_t get_signal_snake(int user_input, UserAction_t action,
                              bool* press) {
  if (user_input == KEY_UP) {
    action = Up;
    *press = false;
  } else if (user_input == KEY_DOWN) {
    action = Down;
    *press = false;
  } else if (user_input == KEY_LEFT) {
    action = Left;
    *press = false;
  } else if (user_input == KEY_RIGHT) {
    action = Right;
    *press = false;
  } else if (user_input == 27) {
    action = Terminate;
    *press = false;
  } else if (user_input == 's') {
    action = Start;
    *press = false;
  } else if (user_input == 'p') {
    action = Pause;
    *press = false;
  } else if (user_input == 'P') {
    action = Pause;
    *press = false;
  }
  if (user_input == ' ' && *press == false) {
    action = Action;
    *press = true;
  }
  return action;
}
void endinit() { endwin(); }