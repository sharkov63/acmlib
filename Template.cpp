#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#define ALL(a) (a).begin(), (a).end()
#define TIME (static_cast<long double>(clock()) / CLOCKS_PER_SEC)

#define int ll
using ll = long long;
using ull = unsigned long long;
using dbl = double;
using ld = long double;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

template <typename T1, typename T2>
bool chkmin(T1& x, T2 y) {
    return y < x ? (x = y, true) : false;
}
template <typename T1, typename T2>
bool chkmax(T1& x, T2 y) {
    return y > x ? (x = y, true) : false;
}

template <typename T1, typename T2>
ostream& operator<<(ostream& stream, const pair<T1, T2>& p) {
    return stream << p.first << ' ' << p.second;
}

template <typename T>
ostream& operator<<(ostream& stream, const vector<T>& v) {
    for (auto& e : v) stream << e << ' ';
    return stream;
}

#ifdef LOCAL
#include "acm/debug.hpp"
#else
#define DEBUG(...) ;
#define ADEBUG(a, n) ;
#endif

void runSolution(void);

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    runSolution();
#ifdef LOCAL
    // cerr << "Solution ran in " << TIME << endl;
#endif
    return 0;
}
/***************************************************************************/


void runSolution() {
    
}
