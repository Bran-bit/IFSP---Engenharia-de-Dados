#include <iostream>
#include <fstream>
#include <locale.h>
#include <cctype>
using namespace std;

int main(int argc, char** argv) {
    setlocale(LC_ALL, "");

    ifstream arq("nomes.txt");
    if (arq.is_open()) {
        string linha;
        while (!arq.eof()) {
            getline(arq, linha);
            if (linha.empty()) continue;

            // Acha o primeiro e último espaço com iteradores
            string::iterator primIt = linha.end();
            string::iterator ultIt  = linha.begin();

            for (string::iterator it = linha.begin(); it < linha.end(); it++) {
                if (*it == ' ') {
                    if (primIt == linha.end()) primIt = it; // primeiro espaço
                    ultIt = it;                             // último espaço
                }
            }

            // Primeiro nome = início até o primeiro espaço
            string primNome = "";
            for (string::iterator it = linha.begin(); it < primIt; it++)
                primNome += *it;

            // Sobrenome = depois do último espaço até o fim
            string sobrenome = "";
            for (string::iterator it = ultIt + 1; it < linha.end(); it++)
                sobrenome += *it;

            // Nomes do meio = entre primeiro e último espaço
            // Abrevia pegando a 1ª letra após cada espaço
            string abreviaturas = "";
            for (string::iterator it = primIt; it < ultIt; it++) {
                if (*it == ' ' && (it + 1) < ultIt) {
                    abreviaturas += " ";
                    abreviaturas += toupper(*(it + 1));
                    abreviaturas += ".";
                }
            }

            // Sobrenome em maiúsculas
            string sobrenomeMaius = "";
            for (char c : sobrenome)
                sobrenomeMaius += toupper(c);

            cout << sobrenomeMaius << ", " << primNome << abreviaturas << endl;
        }
        arq.close();
    } else {
        cout << "Erro ao abrir o arquivo" << endl;
    }

    return 0;
}
