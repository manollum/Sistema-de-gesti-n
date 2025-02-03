#pragma once
#include <iostream>
using namespace std;

class Hora {
private:
    int hora;   /// Rango válido: 0-23
    int minuto; /// Rango válido: 0-59

public:
    /// Constructor por defecto
    Hora() : hora(0), minuto(0) {}

    /// Constructor parametrizado
    Hora(int _hora, int _minuto) {
        setHora(_hora);
        setMinuto(_minuto);
    }

    /// Setters con validación
void setHora(int _hora);

void setMinuto(int _minuto);
    /// Getters
int getHora();
int getMinuto();

    /// Método para mostrar la hora en formato HH:MM
void mostrarHora();

    /// Método para cargar la hora
void cargarHora();

    /// Metodo para cargar la hora de la reserva
void cargarHoraReserva();

    /// Comparador de igualdad
bool operator==(const Hora& otra) const {
        return hora == otra.hora && minuto == otra.minuto;
    }

    /// Comparador "mayor o igual" para comparación de horas
bool operator>=(const Hora& otra) const {
        if (hora > otra.hora) return true;
        if (hora == otra.hora && minuto >= otra.minuto) return true;
        return false;
    }
};

