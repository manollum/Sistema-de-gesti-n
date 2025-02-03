#include <iostream>
#include <cstring>
#include "Producto.h"
#include "ArchivoProductos.h"

using namespace std;


void Producto::setPrecio(double _precio){
precio = _precio;
}

void Producto::setDescripcion(const char *_descripcion){
strcpy(descripcion, _descripcion);
}

void Producto::setEstado(bool _estado){
estado = _estado;
}

void Producto::setTipoProducto(int _tipo){
tipoProducto = _tipo;
}

void Producto::cargarProducto(ArchivoProductos &archivoP){
system("cls");

char _descripcion[50];
double _precio;
int _tipo;
idProducto = archivoP.obtenerIdRegistro();

cout << "Ingrese el nombre del producto, (0 para volver al MENU anterior): ";
cin.ignore();
cin.getline(_descripcion, 49);
descripcion[0] = _descripcion[0];
if(descripcion[0]=='0')return;
cout << "Ingrese el valor del producto: ";
cin >> _precio;
cout << "Ingrese el tipo de producto:" << endl << "1) Plato" << endl << "2) Guarnicion" << endl << "3) Bebida" << endl;
cin >> _tipo;

strcpy(descripcion, _descripcion);
precio = _precio;
tipoProducto = _tipo;
}

void Producto::mostrarProducto(){
if (!estado) {
    cout << "Producto dado de baja." << endl;
    return;
}
cout << "ID de producto: " << idProducto << endl;
cout << "Descripcion: " << descripcion << endl;
cout << "Valor: " << precio << endl;
cout << "Tipo de producto: ";

switch(tipoProducto){
case 1:
cout << "Plato" << endl;
break;

case 2:
cout << "Guarnicion" << endl;
break;

case 3:
cout << "Bebida" << endl;
break;
    }
}





