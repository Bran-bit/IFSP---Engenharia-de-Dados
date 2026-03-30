#include <iostream>
#include <locale.h>
#include <string>
#include <cctype>
using namespace std;

int main() {
    setlocale(LC_ALL, "");

    string msg;
    cout << "Digite uma mensagem: ";
    getline(cin, msg);

    string limpa = "";
    for (char c : msg) {
        if (c != ' ')
            limpa += toupper(c);
    }

    bool palindromo = true;
    int n = limpa.size();
    for (int i = 0; i < n / 2; i++) {
        if (limpa[i] != limpa[n - 1 - i]) {
            palindromo = false;
            break;
        }
    }

    if (palindromo)
        cout << "\"" << msg << "\" é um palíndromo." << endl;
    else
        cout << "\"" << msg << "\" não é um palíndromo." << endl;

    return 0;
}
