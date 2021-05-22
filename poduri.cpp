#include <bits/stdc++.h>

using namespace std;
#define ROW 9
#define COL 10

struct Point {
    int x;
    int y;
};

struct queueNode {
    Point pt;  // The cordinates of a cell
    int dist;  // cell's distance of from the source
};

struct celula {
	char tipnod;
	int distanta;
};

bool isValid(int row, int col, int n, int m) {
    return (row >= 0) && (row < n) &&
           (col >= 0) && (col < m);
}

int rowD[] = {-1, 0, 0, 1};
int colD[] = {0, -1, 1, 0};

int rowO[] = {0, 0};
int colO[] = {-1, 1};

int rowV[] = {-1, 1};
int colV[] = {0, 0};

int BFS(ofstream &fout, vector <vector <char>> &mat, Point src, int n, int m) {
    if (!isValid(src.x, src.y, n, m))
        return -1;

    bool visited[n][m];
    memset(visited, false, sizeof visited);

    visited[src.x][src.y] = true;

    queue<queueNode> q;

    queueNode s = {src, 0};
    q.push(s);
    while (!q.empty()) {
        queueNode curr = q.front();
        Point pt = curr.pt;

        if ((pt.x == 0 && mat[pt.x][pt.y] != 'O') ||
			(pt.y == 0 && mat[pt.x][pt.y] != 'V') ||
			(pt.x == n-1 && mat[pt.x][pt.y] != 'O') ||
			(pt.y == m-1 && mat[pt.x][pt.y] != 'V'))
            return curr.dist + 1;

        q.pop();
		if (mat[pt.x][pt.y] == 'D') {
			for (int i = 0; i < 4; i++) {
				int row = pt.x + rowD[i];
				int col = pt.y + colD[i];

				if (isValid(row, col, n, m) && mat[row][col] != '.' &&
				!visited[row][col]) {
					visited[row][col] = true;
					queueNode Adjcell = { {row, col},
										curr.dist + 1 };
					q.push(Adjcell);
				}
			}
		} else if (mat[pt.x][pt.y] == 'O') {
			for (int i = 0; i < 2; i++) {
				int row = pt.x + rowO[i];
				int col = pt.y + colO[i];

				if (isValid(row, col, n, m) && mat[row][col] != '.' &&
				!visited[row][col]) {
					visited[row][col] = true;
					queueNode Adjcell = { {row, col},
										curr.dist + 1 };
					q.push(Adjcell);
				}
			}
		} else if (mat[pt.x][pt.y] == 'V') {
			for (int i = 0; i < 2; i++) {
				int row = pt.x + rowV[i];
				int col = pt.y + colV[i];

				if (isValid(row, col, n, m) && mat[row][col] != '.' &&
				!visited[row][col]) {
					visited[row][col] = true;
					queueNode Adjcell = { {row, col},
										curr.dist + 1 };
					q.push(Adjcell);
				}
			}
		}
    }

    return -1;
}

int main() {
	ifstream fin("poduri.in");
	ofstream fout("poduri.out");
	int n, m;
	Point sursa;
    fin >> n;
	fin >> m;
	fin >> sursa.x >> sursa.y;
	sursa.x = sursa.x - 1;
	sursa.y = sursa.y - 1;
	vector <vector <char>> matrix(n);

	for(int i = 0; i < n; i++) {
		matrix[i] = (vector<char>(m));
		for (int j = 0; j < m; j++) {
			fin >> matrix[i][j];
		}
	}

    int dist = BFS(fout, matrix, sursa, n, m);
    fout << dist;

    return 0;
}
