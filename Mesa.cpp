#include <iostream>
#include <iomanip>
#include "Mesa.h"

using namespace std;


    /// Getters
    int Mesa::getIdMesa() { return idMesa; }
    float Mesa::getSaldo() { return saldo; }
    bool Mesa::getEstado() { return estado; }
    int Mesa::getCantidadProductos(){
    return cantidadProductos;
    }


    Producto Mesa::getProducto(int n) {
    if (n >= 0 && n < cantidadProductos) {
        return productos[n];  /// Devuelve el producto en la posición n
    } else {
        /// Si el índice está fuera de rango, podemos lanzar una excepción o devolver un producto vacío
        cout << "Indice fuera de rango." << endl;
        return Producto();  /// Devuelve un producto por defecto (vacío)
        }
    }



    /// Setters
    void Mesa::setIdMesa(int id) { idMesa = id; }
    void Mesa::setEstado(bool est) { estado = est; }

    void Mesa::setSaldo(float nuevoSaldo) {
        saldo = nuevoSaldo;  // Asignamos el nuevo valor al saldo
    }

    /// Metodos adicionales
    void Mesa::agregarProducto(Producto& prod, int cant) {
    if (cantidadProductos < 100) {
        // Agregar producto al array de productos y cantidad
        productos[cantidadProductos] = prod;
        cantidades[cantidadProductos] = cant;

        // Actualizar el saldo acumulando el precio total por la cantidad
        saldo += prod.getPrecio() * cant;

        // Incrementar la cantidad de productos
        cantidadProductos++;
    } else {
        cout << "No se pueden agregar mas productos a esta mesa." << endl;
        system("pause");
        }
    }

    void Mesa::resetearMesa() {
        cantidadProductos = 0;
        saldo = 0;
        estado = false;
    }

    void Mesa::mostrarMesa() {
    cout << "****************" << endl;
    cout << "Mesa ID: " << getIdMesa() << "     *"<<endl;
    cout << "****************" << endl;

    // Solo mostrar productos activos
    int cantidadProductos = getCantidadProductos();  // Método que devuelve la cantidad de productos en la mesa
    if (cantidadProductos > 0) {
        cout << "Productos asociados a la mesa:" << endl;
        for (int i = 0; i < cantidadProductos; ++i) {
            Producto prod = getProducto(i);  // Obtener el producto en la posición 'i'
            if (prod.getEstado()) {  // Verificar si el producto está activo con getEstado()
                cout << "*Producto " << (i + 1) << ":" << endl;
                cout << "ID Producto: " << prod.getIdProducto() << endl;
                cout << "Descripcion: " << prod.getDescripcion() << endl;
                cout << "Precio: " << prod.getPrecio() << " ARS" << endl;
                cout << "Cantidad: " << getCantidadProducto(i) << endl;  // Usar el getter
                cout << "Tipo de Producto: " << (prod.getTipoProducto() == 1 ? "Plato" : prod.getTipoProducto() == 2 ? "Bebida" : "Guarnicion") << endl;
                cout << "-----------" << endl;
            }
        }
    } else {
        cout << "No hay productos asociados a esta mesa." << endl;
    }

    cout << "SALDO: $" << getSaldo() << endl <<endl;
}


    void Mesa::setProducto(const Producto& prod, int cant) {
        if (cantidadProductos < 100) {
            productos[cantidadProductos] = prod;  // Aquí asignamos un objeto Producto
            cantidades[cantidadProductos] = cant;
            saldo += prod.getPrecio() * cant;
            cantidadProductos++;
        } else {
            cout << "No se pueden agregar mas productos a esta mesa." << endl;
        }
    }



    int Mesa::getCantidadProducto(int i) {
    if (i >= 0 && i < cantidadProductos) {  /// Verificar que el índice esté dentro del rango válido
        return cantidades[i];
        }
    return 0; /// Si el índice es inválido, devolver 0 (o manejar de otra manera si lo prefieres)
    }




    void Mesa::eliminarProducto(Producto& prod) {
    int indice = -1;

    // Buscar el indice del producto por ID
    for (int i = 0; i < cantidadProductos; ++i) {
        if (productos[i].getIdProducto() == prod.getIdProducto()) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        cout << "Producto no encontrado en esta mesa." << endl;
        return;
    }

    // Restar el saldo correspondiente al producto eliminado
    saldo -= productos[indice].getPrecio() * cantidades[indice];

    // Mover los productos restantes una posicion atras
    for (int i = indice; i < cantidadProductos - 1; ++i) {
        productos[i] = productos[i + 1];
        cantidades[i] = cantidades[i + 1];
    }

    // Reducir la cantidad de productos
    cantidadProductos--;

    cout << "Producto eliminado exitosamente." << endl;
}




void Mesa::generarTicket(float saldoOriginal) {
    system("cls");
    system("color 04");

    cout << "\n--- TICKET DE MESA ---" << endl;
    cout << "Mesa No: " << idMesa << endl;
    cout << "-----------------------------------" << endl;

    // Alinear las columnas con setw, dejando más espacio para la descripción
    cout << setw(40) << left << "Descripcion"
         << setw(15) << "Precio"
         << setw(15) << "Tipo"
         << setw(10) << "Cantidad" << endl;
    cout << "-----------------------------------" << endl;

    for (int i = 0; i < cantidadProductos; i++) {
        Producto prod = productos[i];
        double totalProducto = prod.getPrecio() * cantidades[i];  /// Precio por la cantidad pedida

        // Imprimir detalles del producto, alineados
        cout << setw(40) << left << prod.getDescripcion()  // Mayor espacio para la descripcion
             << setw(15) << fixed << setprecision(2) << totalProducto
             << setw(15) << (prod.getTipoProducto() == 1 ? "Plato" : (prod.getTipoProducto() == 2 ? "Bebida" : "Guarnicion"))
             << setw(10) << cantidades[i]  /// Mostrar la cantidad pedida
             << endl;
    }

    // Verificar si el saldo ha sido modificado (suma o resta)
    if (saldo > saldoOriginal) {  /// Si el saldo es mayor, se sumó una propina
        cout << "Propina: +$" << fixed << setprecision(2) << saldo - saldoOriginal << endl;
    } else if (saldo < saldoOriginal) {  /// Si el saldo es menor, se restó algo de la mesa
        cout << "Saldo a favor: -$" << fixed << setprecision(2) << saldoOriginal - saldo << endl;
    }

    cout << "-----------------------------------" << endl;
    cout << "Total: $" << fixed << setprecision(2) << saldo << endl;

    cout << "-----------------------------------" << endl;
    cout << "Gracias por su visita!" << endl;
}
