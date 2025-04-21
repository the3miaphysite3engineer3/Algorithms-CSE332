#include <iostream>
#include <vector>

using namespace std;


#define N 8 // board row or column size

// Function prototypes
bool knightTour(vector<vector<int>>& board, vector<int>& posX, vector<int>& posY, int x, int y, int moveNum);
void visualizeMove(vector<vector<int>>& board, vector<int>& posX, vector<int>& posY, int nextX, int nextY, int moveNum);
void visualizeBacktrack(vector<vector<int>>& board, int nextX, int nextY, int moveNum);

const int X[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int Y[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int main() {
    vector<vector<int>> board(N, vector<int>(N, -1));
    vector<int> posX(1, -1);
    vector<int> posY(1, -1);

    // Starting position
    int startX = 0, startY = 0;
    board[startX][startY] = 0;
    posX[0] = startX;
    posY[0] = startY;

    if (!knightTour(board, posX, posY, startX, startY, 1)) {
        cout << "Solution does not exist" << endl;
    } else {
        cout << "Solution found" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << board[i][j] << " ";
                if (board[i][j] < 10) {
                    cout << " ";
                }
            }
            cout << endl;
        }
        
    }

    return 0;
}

bool knightTour(vector<vector<int>>& board, vector<int>& posX, vector<int>& posY, int x, int y, int moveNum) {
    if (moveNum == N * N) {
        return true;
    }

    for (int i = 0; i < 8; i++) {
        int nextX = x + X[i];
        int nextY = y + Y[i];

        if (nextX >= 0 && nextX < N && nextY >= 0 && nextY < N && board[nextX][nextY] == -1) {
            board[nextX][nextY] = moveNum;
            visualizeMove(board, posX, posY, nextX, nextY, moveNum);

            if (knightTour(board, posX, posY, nextX, nextY, moveNum + 1)) {
                return true;
            }

            visualizeBacktrack(board, nextX, nextY, moveNum);
            board[nextX][nextY] = -1;
        }
    }
    return false;
}

void visualizeMove(vector<vector<int>>& board, vector<int>& posX, vector<int>& posY, int nextX, int nextY, int moveNum) {
    posX.push_back(nextX);
    posY.push_back(nextY);
    cout << "Move to " << nextX << "," << nextY << endl;
}

void visualizeBacktrack(vector<vector<int>>& board, int nextX, int nextY, int moveNum) {
    cout << "No place to move from " << nextX << "," << nextY << ": Backtrack" << endl;
}
