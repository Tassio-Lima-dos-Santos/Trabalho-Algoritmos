#include <stdio.h>

int procurar_menor(int *v, int n){
  int menor = 0;
  for(int i = 0; i < n; i++){
    if(v[i] < v[menor]){
      menor = i;
    }
  }
  return menor;
}

void troca(int *v, int posicao1, int posicao2){
   int *buffer = malloc(sizeof(int));
   *buffer = v[posicao1];
   v[posicao1] = v[posicao2];
   v[posicao2] = *buffer;
   free(buffer);
}

void ordenacao_selecao(int *v, int n){
  int menor,temp;
  for(int i = 0; i < n-1; i++){
    menor = i;
    for(int j = i+1; j < n; j++){
      if(v[j] < v[menor])
      menor = j;
    }
    temp = v[i];
    v[i] = v[menor];
    v[menor] = temp;
  }
  /*for(int i = 0; i < n-1; i++){
    troca(v, i, procurar_menor(v+i, n-i));
  }*/
}

int main(){
  int i, vetor[10] = {10,9,8,7,6,5,4,3,2,1};
  ordenacao_selecao(vetor, 10);
  for(i = 0; i < 10; i++){
    printf("%d ", vetor[i]);
  }
}