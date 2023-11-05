// model solution by Yazmau
#include<stdio.h>
#define maxn 305
char s[maxn][maxn];
int gateX[30],gateY[30];
int vis[maxn][maxn];
int sol(int n,int m,int x,int y,int edX,int edY) {
	static int dx[] = {-1,0,0,1}, dy[] = {0,-1,1,0};
	vis[x][y] = 1;
	if(x == edX && y == edY)	return 1;
	for(int dir=0;dir<4;dir++) {
		int nx = x + dx[dir], ny = y + dy[dir];
		if(nx < 0 || nx >= n || ny < 0 || ny >= m)	continue;

		char nxtCell = s[nx][ny];
		if('a' <= nxtCell && nxtCell <= 'z')	nx = gateX[nxtCell - 'a'], ny = gateY[nxtCell - 'a'];
		if(vis[nx][ny] == 1 || s[nx][ny] == '#')	continue;
		if(sol(n,m,nx,ny,edX,edY) == 1)	return 1;
	}
	return 0;
}
int main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		int n,m;
		scanf("%d %d",&n,&m);
		for(int i=0;i<n;i++)
			scanf("%s",s[i]);
		int stX, stY, edX, edY;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++) {
				if(s[i][j] == '$')
					stX = i, stY = j;
				else if(s[i][j] == '&')
					edX = i, edY = j;
				else if('A' <= s[i][j] && s[i][j] <= 'Z')
					gateX[s[i][j] - 'A'] = i, gateY[s[i][j] - 'A'] = j;
				
				vis[i][j] = 0;
			}
		printf("%s\n",(sol(n,m,stX,stY,edX,edY) == 1 ? "Yes" : "No"));
	}
	return 0;
}