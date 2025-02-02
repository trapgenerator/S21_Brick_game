#ifndef SNAKEQT_H
#define SNAKEQT_H

#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QVBoxLayout>

#include "../../../brick_game/snake/controller.h"
#define HEIGHT 20
#define WIDTH 10
namespace s21 {
class SnakeQT : public QMainWindow {
  Q_OBJECT

 private:
  /**
   * @brief Controller - an instance of the Controller class to manage game
   * logic
   */
  Controller *controller_;

 public:
  /**
   * @brief SnakeQT - constructor for initializing the SnakeQT window
   */
  SnakeQT(Controller *controller);
  /**
   * @brief ~SnakeQT - destructor for the SnakeQT class, default implementation
   */
  ~SnakeQT() = default;

 private:
  /**
   * @brief DOT_SIZE - size of each dot (pixel) in the game grid
   */
  int DOT_SIZE = 30;
  /**
   * @brief drawGame - draws the main game elements based on the current game
   * state
   * @param game - pointer to the current game information
   */
  void drawGame(GameInfo_t *game);
  /**
   * @brief timer - timer for controlling game updates
   */
  QTimer *timer;
  /**
   * @brief update_game - updates the game state and triggers a repaint of the
   * game window
   */
  void update_game();
  /**
   * @brief drawField - renders the game field, including the snake and apple
   * @param game - pointer to the current game information
   * @param painter - reference to the QPainter object used for drawing
   */
  void drawField(GameInfo_t *game, QPainter &painter);
  /**
   * @brief drawInformation - displays game information such as score and level
   * @param game - pointer to the current game information
   * @param painter - reference to the QPainter object used for drawing
   */
  void drawInformation(GameInfo_t *game, QPainter &painter);
  /**
   * @brief drawGameOver - renders the Game Over screen
   * @param painter - reference to the QPainter object used for drawing
   */
  void drawGameOver(QPainter &painter);
  /**
   * @brief drawWin - renders the victory screen
   * @param painter - reference to the QPainter object used for drawing
   */
  void drawWin(QPainter &painter);
  /**
   * @brief drawPause - renders the pause screen
   * @param painter - reference to the QPainter object used for drawing
   */
  void drawPause(QPainter &painter);
  /**
   * @brief is_pressed - flag indicating whether a key is currently pressed
   */
  bool is_pressed;
  /**
   * @brief levelLabel - label for displaying the current level
   */
  QLabel *levelLabel;
  /**
   * @brief scoreLabel - label for displaying the current score
   */
  QLabel *scoreLabel;
  /**
   * @brief speedLabel - label for displaying the game speed
   */
  QLabel *speedLabel;
  /**
   * @brief highScoreLabel - label for displaying the high score
   */
  QLabel *highScoreLabel;
  /**
   * @brief pause - label for displaying the pause status
   */
  QLabel *pause;
  /**
   * @brief victory - label for displaying the victory message
   */
  QLabel *victory;

 protected:
  /**
   * @brief paintEvent - overridden function to handle the paint events for the
   * window
   * @param event - pointer to the paint event object
   */
  void paintEvent(QPaintEvent *event);
  /**
   * @brief keyPressEvent - overridden function to handle key press events
   * @param event - pointer to the key event object
   */
  void keyPressEvent(QKeyEvent *event);
  /**
   * @brief keyReleaseEvent - overridden function to handle key release events
   * @param event - pointer to the key event object
   */
  void keyReleaseEvent(QKeyEvent *event);
};
}  // namespace s21
#endif  // SNAKEQT_H
