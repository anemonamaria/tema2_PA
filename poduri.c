#include <stdio.h>
#include <stdlib.h>

typedef struct celula {
	char tipPod;
	int distanta;
} celula;

int miscareValida(int i, int j, int n, int m) {
	if(i < n && i >= 0 && j < m && j >= 0)
		return 1;
	return 0;
}

void mutari(celula ***matrix, int n, int m, int i, int j) {
	int rez = 0;
	int distParcursa = matrix[i][j]->distanta;
	if(matrix[i][j]->tipPod == 'V') {
		if(miscareValida(i-1, j, n, m)) {
			matrix[i-1][j]->distanta = matrix[i-1][j]->distanta + distParcursa;
			mutari(matrix, n, m, i-1, j);
		}
		if(miscareValida(i+1, j, n, m)) {
			matrix[i+1][j]->distanta = matrix[i+1][j]->distanta + distParcursa;
			mutari(matrix, n, m, i+1, j);
		}
	}

	else if(matrix[i][j]->tipPod == 'O') {
		if(miscareValida(i, j-1, n, m)) {
			matrix[i][j-1]->distanta = matrix[i][j-1]->distanta + distParcursa;
			mutari(matrix, n, m, i, j-1);
		}
		if(miscareValida(i, j+1, n, m)) {
			matrix[i][j+1]->distanta = matrix[i][j+1]->distanta + distParcursa;
			mutari(matrix, n, m, i, j+1);
		}
	}

	else if(matrix[i][j]->tipPod == 'D') {
		if(miscareValida(i-1, j, n, m)) {
			matrix[i-1][j]->distanta = matrix[i-1][j]->distanta + distParcursa;
			mutari(matrix, n, m, i-1, j);
		}
		if(miscareValida(i+1, j, n, m)) {
			matrix[i+1][j]->distanta = matrix[i+1][j]->distanta + distParcursa;
			mutari(matrix, n, m, i+1, j);
		}
		if(miscareValida(i, j-1, n, m)) {
			matrix[i][j-1]->distanta = matrix[i][j-1]->distanta + distParcursa;
			mutari(matrix, n, m, i, j-1);
		}
		if(miscareValida(i, j+1, n, m)) {
			matrix[i][j+1]->distanta = matrix[i][j+1]->distanta + distParcursa;
			mutari(matrix, n, m, i, j+1);
		}
	}
}

int main(){
	FILE *f, *g;
	f = fopen("poduri.in", "r");
	g = fopen("poduri.out", "w");

	int n, m, x, y;
	fscanf(f, "%d %d", &n, &m); // dimensiunea
	fscanf(f, "%d %d", &x, &y); // positia

	int i, j;
	char aux;
	celula **matrix = (celula **)calloc((n + 1), sizeof(celula *));
	for(int i = 0; i < n; i++){
		matrix[i] = (celula *)calloc((m + 1), sizeof(celula));
		for (int j = 0; j < m; j++) {
			fscanf(f, "%c", &matrix[i][j].tipPod);
		}
	}

	int rez = __INT_MAX__;
	i = x - 1;
	j = y - 1;
	mutari(&matrix, n, m, i, j);

	for(int i = 0; i < n ; i++) {
		if(matrix[i][0].distanta < rez && matrix[i][0].distanta != 0) {
			rez = matrix[i][0].distanta;
		}
		if(matrix[i][m-1].distanta < rez && matrix[i][m-1].distanta != 0) {
			rez = matrix[i][m-1].distanta;
		}
	}

	for(int j = 0; j < m ; j++) {
		if(matrix[0][j].distanta < rez && matrix[0][j].distanta != 0) {
			rez = matrix[0][j].distanta;
		}
		if(matrix[n-1][j].distanta < rez &&  matrix[n-1][j].distanta != 0) {
			rez = matrix[n-1][j].distanta;
		}
	}
	for(i = 0; i< n; i++ ) {
		for(j = 0; j< m;j ++){
			fprintf(g, "%d ", matrix[i][j].distanta);
		}
		fprintf(g, "\n");
	}

	fprintf(g, "%d", rez);

	for(i = 0; i <= n; i++){
		free(matrix[i]);
	}
	free(matrix);
	fclose(f);
	fclose(g);
	return 0;
}