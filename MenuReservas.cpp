#include <iostream>
#include "Reserva.h"
#include "ArchivoReservas.h"
#include "Menues.h"
#include "MenuReservas.h"
using namespace std;

void mostrarMenuReservas() {
    /// MENU RESERVAS
    system("cls");
    system("color 20");
    int opcion, pos;
    Reserva obj;
    ArchivoReservas archivoR;

    do {
        system("cls");
        cout << "***** MENU RESERVAS *****" << endl;
        cout << "1) Cargar nueva reserva" << endl;
        cout << "2) Listar reservas" << endl;
        cout << "3) Buscar reserva" << endl;
        cout << "4) Modificar reserva" << endl;
        cout << "5) Eliminar reserva" << endl;
        cout << "0) Volver al MENU principal" << endl;
        cin >> opcion;

        switch(opcion) {
            case 1: {
                obj.cargarReserva(archivoR);
                if (obj.getDniCliente() == 0 || !obj.getFechaReserva().getDia()) break;
                archivoR.grabarRegistroReservas(obj);
                break;
            }

            case 2:
                archivoR.listarReservas();
                break;

            case 3: {
                archivoR.buscarRegistro();
                break;
            }

            case 4: {
                archivoR.modificarRegistro();
                break;
            }

            case 5: {
                archivoR.eliminarRegistro();
                break;
            }
            case 0:
                cout << "Volviendo al menu principal" << endl;
                system("pause");
                break;
        }
    } while (opcion != 0);
}




