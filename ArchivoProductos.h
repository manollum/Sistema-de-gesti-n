#pragma once
#include <cstring>

class Producto; ///declaracion anticipada. Esto permite que la clase conozca a "Producto", no así a sus metodos y propiedades. Eso se logra unicamente con #include (esto se da en un cpp aparte)

class ArchivoProductos{
private:
char nombre[20];
int tam;

public:
ArchivoProductos(const char *_nombre = "productos.dat");


bool grabarRegistro(Producto obj);
int obtenerIdRegistro();
int buscarRegistro();
bool leerRegistro(int pos);
bool listarRegistros();
bool modificarRegistro(int pos);
bool bajaRegistro();
bool altaRegistro();
bool darDeBaja(int idProducto);
Producto buscarProducto(int idProducto);
bool buscarProductoPorId(int idProducto, Producto &producto);
};
