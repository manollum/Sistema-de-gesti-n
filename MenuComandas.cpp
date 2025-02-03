#include "MenuComandas.h"

void mostrarMenuComandas() {
    system("cls");
    system("color 20");
    int opcion, pos;
    Comanda obj;
    ArchivoComandas archivoC;
    ArchivoProductos archivoP;

    do {
        system("cls");
        cout << "***** MENU COMANDAS *****" << endl;
        cout << "1) Cargar nueva comanda" << endl;
        cout << "2) Listar comandas" << endl;
        cout << "3) Resetear comandas" << endl;
        cout << "0) Volver al MENU principal" << endl;
        cin >> opcion;

        switch(opcion) {
            case 1: {
                obj.cargarComanda(archivoC, archivoP);
                if (obj.getIdComanda() == 0) break;  /// Si no se carga una comanda valida, salimos del caso
                archivoC.grabarRegistro(obj);  /// Grabar la comanda en el archivo de comandas
                break;
            }

            case 2:
                archivoC.listarRegistros();  /// Listar todas las comandas registradas
                break;

            case 3:
                archivoC.resetearComandas();  // Resetear las comandas
                system("pause");
                break;

            case 0:
                cout << "Volviendo al menu principal" << endl;
                system("pause");
                break;
        }
    } while (opcion != 0);
}


