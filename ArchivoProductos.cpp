#include <iostream>
#include "ArchivoProductos.h"
#include "Producto.h"

    ///Modo "rb+": Abre el archivo para lectura y escritura en modo binario, pero falla si el archivo no
    ///existe. Esto es útil solo si tenes la certeza de que el archivo ya fue creado.

    ///Modo "ab+": Abre el archivo en modo binario para añadir datos al final, pero también permite leer
    ///desde él. Este modo crea el archivo si no existe, lo cual es conveniente para un método como
    ///calcularIdRegistros que depende de que el archivo esté disponible

using namespace std;

ArchivoProductos::ArchivoProductos(const char *_nombre){
strncpy(nombre, _nombre, 19);
tam = sizeof(Producto);
}

int ArchivoProductos::obtenerIdRegistro(){
    int cant = 0;
    FILE *pProductos;

    pProductos = fopen(nombre, "ab+");
    if (pProductos == nullptr) {
        cout << "Algo salio mal. Volviendo al menu." << endl;
        system("pause");
        system("cls");
        return -1;  // Error al abrir el archivo
    }

    // Leemos el archivo registro por registro
    Producto producto;
    while(fread(&producto, sizeof(Producto), 1, pProductos)){
        cant++;  // Contamos los registros
    }

    fclose(pProductos);

    if (!cant) {
        return 1;  // Si no hay registros, el primer ID será 1
    }

    return cant + 1;  // Devuelve el siguiente ID (cantidad de registros + 1)
}


bool ArchivoProductos::grabarRegistro(Producto obj){
FILE * pProductos;

pProductos = fopen(nombre, "ab");
if(pProductos==nullptr){
   cout << "No se pudo establecer la conexion." << endl;
    return false;
    }

int escribio = fwrite(&obj, tam, 1, pProductos);

fclose(pProductos);

if(escribio){
    cout << "Registro grabado con exito" <<endl;
    system("pause");
    system("cls");
    return true;
}

else
cout << "No se pudo grabar el registro" <<endl;
 system("pause");
    system("cls");
    return -1;

}

int ArchivoProductos::buscarRegistro() {
system("cls");
FILE *pProductos = fopen(nombre, "rb");
if (!pProductos) {
    cout << "No se pudo establecer la conexion." <<endl;
    system("pause");
    system("cls");
    return false;
}

int id;
cout << "Ingrese el ID a buscar (0 para volver al menu anterior): ";
cin >> id;
if (id == 0) return -2;

int pos = 0;
Producto obj;
while (fread(&obj, tam, 1, pProductos)) {
    if (obj.getIdProducto() == id && obj.getEstado()) { // Verificar estado
        fclose(pProductos);
        return pos;
    }
    pos++;
}

fclose(pProductos);
cout << "No se encontro un producto activo con ese ID." <<endl;
return -1;
}



bool ArchivoProductos::listarRegistros() {
system("cls");
Producto obj;

FILE *pProductos = fopen(nombre, "rb");
if (!pProductos) {
    cout << "No se encontraron registros en el archivo." << endl;
    system("pause");
    system("cls");
    return false;
}

while (fread(&obj, tam, 1, pProductos)) {
    if (obj.getEstado()) { // Muestra solo archivos activos
        obj.mostrarProducto();
        cout <<endl;
    }
}

fclose(pProductos);
system("pause");
system("cls");
return true;
}



bool ArchivoProductos::leerRegistro(int pos){
system("cls");

if(pos==-1){
cout << "El ID no se encuentra en los registros." << endl;
system("pause");
system("cls");
return -1;
}

Producto obj;
FILE *pProductos;
pProductos = fopen(nombre, "rb");

if(pProductos==nullptr){
    cout << "No se pudo establecer la conexion." << endl;
    system("cls");
    return false;
}

fseek(pProductos, tam * pos, 0);

int leyo = fread(&obj, tam, 1, pProductos);

if(leyo)
obj.mostrarProducto();

else
cout << "No se encuentran productos con ese ID" << endl;

system("pause");
system("cls");
fclose(pProductos);

return leyo;
}



bool ArchivoProductos::modificarRegistro(int pos){

if(pos == -1){
cout << "El ID no se encuentra en los registros." << endl;
system("pause");
system("cls");
return -1;
}

FILE *pProductos;
pProductos = fopen(nombre, "rb+");

if(pProductos==nullptr){
    cout << "No se pudo establecer la conexion." <<endl;
    system("cls");
    return false;
    }

fseek(pProductos, pos * tam, 0);

Producto obj;

int leyo = fread(&obj, tam, 1, pProductos);

if(!leyo){
cout << "Algo salio mal. Volviendo al menu" <<endl;
return -1;
}

int opcion;

char _descripcion[50];
double _precio;
int _tipo;

cout << "Producto: " << obj.getDescripcion() << endl;
cout << "Que dato desea modificar?" << endl;
cout << "Presione:" << endl;
cout << "1) Descripcion" << endl;
cout << "2) Valor" << endl;
cout << "3) Tipo" << endl;
cout << "4) Todas" << endl;
cout << "0) Volver al menu" << endl;
cin >> opcion;


system("cls");

switch(opcion){
case 1:
cout << "nueva Descripcion: ";
cin.ignore();
cin.getline(_descripcion, 49);
obj.setDescripcion(_descripcion);
break;

case 2:
cout << "nuevo Valor : ";
cin >> _precio;
obj.setPrecio(_precio);
break;

case 3:
cout << "- nuevo Tipo:" << endl;
cout << "1) Plato" << endl;
cout << "2) Guarnicion" << endl;
cout << "3) Bebida" << endl;
cin >> _tipo;
obj.setTipoProducto(_tipo);
break;

case 4:
cout << "- nueva Descripcion: ";
cin.ignore();
cin.getline(_descripcion, 49);

cout << "nuevo Valor: ";
cin >> _precio;

cout << "- nuevo Tipo:" << endl;
cout << "1) Plato" << endl;
cout << "2) Guarnicion" << endl;
cout << "3) Bebida" << endl;
cin >> _tipo;

obj.setDescripcion(_descripcion);
obj.setPrecio(_precio);
obj.setTipoProducto(_tipo);
break;

case 0:
cout << "Volviendo al menu." << endl;
system("pause");
system("cls");
return 0;
}

fseek(pProductos, pos * tam, 0);
int escribio = fwrite(&obj, tam, 1, pProductos);

fclose(pProductos);

if(escribio){
cout << "Modificacion realizada." << endl;
system("pause");
system("cls");
return true;
}

else
cout << "No se pudo realizar la modificacion." << endl;
system("pause");
system("cls");
return -1;

}

bool ArchivoProductos::darDeBaja(int idProducto) {
FILE *pProductos = fopen(nombre, "rb+");
if (!pProductos) {
    cout << "No se pudo abrir el archivo." << endl;
    return false;
}

Producto obj;
while (fread(&obj, tam, 1, pProductos)) {
    if (obj.getIdProducto() == idProducto) {
        obj.setEstado(false);
        fseek(pProductos, -tam, SEEK_CUR);
        fwrite(&obj, tam, 1, pProductos);
        fclose(pProductos);
        system("cls");
        cout << "Producto dado de baja exitosamente." << endl;
        system("pause");
        return true;
    }
}

fclose(pProductos);
cout << "No se encontro un producto con ese ID." << endl;
system("pause");
system("cls");
return false;
}



Producto ArchivoProductos::buscarProducto(int idProducto) {
    system("cls");
    Producto prod;
    FILE *pProductos;

    pProductos = fopen(nombre, "rb");  // Abrimos el archivo en modo de solo lectura binaria
    if (pProductos == nullptr) {
        cout << "El archivo de productos no se pudo encontrar o no existen registros." << endl;
        system("pause");
        system("cls");
        return prod;  // Retorna un objeto Producto vacío (por defecto)
    }

    // Buscamos el producto por su ID
    while (fread(&prod, tam, 1, pProductos)) {
        if (prod.getIdProducto() == idProducto) {
            fclose(pProductos);  // Cerramos el archivo después de encontrar el producto
            return prod;  // Retorna el producto encontrado
        }
    }

    fclose(pProductos);  // Cerramos el archivo después de leerlo

    /// Si el producto no fue encontrado, retornamos un objeto Producto vacío
    cout << "Producto no encontrado." << endl;
    system("pause");
    return Producto();  /// Retorna un objeto Producto vacío (por defecto)
}



bool ArchivoProductos::buscarProductoPorId(int idProducto, Producto &producto) {
    /// Abrimos el archivo en modo lectura binaria
    FILE *pProductos = fopen(nombre, "rb");
    if (pProductos == nullptr) {
        cout << "No se pudo abrir el archivo de productos." << endl;
        return false;
    }

    Producto aux;

    /// Recorremos el archivo leyendo los registros
    while (fread(&aux, sizeof(Producto), 1, pProductos)) {
        if (aux.getIdProducto() == idProducto) {
            /// Si encontramos el producto, lo devolvemos a través de la referencia
            producto = aux;
            fclose(pProductos);
            return true;
        }
    }

    /// Si no se encontró el producto, cerramos el archivo y devolvemos false
    fclose(pProductos);
    return false;
}



