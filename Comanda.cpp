#include <iostream>
#include "Comanda.h"
#include "ArchivoProductos.h"

    ///constructor por defecto
    Comanda::Comanda() {
    idComanda = 0;  /// Inicializar el ID de la comanda
    idMesa = 0;  /// Inicializar el ID de la mesa
    cantidadProductos = 0;  /// Inicializar la cantidad de productos
    cargarFechaHora();  /// Llamar al método que establece la fecha y la hora
    }



    int Comanda::getIdComanda() {
        return idComanda;
    }

    int Comanda::getIdMesa() {
        return idMesa;
    }

    const char* Comanda::getFecha() {
        return fecha;
    }

    const char* Comanda::getHora() {
    }

    Producto* Comanda::getProductos() {
        return productos; // Devuelve un puntero al array de productos
    }

    int Comanda::getCantidadProductos() {
        return cantidadProductos;
    }

    // Setters
    void Comanda::setIdComanda(int id) {
        idComanda = id;
    }

    void Comanda::setIdMesa(int mesa) {
        idMesa = mesa;
    }

    // Métodos adicionales
    void Comanda::agregarProducto(const Producto& producto) {
        if (cantidadProductos < 100) {
            productos[cantidadProductos] = producto;
            cantidadProductos++;
        } else {
            cout << "No se pueden agregar más productos a la comanda." << endl;
        }
    }

    void Comanda::listarProductos() {
        if (cantidadProductos == 0) {
            cout << "No hay productos en la comanda." << endl;
            return;
        }
        for (int i = 0; i < cantidadProductos; i++) {
            productos[i].mostrarProducto();
            cout << "-----------------" << endl;
        }
    }

    void Comanda::eliminarProducto(int indice) {
        if (indice < 0 || indice >= cantidadProductos) {
            cout << "Índice invalido." << endl;
            return;
        }
        for (int i = indice; i < cantidadProductos - 1; i++) {
            productos[i] = productos[i + 1];
        }
        cantidadProductos--;
        cout << "Producto eliminado correctamente." << endl;
    }

    // Mostrar los detalles de una comanda
void Comanda::mostrarComanda(){
    // Mostrar la comanda
    cout << "ID Comanda: " << idComanda << endl;
    cout << "------------------------------------------" <<endl;
    cout << "ID Mesa: " << idMesa << endl;
    cout << "Fecha: " << fecha << endl;
    cout << "Hora: " << hora << endl;
    cout << "Productos en la comanda: " << cantidadProductos << endl;

    // Mostrar los productos
    for (int i = 0; i < cantidadProductos; ++i) {
        // Asumimos que cada producto tiene un método `mostrarProducto()` para mostrar su detalle
        productos[i].mostrarProducto();
    }

    cout << endl;
}

// Método estático para mostrar todas las comandas
bool Comanda::mostrarComandas() {
    system("cls");  // Limpiamos la pantalla

    FILE *pComandas = fopen("comandas.dat", "rb");  // Abrimos el archivo en modo lectura binaria
    if (!pComandas) {
        cout << "No se encontraron registros en el archivo." << endl;
        system("pause");
        system("cls");
        return false;
    }

    Comanda obj;  // Creamos un objeto Comanda para almacenar los datos leídos

    while (fread(&obj, sizeof(Comanda), 1, pComandas)) {  // Leemos las comandas del archivo
        obj.mostrarComanda();  // Mostramos la comanda
        cout << endl;
    }

    fclose(pComandas);  // Cerramos el archivo
    system("pause");
    system("cls");

    return true;
}



void Comanda::cargarComanda(ArchivoComandas &archivoC, ArchivoProductos &archivoP) {  /// Recibe ArchivoProductos para buscar productos
    /// Declaramos el array cantidades en la función
    int cantidades[100];  // Array para almacenar la cantidad de cada producto
    /// Solicitar ID de la mesa
    do{
    system("cls");
    cout << "Ingrese el ID de la mesa del 1-20, (0 para volver): ";
    cin >> idMesa;
    if(idMesa==0)return;
    if(idMesa<1||idMesa>20){
        cout<<"Mesa fuera de rango, intente nuevamente..."<<endl;
        system("pause");
        }
    }while(idMesa<1||idMesa>20);


    /// Solicitar la cantidad de productos diferentes que se van a agregar a la comanda
    cout << "Ingrese la cantidad de productos de ID diferentes que desea agregar a la comanda: ";
    cin >> cantidadProductos;

    /// Verificar que la cantidad de productos no sea mayor que el tamaño máximo
    if (cantidadProductos <= 0 || cantidadProductos > 100) {
        cout << "La cantidad de productos debe ser un numero entre 1 y 100." << endl;
        return;  // Salir de la función si la cantidad de productos es incorrecta
    }

    /// Cargar los productos
    for (int i = 0; i < cantidadProductos; i++) {
        int idProducto, cantidad;

        cout << "\nProducto " << i + 1 << " de " << cantidadProductos << endl;
        cout << "Ingrese el ID del producto: ";
        cin >> idProducto;

        /// Buscar el producto con el ID proporcionado en el archivo de productos
        Producto producto = archivoP.buscarProducto(idProducto);  // Usamos el método buscarProducto()
        if (producto.getIdProducto() == 0) {
            cout << "Producto no encontrado. Intente nuevamente." << endl;
            i--;  // Decrementar para repetir la carga de este producto
            continue;
        }

        /// Asignar el producto al arreglo de productos de la comanda
        productos[i] = producto;

        /// Solicitar la cantidad del producto
        cout << "Ingrese la cantidad de este producto: ";
        cin >> cantidad;

        /// Asegurarse de que la cantidad sea válida
        if (cantidad <= 0) {
            cout << "La cantidad debe ser mayor que 0." << endl;
            i--;  // Repetir el ingreso para este producto
            continue;
        }

        /// Asignamos la cantidad al producto en la comanda
        cantidades[i] = cantidad;  // Guardamos la cantidad del producto
    }

    /// Llamamos a la función que asigna fecha y hora
    cargarFechaHora();

    // Establecer el ID de la comanda
    idComanda = archivoC.obtenerIdRegistro();  // Esto es para obtener un nuevo ID de comanda de los registros
}
