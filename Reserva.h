#pragma once
#include "Fecha.h"
#include "Hora.h"

class ArchivoReservas;

class Reserva {
protected:
    int idReserva;           /// ID único por día
    int dniCliente;          /// DNI del cliente que efectúa la reserva
    Fecha fechaReserva;      /// Fecha de la reserva
    Hora horaReserva;        /// Hora de la reserva
    int comensales;          /// Cantidad de comensales
    int mesaAsignada;        /// Mesa asignada (1 a 20)
    float senia;             /// Seña del cliente
    int situacion;           /// 1-pendiente, 2-en curso, 3-finalizada, 4-cancelada
    int tipo;                /// Reserva anticipada o en el momento
    bool estado;             /// Estado de la reserva (activa o no)

public:
    /// Métodos existentes
    Reserva() : situacion(1), estado(true) {}
    int getIdReserva();
    int getDniCliente();
    Fecha getFechaReserva();
    int getMesaAsignada();
    float getSenia();
    int getSituacion();
    int getTipo();
    void cargarHoraReserva();
    void cargarReserva(ArchivoReservas& archR);
    void mostrarReserva();
    bool getEstado();

    /// Setters
    void setIdReserva(int id);
    void setDniCliente(int dni);
    void setFechaReserva(const Fecha& fecha);
    void setMesaAsignada(int mesa);
    void setSenia(float sena);
    void setSituacion(int situacionValor);
    void setTipo(int tipoReserva);
    void setComensales(int numComensales);
    void setEstado(bool estadoValor);
    void setHoraReserva(const Hora& nuevaHora);

};
