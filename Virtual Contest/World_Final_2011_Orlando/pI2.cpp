#include <bits/stdc++.h>
using namespace std;

#define al(a) a.begin(), a.end()

int N;
vector<vector<int>> mummy(100000, vector<int>(2));
int seg[10000000] = {0};
int tag[10000000] = {0};

void build(int id, int l, int r) {
    if (l == r) {
        seg[id] = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    if(seg[id * 2] < seg[id * 2 + 1]){
        seg[id] = seg[id * 2];
    }else{
        seg[id] = seg[id * 2 + 1];
    }
}
void modify(int l, int r, int L, int R, int idx, int val) {
    if (L <= l && r <= R) {
        seg[idx] += val;
        tag[idx] += val;
        return;
    } else if (r < L || R < l)
        return;

    int m = (l+r) / 2;

    seg[idx*2] += tag[idx];
    seg[idx*2+1] += tag[idx];

    tag[idx*2] += tag[idx];
    tag[idx*2+1] += tag[idx];

    tag[idx] = 0;

    modify(l, m, L, R, idx*2, val);
    modify(m+1, r, L, R, idx*2+1, val);

    if(seg[idx * 2] < seg[idx * 2 + 1]){
        seg[idx] = seg[idx * 2];
    }else{
        seg[idx] = seg[idx * 2 + 1];
    }
}
int query(int idx, int l, int r, int L, int R) {
    if (L <= l && r <= R){
        return seg[idx];
    }else if (r < L || R < l){
        return 10000000;
    }

    seg[idx*2] += tag[idx];
    seg[idx*2+1] += tag[idx];

    tag[idx*2] += tag[idx];
    tag[idx*2+1] += tag[idx];

    tag[idx] = 0;

    int m = (l+r) / 2;
    int lRet = query(idx*2, l, m, L, R);
    int rRet = query(idx*2+1, m+1, r, L, R);
    
    return (lRet < rRet ? lRet : rRet);
}

int binary_search(){
    int j,k,m;
    int max = 1000001;
    int min = 0;
    int now = (max + min) / 2;
    int all_start[100000] = {0};
    int all_end[100000] = {0};
    int count_start,count_end;
    int now_all_start = 0;
    int now_all_end = 0;
    int front_mummy = 0;
    int last_mummy = 0;
    int check;
    int now_slice = 0;
    for(j=0;j<20;j++){
        now = (max + min) / 2;
        /*now = 4;*/
        build(1, 1, 2*now + 1);
        for(k=0;k<10000000;k++){
            tag[k] = 0;
        }
        now_all_start = 0;
        now_all_end = 0;
        /*printf("now = %d\n",now);*/
        for(k=0;k<N;k++){
            if(mummy[k][0] > 0 && mummy[k][0] <= 2*now){
                all_start[now_all_start] = mummy[k][0] - now;
                now_all_start++;
            }
            if(mummy[k][0] >= (-2)*now && mummy[k][0] < 0){
                all_end[now_all_end] = mummy[k][0] + now + 1;
                now_all_end++;
            }
        }

        check = 0;
        last_mummy = -1;
        front_mummy = -1;
        for(k=0;k<N;k++){
            if(mummy[k][0] <= 0 && mummy[k][0] > (-2)*now){
                if(check == 0){
                    last_mummy = k;
                    check = 1;
                }
                front_mummy = k;
            }
        }
        /*printf("front last = %d %d\n",front_mummy,last_mummy);
        for(m=0;m<50;m++){
            printf("%d ",seg[m]);
        }
        printf("\n");
        printf("query = %d\n",query(1, 1, 2*now+1, 1, 2*now+1));*/
        if(last_mummy == -1 && front_mummy == -1){
            /*printf("never1\n");*/
            min = now;
            continue;
        }
        for(k=last_mummy;k<=front_mummy;k++){
            if(mummy[k][1] == 0){
                modify(1,2*now+1,1,2*now+1,1,1);
            }else if(mummy[k][1] > 0){
                modify(1,2*now+1,1,2*now-mummy[k][1]+1,1,1);
            }else{
                modify(1,2*now+1,1-mummy[k][1],2*now+1,1,1);
            }
        }
        /*printf("all_start = ");
        for(k=0;k<now_all_start;k++){
            printf("%d ",all_start[k]);
        }
        printf("\n");
        printf("all_end = ");
        for(k=0;k<now_all_end;k++){
            printf("%d ",all_end[k]);
        }
        printf("\n");*/


        /*printf("query = %d\n",query(1, 1, 2*now+1, 1, 2*now+1));*/
        if(query(1, 1, 2*now+1, 1, 2*now+1) == 0){
            /*printf("never2\n");*/
            min = now;
            continue;
        }

        check = 0;
        count_start = 0;
        count_end = 0;
        all_start[now_all_start] = 10000000;
        all_end[now_all_end] = 10000000;
        while((count_start < now_all_start || count_end < now_all_end) && check == 0){
            /*printf("count = %d %d\n",count_start,count_end);*/
            if(all_start[count_start] < all_end[count_end] || all_end[count_end] == 10000000){
                now_slice = all_start[count_start];
                count_start++;
            }else if(all_start[count_start] > all_end[count_end] || all_start[count_start] == 10000000){
                now_slice = all_end[count_end];
                count_end++;
            }else if(all_start[count_start] == all_end[count_end]){
                now_slice = all_start[count_start];
                count_start++;
                count_end++;
            }
            /*printf("now slice = %d\n",now_slice);*/
            for(k=front_mummy+1;k<N;k++){
                if(mummy[k][0] - now == now_slice){
                    if(mummy[k][1] == 0){
                        modify(1,2*now+1,1,2*now+1,1,1);
                    }else if(mummy[k][1] > 0){
                        modify(1,2*now+1,1,2*now-mummy[k][1]+1,1,1);
                    }else{
                        modify(1,2*now+1,1-mummy[k][1],2*now+1,1,1);
                    }
                    front_mummy++;
                }
            }
            for(k=last_mummy;k<=front_mummy;k++){
                if(mummy[k][0] + now + 1 == now_slice){
                    /*printf("@@@@@@@@");*/
                    if(mummy[k][1] == 0){
                        modify(1,2*now+1,1,2*now+1,1,-1);
                    }else if(mummy[k][1] > 0){
                        modify(1,2*now+1,1,2*now-mummy[k][1]+1,1,-1);
                    }else{
                        modify(1,2*now+1,1-mummy[k][1],2*now+1,1,-1);
                    }
                    last_mummy++;
                }
            }
            if(query(1, 1, 2*now+1, 1, 2*now+1) == 0){
                check = 1;
                break;
            }
        }
        if(check == 0){
            /*printf("dead\n");*/
            max = now;
        }else if(check == 1){
            /*printf("never3\n");*/
            min = now;
        }
    }
    if(check == 1){
        return now+1;
    }else{
        return now;
    }
}

int main(){
    int i = 1;
    int j,k,m;
    int temp;
    int answer;
    FILE* test;
    test = fopen("test.txt","r");
    while(1){
        /*fscanf(test,"%d",&N);*/
        scanf("%d",&N);
        if(N == -1){
            return 0;
        }
        for(j=0;j<N;j++){
            /*fscanf(test,"%d %d",&mummy[j][0],&mummy[j][1]);*/
            scanf("%d %d",&mummy[j][0],&mummy[j][1]);
        }
        
        sort(al(mummy));
        /*
        for(j=0;j<N-1;j++){
            for(k=0;k<N-1-j;k++){
                if (mummy[k][0] > mummy[k+1][0]) {
                    temp = mummy[k][0];
                    mummy[k][0] = mummy[k+1][0];
                    mummy[k+1][0] = temp;

                    temp = mummy[k][1];
                    mummy[k][1] = mummy[k+1][1];
                    mummy[k+1][1] = temp;
                }
            }
        }
        */
        answer = binary_search();

        if(answer == 1000001 || N == 0){
            printf("Case %d: never\n",i);
        }else{
            printf("Case %d: %d\n",i,answer);
        }
        i++;
    }
}
