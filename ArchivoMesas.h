#pragma once
#include "Mesa.h"
#include "Producto.h"
#include <cstring>

using namespace std;

class ArchivoMesas {
private:
    char nombre[20];
    int tam;

public:

    ArchivoMesas(const char *_nombre = "mesas.dat");

    bool grabarRegistroMesas(Mesa obj);
    int buscarRegistro(int idMesa);
    bool listarRegistros();
    bool modificarRegistro(int pos, Mesa obj);
    bool eliminarRegistro(int pos);
    int obtenerIdMesa();
    Producto seleccionarProducto();
    Mesa leerRegistro(int pos);
    bool buscarMesaPorId(int idMesa, Mesa &mesa);
    bool modificarRegistro(Mesa &mesa);

};
