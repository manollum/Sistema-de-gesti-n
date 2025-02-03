#include <iostream>
#include "Producto.h"
#include "ArchivoProductos.h"
#include "Menues.h"
#include "MenuProductos.h"

using namespace std;

void mostrarMenuProductos(){
/// MENU PRODUCTOS

system("cls");
system("color 20");
int pos, opcion;
Producto obj;
ArchivoProductos archivoP;

do{
    system("cls");
    cout << "***** MENU PRODUCTOS *****" << endl;
    cout << "1) Cargar producto" << endl;
    cout << "2) Listar productos" << endl;
    cout << "3) Buscar producto" << endl;
    cout << "4) Modificar producto" << endl;
    cout << "5) Dar de baja producto" << endl;
    cout << "0) Volver al MENU principal" << endl;
    cin >> opcion;

    switch(opcion){
        case 1:
        obj.cargarProducto(archivoP);
        if(obj.getDescripcion()[0]=='0')break;
        archivoP.grabarRegistro(obj);
        break;

        case 2:
        archivoP.listarRegistros();
        break;

        case 3:
        pos = archivoP.buscarRegistro();
        if(pos==-2)break;
        archivoP.leerRegistro(pos);
        break;

        case 4:
        pos = archivoP.buscarRegistro();
        if(pos==-2)break;
        archivoP.modificarRegistro(pos);
        break;

        case 5:
        system("cls");
        int id;
        cout << "Ingrese el ID del producto a dar de baja, (0 para volver al MENU anterior): ";
        cin >> id;
        if(id==0)break;
        archivoP.darDeBaja(id);
        break;

        case 0:
        cout << "Volviendo al menu principal" << endl;
        system("pause");
        break;;
        }
        }while(opcion!=0);
        }


