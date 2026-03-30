#include <iostream>
#include <fstream>
#include <locale.h>
using namespace std;

int main(int argc, char** argv) {
    setlocale(LC_ALL, "");

    ifstream arq("nomes.txt");
    if (arq.is_open()) {
        string linha;
        while (!arq.eof()) {
            getline(arq, linha);
            if (linha.empty()) continue;

            // Acha o último espaço percorrendo do fim para o início
            string::iterator ultIt = linha.begin();
            for (string::iterator it = linha.begin(); it < linha.end(); it++) {
                if (*it == ' ') ultIt = it;
            }

            // Sobrenome = do último espaço até o fim
            string sobrenome = "";
            for (string::iterator it = ultIt + 1; it < linha.end(); it++)
                sobrenome += *it;

            // Resto = do início até o último espaço
            string resto = "";
            for (string::iterator it = linha.begin(); it < ultIt; it++)
                resto += *it;

            cout << sobrenome << ", " << resto << endl;
        }
        arq.close();
    } else {
        cout << "Erro ao abrir o arquivo" << endl;
    }

    return 0;
}
