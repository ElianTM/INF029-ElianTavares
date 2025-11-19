// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Elian Tavares de Melo Junior
//  email: tavareselian2006@gmail.com
//  Matrícula: 20251160018
//  Semestre: 2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
  int datavalida = 1;
  DataQuebrada dq = quebraData(data);
  if (!dq.valido)
    return 0;

  if (dq.iDia <= 0 || dq.iMes <= 0 || dq.iMes > 12 || dq.iAno < 0)
    return 0;

  int diasMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  int bissexto = (dq.iAno % 400 == 0 || (dq.iAno % 4 == 0 && dq.iAno % 100 != 0));
  if (dq.iMes == 2 && bissexto)
    diasMes[2] = 29;

  if (dq.iDia > diasMes[dq.iMes])
    return 0;

  return 1;
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{
  DiasMesesAnos dma;

  if (q1(datainicial) == 0)
  {
    dma.retorno = 2;
    return dma;
  }
  else if (q1(datafinal) == 0)
  {
    dma.retorno = 3;
    return dma;
  }

  DataQuebrada dq1 = quebraData(datainicial);
  DataQuebrada dq2 = quebraData(datafinal);

  if (dq2.iAno < dq1.iAno || (dq2.iAno == dq1.iAno && dq2.iMes < dq1.iMes) || (dq2.iAno == dq1.iAno && dq2.iMes == dq1.iMes && dq2.iDia < dq1.iDia))
  {
    dma.retorno = 4;
    return dma;
  }

  int diasMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  int bissexto = (dq2.iAno % 400 == 0 || (dq2.iAno % 4 == 0 && dq2.iAno % 100 != 0));
  if (dq2.iMes == 2 && bissexto)
    diasMes[2] = 29;

  dma.qtdAnos = dq2.iAno - dq1.iAno;
  dma.qtdMeses = dq2.iMes - dq1.iMes;
  dma.qtdDias = dq2.iDia - dq1.iDia;

  if (dma.qtdDias < 0)
  {
    dma.qtdMeses--;

    if (dq2.iMes == 1)
    {
      int bissextoAnt = ((dq2.iAno - 1) % 400 == 0 || ((dq2.iAno - 1) % 4 == 0 && (dq2.iAno - 1) % 100 != 0));
      dma.qtdDias += bissextoAnt ? 29 : 31;
    }
    else
    {
      int mesAnt = dq2.iMes - 1;

      if (mesAnt == 2 && (dq2.iAno % 400 == 0 || (dq2.iAno % 4 == 0 && dq2.iAno % 100 != 0)))
        dma.qtdDias += 29;
      else
        dma.qtdDias += diasMes[mesAnt];
    }
  }

  if (dma.qtdMeses < 0)
  {
    dma.qtdAnos--;
    dma.qtdMeses += 12;
  }

  dma.retorno = 1;
  return dma;
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
   int qtdOcorrencias = 0;

  if (isCaseSensitive != 1)
  {
    c = tolower(c);

    for (int i = 0; texto[i] != '\0'; i++)
    {
      if (tolower(texto[i]) == c)
        qtdOcorrencias++;
    }
  }
  else
  {
    for (int i = 0; texto[i] != '\0'; i++)
    {
      if (texto[i] == c)
        qtdOcorrencias++;
    }
  }

  return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
  int qtdOcorrencias = 0;
  int tamTexto = strlen(strTexto);
  int tamBusca = strlen(strBusca);
  for (int i = 0; i <= tamTexto - tamBusca; i++)
  {
    int encontrou = 1;
    for (int j = 0; j < tamBusca; j++)
    {
      if (strTexto[i + j] != strBusca[j])
      {
        encontrou = 0;
        break;
      }
    }
    if (encontrou)
    {
      posicoes[2 * qtdOcorrencias] = i + 1;
      posicoes[2 * qtdOcorrencias + 1] = i + tamBusca;
      qtdOcorrencias++;
    }
  }
  return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
int numInvert = 0;
  int negativo = 0;
  if (num == 0)
    return 0;
  if (num < 0)
  {
    negativo = 1;
    num = -num;
  }
  while (num > 0)
  {
    int digito = num % 10;
    numInvert = numInvert * 10 + digito;
    num = num / 10;
  }
  if (negativo)
    numInvert = -numInvert;
  return numInvert;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
char base[20], busca[10];
  sprintf(base, "%d", numerobase);
  sprintf(busca, "%d", numerobusca);

  int qtdOcorrencias = 0;

  int tamBusca = strlen(busca);
  int tamBase = strlen(base);

  for (int i = 0; i <= tamBase - tamBusca; i++)
  {
    int j;
    for (j = 0; j < tamBusca; j++)
    {
      if (base[i + j] != busca[j])
        break;
    }
    if (j == tamBusca)
      qtdOcorrencias++;
  }

  return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

 int q7( char grade[8][10],
    char palavra[],
    int linhaInicial,
    int colunaInicial,
    int passoLinha,
    int passoColuna
) {
    int tamanhoPalavra = strlen(palavra);

    for (int i = 0; i < tamanhoPalavra; i++) {
        int linhaAtual = linhaInicial + i * passoLinha;
        int colunaAtual = colunaInicial + i * passoColuna;

        if (linhaAtual < 0 || linhaAtual >= 8 ||
            colunaAtual < 0 || colunaAtual >= 10)
            return 0;

        if (grade[linhaAtual][colunaAtual] != palavra[i])
            return 0;
    }

    return 1;
}

int procurarPalavra(char grade[8][10], char palavra[]) {

    int direcoesLinha[8]  = { 0,  0,  1, -1,  1,  1, -1, -1 };
    int direcoesColuna[8] = { 1, -1,  0,  0,  1, -1,  1, -1 };

    for (int linha = 0; linha < 8; linha++) {
        for (int coluna = 0; coluna < 10; coluna++) {

            if (grade[linha][coluna] == palavra[0]) {

                for (int d = 0; d < 8; d++) {
                    int passoLinha = direcoesLinha[d];
                    int passoColuna = direcoesColuna[d];

                    if (verificarDirecao(grade, palavra, linha, coluna, passoLinha, passoColuna))
                        return 1;
                }
            }
        }
    }

    return 0;
}

int main() {
    char grade[8][10];
    char palavra[100];

    for (int linha = 0; linha < 8; linha++)
        scanf("%s", grade[linha]);

    scanf("%s", palavra);

    printf("%d\n", procurarPalavra(grade, palavra));

    return 0;
}



DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}

