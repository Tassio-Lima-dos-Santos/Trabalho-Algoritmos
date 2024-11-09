#include <stdio.h>

int pesquisa_binaria (int *v, int x, int inicio, int fim){
  while (inicio<=fim){
  int meio = (inicio+fim)/2;
  //printf("%d", meio);
  if(x==v[meio]){
    return meio;
  }/*else if(fim < inicio){
    return -1;
  }*/else if(x > v[meio]){
    inicio = meio+1;
    //pesquisa_binaria(v, x, meio+1, fim);
  }else if(x < v[meio]){
    fim = meio-1;
    //pesquisa_binaria(v, x, inicio, meio-1);
  }
}return -1;
}

/*int main(){
  int n, vetor[10] = {1,2,3,4,5,6,7,8,9,10};
  printf("Digite o número a pesquisar: ");
  scanf("%d", &n);
  printf("Resultado da busca: %d\n", pesquisa_binaria(vetor,n,0,9));
}*/