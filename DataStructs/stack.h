#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef double t_data; 

#define unitest(what, ref){ \
  if(what != ref){\
    printf("FAILED: %s=%d, expected %d\n", #what, (what), (ref))\
  else\
    printf("&s\n", "PASSED")\
  }\
}

const int STACK_AUTO_INCREASING_COEF = 2;
const int STACK_AUTO_DECREASING_COEF = 4;
const t_data            CANARY_VALUE = 666.13;

struct Stack
{
  t_data* data = {};
  size_t size = 0;
  size_t capacity = 0;
};

struct Stack stackCtor(size_t stackSize);
int stackDtor(struct Stack* __this);
int stackResize(struct Stack* __this, long long int resizeNumber);
int stackPush(struct Stack* __this, t_data element);
t_data stackPop(struct Stack* __this);
int stackOk(struct Stack* __this);
size_t stackGetSize(struct Stack* __this);
size_t stackGetCapacity(struct Stack* __this);

/*
int main()
{
  struct Stack stack = stackCtor(0);
  
  unitest(stackOk(&stack), 1);
  unitest(stackGetSize(&stack), 0);
  unitest(stackGetCapacity(&stack), 0);
  unitest(stackPush(&stack, 42), 1); 
  unitest(stackOk(&stack), 1);
  unitest(stackGetSize(&stack), 1);
  unitest(stackgetCapacity(&stack), 4);
  unitest(stackPop(&stack), 42);
  unitest(stackOk(&stack), 1);
  unitest(stackGetSize(&stack), 0);
  unitest(stackGetCapacity(&stack), 0);
  unitest(stackResize(&stack, 42), 1);
  unitest(stackOk(&stack), 1);
  unitest(stackGetCapacity(&stack), 42);
  unitest(stackGetSize(&stack), 0);
  unitest(stackDtor(&stack), 1);
}
*/

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
  assert(stackOk(__this));
  
  if(__this->data != NULL)
  {
    __this->size = -1;
    __this->capacity = -1;
    __this->data = {};
    free(__this->data);
  }
  free(__this);
  return 1;
}

int stackResize(struct Stack* __this, ssize_t resizeNumber)
{
  assert(stackOk(__this));
  assert(__this->capacity + resizeNumber >= __this->size);
    
  __this->capacity += resizeNumber;
  __this->data = realloc(__this->data, __this->capacity);
  assert(stackOk(__this));
  return 1;
}

int stackPush(struct Stack* __this, t_data element)
{
  assert(stackOk(__this));
  
  if(__this->size == 0)
    __this->capacity = 4;
  __this->size++;

  if(__this->size == __this->capacity)
    resizeStack(__this, __this->capacity*(STACK_AUTO_INCREASING_COEF - 1));

  assert(stackOk(__this));
  return 1; 
}

t_data stackPop(struct Stack* __this)
{
  assert(stackOk(__this));
  assert(__this->size == 0);
   
  if(__this->capacity/__this->size <= 1/STACK_AUTO_DECREASING_COEF)
    resizeStack(__this, (1/STACK_AUTO_DECREASING_COEF - 1)*__this->capacity);
  
  __this->size--;
  assert(stackOk(__this));
  return __this->data[__this->size+1];
}

int stackOk(struct Stack* __this)
{
  if(__this != NULL && __this->data[0] == CANARY_VALUE && __this->data[__this->capacity+1] == CANARY_VALUE && __this->capacity >= __this->size && __this->capacity >=0 && __this->size >= 0)
    return 1;
  return 0;
}
