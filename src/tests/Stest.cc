#include <gtest/gtest.h>

#include "../brick_game/snake/model.h"
TEST(model, constructor) {
  s21::Model s;
  EXPECT_EQ(s.GameInfo()->score, 0);
}
TEST(model, spawn) {
  s21::Model s;
  UserAction_t act = Start;
  s.Fsm(&act);
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(s.GameInfo()->field[9 - i][5], 1);
  }
}
TEST(model, pause) {
  s21::Model s;
  UserAction_t act = Start;
  s.Fsm(&act);

  act = Pause;
  s.Fsm(&act);
  EXPECT_EQ(s.GameInfo()->pause, 1);

  act = Pause;
  s.Fsm(&act);
  EXPECT_EQ(s.GameInfo()->pause, 0);
}
TEST(model, eating_addTail_changelvl) {
  s21::Model s;
  UserAction_t act = Start;
  s.Fsm(&act);
  s.SetState(s21::kEating);
  s.Fsm(&act);
  EXPECT_EQ(s.GameInfo()->score, 1);
  EXPECT_EQ(s.GetState(), s21::kMoving);
  EXPECT_EQ(s.GameInfo()->level, 1);

  s.SetState(s21::kEating);
  s.GameInfo()->score = 194;
  s.Fsm(&act);
  EXPECT_EQ(s.GameInfo()->pause, 3);
  EXPECT_EQ(act, Start);
}
TEST(model, gameOver_cleanField) {
  s21::Model s;
  UserAction_t act = Start;
  s.Fsm(&act);
  s.SetState(s21::kGameOver);
  s.Fsm(&act);
  EXPECT_EQ(s.GameInfo()->pause, 2);
  EXPECT_EQ(act, Start);
}
TEST(model, gameOver_HIGH) {
  s21::Model s;
  UserAction_t act = Start;
  s.Fsm(&act);
  s.GameInfo()->score = 40;
  s.SetState(s21::kGameOver);
  s.Fsm(&act);
  EXPECT_EQ(s.GameInfo()->pause, 2);
  EXPECT_EQ(act, Start);
}
TEST(model, SHIFTING1) {
  s21::Model s;
  UserAction_t act = Start;
  s.Fsm(&act);
  s.SetState(s21::kShifting);
  s.Fsm(&act);
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(s.GameInfo()->field[10 - i][5], 1);
  }
  EXPECT_EQ(s.GetState(), s21::kMoving);

  act = Right;
  s.SetState(s21::kShifting);
  s.Fsm(&act);
  EXPECT_EQ(s.GameInfo()->field[10][6], 1);
  EXPECT_EQ(s.GameInfo()->field[10][5], 1);
  EXPECT_EQ(s.GameInfo()->field[9][5], 1);
  EXPECT_EQ(s.GameInfo()->field[8][5], 1);

  act = Up;
  s.SetState(s21::kShifting);
  s.Fsm(&act);
  EXPECT_EQ(s.GameInfo()->field[9][6], 1);
  EXPECT_EQ(s.GameInfo()->field[10][6], 1);
  EXPECT_EQ(s.GameInfo()->field[10][5], 1);
  EXPECT_EQ(s.GameInfo()->field[9][5], 1);
}
TEST(model, SHIFTING2) {
  s21::Model s;
  UserAction_t act = Start;
  s.Fsm(&act);
  s.SetState(s21::kShifting);
  s.Fsm(&act);
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(s.GameInfo()->field[10 - i][5], 1);
  }
  EXPECT_EQ(s.GetState(), s21::kMoving);

  act = Left;
  s.SetState(s21::kShifting);
  s.Fsm(&act);
  EXPECT_EQ(s.GameInfo()->field[10][4], 1);
  EXPECT_EQ(s.GameInfo()->field[10][5], 1);
  EXPECT_EQ(s.GameInfo()->field[9][5], 1);
  EXPECT_EQ(s.GameInfo()->field[8][5], 1);

  act = Down;
  s.SetState(s21::kShifting);
  s.Fsm(&act);
  EXPECT_EQ(s.GameInfo()->field[11][4], 1);
  EXPECT_EQ(s.GameInfo()->field[10][4], 1);
  EXPECT_EQ(s.GameInfo()->field[10][5], 1);
  EXPECT_EQ(s.GameInfo()->field[9][5], 1);
}
int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}