#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <conio.h>

using namespace std;
const int Num_Monsters = 25;
int monsterPositions[Num_Monsters][2]; // Mảng lưu vị trí của quái vật
const int SIZE = 10; // Kích thước của map
enum GameMode { CLASSIC, ADVANCE, HELL }; // Các chế độ chơi

void setupGame(char map[SIZE][SIZE], int playerPosition[2], int exitPosition[2], int keyPosition[2], GameMode mode) {
    srand(time(NULL));
    
    // Tạo map với ký tự '_'
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            map[i][j] = '_';
        }
    }

    // Tạo các vị trí ngẫu nhiên cho người chơi, cửa thoát và chìa khóa
    playerPosition[0] = rand() % SIZE;
    playerPosition[1] = rand() % SIZE;
    exitPosition[0] = rand() % SIZE;
    exitPosition[1] = rand() % SIZE;
    keyPosition[0] = rand() % SIZE;
    keyPosition[1] = rand() % SIZE;

    // Đảm bảo các vị trí không bị trùng lặp
    while ((playerPosition[0] == exitPosition[0] && playerPosition[1] == exitPosition[1]) ||
           (playerPosition[0] == keyPosition[0] && playerPosition[1] == keyPosition[1]) ||
           (exitPosition[0] == keyPosition[0] && exitPosition[1] == keyPosition[1])) {
        playerPosition[0] = rand() % SIZE;
        playerPosition[1] = rand() % SIZE;
        exitPosition[0] = rand() % SIZE;
        exitPosition[1] = rand() % SIZE;
        keyPosition[0] = rand() % SIZE;
        keyPosition[1] = rand() % SIZE;
    }

    // Đặt ký tự 'P' cho vị trí người chơi, 'E' cho cửa thoát và 'K' cho chìa khóa
    map[playerPosition[0]][playerPosition[1]] = 'P';
    map[exitPosition[0]][exitPosition[1]] = 'E';
    map[keyPosition[0]][keyPosition[1]] = 'K';
}
void displayMap(char map[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << map[i][j] << " "; // Thay printf bằng cout
        }
        cout << endl; // Thay printf("\n") bằng cout << endl
    }
}
void movePlayer(char map[SIZE][SIZE], int playerPosition[2]) {
    char move;
    cout << "Your move? ";
    move = _getch(); // Sử dụng _getch() trên Windows, thay vì getch()

    int playerX = playerPosition[0];
    int playerY = playerPosition[1];

    switch (move) {
        case 'w':
        case 'W':
            if (playerPosition[0] > 0) {
                map[playerPosition[0]][playerPosition[1]] = '_';
                map[--playerPosition[0]][playerPosition[1]] = 'P';
            }
            break;
        case 's':
        case 'S':
            if (playerPosition[0] < SIZE - 1) {
                map[playerPosition[0]][playerPosition[1]] = '_';
                map[++playerPosition[0]][playerPosition[1]] = 'P';
            }
            break;
        case 'a':
        case 'A':
            if (playerPosition[1] > 0) {
                map[playerPosition[0]][playerPosition[1]] = '_';
                map[playerPosition[0]][--playerPosition[1]] = 'P';
            }
            break;
        case 'd':
        case 'D':
            if (playerPosition[1] < SIZE - 1) {
                map[playerPosition[0]][playerPosition[1]] = '_';
                map[playerPosition[0]][++playerPosition[1]] = 'P';
            }
            break;
        default:
            break;
    }
}
void displayRules() {
    cout << "RULES" << endl;
    cout << "***** You (Player), K (Key), E (Exit)." << endl;
    cout << "***** Move 'P' to 'E' to escape the prison." << endl;
    cout << "***** If you see 'K', pick it up to acquire the key." << endl;
    cout << "***** You can't exit without acquiring the key." << endl;
    cout << "***** Choose your moves wisely!" << endl;
    cout << "***** Good luck!" << endl;
}
int calculateDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}
void setupGameAdvance(char map[SIZE][SIZE], int playerPosition[2], int exitPosition[2], int keyPosition[2], GameMode mode, int numMonster) {
    srand(time(NULL));

    // Tạo map với ký tự '_'
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            map[i][j] = '_';
        }
    }

    // Tạo vị trí ngẫu nhiên cho người chơi, cửa thoát và chìa khóa
    playerPosition[0] = rand() % SIZE;
    playerPosition[1] = rand() % SIZE;
    exitPosition[0] = rand() % SIZE;
    exitPosition[1] = rand() % SIZE;
    keyPosition[0] = rand() % SIZE;
    keyPosition[1] = rand() % SIZE;

    // Đảm bảo không bị trùng lặp vị trí
    while ((playerPosition[0] == exitPosition[0] && playerPosition[1] == exitPosition[1]) ||
           (playerPosition[0] == keyPosition[0] && playerPosition[1] == keyPosition[1]) ||
           (exitPosition[0] == keyPosition[0] && exitPosition[1] == keyPosition[1])) {
        playerPosition[0] = rand() % SIZE;
        playerPosition[1] = rand() % SIZE;
        exitPosition[0] = rand() % SIZE;
        exitPosition[1] = rand() % SIZE;
        keyPosition[0] = rand() % SIZE;
        keyPosition[1] = rand() % SIZE;
    }

    // Tạo vị trí cho các quái vật
    for (int i = 0; i < numMonster; i++) {
        do {
            monsterPositions[i][0] = rand() % SIZE;
            monsterPositions[i][1] = rand() % SIZE;
        } 
        while ((monsterPositions[i][0] == playerPosition[0] && monsterPositions[i][1] == playerPosition[1]) ||
               (monsterPositions[i][0] == exitPosition[0] && monsterPositions[i][1] == exitPosition[1]) ||
               (monsterPositions[i][0] == keyPosition[0] && monsterPositions[i][1] == keyPosition[1]));

        map[monsterPositions[i][0]][monsterPositions[i][1]] = 'M'; // Ký tự 'M' đại diện cho quái vật
    }

    // Đặt vị trí cho người chơi
    map[playerPosition[0]][playerPosition[1]] = 'P';
}

int main() {
    char map[SIZE][SIZE];
    int playerPosition[2], exitPosition[2], keyPosition[2];
    int exitPositionAdvance[2], keyPositionAdvance[2];
    enum GameMode mode;

    while (true) {
        cout << "Choose game mode:\n";
        cout << "1. Classic\n";
        cout << "2. Advance\n";
        cout << "3. Hell\n";
        cout << "4. Rules\n";
        cout << "5. Quit\n";
        cout << "Your choice? ";
        int choice;
        cin >> choice;
        int gameOver = 0;

        switch (choice) {
            case 1:
                mode = CLASSIC;
                break;
            case 2:
                mode = ADVANCE;
                break;
            case 3:
                mode = HELL;
                break;
            case 4:
                displayRules();
                continue;
            case 5:
                return 0;
            default:
                cout << "\aInvalid choice.\n";
                continue;
        }

        // CLASSIC
        if (choice == 1) {
            setupGame(map, playerPosition, exitPosition, keyPosition, mode); // Thiết lập map và các vị trí
            displayMap(map);

            int hasKey = 0;
            int maxMoves = 39;
            int currentMove = 0;
            int getExit = 0;

            while (!gameOver) {
                movePlayer(map, playerPosition);
                system("cls");

                if (playerPosition[0] == exitPosition[0] && playerPosition[1] == exitPosition[1] && !hasKey) {
                    cout << "\aYou can't exit, please acquire the key first\n";
                    cout << "From now the key won't be displayed on the map as a consequence of your impetuous!!!\n";
                    cout << "Remember carefully the 'E' position! Good luck!\n";
                    getExit = 1;
                    continue;
                }

                if (playerPosition[0] == exitPosition[0] && playerPosition[1] == exitPosition[1]) {
                    cout << "\aCongrats, you've just escaped the prison\n";
                    gameOver = 1;
                    break;
                }

                int movesLeft = maxMoves - currentMove;
                if (currentMove >= maxMoves) {
                    cout << "\aYou've run out of moves. The game will be ended!\n";
                    gameOver = 1;
                    break;
                }

                if (movesLeft == 20 && !hasKey) {
                    cout << "\aYou've used 20 moves and the key's still there?\n";
                }

                if (movesLeft == 20 && hasKey) {
                    cout << "\aGet to the Exit, your mission is to escape!!\n";
                }

                cout << "Moves left: " << movesLeft << endl;
                currentMove++;

                if (playerPosition[0] == keyPosition[0] && playerPosition[1] == keyPosition[1] && getExit == 0) {
                    cout << "\aCongrats, you've found the key!!!\n";
                    keyPosition[0] = keyPosition[1] = -1;
                    hasKey = 1;
                }

                displayMap(map);
            }
        }

        // Advance
        if (choice == 2) {
            setupGameAdvance(map, playerPosition, exitPositionAdvance, keyPositionAdvance, mode, Num_Monsters);
            displayMap(map);

            int hasKey = 0;
            int maxMoves = 49;
            int currentMove = 0;
            int getExit = 0;
            int distance;

            while (!gameOver) {
                movePlayer(map, playerPosition);
                system("cls");

                // Hiển thị khoảng cách
                if (!hasKey) {
                    distance = calculateDistance(playerPosition[0], playerPosition[1], keyPositionAdvance[0], keyPositionAdvance[1]);
                    cout << "Distance to key: " << distance << endl;
                } else {
                    distance = calculateDistance(playerPosition[0], playerPosition[1], exitPositionAdvance[0], exitPositionAdvance[1]);
                    cout << "Distance to exit: " << distance << endl;
                }

                // Chết khi gặp quái vật
                for (int i = 0; i < Num_Monsters; i++) {
                    if (playerPosition[0] == monsterPositions[i][0] && playerPosition[1] == monsterPositions[i][1]) {
                        cout << "Oh no! You've been caught by a Monster. Game over!\n";
                        gameOver = 1;
                        break;
                    }
                }

                // Điều kiện thắng
                if (playerPosition[0] == exitPositionAdvance[0] && playerPosition[1] == exitPositionAdvance[1]) {
                    cout << "\aCongrats, you've just escaped the prison\n";
                    gameOver = 1;
                    break;
                }

                // Đếm số bước
                int movesLeft = maxMoves - currentMove;
                if (currentMove >= maxMoves) {
                    cout << "\aYou've run out of moves. The game has ended!\n";
                    gameOver = 1;
                    break;
                }

                if (movesLeft == 30 && !hasKey) {
                    cout << "\aHurry up there's only 30 moves left\n";
                }

                if (movesLeft == 30 && hasKey) {
                    cout << "\aJust find the damn Exit, your mission is to escape???\n";
                }

                cout << "Moves left: " << movesLeft << endl;
                currentMove++;

                if (playerPosition[0] == keyPositionAdvance[0] && playerPosition[1] == keyPositionAdvance[1] && getExit == 0) {
                    cout << "\aCongrats, you've found the key!!!\n";
                    keyPositionAdvance[0] = keyPositionAdvance[1] = -1;
                    hasKey = 1;
                }

                displayMap(map);
            }
        }
    }
    return 0;
}
