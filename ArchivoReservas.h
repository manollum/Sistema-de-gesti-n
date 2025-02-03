#pragma once
#include "Reserva.h"
#include <cstring>

using namespace std;

class ArchivoReservas {
private:
    char nombre[20];
    int tam;

public:
    ArchivoReservas(const char *_nombre = "reservas.dat") {
        strncpy(nombre, _nombre, 19);
        tam = sizeof(Reserva);
    }

    bool grabarRegistroReservas(Reserva obj);
    bool buscarRegistro();
    bool leerRegistro(int pos);
    bool listarReservasDelDia();
    bool listarReservasProximas();
    bool listarReservasPasadas();
    bool listarReservas();
    bool modificarRegistro();
    bool altaRegistro();
    bool eliminarRegistro();
    int obtenerIdReserva(Fecha _fechaReserva);
};

