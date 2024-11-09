/*#include <stdio.h>
#include <stdlib.h>

void lerVetor(int vetor[10]);

int maior(int vetor[10]);

int menor(int vetor[10]);

int main(){
  int vetor[10];

  lerVetor(vetor);

  printf("O maior elemento é: %d\n", maior(vetor));

  printf("O menor elemento é: %d", menor(vetor));

  return 0;
}

void lerVetor(int vetor[10]){
  printf("Digite 10 valores, um em cada linha\n");

  for(int i = 0; i < 10; i++){
    scanf("%d", &vetor[i]);
  }
}

int maior(int vetor[10]){
  int maiorNum = vetor[1];

  for(int i = 0; i < 10; i++){
    if(vetor[i] > maiorNum){
      maiorNum = vetor[i];
    }
  }

  return maiorNum;
}

int menor(int vetor[10]){
  int menorNum = vetor[1];

  for(int i = 0; i < 10; i++){
    if(vetor[i] < menorNum){
      menorNum = vetor[i];
    }
  }

  return menorNum;
}*/