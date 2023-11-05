#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	
	vector<int> w(n);
	vector<int> x(n);
	
	for (int i = 0; i < n; i++) {
		cin >> w[i] >> x[i];
	}
	
	//* int_max = 2147483647 = 2 * 10^9
	
	int ans = 0;
	
	for (int i = 0; i <= 23; i++) {
		int tmp = 0;
		
		for (int k = 0; k < n; k++) {
			int time = (i + x[k]) % 24;
			
			// cout << time << endl;
			
			if (time >= 9 and time <= 17)
				tmp += w[k];
		}
		// cout << "---\n";
		// cout << ans << ' ' << tmp << endl;
		// cout << endl;
		
		ans = max(ans, tmp);
		
	}
	
	cout << ans;
}