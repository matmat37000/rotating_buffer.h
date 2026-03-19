/****************************************************************************
 *  rotating_buffer.h
 *  BORDIER-AUPY Mathieu
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

/** A rotating buffer */
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
 * @param buf Address of the buffer to initialise
 * @param size Size of the buffer
 */
void rotating_buffer_init(rotating_buffer *buf, int size);

/** 
 * Create a buffer object, and use rotating_buffer_init
 *
 * @param size Size of the buffer
 */
rotating_buffer rotating_buffer_create(int size);

/**
 * Free the allocated memory inside the struct, 
 * doesn't free the struct pointer
 *
 * @param buf Address of the buffer to free the content
 */
void rotating_buffer_free(rotating_buffer *buf);

/**
 * Add an element to the buffer
 *
 * @param buf Address of the buffer to modify
 * @param element the element to add
 */
void rotating_buffer_add(rotating_buffer *buf, int element);

/**
 * Get an element of the buffer
 *
 * @param buf Address of the buffer to get the element of
 * @param pos The index of the element
 */
int* rotating_buffer_get(const rotating_buffer *buf, int pos);

#endif // MATHIOL_ROTATING_BUFFER_H_

/* IMPLEMENTATION */
#if defined(LIB_ROTATING_BUFFER_IMPLEMENTATION) || defined(__CLION_IDE__) || defined(__INTELLISENSE__)

#include <stdlib.h>

inline void rotating_buffer_init(rotating_buffer *buf, const int size) {
  buf->size = 0;
  buf->allocated_size = size + 1;
  buf->raw = (int*)malloc(sizeof(int) * buf->allocated_size);
  buf->start_ptr = buf->end_ptr = &buf->raw[0];
}

inline rotating_buffer rotating_buffer_create(const int size) {
  rotating_buffer buf;
  rotating_buffer_init(&buf, size);
  return buf;
}

inline void rotating_buffer_free(rotating_buffer *buf) {
  free(buf->raw);
  buf->allocated_size = buf->size = 0;
  buf->raw = buf->start_ptr = buf->end_ptr = NULL;
}

void rotating_buffer_add(rotating_buffer *buf, const int element) {
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

inline int* rotating_buffer_get(const rotating_buffer *buf, const int pos) {
  int *ptr = buf->start_ptr + pos;
  const int *max = buf->raw + (buf->allocated_size - 1);
  // Clamp the pointer back to the start
  // with the difference of passed cell from the max
  if (ptr > max) {
    ptr = buf->raw + (ptr - max - 1); // Minus one for the buffer cell
  }

  return ptr;
}

#endif // LIB_ROTATING_BUFFER_IMPLEMENTATION