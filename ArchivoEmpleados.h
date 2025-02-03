#pragma once
#include "Empleado.h"

class ArchivoEmpleados{
private:
char nombre[20];
int tam;

public:
ArchivoEmpleados(const char *_nombre = "empleados.dat"){
strncpy(nombre, _nombre, 19);
tam = sizeof(Empleado);
}

bool grabarRegistro(Empleado obj);
int buscarRegistro();
bool leerRegistro(int pos);
bool listarRegistros();
bool listarRegistrosInactivos();
bool modificarRegistro(int pos);
bool bajaRegistro();
bool altaRegistro();
int contarRegistros();

};
