#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string invertir(const string &s) {
    string r = "";
    for (int i = s.length() - 1; i >= 0; i--) r += s[i];
    return r;
}

int main() {
    ifstream fin;
    ofstream fout;
    string entrada, salida, data = "", binario = "";

    cout << "Archivo de entrada: " << endl;
    cin >> entrada;
    cout << "Archivo de salida: " << endl;
    cin >> salida;

    fin.open(entrada);
    if (!fin.is_open()) {
        cout << "Error: no se pudo abrir el archivo de entrada." << endl;
        return 1;
    }

    char c;
    while (fin.get(c)) data += c;
    fin.close();

    for (int i = 0; i < (int)data.length(); i++) {
        int val = (unsigned char)data[i];
        string bin = "";
        for (int j = 0; j < 8; j++) {
            bin += (val % 2) ? '1' : '0';
            val /= 2;
        }
        binario += invertir(bin);
    }

    int semilla, caso;
    cout << "Ingrese semilla de codificacion: ";
    cin >> semilla;
    cout << "Seleccione metodo de codificacion (1 o 2): ";
    cin >> caso;

    if (caso == 1) {
        string array2 = binario;
        long int n = array2.length();
        int u = 0, contador = 0;

        while (contador < semilla && u < n) {
            array2[u] = (array2[u] == '1') ? '0' : '1';
            u++; contador++;
        }

        int x = 0, unos = 0, ceros = 0, aux = 0;
        for (int j = 0; j < n; j++) {
            if (x == semilla) {
                x = 0;
                if (aux > 0) {
                    if (unos == ceros) {
                        contador = 0;
                        while (contador < semilla && u < n) {
                            array2[u] = (array2[u] == '1') ? '0' : '1';
                            u++; contador++;
                        }
                    } else if (unos > ceros) {
                        int y = 0; contador = 0;
                        while (contador < semilla && u < n) {
                            if (y == 2) {
                                array2[u] = (array2[u] == '1') ? '0' : '1';
                                y = 0;
                            } else y++;
                            u++; contador++;
                        }
                    } else {
                        int z = 0; contador = 0;
                        while (contador < semilla && u < n) {
                            if (z == 1) {
                                array2[u] = (array2[u] == '1') ? '0' : '1';
                                z = 0;
                            } else z++;
                            u++; contador++;
                        }
                    }
                }
                unos = 0; ceros = 0;
            }
            if (binario[j] == '1') unos++;
            else ceros++;
            aux++; x++;
        }
        fout.open(salida);
        fout << array2;
        fout.close();
        cout << "Mensaje codificado en el archivo " << salida << endl;
    }
    else if (caso == 2) {
        string array3 = "";
        int y = 0;
        fout.open(salida);

        for (int j = 0; j < (int)binario.length(); j++) {
            if (y == semilla) {
                y = 0;
                char au = array3[semilla - 1];
                for (int k = semilla - 1; k > 0; k--) {
                    array3[k] = array3[k - 1];
                }
                array3[0] = au;
                for (int num = 0; num < semilla; num++) fout << array3[num];
            }
            if (y < (int)array3.size())
                array3[y] = binario[j];
            else
                array3 += binario[j];
            y++;
        }

        if (array3.size() > 0) {
            char au = array3[semilla - 1];
            for (int k = semilla - 1; k > 0; k--) array3[k] = array3[k - 1];
            array3[0] = au;
            for (int num = 0; num < (int)array3.size(); num++) fout << array3[num];
        }

        fout.close();
        cout << "Mensaje codificado en el archivo " << salida << endl;
    }

    else {
        cout << "Error en codificacion." << endl;
    }

    return 0;
}
