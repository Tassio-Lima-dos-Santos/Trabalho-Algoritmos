#include <stdio.h>
#include <stdlib.h>

void merge(int *v, int inicio1, int fim1, int inicio2, int fim2){
  int i = inicio1, j = inicio2, k = inicio1;
  int **temp = malloc(sizeof(int*) * fim2-inicio1);
  while(i <= fim1 || j <= fim2){
    if(v[i] <= v[j]){
      *temp[k] = v[i];
      i++;
    }else{
      *temp[k] = v[j];
      j++;
    }
    k++;
  }
  while(i<=fim1){
    *temp[k] = v[i];
    i++;
    k++;
  }
  while(j<=fim2){
    *temp[k] = v[j];
    j++;
    k++;
  }
  for(int n = inicio1; n <= fim2; n++){
    v[n] = *temp[n-inicio1];
  }
  free(temp);
}

void mergeSort(int *v, int inicio, int fim){
  if(inicio < fim){
    int meio = (inicio+fim)/2;
    mergeSort(v, inicio, meio);
    mergeSort(v, meio+1, fim);
    merge(v, inicio, meio, meio+1, fim);
  }
}

int main(){
  int vetor[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  mergeSort(vetor, 0, 9);
  for(int i = 0; i < 10; i++){
    printf("%d ", vetor[i]);
  }
}