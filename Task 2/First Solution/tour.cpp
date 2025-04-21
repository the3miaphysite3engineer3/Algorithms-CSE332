//
// Created by AHMED BAKR on 3/1/2024.
//
#include <iostream>
#include "tour.h"
using namespace std;


int moveX[] = {2,2,1,1,-1,-1,-2,-2};
int moveY[] = {1,-1,2,-2,2,-2,1,-1};
int chessboard[N][N];

void initializeTheBoard() {
    for (auto & i : chessboard) {
        for (int & j : i) {
            j = -1;
        }
    }
}

bool searchClosedKnightTour(int x_init, int y_init) {
    initializeTheBoard();

    int x = x_init;
    int y = y_init;
    chessboard[x][y] = 0;

    for (int i = 0; i < N * N - 1; i++) {
        if (!pickNextMove(x, y))
            return false;
    }

    if (!isNeighbourSquare(x, y, x_init, y_init))
        return false;

    printChessBoard();
    return true;
}

bool isOnBoardSquare(int x, int y) {
    return ((x >= 0) && (y >= 0) && (x < N) && (y < N));
}

bool isEmptySquare(int x, int y) {
    return (isOnBoardSquare(x, y) && chessboard[x][y] < 0);
}

bool isNeighbourSquare(int x1, int y1, int x2, int y2) {
    for (int i = 0; i < N; i++) {
        if ((x2 == (x1 + moveX[i])) && (y2 == (y1 + moveY[i])))
            return true;
    }
    return false;
}

bool pickNextMove(int &x, int &y) {
    int nextMoveIndex = -1;
    int minDegree = N + 1; // initialize the min degree be 9 so that no square has greater degree
    int newX, newY;
    int currentDegree;

    int start = rand() % N;
    for (int count = 0; count < N; count++) {
        int i = (start + count) % N;
        newX = x + moveX[i];
        newY = y + moveY[i];

        if (isEmptySquare(newX, newY)) {
            currentDegree = getSquareDegree(newX, newY);
            if (currentDegree < minDegree) {
                nextMoveIndex = i;
                minDegree = currentDegree;
            }
        }
    }

    if (nextMoveIndex == -1)
        return false;

    newX = x + moveX[nextMoveIndex];
    newY = y + moveY[nextMoveIndex];

    chessboard[newX][newY] = chessboard[x][y] + 1;

    x = newX;
    y = newY;

    return true;
}

int getSquareDegree(int x, int y) {
    int degree = 0;

    for (int i = 0; i < N; i++) {
        int newX = x + moveX[i];
        int newY = y + moveY[i];
        if (isEmptySquare(newX, newY))
            degree++;
    }
    return degree;
}

void printChessBoard() {
    for (auto & i : chessboard) {
        for (int j : i) {
            cout << j << " ";
            if (j < 10)
                cout << " ";
        }
        cout << endl;
    }
}
