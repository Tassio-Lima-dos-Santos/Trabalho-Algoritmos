#include <stdio.h>

// Prototipação das funções criadas no código.
// É importante para que o compilador conheça essa função, seu tipo e os seus argumentos,
// assim o código pode chamar essa função mesmo que o corpo da função só apareça depois da chamada.
int maxDiferenca(int matriz[379][4]);
float tempoMedio(int matriz[379][4], int status);
void ocorrenciasSobrecarga(int matriz[379][4]);
int ocorrenciaMaiorDuracao(int matriz[379][4],int operacao, int status);

int main(){
// Os dados que serão usados pelo código
  int log[379][4] = {
      {10706,59,1,1},{10709,112,4,1},{10723,29,3,0},{10726,84,5,1},{10802,86,2,2},{10816,102,4,1},{10900,115,4,3},{10912,67,6,1},{10926,80,1,2},{11005,89,6,1},{11104,4,6,0},{11207,40,3,0},{11210,104,5,0},{11216,112,6,1},{11300,87,2,1},{11404,35,6,0},{11409,69,2,0},{11422,53,5,1},{11504,70,4,0},{11512,33,4,0},{11602,39,3,2},{11611,33,4,2},{11706,8,1,0},{11801,94,4,2},{11903,41,3,1},{12006,49,6,3},{12103,98,6,0},{12115,122,4,1},{12205,110,3,1},{12208,55,5,2},{12300,29,2,0},{12303,76,4,1},{20700,87,1,2},{20804,48,5,0},{20905,86,4,0},{20914,23,6,0},{21005,15,3,2},{21101,123,4,3},{21105,92,5,0},{21112,92,4,2},{21205,97,3,0},{21213,120,6,1},{21307,4,6,0},{21407,107,2,2},{21417,105,4,2},{21506,51,4,0},{21516,11,4,3},{21525,96,2,0},{21532,108,5,0},{21542,54,2,0},{21554,51,5,0},{21559,61,3,0},{21607,108,4,0},{21620,23,6,0},{21634,105,5,1},{21640,59,4,1},{21645,96,2,0},{21654,93,4,1},{21703,109,5,0},{21708,15,4,0},{21801,113,1,0},{21901,27,4,2},{22003,74,3,0},{22102,47,6,2},{22202,77,5,1},{22216,95,6,0},{22230,4,3,2},{22238,69,4,3},{22305,65,6,2},{22319,100,5,0},{30708,27,6,0},{30713,92,4,0},{30723,10,1,1},{30805,33,5,0},{30904,15,4,0},{30916,31,1,2},{30926,111,6,0},{31005,24,2,1},{31104,41,6,0},{31115,31,6,2},{31205,9,3,0},{31219,110,4,0},{31229,45,1,2},{31302,66,4,0},{31403,90,5,2},{31417,78,3,1},{31508,40,6,2},{31601,72,2,0},{31612,54,4,1},{31704,54,1,1},{31707,29,6,0},{31802,73,6,0},{31809,89,1,0},{31904,71,6,0},{32004,119,4,3},{32017,115,6,1},{32105,85,2,2},{32204,111,6,0},{32206,73,2,0},{32304,40,6,3},{32310,35,4,0},{40704,77,3,0},{40712,12,4,1},{40716,3,5,0},{40802,82,4,0},{40904,57,2,0},{41005,5,4,1},{41100,42,2,0},{41111,99,5,0},{41119,57,3,1},{41128,57,6,0},{41140,108,2,0},{41207,111,4,3},{41308,9,2,2},{41320,38,5,0},{41402,36,1,0},{41508,46,5,0},{41608,93,5,3},{41617,39,6,1},{50701,18,5,1},{50800,118,1,0},{50806,103,5,3},{50905,110,5,2},{50917,89,5,2},{51007,47,1,0},{51016,26,4,3},{51019,61,1,0},{51031,58,4,2},{51038,121,5,1},{51100,95,4,0},{51208,4,6,0},{51218,72,2,0},{51228,113,4,1},{51306,115,4,2},{51312,123,5,1},{51404,89,2,2},{51500,102,6,2},{51508,95,5,2},{51522,77,4,0},{51532,62,1,0},{51606,110,6,0},{51619,107,6,3},{51707,53,6,3},{51806,87,1,0},{80700,90,5,2},{80714,116,6,0},{80803,82,3,1},{80905,105,6,1},{80919,28,1,0},{80931,63,4,0},{81004,122,4,3},{81007,24,5,2},{81017,64,2,1},{81102,2,6,0},{81109,86,3,0},{81121,97,5,1},{81200,75,4,0},{81305,100,3,0},{81314,38,5,1},{81403,26,1,0},{81416,32,6,1},{81503,15,4,0},{81509,79,3,0},{81606,106,6,1},{81620,71,1,0},{81628,112,4,3},{81632,77,4,0},{81701,122,2,0},{81801,94,4,1},{81901,10,6,2},{90703,64,4,2},{90709,41,3,1},{90803,74,6,0},{90901,92,5,0},{90915,38,1,0},{91002,65,4,1},{91010,72,2,2},{91021,68,4,2},{91103,85,2,3},{91201,118,6,0},{91209,105,2,2},{91213,74,5,2},{91218,52,4,1},{91225,32,4,0},{91234,116,3,0},{91303,20,6,2},{91403,41,6,1},{91412,72,5,1},{91505,51,6,2},{91515,5,3,1},{100708,39,6,0},{100720,117,4,0},{100728,118,6,2},{100808,47,5,0},{100901,56,5,0},{100911,112,3,2},{100914,88,4,0},{100922,98,3,0},{100929,115,6,1},{
      101007,5,4,1},{101107,54,1,0},{101208,52,5,0},{101308,44,3,0},{101401,42,5,0},{110706,37,6,0},{110802,99,6,3},{110907,43,2,1},{111000,97,4,1},{111004,24,2,2},{111103,30,4,0},{111205,80,6,1},{111212,21,3,2},{111223,71,6,0},{111302,61,1,0},{111408,61,5,2},{111504,32,3,2},{111512,59,4,0},{111601,120,5,3},{111704,114,4,0},{111806,85,4,1},{120700,11,4,3},{120710,40,5,1},{120716,63,5,0},{120721,4,3,0},{120735,24,6,0},{120748,42,5,2},{120756,3,3,0},{120760,10,5,1},{120806,116,6,0},{120908,102,6,1},{121008,18,2,2},{121101,28,5,0},{121208,64,3,2},{121215,95,6,0},{121302,46,1,0},{121307,78,6,0},{121400,30,3,3},{121409,4,6,0},{121505,117,1,2},{150705,48,6,2},{150715,6,2,0},{150727,77,6,2},{150801,101,1,1},{150901,84,5,1},{150906,75,4,0},{150915,119,3,3},{150929,17,6,0},{151006,53,2,1},{151105,86,6,0},{151113,113,6,0},{151120,66,4,0},{151129,115,6,3},{151202,112,6,1},{151303,111,6,0},{151405,72,5,1},{151411,52,3,0},{151507,12,5,2},{151513,107,6,0},{151520,92,6,0},{151604,34,1,0},{151616,60,4,0},{160707,59,3,0},{160721,119,6,0},{160803,38,2,2},{160812,50,6,0},{160906,77,6,0},{161000,55,3,1},{161014,53,5,2},{161021,66,6,0},{161032,55,3,0},{161101,71,5,0},{161202,12,6,2},{161206,23,2,2},{161304,84,6,1},{161307,64,3,0},{161405,15,5,2},{161417,111,5,0},{161429,56,6,0},{161442,46,4,0},{161506,108,6,0},{161608,2,5,1},{161622,13,4,2},{161707,87,3,1},{161712,75,5,2},{170705,57,2,0},{170804,108,5,2},{170903,94,4,1},{171008,91,2,1},{171101,22,5,0},{171106,78,4,2},{171118,37,1,0},{171201,43,5,2},{171301,33,1,0},{171308,25,6,0},{171313,91,3,2},{171403,62,5,1},{171408,118,5,2},{171503,110,5,1},{171512,77,1,3},{171518,26,5,0},{171600,54,2,0},{171702,105,4,1},{171803,12,1,0},{171901,39,5,0},{172004,42,4,0},{180708,59,4,3},{180807,91,6,0},{180820,99,1,0},{180828,15,6,2},{180839,88,5,2},{180844,3,1,0},{180849,33,5,0},{180901,102,2,2},{180911,29,5,1},{180925,12,4,1},{181007,63,5,3},{181103,32,1,0},{181203,21,5,0},{181301,3,2,2},{181309,57,6,0},{181400,119,2,3},{181508,13,4,0},{181603,25,3,3},{181611,39,5,2},{181702,20,6,1},{181808,75,3,0},{181819,48,6,2},{181901,5,6,0},{182001,59,1,1},{182005,50,4,1},{190700,54,2,0},{190805,81,6,0},{190902,58,4,0},{191006,28,3,0},{191101,101,5,2},{191110,67,3,2},{191200,9,6,1},{191213,109,2,2},{191218,4,4,1},{191308,75,3,3},{191408,18,5,1},{191502,34,6,0},{191603,63,1,0},{191704,25,6,0},{191707,65,1,1},{191713,2,5,0},{191808,19,4,0},{191904,40,4,0},{191914,45,4,0},{192003,42,3,0},{220704,75,4,0},{220709,26,5,1},{220804,90,6,0},{220814,86,1,2},{220904,70,4,0},{221008,114,2,1},{221100,50,5,0},{221114,15,3,1},{221123,73,6,0},{221126,10,1,1},{221205,21,4,1},{221305,92,3,0},{221403,93,4,1},{221501,72,1,1},{221507,11,5,3},{221601,95,1,0},{221608,38,5,2},{221620,24,4,1},{221706,4,5,1},{221713,39,1,0},{221719,74,5,0},{221804,110,6,2},{221812,61,2,1},{221824,64,4,0},{221904,14,5,0},{221911,50,6,0},{222007,78,6,3},{222106,83,2,0},{222109,113,6,0}
      };
  int input[3];

  printf("Maior diferença de tempo de início entre duas ocorrências: %d\n", maxDiferenca(log));

  printf("\nInforme um status: ");
  scanf("%d", &input[0]);
  printf("\nTempo médio de todas as operações com aquele status: %f\n", tempoMedio(log, input[0]));

  printf("\nOcorrências com sobrecarga de cada uma das operações: \n");
  ocorrenciasSobrecarga(log);

  printf("\nInforme um tipo de operação e um status: ");
  scanf("%d %d", &input[1], &input[2]);
  printf("\nOperação de maior duração daquele tipo com aquele status: %d", ocorrenciaMaiorDuracao(log, input[1], input[2]));

  return 0;
}

int maxDiferenca(int matriz[379][4]){
// Uma variável que representa a atual maior diferença de tempo de início,
// como nenhum dado foi comparado até agora, a variável é igual a 0
  int maiorDiferenca = 0;

// Um loop for que vai percorrer desde a segunda ocorrência até a última da matriz
  for(int i = 1; i < 379; i++){

  // Uma variável que representa a diferença de tempo de início entre
  // a ocorrência que está sendo analisada e a ocorrência anterior
    int diferencaAtual = matriz[i][0] - matriz[i-1][0];
  // Compara a diferença que acabou de ser analisada com a até então maior diferença.
  // Se a diferença que foi analisada agora é maior, então ela se torna a maior diferença.
    if( diferencaAtual > maiorDiferenca){
      maiorDiferenca = diferencaAtual;
    }
  }

// Depois de analisar todas as ocorrências, a função retorna a maior diferença de todos os elementos comparados
  return maiorDiferenca;
}

float tempoMedio(int matriz[379][4], int status){
// Se o status que foi passado como parâmetro da função for maior que 3 ou menor que 0,
// ou seja, for um status inválido, então a função retorna -1, o que quer dizer que ocorreu um erro.
  if(status < 0 || status > 3){
    return -1;
  }

// Essas duas variáveis representam a soma da duração de todas as ocorrências com um status e o número de
// ocorrências com aquele status, respectivamente. Esses dois valores são úteis para calcular a média.
  int soma = 0;
  int ocorrenciasAnalisadas = 0;

// Loop for que vai da primeira ocorrência até a última
  for(int i = 0; i < 379; i++){
  // Para cada ocorrência percorrida pelo loop for, o código vai comparar se o status daquela ocorrência é igual
  // ao status passado como parâmetro. Se sim, a duração daquela ocorrência é somada à soma e o número de ocorrências
  // analisadas, que são aquelas com mesmo status, aumenta em 1.
    if(status == matriz[i][3]){
      soma += matriz[i][1];
      ocorrenciasAnalisadas++;
    }
  }
// O valor da média é igual a soma da duração de todas ocorrências analisadas dividida pelo número de ocorrências.
// É importante adicionar o (float) para converter a soma, que é um inteiro, para float, pois uma divisão entre dois
// inteiros é igual a outro inteiro, que é um arredondamento dessa divisão.
  float media = (float) soma/ocorrenciasAnalisadas;
  return media;
}

void ocorrenciasSobrecarga(int matriz[379][4]){
// Aqui foi criado um array no qual cada item representa o número de sobrecargas de um tipo de operação específico
  int sobrecargas[6] = {0, 0, 0, 0, 0, 0};

// Loop for que vai da primeira ocorrência até a última
  for(int i = 0; i < 379; i++){
  // Se o status da ocorrência que está sendo analisada for igual a 2 ou 3, que são os status de sobrecarga,
  // então um dos valores de sobrecarga aumenta em 1. A posição do item no array que será incrementado é 
  // igual ao valor de operação da ocorrência analisada - 1, isso porque o valor de operação vai de 1 a 6 e
  // as posições do array de sobrecarga vão de 0 a 5.
    if(matriz[i][3] == 2 || matriz[i][3] == 3){
      sobrecargas[matriz[i][2] - 1]++;
    }
  }

// Print dos valores de sobrecarga de cada tipo de operação
  printf("carregar matéria-prima 1: %d\n", sobrecargas[0]);
  printf("carregar matéria-prima 2: %d\n", sobrecargas[1]);
  printf("carregar matéria-prima 3: %d\n", sobrecargas[2]);
  printf("processo de secagem: %d\n", sobrecargas[3]);
  printf("processo de lavagem: %d\n", sobrecargas[4]);
  printf("processo de tingimento: %d\n", sobrecargas[5]);
}

int ocorrenciaMaiorDuracao(int matriz[379][4], int operacao, int status){
// Se os valores dos parâmetros de operação ou status forem inválidos, então a função retorna -1
  if(status < 0 || status > 3 || operacao < 1 || operacao > 6){
    return -1;
  }

// Essas variáveis representam respectivamente a maior duração das ocorrências daquele tipo de operação
// e com aquele status que foram analisadas até agora, por isso que inicia em 0, e a posição da ocorrência
// com a maior duração. A primeira variável tem que iniciar com 0, pois ela vai ser comparada logo depois
// e se ele não for iniciada, ela começa com um valor aleatório, o que vai prejudicar a comparação.
  int maiorDuracao = 0;
  int posicaoMaiorDuracao;

// Loop for que vai da primeira ocorrência até a última
  for(int i = 0; i < 379; i++){
  // Se o tipo de operação e o status da ocorrência que está sendo percorrida forem iguais ao tipo de 
  // operação e status passados como parâmetro, e a duração dessa ocorrência for maior que a maior
  // duração já registrada. Então a duração dessa ocorrência se torna a maior duração e a posição da
  // ocorrência com maior duração se torna o índice da ocorrência + 1, pois o índice da matriz vai
  // de 0 a 378, que é a posição do item - 1.
    if(operacao == matriz[i][2] && status == matriz[i][3] && matriz[i][1] > maiorDuracao){
      maiorDuracao = matriz[i][1];
      posicaoMaiorDuracao = i+1;
    }
  }

  // No final, a função retorna a posição da ocorrência com a maior duração.
  return posicaoMaiorDuracao;
}