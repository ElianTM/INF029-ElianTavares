#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

typedef struct {
    int *data;
    int count;
    int capacity;
} ElementoAux;

ElementoAux estrutura[TAM];

int is_valid_index(int pos) {
    return (pos >= 1 && pos <= TAM);
}

int has_aux_structure(int idx) {
    return (estrutura[idx].data != NULL);
}

int is_full(int idx) {
    return (estrutura[idx].count >= estrutura[idx].capacity);
}

int find_value_index(int idx, int val) {
    for (int k = 0; k < estrutura[idx].count; k++) {
        if (estrutura[idx].data[k] == val) {
            return k;
        }
    }
    return -1;
}

int total_elements() {
    int total = 0;
    for (int k = 0; k < TAM; k++) {
        total += estrutura[k].count;
    }
    return total;
}

void sort_array(int arr[], int len) {
    int k, l, key;
    for (k = 1; k < len; k++) {
        key = arr[k];
        l = k - 1;
        while (l >= 0 && arr[l] > key) {
            arr[l + 1] = arr[l];
            l--;
        }
        arr[l + 1] = key;
    }
}

int criarEstruturaAuxiliar(int posicao, int tamanho) {
    if (!is_valid_index(posicao)) 
        return POSICAO_INVALIDA;
        
    int idx = posicao - 1;

    if (has_aux_structure(idx)) 
        return JA_TEM_ESTRUTURA_AUXILIAR;
        
    if (tamanho < 1) 
        return TAMANHO_INVALIDO;

    int *ptr = (int*) malloc(tamanho * sizeof(int));
    if (!ptr) 
        return SEM_ESPACO_DE_MEMORIA;

    estrutura[idx].data = ptr;
    estrutura[idx].count = 0;
    estrutura[idx].capacity = tamanho;

    return SUCESSO;
}

int inserirNumeroEmEstrutura(int posicao, int valor) {
    if (!is_valid_index(posicao)) 
        return POSICAO_INVALIDA;

    int idx = posicao - 1;

    if (!has_aux_structure(idx)) 
        return SEM_ESTRUTURA_AUXILIAR;
    
    if (is_full(idx)) 
        return SEM_ESPACO;

    estrutura[idx].data[estrutura[idx].count] = valor;
    estrutura[idx].count++;

    return SUCESSO;
}

int excluirNumeroDoFinaldaEstrutura(int posicao) {
    if (!is_valid_index(posicao)) 
        return POSICAO_INVALIDA;

    int idx = posicao - 1;

    if (!has_aux_structure(idx)) 
        return SEM_ESTRUTURA_AUXILIAR;

    if (estrutura[idx].count == 0) 
        return ESTRUTURA_AUXILIAR_VAZIA;

    estrutura[idx].count--;
    return SUCESSO;
}

int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
    if (!is_valid_index(posicao)) 
        return POSICAO_INVALIDA;

    int idx = posicao - 1;

    if (!has_aux_structure(idx)) 
        return SEM_ESTRUTURA_AUXILIAR;

    if (estrutura[idx].count == 0) 
        return ESTRUTURA_AUXILIAR_VAZIA;

    int found_idx = find_value_index(idx, valor);
    
    if (found_idx == -1) 
        return NUMERO_INEXISTENTE;

    for (int k = found_idx; k < estrutura[idx].count - 1; k++) {
        estrutura[idx].data[k] = estrutura[idx].data[k + 1];
    }
    
    estrutura[idx].count--;
    return SUCESSO;
}

int ehPosicaoValida(int posicao) {
    return is_valid_index(posicao) ? SUCESSO : POSICAO_INVALIDA;
}

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    if (!is_valid_index(posicao)) 
        return POSICAO_INVALIDA;

    int idx = posicao - 1;

    if (!has_aux_structure(idx)) 
        return SEM_ESTRUTURA_AUXILIAR;

    for (int k = 0; k < estrutura[idx].count; k++) {
        vetorAux[k] = estrutura[idx].data[k];
    }

    return SUCESSO;
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    int status = getDadosEstruturaAuxiliar(posicao, vetorAux);
    
    if (status == SUCESSO) {
        sort_array(vetorAux, estrutura[posicao - 1].count);
    }
    
    return status;
}

int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int iterator = 0;
    int has_content = 0;

    for (int k = 0; k < TAM; k++) {
        if (has_aux_structure(k) && estrutura[k].count > 0) {
            has_content = 1;
            for (int l = 0; l < estrutura[k].count; l++) {
                vetorAux[iterator++] = estrutura[k].data[l];
            }
        }
    }

    return has_content ? SUCESSO : TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
}

int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int status = getDadosDeTodasEstruturasAuxiliares(vetorAux);
    
    if (status == SUCESSO) {
        sort_array(vetorAux, total_elements());
    }
    
    return status;
}

int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {
    if (!is_valid_index(posicao)) 
        return POSICAO_INVALIDA;

    int idx = posicao - 1;

    if (!has_aux_structure(idx)) 
        return SEM_ESTRUTURA_AUXILIAR;

    int final_size = estrutura[idx].capacity + novoTamanho;

    if (final_size < 1) 
        return NOVO_TAMANHO_INVALIDO;

    int *new_ptr = realloc(estrutura[idx].data, final_size * sizeof(int));
    
    if (!new_ptr) 
        return SEM_ESPACO_DE_MEMORIA;

    estrutura[idx].data = new_ptr;
    estrutura[idx].capacity = final_size;

    if (estrutura[idx].capacity < estrutura[idx].count) {
        estrutura[idx].count = estrutura[idx].capacity;
    }

    return SUCESSO;
}

int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
    if (!is_valid_index(posicao)) 
        return POSICAO_INVALIDA;

    int idx = posicao - 1;

    if (!has_aux_structure(idx)) 
        return SEM_ESTRUTURA_AUXILIAR;

    if (estrutura[idx].count == 0) 
        return ESTRUTURA_AUXILIAR_VAZIA;

    return estrutura[idx].count;
}

void append_node(No *head, int val) {
    No *new_node = (No*) malloc(sizeof(No));
    new_node->conteudo = val;
    new_node->prox = NULL;

    No *current = head;
    while (current->prox != NULL) {
        current = current->prox;
    }
    current->prox = new_node;
}

No *montarListaEncadeadaComCabecote() {
    int qtd_total = total_elements();
    
    if (qtd_total == 0) return NULL; 

    No *head = (No*) malloc(sizeof(No));
    head->prox = NULL; 

    int *temp_buffer = (int*) malloc(qtd_total * sizeof(int));
    
    if (getDadosDeTodasEstruturasAuxiliares(temp_buffer) == SUCESSO) {
        for (int k = 0; k < qtd_total; k++) {
            append_node(head, temp_buffer[k]);
        }
        free(temp_buffer);
        return head;
    }

    free(temp_buffer);
    free(head);
    return NULL;
}

void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {
    No *current = inicio->prox;
    int k = 0;
    while (current != NULL) {
        vetorAux[k++] = current->conteudo;
        current = current->prox;
    }
}

void destruirListaEncadeadaComCabecote(No **inicio) {
    No *current = *inicio;
    No *next_node;

    while (current != NULL) {
        next_node = current->prox;
        free(current);
        current = next_node;
    }
    *inicio = NULL;
}

void inicializar() {
    for (int k = 0; k < TAM; k++) {
        estrutura[k].data = NULL;
        estrutura[k].count = 0;
        estrutura[k].capacity = 0;
    }
}

void finalizar() {
    for (int k = 0; k < TAM; k++) {
        if (estrutura[k].data != NULL) {
            free(estrutura[k].data);
            estrutura[k].data = NULL;
        }
    }
}
