#include <iostream>
#include "MenuMesas.h"
#include "ArchivoProductos.h"

using namespace std;

void mostrarMenuMesas() {
    /// MENU MESAS
    system("cls");
    system("color 20");
    int opcion, pos;
    Mesa mesa;
    ArchivoMesas archivoM;

    do {
        system("cls");
        cout << "***** MENU MESAS *****" << endl;
        cout << "1) Cargar nueva mesa" << endl;
        cout << "2) Listar mesas" << endl;
        cout << "3) Buscar mesa" << endl;
        cout << "4) Modificar mesa" << endl;
        cout << "5) Cerrar mesa" << endl;
        cout << "0) Volver al MENU principal" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

            switch (opcion) {
            case 1: {
                    int numMesa;
                    do{
                    system("cls");
                    cout << "Ingrese el ID de la mesa del 1-20, (0 para volver): ";
                    cin >> numMesa;
                    if(numMesa==0)return;
                    if(numMesa<1||numMesa>20){
                        cout<<"Mesa fuera de rango, intente nuevamente..."<<endl;
                        system("pause");
                        }
                    }while(numMesa<1||numMesa>20);
                /// Verificar si la mesa ya existe y está ocupada
                if (archivoM.buscarRegistro(numMesa) != -1) {
                    cout << "La mesa ya existe y esta ocupada." << endl;
                    system("pause");
                    break;  /// Salimos porque no se puede gestionar una mesa ocupada
                }

                /// Si la mesa no existe, crear una nueva
                cout << "La mesa no existe. Se creara una nueva mesa." << endl;
                system("pause");
                mesa = Mesa();  /// Crear una nueva instancia con estado en false
                mesa.setIdMesa(numMesa);  /// Asignar el número de mesa

                while (true) {
                    cout << "Se mostrara la carta. Seleccionar los ID:" << endl;
                    system("pause");

                    Producto producto = archivoM.seleccionarProducto();  /// Seleccionar producto

                    int cantidad;
                    cout << "Ingrese la cantidad de productos a pedir: ";
                    cin >> cantidad;

                    mesa.setProducto(producto, cantidad);  /// Agregar producto a la mesa

                    cout << "El saldo actual de la mesa es: $" << mesa.getSaldo() << endl;

                    char opcion;
                    cout << "¿Desea agregar otro producto? (s/n): ";
                    cin >> opcion;
                    if (opcion == 'n' || opcion == 'N') break;
                }

                /// Marcar la mesa como ocupada y grabarla
                mesa.setEstado(true);  // Ahora la mesa está ocupada
                archivoM.grabarRegistroMesas(mesa);

                cout << "Mesa registrada con exito." << endl;
                system("pause");
                break;
            }

            case 2:
                system("cls");
                archivoM.listarRegistros();  /// Listar todas las mesas
                break;

            case 3: {
                system("cls");
                cout << "Ingrese el numero de mesa a buscar, (0 para volver): ";
                int numMesa;
                cin >> numMesa;
                if(numMesa==0)break;
                pos = archivoM.buscarRegistro(numMesa);  // Buscar mesa por número
                if (pos == -1) {
                    cout << "Mesa no encontrada." << endl;
                    system("pause");
                } else {
                    archivoM.leerRegistro(pos);  /// Mostrar la mesa encontrada
                }
                break;
            }

                case 4: {

                    system("cls");
                    cout << "Ingrese el numero de mesa a modificar, (0 para volver): ";
                    int numMesa;
                    cin >> numMesa;
                    if (numMesa == 0) break;

                    int pos = archivoM.buscarRegistro(numMesa);  // Buscar la mesa
                    if (pos == -1) {
                        cout << "Mesa no encontrada." << endl;
                        system("pause");
                    } else {
                        mesa = archivoM.leerRegistro(pos);

                        // Submenú para elegir entre agregar o eliminar un producto
                        int opcionSubmenu = -1;
                        while (opcionSubmenu != 0) {
                            system("cls");
                            cout << "MODIFICANDO LA MESA: " << numMesa << endl;
                            cout << "1) Agregar producto" << endl;
                            cout << "2) Eliminar producto" << endl;
                            cout << "0) Volver al menu anterior" << endl;
                            cout << "Ingrese una opcion: ";
                            cin >> opcionSubmenu;

                            switch (opcionSubmenu) {
                                    case 1: {
                                        /// Agregar producto a la mesa
                                        cout << "Ingrese el ID del producto que desea agregar: ";
                                        int productoId;
                                        cin >> productoId;

                                        /// Crear un objeto de ArchivoProductos para buscar el producto
                                        ArchivoProductos archivoP;
                                        Producto productoSeleccionado;

                                        if (!archivoP.buscarProductoPorId(productoId, productoSeleccionado)) {
                                            /// Método buscarProductoPorId busca el producto en el archivo y lo almacena en productoSeleccionado
                                            cout << "Producto no encontrado. Verifique el ID ingresado." << endl;
                                            break;
                                        }

                                        cout << "Producto seleccionado: " << productoSeleccionado.getDescripcion() << endl;

                                        /// Preguntar la cantidad del producto a agregar
                                        cout << "Ingrese la cantidad que desea agregar de este producto: ";
                                        int cantidad;
                                        cin >> cantidad;

                                        if (cantidad <= 0) {
                                            cout << "Cantidad no valida. Debe ser mayor a 0." << endl;
                                            break;
                                        }

                                        /// Crear un objeto de ArchivoMesas para manejar la mesa actual
                                        ArchivoMesas archivoM;
                                        Mesa mesa;

                                        if (!archivoM.buscarMesaPorId(numMesa, mesa)) {
                                            /// Método buscarMesaPorId busca la mesa con el ID numMesa
                                            cout << "Mesa no encontrada. Verifique el numero de mesa." << endl;
                                            break;
                                        }

                                        mesa.agregarProducto(productoSeleccionado, cantidad);

                                        /// Actualizar el registro de la mesa en el archivo
                                        if (!archivoM.modificarRegistro(mesa)) {
                                            /// Método modificarRegistro actualiza el registro de la mesa en el archivo
                                            cout << "Error al actualizar los datos de la mesa." << endl;
                                            system("pause");
                                            break;
                                        }

                                        cout << "Producto agregado con exito a la mesa ID: " << numMesa
                                             << " en cantidad de: " << cantidad << endl;
                                        break;
                                    }

                                    case 2: {
                                        cout << "Ingrese el ID del producto que desea eliminar: ";
                                        int productoId;
                                        cin >> productoId;

                                        ArchivoProductos archivoP;
                                        Producto productoSeleccionado;

                                        if (!archivoP.buscarProductoPorId(productoId, productoSeleccionado)) {
                                            cout << "Producto no encontrado. Verifique el ID ingresado." << endl;
                                            system("pause");
                                            break;
                                        }

                                        ArchivoMesas archivoM;
                                        Mesa mesa;

                                        if (!archivoM.buscarMesaPorId(numMesa, mesa)) {
                                            cout << "Mesa no encontrada. Verifique el numero de mesa." << endl;
                                            break;
                                        }

                                        /// Intentar eliminar el producto
                                        mesa.eliminarProducto(productoSeleccionado);

                                        /// Actualizar la mesa en el archivo
                                        if (!archivoM.modificarRegistro(mesa)) {
                                            cout << "Error al actualizar los datos de la mesa." << endl;
                                            system("pause");
                                            break;
                                        }

                                        cout << "Producto eliminado con exito de la mesa ID: " << numMesa << endl;
                                        system("pause");
                                        break;
                                    }

                                    case 0:
                                        cout << "Volviendo al menu anterior..." << endl;
                                        system("pause");
                                        break;

                                    default:
                                        cout << "Opcion no valida. Intente nuevamente." << endl;
                                        system("pause");
                                        break;
                                }
                            }
                        }
                }
                break;
                case 5: {
                    system("cls");
                    cout << "Ingrese el numero de mesa a cerrar, (0 para volver): ";
                    int numMesa;
                    cin >> numMesa;
                    if (numMesa == 0) break;

                    Mesa mesa;
                    bool mesaEncontrada = archivoM.buscarMesaPorId(numMesa, mesa);
                    if (!mesaEncontrada) {
                        cout << "Mesa no encontrada." << endl;
                    } else {
                        // Guardar el saldo actual de la mesa en memoria (sin guardarlo en archivo)
                        float saldoGuardado = mesa.getSaldo();
                        cout << "Saldo actual de la mesa " << numMesa << ": $" << saldoGuardado << endl;

                        // Preguntar al usuario si desea sumar o restar saldo
                        cout << "Desea restar o sumar saldo? (1- Sumar, 2- Restar, 0- No modificar): ";
                        int opcion;
                        cin >> opcion;

                        float cantidad;
                        if (opcion == 1) {
                            cout << "Ingrese el monto a sumar a la mesa: $";
                            cin >> cantidad;
                            mesa.setSaldo(mesa.getSaldo() + cantidad);
                            cout << "Nuevo saldo de la mesa " << numMesa << ": $" << mesa.getSaldo() << endl;
                        } else if (opcion == 2) {
                            cout << "Ingrese el monto a restar de la mesa: $";
                            cin >> cantidad;

                            if (cantidad > mesa.getSaldo()) {
                                cout << "El monto a restar es mayor que el saldo actual." << endl;
                            } else {
                                mesa.setSaldo(mesa.getSaldo() - cantidad);  // Restar saldo en memoria
                                cout << "Nuevo saldo de la mesa " << numMesa << ": $" << mesa.getSaldo() << endl;
                            }
                        }

                        cout << "\nGenerando ticket...\n";
                        mesa.generarTicket(saldoGuardado);  // Llamada al método para generar el ticket con el saldo original
                        system("pause");
                        system("cls");
                        system("color 20");

                        // Ahora cerramos la mesa (sin guardar el saldo modificado en el archivo)
                        archivoM.eliminarRegistro(numMesa);  // Eliminamos el registro de la mesa
                        cout << "Mesa " << numMesa << " cerrada correctamente." << endl;
                    }
                    system("pause");
                    break;
                }

            case 0:
                cout << "Volviendo al menu principal" << endl;
                system("pause");
                break;

            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
                system("pause");
                break;
        }
    } while (opcion != 0);
}







