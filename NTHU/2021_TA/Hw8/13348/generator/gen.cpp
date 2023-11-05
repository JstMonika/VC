#include <bits/stdc++.h>
using namespace std;

ofstream fout;
bool _list[10];
int front = 7;
int back = 7;

void solve();

int main() {
    for (int i = 0; i < 10; i++)
        _list[i] = ((i >= front and i <= back) ? 1 : 0);
    srand(time(NULL));

    for (int i = 0; i <= back; i++) {
        if (!_list[i]) continue;

        fout.open("in" + to_string(i) + ".txt");

        solve();

        fout.close();
    }
}

void solve() {
    int W = rand() % 10 + 5;
    int H = rand() % 10 + 5;

    fout << W << ' ' << H << endl;

    for (int i = 0; i < W; i++) {
        for (int k = 0; k < H; k++) {
            if (rand() % 10 < 5)
                fout << 1;
            else
                fout << 0;
        }
        fout << endl;
    }
}