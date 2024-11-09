/*#include <stdio.h>

double euler(int n);
int factorial(int n);

int main(){
  int input;

  printf("Digite um número.\n");
  scanf("%d", &input);

  printf("S = %lf", euler(input));

  return 0;
}

double euler(int n){
  double e = 0;

  for(int i = 0; i <= n; i++){
    e += (double) 1/factorial(i);
  }
  
  return e;
}

int factorial(int n){
  if(n < 0){
    return -1;
  }
  int r = 1;
  for(int i = n; i > 0; i--){
    r *= i;
  }
  return r;
}*/