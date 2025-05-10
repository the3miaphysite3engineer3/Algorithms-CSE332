#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int n = 10;  // Total number of hiding spots (n > 2)
int targetPos;     // Target's current position

// Move the target to an adjacent position (±1)
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
    targetPos = rand() % n + 1;  // Random initial target position

    cout << "Starting simulation with target hiding in positions 1 to " << n << "." << endl;
    cout << "Target starts at position: " << targetPos << endl;

    bool hit = false;
    int time = 0;

    // First sweep: fire at 2 to n-1
    for (int i = 2; i <= n - 1 && !hit; ++i) {
        hit = fireAt(i);
        ++time;
        if (!hit) moveTarget();
    }

    // Second sweep: fire at n-1 back to 2
    for (int i = n - 1; i >= 2 && !hit; --i) {
        hit = fireAt(i);
        ++time;
        if (!hit) moveTarget();
    }

    cout << "Target was hit after " << time << " time steps." << endl;
    return 0;
}
