#include <cstring>
#pragma once
#include <iostream>

using namespace std;

class Persona{
protected:
int dni;
char nombre[30];
char apellido[30];
long telefono;

public:


void setNombre(char *_nombre);
void setApellido(char *_apellido);
void setDni(int _dni);
void setTelefono(long _telefono);
void Cargar();
void Mostrar();

char* getNombre(){return nombre;}
char* getApellido(){return apellido;}
int getDni(){return dni;}
long getTelefono(){return telefono;}

};

