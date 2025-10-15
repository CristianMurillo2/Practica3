#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
using namespace std;

int main()
{
    ifstream fin;     //stream de entrada
    ofstream fout;    //stream de salida
    char cadena1[100000],cadena2[10000], array[100000], array2[100000],array3[100000], au;
    long long int contador=0, num=0, caso, semilla, x=0, aux=0, unos=0, ceros=0, u=0,y=0, exp,digito;
    long double binario, decimal;
    string data,a,b;
    cout<<"Archivo de entrada: "<<endl;
    cin>>b;
    cout<<"Archivo de salida: "<<endl;
    cin>>a;

    try{
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

    cout<<"Ingrese semilla de decodificacion: ";
    cin>>semilla;
    cout<<endl<<"Seleccione metodo de decodificacion 1 o 2: "<<endl;
    cin>>caso;
    if (caso==1){  //Decodificación por método 1.
        contador=0;


        fin.open(b);
        fin.getline(array,100000);
        fin.seekg(0);
        fin.close();
        fin.open(b);
        fin.getline(array2,100000);
        fin.seekg(0);
        fin.close();
        fout.open("Binario.txt");

        strcpy(array,array2); //Con esto hago una copia por que arriba a la hora de añadir del archivo me genera un error

        long int longitud;
        longitud=strlen(array2);
        contador=0;
        while(contador<semilla){
            if (array2[u]=='0'){
                array2[u]='1';
            }
            else {
                array2[u]='0';
            }
            u++;
            contador++;
        }
        for (int j=0;array[j]!='\0';j++){
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
            if (array2[j]=='1')
                unos+=1;
            else ceros+=1;
            aux++;
            x++;
        }
        fout<<array2;
        fout.close();
        cout<<"Mensaje decodificado en el archivo Binario.txt."<<endl;
    }
    else if (caso==2){      //Decodificación por método 2.
        fin.open(b);
        fin.getline(array2,100000);
        fin.seekg(0);
        fin.close();
        fin.open(b);
        fin.getline(array,100000);
        fin.seekg(0);
        fin.close();

        fout.open("Binario.txt");
        for (int j=0;array[j]!='\0';j++){
            if (y==semilla){
                y=0;
                au=array3[0];
                for (int k=0;k<semilla-1;k++){
                    array3[k]=array3[k+1];
                }
                array3[semilla-1]=au;
                for (int num=0; array3[num]!='\0';num++){

                        fout<<array3[num];
                }
            }
            array3[y]=array[j];
            y++;
        }
        au=array3[0];
        for (int k=0;k<semilla-1;k++){
            array3[k]=array3[k+1];
        }
        array3[semilla-1]=au;
        for (int num=0; array3[num]!='\0';num++){

                fout<<array3[num];
        }
        fout.close();
        cout<<"Mensaje decodificado en el archivo Binario.txt."<<endl;
    }
    else cout<<"Error decodificando."<<endl;
    try{
        //Lectura en archivo
        fin.open("Binario.txt");        //Flujo de entrada para leer, el archivo debe existir.
        if (!fin.is_open()){            //si no se pudo abrir el archivo para lectura.
            throw '1';
        }
        fin.getline(cadena1,100000);        //recibe arreglo o puntero (referencia) y cantidad de caracteres (tamaño). Lee una linea del archivo y lo asigna en cadena2
        fin.seekg(0);                   //reubicar puntero a la dirección cero, es decir al inicio del archivo.
        fin.close();                    //se cierra el archivo de lectura
    }
    catch (char c){
        if (c=='1')
            cout<<"Error en el archivo de lectura."<<endl;
    }
    catch (...){    //Error que no se consideró.
        cout<<"Error inesperado."<<endl;
    }
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //Se covierte el archivo de binario a texto.
    fout.open(a);
    contador=0;
    while(cadena1[contador]!='\0') {
        if (num==8){
            num=0;
            binario=atoi(cadena2);
            exp=0;
            decimal=0;
            while(((int)(binario/10))!=0)
            {
                    digito = (int)binario % 10;
                    decimal = decimal + digito * pow(2.0,exp);
                    exp++;
                    binario=(int)(binario/10);
            }
            decimal=decimal + binario * pow(2.0,exp);
            if ((char(decimal)>=32 && char(decimal)<=122))
                fout<<char(decimal);
        }
        cadena2[num]=cadena1[contador];
        num++;
        contador+=1;
    }
    binario=atoi(cadena2);
    exp=0;
    decimal=0;
    while(((int)(binario/10))!=0)
    {
            digito = (int)binario % 10;
            decimal = decimal + digito * pow(2.0,exp);
            exp++;
            binario=(int)(binario/10);
    }
    decimal=decimal + binario * pow(2.0,exp);
    if ((char(decimal)>=32 && char(decimal)<=122) )
        fout<<char(decimal);
    cout<<"El mensaje original se encuentra en el archivo "<<a<<endl;
    fout.close();
    return 0;
}
