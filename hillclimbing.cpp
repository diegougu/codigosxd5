#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

int N = 200;

int heuristica(int x, int y, int endx, int endy) {
	return abs(x - endx) + abs(y - endy);
}

vector<pair<int, int>> hillclimbing(int startx, int starty, int endx, int endy, vector<vector<int>>& matriz) {
	vector<pair<int, int>> rec;
	vector<vector<bool>> visited(N, vector<bool>(N, false));
	rec.push_back(make_pair(startx, starty));
	visited[startx][starty] = true;
	visited[starty][startx] = true;
	int x = startx;
	int y = starty;
	vector<pair<int, int>> moves = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

	while (x != endx || y != endy) {
		int heuristicaactual = heuristica(x, y, endx, endy);
		pair<int, int> newpos = { -1, -1 };
		for (auto e : moves) {
			int posiblex = x + e.first;
			int posibley = y + e.second;

			if (posiblex >= 0 && posiblex < N && posibley >= 0 && posibley < N && !visited[posiblex][posibley] && matriz[posiblex][posibley] != -1) {
				int newheuristica = heuristica(posiblex, posibley, endx, endy);
				if (newheuristica < heuristicaactual) {
					heuristicaactual = newheuristica;
					newpos = make_pair(posiblex, posibley);
				}
			}
		}

		if (newpos.first == -1 || newpos.second == -1) {
			break;
		}

		x = newpos.first;
		y = newpos.second;
		visited[x][y] = true;
		visited[y][x] = true;
		rec.push_back(make_pair(x, y));
	}

	return rec;
}

int main() {
	vector<vector<int>> matriz(N, vector<int>(N, 1));
	vector<pair<int, int>> rec = hillclimbing(0, 0, 10, 10, matriz);
	for (auto e : rec) {
		cout << "(" << e.first << "," << e.second << ")" << endl;
	}


}
