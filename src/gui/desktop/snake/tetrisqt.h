#ifndef TETRISQT_H
#define TETRISQT_H

#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QVBoxLayout>
extern "C" {
#include "../../../brick_game/tetris/tetris.h"
}
namespace s21 {
class TetrisQt : public QMainWindow {
  Q_OBJECT
 public:
  TetrisQt();
  void drawGame(GameInfo_t *game);
  void update_game();
  void drawField(GameInfo_t *game, QPainter &painter);
  void drawInformation(GameInfo_t *game, QPainter &painter);
  void drawGameOver(QPainter &painter);
  void drawPause(QPainter &painter);
  void drawNext(GameInfo_t *game, QPainter &painter);
  int DOT_SIZE = 30;
  All_info *info;
  UserAction_t action;
  QTimer *timer;
  QLabel *levelLabel;
  QLabel *scoreLabel;
  QLabel *speedLabel;
  QLabel *highScoreLabel;
  QLabel *pause;
  QLabel *victory;

 protected:
  void paintEvent(QPaintEvent *event);
  void keyPressEvent(QKeyEvent *event);

 signals:
};
}  // namespace s21
#endif  // TETRISQT_H
