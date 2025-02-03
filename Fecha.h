#pragma once
#include <iostream>
#include <chrono>
#include <ctime> /// Para obtener la hora actual

extern int diasMeses[];

class Fecha {
private:
    int dia, mes, anio;

public:
    Fecha();
    Fecha(int _dia, int _mes, int _anio);
    Fecha(bool usarFechaSistema);

    ///Sobrecarga operador ==
    bool operator ==(Fecha obj);

    /// Sobrecarga del operador >=
    bool operator >=(Fecha obj);

    ///Sobrecarga del operador >
    bool operator >(Fecha obj);

    ///Sobrecarga operador <
    bool operator <(Fecha obj);


    /// Validación de la fecha con respecto al sistema
    bool esFechaValida();

    /// Métodos para cargar, obtener y mostrar la fecha
    void setAnio(int _anio);
    void setMes(int _mes);
    void setDia(int _dia);
    void cargarFecha();
    void cargarFechaReserva();
    Fecha getFecha();
    int getDia();
    int getMes();
    int getAnio();
    void actualizarFecha();
    void mostrarFecha();
};


