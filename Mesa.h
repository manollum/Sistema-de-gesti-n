#pragma once
#include "Producto.h"

class Mesa {
protected:
    int idMesa;                 /// ID unico de la mesa
    Producto productos[100];    /// Array de productos asociados
    int cantidades[100];        /// Cantidades de cada producto
    int cantidadProductos = 0;  /// Numero actual de productos en la mesa
    float saldo;                /// Total gastado por la mesa
    bool estado = false;

public:
    /// Constructores
    Mesa() : idMesa(0), saldo(0) {}
    Mesa(int id) : idMesa(id), saldo(0) {}

    /// Getters
    int getIdMesa();
    float getSaldo();
    bool getEstado();
    int getCantidadProductos();
    int getCantidadProducto(int i);
    Producto getProducto(int n);

    /// Setters
    void setIdMesa(int id);
    void setEstado(bool est);
    void setProducto(const Producto& prod, int cant);
    void setSaldo(float nuevoSaldo) ;

    /// Metodos adicionales
    void agregarProducto(Producto& prod, int cant);
    void resetearMesa();
    void mostrarMesa();
    void eliminarProducto(Producto& producto);
    void generarTicket(float saldoOriginal);
};
