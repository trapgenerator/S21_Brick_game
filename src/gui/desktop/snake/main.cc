#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "snakeqt.h"
#include "tetrisqt.h"
void MenuReference(QMainWindow *m) {
  m->setWindowTitle("Menu");
  m->resize(300, 200);
  QWidget *central = new QWidget(m);
  m->setCentralWidget(central);
  QPushButton *snakeBtn = new QPushButton("Snake");
  QPushButton *tetrisBtn = new QPushButton("Tetris");
  QPushButton *exitBtn = new QPushButton("Exit");
  QVBoxLayout *layout = new QVBoxLayout(central);
  layout->setAlignment(Qt::AlignCenter);
  layout->addWidget(snakeBtn);
  layout->addWidget(tetrisBtn);
  layout->addWidget(exitBtn);
  layout->setAlignment(Qt::AlignCenter);
  QObject::connect(tetrisBtn, &QPushButton::clicked, [&]() {
    s21::TetrisQt *t = new s21::TetrisQt();
    t->show();
  });
  QObject::connect(snakeBtn, &QPushButton::clicked, [&]() {
    s21::Model *s = new s21::Model();
    s21::Controller *c = new s21::Controller(s);
    s21::SnakeQT *sn = new s21::SnakeQT(c);
    sn->show();
  });
  QObject::connect(exitBtn, &QPushButton::clicked, [m]() { m->close(); });
}

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QMainWindow menu;
  MenuReference(&menu);
  menu.show();
  return app.exec();
}
