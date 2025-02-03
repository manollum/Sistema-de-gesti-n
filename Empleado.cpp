#include <iostream>
#include "Persona.h"
#include "Empleado.h"
#include "ArchivoEmpleados.h"


Empleado::Empleado(int _legajo, const char *_cargo, double _sueldo){
legajo = _legajo;
strncpy(cargo, _cargo, 19);
sueldo = _sueldo;
estado = true;
}

void Empleado::setLegajo(int _legajo){
legajo = _legajo;
}

void Empleado::setCargo(char *_cargo){
strncpy(cargo, _cargo, 19);
}

void Empleado::setSueldo(double _sueldo){
sueldo = _sueldo;
}

void Empleado::setEstado(bool _estado){
estado = _estado;
}

void Empleado::cargarEmpleado(ArchivoEmpleados archivoE){
system("cls");
char _cargo[20];

Cargar();
if(dni==0)return;
cin.ignore();

legajo = archivoE.contarRegistros()+1;

cout << "Ingrese el cargo actual: ";
cin.getline(_cargo, 29);
cout << "Ingrese el sueldo fijo: ";
cin >> sueldo;
cout << "Carga finalizada." << endl;
cout << system("pause");
system("cls");

strcpy(cargo, _cargo);
}

void Empleado::mostrarEmpleado(){
Mostrar();
cout << "Legajo: ";

if(legajo > 0 && legajo < 10000){
    if(legajo < 10)
    cout << "000" << legajo;

    else if(legajo < 100)
    cout << "00" << legajo;

    else if(legajo < 1000)
    cout << "0" << legajo;

    else
    cout << legajo;
}
cout << endl;

cout << "Cargo: " << cargo << endl;
cout << "Sueldo fijo: $" << (int)sueldo << endl;
}
