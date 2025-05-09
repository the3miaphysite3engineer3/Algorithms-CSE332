#include <iostream> 

#include <vector> 

#include <set> 

#include <map> 

#include <tuple> 

#include <climits> 

#include <algorithm> 

#include <string> 

using namespace std;



// Define directions: up, down, left, right 

const vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };



// Global variables 

int N;

int total_points;

int best_result = INT_MAX;



// Memoization table for DP 

map<tuple<int, int, int, uint64_t>, int> memo;



// Set to store used line segments 

set<string> used_edges;



// Store current and best paths 

vector<vector<pair<int, int>>> best_path;

vector<pair<int, int>> current_path;



// Check if a point is inside the grid 

bool is_valid(int x, int y) {

	return x >= 0 && x < N && y >= 0 && y < N;

}



// Create a unique key for each undirected line segment 

string edge_key(int x1, int y1, int x2, int y2) {

	if (x1 > x2 || (x1 == x2 && y1 > y2)) {

		swap(x1, x2);

		swap(y1, y2);

	}

	return to_string(x1) + "," + to_string(y1) + "-" + to_string(x2) + "," + to_string(y2);

}



// Count how many unvisited neighbors a cell has 

int count_unvisited_neighbors(int x, int y, uint64_t visited_mask) {

	int count = 0;

	for (auto [dx, dy] : directions) {

		int nx = x + dx, ny = y + dy;

		if (is_valid(nx, ny)) {

			int bit = nx * N + ny;

			if (!(visited_mask & (1ULL << bit))) count++;

		}

	}

	return count;

}



int popcount(uint64_t x) {

	int count = 0;

	while (x) {

		x &= (x - 1); // Clear lowest set bit 

		count++;

	}

	return count;

}



// Main recursive DP function 

int dp(int x, int y, int dir, uint64_t visited_mask, int lines_used) {

	// If all points are visited, save path 

	if (popcount(visited_mask) == total_points)

	{

		if (lines_used < best_result) {

			best_result = lines_used;

			best_path.clear();

			best_path.push_back(current_path);

		}

		return 0;

	}



	// Prune: too many lines used 

	if (lines_used >= best_result) return INT_MAX;



	// Memoization key 

	auto key = make_tuple(x, y, dir, visited_mask);

	if (memo.count(key)) return memo[key];



	int answer = INT_MAX;



	// Sort directions using heuristic 

	vector<int> dir_order = { 0, 1, 2, 3 };

	sort(dir_order.begin(), dir_order.end(), [&](int a, int b) {

		int ax = x + directions[a].first, ay = y + directions[a].second;

		int bx = x + directions[b].first, by = y + directions[b].second;

		int count_a = is_valid(ax, ay) ? count_unvisited_neighbors(ax, ay, visited_mask) : -1;

		int count_b = is_valid(bx, by) ? count_unvisited_neighbors(bx, by, visited_mask) : -1;

		return count_a > count_b;

		});



	for (int d : dir_order) {

		int dx = directions[d].first;

		int dy = directions[d].second;

		int nx = x + dx, ny = y + dy;



		int line_cost = (dir == -1 || dir != d) ? 1 : 0;

		vector<string> added_edges;

		uint64_t new_mask = visited_mask;

		vector<pair<int, int>> segment;



		while (is_valid(nx, ny)) {

			string edge = edge_key(nx - dx, ny - dy, nx, ny);

			if (used_edges.count(edge)) break;



			used_edges.insert(edge);

			added_edges.push_back(edge);



			int bit = nx * N + ny;

			new_mask |= (1ULL << bit);

			segment.push_back({ nx, ny });

			current_path.push_back({ nx, ny });



			int sub_result = dp(nx, ny, d, new_mask, lines_used + line_cost);

			if (sub_result != INT_MAX)

				answer = min(answer, sub_result + line_cost);



			current_path.pop_back();

			nx += dx;

			ny += dy;

		}



		for (auto& e : added_edges)

			used_edges.erase(e);

	}



	return memo[key] = answer;

}



// Solves the problem for a given n 

int solve(int n) {

	N = n;

	total_points = N * N;

	best_result = INT_MAX;



	// Start from the center (or near center) 

	vector<pair<int, int>> starts;

	int mid = N / 2;

	for (int dx = -1; dx <= 1; dx++) {

		for (int dy = -1; dy <= 1; dy++) {

			int x = mid + dx, y = mid + dy;

			if (is_valid(x, y)) starts.emplace_back(x, y);

		}

	}



	// Try all starting positions 

	for (auto [sx, sy] : starts) {

		memo.clear();

		used_edges.clear();

		current_path.clear();



		current_path.push_back({ sx, sy });

		uint64_t start_mask = 1ULL << (sx * N + sy);

		dp(sx, sy, -1, start_mask, 0);

	}



	return best_result;

}



// Main function 

int main() {

	int n;

	cout << "Enter grid size n (recommended ≤ 5): ";

	cin >> n;



	int answer = solve(n);

	cout << "\nMinimum number of lines: " << answer << " (Target: " << (2 * n - 2) << ")\n";



	// Print the path 

	if (!best_path.empty()) {

		auto path = best_path[0];

		cout << "\nPath (straight line segments):\n";

		for (auto [x,y] : path)

			cout << "(" << x << ", " << y << ") -> ";

		cout << "END\n";

	}

	else {

		cout << "No solution found.\n";

	}



	return 0;

}