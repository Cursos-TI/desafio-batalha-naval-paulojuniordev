#include <stdio.h>
#include <stdbool.h>

// Definições do jogo
#define TAMANHO_TABULEIRO 10  // Tamanho do tabuleiro (10x10)
#define TAMANHO_NAVIO 3       // Tamanho fixo dos navios
#define AGUA 0                // Representa água no tabuleiro
#define NAVIO 3               // Representa parte de um navio no tabuleiro

// Estrutura para representar um navio
typedef struct {
    int linha_inicio;    // Linha inicial do navio
    int coluna_inicio;   // Coluna inicial do navio
    bool horizontal;     // true para horizontal, false para vertical
} Navio;

// Declaração do tabuleiro e dos navios
int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
Navio navios[2];  // Dois navios: um horizontal, um vertical

// Protótipos das funções
void inicializar_tabuleiro();
bool validar_posicionamento(int linha_inicio, int coluna_inicio, bool horizontal);
bool verificar_sobreposicao(int linha_inicio, int coluna_inicio, bool horizontal);
void posicionar_navio(int navio_idx);
void exibir_tabuleiro();

int main() {
    // Inicializa o tabuleiro com água (0)
    inicializar_tabuleiro();

    // Define coordenadas iniciais dos navios (fixas, conforme especificação)
    navios[0].linha_inicio = 2;    // Navio 1: horizontal, começa em (2,3)
    navios[0].coluna_inicio = 3;
    navios[0].horizontal = true;

    navios[1].linha_inicio = 5;    // Navio 2: vertical, começa em (5,7)
    navios[1].coluna_inicio = 7;
    navios[1].horizontal = false;

    // Posiciona os navios com validação
    for (int i = 0; i < 2; i++) {
        if (!validar_posicionamento(navios[i].linha_inicio, navios[i].coluna_inicio, navios[i].horizontal)) {
            printf("Erro: Posicionamento inválido para o navio %d.\n", i + 1);
            return 1;
        }
        if (!verificar_sobreposicao(navios[i].linha_inicio, navios[i].coluna_inicio, navios[i].horizontal)) {
            printf("Erro: Sobreposição detectada para o navio %d.\n", i + 1);
            return 1;
        }
        posicionar_navio(i);
    }

    // Exibe o tabuleiro com os navios posicionados
    printf("Tabuleiro com navios posicionados:\n");
    exibir_tabuleiro();

    return 0;
}

// Inicializa o tabuleiro com água (0)
void inicializar_tabuleiro() {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;  // Todas as posições começam como água
        }
    }
}

// Valida se o posicionamento do navio está dentro dos limites do tabuleiro
bool validar_posicionamento(int linha_inicio, int coluna_inicio, bool horizontal) {
    if (linha_inicio < 0 || linha_inicio >= TAMANHO_TABULEIRO || coluna_inicio < 0 || coluna_inicio >= TAMANHO_TABULEIRO) {
        return false;  // Coordenadas iniciais fora do tabuleiro
    }
    if (horizontal) {
        if (coluna_inicio + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            return false;  // Navio horizontal ultrapassa o limite
        }
    } else {
        if (linha_inicio + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            return false;  // Navio vertical ultrapassa o limite
        }
    }
    return true;
}

// Verifica se o navio se sobrepõe a outro navio já posicionado
bool verificar_sobreposicao(int linha_inicio, int coluna_inicio, bool horizontal) {
    if (horizontal) {
        for (int j = coluna_inicio; j < coluna_inicio + TAMANHO_NAVIO; j++) {
            if (tabuleiro[linha_inicio][j] == NAVIO) {
                return false;  // Sobreposição detectada
            }
        }
    } else {
        for (int i = linha_inicio; i < linha_inicio + TAMANHO_NAVIO; i++) {
            if (tabuleiro[i][coluna_inicio] == NAVIO) {
                return false;  // Sobreposição detectada
            }
        }
    }
    return true;
}

// Posiciona o navio no tabuleiro
void posicionar_navio(int navio_idx) {
    int linha = navios[navio_idx].linha_inicio;
    int coluna = navios[navio_idx].coluna_inicio;
    bool horizontal = navios[navio_idx].horizontal;

    if (horizontal) {
        for (int j = coluna; j < coluna + TAMANHO_NAVIO; j++) {
            tabuleiro[linha][j] = NAVIO;  // Coloca navio (3) na posição
        }
    } else {
        for (int i = linha; i < linha + TAMANHO_NAVIO; i++) {
            tabuleiro[i][coluna] = NAVIO;  // Coloca navio (3) na posição
        }
    }
}

// Exibe o tabuleiro no console
void exibir_tabuleiro() {
    // Imprime números das colunas
    printf("  ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    // Imprime linhas do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);  // Imprime número da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);  // Imprime valor da célula (0 ou 3)
        }
        printf("\n");
    }
}