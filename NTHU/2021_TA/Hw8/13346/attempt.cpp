#include <bits/stdc++.h>
using namespace std;

int main() {
    int W, H;
    cin >> W >> H;
    cin.get();

    int pw[2] = {-1, -1}, ph[2] = {-1, -1}, idx = 0;
    char ch;

    for (int i = 1; i <= W; i++) {
        for (int k = 1; k <= H; k++)
            if ((ch = cin.get()) == '1') {
                pw[idx] = i;
                ph[idx] = k;
                idx++;
            }

        cin.get();
    }

    int pans;
    int ans[20][20] = {0};
    
    ans[0][0] = 1;

    int m = 0;
    for (int i = 1; i <= W;) {
        for (int k = 1; k <= H;) {
            ans[i][k] = ans[i - 1][k] + ans[i][k - 1] + ans[i - 1][k - 1];
            
            if (idx > m) {
                if (i == pw[m] and k == ph[m]) {
                    ans[i - 2][k - 2] += ans[i][k];

                    i -= 2;
                    k -= 1;

                    m++;
                } else
                    k++;
            } else
                k++;
        }

        i++;
    }
    
    for (int i = 1; i <= W; i++)
    {
        for (int k = 1; k <= H; k++)
            cout << ans[i][k] << ' ';
        cout << endl;
    }
    
    
    pans = ans[W][H];

    if (idx == 2) {
        if (pw[1] - 2 <= pw[0] and ph[1] - 2 <= ph[1]) {
            memset(ans, 0, sizeof(ans));

            for (int i = 1; i <= W; i++)
                ans[i][1] = ans[1][i] = 1;
            int f, s;

            for (int i = 2; i <= pw[1]; i++)
                for (int k = 2; k <= ph[1]; k++)
                    ans[i][k] =
                        ans[i - 1][k] + ans[i][k - 1] + ans[i - 1][k - 1];

            f = ans[pw[1]][ph[1]];

            memset(ans, 0, sizeof(ans));

            for (int i = 1; i <= W; i++)
                ans[i][1] = ans[1][i] = 1;

            for (int i = 2; i <= (W - 1) - (pw[1] - 2) + 1; i++)
                for (int k = 2; k <= (H - 1) - (ph[1] - 2) + 1; k++)
                    ans[i][k] =
                        ans[i - 1][k] + ans[i][k - 1] + ans[i - 1][k - 1];

            s = ans[(W - 1) - (pw[1] - 2) + 1][(H - 1) - (ph[1] - 2) + 1];

            pans += f * s;
        }
    }

    cout << pans << endl;
}