//Faça um programa que leia a idade de duas pessoas e imprima a soma das idades
#include <stdio.h>
#include <string.h>

int main(void){
	int i1, i2;
	
	scanf("%d", &i1);
	scanf("%d", &i2);
	
	int i3 = i1+i2;
	
	printf("%d", i3);
	return 0;
}
