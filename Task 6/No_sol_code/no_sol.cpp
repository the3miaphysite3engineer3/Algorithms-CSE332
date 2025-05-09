#include <iostream> 

#include <vector> 

#include <queue> 

#include <tuple> 

#include <unordered_map> 

#include <bitset> 

#include <cstring>  // For memset 

using namespace std;



const int N = 3;	// Grid size 

const int MAX_VISITED = 1 << (N * N);	// 2^(N^2) possible visited point combinations 



// Movement directions: right, down, left, up 

const int dx[] = { 0, 1, 0, -1 };

const int dy[] = { 1, 0, -1, 0 };



// Check if (x, y) is inside the grid 

bool inBounds(int x, int y) {

	return x >= 0 && y >= 0 && x < N && y < N;

}



// Convert (x, y) position into a bitmask index 

int pointToBit(int x, int y) {

	return x * N + y;

}



// dp[x][y][dir][visited_mask] = lines_used to reach this state 

int dp[N][N][4][MAX_VISITED];



// State to store in BFS queue 

struct State {

	int x, y, dir, visited, lines;

};



int solve() {

	queue<State> q;

	memset(dp, -1, sizeof(dp));  // Mark all states unvisited 



	// Start from (0, 0) in all 4 directions 

	for (int d = 0; d < 4; ++d) {

		int mask = 1 << pointToBit(0, 0); // Only (0,0) visited 

		dp[0][0][d][mask] = 1;	// 1 line started 

		q.push({ 0, 0, d, mask, 1 });

	}



	int target_mask = (1 << (N * N)) - 1; // All points visited (all bits = 1) 



	while (!q.empty()) {

		State s = q.front(); q.pop();



		// Found a valid solution with exactly 2n - 2 lines 

		if (s.visited == target_mask && s.lines == 2 * N - 2)

			return s.lines;



		// Try all 4 directions 

		for (int d = 0; d < 4; ++d) {

			int nx = s.x + dx[d];

			int ny = s.y + dy[d];



			if (!inBounds(nx, ny)) continue;



			int new_visited = s.visited | (1 << pointToBit(nx, ny));

			int new_lines = s.lines + (d != s.dir ? 1 : 0); // +1 line if direction changed 



			if (new_lines > 2 * N - 2) continue;



			if (dp[nx][ny][d][new_visited] == -1 || dp[nx][ny][d][new_visited] > new_lines) {

				dp[nx][ny][d][new_visited] = new_lines;

				q.push({ nx, ny, d, new_visited, new_lines });

			}

		}

	}



	return -1;  // No solution found with exactly 2n - 2 lines 

}



int main() {

	cout << "Solving for grid size N = " << N << endl;

	int result = solve();

	if (result != -1)

		cout << "Minimum number of lines used: " << result << endl;

	else

		cout << "It is not possible to solve with exactly 2n-2 lines for N = " << N << endl;

	return 0;

}

