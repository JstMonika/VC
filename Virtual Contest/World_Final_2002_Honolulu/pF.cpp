#include<bits/stdc++.h>
using namespace std;
#define EPS 1e-7
struct Point {
	double x,y;
	int type;
	Point() : x(0), y(0), type(0){
	};
	Point(const double x, const double y) : x(x), y(y) {
	};
	Point(const double x, const double y, const int type) : x(x), y(y), type(type) {
	};

	void print() {
		printf("(%.2lf, %.2lf)\n",x,y);
	}
};
struct Line{
	Point st, ed;
	Line(const Point st, const Point ed) : st(st), ed(ed) {
	};
	
	double getX(double y) {
		double Xslope = (ed.x - st.x) / (ed.y - st.y);
		return st.x + (y - st.y) * Xslope;
	}

	void print() {
		printf("st:(%.2lf, %.2lf, %d), ed:(%.2lf, %.2lf, %d)\n",st.x, st.y, st.type, ed.x, ed.y, ed.type);
	}
};

struct Trapezoid {
	Line l,r;
	int idx;
	Trapezoid (const Line l, const Line r, const int idx) : l(l), r(r), idx(idx){
	};
	double getArea() {
		return (abs(l.st.x - r.st.x) + abs(l.ed.x - r.ed.x)) * (abs(l.st.y - l.ed.y)) / 2.0;
	}
	void print() {
		printf("l:"); l.print();
		printf("r:"); r.print();
	}
};

bool lte(double a, double b) {
	return ((abs(a-b) < EPS) || (a < b));
}

bool equal(double a, double b) {
	return (abs(a-b) < EPS);
}

bool gt(double a, double b) {
	return !lte(a,b);
}

bool lt(double a, double b) {
	return a<b && abs(a-b) > EPS;
}

bool gte(double a, double b) {
	return !lt(a,b);
}
vector<Point> pt;
vector<Line> line;
vector<Line> Slice[105];
vector<Trapezoid> trape[105];
vector<Trapezoid> table;
vector<int> G[10005];
bool isHole[10005];
double holeH[10005];
void init() {
	pt.clear();
	line.clear();
	table.clear();
	for(int i=0;i<105;i++){
		Slice[i].clear();
		trape[i].clear();
	}
		
	for(int i=0;i<10005;i++) {
		G[i].clear();
		isHole[i] = false;
		holeH[i] = 0.0;
	}
}

int Slicing() {
	int H = 0;
	for(int i=0;i+1<pt.size();i++) {
		if(equal(pt[i].y, pt[i+1].y)) continue;
		double midY = (pt[i].y + pt[i+1].y)/2.0;
		for(auto &L:line) {
			if(lt(midY, min(L.st.y, L.ed.y)) || gt(midY, max(L.st.y, L.ed.y))) continue;
			Slice[H].emplace_back(Line(Point(L.getX(pt[i].y), pt[i].y), Point(L.getX(pt[i+1].y), pt[i+1].y)));
		}
		sort(Slice[H].begin(), Slice[H].end(), [](const Line &a, const Line &b) {
			return (a.st.x + a.ed.x)/2.0 < (b.st.x + b.ed.x)/2.0; 
		});
		H++;
	}
	return H;
}

int getTrape(int H) {
	int cnt = 0;
	for(int i=0;i<H;i++) {
		for(int j=0;j<(int)Slice[i].size();j+=2) {
			trape[i].emplace_back(Trapezoid(Slice[i][j], Slice[i][j+1], cnt));
			table.emplace_back(Trapezoid(Slice[i][j], Slice[i][j+1], cnt++));
		}
	}
	return cnt;
}
vector<Point> holeV;
void getHole() {
	holeV.clear();
	for(auto &V:pt) {
		if(V.type) {
			holeV.emplace_back(V);
		}
	}
	//int cnt = 0;
	for(auto &T:table) {
		for(auto &V:holeV) {
			if(equal(V.y, T.l.st.y)) {
				if(lt(V.x, T.l.st.x) || gt(V.x, T.r.st.x));
				else {
					isHole[T.idx] = true;
					holeH[T.idx] = V.y;
					break;
				}
			}
			if(equal(V.y, T.l.ed.y)) {
				if(lt(V.x, T.l.ed.x) || gt(V.x, T.r.ed.x));
				else {
					isHole[T.idx] = true;
					holeH[T.idx] = V.y;
					break;
				}
			}
		}
	}
}

void buildGraph(int H) {
	for(int i=1;i<H;i++) {
		for(auto &T1 : trape[i]) {
			for(auto &T2 : trape[i-1]) {
				if(lte(T1.r.st.x ,T2.l.ed.x)) continue;
				if(gte(T1.l.st.x ,T2.r.ed.x)) continue;
				G[T1.idx].emplace_back(T2.idx);
				G[T2.idx].emplace_back(T1.idx);
			}
		}
	}
}

bool isv[10005];
bool dfs(int now, double H) {
	if(isHole[now] && lt(holeH[now], H)) {
		return false;
	}
		
	isv[now] = true;
	bool isf = true;
	for(auto &e : G[now]) {
		if(!isv[e] && lte(table[e].l.ed.y, H)) {
			isf = dfs(e, H);
		}
		if(!isf) break;
	}
	return isf;
}
float solve(int vNum){
	double ans = 0.0;
	for(int i=0;i<vNum;i++) {
		for(int j=0;j<vNum;j++) isv[j] = false;
		if(dfs(i, table[i].l.ed.y)){
			ans += table[i].getArea();
		}
		
	}
	return ans;
}

int main(){
	int n;
	for(int cnt=1;;cnt++) {
		scanf("%d",&n);
		if(n==0) break;
		init();
		for(int i=0;i<n;i++) {
			double x,y;
			int type;
			scanf("%lf %lf %d",&x,&y,&type);
			pt.emplace_back(Point(x,y,type));
		} 
		for(int i=0;i<n;i++) {
			line.emplace_back(Line(pt[i], pt[(i+1)%n]));
		}
		sort(pt.begin(), pt.end(), [](const Point &a, const Point &b){
			return a.y < b.y;
		});
		int h = Slicing();
		int vNum = getTrape(h);
		getHole();
		buildGraph(h);
		
		float ans = solve(vNum);
		printf("Cave %d: Oil capacity = %.0f\n\n",cnt,ans);
	}
}
