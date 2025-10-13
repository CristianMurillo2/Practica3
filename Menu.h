#ifndef MENU_H
#define MENU_H
#include "codificaciones.h"
#include <string>

int NumeroLineasArchivo(string nombreArchivo){
    string linea;
    int numero_linea_actual=0;
    ifstream archivo;
    archivo.open(nombreArchivo);
    while(getline(archivo, linea)){
        numero_linea_actual++;
    }
    archivo.close();
    return numero_linea_actual;
}

bool comprobarLectura( string nombredelarchivo){
    ifstream archivo;
    archivo.open(nombredelarchivo);
    if(!archivo){
        cerr << "No se puede abrir el archivo. No se encuentra." << endl;
        return false;
    }else{
        archivo.close();
        cout << "Verificacion exitosa" <<endl;
        return true;
    }
}

string leerUnaLinea(int numero_linea_deseada, string nombreArchivo){
    string linea;
    int numero_linea_actual=0;
    ifstream archivo;
    archivo.open(nombreArchivo);
    while(getline(archivo, linea)){
        if(numero_linea_actual==numero_linea_deseada){
            archivo.close();
            return linea;
        }
        numero_linea_actual++;
    }
}
string ponerCeros(string lineaBinString, int n){
    if(lineaBinString.length() < n){
        for(int x = lineaBinString.length(); x < n ; x++)
            lineaBinString += "0";
    }

    if((lineaBinString.length() % n) != 0){
        for(int x = (lineaBinString.length()%n); x < n ; x++)
            lineaBinString += "0";
    }
    return lineaBinString;
}


bool verificacionAdministrador(string nombreArchivo, int semilla_de_codificacion, int longitud){
    string contraseña_ingresada = " ";
    string contraseña_guardada= leerUnaLinea(0, nombreArchivo);
    cin >> contraseña_ingresada;
    contraseña_guardada= decodificarM2(contraseña_guardada, semilla_de_codificacion);
    contraseña_guardada= quitarCeros(contraseña_guardada, longitud);
    contraseña_guardada= convBinInt(contraseña_guardada);
    if(contraseña_guardada==contraseña_ingresada){
        return true;
    }else{
        return false;
    }
}

void EscribirContraseñasobreArchivo(string line, string nombreArchivo){
    ofstream archivo;
    archivo.open(nombreArchivo);
    archivo<<line<<endl;
    archivo.close();
}


bool esNumero(string str){
    for(char c : str){
        if((c < '0') || (c > '9')){
            return false;
        }
    }
    return true;
}

int numeroLegal(){
    string entrada;
    bool entradaValida = false;
    int numero = 0;

    while(!entradaValida){
        cout << "Ingrese la semilla de codificacion: ";
        cin >> entrada;

        entradaValida = esNumero(entrada);

        if(entradaValida){
            numero = 0;
            for (char c : entrada){
                numero = numero * 10 + (c - '0');
            }

            if(numero < 1){

                entradaValida = false;
            }
        }

        if(!entradaValida){
            cout << "Entrada invalida. Por favor, ingrese un numero entero mayor o igual a 1." << endl;
        }
    }

    return numero;
}

string CrearArhcivo(int& n, int &longitud, int*& longitud_cedula, int*& longitd_clave, int*& longitud_saldo, int& numero_usuarios, int& capacidad_usuarios){
    string nombre_nuevo_archivo= "Nuevo archivo.txt";
    string lecturaConsola = "";
    cout << "Ingrese la clave del administrador: " << endl;
    cin >> lecturaConsola;
    longitud = lecturaConsola.length();

    string lineaBin= "";

    for (int i = 0; i < longitud; i++) {
        char aux[9];
        convIntBin(aux, lecturaConsola[i]);
        lineaBin+= aux;
    }

    n = numeroLegal();

    int tamaño= lineaBin.length();
    if(tamaño < n){
        for(int x = tamaño; x < n ; x++)
            lineaBin += "0";
    }

    if((tamaño % n) != 0){
        for(int x = (tamaño % n); x < n ; x++)
            lineaBin += "0";
    }

    string contraseña_encriptada;

    contraseña_encriptada= codificarM2(lineaBin, n);

    EscribirContraseñasobreArchivo(contraseña_encriptada, nombre_nuevo_archivo);

    delete[] longitud_cedula;
    delete[] longitd_clave;
    delete[] longitud_saldo;

    numero_usuarios = 0;
    capacidad_usuarios = 1;
    longitud_cedula = new int[capacidad_usuarios];
    longitd_clave = new int[capacidad_usuarios];
    longitud_saldo = new int[capacidad_usuarios];

    return nombre_nuevo_archivo;
}

void ComprobacionDeArchivo(string& nombre_del_archivo, bool& bandera, int &semilla, int& longitud, int*& longitud_cedula, int*& longitd_clave, int*& longitud_saldo, int& numero_usuarios, int& capacidad_usuarios){
    bool inicio= true;
    char respuesta= ' ';
    string verificar_tamaño= "";
    char respuesta_creacion_archivo= ' ';

    while(inicio){
        cout <<"\nVerficacion de los archivos del sistema...\n"<<endl;
        bandera= comprobarLectura(nombre_del_archivo);
        if(bandera){
            inicio= false;
        }else{
            cout << "Desea crear un archivo? (Ingrese s(si) o n(no)): "; cin >>verificar_tamaño;
            if(verificar_tamaño.length() > 1){
                cout << "Solo puedes ingresar una letra" <<endl;
            }else if (verificar_tamaño.length() ==1 && verificar_tamaño != "\n"){
                respuesta= verificar_tamaño[0];
                switch(respuesta){
                case 's':
                    nombre_del_archivo = CrearArhcivo(semilla, longitud, longitud_cedula, longitd_clave, longitud_saldo, numero_usuarios, capacidad_usuarios);
                    break;
                case 'n':
                {
                    bool bandera_interna= true;
                    while(bandera_interna){
                        cout<< "Desea salir del programa? (Ingrese s(si) o n(no)):  "; cin >> respuesta_creacion_archivo;
                        switch(respuesta_creacion_archivo){
                        case 's':{
                            inicio=false;
                            bandera_interna=false;}
                        break;
                        case 'n':
                            bandera_interna= false;
                            break;
                        default:
                            cout << "\nIngresaste una opcion invalida" <<endl;
                            break;
                        }
                        cin.clear();
                        cin.ignore(255, '\n');
                    }
                }
                break;
                default:
                    cout << "\nIngresaste una opcion invalida" <<endl;
                    cin.clear();
                    cin.ignore(255, '\n');
                    break;
                }
            }
        }
    }

}

bool VerificarNumeroPositivo( int numero){
    if(numero<0){
        return false;
    }else{
        return true;
    }
}

bool cedulaRepetida(string nombre_del_archivo, string cedula_a_verificar){
    string linea;
    ifstream archivo;
    archivo.open(nombre_del_archivo);
    int numero_de_lineas= NumeroLineasArchivo(nombre_del_archivo);
    for(int i=1; i<numero_de_lineas; i+=3){
        linea= leerUnaLinea(i, nombre_del_archivo);
        if(linea==cedula_a_verificar){
            archivo.close();
            return true;
        }
    }
    return false;
}

void CrearUsuario(string nombre_archivo, int& semilla, int*& longitud_cedula, int*& longitd_clave, int*& longitud_saldo, int& numero_usuarios, int& capacidad_usuarios){
    ofstream archivo;
    string linea;
    long long int numero;

    if (numero_usuarios == capacidad_usuarios) {
        capacidad_usuarios *= 2;
        int* temp_cedula = new int[capacidad_usuarios];
        int* temp_clave = new int[capacidad_usuarios];
        int* temp_saldo = new int[capacidad_usuarios];
        for (int i = 0; i < numero_usuarios; ++i) {
            temp_cedula[i] = longitud_cedula[i];
            temp_clave[i] = longitd_clave[i];
            temp_saldo[i] = longitud_saldo[i];
        }
        delete[] longitud_cedula;
        delete[] longitd_clave;
        delete[] longitud_saldo;
        longitud_cedula = temp_cedula;
        longitd_clave = temp_clave;
        longitud_saldo = temp_saldo;
    }


    archivo.open(nombre_archivo, ios::app);
    for(int i=0; i<3; i++){
        if(i==0){
            bool bandera=true;
            while(bandera){
                cout <<"Ingrese la cedula (Solo ingrese numeros): ";
                try{
                    if(!(cin >> numero)){
                        throw 1;
                    }else{
                        if(numero<0){
                            cout<<"Solo puede ingresar numeros positivos"<<endl;
                        }else{
                            string version_string= to_string(numero);
                            int longitud = version_string.length();
                            longitud_cedula[numero_usuarios] = longitud;
                            string lineaBina= "";
                            for (int i = 0; i < longitud; i++) {
                                char aux[9];
                                convIntBin(aux, version_string[i]);
                                lineaBina+= aux;
                            }

                            version_string= ponerCeros(lineaBina, semilla);
                            version_string= codificarM2(version_string, semilla);
                            if(cedulaRepetida(nombre_archivo, version_string)){
                                cout << "No se puede agregar esta cedula porque ya existe en el archivo" <<endl;
                            }else{
                                archivo << version_string<< endl;
                                bandera=false;
                            }
                        }
                    }
                }catch(int error){
                    if(error==1){
                        cout<<"\n Ingresate una opcion invalida. Solo puede ingresar numeros\n"<<endl;
                        cin.clear();
                        cin.ignore(255, '\n');
                    }
                }
            }
        }else if(i==1){
            cout <<"Ingrese la clave: "; cin >> linea;
            int longitud = linea.length();
            longitd_clave[numero_usuarios] = longitud;
            string lineaBina= "";
            for (int i = 0; i < longitud; i++) {
                char aux[9];
                convIntBin(aux, linea[i]);
                lineaBina+= aux;
            }
            lineaBina= ponerCeros(lineaBina, semilla);
            linea= codificarM2(lineaBina, semilla);
            archivo << linea<< endl;
        }else{
            bool bandera2=true;
            while(bandera2){
                cout <<"Ingrese el saldo (Solo ingrese numeros): ";
                try{
                    if(!(cin >> numero)){
                        throw 1;
                    }else{
                        if(VerificarNumeroPositivo(numero)){
                            string version_string_saldo= to_string(numero);
                            int longitud = version_string_saldo.length();
                            longitud_saldo[numero_usuarios] = longitud;
                            string lineaBina= "";
                            for (int i = 0; i < longitud; i++) {
                                char aux[9];
                                convIntBin(aux, version_string_saldo[i]);
                                lineaBina+= aux;
                            }
                            lineaBina= ponerCeros(lineaBina, semilla);
                            version_string_saldo= codificarM2(lineaBina, semilla);
                            archivo << version_string_saldo<< endl;
                            bandera2=false;
                        }else{
                            cout<<"Solo puede ingresar numeros positivos"<<endl;
                        }

                    }
                }catch(int error){
                    if(error==1){
                        cout<<"\n Ingresate una opcion invalida. Solo puede ingresar numeros\n"<<endl;
                        cin.clear();
                        cin.ignore(255, '\n');
                    }
                }
            }

        }
    }
    archivo.close();
    numero_usuarios++;
}

string ValidarCedula_o_Saldo(string nombre){
    string version_string;
    long long int numero;
    bool bandera=true;
    while(bandera){
        cout <<"Ingrese "<<nombre<<" (Solo ingrese numeros): ";
        try{
            if(!(cin >> numero)){
                throw 1;
            }else{
                if(VerificarNumeroPositivo(numero)){
                    version_string= to_string(numero);
                    bandera=false;
                }else{
                    cout<<"Solo puede ingresar numeros positivos"<<endl;
                }

            }
        }catch(int error){
            if(error==1){
                cout<<"\n Ingresate una opcion invalida. Solo puede ingresar numeros\n"<<endl;
                cin.clear();
                cin.ignore(255, '\n');
            }
        }
    }
    return version_string;
}


bool ValidacionUsuario(string nombre_del_archivo, int semilla, int& numero_de_linea_cedula, int* longitud, int& contador){
    string cedula;
    cedula= ValidarCedula_o_Saldo("la cedula");
    string linea;
    ifstream archivo;
    archivo.open(nombre_del_archivo);
    int numero_lineas_del_archivo= NumeroLineasArchivo(nombre_del_archivo);
    contador=0;
    for(int numero_linea_actual=1; numero_linea_actual<numero_lineas_del_archivo; numero_linea_actual+=3){
        linea= leerUnaLinea(numero_linea_actual, nombre_del_archivo);
        linea= decodificarM2(linea, semilla);
        linea= quitarCeros(linea, longitud[contador]);
        linea= convBinInt(linea);
        if(linea==cedula){
            numero_de_linea_cedula=numero_linea_actual;
            archivo.close();
            return true;
        }
        contador+=1;
    }
    archivo.close();
    return false;
}

char VerificarTamaño(){
    char respuesta= ' ';
    bool var_control=true;
    while(var_control){
        string verificar_tamaño;
        cin>> verificar_tamaño;
        if(verificar_tamaño.length() > 1){
            cout << "Solo puedes ingresar una letra: ";
        }else if (verificar_tamaño.length() ==1 && verificar_tamaño != "\n"){
            respuesta= verificar_tamaño[0];
            var_control=false;
        }
    }
    return respuesta;
}

bool VerificarSaldoRetirar(int& saldo_entero, int numero_linea_deseada, string nombreArchivo, int semilla, int longitud, long long int cantidad_a_retirar){
    string saldo_string=leerUnaLinea(numero_linea_deseada, nombreArchivo);
    saldo_string= decodificarM2(saldo_string, semilla);
    saldo_string= quitarCeros(saldo_string, longitud);
    saldo_string= convBinInt(saldo_string);
    saldo_entero= stoi(saldo_string);
    if((saldo_entero-cantidad_a_retirar-1000)< 0){
        return false;
    }else{
        return true;
    }
}

bool VerificarSaldo(int& saldo_entero, int numero_linea_deseada, string nombreArchivo, int semilla, int longitud){
    string saldo_string=leerUnaLinea(numero_linea_deseada, nombreArchivo);
    saldo_string= decodificarM2(saldo_string, semilla);
    saldo_string= quitarCeros(saldo_string, longitud);
    saldo_string= convBinInt(saldo_string);
    saldo_entero= stoi(saldo_string);
    if(saldo_entero< 1000){
        return false;
    }else{
        return true;
    }
}

string EncriptarNuevosValores(int valor, int semilla){
    string version_string_saldo= to_string(valor);
    int longitud = version_string_saldo.length();
    string lineaBina= "";
    for (int i = 0; i < longitud; i++) {
        char aux[9];
        convIntBin(aux, version_string_saldo[i]);
        lineaBina+= aux;
    }
    lineaBina= ponerCeros(lineaBina, semilla);
    version_string_saldo= codificarM2(lineaBina, semilla);
    return version_string_saldo;
}

void ActualizarSaldo(int valorSaldo, string nombreArchivo, int linea_a_cambiar, int semilla, int* vectorsaldo, int posicion){

    ifstream archivo_lectura(nombreArchivo);
    ofstream archivo_escritura("temp.txt");
    string versionstring= to_string(valorSaldo);
    int longitud= versionstring.length();
    vectorsaldo[posicion]= longitud;
    string linea;
    int contador=0;
    string nueva_linea= EncriptarNuevosValores(valorSaldo, semilla);
    while(getline(archivo_lectura, linea)){
        if (contador == linea_a_cambiar){
            archivo_escritura<<nueva_linea<<endl;
        }else{
            archivo_escritura<<linea<<endl;
        }
        contador++;
    }
    archivo_escritura.close();
    archivo_lectura.close();

    remove(nombreArchivo.c_str());
    rename("temp.txt", nombreArchivo.c_str());
}

#endif // MENU_H
