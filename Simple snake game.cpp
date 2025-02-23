#include <iostream>
#include <conio.h>   // Для _kbhit() и _getch()
#include <windows.h> // Для Sleep() и system("cls")

bool gameOver;
const int width = 20;
const int height = 17;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100]; // Координаты хвоста
int nTail; // Текущая длина хвоста

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
    gameOver = false;
	dir = STOP; // Изначальное направление змеи
    x = width / 2;
    y = height / 2;
	fruitX = rand() % width; // Рандомное положение фруктов
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
	system("cls"); // Очистка консоли

	// Верхняя граница
    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;

	// Игровое поле
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

			// Левая граница
            if (j == 0)
                std::cout << "#";

            // Голова змеи
            if (i == y && j == x)
                std::cout << "O";
			// Фрукт
            else if (i == fruitY && j == fruitX)
                std::cout << "F";
            else {
                bool printTail = false;

				// Хвост змеи
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        std::cout << "o";
                        printTail = true;
                    }
                }

                if (!printTail)
                    std::cout << " ";
            }

			// Правая граница
            if (j == width - 1)
                std::cout << "#";
        }
        std::cout << std::endl;
    }

    // Нижняя граница
    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;

	// Отображение счета
    std::cout << "Score: " << score << std::endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a': case 'A':
            dir = LEFT;
            break;
        case 'd': case 'D':
            dir = RIGHT;
            break;
        case 'w': case 'W':
            dir = UP;
            break;
        case 's': case 'S':
            dir = DOWN;
            break;
        case 'x': case 'X':
            gameOver = true; // Выход из игры
            break;
        }
    }
}

void Logic() {
	// Предыдущие координаты головы
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

	// Обновить положение головы
    tailX[0] = x;
    tailY[0] = y;

	// Движение хвоста
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    // Обновить положение головы змеи в зависимости от направления
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // Обнаружение столкновения (сними комментарий, чтобы игнорировать столкновения)
    /*
    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;
    */

    // Wrap-around behavior
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    // Обнаружение самостолкновения
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    // Логика сбора фруктов
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;  //   
                                    // Новое положение фруктов
        fruitY = rand() % height; //
        nTail++; // Увеличить длину хвоста
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(50);
    }

    std::cout << "Game Over! Your journey ends here, but a new adventure awaits if you restart." << std::endl;
	int ch = _getch(); // Ждёт нажатия любой клавиши

    return 0;
}
