/*#include <stdio.h>

int mdc(int n[2]);

int main(){
  int input[2];

  printf("Digite dois número, um em cada linha.\n");
  scanf("%d %d", &input[0], &input[1]);

  printf("O MDC entre %d e %d é %d.", input[0], input[1], mdc(input));

  return 0;
}

int mdc(int n[2]){
  int r = 1;
  for(int i = 2; i<=n[0] && i<=n[1]; i++){
    if(n[0]%i == 0 && n[1]%i == 0){
      r = i;
    }
  }
  
  return r;
}*/