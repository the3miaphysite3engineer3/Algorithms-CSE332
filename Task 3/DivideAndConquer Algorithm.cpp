#include <iostream>
#include <vector>
using namespace std;
int Number_Of_moves=0;

// Function to move a disk from source peg to destination peg
void moveDisk(int disk, char fromPeg, char toPeg) {
    cout << "Move disk " << disk << " from peg " << fromPeg << " to peg " << toPeg << endl;
    Number_Of_moves++;
}

// Function to solve Tower of Hanoi with 4 pegs
void towerOfHanoi4Pegs(int n, char source, char auxiliary1, char auxiliary2, char destination) {
    if (n == 0) return;
    if (n == 1) {
        moveDisk(n, source, destination);
        return;
    }

    // Move n-2 disks to auxiliary1 using all 4 pegs
    towerOfHanoi4Pegs(n-2, source, auxiliary2, destination, auxiliary1);

    // Move the n-1th disk to auxiliary2
    moveDisk(n-1, source, auxiliary2);

    // Move the nth disk to destination
    moveDisk(n, source, destination);

    // Move the n-1th disk from auxiliary2 to destination
    moveDisk(n-1, auxiliary2, destination);

    // Move n-2 disks from auxiliary1 to destination using all 4 pegs
    towerOfHanoi4Pegs(n-2, auxiliary1, source, auxiliary2, destination);
}

int main() {
    int n = 8; // Number of disks
    cout << "Tower of Hanoi with 4 pegs solution for " << n << " disks:" << endl;
    towerOfHanoi4Pegs(n, 'A', 'B', 'C', 'D');
    cout<<"Number Of Moves : " << Number_Of_moves<< endl;
    return 0;
}
