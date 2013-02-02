/* 
 * File:   balanced_smileys.cpp
 * Author: Oleg.Chumakov
 *
 * Created on January 27, 2013, 2:20 AM
 */

#include <iostream>
#include <algorithm>
#include <cstring>

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
  string line;
  for (int cas = 0; cas < cases; cas++) {
    getline(cin, line);
    bool wascolon = false;
    int min = 0, max = 0;
    for (int i = 0; min <= max && i < ln.size(); i++) {
      if (ln[i] == '(') {
        min++;
        max++;
        if (wascolon)
          max++;
      } else if (ln[i] == ')') {
        min--;
        max--;
        if (wascolon) {
          min--;
        }
        min = max(0, min);
      }

      if (ln[i] == ':')
        wascolon = true;
      else
        wascolon = false;
    }
    string result = "NO";
    if (min == 0 && max >= 0)
      result = "YES";

    printf("Case #%d: %s\n", cas + 1, result.c_str());
  }
  return 0;
}



