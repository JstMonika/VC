#include<bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
struct vline{
    int x,y1,y2;
};

struct hline{
    int y,x1,x2;
};
vector<pii> c;
vector<pii> h;
set<int> hx;
set<int> hy;
set<int> cx;
set<int> cy;
vector<vline> cv;
vector<vline> hv;
vector<hline> ch;
vector<hline> hh;

bool hcmp(const hline &a, const hline &b) {
    if(a.y == b.y) return a.x1 < b.x1;
    return a.y<b.y;
}

bool vcmp(const vline &a, const vline &b) {
    if(a.x == b.x) return a.y1<b.y1;
    return a.x<b.x;
}


void init() {
    cv.clear();
    hv.clear();
    ch.clear();
    hh.clear();
    c.clear();
    h.clear();
    hx.clear();
    hy.clear();
    cx.clear();
    cy.clear();
}

bool check(int offsetX, int offsetY) {//add offset to cover
    int hi,ci;
    bool isf,inCover;
    //check hole vertical(make line x = hx)
    for(auto &xx : hx){
    	int x = xx+1;
//    	printf("x=%d\n",x);
        inCover = false;
        hi = ci = 0;
        while(hi<(int)hh.size() && ci<(int)ch.size()) {
        	//printf("hi=%d ci=%d\n",hi,ci);
            if(hh[hi].x1 > x || hh[hi].x2 < x) {
                hi++;
                continue;
            }
            if((ch[ci].x1 + offsetX > x) || (ch[ci].x2 + offsetX < x)) {
                ci++;
                continue;
            }
//           printf("hi=%d ci=%d\n",hi,ci);
//           printf("isCover = %d\n",(inCover?1:0));

            if(hh[hi].y == (ch[ci].y + offsetY)) {
//            	printf("equal\n");
                hi++; ci++;
                inCover = !inCover;
            } else if((ch[ci].y + offsetY) < hh[hi].y) {
//            	printf("ci++\n");
                ci++;
                inCover = !inCover;
            } else {
                if(!inCover) return false;
//                printf("hi++\n");
                hi++;
            }
        }
        if(hi < (int)hh.size()) return false;
    }
	//printf("pass 1\n");
    for(auto &xx : cx) {
        int x = xx + offsetX + 1;
        inCover = false;
        hi = ci = 0;
        while(hi<(int)hh.size() && ci<(int)ch.size()) {
            if(hh[hi].x1 > x || hh[hi].x2 < x) {
                hi++;
                continue;
            }
            if((ch[ci].x1 + offsetX > x) || (ch[ci].x2 + offsetX < x)) {
                ci++;
                continue;
            }
            if(hh[hi].y == (ch[ci].y + offsetY)) {
                hi++; ci++;
                inCover = !inCover;
            } else if((ch[ci].y + offsetY) < hh[hi].y) {
                ci++;
                inCover = !inCover;
            } else {
                if(!inCover) return false;
                hi++;
            }
        }
        if(hi < (int)hh.size()) return false;
    }
//    printf("pass 2\n");

    for(auto &yy: hy) {
    	int y = yy + 1;
        inCover = false;
        hi = ci = 0;
         while(hi<(int)hv.size() && ci<(int)cv.size()) {
             if(hv[hi].y1 > y || hv[hi].y2 < y) {
                hi++;
                continue;
             }
             if(cv[ci].y1 + offsetY > y || cv[ci].y2 + offsetY < y) {
                ci++;
                continue;
             }
             if(hv[hi].x == cv[ci].x + offsetX) {
                hi++; ci++;
                inCover = !inCover;
             } else if(cv[ci].x + offsetX < hv[hi].x) {
                ci++;
                inCover = !inCover;
             } else {
                hi++;
                if(!inCover) return false;
             }
         }
         if(hi<(int)hv.size()) return false;
    }
//    printf("pass 3\n");

     for(auto &yy: cy) {
        int y = yy + offsetY + 1;
        inCover = false;
        hi = ci = 0;
         while(hi<(int)hv.size() && ci<(int)cv.size()) {
             if(hv[hi].y1 > y || hv[hi].y2 < y) {
                hi++;
                continue;
             }
             if(cv[ci].y1 + offsetY > y || cv[ci].y2 + offsetY < y) {
                ci++;
                continue;
             }
             if(hv[hi].x == cv[ci].x + offsetX) {
                hi++; ci++;
                inCover = !inCover;
             } else if(cv[ci].x + offsetX < hv[hi].x) {
                ci++;
                inCover = !inCover;
             } else {
                hi++;
                if(!inCover) return false;
             }
         }
         if(hi<(int)hv.size()) return false;
    }

	for(auto &xx : hx){
    	int x = xx-1;
//    	printf("x=%d\n",x);
        inCover = false;
        hi = ci = 0;
        while(hi<(int)hh.size() && ci<(int)ch.size()) {
        	//printf("hi=%d ci=%d\n",hi,ci);
            if(hh[hi].x1 > x || hh[hi].x2 < x) {
                hi++;
                continue;
            }
            if((ch[ci].x1 + offsetX > x) || (ch[ci].x2 + offsetX < x)) {
                ci++;
                continue;
            }
//            printf("hi=%d ci=%d\n",hi,ci);
//            printf("isCover = %d\n",(inCover?1:0));

            if(hh[hi].y == (ch[ci].y + offsetY)) {
//            	printf("equal\n");
                hi++; ci++;
                inCover = !inCover;
            } else if((ch[ci].y + offsetY) < hh[hi].y) {
//            	printf("ci++\n");
                ci++;
                inCover = !inCover;
            } else {
                if(!inCover) return false;
//                printf("hi++\n");
                hi++;
            }
        }
        if(hi < (int)hh.size()) return false;
    }
//	printf("pass 1\n");
    for(auto &xx : cx) {
        int x = xx + offsetX - 1;
        inCover = false;
        hi = ci = 0;
        while(hi<(int)hh.size() && ci<(int)ch.size()) {
            if(hh[hi].x1 > x || hh[hi].x2 < x) {
                hi++;
                continue;
            }
            if((ch[ci].x1 + offsetX > x) || (ch[ci].x2 + offsetX < x)) {
                ci++;
                continue;
            }
            if(hh[hi].y == (ch[ci].y + offsetY)) {
                hi++; ci++;
                inCover = !inCover;
            } else if((ch[ci].y + offsetY) < hh[hi].y) {
                ci++;
                inCover = !inCover;
            } else {
                if(!inCover) return false;
                hi++;
            }
        }
        if(hi < (int)hh.size()) return false;
    }
//    printf("pass 2\n");

    for(auto &yy: hy) {
    	int y = yy - 1;
        inCover = false;
        hi = ci = 0;
         while(hi<(int)hv.size() && ci<(int)cv.size()) {
             if(hv[hi].y1 > y || hv[hi].y2 < y) {
                hi++;
                continue;
             }
             if(cv[ci].y1 + offsetY > y || cv[ci].y2 + offsetY < y) {
                ci++;
                continue;
             }
             if(hv[hi].x == cv[ci].x + offsetX) {
                hi++; ci++;
                inCover = !inCover;
             } else if(cv[ci].x + offsetX < hv[hi].x) {
                ci++;
                inCover = !inCover;
             } else {
                hi++;
                if(!inCover) return false;
             }
         }
         if(hi<(int)hv.size()) return false;
    }
//    printf("pass 3\n");

     for(auto &yy: cy) {
        int y = yy + offsetY - 1;
        inCover = false;
        hi = ci = 0;
         while(hi<(int)hv.size() && ci<(int)cv.size()) {
             if(hv[hi].y1 > y || hv[hi].y2 < y) {
                hi++;
                continue;
             }
             if(cv[ci].y1 + offsetY > y || cv[ci].y2 + offsetY < y) {
                ci++;
                continue;
             }
             if(hv[hi].x == cv[ci].x + offsetX) {
                hi++; ci++;
                inCover = !inCover;
             } else if(cv[ci].x + offsetX < hv[hi].x) {
                ci++;
                inCover = !inCover;
             } else {
                hi++;
                if(!inCover) return false;
             }
         }
         if(hi<(int)hv.size()) return false;
    }

    return true;
}

int main() {
    int n,m;
    int cnt = 1;
    while(1) {
        scanf("%d %d",&n,&m);
        if(n == 0 && m == 0) break;
        init();
        //input
        for(int i=0;i<n;i++) {
            int x,y;
            scanf("%d %d",&x,&y);
            x*=2; y*=2;
            //if(i>0 && h[(int)h.size()-1] == make_pair(x,y)) continue;
            h.emplace_back(make_pair(x,y));
            hx.insert(x); hy.insert(y);
        }
        for(int i=0;i<m;i++) {
            int x,y;
            scanf("%d %d",&x,&y);
            x*=2; y*=2;
            //if(i>0 && c[(int)c.size()-1] == make_pair(x,y)) continue;
            c.emplace_back(make_pair(x,y));
            cx.insert(x); cy.insert(y);
        }
        /*
        if(cnt == 6) {
            printf("%d %d\n",n,m);
            for(auto e:h) printf("%d %d\n",e.first,e.second);
            for(auto e:c) printf("%d %d\n",e.first,e.second);
        }
        */
        //make edge
        int cs,hs;
        hline tmph;
        vline tmpv;
        cs = (int)c.size();
        hs = (int)h.size();
        for(int i=0;i<cs;i++) {
            if(c[i].first == c[(i+1)%cs].first) {
                tmpv.x = c[i].first;
                tmpv.y1 = min(c[i].second, c[(i+1)%cs].second);
                tmpv.y2 = max(c[i].second, c[(i+1)%cs].second);
                cv.emplace_back(tmpv);
            } else {
                tmph.y = c[i].second;
                tmph.x1 = min(c[i].first, c[(i+1)%cs].first);
                tmph.x2 = max(c[i].first, c[(i+1)%cs].first);
                ch.emplace_back(tmph);
            }
        }

        for(int i=0;i<hs;i++) {
            if(h[i].first == h[(i+1)%hs].first) {
                tmpv.x = h[i].first;
                tmpv.y1 = min(h[i].second, h[(i+1)%hs].second);
                tmpv.y2 = max(h[i].second, h[(i+1)%hs].second);
                hv.emplace_back(tmpv);
            } else {
                tmph.y = h[i].second;
                tmph.x1 = min(h[i].first, h[(i+1)%hs].first);
                tmph.x2 = max(h[i].first, h[(i+1)%hs].first);
                hh.emplace_back(tmph);
            }
        }
        
        sort(ch.begin(), ch.end(), hcmp);
        sort(hh.begin(), hh.end(), hcmp);
        sort(cv.begin(), cv.end(), vcmp);
        sort(hv.begin(), hv.end(), vcmp);
//	printf("ch:\n");
//        for(auto e:ch) {
//            printf("y=%d x1=%d x2=%d\n",e.y,e.x1,e.x2);
//        }
//    printf("hh:\n");
//        for(auto e:hh) {
//            printf("y=%d x1=%d x2=%d\n",e.y,e.x1,e.x2);
//        }
//    printf("cv:\n");
//        for(auto e:cv) {
//            printf("x=%d y1=%d y2=%d\n",e.x,e.y1,e.y2);
//        }
//    printf("hv:\n");
//        for(auto e:hv) {
//            printf("x=%d y1=%d y2=%d\n",e.x,e.y1,e.y2);
//        }

        bool isf = false;
        for(auto &h1 : ch) {
            for(auto &v1 : cv) {
                for(auto &h2 : hh) {
                    for(auto &v2 : hv) {
                        int offsetX, offsetY;
                        //if(h1.x1 == 0 && h1.x2 == 50 && h2.x1 == 20 && h2.x2 == 40 && v1.y1 == 0 && v1.y2 == 50 && v2.y1 == 20 && v2.y2 == 40){
	                        	//printf("should true\n");
	                        offsetX = v2.x - v1.x;
	                        offsetY = h2.y - h1.y;
	                        	//printf("x=%d y=%d\n",offsetX,offsetY);
	                        if(h1.x2 + offsetX < h2.x1 || h1.x1 + offsetX > h2.x2) continue;
	                        if(v1.y2 + offsetY < v2.y1 || v1.y1 + offsetY > v2.y2) continue;
	                        if(check(offsetX, offsetY)) {
	                            isf = true;
	                            break;
	                        }
						//}
                        	
                    }
                }
                if(isf) break;
            }
            if(isf) break;
        }
        if(isf) printf("Hole %d: Yes\n",cnt++);
        if(!isf) printf("Hole %d: No\n",cnt++);
    }
    /*
    12 12
10 20
10 40
20 40
20 60
40 60
40 50
60 50
60 30
50 30
50 10
30 10
30 20
10 0
10 50
0 50
0 60
50 60
50 70
60 70
60 20
70 20
70 10
20 10
20 0
*/

}