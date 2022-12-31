#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
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

#define int i64
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;

template <typename T1, typename T2>
bool chkmin(T1 &x, T2 y) {
  return y < x ? (x = y, true) : false;
}
template <typename T1, typename T2>
bool chkmax(T1 &x, T2 y) {
  return x < y ? (x = y, true) : false;
}

namespace std {

template <typename T1, typename T2>
ostream &operator<<(ostream &stream, const pair<T1, T2> &p) {
  return stream << p.first << ' ' << p.second;
}

template <typename T>
ostream &operator<<(ostream &stream, const vector<T> &v) {
  for (auto &e : v)
    stream << e << ' ';
  return stream;
}

} // namespace std

#ifdef LOCAL
#include "acm/debug.hpp"
#else
#define DEBUG(...) ;
#define ADEBUG(a, n) ;
#endif

void runSolution(void);

i32 main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  runSolution();
#ifdef LOCAL
  // std::cerr << "Solution ran in " << static_cast<double>(clock()) /
  // CLOCKS_PER_SEC << std::endl;
#endif
  return 0;
}
/***************************************************************************/

void runSolution() {
  
}
