#include <stdio.h>

int fib(int num1, int num2, int start, int fin) {
  if(start < fin) {
    int num3;
    num3 = num1+num2;
    printf("%d",num3);
    printf(" ");
    fib(num2,num3,start+1,fin);
  }
  return 0;
}

int main(int argc, char const *argv[]) {
  fib(0,1,0,10);
  return 0;
}
