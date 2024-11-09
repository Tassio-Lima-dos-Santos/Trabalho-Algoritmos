/*#include <stdio.h>

void maximoMinimo(int *v, int N, int *maximo, int *minimo);

int main(){
  int N = 5, max, min;
  int v[5] = {1, 2, 3, 4, 5};

  maximoMinimo(v, N, &max, &min);

  printf("%d %d", max, min);

  return 0;
}

void maximoMinimo(int *v, int N, int *maximo, int *minimo){
  *maximo = *v;
  *minimo = *v;
  for(int i = 0; i < N; i++){
    if(*(v+i) >= *maximo){
      *maximo = *(v+i);
    }else if(*(v+i) <= *minimo){
        *minimo = *(v+i);
    }
  }
}*/