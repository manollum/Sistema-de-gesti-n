#pragma once
#include <cstring>
#include "Comanda.h"  // Se supone que la clase Comanda est� definida en otro archivo


class Comanda;


class ArchivoComandas {
private:
    char nombre[20];
    int tam;  // Tama�o de una comanda (tama�o de la clase Comanda)

public:
    ArchivoComandas(const char *_nombre = "comandas.dat");  // Constructor que recibe el nombre del archivo

    // M�todos de la clase ArchivoComandas
    bool grabarRegistro(Comanda obj);  // Graba una nueva comanda en el archivo
    int obtenerIdRegistro();  // Obtiene el siguiente ID disponible para una nueva comanda
    int buscarRegistro();  // Busca una comanda por su ID
    bool leerRegistro(int pos);  // Lee una comanda en una posici�n espec�fica
    bool listarRegistros();  // Lista todas las comandas activas
    Comanda buscarComanda(int idComanda);  // Busca una comanda por su ID y devuelve el objeto
    void resetearComandas();
};
