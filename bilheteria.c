#include <stdio.h>
#include <locale.h>

#define FILEIRAS 15
#define POLTRONAS 40

int main() {

    int teatro[FILEIRAS][POLTRONAS] = {0};
    int opcao, f, p;
    int ocupados = 0;
    float faturamento = 0.0;

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("0. Finalizar\n1. Reservar poltrona\n2. Mapa de ocupação\n3. Faturamento\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                // Loop de validação para a FILEIRA
                do {
                    printf("Informe a fileira (1 a %d): ", FILEIRAS);
                    scanf("%d", &f);
                    if (f < 1 || f > FILEIRAS)
                        printf("Entrada inválida! Digite um valor entre 1 e %d.\n", FILEIRAS);
                } while (f < 1 || f > FILEIRAS);

                // Loop de validação para a POLTRONA
                do {
                    printf("Informe a poltrona (1 a %d): ", POLTRONAS);
                    scanf("%d", &p);
                    if (p < 1 || p > POLTRONAS)
                        printf("Entrada inválida! Digite um valor entre 1 e %d.\n", POLTRONAS);
                } while (p < 1 || p > POLTRONAS);

                // Verificação de ocupação
                if (teatro[f-1][p-1] == 1) {
                    printf("\n[AVISO] O lugar F%d-P%d já está ocupado!\n", f, p);
                } else {
                    teatro[f-1][p-1] = 1;
                    ocupados++;

                    // Regra de preços por fileira
                    if (f <= 5) faturamento += 50.0;
                    else if (f <= 10) faturamento += 30.0;
                    else faturamento += 15.0;

                    printf("\n[SUCESSO] Reserva efetuada com sucesso!\n");
                }
                break;

            case 2:
                printf("\n--- MAPA DE OCUPAÇÃO ---\n");
                for (int i = 0; i < FILEIRAS; i++) {
                    printf("F%02d: ", i + 1);
                    for (int j = 0; j < POLTRONAS; j++) {
                        printf("%c ", (teatro[i][j] == 0) ? '.' : '#');
                    }
                    printf("\n");
                }
                printf("Legenda: . (Vago) | # (Ocupado)\n");
                break;

            case 3:
                printf("\n-------------------------------\n");
                printf("Qtde de lugares ocupados: \t%d\n", ocupados);
                printf("Valor da bilheteria:      \tR$ %.2f\n", faturamento);
                printf("-------------------------------\n");
                break;

            case 0:
                printf("Encerrando o sistema...\n");
                break;

            default:
                printf("Opção de menu inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}