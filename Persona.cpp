#include <cstring>
#include <iostream>
#include "Persona.h"

using namespace std;


void Persona::setNombre(char *_nombre){
strcpy(nombre, _nombre);
}

void Persona::setApellido(char *_apellido){
strcpy(apellido, _apellido);
}

void Persona::setDni(int _dni){
dni = _dni;
}

void Persona::setTelefono(long _telefono){
telefono = _telefono;
}

void Persona::Cargar(){
int _dni;
long _telefono;
char _nombre[30], _apellido[30];
cout << "Ingrese el DNI, (0 para volver al MENU anterior): ";
cin >> _dni;
if(_dni==0){
    dni = 0;
    return;
}
cin.ignore();
cout << "Ingrese el nombre: ";
cin.getline(_nombre, 29);
cout << "Ingrese el apellido: ";
cin.getline(_apellido, 29);
cout << "Ingrese el numero de telefono: ";
cin >> _telefono;

strcpy(nombre, _nombre);
strcpy(apellido, _apellido);
dni = _dni;
telefono = _telefono;
}

void Persona::Mostrar(){
cout << "Nombre: " << nombre << endl;
cout << "Apellido: " << apellido << endl;
cout << "DNI: " << dni << endl;
cout << "Telefono: " << telefono << endl;
}
