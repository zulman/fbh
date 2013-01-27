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

static bool changeAll(int arr[], int idx, int change) {
  bool wasChanged = false;
  for (int i = 0; i <= idx; i++) {
    if (arr[i] < 0)
      continue;
    wasChanged = true;
    arr[i] += change;
  }
  return wasChanged;
}

static bool branchAll(int arr[], int &idx, int change) {
  int offset = 0;
  bool wasChanged = false;
  for (int i = 0; i <= idx; i++) {
    if (arr[i] < 0)
      continue;
    wasChanged = true;
    //    Creating branch for changed value and 
    //    keeping original branch with prev value
    offset++;
    arr[idx + offset] = arr[i] + change;
  }
  idx += offset;
  return wasChanged;
}

//A message has balanced parentheses if it consists of one of the following:
//
//- An empty string ""
//- One or more of the following characters: 'a' to 'z', ' ' (a space) or ':' (a colon)
//- An open parenthesis '(', followed by a message with balanced parentheses, followed by a close parenthesis ')'.
//- A message with balanced parentheses followed by another message with balanced parentheses.
//- A smiley face ":)" or a frowny face ":("

int main(int argc, const char **argv) {
  redirect(argc, argv);  

  int cases;
  cin >> cases >> ws;
  for (int cas = 0; cas < cases; cas++) {
    string line;
    getline(cin, line);
    bool wasColon = false;
    //Can't catch error on vector implementation so using forward array way
    //String with 50 :) will proceed stack overflow
    int sol[100000];
    for (int i = 1; i < 100000; i++)
      sol[i] = -1;
    sol[0] = 0;
    int lastSol = 0;
    bool wasBreaked = false;
    for (int i = 0; i < SZ(line); i++) {
      char c = line[i];

      if ((c >= 'a' && c <= 'z')
              || c == ' '
              || c == '('
              || c == ')'
              || c == ':') {
        if (c == '(') {
          if (!wasColon) {
            if (!changeAll(sol, lastSol, 1)) {
              wasBreaked = true;
              break;
            }
          } else
            //Creating branch for smile case
            if (!branchAll(sol, lastSol, 1)) {
            wasBreaked = true;
            break;
          }
        }
        if (c == ')') {
          if (!wasColon) {
            if (!changeAll(sol, lastSol, -1)) {
              wasBreaked = true;
              break;
            }
          } else
            //Creating branch for smile case
            if (!branchAll(sol, lastSol, -1)) {
            wasBreaked = true;
            break;
          }
        }
        if (c == ':') {
          wasColon = true;
          continue;
        }
        wasColon = false;
      } else {
        wasBreaked = true;
        break;
      }
    }
    string result = "NO";
    if (!wasBreaked) {
      for (int i = 0; i <= lastSol; i++) {
        if (sol[i] == 0) {
          result = "YES";
          break;
        }
      }

    }
    printf("Case #%d: %s\n", cas + 1, result.c_str());
  }
  return 0;
}



