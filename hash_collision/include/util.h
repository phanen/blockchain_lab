#pragma once

// utilize
template <class T> int print_array(T *arr, std::size_t sz) {
  for (std::size_t i = 0; i < sz; i++) {
    if (i % 8 == 0)
      std::cout << std::endl;
    std::cout << int(arr[i]) << ", ";
  }
  std::cout << std::endl;
  return 1;
}

inline void dump_buf(uint8_t *buf, std::size_t len, uint8_t sep = ' ') {
  for (std::size_t i = 0; i < len; i++) {
    printf("0x%.2x%c", buf[i], sep);
    if ((i + 1) % 8 == 0)
      printf("\n");
  }
  printf("\n");
}

void test_large_file(const char *filename) {
  const size_t dgst_len = MD5_DIGST_SZ_IN_BT;
  uint8_t dgst[dgst_len];

  // Start measuring time
  struct timeval begin, end;
  gettimeofday(&begin, 0);
  const size_t byte_len = 1 << 20;
  uint8_t buf[byte_len];
  FILE *finp = fopen(filename, "r");
  if (finp == NULL) {
    printf("fail to open\n");
    return;
  }

#ifdef Progress_Log
  printf("Hashing... finished:\n");
#endif

  md5_ctx_t ctx;
  md5_init(&ctx);
  int cnt = 0;
  size_t cur_len = 0;
#ifdef Progress_Log
  printf("1234567");
#endif

  while (cur_len = fread(buf, 1, byte_len, finp)) {
#ifdef Progress_Log
    printf("\b\b\b\b\b\b\b%4d MB", cnt++);
#endif
    md5_update(&ctx, buf, cur_len);
  }

  md5_finish(&ctx, dgst);

  // Stop measuring time and calculate the elapsed time
  gettimeofday(&end, 0);
  long seconds = end.tv_sec - begin.tv_sec;
  long microseconds = end.tv_usec - begin.tv_usec;
  double elapsed = seconds + microseconds * 1e-6;
  printf("\nTime measured: %.3f seconds.\n", elapsed);

  dump_buf(dgst, dgst_len);
  fclose(finp);
}

void test_large_file_sha(const char *filename) {
  const size_t dgst_len = SHA1_DIGST_SZ_IN_BT;
  uint8_t dgst[dgst_len];

  // Start measuring time
  struct timeval begin, end;
  gettimeofday(&begin, 0);
  const size_t byte_len = 1 << 20;
  uint8_t buf[byte_len];
  FILE *finp = fopen(filename, "r");
  if (finp == NULL) {
    printf("fail to open\n");
    return;
  }

#ifdef Progress_Log
  printf("Hashing... finished:\n");
#endif

  sha1_ctx_t ctx;
  sha1_init(&ctx);
  int cnt = 0;
  size_t cur_len = 0;
#ifdef Progress_Log
  printf("1234567");
#endif

  while (cur_len = fread(buf, 1, byte_len, finp)) {
#ifdef Progress_Log
    printf("\b\b\b\b\b\b\b%4d MB", cnt++);
#endif
    sha1_update(&ctx, buf, cur_len);
  }

  sha1_finish(&ctx, dgst);

  // Stop measuring time and calculate the elapsed time
  gettimeofday(&end, 0);
  long seconds = end.tv_sec - begin.tv_sec;
  long microseconds = end.tv_usec - begin.tv_usec;
  double elapsed = seconds + microseconds * 1e-6;
  printf("\nTime measured: %.3f seconds.\n", elapsed);

  dump_buf(dgst, dgst_len);
  fclose(finp);
}
