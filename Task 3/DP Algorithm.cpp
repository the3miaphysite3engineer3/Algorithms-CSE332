#include <iostream>
#include <vector>
#include <map>
#include <climits>
using namespace std;

// Structure to save the best k for each (n, pegs) state
map<pair<int, int>, int> bestK;

// Memoization table for minimum number of moves
map<pair<int, int>, long long> memoMoves;

// Function to move a disk
void moveDisk(int disk, char fromPeg, char toPeg) {
    cout << "Move disk " << disk << " from peg " << fromPeg << " to peg " << toPeg << endl;
}

// Solve classic 3-peg Tower of Hanoi with correct disk numbering
void towerOfHanoi3Pegs(int n, char source, char auxiliary, char destination, int startDisk) {
    if (n == 0) return;
    towerOfHanoi3Pegs(n-1, source, destination, auxiliary, startDisk);
    moveDisk(startDisk + n - 1, source, destination);
    towerOfHanoi3Pegs(n-1, auxiliary, source, destination, startDisk);
}

// Function to compute the minimal moves with memoization
long long minMoves(int n, int pegs) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (pegs == 3) return (1LL << n) - 1; // 2^n - 1

    if (memoMoves.count({n, pegs}))
        return memoMoves[{n, pegs}];

    long long minMoveCount = LLONG_MAX;
    int optimalK = -1;

    for (int k = 1; k < n; ++k) {
        long long moves = 2 * minMoves(k, pegs) + minMoves(n - k, pegs - 1);
        if (moves < minMoveCount) {
            minMoveCount = moves;
            optimalK = k;
        }
    }

    bestK[{n, pegs}] = optimalK;
    memoMoves[{n, pegs}] = minMoveCount;
    return minMoveCount;
}

// DP-based 4-peg Hanoi solver with correct disk numbering
void towerOfHanoi4Pegs(int n, char source, char auxiliary1, char auxiliary2, char destination, int startDisk) {
    if (n == 0) return;
    if (n == 1) {
        moveDisk(startDisk, source, destination);
        return;
    }

    int k = bestK[{n, 4}];

    // Step 1: Move k disks to auxiliary1 using 4 pegs
    towerOfHanoi4Pegs(k, source, destination, auxiliary2, auxiliary1, startDisk);

    // Step 2: Move (n-k) disks to destination using 3 pegs
    towerOfHanoi3Pegs(n - k, source, auxiliary2, destination, startDisk + k);

    // Step 3: Move k disks from auxiliary1 to destination using 4 pegs
    towerOfHanoi4Pegs(k, auxiliary1, source, auxiliary2, destination, startDisk);
}

int main() {
    int n = 8; // Number of disks

    cout << "Tower of Hanoi with 4 pegs (Dynamic Programming solution) for " << n << " disks:\n\n";

    // Precompute minimal moves and bestK
    minMoves(n, 4);

    cout << "Best split of the disks (P) is: " << bestK[{n, 4}] << "\n\n";

    // Solve the Tower of Hanoi
    towerOfHanoi4Pegs(n, 'A', 'B', 'C', 'D', 1); // Start disk numbering from 1

    cout << "\nTotal moves needed: " << memoMoves[{n, 4}] << endl;

    return 0;
}
