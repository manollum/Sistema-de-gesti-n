#pragma once
#include <iostream>
#include <ctime>
#include "Producto.h"
#include "ArchivoComanda.h"


using namespace std;


class ArchivoComandas;


class Comanda {
private:
    int idComanda;
    Producto productos[100];
    int idMesa;
    int cantidadProductos; /// Cantidad actual de productos en la comanda
    char fecha[11]; /// Formato: DD/MM/YYYY
    char hora[9];   /// Formato: HH:MM:SS

    /// Método privado para establecer automáticamente fecha y hora
    void cargarFechaHora() {
        time_t t = time(nullptr);
        tm* now = localtime(&t);

        strftime(fecha, sizeof(fecha), "%d/%m/%Y", now);
        strftime(hora, sizeof(hora), "%H:%M:%S", now);
    }

public:
    /// Constructor
    Comanda(int id, int mesa) : idComanda(id), idMesa(mesa), cantidadProductos(0) {
        cargarFechaHora(); /// Carga automática de fecha y hora
    }
    Comanda();

    /// Getters
    int getIdComanda();
    int getIdMesa();
    const char* getFecha();
    const char* getHora();
    Producto* getProductos();
    int getCantidadProductos();
    /// Setters
    void setIdComanda(int id);
    void setIdMesa(int mesa);


    /// Mostrar los detalles de una comanda
    void mostrarComanda();

    bool mostrarComandas();
    void agregarProducto(const Producto& producto);
    void listarProductos();
    void eliminarProducto(int indice);
    void cargarComanda(ArchivoComandas &archivoC, ArchivoProductos &archivoP);
};
