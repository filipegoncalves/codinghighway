/*
2.5
There are many viable interfaces for stacks. Design and implement some alternatives to the Stack interface. For example, one alternative is to specify a maximum size as an argument to Stack_new.
--
It is very easy to implement a stack using an array. This implementation will rely on a dynamically allocated array whose size is specified to Stack_new.
The stack shall not hold more than the elements it was created for.

To accomodate this, we will add a new field in a stack structure: instead of storing elements in a linked list, we store them in a dynamically allocated array.

asserts() are now commented and calls to NEW() and FREE() were replaced by malloc() and free(), so that this file is compilable without relying on the interfaces of later chapters.
*/

#include "stack_2.5.h"
#include <stdio.h>
#include <stdlib.h>

#define T Stack_T

struct T {
  int count;
  int capacity;
  void **elements;
};

T Stack_new(int capacity) {
  T stk;

  stk = malloc(sizeof(*stk));
  if (stk == NULL)
    return NULL;
  stk->count = 0;
  stk->capacity = capacity;
  if ((stk->elements = malloc(sizeof(*stk->elements)*capacity)) == NULL) {
    free(stk);
    return NULL;
  }
  return stk;
}

int Stack_empty(T stk) {
  /* assert(stk); */
  return stk->count == 0;
}

void Stack_push(T stk, void *x) {
  /*
    assert(stk);
    assert(stk->count < stk->capacity);
  */
  stk->elements[stk->count++] = x;
}

void *Stack_pop(T stk) {
  /* assert(stk);
     assert(stk->count > 0);
  */
  return stk->elements[--stk->count];
}

void Stack_free(T *stk) {
  /*
    assert(stk && *stk);
  */
  free((*stk)->elements);
  free(*stk);
  *stk = NULL;
}

