# rotating-buffer.h
A single header C/C++ library

## How to use ?

To use this library you just `#include "rotating_buffer.h"` in any file using it. You also need to add `#define LIB_ROTATING_BUFFER_IMPLEMENTATION` before one of the `#include` to add implementation of the code in the file.

**Exemple:**

```c
#define LIB_ROTATING_BUFFER_IMPLEMENTATION
#include "rotating_buffer.h"

int main() {
  rotating_buffer buf = create_rotating_buffer(4);
  
  for (int i = 0; i <= 7; i++)
    add(&buf, i);
}
```

> [!NOTE]
> This library use `malloc` to allocated memory for the buffer !

> [!IMPORTANT]
> To free the buffer, call `rotating_buffer_free` on it.
> ```c
> // Create the object
> rotating_buffer *buf = malloc(sizeof(rotating_buffer));
> rotating_buffer_init(buf, 10);
>
> // Call it beffor the free-ing the pointer
> rotating_buffer_free(buf);  // Free allocated memory by the buffer
> free(buf); // Free allocated memory for the object
> ```

---
This project is licensed under the [GNU Lesser General Public License](https://www.gnu.org/licenses/lgpl-3.0.html).
