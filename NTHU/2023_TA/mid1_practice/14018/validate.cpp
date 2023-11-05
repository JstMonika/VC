#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

int main() {
	yccc;
	
	for (int i = 1; i <= 8; i++) {
		ifstream fin;
		fin.open(to_string(i) + ".in");
		cout << char(fin.peek()) << ' ';
		
		int count = 0;
		string str;
		while (fin >> str) {
			count++;
			
			assert(str.size() <= 1000);
			for (auto i : str) {
				assert(i == '\'' or isalnum(i));
			}
		}
		
		assert(count <= 100);
		
		fin.clear();
		fin.close();
		fin.open(to_string(i) + ".out");
		cout << char(fin.peek()) << ' ';
		
		while (getline(fin, str)) {
			assert(str.size() < 1000000);
		}
	}
	
	cout << endl;
	cout << "validation passed.";
}