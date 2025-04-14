#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int n = 15;           // Total positions
bool visited[n + 1] = {0};  // Track fired positions
int targetPos;              // Target's current position

// Move the target to an adjacent unvisited spot
void moveTarget() {
    int left = targetPos - 1;
    int right = targetPos + 1;

    if (left >= 1 && !visited[left] && right <= n && !visited[right]) {
        targetPos += (rand() % 2 == 0) ? -1 : 1;
    } else if (left >= 1 && !visited[left]) {
        targetPos = left;
    } else if (right <= n && !visited[right]) {
        targetPos = right;
    }
    // If no valid move, stay (will be caught next shot)
}

// Simulate firing at a position
bool fireAt(int pos) {
    visited[pos] = true;
    cout << "Shooter fires at position " << pos;
    if (pos == targetPos) {
        cout << " 🔥 HIT!" << endl;
        return true;
    } else {
        cout << " (miss)" << endl;
        moveTarget();
        return false;
    }
}

// Divide and Conquer Shooting
bool shoot(int left, int right, bool leftToRight) {
    if (left > right) return false;

    int mid = (left + right) / 2;

    if (fireAt(mid)) return true;

    bool hit;
    if (leftToRight) {
        hit = shoot(left, mid - 1, !leftToRight);
        if (hit) return true;
        hit = shoot(mid + 1, right, !leftToRight);
    } else {
        hit = shoot(mid + 1, right, !leftToRight);
        if (hit) return true;
        hit = shoot(left, mid - 1, !leftToRight);
    }

    return hit;
}

int main() {
    srand(time(0));
    targetPos = rand() % n + 1;

    cout << "Target is hiding in 1 to " << n << ", starting search...\n";

    bool hit = shoot(1, n, true);

    if (hit) {
        cout << "✅ Target successfully hit using Divide and Conquer!" << endl;
    } else {
        cout << "❌ Target escaped (should never happen with assumption)." << endl;
    }

    return 0;
}