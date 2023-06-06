#include "./sqlite3.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int status;
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <database> <query>\n", argv[0]);
    return EXIT_FAILURE;
  }

  sqlite3 *db;

  status = sqlite3_open(argv[1], &db);
  if (status) {
    fprintf(stderr, "open error: %s\n", sqlite3_errmsg(db));
    exit(1);
  }

  return 0;
}
