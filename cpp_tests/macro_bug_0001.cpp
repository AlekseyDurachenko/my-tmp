#include <stdio.h>

#define test(val) \
{ \
    int some = 10; \
    printf("val: %d, some: %d\n", val, some); \
}


int main(void) 
{
  test(20);
  int x1 = 30;
  test(x1); // test
  // info 10
  int some = 40;
  test(some);
  // test 123
}
