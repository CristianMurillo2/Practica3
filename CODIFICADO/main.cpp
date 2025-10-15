#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

//El archivo de entrada debe de existir en el build

int main()
{
    ifstream fin;     //stream de entrada
    ofstream fout;    //stream de salida
    char   array[100000],array3[100], au;
    char array2[100000];
    int contador=0, caso, semilla, u=0,y=0;

    string data,a,b;


    cout<<"Archivo de entrada: "<<endl;
    cin>>b;
    cout<<"Archivo de salida: "<<endl;
    cin>>a;

    try{                                //excepción.


        fin.open(b);        //Flujo de entrada para leer, el archivo debe existir.
        if (!fin.is_open()){            //si no se pudo abrir el archivo para lectura.
            throw '2';
        }
        fin.close();                    //se cierra el archivo de lectura
    }
    catch (char c){     //capturar caracter que se puso
        cout<<"Error # "<<c<<" : "<<endl;

        if (c=='2')
            cout<<"Error en el archivo de lectura."<<endl;

    }
    catch (...){    //Error que no se consideró.
        cout<<"Error inesperado."<<endl;

    }
    fin.open(b);
    getline(fin,data);
    fin.close();

    fout.open("Binario");
    int n = data.length(); //Su funcion de binario :)


    for (int i = 0; i < n; ++i) {
        string bin = "";

        int val = int(data[i]);

        unsigned short int cont = 0;
        while (cont < 8) {
            (val % 2)? bin.push_back('1') :
                       bin.push_back('0');
            val/=2;
            cont++;
        }
        reverse(bin.begin(), bin.end());
        for (unsigned int i = 0; i < bin.length(); i++) {
                  fout<<bin.at(i);

              }
    }
    fout.close();
    cout<<"Ingrese semilla de codificacion: ";
    cin>>semilla;
    cout<<endl<<"Seleccione metodo de codificacion 1 o 2: "<<endl;
    cin>>caso;
    if (caso==1){           //Método 1.
        contador=0;
        fin.open("Binario");
        fin.getline(array,100000);
        fin.seekg(0);
        fin.close();
        fin.open("Binario");
        fin.getline(array2,100000);
        fin.seekg(0);
        fin.close();
        fout.open(a);
        contador=0;


        long int longitud;
        longitud=strlen(array2);//Saco la longitud del binario que se formo para controlar el ciclo
        cout<<longitud;

        while(contador<semilla){ //Primer bloque
            if (array2[u]=='1'){
                array2[u]='0';
            }
            else {
                array2[u]='1';
            }
            u++;
            contador++;
        }
        int aux=0 , x=0 , unos=0, ceros=0;
        for (int j=0;j!=longitud;j++){
            if (x==semilla){
                x=0;
                if(aux>0){
                    if (unos==ceros){ //Se invierte cada bit
                        contador=0;
                        while(contador<semilla){
                            if(u==longitud){
                                break;
                            }
                            if (array2[u]=='1'){
                               array2[u]='0';
                            }
                            else {
                                array2[u]='1';
                            }
                            u++;
                            contador++;
                        }
                    }
                    else if (unos>ceros) { //Cada 3 bits
                        int y=0;
                        contador=0;

                        while(contador<semilla){
                            if(u==longitud){
                                break;
                            }
                            if (y==2){
                                if (array2[u]=='1'){
                                   array2[u]='0';
                                }
                                else {
                                    array2[u]='1';
                                }
                                y=0;


                            }

                            else y++;
                            u++;
                            contador++;

                        }
                    }
                    else{ //Cada 2 bits
                        int z=0;
                        contador=0;
                        while(contador<semilla){
                            if(u==longitud){
                                break;
                            }
                            if (z==1){
                                if (array2[u]=='1'){
                                   array2[u]='0';
                                }
                                else {
                                    array2[u]='1';
                                }
                            }
                            if (z==1)
                                z=0;
                            else z++;
                            u++;
                            contador++;
                        }
                    }
                }
                unos=0;
                ceros=0;
            }
            if (array[j]=='1') //Cuento unos y ceros
                unos+=1;
            else ceros+=1;
            aux++;
            x++;
        }
        fout<<array2;
        fout.close();
        cout<<"Mensaje codificado en el archivo "<<a<<endl;
    }
    else if (caso==2){
        fin.open("Binario");
        fin.getline(array,100000);
        fin.seekg(0);
        fin.close();
        fout.open(a);
        for (int j=0;array[j]!='\0';j++){
            if (y==semilla){
                y=0;
                au=array3[semilla-1];
                for (int k=semilla-1;k>=0;k--){
                    array3[k]=array3[k-1]; //Corremos una pocision
                }
                array3[0]=au;
                for (int num=0; array3[num]!='\0';num++){
                    //if (array3[num]>='0' && array3[num]<='9')
                        fout<<array3[num]; //Vamos guardando en el archivo los bloques de n simbolos
                }
            }
            array3[y]=array[j]; //Voy copiando segun la semilla
            y++;
        }
        au=array3[semilla-1];
        for (int k=semilla-1;k>=0;k--){
            array3[k]=array3[k-1];
        }
        array3[0]=au; //El mismo procedimiento para el ultimo bloque
        for (int num=0; array3[num]!='\0';num++){
            //if (array3[num]>='0' && array3[num]<='9')
                fout<<array3[num];
        }
        fout.close();
        cout<<"Mensaje codificado en el archivo "<<a<<endl;
    }
    else cout<<"Error en codificacion."<<endl;

    return 0;
}
