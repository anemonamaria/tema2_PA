#include <bits/stdc++.h>

using namespace std;

struct Node {
	int x;
	int y;
    int distanta;
};

bool isValid(int x, int y, int n, int m, vector <vector <char>> &matrix) {
	// verific daca pozitia exista
    if (x >= 0 && y < n && x >= 0 && y < m && matrix[x][y] != '.')
		return 1;
	return 0;
}

int BFS(vector <vector <char>> &matrix, int x, int y, int n, int m) {
	// parcurgerea matricii
    if (!isValid(x, y, n, m, matrix))
        return -1;

    bool vizitat[n][m];
    memset(vizitat, false, sizeof(vizitat));
    vizitat[x][y] = true;

    queue<Node> q;
    q.push({x, y, 0});

    while (q.size()) {
        Node nod = q.front();
		q.pop();

		if ((nod.x == 0 && matrix[nod.x][nod.y] != 'O') ||
			(nod.y == 0 && matrix[nod.x][nod.y] != 'V') ||
			(nod.x == n-1 && matrix[nod.x][nod.y] != 'O') ||
			(nod.y == m-1 && matrix[nod.x][nod.y] != 'V'))
            return nod.distanta + 1;

		if (matrix[nod.x][nod.y] == 'D') {
			if (isValid(nod.x - 1, nod.y, n, m, matrix) && !vizitat[nod.x - 1][nod.y]) {
				vizitat[nod.x - 1][nod.y] = true;
				q.push({nod.x - 1, nod.y, nod.distanta + 1});
			}

			if (isValid(nod.x, nod.y - 1, n, m, matrix) && !vizitat[nod.x][nod.y - 1]) {
				vizitat[nod.x][nod.y - 1] = true;
				q.push({nod.x, nod.y - 1, nod.distanta + 1});
			}

			if (isValid(nod.x, nod.y + 1, n, m, matrix) && !vizitat[nod.x][nod.y + 1]) {
				vizitat[nod.x][nod.y + 1] = true;
				q.push({nod.x, nod.y + 1, nod.distanta + 1});
			}

			if (isValid(nod.x + 1, nod.y, n, m, matrix) && !vizitat[nod.x + 1][nod.y]) {
				vizitat[nod.x + 1][nod.y] = true;
				q.push({nod.x + 1, nod.y, nod.distanta + 1});
			}
		} else if (matrix[nod.x][nod.y] == 'O') {
			if (isValid(nod.x, nod.y - 1, n, m, matrix) && !vizitat[nod.x][nod.y - 1]) {
				vizitat[nod.x][nod.y - 1] = true;
				q.push({nod.x, nod.y - 1, nod.distanta + 1});
			}

			if (isValid(nod.x, nod.y + 1, n, m, matrix) && !vizitat[nod.x][nod.y + 1]) {
				vizitat[nod.x][nod.y + 1] = true;
				q.push({nod.x, nod.y + 1, nod.distanta + 1});
			}
		} else if (matrix[nod.x][nod.y] == 'V') {
			if (isValid(nod.x - 1, nod.y, n, m, matrix) && !vizitat[nod.x - 1][nod.y]) {
				vizitat[nod.x - 1][nod.y] = true;
				q.push({nod.x - 1, nod.y, nod.distanta + 1});
			}

			if (isValid(nod.x + 1, nod.y, n, m, matrix) && !vizitat[nod.x + 1][nod.y]) {
				vizitat[nod.x + 1][nod.y] = true;
				q.push({nod.x + 1, nod.y, nod.distanta + 1});
			}
		}
    }

    return -1;
}

int main() {
	ifstream fin("poduri.in");
	ofstream fout("poduri.out");
	int n, m, x, y;
    fin >> n >> m;
	fin >> x >> y;

	vector <vector <char>> matrix(n);

	for(int i = 0; i < n; i++) {
		matrix[i] = (vector<char>(m));
		for (int j = 0; j < m; j++) {
			fin >> matrix[i][j];
		}
	}

    fout << BFS(matrix, x - 1, y - 1, n, m);

    return 0;
}
