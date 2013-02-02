/* 
 * File:   card_game.cpp
 * Author: Oleg.Chumakov
 *
 * Created on February 2, 2013, 9:30 PM
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

int factorial(int x) {
  return !x ? 1 : x * factorial(x - 1);
}

uint combinations(uint N, uint K) {
  return factorial(N) / (factorial(K) * factorial(N - K));
}

int main(int argc, const char **argv) {
  redirect(argc, argv);

  uint cases;
  cin >> cases >> ws;
  for (int cas = 0; cas < cases; cas++) {
    uint N, K;
    cin >> N >> K;
    uint comb = 1;
    comb = combinations(N, K);

    uint a[N];
    for (uint i = 0; i < N; i++)
      cin >> a[i];

    std::sort(a, a + N, std::greater<int>());
    uint i = comb;
    uint cntr = 0;
    uint c = 0;
    uint f = 1;
    unsigned long result = 0;
    while (i > 0) {
      int nn = N - cntr - 1;
      int nk = K - 1;
      if (nn > nk && nk > 0)
        f = combinations(nn, nk);
      else f = 1;

      c = min(f, i);
      result += a[cntr] * c;
      cntr++;
      i -= c;
    }

    printf("Case #%d: %d\n", cas + 1, result);
  }
  return 0;
}




