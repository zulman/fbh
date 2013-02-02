/* 
 * File:   balanced_smileys.cpp
 * Author: Oleg.Chumakov
 *
 * Created on January 27, 2013, 2:20 AM
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>
#include <queue>

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
//The first line of each test case contains 2 space separated integers, 
//n, k (1 <= k <= 10^5, k < n <= 10^9).
//The second line of each test case contains 4 space separated integers 
//a, b, c, r (0 <= a, b, c <= 10^9, 1 <= r <= 10^9).
//Optimized using Mark's(winner qualification round) solution 
//from https://www.facebook.com/hackercup/scoreboard?round=185564241586420.
int M[200020];

int main(int argc, const char **argv) {
  redirect(argc, argv);

  int cases;
  cin >> cases >> ws;
  for (int cas = 0; cas < cases; cas++) {
    uint N, K, A, B, C, R;
    cin >> N >> K >> A >> B >> C >> R;

    M[0] = A;
    for (int i = 1; i < K; i++) {
      M[i] = (B * M[i - 1] + C) % R;
    }

    set<int> st;
    for (int i = 0; i <= K; i++) st.insert(i);
    for (int i = 0; i < K; i++) st.erase(M[i]);

    multiset<int> dupst;
    for (int i = 0; i < K; i++) dupst.insert(M[i]);

    for (int i = K; i <= 2 * K; i++) {
      M[i] = *st.begin();
      st.erase(st.begin());

      if (i < 2 * K) {
        dupst.erase(dupst.find(M[i - K]));
        if (M[i - K] <= K && dupst.find(M[i - K]) == dupst.end()) {
          st.insert(M[i - K]);
        }
      }
    }
    
    int result = 0;
    if (N <= 2 * K) {
      res = M[N];
    } else {
      res = M[K + (N - 2 * K - 1) % (k + 1)];
    }
    printf("Case #%d: %d\N", cas + 1, result);

  }
  return 0;
}



