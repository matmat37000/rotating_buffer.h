/****************************************************************************
 *  
 *  This program is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or (at 
 *  your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 ****************************************************************************/

/* DECLARATION */

#ifndef MATHIOL_ROTATING_BUFFER_H_
#define MATHIOL_ROTATING_BUFFER_H_

#include <stdlib.h>

/** 
 * A rotating buffer
 */
typedef struct {
  int size;
  int allocated_size;
  int* raw;
  int* start_ptr;
  int* end_ptr; 
} rotating_buffer;

/**
 * Initialise a buffer struct, call malloc for the memory
 *
 * @param buf Adresse of the buffer to initialise
 * @param size Size of the buffer
 */
void init_rotating_buffer(rotating_buffer *buf, int size);

/** 
 * Create a buffer object, and use init_rotating_buffer 
 * @param size Size of the buffer
 */
rotating_buffer create_rotating_buffer(int size);

/**
 * Free the allocated memory inside the struct, 
 * doesn't free the struct pointer
 * @param buf Adresse of the buffer to free the content
 */
void free_rotating_buffer(rotating_buffer *buf);

/**
 * Add an element to the buffer
 * @param buf Adresse of the buffer to modify
 * @param element the element to add
 */
void add(rotating_buffer *buf, int element);

/**
 * Get an element of the buffer
 * @param pos The index of the element
 */
int* get(rotating_buffer *buf, int pos);

#endif

/* IMPLEMENTATION */

#ifdef LIBROTATING_BUFFER_IMPLEMENTATION

inline void init_rotating_buffer(rotating_buffer *buf, int size) {
  buf->size = 0;
  buf->allocated_size = size + 1;
  buf->raw = (int*)malloc(sizeof(int) * buf->allocated_size);
  buf->start_ptr = buf->end_ptr = &buf->raw[0];
}

inline rotating_buffer create_rotating_buffer(int size) {
  rotating_buffer buf;
  init_rotating_buffer(&buf, size);
  return buf;
}

inline void free_rotating_buffer(rotating_buffer *buf) {
  free(buf->raw);
  buf->raw = buf->start_ptr = buf->end_ptr = nullptr;
}

void add(rotating_buffer *buf, int element) {
  // Move by one the end_ptr
  buf->end_ptr++;
  // Clamp it
  if (buf->end_ptr > buf->raw + buf->size) {
    buf->end_ptr = buf->raw;
  }
  // Set the value
  *buf->end_ptr = element;
 
  // Start moving the start only if buffer full
  if (buf->size == buf->allocated_size - 1) {
    // Move by one the start_ptr
    buf->start_ptr++;
    // Clamp it
    if (buf->start_ptr > buf->raw + buf->size) {
      buf->start_ptr = buf->raw;
    }
  }
  else {
    buf->size++;
  }
}

inline int* get(rotating_buffer *buf, int pos) {
  int *ptr = buf->start_ptr + pos;
  int *max = buf->raw + (buf->allocated_size - 1);
  // Clamp the pointer back to the start
  // with the difference of passed cell from the max
  if (ptr > max) {
    ptr = buf->raw + (ptr - max - 1); // Minus one for the buffer cell
  }

  return ptr;
}

#endif
