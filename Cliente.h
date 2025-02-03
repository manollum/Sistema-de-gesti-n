#pragma once

#include "Persona.h"

class Cliente:public Persona{
private:
int comensales;
int mesaAsignada;
bool estado;

public:
Cliente(int _comensales = 0, int _mesaAsignada = 0);
void setComensales(int numero);
void setMesaAsignada(int numero);
void setEstado(bool _estado);
void cargarCliente();
void mostrarCliente();
///void cargarCliente();

int getComensales(){return comensales;}
int getMesaAsignada(){return mesaAsignada;}
bool getEstado(){return estado;}

};

