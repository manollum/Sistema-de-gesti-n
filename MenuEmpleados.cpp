#include <iostream>
#include <cstring>
#include "Fecha.h"
#include "Login.h"
#include "Persona.h"
#include "Cliente.h"
#include "Empleado.h"
#include "ArchivoEmpleados.h"
#include "ArchivoProductos.h"
#include "ArchivoReservas.h"
#include "ArchivoMesas.h"
#include "ArchivoComanda.h"
#include "Comanda.h"
#include "Producto.h"
#include "Reserva.h"
#include "Menues.h"
#include "Mesa.h"
#include "MenuEmpleados.h"

using namespace std;

void mostrarMenuEmpleados(){
/// MENU EMPLEADOS

system("color 20");
int pos, opcion;
Empleado obj;
ArchivoEmpleados archivoE;

do{
    system("cls");
    cout << "***** MENU EMPLEADOS *****" << endl;
    cout << "1) Cargar empleado" << endl;
    cout << "2) Listar empleados" << endl;
    cout << "3) Buscar empleado" << endl;
    cout << "4) Modificar empleado" << endl;
    cout << "5) Dar de baja un empleado" << endl;
    cout << "6) Dar de alta un empleado" << endl;
    cout << "7) Listar empleados inactivos" << endl;
    cout << "0) Volver al MENU principal" << endl;
    cin >> opcion;

    switch(opcion){
        case 1:
        obj.cargarEmpleado(archivoE);
        if(obj.getDni()==0)break;
        archivoE.grabarRegistro(obj);
        break;
        case 2:
        archivoE.listarRegistros();
        break;
        case 3:
        pos = archivoE.buscarRegistro();
        if (pos == -2) break;
        archivoE.leerRegistro(pos);
        break;
        case 4:
        pos = archivoE.buscarRegistro();
        if (pos == -2) break;
        archivoE.modificarRegistro(pos);
        break;
        case 5:
        archivoE.bajaRegistro();
        break;
        case 6:
        archivoE.altaRegistro();
        break;
        case 7:
        archivoE.listarRegistrosInactivos();
        break;
        case 0:
        cout << "Volviendo al menu principal" << endl;
        system("pause");
        return;
        }
        }while(opcion!=0);

}


