#include <iostream>
#include "Reserva.h"
#include "ArchivoReservas.h"




using namespace std;



int Reserva::getIdReserva(){return idReserva;}
int Reserva::getDniCliente(){return dniCliente;}
Fecha Reserva::getFechaReserva(){return fechaReserva;}
int Reserva::getMesaAsignada(){return mesaAsignada;}
float Reserva::getSenia(){return senia;}
int Reserva::getSituacion(){return situacion;}
int Reserva::getTipo(){return tipo;}
bool Reserva::getEstado(){return estado;}

void Reserva::setIdReserva(int id) {
    idReserva = id;
}

void Reserva::setDniCliente(int dni) {
    dniCliente = dni;
}

void Reserva::setFechaReserva(const Fecha& fecha) {
    fechaReserva = fecha;
}

void Reserva::setMesaAsignada(int mesa) {
    mesaAsignada = mesa;
}

void Reserva::setSenia(float sena) {
    senia = sena;
}

void Reserva::setSituacion(int situacionValor) {
    situacion = situacionValor;
}

void Reserva::setTipo(int tipoReserva) {
    tipo = tipoReserva;
}

void Reserva::setComensales(int numComensales) {
    comensales = numComensales;
    }

void Reserva::setEstado(bool estadoValor) {
        estado = estadoValor;
    }

void Reserva::cargarReserva(ArchivoReservas &archivoR) {
    system("cls");

    int _horaReserva;
    int _minutoReserva;

    cout << "Ingrese el DNI del cliente, (0 para volver al MENU anterior): ";
    cin >> dniCliente;
    if(dniCliente == 0){
     system("cls");

     cout << "Volviendo al menu anterior..." << endl;
     system("pause");
     system("cls");
        return;
    }
    cin.ignore();

    cout << "Ingrese la fecha de la reserva:" << endl;
    fechaReserva.cargarFecha();
    if(!fechaReserva.getDia())
        return;

    /// Asignar el ID automáticamente
    idReserva = archivoR.obtenerIdReserva(fechaReserva); ///MODIFIQUE ACA

    horaReserva.cargarHoraReserva(); ///horaReserva.cargarHora()Reserva; /// Usar el método de la clase Hora para cargar la hora

    cout << "Ingrese la cantidad de comensales: ";
    cin >> comensales;

    cout << "Ingrese el numero de mesa asignada (1-20): ";
    cin >> mesaAsignada;

    cout << "Ingrese la senia por parte del cliente: ";
    cin >> senia;

///    cout << "Ingrese la situacion de la reserva (1 - pendiente, 2 - en curso, 3 - finalizada): ";
///    cin >> situacion;

    cout << "Ingrese el tipo de reserva (1 - con anticipacion, 2 - en el momento): ";
    cin >> tipo;

    ///cout << "Reserva cargada correctamente con ID: " << idReserva << "." << endl;
    ///system("pause");
    ///system("cls");
}

void Reserva::mostrarReserva() {
    cout << "Detalles de la Reserva:" << endl;
    cout << "ID Reserva: " << idReserva << endl;
    cout << "DNI del Cliente: " << dniCliente << endl;

    cout << "Fecha de la Reserva: ";
    fechaReserva.mostrarFecha();

    cout << "Hora de la Reserva: ";
    horaReserva.mostrarHora(); /// Mostrar la hora usando el método de la clase Hora
    cout<<endl;
    cout << "Numero de Comensales: " << comensales << endl;
    cout << "Mesa Asignada: " << mesaAsignada << endl;
    cout << "Senia: " << senia << " ARS" << endl;

    /// Mostrar la situación de la reserva
    cout << "Situacion: ";
    switch (situacion) {
        case 1: cout << "Pendiente"; break;
        case 2: cout << "En curso"; break;
        case 3: cout << "Finalizada"; break;
        case 4: cout << "Cancelada"; break;
        default: cout << "Desconocida"; break;
    }
    cout << endl;

    /// Mostrar el tipo de reserva
    cout << "Tipo de Reserva: ";
    switch (tipo) {
        case 1: cout << "Anticipada"; break;
        case 2: cout << "En el momento"; break;
        default: cout << "Desconocida"; break;
    }
    cout << endl;
}


void Reserva::setHoraReserva(const Hora& nuevaHora) {
    horaReserva = nuevaHora;
}

