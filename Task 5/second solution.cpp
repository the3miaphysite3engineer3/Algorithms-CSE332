#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

// Total number of hiding spots
const int n = 10;

// Target's current position
int targetPos;

// Move the target to an adjacent position (i ± 1)
void moveTarget() {
    int direction = rand() % 2 == 0 ? -1 : 1;
    int nextPos = targetPos + direction;
    if (nextPos < 1) nextPos = 2;
    if (nextPos > n) nextPos = n - 1;
    targetPos = nextPos;
}

// Simulate firing at a position
bool fireAt(int pos) {
    cout << "Shooter fires at position " << pos;
    if (pos == targetPos) {
        cout << " 🔥 HIT!" << endl;
        return true;
    } else {
        cout << " (miss)" << endl;
        return false;
    }
}

int main() {
    srand(time(0));
    targetPos = rand() % n + 1; // Random initial target position

    int time = 0;
    bool hit = false;

    cout << "Starting simulation with target hiding in positions 1 to " << n << "." << endl;

    while (!hit) {
        // Sweep left to right
        for (int i = 1; i <= n && !hit; ++i) {
            hit = fireAt(i);
            if (hit) break;
            moveTarget();
            ++time;
        }

        // Sweep right to left
        for (int i = n; i >= 1 && !hit; --i) {
            hit = fireAt(i);
            if (hit) break;
            moveTarget();
            ++time;
        }
    }

    cout << "Target was hit after " << time << " time steps." << endl;
    return 0;
}