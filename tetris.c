#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>

#define TAM_FILA 5   // Tamanho máximo da fila de peças

// -------------------------------------------------------------------
// STRUCT — Representa cada peça do Tetris Stack
// -------------------------------------------------------------------
typedef struct {
    char nome;  // Tipo da peça: I, O, T, L
    int id;     // Identificador único
} Peca;


// -------------------------------------------------------------------
// VARIÁVEIS DA FILA CIRCULAR
// -------------------------------------------------------------------
Peca fila[TAM_FILA];
int inicio = 0;        // Posição da primeira peça
int fim = 0;           // Próxima posição disponível
int quantidade = 0;    // Número de peças na fila
int geradorID = 0;     // Contador global para IDs automáticos


// -------------------------------------------------------------------
// Função que gera automaticamente uma nova peça
// -------------------------------------------------------------------
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;

    nova.nome = tipos[rand() % 4]; // Escolhe tipo aleatório
    nova.id = geradorID++;         // ID sequencial

    return nova;
}


// -------------------------------------------------------------------
// ENQUEUE — Insere nova peça ao final da fila
// -------------------------------------------------------------------
void enqueue() {
    if (quantidade == TAM_FILA) {
        printf("\n⚠️  A fila está cheia! Não é possível adicionar nova peça.\n");
        return;
    }

    Peca nova = gerarPeca();
    fila[fim] = nova;

    fim = (fim + 1) % TAM_FILA;  // Avança circularmente
    quantidade++;

    printf("\n✅ Peça inserida: [%c %d]\n", nova.nome, nova.id);
}


// -------------------------------------------------------------------
// DEQUEUE — Remove a peça da frente da fila
// -------------------------------------------------------------------
void dequeue() {
    if (quantidade == 0) {
        printf("\n⚠️  A fila está vazia! Não há peça para jogar.\n");
        return;
    }

    Peca jogada = fila[inicio];

    inicio = (inicio + 1) % TAM_FILA;  // Avança circularmente
    quantidade--;

    printf("\n🎮 Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
}


// -------------------------------------------------------------------
// Exibe o conteúdo atual da fila
// -------------------------------------------------------------------
void mostrarFila() {
    printf("\n📌 Fila de Peças Futuras:\n");

    if (quantidade == 0) {
        printf("[VAZIA]\n");
        return;
    }

    int pos = inicio;

    for (int i = 0; i < quantidade; i++) {
        printf("[%c %d] ", fila[pos].nome, fila[pos].id);
        pos = (pos + 1) % TAM_FILA;
    }

    printf("\n");
}


// -------------------------------------------------------------------
// Preenche a fila inicialmente com 5 peças
// -------------------------------------------------------------------
void inicializarFila() {
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue();
    }
}


// -------------------------------------------------------------------
// PROGRAMA PRINCIPAL
// -------------------------------------------------------------------
int main() {
    int opcao;

    srand(10); // Semente fixa para testes consistentes

    printf("=== 🎮 TETRIS STACK — NIVEL NOVATO 🎮 ===\n");

    inicializarFila();

    do {
        mostrarFila();

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue();
                break;
            case 2:
                enqueue();
                break;
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\n❌ Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
} 

