#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <utility>
#include <unordered_map>
using namespace std;
using namespace std;

int N = 200;

int heuristica(int x, int y, int endx, int endy) {
	int dx = x - endx;
	int dy = y - endy;
	return dx * dx + dy * dy;
}

struct node {
	int x;
	int y;
	int h;
	bool operator<(const node& other) const {
		return h > other.h;
	}
};

vector<pair<int, int>> hillclimbing(int startx, int starty, int endx, int endy, vector<vector<int>>& matriz) {
	vector<pair<int, int>> rec;
	vector<vector<bool>> visited(N, vector<bool>(N, false));
	vector<pair<int, int>> moves = { {-1,0},{1,0},{0,-1},{0,1},{-1,-1},{-1,1},{1,-1},{1,1} };
	vector<vector<pair<int, int>>> padre(N, vector<pair<int, int>>(N, { -1,-1 }));

	priority_queue<node> pq;
	pq.push({ startx, starty, heuristica(startx, starty, endx, endy) });
	visited[startx][starty] = true;
	bool find = false;

	while (!pq.empty()) {
		node actual = pq.top();
		pq.pop();

		if (actual.x == endx && actual.y == endy) {
			find = true;
			break;
		}

		int heuristicaactual = actual.h;
		for (auto e : moves) {
			int nx = actual.x + e.first;
			int ny = actual.y + e.second;

			if (nx >= 0 && nx < N && ny >= 0 && ny < N && !visited[nx][ny] && matriz[nx][ny] != -1) {
				int nh = heuristica(nx, ny, endx, endy);
				if (nh <= heuristicaactual) {
					pq.push({ nx, ny, nh });
					visited[nx][ny] = true;
					padre[nx][ny] = { actual.x, actual.y };
				}
			}
		}

		if (find) {
			int cx = endx;
			int cy = endy;
			while (!(cx == startx && cy == starty)) {
				rec.push_back({ cx,cy });
				auto p = padre[cx][cy];
				cx = p.first;
				cy = p.second;
			}
			rec.push_back({ startx,starty });
			reverse(rec.begin(), rec.end());
		}
		return rec;
	}
}

int main() {
	int N = 200;
	vector<vector<int>> matriz(N, vector<int>(N, 1));

	for (int i = 5; i < 15; i++) {
		matriz[i][7] = -1;
	}

	vector<pair<int, int>> rec = hillclimbing(0, 0, 10, 10, matriz);

	for (auto e : rec) {
		cout << "(" << e.first << "," << e.second << ")\n";
	}
}
