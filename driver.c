#include "./sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Simply use clock_gettime, which is fast enough on most systems
unsigned long timestamp() {
  struct timespec spec;
  clock_gettime(1, &spec);
  return spec.tv_sec * (1000 * 1000 * 1000) + spec.tv_nsec;
}

char *read_file(char *path) {
  FILE *f = fopen(path, "rb");
  if (f == NULL)
    return NULL;
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET); /* same as rewind(f); */

  char *string = malloc(fsize + 1);
  fread(string, fsize, 1, f);
  fclose(f);

  string[fsize] = 0;

  return string;
}

int callback(void *private, int cols, char **values, char **names) {
  // for (int col = 0; col < cols; col++) {
  //   printf("%s: %s\n", names[col], values[col]);
  // }
  // printf("\n");

  return 0;
}

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

  char *query = read_file(argv[2]);
  if (query == NULL) {
    fprintf(stderr, "open error: %s\n", argv[2]);
    exit(1);
  }

  puts(query);
  char *error;
	unsigned long start = timestamp();
  status = sqlite3_exec(db, query, callback, NULL, &error);
	unsigned long end = timestamp();
  if (status) {
    fprintf(stderr, "query error: %s\n", sqlite3_errmsg(db));
    exit(1);
  }

	printf("query took %luns\n", end - start);

  // puts(error);

  sqlite3_close(db);

  return 0;
}
