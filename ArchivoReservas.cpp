#include <iostream>
#include "Reserva.h"
#include "ArchivoReservas.h"
#include "Fecha.h"

using namespace std;


bool ArchivoReservas::grabarRegistroReservas(Reserva obj) {
    system("cls");

    Reserva aux;

    FILE *pReservas;
    pReservas = fopen(nombre, "ab+");
    if (pReservas == nullptr) {
        cout << "No se pudo establecer la conexion." << endl;
        return false;
    }

    /// Recorremos el archivo para verificar si ya existe el cliente con el mismo DNI
    while (fread(&aux, tam, 1, pReservas)) {
        if (aux.getDniCliente() == obj.getDniCliente() && aux.getFechaReserva() == obj.getFechaReserva() && aux.getEstado()) {
            cout << "El cliente ya tiene una reserva activa en el sistema para la fecha solicitada." << endl;
            system("pause");
            system("cls");
            return false;
        }
    }

    int escribio = fwrite(&obj, tam, 1, pReservas);

    if (escribio)
        cout << "Reserva cargada con exito." << endl;
    else
        cout << "No se pudo cargar la reserva." << endl;

    system("pause");
    system("cls");

    fclose(pReservas);

    return escribio;
}

bool ArchivoReservas::buscarRegistro() {
    system("cls");
    int idReserva;
    bool encontro = false;
    Reserva obj;
    cout << "Ingrese el ID de la reserva, (0 para volver al menu anterior): ";
    cin >> idReserva;
    if (idReserva == 0) return false;  /// Permitir volver al menú si el ID ingresado es 0

    FILE *pReservas;
    pReservas = fopen(nombre, "rb");
    if (pReservas == nullptr) {
        cout << "El archivo no se pudo encontrar o no existen registros." << endl;
        system("pause");
        system("cls");
        return false;  /// Retornar 0 si el archivo no existe
    }

    Fecha fechaReserva;
    cout << "Ingrese la fecha de la reserva a buscar: \n";
    fechaReserva.cargarFecha();

    /// Buscamos el registro en el archivo
    while (fread(&obj, tam, 1, pReservas)) {
        if (obj.getIdReserva() == idReserva && obj.getFechaReserva() == fechaReserva) {  /// Buscar por ID de reserva
            encontro = true;
            break;
        }
    }

    system("cls");

    fclose(pReservas);  /// Cerrar el archivo después de leerlo

    if (encontro){

        obj.mostrarReserva();
        system("pause");
        return true;  /// Retornar el ID de la reserva
    }

    else
        cout << "No se ha podido encontrar registro con el ID " << idReserva << " en la fecha establecida." << endl;
        system("pause");
        return false;  /// Retornar -1 si no se encuentra el ID
}


bool ArchivoReservas::listarReservas(){
system("cls");

int opcion;
do{
cout << "LISTADO DE RESERVAS:" << endl;
cout << "1) Del dia:" << endl;
cout << "2) Proximas:" << endl;
cout << "3) Pasadas o canceladas:" << endl;
cout << "0) Volver al menu anterior:" << endl;
cin >> opcion;

system("cls");

switch(opcion){
case 1:
    listarReservasDelDia();
    break;

case 2:
    listarReservasProximas();
    break;

case 3:
    listarReservasPasadas();
    break;

case 0:
    cout << "Volviendo al menu ..." << endl;
    system("pause");
    break;
    }
 }while(opcion);
}



bool ArchivoReservas::listarReservasDelDia() {
    system("cls");
    FILE *pReservas;
    Reserva obj;
    pReservas = fopen(nombre, "rb");

    if (pReservas == nullptr) {
        cout << "No se pudo encontrar el archivo de registros. Volviendo al menu anterior..." << endl;
        system("pause");
        system("cls");
        return false;
    }

    bool ban = false;
    Fecha fechaActual(true);

    cout << "RESERVAS DEL DIA:" << endl << endl;
    /// Leemos y mostramos todos los registros con estado "activo" (true)
    while (fread(&obj, tam, 1, pReservas)) {
        if (obj.getEstado() && obj.getFechaReserva()==fechaActual){  /// Verifica si el estado es "activo" y la fecha de reserva del día actual
            obj.mostrarReserva();  /// Asumo que 'mostrarReserva()' es un método de la clase Reserva
            ban = true;
            cout << endl;
        }
    }
    if(!ban)
        cout << "No hay reservas para el dia de la fecha" << endl;

    system("pause");
    system("cls");

    fclose(pReservas);

    return true;
}


bool ArchivoReservas::listarReservasProximas(){
system("cls");

FILE *pReservas;
pReservas = fopen(nombre, "rb");

if(!pReservas){
    cout << "No se pudo encontrar el archivo de registros. Volviendo al menu anterior..." << endl;
    system("pause");
    system("cls");
    return false;
}

Reserva obj;
Fecha fechaActual(true);
int cantReservasProximas = 0;

while(fread(&obj, tam, 1, pReservas)){                          ///se recorre el archivo y compara las fechas de los registros
    if(obj.getFechaReserva() > fechaActual && obj.getEstado())  ///con la fecha actual, filtrando y contando las que son
    cantReservasProximas++;                                     ///mayores (proximas)
}

fseek(pReservas, 0, 0);

if(!cantReservasProximas){
cout << "No se encontraron reservas proximas." << endl;
system("pause");
system("cls");
fclose(pReservas);
return false;
}

Reserva *arrayReservasProximas = new Reserva[cantReservasProximas];   ///se crea array dinamico de tamaño de reservas proximas

if(!arrayReservasProximas){
        cout << "No se pudo asignar memoria. Volviendo al menu anterior..." << endl;
        fclose(pReservas);
        system("pause");
        system("cls");
        return false;
}

int i, j;

i = 0;

while(fread(&obj, tam, 1, pReservas)){                           ///se copian las reservas proximas en el array dinamico,
    if(obj.getFechaReserva() > fechaActual && obj.getEstado()){  ///trayendolas desde el archivo a la memoria
    arrayReservasProximas[i]=obj;
    i++;
    }
  }

fclose(pReservas);

Reserva reservaAux;
int posReservaMenor;

for(i=0; i<cantReservasProximas; i++){  ///ordenamiento por seleccion de reservas por fecha en "orden ascendente"
posReservaMenor = i;
    for(j=i+1; j<cantReservasProximas; j++){
    if(arrayReservasProximas[j].getFechaReserva() < arrayReservasProximas[posReservaMenor].getFechaReserva())
         posReservaMenor = j;
    }
    if(posReservaMenor != i){                   ///comprobacion de si se encontro en el array una reserva de fecha anterior,
    reservaAux = arrayReservasProximas[i];      ///para así no tener que realizar instrucciones innecesarias
    arrayReservasProximas[i] = arrayReservasProximas[posReservaMenor];
    arrayReservasProximas[posReservaMenor] = reservaAux;
    }
}

cout << "RESERVAS PROXIMAS:" << endl << endl;
for(i=0; i<cantReservasProximas; i++){
    arrayReservasProximas[i].mostrarReserva();
    cout << endl;
}

system("pause");
system("cls");

delete [] arrayReservasProximas;

return true;
}


bool ArchivoReservas::listarReservasPasadas(){
system("cls");

FILE *pReservas;
pReservas = fopen(nombre, "rb+");

if(!pReservas){
    cout << "No se pudo encontrar el archivo de registros. Volviendo al menu anterior..." << endl;
    system("pause");
    system("cls");
    return false;
}

Fecha fechaActual(true);
Reserva obj;

int cantReservasPasadas = 0;

while(fread(&obj, tam, 1, pReservas)){
if(obj.getFechaReserva() < fechaActual || !obj.getEstado()){ ///validacion de reserva con fecha anterior o cancelada (estado "false")
    if(obj.getEstado()){             /// comprobacion del estado y la situacion del registro
    obj.setEstado(false);            ///si pasa la anterior validacion, ahi recien se implementa la modificacion
    obj.setSituacion(3);             ///del "estado" y "situacion" (finalizada) del registro.
    fseek(pReservas, -tam, 1);       ///se ubica el eof al principio del registro en cuestion
    fwrite(&obj, tam, 1, pReservas); ///se escribe encima y reemplaza ahora con el estado y situacion correspondientes
    fseek(pReservas, 0, 1);
    }                                ///NOTA: estas validaciones se utilizan para que los registros que son "mas viejos"
    cantReservasPasadas++;           ///no tengan que modificarse cada vez que se llame al metodo "listarReservasPasadas",
    }                                ///haciendo que no se ejecuten "instrucciones innecesarias"
}

fseek(pReservas, 0, 0);

if(!cantReservasPasadas){
    cout << "No se encontraron reservas pasadas o canceladas" << endl;
    system("pause");
    system("cls");
    fclose(pReservas);
    return false;
}

Reserva *arrayReservasPasadas = new Reserva[cantReservasPasadas]; ///se crea un array dinamico del tamaño de reservas pasadas o canceladas

int i = 0;

while(fread(&obj, tam, 1, pReservas)){                          ///se recorre nuevamente el archivo y se copian los registros
if(obj.getFechaReserva() < fechaActual || (!obj.getEstado())){  ///anteriores en el array dinamico creado
    arrayReservasPasadas[i] = obj;
    i++;
    }
}

fclose(pReservas);

Reserva aux;
int j, posReservaMenor;

for(i=0; i<cantReservasPasadas; i++){ ///ordenamiento de reservas pasadas o canceladas por "fecha" (ascendente)
posReservaMenor = i;
    for(j=i+1; j<cantReservasPasadas; j++){
        if(arrayReservasPasadas[j].getFechaReserva() < arrayReservasPasadas[posReservaMenor].getFechaReserva()){
            posReservaMenor = j;
            }
        }
            if(posReservaMenor != i){
            aux = arrayReservasPasadas[i];
            arrayReservasPasadas[i] = arrayReservasPasadas[posReservaMenor];
            arrayReservasPasadas[posReservaMenor] = aux;
            }
}

cout << " RESERVAS CON FECHAS" << endl;
cout << "PASADAS O CANCELADAS:" << endl << endl;
for(i=0; i<cantReservasPasadas; i++){
    arrayReservasPasadas[i].mostrarReserva();
    cout << endl;
}

delete [] arrayReservasPasadas; ///se libera la memoria

system("pause");
system("cls");

return true;
}



bool ArchivoReservas::leerRegistro(int idReserva) {
    system("cls");

    Reserva obj;
    FILE *pReservas;
    pReservas = fopen(nombre, "rb");

    if (pReservas == nullptr) {
        cout << "No se pudo establecer la conexion." << endl;
        system("cls");
        return false;
    }

    bool encontro = false;
    /// Recorrer el archivo buscando el idReserva

    Fecha fechaAux;
    fechaAux.cargarFecha();

    while (fread(&obj, tam, 1, pReservas)) {
        if (obj.getIdReserva() == idReserva && obj.getFechaReserva() == fechaAux) {
            encontro = true;
            break;
        }
    }

    if (encontro) {
        if (obj.getSituacion()) {  /// Verifica si el estado de la reserva es "activo"
            obj.mostrarReserva();
        } else {
            cout << "El registro esta en estado inactivo o eliminado." << endl;
        }
    } else {
        cout << "No se encontro un registro con ese ID en esa fecha." << endl;
    }

    system("pause");
    system("cls");
    fclose(pReservas);

    return encontro;  /// Retorna true si se encontró el registro, false en caso contrario
}



bool ArchivoReservas::modificarRegistro() {
    system("cls");

    FILE *pReservas;
    pReservas = fopen(nombre, "rb+");

    if (pReservas == nullptr) {
        cout << "No se pudo encontrar el archivo de registros. Volviendo al menu anterior." << endl;
        system("pause");
        system("cls");
        return false;
    }

    Reserva obj;
    bool encontrado = false;
    long posicionRegistro = 0;

    int idReserva;
    cout << "Ingrese el ID de la reserva a modificar: ";
    cin >> idReserva;

    Fecha fechaActual(true);

    Fecha fechaAux;
    fechaAux.cargarFecha();

        if(!fechaAux.getDia()){
        fclose(pReservas);
        return 0;
    }

    /// Recorrer el archivo buscando la reserva con el idReserva especificado
    while (fread(&obj, tam, 1, pReservas)) {
        if (obj.getIdReserva() == idReserva && obj.getFechaReserva() == fechaAux && obj.getFechaReserva() >= fechaActual) {
            if (obj.getEstado()) {  /// Verifica si el estado de la reserva es "activo" (true)
                encontrado = true;
                posicionRegistro = ftell(pReservas) - tam; // Guarda la posición del registro
            }
            break; /// Salir del ciclo una vez que encontramos el id
        }
    }

    if (!encontrado) {
        cout << "La reserva con ID " << idReserva << " en la fecha establecida, no se encuentra en los registros o esta inactiva." << endl;
        system("pause");
        system("cls");
        fclose(pReservas);
        return false;
    }

    /// Solicitar modificación de los datos
    int nuevoDni;
    Fecha nuevaFecha;
    Hora nuevaHora;
    int nuevosComensales;
    int nuevaMesa;
    float nuevaSenia;
    int nuevoTipo;

    cout << "Ingrese el nuevo DNI del cliente: ";
    cin >> nuevoDni;

    /// Solicitar y validar la nueva fecha
    while (true) {
        cout << "Ingrese la nueva fecha de la reserva:" << endl;
        nuevaFecha.cargarFecha();

        if (nuevaFecha.esFechaValida()) {  // Validar fecha
            break;
        } else {
            cout << "La fecha ingresada es invalida o esta en el pasado. Intente nuevamente." << endl;
        }
    }

    /// Solicitar la nueva hora
    cout << "Ingrese la nueva hora de la reserva:" << endl;
    nuevaHora.cargarHora();

    cout << "Ingrese la nueva cantidad de comensales: ";
    cin >> nuevosComensales;

    cout << "Ingrese la nueva mesa asignada (1-20): ";
    cin >> nuevaMesa;

    cout << "Ingrese el nuevo valor de la senia: ";
    cin >> nuevaSenia;

    cout << "Ingrese el nuevo tipo de reserva (1-Anticipada, 2-En el momento): ";
    cin >> nuevoTipo;

    /// Actualizar los valores
    obj.setDniCliente(nuevoDni);
    obj.setFechaReserva(nuevaFecha);  /// Usar la nueva fecha validada
    obj.setHoraReserva(nuevaHora);   /// Usar la nueva hora ingresada
    obj.setComensales(nuevosComensales);
    obj.setMesaAsignada(nuevaMesa);
    obj.setSenia(nuevaSenia);
    obj.setTipo(nuevoTipo);

    /// Volver a la posición del registro en el archivo para escribir la modificación
    fseek(pReservas, posicionRegistro, SEEK_SET); /// Nos movemos a la posición correcta

    int escribio = fwrite(&obj, tam, 1, pReservas);

    fclose(pReservas);

    if (escribio) {
        cout << "Modificacion realizada." << endl;
        system("pause");
        system("cls");
        return true;
    } else {
        cout << "No se pudo realizar la modificacion." << endl;
        system("pause");
        system("cls");
        return false;
    }
}

bool ArchivoReservas::eliminarRegistro() {
    system("cls");

    FILE *pReservas;
    pReservas = fopen(nombre, "rb+");

    if (pReservas == nullptr) {
        cout << "No se pudo encontrar el archivo de registros. Volviendo al menu anterior..." << endl;
        system("pause");
        system("cls");
        return false;
    }

    Reserva obj;
    bool encontrado = false;
    long posicionRegistro = 0;

    int idReserva;
    cout << "Ingrese el ID a eliminar: ";
    cin >> idReserva;

    Fecha fechaActual(true);

    Fecha fechaAux;
    fechaAux.cargarFecha();

    if(!fechaAux.getDia()){
        fclose(pReservas);
        return 0;
    }


    /// Recorrer el archivo buscando la reserva con el idReserva especificado
    while (fread(&obj, tam, 1, pReservas)) {
        if (obj.getIdReserva() == idReserva && obj.getFechaReserva() == fechaAux && obj.getFechaReserva() >= fechaActual){
            if(obj.getEstado()){
            encontrado = true;
            posicionRegistro = ftell(pReservas) - tam; // Guarda la posición del registro
            break; /// Salir del ciclo una vez que encontramos el id
            }
        }
    }

    if (!encontrado) {
        cout << "La reserva con ID " << idReserva << " en la fecha establecida, no se encuentra en los registros o esta inactiva." << endl;
        system("pause");
        system("cls");
        fclose(pReservas);
        return 0;
    }

    obj.setEstado(false); /// Suponiendo que 'false' representa el estado "inactivo"
    obj.setSituacion(4); /// Situacion de reserva "cancelada"
    /// Volver a la posición del registro en el archivo para escribir la modificación
    fseek(pReservas, posicionRegistro, SEEK_SET); /// Nos movemos a la posición correcta
    int escribio = fwrite(&obj, tam, 1, pReservas);

    fclose(pReservas);

    if (escribio) {
        cout << "Registro eliminado correctamente." << endl;
        system("pause");
        system("cls");
        return true;
    } else {
        cout << "No se pudo realizar el borrado logico del registro." << endl;
        system("pause");
        system("cls");
        return false;
    }
}

int ArchivoReservas::obtenerIdReserva(Fecha _fechaReserva) {
    Reserva aux;
    int cont = 0;

    /// Abrimos el archivo en modo "ab+" (lectura y escritura, crea el archivo si no existe)
    FILE *pReservas = fopen(nombre, "ab+");
    if (pReservas == nullptr) {
        cout << "Algo salio mal al intentar abrir el archivo de reservas." << endl;
        system("pause");
        system("cls");
        return -1; // Error al abrir el archivo
    }


    while(fread(&aux, tam, 1, pReservas)){
    if(aux.getFechaReserva() == _fechaReserva)
        cont++;
    }

    fclose(pReservas);

    /// Si el archivo está vacío, el primer ID será 1
    if(!cont)
        return 1;

    /// Si hay contenido, calcular el próximo ID
    return cont + 1;
}


