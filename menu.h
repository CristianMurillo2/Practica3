#ifndef MENU_H
#define MENU_H

#include "codificaciones.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int NumeroLineasArchivo(string nombreArchivo);
bool comprobarLectura(string nombredelarchivo);
string leerUnaLinea(int numero_linea_deseada, string nombreArchivo);
string ponerCeros(string lineaBinString, int n);
bool verificacionAdministrador(string nombreArchivo, int semilla_de_codificacion, int longitud);
void EscribirContraseñasobreArchivo(string line, string nombreArchivo);
bool esNumero(string str);
int numeroLegal();
string CrearArhcivo(int& n, int &longitud, int*& longitud_cedula, int*& longitd_clave, int*& longitud_saldo, int& numero_usuarios, int& capacidad_usuarios);
void ComprobacionDeArchivo(string& nombre_del_archivo, bool& bandera, int &semilla, int& longitud,int*& longitud_cedula, int*& longitd_clave, int*& longitud_saldo,int& numero_usuarios, int& capacidad_usuarios);
bool VerificarNumeroPositivo(int numero);
bool cedulaRepetida(string nombre_del_archivo, string cedula_a_verificar);
void CrearUsuario(string nombre_archivo, int& semilla, int*& longitud_cedula, int*& longitd_clave,int*& longitud_saldo, int& numero_usuarios, int& capacidad_usuarios);
string ValidarCedula_o_Saldo(string nombre);
bool ValidacionUsuario(string nombre_del_archivo, int semilla, int& numero_de_linea_cedula,int* longitud, int& contador);
char VerificarTamaño();
bool VerificarSaldoRetirar(int& saldo_entero, int numero_linea_deseada, string nombreArchivo, int semilla, int longitud, long long int cantidad_a_retirar);
bool VerificarSaldo(int& saldo_entero, int numero_linea_deseada, string nombreArchivo,int semilla, int longitud);
string EncriptarNuevosValores(int valor, int semilla);
void ActualizarSaldo(int valorSaldo, string nombreArchivo, int linea_a_cambiar, int semilla,int* vectorsaldo, int posicion,int* longitudes_cedula, int* longitudes_claves,int* longitudes_saldos, int numero_usuarios);

#endif // MENU_H
