#include <cstdio>

#define LIBROTATING_BUFFER_IMPLEMENTATION
#include "rotating_buffer.h"

/// Quick demo of the buffer
int main() {
  rotating_buffer buf = create_rotating_buffer(4);
  
  for (int i = 0; i < buf.allocated_size; i++)
    printf("%d (%p)\n", buf.raw[i], &buf.raw[i]);

  for (int i = 0; i <= 7; i++)
    add(&buf, i);

  printf("--------\n");
  
  for (int i = 0; i < buf.allocated_size; i++) {
    if (&buf.raw[i] == buf.start_ptr) printf("\033[32m");
    else if (&buf.raw[i] == buf.end_ptr) printf("\033[31m");

    printf("%d (%p)\033[0m\n", buf.raw[i], &buf.raw[i]);
  }

  printf("--------\n");

  for (int i = 0; i < buf.size; i++) {
    int* val = get(&buf, i);
    printf("%d (%p)\n", *val, val);
  }
}
