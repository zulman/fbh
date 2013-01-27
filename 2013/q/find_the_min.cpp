/* 
 * File:   balanced_smileys.cpp
 * Author: Oleg.Chumakov
 *
 * Created on January 27, 2013, 2:20 AM
 */

#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iostream>
#include <sstream>
#include <cstddef>
#include <algorithm>
#include <utility>
#include <iterator>
#include <numeric>
#include <list>
#include <complex>
#include <cstdio>
#include <climits>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

static void redirect(int argc, const char **argv) {
  if (argc > 1) {
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
      perror(argv[1]);
      exit(1);
    }
    if (-1 == dup2(fd, 0)) {
      perror(argv[1]);
      exit(1);
    }
    if (-1 == close(fd)) {
      perror(argv[1]);
      exit(1);
    }
  }

  if (argc > 2) {
    int fd = open(argv[2], O_WRONLY | O_CREAT, 0666);
    if (fd == -1) {
      perror(argv[2]);
      exit(1);
    }
    if (-1 == dup2(fd, 1)) {
      perror(argv[2]);
      exit(1);
    }
    if (-1 == close(fd)) {
      perror(argv[2]);
      exit(1);
    }
  }
}
//The first line contains an integer T (T <= 20), the number of test cases.
//This is followed by T test cases, consisting of 2 lines each.
//The first line of each test case contains 2 space separated integers, n, k (1 <= k <= 105, k < n <= 109).
//The second line of each test case contains 4 space separated integers a, b, c, r (0 <= a, b, c <= 109, 1 <= r <= 109).

int main(int argc, const char **argv) {
  redirect(argc, argv);

  int cases;
  cin >> cases >> ws;
  for (int cas = 0; cas < cases; cas++) {
    uint N, K, A, B, C, R;
    cin >> N >> K >> A >> B >> C >> R;

    uint m[N];
    uint temp[N];
    m[0] = A;
    for (uint i = 1; i < K; i++) {
      m[i] = (B * m[i - 1] + C) % R;
    }

    for (uint i = K; i < N; i++) {
      memcpy(temp, m, sizeof (m));
      uint startIdx = i - K;
      sort(temp + startIdx, temp + i);

      //Not found min case
      m[i] = temp[i - 1] + 1;
      int last = -1;
      for (uint j = startIdx; j <= i - 1; j++) {
        if (temp[j] - last > 1) {
          m[i] = last + 1;
          break;
        }
        last = temp[j];
      }
    }
    printf("Case #%d: %d\n", cas + 1, m[N - 1]);

  }
  return 0;
}



