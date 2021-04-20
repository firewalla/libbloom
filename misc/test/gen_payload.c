#include <stdio.h>
#include "bloom.h"
#include <stdlib.h>

int usage() {
  printf("./gen_payload <item.lst> <export_file>\n");
  return 0;
}

int main(int argc, char** argv) {
  if(argc != 3) {
    usage();
    return 1;
  }

  FILE *stream;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  stream = fopen(argv[1], "r");
  if (stream == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  struct bloom bloom;
  int processed = 0;

  // number of entries is about 1 million
  // error rate is 0.0001
  bloom_init(&bloom, 1000000, 0.0001);

  while ((nread = getline(&line, &len, stream)) != -1) {
    if(nread > 1) {
      line[nread-1]='\0';
      bloom_add(&bloom, line, nread-1);
      printf("%s\n", line);
      processed++;
    }
  }

  free(line);
  fclose(stream);

  printf("exporting bloomfilter data to file: %s\n", argv[2]);
  bloom_export(&bloom, argv[2]);
  printf("%d items exported.\n", processed);

  return 0;
}