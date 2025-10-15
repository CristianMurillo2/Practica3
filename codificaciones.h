#ifndef CODIFICACIONES_H
#define CODIFICACIONES_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
using namespace std;
void aplicarReglasInv(string &grupo, string &grupoAnterior);
void decodificarM1(string &cadena, int n);
string decodificarM2(string cadena, int n);
string convBinInt(string linea);
void convIntBin(char *linea, int ent);
void aplicarReglas(string &grupo, string &grupoAnterior);
string codificarM2(string &cadena, int n);
void codificarM1(string &cadena, int n);
string quitarCeros(string linea, int cantidad_bytes);
void generarArchivoTextoDecodificado(string nombreCodificado, string nombreSalida, int semilla, int* longitudesCedulas, int* longitudesClaves, int* longitudesSaldos, int numeroUsuarios);

#endif // CODIFICACIONES_H

