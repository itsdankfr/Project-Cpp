#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <conio.h>
#include <algorithm>

#define SIZE 10
#define Num_Monsters 25

// mode
enum GameMode {
    CLASSIC,
    ADVANCE,
    HELL,
    RULES
};

// map
void displayMap(const std::vector<std::vector<char>>& map) {
    for (const auto& row : map) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
}

// player - movement
void movePlayer(std::vector<std::vector<char>>& map, std::vector<int>& playerPosition) {
    char move;
    std::cout << "Your move? ";
    move = getch();

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

// CLASSIC mode
void setupGame(std::vector<std::vector<char>>& map, std::vector<int>& playerPosition, std::vector<int>& exitPosition, std::vector<int>& keyPosition, GameMode mode) {
    srand(static_cast<unsigned int>(time(nullptr)));

    map.assign(SIZE, std::vector<char>(SIZE, '_'));

    playerPosition[0] = rand() % SIZE;
    playerPosition[1] = rand() % SIZE;
    exitPosition[0] = rand() % SIZE;
    exitPosition[1] = rand() % SIZE;
    keyPosition[0] = rand() % SIZE;
    keyPosition[1] = rand() % SIZE;

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

    map[playerPosition[0]][playerPosition[1]] = 'P';
    map[exitPosition[0]][exitPosition[1]] = 'E';
    map[keyPosition[0]][keyPosition[1]] = 'K';
}

// ADVANCE mode
int calculateDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

std::vector<int> exitPositionAdvance(2), keyPositionAdvance(2);
std::vector<std::vector<int>> monsterPositions(Num_Monsters, std::vector<int>(2));

// map Advance
void setupGameAdvance(std::vector<std::vector<char>>& map, std::vector<int>& playerPosition, std::vector<int>& exitPosition, std::vector<int>& keyPosition, GameMode mode, int numMonster) {
    srand(static_cast<unsigned int>(time(nullptr)));

    map.assign(SIZE, std::vector<char>(SIZE, '_'));

    playerPosition[0] = rand() % SIZE;
    playerPosition[1] = rand() % SIZE;
    exitPosition[0] = rand() % SIZE;
    exitPosition[1] = rand() % SIZE;
    keyPosition[0] = rand() % SIZE;
    keyPosition[1] = rand() % SIZE;

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

    for (int i = 0; i < Num_Monsters; i++) {
        do {
            monsterPositions[i][0] = rand() % SIZE;
            monsterPositions[i][1] = rand() % SIZE;
        } while ((monsterPositions[i][0] == playerPosition[0] && monsterPositions[i][1] == playerPosition[1]) ||
                 (monsterPositions[i][0] == exitPosition[0] && monsterPositions[i][1] == exitPosition[1]) ||
                 (monsterPositions[i][0] == keyPosition[0] && monsterPositions[i][1] == keyPosition[1]));

        map[monsterPositions[i][0]][monsterPositions[i][1]] = 'm';
    }

    map[playerPosition[0]][playerPosition[1]] = 'P';
}

// HELL mode
void moveGateAndKey(std::vector<std::vector<char>>& map, std::vector<int>& exitPosition, std::vector<int>& keyPosition, const std::vector<int>& playerPosition) {
    exitPosition[0] = rand() % SIZE;
    exitPosition[1] = rand() % SIZE;

    keyPosition[0] = rand() % SIZE;
    keyPosition[1] = rand() % SIZE;

    while ((exitPosition[0] == keyPosition[0] && exitPosition[1] == keyPosition[1]) ||
           (exitPosition[0] == playerPosition[0] && exitPosition[1] == playerPosition[1]) ||
           (keyPosition[0] == playerPosition[0] && keyPosition[1] == playerPosition[1])) {
        keyPosition[0] = rand() % SIZE;
        keyPosition[1] = rand() % SIZE;
    }
}

// map HELL
void setupGameHell(std::vector<std::vector<char>>& map, std::vector<int>& playerPosition, std::vector<int>& exitPosition, std::vector<int>& keyPosition, GameMode mode, int numMonster) {
}

// RULES
void displayRules() {
    std::cout << "RULES\n";
    std::cout << "***** You (Player), K (Key), E(Exit).\n***** Move 'P' to 'E' to escape the prison.\n";
    std::cout << "***** If you see 'K', pick it up to acquire the key.\n";
    std::cout << "***** You can't exit without acquiring the key.\n";
    std::cout << "***** Choose your moves wisely!\n";
    std::cout << "***** Good luck!\n";
}

int main() {
    std::vector<std::vector<char>> map(SIZE, std::vector<char>(SIZE));
    std::vector<int> playerPosition(2), exitPosition(2), keyPosition(2);
    GameMode mode;

    while (true) {
        std::cout << "Choose game mode:\n";
        std::cout << "1. Classic\n";
        std::cout << "2. Advance\n";
        std::cout << "3. Hell\n";
        std::cout << "4. Rules\n";
        std::cout << "5. Quit\n";
        std::cout << "Your choice? ";
        int choice;
        std::cin >> choice;
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
                break;
            case 5:
                return 0;
            default:
                std::cout << "\a";
                std::cout << "Invalid choice.\n";
                continue;
        }

        // CLASSIC
        if (choice == 1) {
            setupGame(map, playerPosition, exitPosition, keyPosition, mode);
            displayMap(map);

            int hasKey = 0;
            int maxMoves = 39;
            int currentMove = 0;
            int getExit = 0;

            while (gameOver != 1) {
                movePlayer(map, playerPosition);
                system("cls");

                if ((playerPosition[0] == exitPosition[0] && playerPosition[1] == exitPosition[1]) && (hasKey != 1)) {
                    std::cout << "\a";
                    std::cout << "You can't exit, please acquire the key first\nFrom now the key won't be displayed on the map as a consequence of your impetuous!!!\n";
                    std::cout << "Remember carefully the 'E' position! Good luck!\n";
                    getExit = 1;
                    continue;
                }

                if (playerPosition[0] == exitPosition[0] && playerPosition[1] == exitPosition[1]) {
                    std::cout << "\a";
                    std::cout << "Congrats, you've just escaped the prison\n";
                    gameOver = 1;
                    break;
                }

                int movesleft = maxMoves - currentMove;
                if (currentMove >= maxMoves) {
                    std::cout << "\a";
                    std::cout << "You've run out of moves. The game will be ended!\n";
                    gameOver = 1;
                    break;
                }

                if (movesleft == 20 && hasKey != 1) {
                    std::cout << "\a";
                    std::cout << "You've used 20 moves and the key's still there?\n";
                }

                if (movesleft == 20 && hasKey == 1) {
                    std::cout << "\a";
                    std::cout << "Get to the Exit, your mission is to escape!!\n";
                }

                std::cout << "Moves left : " << movesleft << "\n";
                currentMove++;

                if (playerPosition[0] == keyPosition[0] && playerPosition[1] == keyPosition[1] && getExit != 1) {
                    std::cout << "\a";
                    std::cout << "Congrats, you've found the key!!!\n";
                    keyPosition[0] = keyPosition[1] = -1;
                    hasKey = 1;
                }

                if (playerPosition[0] == keyPosition[0] && playerPosition[1] == keyPosition[1] && getExit == 1) {
                    std::cout << "\a";
                    std::cout << "You've just picked up a key!!! But now what???\n";
                    std::cout << "Still remember where the 'E' is?\n";
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

            while (gameOver != 1) {
                movePlayer(map, playerPosition);
                system("cls");

                // display distance
                if (hasKey != 1) {
                    distance = calculateDistance(playerPosition[0], playerPosition[1], keyPositionAdvance[0], keyPositionAdvance[1]);
                    std::cout << "Distance to key: " << distance << "\n";
                } else {
                    distance = calculateDistance(playerPosition[0], playerPosition[1], exitPositionAdvance[0], exitPositionAdvance[1]);
                    std::cout << "Distance to exit: " << distance << "\n";
                }

                // die when encountering monster
                for (int i = 0; i < Num_Monsters; i++) {
                    if (playerPosition[0] == monsterPositions[i][0] && playerPosition[1] == monsterPositions[i][1]) {
                        std::cout << "Oh no! You've been caught by a Monster. Game over!\n";
                        gameOver = 1;
                        break;
                    }
                }

                // win condition
                if (playerPosition[0] == exitPositionAdvance[0] && playerPosition[1] == exitPositionAdvance[1]) {
                    std::cout << "\a";
                    std::cout << "Congrats, you've just escaped the prison\n";
                    gameOver = 1;
                    break;
                }

                // count moves
                int movesleft = maxMoves - currentMove;
                if (currentMove >= maxMoves) {
                    std::cout << "\a";
                    std::cout << "You've run out of moves. The game has ended!\n";
                    gameOver = 1;
                    break;
                }

                if (movesleft == 30 && hasKey != 1) {
                    std::cout << "\a";
                    std::cout << "Hurry up there's only 30 moves left\n";
                }

                if (movesleft == 30 && hasKey == 1) {
                    std::cout << "\a";
                    std::cout << "Just find the damn Exit, your mission is to escape???\n";
                }

                std::cout << "Moves left : " << movesleft << "\n";
                currentMove++;

                if (playerPosition[0] == keyPositionAdvance[0] && playerPosition[1] == keyPositionAdvance[1] && getExit != 1) {
                    std::cout << "\a";
                    std::cout << "Congrats, you've found the key!!!\n";
                    keyPositionAdvance[0] = keyPositionAdvance[1] = -1;
                    hasKey = 1;
                }

                displayMap(map);
            }
        }

        // HELL
    }

    return 0;
}


