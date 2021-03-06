#include <stdint.h>
#include <stdlib.h>

int func2(const uint8_t *data, size_t len) {
  int cnt = 0;

  if (len < 4) {
    return 1;
  }

  if (data[0] == 'a') { cnt++; }
  if (data[1] == 'b') { cnt++; }
  if (data[2] == 'c') { cnt++; }

  if (cnt >= 3) {
    switch (data[3]) {
      case '0': {
        // segv
        int *p = NULL; *p = 123;
        break;
      }
      case '1': {
        // stack-buffer-underflow
        int* p = &cnt - 32; for (int i = 0; i < 32; i++) { *(p + i) = 0; }
        break;
      }
      case '2': {
        // stack-buffer-overflow 
        int* p = &cnt + 32; for (int i = 0; i < 32; i++) { *(p - i) = 0; }
        break;
      }
      case '3': {
        // bad-free
        int *p = &cnt; free(p);
        break;
      }
    }
  }

  return 0;
}
