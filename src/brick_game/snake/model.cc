#include "model.h"
namespace s21 {

// 1. Конструктор, деструктор и инициализация
Model::Model() {
  srand(time(0));
  info.field = new int*[HEIGHT];
  for (int i = 0; i < HEIGHT; i++) {
    info.field[i] = new int[WIDTH];
  }
  InitGameSnake();
}
Model::~Model() {
  for (int i = 0; i < HEIGHT; i++) {
    delete[] info.field[i];
  }
  delete[] info.field;
}

void Model::InitGameSnake() {
  State = kSpawn;
  ResetGameStats();
  ClearField();
  LoadHighScore();
}

void Model::ResetGameStats() {
  info.high_score = 0;
  info.level = 1;
  info.speed = 1;
  info.pause = 0;
  info.score = 0;
  apple = {0, 0};
}

void Model::ClearField() {
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      info.field[i][j] = 0;
    }
  }
}

// 2. Работа с файлом рекордов
void Model::LoadHighScore() {
  std::ifstream inputFile(SNAKE_SCORE_FILE);
  if (!inputFile) {
    CreateHighScoreFile();
    return;
  }

  int highScore = 0;
  inputFile >> highScore;
  if (inputFile.fail()) {
    std::cerr << "Error reading from file!" << std::endl;
  } else {
    info.high_score = highScore;
  }
  inputFile.close();
}

void Model::CreateHighScoreFile() {
  std::ofstream outputFile(SNAKE_SCORE_FILE);
  if (outputFile) {
    outputFile << "0\n";
    info.high_score = 0;
  } else {
    std::cerr << "Failed to create file!" << std::endl;
  }
}

// 3. Управление состоянием игры
GameInfo_t* Model::GameInfo() { return &info; }

GameStateS Model::GetState() { return this->State; }

void Model::SetState(GameStateS St) { this->State = St; }

void Model::ChangeLevel() {
  if ((info.score / 5) + 1 > 9) {
    info.level = 10;
  } else {
    info.level = 1 + info.score / 5;
  }
}

// 4. Спавн и инициализация объектов
void Model::Spawn() {
  for (int i = 0; i < INITIAL_LENGTH; i++) {
    location.push_back({5, 9 - i});
  }
}

void Model::SpawnApple() {
  bool outside = false;
  while (outside != true) {
    outside = true;
    apple.x = rand() % 10;
    apple.y = rand() % 20;
    for (long unsigned int i = 0; i < location.size(); i++) {
      if (apple.x == location[i].x && apple.y == location[i].y) {
        outside = false;
      }
    }
  }
}

// 5. Управление движением змейки
void Model::Move(int dx, int dy) {
  bool canMove = (dx != 0 && location[0].x == location[1].x) ||
                 (dy != 0 && location[0].y == location[1].y);

  if (canMove) {
    fig_loc temporary = location[0];
    location[0].x += dx;
    location[0].y += dy;

    for (long unsigned int i = 1; i < location.size(); i++) {
      fig_loc temporary2 = location[i];
      location[i] = temporary;
      temporary = temporary2;
    }
  } else {
    ShiftSnake();
  }
}

void Model::MoveRight() { Move(1, 0); }
void Model::MoveLeft() { Move(-1, 0); }
void Model::MoveDown() { Move(0, 1); }
void Model::MoveUp() { Move(0, -1); }

void Model::ShiftSnake() {
  int xx = 0;
  int yy = 0;
  if (location[0].x == location[1].x && (location[0].y - location[1].y) == 1)
    yy++;
  else if (location[0].x == location[1].x &&
           (location[0].y - location[1].y) == -1)
    yy--;
  else if (location[0].y == location[1].y &&
           (location[0].x - location[1].x) == 1)
    xx++;
  else
    xx--;
  fig_loc temporary = location[0];
  location[0].x += xx;
  location[0].y += yy;
  for (long unsigned int i = 1; i < location.size(); i++) {
    fig_loc temporary2 = location[i];
    location[i] = temporary;
    temporary = temporary2;
  }
}

// 6. Обработка поля и коллизий
void Model::CleanField() {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      info.field[i][j] = 0;
    }
  }
}
void Model::PutSnakeField() {
  if (location[0].x == apple.x && location[0].y == apple.y) {
    info.field[location[0].y][location[0].x] = 0;
    State = kEating;
  }
  if (location[0].x < 0 || location[0].x > 9 || location[0].y < 0 ||
      location[0].y > 19 || EatingTail()) {
    State = kGameOver;
  } else {
    for (long unsigned int i = 0; i < location.size(); i++) {
      info.field[location[i].y][location[i].x] = 1;
    }
  }
}

void Model::PutAppleField() { info.field[apple.y][apple.x] = 2; }

void Model::AddTail() {
  int xx = 0;
  int yy = 0;
  long unsigned int size = location.size();
  if (location[size - 1].x == location[size - 2].x &&
      (location[size - 1].y - location[size - 2].y) == 1)
    yy--;
  else if (location[size - 1].x == location[size - 2].x &&
           (location[size - 1].y - location[size - 2].y) == -1)
    yy++;
  else if (location[size - 1].y == location[size - 2].y &&
           (location[size - 1].x - location[size - 2].x) == 1)
    xx--;
  else
    xx++;
  location.push_back({location[location.size() - 1].x + xx,
                      location[location.size() - 1].y + yy});
}
bool Model::EatingTail() {
  for (long unsigned int i = 1; i < location.size(); i++) {
    if (location[0].x == location[i].x && location[0].y == location[i].y) {
      return true;
    }
  }
  return false;
}

// 7. Основной игровой цикл
void Model::Fsm(UserAction_t* action) {
  if (*action == Pause) {
    if (info.pause == 0)
      info.pause = 1;
    else if (info.pause == 1)
      info.pause = 0;
    *action = Start;
  }
  if (State == kSpawn) {
    Spawn();
    SpawnApple();
    State = kMoving;
  } else if (State == kShifting && info.pause == 0) {
    if (*action == Right) {
      MoveRight();
    } else if (*action == Left) {
      MoveLeft();
    } else if (*action == Down) {
      MoveDown();
    } else if (*action == Up) {
      MoveUp();
    } else {
      ShiftSnake();
    }
    State = kMoving;
    CleanField();
    *action = Start;
  } else if (State == kEating) {
    info.score++;
    if (info.score == 195) {
      info.pause = 3;
      location.clear();
      *action = Start;
    } else {
      ChangeLevel();
      AddTail();
      SpawnApple();
    }
    State = kMoving;
  } else if (State == kGameOver) {
    if (info.score > info.high_score) {
      void userInput(UserAction_t action, bool hold);
      info.high_score = info.score;
      std::ofstream out;
      out.open(SNAKE_SCORE_FILE, std::ios::trunc);
      if (out.is_open()) {
        out << info.high_score << " ";
      }
      out.close();
    }
    info.pause = 2;
    location.clear();
    *action = Start;
  }
  PutSnakeField();
  PutAppleField();
}
}  // namespace s21