/*#include <stdio.h>

int verificarTriangulo(int n[3]);

int main(){
  int input[3];

  printf("Digite três valores, um em cada linha.\n");
  scanf("%d %d %d", &input[0], &input[1], &input[2]);

  if(verificarTriangulo(input)){
    printf("Estes valores formam um triângulo.");
  }else{
    printf("Estes valores não formam um triângulo.");
  }

  return 0;
}

int verificarTriangulo(int n[3]){
  return ( (n[0] < n[1]+n[2]) && (n[1] < n[0]+n[2]) && (n[2] < n[1]+n[0]) ) ? 1 : 0;
}*/