#include <iostream>
#include "Menues.h"
#include "MenuEmpleados.h"
#include "MenuProductos.h"
#include "MenuReservas.h"
#include "MenuMesas.h"
#include "MenuComandas.h"
#include "MenuReportes.h"

using namespace std;

void mostrarMenuPrincipal() {
    int opcion;


    do {
        system("color 60");
        system("cls");
        cout << "***** MENU PRINCIPAL *****" << endl;
        cout << "1) Empleados" << endl;
        cout << "2) Productos" << endl;
        cout << "3) Reservas" << endl;
        cout << "4) Mesas" << endl;
        cout << "5) Comandas" << endl;
        cout << "6) Reportes" << endl;
        cout << "0) Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                mostrarMenuEmpleados();
                break;
            case 2:
                mostrarMenuProductos();
                break;
            case 3:
                mostrarMenuReservas();
                break;
            case 4:
                mostrarMenuMesas();
                break;
            case 5:
                mostrarMenuComandas();
                break;
            case 6:
                mostrarMenuReportes();
                break;
            case 0:
                cout << "Saliendo del sistema..." << endl;
                system("pause");
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente." << endl;
                system("pause");
                break;
        }

    } while(opcion != 0);
}
