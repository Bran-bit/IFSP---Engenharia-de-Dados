#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_BARALHOS        2
#define CARTAS_POR_BARALHO  52
#define NUM_NAIPES          4
#define CARTAS_POR_NAIPE    13
#define NUM_JOGADORES       4
#define CARTAS_NA_MAO       11
#define TOTAL_CARTAS        (NUM_BARALHOS * CARTAS_POR_BARALHO)  /* 104 */

/* Tamanho do código de uma carta: 4 caracteres + '\0' */
#define TAM_CODIGO  5

#define LARGURA_VALOR   6   
#define LARGURA_NAIPE   6  


static const char *NAIPES[] = { "", "Copas", "Paus", "Ouro", "Espada" };
static const char *VALORES[] = {
    "", "As", "2", "3", "4", "5", "6",
    "7", "8", "9", "10", "Valete", "Dama", "Rei"
};


typedef char Carta[TAM_CODIGO];
typedef Carta Baralho[CARTAS_POR_BARALHO];
typedef Carta Mao[CARTAS_NA_MAO];


void inicializar_baralhos(Baralho baralho[NUM_BARALHOS])
{
    for (int numero_baralho = 0; numero_baralho < NUM_BARALHOS; numero_baralho++) {
        int posicao = 0;
        for (int naipe = 1; naipe <= NUM_NAIPES; naipe++) {
            for (int numero = 1; numero <= CARTAS_POR_NAIPE; numero++) {
                snprintf(baralho[numero_baralho][posicao], TAM_CODIGO,
                         "%d%02d%d", naipe, numero, numero_baralho + 1);
                posicao++;
            }
        }
    }
}


int inteiro_aleatorio_ate(int limite)
{
    return rand() % limite;
}


// Troca o conteudo de duas cartas na memoria.
void trocar_cartas(Carta carta_a, Carta carta_b)
{
    Carta carta_temporaria;
    strcpy(carta_temporaria, carta_a);
    strcpy(carta_a,          carta_b);
    strcpy(carta_b,          carta_temporaria);
}



void embaralhar(Baralho baralho)
{
    for (int posicao_atual = CARTAS_POR_BARALHO - 1; posicao_atual > 0; posicao_atual--) {
        int posicao_aleatoria = inteiro_aleatorio_ate(posicao_atual + 1);
        trocar_cartas(baralho[posicao_atual], baralho[posicao_aleatoria]);
    }
}


/*
 * Une os dois baralhos embaralhados num unico monte e distribui
 * em rodadas: cada jogador recebe uma carta por vez.
 */
void distribuir(Baralho baralho[NUM_BARALHOS], Mao mao[NUM_JOGADORES])
{
    Carta monte[TOTAL_CARTAS];

    // Copia baralho 0 nas posicoes 0..51 e baralho 1 nas posicoes 52..103
    for (int numero_baralho = 0; numero_baralho < NUM_BARALHOS; numero_baralho++) {
        int offset = numero_baralho * CARTAS_POR_BARALHO;
        for (int carta = 0; carta < CARTAS_POR_BARALHO; carta++) {
            strcpy(monte[offset + carta], baralho[numero_baralho][carta]);
        }
    }

    int topo_do_monte = 0;
    for (int rodada = 0; rodada < CARTAS_NA_MAO; rodada++) {
        for (int jogador = 0; jogador < NUM_JOGADORES; jogador++) {
            strcpy(mao[jogador][rodada], monte[topo_do_monte]);
            topo_do_monte++;
        }
    }
}


/*
 * Converte o codigo de uma carta em texto legivel com largura fixa,
 * para que as colunas fiquem alinhadas independente do valor/naipe.
 *
 * Exemplo de saida: "Valete de Espada (baralho 2)"
 */
void descrever_carta(const char *codigo, char *saida, int tam_saida)
{

    int naipe   = codigo[0] - '0';
    int dezena  = codigo[1] - '0';
    int unidade = codigo[2] - '0';
    int numero  = dezena * 10 + unidade;
    int deck    = codigo[3] - '0';

    /* %-*s alinha a esquerda dentro de uma largura fixa (LARGURA_*),
       garantindo que "2 de Paus" e "Valete de Espada" ocupem o mesmo
       espaco horizontal na tela. */
    snprintf(saida, tam_saida,
             "%-*s de %-*s (baralho %d)",
             LARGURA_VALOR, VALORES[numero],
             LARGURA_NAIPE, NAIPES[naipe],
             deck);
}


/*
 * Exibe as maos dos jogadores dentro de uma moldura de texto.
 */

#define LARGURA_DESCRICAO  28
#define LARGURA_MOLDURA    (11 + LARGURA_DESCRICAO + 3)   /* = 42 */

/* Linha horizontal com N repeticoes de um caractere de borda */
#define SEPARADOR "========================================"

void exibir_maos(Mao mao[NUM_JOGADORES])
{
    char descricao[64];

    for (int jogador = 0; jogador < NUM_JOGADORES; jogador++) {

        /* Topo e fundo usam exatamente LARGURA_MOLDURA-2 caracteres internos */
        printf("+%.*s+\n", LARGURA_MOLDURA - 2, SEPARADOR);

        /*
         * Cabecalho: "|  Jogador N  " ocupa 14 colunas.
         * O padding preenche o restante ate a borda direita.
         * LARGURA_MOLDURA - 14 - 1 = colunas de espaco antes do "|" final.
         */
        printf("|  Jogador %d  %*s|\n",
               jogador + 1,
               LARGURA_MOLDURA - 15, "");

        printf("+%.*s+\n", LARGURA_MOLDURA - 2, SEPARADOR);

        for (int carta = 0; carta < CARTAS_NA_MAO; carta++) {
            descrever_carta(mao[jogador][carta], descricao, sizeof(descricao));

            /*
             * Prefixo fixo "|  [NCCB]  " ocupa 10 colunas.
             * Descricao ocupa LARGURA_DESCRICAO colunas (alinhada a esquerda).
             * Sufixo "  |" fecha a moldura.
             */
            printf("|  [%s]  %-*s  |\n",
                   mao[jogador][carta],
                   LARGURA_DESCRICAO, descricao);
        }

        printf("+%.*s+\n\n", LARGURA_MOLDURA - 2, SEPARADOR);
    }
}

int main(void)
{
    srand(time(0));

    Baralho baralho[NUM_BARALHOS];
    Mao     mao[NUM_JOGADORES];

    inicializar_baralhos(baralho);

    for (int numero_baralho = 0; numero_baralho < NUM_BARALHOS; numero_baralho++) {
        embaralhar(baralho[numero_baralho]);
    }

    distribuir(baralho, mao);

    printf("\n=== BURACO: distribuicao inicial ===\n\n");
    exibir_maos(mao);

    return 0;
}
