#include "MenuReportes.h"
#include <iostream>
using namespace std;

void mostrarMenuReportes() {
    system("cls");
    system("color 20");
    int opcion;
    float e=0.0f;
    float i=0.0f;

    do {
        system("cls");
        cout << "***** MENU REPORTES *****" << endl;
        cout << "1) Egresos del dia" << endl;
        cout << "2) Ingresos del dia" << endl;
        cout << "3) Balance del dia" << endl;
        cout << "4) Resetear todos los saldos" <<endl;
        cout << "0) Volver al MENU principal" << endl;
        cin >> opcion;

        switch(opcion) {
            case 1: {
                system("cls");
                cout << "Mostrando los egresos del dia..." << endl;
                calcularEgresosSueldos();
                system("pause");
                break;
            }

            case 2: {
                system("cls");
                cout << "Mostrando los ingresos del dia..." << endl;
                calcularSaldoMesasActivas();
                system("pause");
                break;
            }



            case 3: {
                e=calcularEgresosSueldos();
                i=calcularSaldoMesasActivas();
                cout << "El balance del dia hasta el momento es de: $"<< i-e <<endl;
                system("pause");
                break;
            }

            case 4: {
                resetearSaldos();
                break;
            }

            case 0:
                cout << "Volviendo al menu principal" << endl;
                system("pause");
                break;
        }
    } while (opcion != 0);
}

