#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

int N = 200;

int heuristica(int x, int y, int endx, int endy) {
	return abs(x - endx) + abs(y - endy);
}

vector<pair<int, int>> MejorElPrimero(int startx, int starty, int endx, int endy, vector<vector<int>>& matriz) {
	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
	vector<pair<int, int>> rec;
	vector<vector<bool>> visited(N, vector<bool>(N, false));
	vector<pair<int, int>> moves = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
	pq.push(make_pair(heuristica(startx, starty, endx, endy), make_pair(startx, starty)));
	visited[startx][starty] = true;

	while (!pq.empty()) {
		auto act = pq.top();
		pq.pop();
		rec.push_back(act.second);

		if (act.second.first == endx && act.second.second == endy) {
			return rec;
		}

		for (auto e : moves) {
			int x = act.second.first + e.first;
			int y = act.second.second + e.second;

			if (x >= 0 && x < N && y >= 0 && y < N && !visited[x][y] && matriz[x][y] != -1) {
				pq.push(make_pair(heuristica(x, y, endx, endy), make_pair(x, y)));
				visited[x][y] = true;
			}
		}
	}
	return rec;
}

int main() {
	vector<vector<int>> matriz(N, vector<int>(N, 1));

	for (int i = 5; i < 15; i++) {
		matriz[i][7] = -1;
	}

	vector<pair<int, int>> rec = MejorElPrimero(0, 0, 10, 10, matriz);

	for (auto e : rec) {
		cout << "(" << e.first << "," << e.second << ")\n";
	}
}
