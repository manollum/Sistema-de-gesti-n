#pragma once
#include "Persona.h"

class ArchivoEmpleados;

class Empleado:public Persona{
protected:
int legajo;
char cargo[30];
double sueldo;
bool estado;

public:
Empleado(int _legajo = 0, const char * _cargo = "...", double _sueldo = 0);

void setLegajo(int _legajo);
void setCargo(char *_cargo);
void setSueldo(double sueldo);
void setEstado(bool _estado);
void cargarEmpleado(ArchivoEmpleados archivoE);
void mostrarEmpleado();

int getLegajo() {return legajo;}
char* getCargo() {return cargo;}
double getSueldo(){return sueldo;}
bool getEstado() {return estado;}
};

