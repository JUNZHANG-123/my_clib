#include <sys/time.h>
#include <stddef.h>
#include <stdio.h>

void f()
{
  //...
}
int main()
{
  struct timeval t1, t2;
  gettimeofday(&t1, NULL);
  f();
  gettimeofday(&t2, NULL);
  //那么函数f运行所花的时间为
  unsigned long diff = (t2.tv_sec-t1.tv_sec) * 1000000 + t2.tv_usec-t1.tv_usec;
  
  printf("diff=%ld\n", diff);
  return 0;
}

