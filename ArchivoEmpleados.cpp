#include <iostream>
#include "Empleado.h"
#include "ArchivoEmpleados.h"


bool ArchivoEmpleados::grabarRegistro(Empleado obj){
Empleado aux;

FILE *pEmpleados;
pEmpleados = fopen(nombre, "ab+");
if(pEmpleados==nullptr){
    cout << "No se pudo establecer la conexion." << endl;
    return 0;
}
while(fread(&aux, tam, 1, pEmpleados)){
if(aux.getDni() == obj.getDni() || aux.getLegajo() == obj.getLegajo()){
        cout << "El DNI/Legajo ingresado ya se encuentra en el sistema." << endl;
        system("pause");
        system("cls");
        return -1;
        }
    }

int escribio = fwrite(&obj, tam, 1, pEmpleados);

if(escribio)
    cout << "Registro cargado con exito." << endl;
else
    cout << "No se pudo cargar el registro." << endl;

system("pause");
system("cls");

fclose(pEmpleados);

return escribio;
}



int ArchivoEmpleados::buscarRegistro(){
    system("cls");
int legajo, pos = 0;
bool encontro = false;
Empleado obj;
cout << "Ingrese el legajo del empleado, (0 para volver al MENU anterior): ";
cin >> legajo;
if(legajo==0)return -2;
FILE *pEmpleados;
pEmpleados = fopen(nombre, "rb");
if(pEmpleados==nullptr){
    cout << "El archivo no se pudo encontrar o aun no existen registros cargados." << endl;
    system("pause");
    system("cls");
    return 0;
}

while(fread(&obj, tam, 1, pEmpleados)){
    if(obj.getLegajo() == legajo){
    encontro = true;
    break;
    }
    pos++;
}

fclose(pEmpleados);

if(encontro)
return pos;
else
return -1;
}


bool ArchivoEmpleados::listarRegistros(){
    system("cls");
        FILE *pEmpleados;
        Empleado obj;
        pEmpleados = fopen(nombre, "rb");

        if (pEmpleados==nullptr) {
        cout << "El archivo no se pudo encontrar o aun no existen registros cargados." << endl;
        system("pause");
        system("cls");
        return false;
        }

        bool encontro = false;

        while(fread(&obj, tam, 1, pEmpleados)) {
        if (obj.getEstado()) { // solo empleados activos
        obj.mostrarEmpleado();
        encontro = true;
        cout << endl;
            }
        }

        if(!encontro)
            cout << "No se encontraron empleados activos." << endl;

        system("pause");
        system("cls");
        fclose(pEmpleados);
        return true;
}


bool ArchivoEmpleados::leerRegistro(int pos){
system("cls");

if(pos==-1){
cout << "El LEGAJO no se encuentra en los registros." << endl;
system("pause");
system("cls");
return -1;
}

Empleado obj;
FILE *pEmpleados;
pEmpleados = fopen(nombre, "rb");

if(pEmpleados==nullptr){
    cout << "No se pudo establecer la conexion." << endl;
    system("cls");
    return false;
}

fseek(pEmpleados, tam * pos, 0);

int leyo = fread(&obj, tam, 1, pEmpleados);

if(leyo) {

    if (!obj.getEstado()) {
    cout << "El empleado esta dado de baja." << endl;
    system("pause");
    system("cls");
    return false;
}
obj.mostrarEmpleado();
}
else
cout << "No se encuentran registros con ese DNI." << endl;

system("pause");
system("cls");
fclose(pEmpleados);

return leyo;
}



bool ArchivoEmpleados::modificarRegistro(int pos){

if(pos==-1){
cout << "El LEGAJO no se encuentra en los registros." << endl;
system("pause");
system("cls");
return -1;
}

FILE *pEmpleados;
pEmpleados = fopen(nombre, "rb+");

if(pEmpleados==nullptr){
    cout << "No se pudo establecer la conexion." << endl;
    system("cls");
    return false;
    }

fseek(pEmpleados, pos * tam, 0);

Empleado obj;

int leyo = fread(&obj, tam, 1, pEmpleados);

if(!leyo){
cout << "Algo salio mal. Volviendo al menu" << endl;
return -1;
}

int opcion;
long telefono;
char cargo[20];
double sueldo;

cout << "Que dato desea modificar?" << endl;
cout << "Presione:" << endl;
cout << "1) Telefono" << endl;
cout << "2) Cargo" << endl;
cout << "3) Sueldo" << endl;
cout << "4) Todas" << endl;
cout << "0) Volver al menu" << endl;
cin >> opcion;


system("cls");

switch(opcion){
case 1:
cout << "- nuevo Telefono: ";
cin >> telefono;
obj.setTelefono(telefono);
break;

case 2:
cout << "- nuevo Cargo: ";
cin.ignore();
cin.getline(cargo, 19);
obj.setCargo(cargo);
break;

case 3:
cout << "- nuevo Sueldo: ";
cin >> sueldo;
obj.setSueldo(sueldo);
break;

case 4:
cout << "- nuevo Telefono: ";
cin >> telefono;

cout << "- nuevo Cargo: ";
cin.ignore();
cin.getline(cargo, 19);

cout << "- nuevo Sueldo: ";
cin >> sueldo;

obj.setTelefono(telefono);
obj.setCargo(cargo);
obj.setSueldo(sueldo);
break;

case 0:
cout << "Volviendo al menu." << endl;
system("pause");
system("cls");
return 0;
}

fseek(pEmpleados, pos * tam, 0);
int escribio = fwrite(&obj, tam, 1, pEmpleados);

fclose(pEmpleados);

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

bool ArchivoEmpleados::bajaRegistro() {
system("cls");
int pos = buscarRegistro();
if (pos < 0) {
    if (pos == -1) {
        cout << "El LEGAJO no se encuentra en los registros." << endl;
    } else if (pos == -2) {
        cout << "Operacion cancelada por el usuario." << endl;
    }
    system("pause");
    system("cls");
    return false;
}

FILE *pEmpleados = fopen(nombre, "rb+");
if (!pEmpleados) {
    cout << "No se pudo abrir el archivo." << endl;
    system("pause");
    system("cls");
    return false;
}

fseek(pEmpleados, pos * tam, 0);
Empleado obj;
fread(&obj, tam, 1, pEmpleados);

if (!obj.getEstado()) {
    cout << "El empleado ya estaba dado de baja." << endl;
    fclose(pEmpleados);
    system("pause");
    system("cls");
    return false;
}

obj.setEstado(false); // estado inactivo
fseek(pEmpleados, -tam, SEEK_CUR);
fwrite(&obj, tam, 1, pEmpleados);

fclose(pEmpleados);

cout << "El empleado ha sido dado de baja exitosamente." << endl;
system("pause");
system("cls");
return true;
}

bool ArchivoEmpleados::altaRegistro() {
system("cls");
int pos = buscarRegistro();
if (pos < 0) {
    if (pos == -1) {
        cout << "El LEGAJO no se encuentra en los registros." << endl;
    } else if (pos == -2) {
        cout << "Operacion cancelada por el usuario." << endl;
    }
    system("pause");
    system("cls");
    return false;
}

FILE *pEmpleados = fopen(nombre, "rb+");
if (!pEmpleados) {
    cout << "No se pudo abrir el archivo." << endl;
    system("pause");
    system("cls");
    return false;
}

fseek(pEmpleados, pos * tam, 0);
Empleado obj;
fread(&obj, tam, 1, pEmpleados);

if (obj.getEstado()) {
    cout << "El empleado ya esta activo." << endl;
    fclose(pEmpleados);
    system("pause");
    system("cls");
    return false;
}

obj.setEstado(true); // estado activo
fseek(pEmpleados, -tam, SEEK_CUR);
fwrite(&obj, tam, 1, pEmpleados);

fclose(pEmpleados);

cout << "El empleado ha sido reactivado exitosamente." << endl;
system("pause");
system("cls");
return true;
}

bool ArchivoEmpleados::listarRegistrosInactivos(){
    system("cls");
        FILE *pEmpleados;
        Empleado obj;
        pEmpleados = fopen(nombre, "rb");

        if (pEmpleados==nullptr) {
        cout << "El archivo no se pudo encontrar o aun no existen registros cargados." << endl;
        system("pause");
        system("cls");
        return false;
        }

        bool encontro = false;

        while(fread(&obj, tam, 1, pEmpleados)) {
        if (!obj.getEstado()) { // solo empleados inactivos
        obj.mostrarEmpleado();
        encontro = true;
        cout << endl;
            }
        }


        if(!encontro)
            cout << "No se encontraron empleados inactivos." << endl;

        system("pause");
        system("cls");
        fclose(pEmpleados);
        return true;
}




int ArchivoEmpleados::contarRegistros() {
    FILE *pEmpleados;
    pEmpleados = fopen(nombre, "ab+");  /// Abrimos el archivo en modo binario de solo lectura

    if (pEmpleados == nullptr) {
        cout << "El archivo no se pudo encontrar o aun no existen registros cargados." << endl;
        system("pause");
        system("cls");
        return 0;  /// Si no existe el archivo, devolvemos 0 (sin registros)
    }

    /// Obtenemos el tamaño del archivo
    fseek(pEmpleados, 0, SEEK_END);  // Nos movemos al final del archivo
    long tamArchivo = ftell(pEmpleados);  // Obtenemos el tamaño del archivo en bytes
    fseek(pEmpleados, 0, SEEK_SET);  // Volvemos al inicio del archivo

    /// Calculamos la cantidad de registros en función del tamaño del archivo y el tamaño de cada registro
    int cantidadRegistros = tamArchivo / tam;  /// `tam` es el tamaño de un registro de tipo Empleado

    fclose(pEmpleados);  /// Cerramos el archivo

    return cantidadRegistros;  /// Devolvemos la cantidad de registros
}




