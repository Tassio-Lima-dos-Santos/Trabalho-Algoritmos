#include <stdio.h>
#include <stdlib.h>

int *merge(int *v1, int t1, int *v2, int t2){
  int *novo = malloc(sizeof(int)*(t1+t2));
  int i=0, j=0, k=0;
  while(i<t1 && j<t2){
    if(v1[i]<=v2[j]){
      novo[k++] = v1[i++];
    }else{
      novo[k++] = v2[j++];
    }
  }
  while(i<t1){
    novo[k++] = v1[i++];
  }
  while(j<t2){
    novo[k++] = v2[j++];
  }
  return novo;
}

void mergeSort(int *v, int inicio, int fim){
  if(inicio < fim){
    int meio = (inicio+fim)/2;
    mergeSort(v, inicio, meio);
    mergeSort(v, meio+1, fim);
    int *novo = merge(v + inicio, meio+inicio+1, v + meio+1, fim-meio);
    for(int i = 0; i<=fim-inicio; i++){
      v[inicio+i]=novo[i];
    }
  }
}

/*int main(){
  int vetor[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  mergeSort(vetor, 0, 9);
  for(int i = 0; i < 10; i++){
    printf("%d ", vetor[i]);
  }
}*/