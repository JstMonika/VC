#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using Prior = priority_queue<T>;
template<typename T> using prior = priority_queue<T, vector<T>, greater<T>>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define pb push_back
#define mp(a, b) make_pair(a, b)
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 4*1e18;
const int MOD = 1e9+7;

ll& pmod(ll& a, ll b) { a = (a+b) % MOD; return a; }
ll& pmod(ll& a, ll b, ll c) { a = (a+b) % c; return a; }
ll& mmod(ll& a, ll b) { a = (a-b+MOD) % MOD; return a; }
ll& mmod(ll& a, ll b, ll c) { a = (a-b+c) % c; return a; }
ll& tmod(ll& a, ll b) { a = (a*b) % MOD; return a; }
ll mul(ll a, ll b) { return (a*b) % MOD; }
ll mul(ll a, ll b, ll c) { return (a*b) % c; }
ll mPOW(ll a, ll b) { ll res=1; do { if(b%2) tmod(res,a); tmod(a,a); } while (b>>=1); return res; }
ll nPOW(ll a, ll b) { ll res=1; do { if(b%2) res*=a; a*=a; } while (b>>=1); return res; }
ll mFAC(ll a) { ll res = 1; REP1(i, a) tmod(res, i); return res; }
ll nFAC(ll a) { ll res = 1; REP1(i, a) res*=i; return res; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

class work {
    public:
    int id;
    int need;
    int rest;
    int first;
    int work_time;
    int next_time;
    
    work();
    work(int, int, int, int, int);
};

class worker {
    public:
    int id;
    int num;
    
    vec<int> wList;
    
    worker(int, int, vec<int>&);
};

work::work() {}
work::work(int id, int need, int first, int work_time, int next_time) : id(id), need(need), rest(need), first(first), work_time(work_time), next_time(next_time) {}

worker::worker(int id, int num, vec<int>& wList) : id(id), num(num), wList(wList) {}

using Que = tuple<int, int, int>;
ostream& operator<<(ostream& os, Que a) {
    os << get<0>(a) << ' ' << (get<1>(a) == 1 ? "work" : "worker") << ' ' << get<2>(a);
    
    return os;
}

int solve(vec<work>& Work, vec<worker>& Worker) {
    auto cmp = [](const Que& a, Que& b) { //* time, type, id
        if (get<0>(a) != get<0>(b))
            return get<0>(a) > get<0>(b);
        
        return get<1>(a) > get<1>(b);
    };
    
    //* Not used now.
    map<int, int> toIdx;
    for (int i = 0; i < Work.size(); i++) {
        toIdx[Work[i].id] = i;
    }
    
    vec<int> waiting(Work.size());
    deque<bool> busying(Worker.size());
    priority_queue<Que, vector<Que>, decltype(cmp)> _list(cmp);
    
    for (int i = 0; i < Work.size(); i++) {
        for (int k = 0; k < Work[i].need; k++)
            _list.emplace(Work[i].first + k * Work[i].next_time, 1, i); //* time, type, idx.
    }
    
    int last = 0;
    while (!_list.empty()) {
        auto front = _list.top();
        // cout << _list.top() << endl;
        
        _list.pop();
        
        if (get<1>(front) == 1) { //* work request.
            waiting[get<2>(front)]++;
            
            for (int i = 0; i < Worker.size(); i++) {
                if (!busying[i]) {
                    bool done = false;
                    
                    for (int k = 0; k < Worker[i].num; k++) {
                        if (toIdx[Worker[i].wList[k]] == get<2>(front)) {
                            waiting[get<2>(front)]--;
                            
                            _list.emplace(get<0>(front) + Work[get<2>(front)].work_time, 0, i); //* time, type, userIdx.
                            busying[i] = true;
                            
                            done = true;
                        }
                    }
                    
                    if (done)
                        break;
                }
            }
        } else { //* worker finished.
            last = get<0>(front);
            busying[get<2>(front)] = false;
            
            for (int i = 0; i < Worker[get<2>(front)].wList.size(); i++) {
                if (waiting[toIdx[Worker[get<2>(front)].wList[i]]] > 0) {
                    waiting[toIdx[Worker[get<2>(front)].wList[i]]]--;
                    
                    _list.emplace(get<0>(front) + Work[toIdx[Worker[get<2>(front)].wList[i]]].work_time, 0, get<2>(front));
                    
                    busying[get<2>(front)] = true;
                    
                    break;
                }
            }
        }
    }
    
    return last;
}

int main()
{
    yccc;
    
    int task, worker_num, now = 1;
    while (cin >> task) {
        
        if (task == 0)
            break;
        
        vec<work> work_list;
        
        REP(i, task) {    
            int a, b, c, d, e;
            cin >> a >> b >> c >> d >> e;
            
            work_list.emplace_back(a, b, c, d, e);
        }
        
        cin >> worker_num;
        vec<worker> worker_list;
        
        REP(i, worker_num) {
            int a, b;
            cin >> a >> b;
            
            vec<int> tmp(b);
            for (auto &k : tmp)
                cin >> k;
            
            worker_list.emplace_back(a, b, tmp);
        }
        
        cout << "Scenario " << now++ << ": All requests are serviced within " << solve(work_list, worker_list) << " minutes.\n";
    }
}   