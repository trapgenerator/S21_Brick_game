#include "snakeqt.h"

#include <QDebug>
namespace s21 {
SnakeQT::SnakeQT(Controller *controller) : controller_(controller) {
  setWindowTitle("Snake");
  setStyleSheet("background-color: #505050;");
  setFixedSize(DOT_SIZE * WIDTH * 2, DOT_SIZE * (HEIGHT + 2) + 2);
  is_pressed = false;
  timer = new QTimer(this);
  int tick = 1000;
  controller_->SetAction(Start);
  connect(timer, &QTimer::timeout, this, &SnakeQT::update_game);
  timer->start(tick);
}
void SnakeQT::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space) {
    is_pressed = true;
  } else if (event->key() == Qt::Key_S &&
             controller_->updateCurrentState()->pause > 1) {
    controller_->InitGame();
    controller_->userInput(Start, false);
    int tick = 300 - 15 * controller_->updateCurrentState()->level;
    timer->start(tick);
  } else {
    UserAction_t action = Start;
    if (event->key() == Qt::Key_Down) {
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
      close();
    } else if (event->key() == Qt::Key_P) {
      action = Pause;
    } else if (event->key() == ' ') {
      action = Action;
    }
    controller_->userInput(action, false);
    repaint();
  }
}
void SnakeQT::keyReleaseEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space) {
    is_pressed = false;
  }
}
void SnakeQT::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  controller_->userInput(*controller_->GetAction(), false);
  drawGame(controller_->updateCurrentState());
}
void SnakeQT::drawGame(GameInfo_t *game) {
  QPainter painter;
  painter.begin(this);
  QPen pen;
  pen.setWidth(DOT_SIZE);
  pen.setBrush(Qt::black);
  painter.setPen(pen);
  painter.drawRect(15, 15, 330, 630);
  if (controller_->updateCurrentState()->pause == 2)
    drawGameOver(painter);
  else if (controller_->updateCurrentState()->pause == 1) {
    drawPause(painter);
  } else if (controller_->updateCurrentState()->pause == 3) {
    drawWin(painter);
  } else
    drawField(game, painter);
  drawInformation(game, painter);
}
void SnakeQT::drawInformation(GameInfo_t *game, QPainter &painter) {
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
  if (game->pause == 1) {
    painter.drawText(425, 600, QString("Pause"));
  }
}
void SnakeQT::drawGameOver(QPainter &painter) {
  QImage gol(":images/goL.png");
  gol = gol.scaled(DOT_SIZE * 8, DOT_SIZE * 8, Qt::KeepAspectRatio,
                   Qt::SmoothTransformation);
  painter.drawImage(DOT_SIZE * 2, DOT_SIZE * 8, gol);
  QFont f1("Arial", 18, QFont::Bold);
  painter.setFont(f1);
  painter.drawText(DOT_SIZE * 3 + 15, DOT_SIZE * 15, "S - RESTART");
  painter.drawText(DOT_SIZE * 4 - 5, DOT_SIZE * 16, "ESC - EXIT");
}
void SnakeQT::drawWin(QPainter &painter) {
  QImage gol(":images/goW.png");
  gol = gol.scaled(DOT_SIZE * 8, DOT_SIZE * 8, Qt::KeepAspectRatio,
                   Qt::SmoothTransformation);
  painter.drawImage(DOT_SIZE * 2, DOT_SIZE * 8, gol);
  QFont f1("Arial", 18, QFont::Bold);
  painter.setFont(f1);
  painter.drawText(DOT_SIZE * 3 + 15, DOT_SIZE * 15, "S - RESTART");
  painter.drawText(DOT_SIZE * 4 - 5, DOT_SIZE * 16, "ESC - EXIT");
}
void SnakeQT::drawPause(QPainter &painter) {
  QImage pause(":images/timeout.png");
  pause = pause.scaled(DOT_SIZE * 8, DOT_SIZE * 8, Qt::KeepAspectRatio,
                       Qt::SmoothTransformation);
  painter.drawImage(DOT_SIZE * 2, DOT_SIZE * 8, pause);
}
void SnakeQT::drawField(GameInfo_t *game, QPainter &painter) {
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
void SnakeQT::update_game() {
  if (controller_->updateCurrentState()->pause < 1) {
    controller_->SetState(kShifting);
    controller_->userInput(*controller_->GetAction(), false);
    int tick =
        300 - 15 * controller_->updateCurrentState()->level - 100 * is_pressed;
    timer->start(tick);
    repaint();
  }
}
}  // namespace s21
