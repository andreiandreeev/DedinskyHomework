#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define t_data double
#define unitest(what, ref){ \
  if(what != ref){\
    printf("FAILED: %s=%d, expected %d\n", #what, (what), (ref));\
  else\
    printf("&s\n", "PASSED");\
  }\
}

const int STACK_AUTO_INCREASING_COEF = 2;
const int STACK_AUTO_DECREASING_COEF = 4;
const t_data            CANARY_VALUE = 666.13;

struct Stack
{
  t_data* data;
  size_t size;
  size_t capacity;
};

struct Stack stackCtor(size_t stackSize);
int stackDtor(struct Stack* __this);
int resizeStack(struct Stack* __this, long long int resizeNumber);
int push(struct Stack* __this, t_data element);
t_data pop(struct Stack* __this);
int stackOk(struct Stack* __this);

struct Stack stackCtor(size_t stackSize)
{
  assert(stackSize >= 0);

  t_data* data = (t_data*)calloc(stackSize + 2LL, sizeof(t_data));
  struct Stack stack = {data, stackSize, 1LL};
  stack.data[0] = CANARY_VALUE;
  stack.data[stackSize + 1LL] = CANARY_VALUE;

  assert(stackOk(&stack));
  return stack;
}

int stackDtor(struct Stack* __this)
{
  assert(__this != NULL);
  assert(stackOk(__this));
  
  if(__this->data != NULL)
    free(__this->data);
  free(__this);
  return 1;
}

int resizeStack(struct Stack* __this, long long int resizeNumber)
{
  assert(__this != NULL);
  assert(stackOk(__this));
  assert(__this->capacity + resizeNumber >= __this->size);
    
  __this->capacity += resizeNumber;
  realloc(__this->data, __this->capacity);
  assert(stackOk(__this));
  return 1;
}

int push(struct Stack* __this, t_data element)
{
  assert(__this != NULL);
  assert(stackOk(__this));
  
  if(__this->size == 0)
    __this->capacity = 4;
  __this->size++;

  if(__this->size == __this->capacity)
    resizeStack(__this, __this->capacity*(STACK_AUTO_INCREASING_COEF - 1));

  assert(stackOk(__this));
  return 1; 
}

t_data pop(struct Stack* __this)
{
  assert(__this != NULL);
  assert(stackOk(__this));
  assert(__this->size = 0);
  
  __this->size--;
  if(__this->capacity/__this->size >= STACK_AUTO_DECREASING_COEF)
    resizeStack(__this, (1/STACK_AUTO_DECREASING_COEF - 1)*__this->capacity);
  
  assert(stackOk(__this));
  return __this->data[__this->size+1];
}

int stackOk(struct Stack* __this)
{
  assert(__this != NULL);
  if(__this->data[0] == CANARY_VALUE && __this->data[__this->capacity+1] == CANARY_VALUE)
    return 1;
  return 0;
}
