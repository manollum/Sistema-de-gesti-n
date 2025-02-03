#pragma once
#include <iostream>

using namespace std;

class ArchivoProductos;

class Producto{
protected:
int idProducto; ///Si existe el idProducto en el archivo no debe poder asignarse a otro producto (si puede modificarse)
char descripcion[50]; //nombre del producto (puede ser comida o bedida)
double precio;
int tipoProducto; /// 1-comida. 2-bebida. 3- guarnicion
bool estado;

public:
Producto() :estado(true){}

void setDescripcion(const char * _descripcion);
void setPrecio(double _precio);
void setTipoProducto(int _tipo);
void setEstado(bool _estado);
void cargarProducto(ArchivoProductos &archivoP);
void mostrarProducto();


int getIdProducto(){return idProducto;}
const char * getDescripcion(){return descripcion;}
double getPrecio() const {return precio;}
int getTipoProducto(){return tipoProducto;}
bool getEstado(){return estado;}


};

