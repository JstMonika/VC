#include <stdio.h>

char _map[200][200];
int vis[200][200];

int score[15];
int posX[15], posY[15];
int n, m, q;

int count = 0, now;

int gx[4] = {0, -1, 0, 1};
int gy[4] = {1, 0, -1, 0};

void run(int i, int k) {
	if (_map[i][k] == '-') {
		if (count < score[now])
			score[now] = count;

		return;
	}
	
	for (int z = 0; z < 4; z++) {
		if (i + gx[z] < 0 or i + gx[z] >= n) continue;
		if (k + gy[z] < 0 or k + gy[z] >= m) continue;

		if (_map[i+gx[z]][k+gy[z]] == 'X' or vis[i+gx[z]][k+gy[z]]) continue;

		vis[i+gx[z]][k+gy[z]] = 1;
		count++;
		
		run(i+gx[z], k+gy[z]);

		count--;
		vis[i+gx[z]][k+gy[z]] = 0;
	}
}

int main() {
	scanf("%d %d %d", &n, &m, &q);

	for (int i = 0; i < n; i++) {
		for (int k = 0; k < m; k++) {
			scanf(" %c", &_map[i][k]);
		}
	}
	
	for (int i = 0; i < q+1; i++) {
		scanf("%d %d", &posX[i], &posY[i]);
		
		now = i;
		
		score[i] = 10000;
		run(posX[i], posY[i]);
	}

	int fast = 10000;
	for (int i = 1; i < q+1; i++) {
		fast = (fast > score[i] ? score[i] : fast);
	}

printf("%d", score[0]);
	for (int i = 1; i < q+1; i++)
		printf(" %d", score[i]);
	printf("\n");
	
	printf("%d\n", fast - score[0]);
}
