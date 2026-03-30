#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/ioctl.h>
#include <locale.h>
using namespace std;

void gotoxy(int x, int y) {
    // ANSI: linha e coluna começam em 1
    printf("\033[%d;%dH", y + 1, x + 1);
    fflush(stdout);
}

int getTerminalWidth() {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0 && w.ws_col > 0)
        return w.ws_col;
    return 80; // fallback
}

void hideCursor() { printf("\033[?25l"); fflush(stdout); }
void showCursor() { printf("\033[?25h"); fflush(stdout); }
void clearScreen() { printf("\033[2J");  fflush(stdout); }

int main() {
    setlocale(LC_ALL, "");

    // Lê mensagem ANTES de esconder cursor e limpar tela
    printf("Digite uma mensagem: ");
    fflush(stdout);

    string msg;
    getline(cin, msg);

    hideCursor();
    clearScreen();

    int cols   = getTerminalWidth();
    int startX = (cols - (int)msg.size()) / 2;
    if (startX < 0) startX = 0;

    int startLinha = 5;
    int fimLinha   = 20;

    // Exibe mensagem completa centralizada na linha 5
    gotoxy(startX, startLinha);
    printf("%s", msg.c_str());
    fflush(stdout);
    usleep(600000); // 600ms de pausa inicial

    // Cada letra "cai" da linha 5 até a linha 20
    for (int i = 0; i < (int)msg.size(); i++) {
        int charX = startX + i;

        for (int linha = startLinha + 1; linha <= fimLinha; linha++) {
            // Apaga na linha anterior
            gotoxy(charX, linha - 1);
            printf(" ");
            fflush(stdout);

            // Desenha na linha atual
            gotoxy(charX, linha);
            printf("%c", msg[i]);
            fflush(stdout);

            usleep(40000); // 40ms por linha
        }
        usleep(30000); // 30ms entre letras
    }

    // Restaura cursor e vai para baixo da animação
    showCursor();
    gotoxy(0, fimLinha + 2);
    printf("\n");
    fflush(stdout);

    return 0;
}
