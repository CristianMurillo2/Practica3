#include "codificaciones.h"

void aplicarReglasInv(string &grupo, string &grupoAnterior){
    int unosAnterior = 0, cerosAnterior = 0;

    for(char bit : grupoAnterior){
        if (bit == '1'){
            unosAnterior++;
        } else{
            cerosAnterior++;
        }
    }

    if(unosAnterior == cerosAnterior){
        for (char &bit : grupo){
            bit = (bit == '1') ? '0' : '1';
        }
    } else if(unosAnterior > cerosAnterior){
        int tamaño= grupo.length();
        for (int i = 2; i < tamaño; i += 3){
            grupo[i] = (grupo[i] == '1') ? '0' : '1';
        }
    } else{
        int tamaño= grupo.length();
        for (int i = 1; i < tamaño; i += 2){
            grupo[i] = (grupo[i] == '1') ? '0' : '1';
        }
    }
}

void decodificarM1(string &cadena, int n){
    int longitud = cadena.length();
    string resultado = "";

    string primerBloque = cadena.substr(0, n);
    for(char &bit : primerBloque){
        bit = (bit == '1') ? '0' : '1';
    }

    resultado += primerBloque;
    string grupoAnterior = primerBloque;

    for(int i = n; i < longitud; i += n){
        string grupo = cadena.substr(i, n);
        aplicarReglasInv(grupo, grupoAnterior);
        resultado += grupo;
        grupoAnterior = grupo;
    }
    cadena = resultado;
}

string decodificarM2(string cadena, int n){
    int longitud = cadena.length();
    string resultado = "";

    for (int i = 0; i < longitud; i += n){
        string grupo = cadena.substr(i, n);
        char primerBit = grupo[0];

        for (int j = 1; j < n; j++){
            grupo[j - 1] = grupo[j];
        }
        grupo[n - 1] = primerBit;

        resultado += grupo;
    }
    return resultado;
}

string convBinInt(string linea){
    string recibido = "";
    int len = linea.length();
    int residuo = len % 8;
    for(int i = 0; i < (len - residuo); i += 8){
        string sublinea = linea.substr(i, 8);
        int entero = 0;
        for(int j = 0; j < 8; j++){
            int aux = sublinea[j] - 48;
            aux = (pow(2, (7 - j))) * aux;
            entero += aux;
        }
        recibido += char(entero);
    }
    return recibido;
}

void convIntBin(char *linea, int ent){
    for (int i = 7; i >= 0; i--) {
        linea[i] = (ent % 2) + '0';
        ent = ent / 2;
    }
    linea[8] = '\0';
}

void aplicarReglas(string &grupo, string &grupoAnterior){
    int unosAnterior = 0, cerosAnterior = 0;

    for (char bit : grupoAnterior){
        if (bit == '1'){
            unosAnterior++;
        } else{
            cerosAnterior++;
        }
    }

    if(unosAnterior == cerosAnterior){
        for(char &bit : grupo){
            bit = (bit == '1') ? '0' : '1';
        }
    } else if(unosAnterior > cerosAnterior){
        int tamaño= grupo.length();
        for(int i = 2; i < tamaño; i += 3){
            grupo[i] = (grupo[i] == '1') ? '0' : '1';
        }
    } else{
        int tamaño= grupo.length();
        for (int i = 1; i < tamaño; i += 2){
            grupo[i] = (grupo[i] == '1') ? '0' : '1';
        }
    }
}

string codificarM2(string &cadena, int n){
    int longitud = cadena.length();
    string resultado = "";

    for (int i = 0; i < longitud; i += n){
        string grupo = cadena.substr(i, n);
        char ultimoBit = grupo[n - 1];

        for (int j = n - 2; j >= 0; j--){
            grupo[j + 1] = grupo[j];
        }
        grupo[0] = ultimoBit;

        resultado += grupo;
    }
    return resultado;
}

void codificarM1(string &cadena, int n){
    int longitud = cadena.length();
    string resultado = "";

    string primerBloque = cadena.substr(0, n);
    string grupoAnterior = primerBloque;

    for(char &bit : primerBloque){
        bit = (bit == '1') ? '0' : '1';
    }
    resultado += primerBloque;

    for (int i = n; i < longitud; i += n){
        string grupo = cadena.substr(i, n);
        aplicarReglas(grupo, grupoAnterior);
        resultado += grupo;
        grupoAnterior = cadena.substr(i, n);
    }
    cadena = resultado;
}

string quitarCeros(string linea, int cantidad_bytes){
    string sincero = "";
    sincero = linea.substr(0, 8 * cantidad_bytes);
    return sincero;
}
void generarArchivoTextoDecodificado(string nombreCodificado, string nombreSalida, int semilla, int* longitudesCedulas, int* longitudesClaves, int* longitudesSaldos, int numeroUsuarios){
    ifstream archivo(nombreCodificado);
    ofstream salida(nombreSalida);
    if(!archivo.is_open()){
        cerr << "Error: no se pudo abrir el archivo codificado." << endl;
        return;
    }
    if(!salida.is_open()){
        cerr << "Error: no se pudo crear el archivo de salida." << endl;
        return;
    }

    string linea;
    int lineaActual = 0;
    int usuarioActual = 0;

    while(getline(archivo, linea)){
        string decodificada = decodificarM2(linea, semilla);

        // Determinar tipo de línea según posición
        if(lineaActual == 0){
            // Contraseña del administrador
            decodificada = quitarCeros(decodificada, 200);
            decodificada = convBinInt(decodificada);
            salida << "Contraseña del administrador: " << decodificada << endl;
        } else {
            int tipo = (lineaActual - 1) % 3; // 0=cedula,1=clave,2=saldo
            if(tipo == 0){
                decodificada = quitarCeros(decodificada, longitudesCedulas[usuarioActual]);
                decodificada = convBinInt(decodificada);
                salida << "Usuario " << usuarioActual+1 << " - Cedula: " << decodificada << endl;
            } else if(tipo == 1){
                decodificada = quitarCeros(decodificada, longitudesClaves[usuarioActual]);
                decodificada = convBinInt(decodificada);
                salida << "Clave: " << decodificada << endl;
            } else {
                decodificada = quitarCeros(decodificada, longitudesSaldos[usuarioActual]);
                decodificada = convBinInt(decodificada);
                salida << "Saldo: " << decodificada << endl << endl;
                usuarioActual++;
            }
        }
        lineaActual++;
    }

    archivo.close();
    salida.close();
    cout << "Archivo " << nombreSalida << " generado exitosamente con el contenido original." << endl;
}
