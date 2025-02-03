#include <iostream>
#include "Persona.h"
#include "Cliente.h"



Cliente::Cliente(int _comensales, int _mesaAsignada){
comensales = _comensales;
mesaAsignada = _mesaAsignada;
estado = true;
}

void Cliente::setComensales(int _comensales){
    comensales = _comensales;
}

void Cliente::setMesaAsignada (int _mesaAsignada){
    mesaAsignada = _mesaAsignada;
}

void Cliente::setEstado(bool _estado){
estado = _estado;
}

void Cliente::cargarCliente(){
int _comensales, _mesaAsignada;

Cargar();

cout << "Ingrese la cantidad de comensales: ";
cin >> _comensales;
cout << "Ingrese el numero de mesa: ";
cin >> _mesaAsignada;
cout << endl;

comensales = _comensales;
mesaAsignada = _mesaAsignada;
}

void Cliente::mostrarCliente(){
Mostrar();
cout << "Comensales: " << comensales << endl;
cout << "Mesa asignada: " << mesaAsignada << endl;
}
