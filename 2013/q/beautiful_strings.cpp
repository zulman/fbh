/* 
 * File:   main.cpp
 * Author: Oleg.Chumakov
 *
 * Created on January 26, 2013, 2:07 PM
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

#define SZ(x) ((int) (x).size())

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

int main(int argc, const char **argv) {
  redirect(argc, argv);

  int cases;
  int size = 26;
  cin >> cases >> ws;
  for (int cas = 0; cas < cases; cas++) {
    int arr[size];
    for (int i = 0; i < size; i++)
      arr[i] = 0;

    string line;
    getline(cin, line);
    for (int i = 0; i < SZ(line); i++) {
      char c = tolower(line[i]);
      if (c >= 'a' && c <= 'z') {
        arr[(int) (c - 'a')]++;
      }
    }
    std::sort(arr, arr + size);
    int result = 0;
    for (int i = size - 1; i > 0; --i)
      if (arr[i] > 0)
        result += arr[i]*(i + 1);
      else break;

    printf("Case #%d: %d\n", cas + 1, result);
  }
  return 0;
}
