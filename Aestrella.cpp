#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <utility>
#include <unordered_map>
using namespace std;

int N = 200;

int heuristica(int x, int y, int endx, int endy, vector<vector<int>>& matriz) {
	int dx = x - endx;
	int dy = y - endy;
	int g = dx * dx + dy * dy;
	return g + matriz[x][y];
}

struct node {
	int x;
	int y;
	int h;
	bool operator<(const node& other) const {
		return h > other.h;
	}
};

vector<pair<int, int>> Aestrella(int startx, int starty, int endx, int endy, vector<vector<int>>& matriz) {
	vector<pair<int, int>> rec;
	vector<vector<bool>> visited(N, vector<bool>(N, false));
	vector<pair<int, int>> moves = { {-1,0},{1,0},{0,-1},{0,1},{-1,-1},{-1,1},{1,-1},{1,1} };
	vector<vector<pair<int, int>>> padre(N, vector<pair<int, int>>(N, { -1,-1 }));

	priority_queue<node> pq;
	pq.push({ startx, starty, heuristica(startx, starty, endx, endy, matriz) });
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
				int nh = heuristica(nx, ny, endx, endy, matriz);
				if (nh <= heuristicaactual) {
					pq.push({ nx, ny, nh });
					visited[nx][ny] = true;
					padre[nx][ny] = { actual.x, actual.y };
				}
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


int main() {
	vector<vector<int>> matriz = {
		{1,1,2,9,9},
		{1,9,1,1,1},
		{1,1,1,9,1},
		{9,1,9,1,1},
		{1,1,1,1,1}
	};

	vector<pair<int, int>> a = Aestrella(0, 0, 4, 4, matriz);
	for (auto e : a) {
		cout << e.first << e.second << " ";
	}
}
