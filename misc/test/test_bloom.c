#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bloom.h"

int usage() {
  printf("./test_bloom <bloom_data> <item_file>\n");
  return 0;
}

int main(int argc, char** argv) {
  if(argc != 3) {
    usage();
    return 1;
  }

  struct bloom bloom;
  int rc;

  bloom_init(&bloom, 1000000, 0.0001);
  bloom_import(&bloom, argv[1]);

  FILE *stream;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  stream = fopen(argv[2], "r");
  if (stream == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  int processed = 0;

  while ((nread = getline(&line, &len, stream)) != -1) {
    if(nread > 1) {
      if(line[nread-1] == '\n') {
        line[nread-1]='\0';
				nread--;
      }
      rc = bloom_check(&bloom, line, nread);
      if(rc == 0) {
        printf("NOT MATCH: %s\n", line);
      } else if(rc == 1) {
        printf("MAYBE MATCH: %s\n", line);
      } else {
        printf("ERROR: %s", line);
      }
      processed++;
    }
  }

  free(line);
  fclose(stream);

  printf("%d items are validated.\n", processed);
  return 0;
}