//Faça um programa que imprima o seu nome, sua matrícula, e o seu semestre de ingresso no curso. Cada informação em uma linha.
#include <stdio.h>
#include <string.h>

int main(void){
	char informacao[] = "Elian 20251160018 2025.1";
	int i;
	int tamanho = strlen(informacao);
	
	for(i=0;i<tamanho;i++){
		if(informacao[i]== 32 ){
			printf("\n");
		} else {
		printf("%c", informacao[i]);}
		
	}
	return 0;
}

