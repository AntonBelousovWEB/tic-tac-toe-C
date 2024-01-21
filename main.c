#include "raylib.h"

#define BOARD_SIZE 3

int board[BOARD_SIZE][BOARD_SIZE] = {0};

void InitGame() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

void DrawBoard() {
    for (int i = 1; i < BOARD_SIZE; i++) {
        DrawLine(0, 100 * i, GetScreenWidth(), 100 * i, LIGHTGRAY);
        DrawLine(100 * i, 0, 100 * i, GetScreenHeight(), LIGHTGRAY);
    }
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 1) {
                DrawText("X", 100 * j + 40, 100 * i + 35, 40, RED);
            } else if (board[i][j] == 2) {
                DrawText("O", 100 * j + 40, 100 * i + 35, 40, BLUE);
            }
        }
    }
}

bool CheckWin() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0) ||
            (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 0)) {
            return true;
        }
    }

    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0)) {
        return true;
    }

    return false;
}

void UpdateGame() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int mouseX = GetMouseX() / 100;
        int mouseY = GetMouseY() / 100;

        if (board[mouseY][mouseX] == 0) {
            static int currentPlayer = 1;
            board[mouseY][mouseX] = currentPlayer;
            currentPlayer = (currentPlayer == 1) ? 2 : 1;

            if (CheckWin()) {
                const char* winnerText = (currentPlayer == 1) ? "Player O wins!" : "Player X wins!";
                BeginDrawing();
                DrawText(winnerText, 15, 15, 20, BLACK);
                EndDrawing();
                WaitTime(1);
                InitGame();
            }
        }
    }
}

int main() {
    const int screenWidth = 300;
    const int screenHeight = 300;
    InitWindow(screenWidth, screenHeight, "Tic-Tac-Toe");
    InitGame();
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        UpdateGame();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawBoard();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}