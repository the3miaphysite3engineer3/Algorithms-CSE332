//
// Created by AHMED BAKR on 3/1/2024.
//

#ifndef CLOSEDCHESSTOUR_TOUR_H
#define CLOSEDCHESSTOUR_TOUR_H
#define N 8


/**
 * @brief searches for a closed knight tour using Warnsdorff algorithm to find a closed 
 * knight's tour on an 8x8 chessboard.

 * 
 * @param x_init the initial x value on the board
 * @param y_init the initial y value on the board
 * @return true if it finds a closed tour
 * @return false otherwise
 */
bool searchClosedKnightTour(int x_init, int y_init);


/**<_ Helper Methods */

/**
 * @brief initializes the board by giving all cells the value of -1
 * 
 */
void initializeTheBoard();

/**
 * @brief checks if the square's x and y are located on the board
 * 
 * @param x the x of the square to be checked
 * @param y the y of the square to be checked
 * @return true if the square is on the board 
 * @return false otherwise
 */
bool isOnBoardSquare(int x, int y);

/**
 * @brief checks if the square is empty i.e. has not been visited yet
 * 
 * @param x the x of the square to be checked
 * @param y the y of the square to be checked
 * @return true if the square has not been visited before
 * @return false otherwise
 */
bool isEmptySquare(int x, int y);

/**
 * @brief checks if the given two squares are neighbours (a knight can move between them) or not
 * 
 * @param x1 the x value of the first square
 * @param y1 the y value of the first square
 * @param x2 the x value of the second square
 * @param y2 the y value of the second square
 * @return true if the two squares are neighbours
 * @return false otherwise
 */
bool isNeighbourSquare(int x1, int y1, int x2, int y2);

/**
 * @brief picks the next move and marks the square as visited by searching for a neighbour square
 * with the least degree
 * 
 * @param x the x value of the current square
 * @param y the y value of the current square
 * @return true if it picks the next move successfully
 * @return false otherwise
 */
bool pickNextMove(int &x, int &y);

/**
 * @brief Get the Square Degree 
 * 
 * @param x the x value of the square
 * @param y the y value of the square
 * @return int the degree of the square
 */
int getSquareDegree(int x, int y);

/**
 * @brief prints the chess board as numbers that indicates the move no. of the knight
 * 
 */
void printChessBoard();

#endif //CLOSEDCHESSTOUR_TOUR_H
