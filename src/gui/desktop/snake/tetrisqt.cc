#include "tetrisqt.h"
namespace s21 {
TetrisQt::TetrisQt() {
  setWindowTitle("Tetris");
  setStyleSheet("background-color: #505050;");
  setFixedSize(DOT_SIZE * WIDTH * 2, DOT_SIZE * (HEIGHT + 2) + 2);
  init_game();
  info = all_info();
  info->State = SPAWN;
  timer = new QTimer(this);
  int tick = 1000;
  action = Up;
  connect(timer, &QTimer::timeout, this, &TetrisQt::update_game);
  timer->start(tick);
}
void TetrisQt::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_S && game_info()->pause == 2) {
    clean_field();
    clean_memory();
    init_game();
    info->State = SPAWN;
    action = Up;
    int tick = 1100 - 100 * game_info()->level;
    timer->start(tick);
  } else {
    action = Up;
    if (event->key() == Qt::Key_Space) {
      action = Action;
    } else if (event->key() == Qt::Key_Down) {
      action = Down;
    } else if (event->key() == Qt::Key_Up) {
      action = Up;
    } else if (event->key() == Qt::Key_Left) {
      action = Left;
    } else if (event->key() == Qt::Key_Right) {
      action = Right;
    } else if (event->key() == Qt::Key_Enter) {
      action = Start;
    } else if (event->key() == Qt::Key_Escape) {
      action = Terminate;
      clean_memory();
      close();
    } else if (event->key() == Qt::Key_P) {
      action = Pause;
    } else if (event->key() == ' ') {
      action = Action;
    }
  }
  repaint();
}
void TetrisQt::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  userInput(action, false);
  action = Up;
  drawGame(game_info());
}
void TetrisQt::drawGame(GameInfo_t *game) {
  QPainter painter;
  painter.begin(this);
  QPen pen;
  pen.setWidth(DOT_SIZE);
  pen.setBrush(Qt::black);
  painter.setPen(pen);
  painter.drawRect(15, 15, 330, 630);
  if (game_info()->pause == 2)
    drawGameOver(painter);
  else if (game_info()->pause == 1) {
    drawPause(painter);
  } else
    drawField(game, painter);
  drawNext(game, painter);
  drawInformation(game, painter);
}
void TetrisQt::drawInformation(GameInfo_t *game, QPainter &painter) {
  QPen pen;
  pen.setWidth(DOT_SIZE);
  pen.setBrush(Qt::black);
  painter.setPen(pen);
  painter.drawRect(345, 15, DOT_SIZE * 8, 630);
  pen.setWidth(1);
  pen.setBrush(Qt::green);
  painter.setPen(pen);
  painter.drawRect(30, 30, 300, 600);
  QFont f1("Arial", 18, QFont::Bold);
  painter.setFont(f1);
  painter.drawText(370, 60, QString("High score: %1").arg(game->high_score));
  painter.drawText(370, 120, QString("Score: %1").arg(game->score));
  painter.drawText(370, 180, QString("Level: %1").arg(game->level));
  painter.drawText(370, 240, QString("Next:"));
  if (game->pause == 1) {
    painter.drawText(425, 600, QString("Pause"));
  }
}
void TetrisQt::drawGameOver(QPainter &painter) {
  QImage gol(":images/goL.png");
  gol = gol.scaled(DOT_SIZE * 8, DOT_SIZE * 8, Qt::KeepAspectRatio,
                   Qt::SmoothTransformation);
  painter.drawImage(DOT_SIZE * 2, DOT_SIZE * 8, gol);
  QFont f1("Arial", 18, QFont::Bold);
  painter.setFont(f1);
  painter.drawText(DOT_SIZE * 3 + 15, DOT_SIZE * 15, "S - RESTART");
  painter.drawText(DOT_SIZE * 4 - 5, DOT_SIZE * 16, "ESC - EXIT");
}
void TetrisQt::drawPause(QPainter &painter) {
  QImage pause(":images/timeout.png");
  pause = pause.scaled(DOT_SIZE * 8, DOT_SIZE * 8, Qt::KeepAspectRatio,
                       Qt::SmoothTransformation);
  painter.drawImage(DOT_SIZE * 2, DOT_SIZE * 8, pause);
}
void TetrisQt::drawField(GameInfo_t *game, QPainter &painter) {
  QImage apple(":images/apple.png");
  QImage body(":images/body.png");
  QImage android(":images/android.png");
  apple = apple.scaled(DOT_SIZE - 5, DOT_SIZE - 5, Qt::KeepAspectRatio,
                       Qt::SmoothTransformation);
  body = body.scaled(DOT_SIZE + 5, DOT_SIZE + 5, Qt::KeepAspectRatio,
                     Qt::SmoothTransformation);

  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      if (game->field[i][j] == 1) {
        painter.drawImage(DOT_SIZE * (j + 1) - 2, DOT_SIZE * (i + 1) - 2, body);
      } else if (game->field[i][j] == 2) {
        painter.drawImage(DOT_SIZE * (j + 1) + 5, DOT_SIZE * (i + 1) + 2,
                          apple);
      }
    }
  }
}
void TetrisQt::drawNext(GameInfo_t *game, QPainter &painter) {
  QPen pen;
  QImage body(":images/body.png");
  body = body.scaled(DOT_SIZE + 5, DOT_SIZE + 5, Qt::KeepAspectRatio,
                     Qt::SmoothTransformation);
  pen.setWidth(1);
  pen.setBrush(Qt::black);
  painter.setPen(pen);
  painter.drawRect(405, 260, 120, 120);
  for (int i = 0; i < 4; i++) {
    painter.drawImage(435 + game->next->fig[i].x * DOT_SIZE,
                      258 + game->next->fig[i].y * DOT_SIZE, body);
  }
}
void TetrisQt::update_game() {
  if (game_info()->pause == 0) {
    repaint();
    all_info()->State = SHIFTING;
    int tick = 1100 - 100 * game_info()->level;
    timer->start(tick);
    repaint();
  }
}
}  // namespace s21