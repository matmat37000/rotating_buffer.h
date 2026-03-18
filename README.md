# rotating-buffer.h
A single header C/C++ library

## How to use ?

To use this library you just `#include "rotating_buffer.h"` in any file using it. You also need to add `#define LIBROTATING_BUFFER_IMPLEMENTATION` before one of the `#include` to add implementation of the code in the file.

**Exemple:**

```c
#define LIBROTATING_BUFFER_IMPLEMENTATION
#include "rotating_buffer.h"


int main() {
  rotating_buffer buf = create_rotating_buffer(4);
  
  for (int i = 0; i <= 7; i++)
    add(&buf, i);
}
```
