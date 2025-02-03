#include "Mesa.h"  // Asegúrate de que la clase Mesa esté definida antes de incluirla
#include "Producto.h"
#include "ArchivoMesas.h"
#include "ArchivoProductos.h"
#include "Reportes.h"
#include <cstring>

using namespace std;





ArchivoMesas::ArchivoMesas(const char *_nombre) {
    strncpy(nombre, _nombre, 19);
    nombre[19] = '\0';
    tam = sizeof(Mesa);
}


    /// Graba un nuevo registro de mesa en el archivo
bool ArchivoMesas::grabarRegistroMesas(Mesa obj) {
    Mesa aux;
    FILE* pMesas;
    pMesas = fopen(nombre, "ab+");  // Abrir en modo binario para añadir al final

    if (pMesas == nullptr) {
        cout << "No se pudo establecer la conexion." << endl;
        return false;
    }

    bool mesaExistente = false;

    // Recorremos el archivo para verificar si ya existe una mesa con el mismo ID
    while (fread(&aux, tam, 1, pMesas)) {
        if (aux.getIdMesa() == obj.getIdMesa()) {
            mesaExistente = true;
            break;  // Encontramos la mesa existente, salimos del bucle
        }
    }

    if (mesaExistente) {
        /// Si la mesa ya existe, simplemente actualizamos los productos
        fseek(pMesas, -(long)tam, SEEK_CUR);  // Mover el puntero a la posición del último registro de la mesa
        fwrite(&obj, tam, 1, pMesas);  // Escribir el nuevo estado de la mesa con los productos actualizados
        cout << "Mesa con ID " << obj.getIdMesa() << " actualizada con nuevos productos." << endl;
    } else {
        // Si la mesa no existe, la grabamos al final del archivo
        fwrite(&obj, tam, 1, pMesas);  // Escribimos la nueva mesa con sus productos
        cout << "Mesa cargada con exito." << endl;
    }

    fclose(pMesas);
    return true;
}

    /// Busca una mesa por ID y devuelve la posición en el archivo (registro)


int ArchivoMesas::buscarRegistro(int numMesa) {
    Mesa aux;
    FILE* pMesas = fopen(nombre, "rb");  // Abrir en modo lectura binaria
    if (pMesas == nullptr) {
        cout << "Error al abrir el archivo." << endl;
        return -1;  // Archivo no disponible
    }

    // Iteramos por todos los registros en el archivo
    while (fread(&aux, sizeof(Mesa), 1, pMesas)) {
        // Verificamos si el ID de la mesa coincide y si está activa
        if (aux.getIdMesa() == numMesa && aux.getEstado() == true) {
            fclose(pMesas);  // Cerramos el archivo antes de salir
            return aux.getIdMesa();  // Devolvemos el ID de la mesa encontrada
        }
    }

    fclose(pMesas);  // Cerramos el archivo después de recorrerlo
    return -1;  // No se encontró la mesa
}


    /// Lista todos los registros de mesas en el archivo
bool ArchivoMesas::listarRegistros() {
    system("cls");
    FILE *pMesas;
    Mesa obj;
    pMesas = fopen(nombre, "rb");

    if (pMesas == nullptr) {
        cout << "El archivo no se pudo encontrar o no existen registros cargados." << endl;
        system("pause");
        system("cls");
        return false;
    }

    /// Leemos y mostramos todos los registros de mesas
    while (fread(&obj, tam, 1, pMesas)) {
        /// Solo mostramos la mesa si está activa (estado == true) y su ID es distinto de -1
        if (obj.getEstado() && obj.getIdMesa() != -1) {
            obj.mostrarMesa();  /// Asumo que 'mostrarMesa()' es un método de la clase Mesa
        }
    }

    system("pause");
    system("cls");
    fclose(pMesas);
    return true;
}

    /// Modifica un registro de mesa en la posición indicada
bool ArchivoMesas::modificarRegistro(int pos, Mesa obj) {
        FILE *pMesas;
        pMesas = fopen(nombre, "rb+");
        if (pMesas == nullptr) {
            cout << "No se pudo abrir el archivo para modificar." << endl;
            system("pause");
            return false;
        }

        // Movemos el puntero al registro en la posición indicada
        fseek(pMesas, pos * tam, SEEK_SET);
        int escribio = fwrite(&obj, tam, 1, pMesas);

        fclose(pMesas);

        if (escribio){
            cout << "Mesa modificada con exito." << endl;
        }
        else{
            cout << "No se pudo modificar la mesa." << endl;

        }
        system("pause");
        system("cls");
        return escribio;
    }

    /// Elimina un registro de mesa en la posición indicada (marca como false)


bool ArchivoMesas::eliminarRegistro(int idMesa) {
    FILE *pMesas = fopen(nombre, "rb+");  // Abrimos el archivo de mesas en modo lectura/escritura binaria
    if (pMesas == nullptr) {
        cout << "No se pudo abrir el archivo para eliminar." << endl;
        return false;
    }

    Mesa mesa;
    bool encontrado = false;

    /// Leemos todos los registros de mesas
    while (fread(&mesa, tam, 1, pMesas)) {
        if (mesa.getIdMesa() == idMesa) {  /// Verificamos si encontramos la mesa por ID
            float saldoActual = mesa.getSaldo();  /// Obtenemos el saldo de la mesa
            guardarIngresoDiario(saldoActual);    /// Guardamos el saldo en el archivo de ingresos
            mesa.setEstado(false);               /// Cambiamos el estado de la mesa a 'false' (inactiva)
            mesa.setIdMesa(-1);                  /// Establecemos el ID de la mesa a -1 para marcarla como eliminada
            fseek(pMesas, -tam, SEEK_CUR);       /// Nos posicionamos en el registro actual
            fwrite(&mesa, tam, 1, pMesas);       /// Sobrescribimos el registro con el nuevo estado e ID
            encontrado = true;
            break;  /// Salimos del bucle después de encontrar y actualizar la mesa
        }
    }

    fclose(pMesas);

    if (encontrado) {
        cout << "Mesa cerrada con exito." << endl;
        return true;
    } else {
        cout << "No se encontro la mesa con ID: " << idMesa << endl;
        return false;
    }
}


Producto ArchivoMesas::seleccionarProducto() {
    system("cls");
    int idProducto;
    Producto prod;
    ArchivoProductos archivoP;

    /// Mostrar productos disponibles
    archivoP.listarRegistros();

    /// Solicitar al usuario que seleccione un producto por su ID
    cout << "Ingrese el ID del producto que desea asociar a la mesa: ";
    cin >> idProducto;

    /// Validación del ID del producto
    if (idProducto == 0) {
        cout << "Operacion cancelada." << endl;
        system("pause");
        return prod;  // Retorna un objeto Producto vacío (por defecto)
    }

    // Buscar el producto seleccionado
    prod = archivoP.buscarProducto(idProducto);

    if (prod.getIdProducto() == 0) {
        cout << "Producto no encontrado." << endl;
        system("pause");
        return prod;  // Retorna un objeto Producto vacío si no se encuentra
    }

    return prod;  // Retorna el producto encontrado
}




Mesa ArchivoMesas::leerRegistro(int idMesaBuscada) {
    system("cls");
    Mesa obj; // Objeto Mesa para almacenar los datos leídos
    FILE *pMesas;

    // Abrimos el archivo en modo de lectura binaria
    pMesas = fopen(nombre, "rb");
    if (pMesas == nullptr) {
        cout << "El archivo no se pudo encontrar o no existen registros." << endl;
        system("pause");
        system("cls");
        return obj; // Devolvemos un objeto vacío si no se pudo abrir
    }
// Recorremos el archivo buscando el registro con el idMesa solicitado
    while (fread(&obj, sizeof(Mesa), 1, pMesas)) {
        if (obj.getIdMesa() == idMesaBuscada) {
            // Mostramos la información de la mesa
            cout << "Mesa ID: " << obj.getIdMesa() << endl;

            // Mostramos los productos asociados, si los hay
            int cantidadProductos = obj.getCantidadProductos();
            if (cantidadProductos > 0) {
                cout << "Productos asociados a la mesa:" << endl;
                for (int i = 0; i < cantidadProductos; ++i) {
                    Producto prod = obj.getProducto(i); // Obtenemos el producto

                    if (prod.getEstado()) { // Solo mostramos los productos activos
                        cout << "Producto " << (i + 1) << ":" << endl;
                        cout << "ID Producto: " << prod.getIdProducto() << endl;
                        cout << "Descripcion: " << prod.getDescripcion() << endl;
                        cout << "Precio: " << prod.getPrecio() << " ARS" << endl;
                        cout << "Cantidad: " << obj.getCantidadProducto(i) << endl;
                        cout << "Tipo de Producto: "
                             << (prod.getTipoProducto() == 1 ? "Plato" :
                                (prod.getTipoProducto() == 2 ? "Bebida" : "Guarnicion")) << endl;
                        cout << "-----------" << endl;
                    }
                }
                cout << "SALDO: $" << obj.getSaldo() << endl;

            } else {
                cout << "No hay productos asociados a esta mesa." << endl;
            }

            system("pause");
            fclose(pMesas); // Cerramos el archivo
            return obj; // Devolvemos el objeto encontrado
        }
    }

    // Si no se encontró la mesa
    cout << "No se encontro una mesa con el ID " << idMesaBuscada << endl;
    system("pause");
    fclose(pMesas); // Cerramos el archivo
    return obj; // Devolvemos un objeto vacío
}



bool ArchivoMesas::buscarMesaPorId(int idMesa, Mesa &mesa) {
    // Abrimos el archivo en modo lectura binaria
    FILE *pMesas = fopen(nombre, "rb");
    if (pMesas == nullptr) {
        cout << "No se pudo abrir el archivo de mesas." << endl;
        return false;
    }

    Mesa aux;

    // Recorremos el archivo leyendo los registros
    while (fread(&aux, sizeof(Mesa), 1, pMesas)) {
        if (aux.getIdMesa() == idMesa) {
            // Si encontramos la mesa, la devolvemos a través de la referencia
            mesa = aux;
            fclose(pMesas);
            return true;
        }
    }

    // Si no se encontró la mesa, cerramos el archivo y devolvemos false
    fclose(pMesas);
    return false;
}




bool ArchivoMesas::modificarRegistro(Mesa &mesa) {
    FILE *pMesas = fopen(nombre, "rb+");  /// Abrir el archivo en modo lectura/escritura binaria
    if (pMesas == nullptr) {
        cout << "No se pudo abrir el archivo para modificar el registro." << endl;
        system("pause");
        return false;
    }

    Mesa temp;
    bool encontrado = false;

    /// Recorrer el archivo para encontrar el registro correspondiente
    while (fread(&temp, tam, 1, pMesas)) {
        if (temp.getIdMesa() == mesa.getIdMesa()) {  /// Comparar por ID de la mesa
            fseek(pMesas, -tam, SEEK_CUR);  /// Retroceder el puntero al inicio del registro encontrado
            fwrite(&mesa, tam, 1, pMesas);  /// Sobrescribir el registro con los nuevos datos
            encontrado = true;
            break;
        }
    }

    fclose(pMesas);

    if (encontrado) {
        cout << "Registro de la mesa con ID " << mesa.getIdMesa() << " modificado correctamente." << endl;
        system("pause");
    } else {
        cout << "No se encontro una mesa con el ID especificado." << endl;
        system("pause");
    }

    return encontrado;
}
