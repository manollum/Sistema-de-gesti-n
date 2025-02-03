#include <iostream>
#include <fstream>
#include "Reportes.h"
#include "ArchivoEmpleados.h"
#include "ArchivoReservas.h"
#include "ArchivoMesas.h"
#include <ctime>
#include <cstring>
#include <iomanip>


using namespace std;

float calcularEgresosSueldos() {
    /// Inicializamos el acumulador para los sueldos y el contador de empleados activos
    double sumaSueldos = 0.0;
    int contadorEmpleados = 0;

    /// Abrimos el archivo empleados.dat
    FILE* pEmpleados = fopen("empleados.dat", "rb");
    if (pEmpleados == nullptr) {
        cout << "El archivo no se pudo encontrar o no existen registros cargados." << endl;
        return 0.0;
    }

    /// Creamos un objeto empleado para leer los registros
    Empleado obj;
    while (fread(&obj, sizeof(Empleado), 1, pEmpleados)) {
        /// Verificamos si el empleado está activo (suponiendo que la función getEstado() devuelve el estado)
        if (obj.getEstado()) {
            sumaSueldos += obj.getSueldo();  /// Sumamos el sueldo del empleado activo
            contadorEmpleados++;  /// Aumentamos el contador de empleados activos
        }
    }

    /// Cerramos el archivo
    fclose(pEmpleados);

    /// Si no hay empleados activos, devolvemos 0 para evitar división por cero
    if (contadorEmpleados == 0) {
        cout << "No hay empleados activos." << endl;
        return 0.0;
    }

    /// Obtener el número de días del mes actual
    time_t t = time(0);  /// Obtenemos el tiempo actual
    struct tm *now = localtime(&t);  /// Convertimos el tiempo actual a una estructura tm

    /// Determinar el número de días del mes actual
    int diasDelMes = 31;  /// Asumimos 31 días por defecto
    switch (now->tm_mon) {  /// Ahora podemos acceder al mes actual (tm_mon va de 0 a 11)
        case 0: case 2: case 4: case 6: case 7: case 9: case 11:  /// Meses con 31 días
            diasDelMes = 31;
            break;
        case 3: case 5: case 8: case 10:  // Meses con 30 días
            diasDelMes = 30;
            break;
        case 1:  /// Febrero, se necesita ver si es un año bisiesto
            if ((now->tm_year + 1900) % 4 == 0 && ((now->tm_year + 1900) % 100 != 0 || (now->tm_year + 1900) % 400 == 0)) {
                diasDelMes = 29;  /// Año bisiesto
            } else {
                diasDelMes = 28;  /// Año no bisiesto
            }
            break;
    }

    /// Dividir la suma de los sueldos entre los días del mes y el número de empleados activos
    double egresos = sumaSueldos / diasDelMes;

    /// Mostrar el resultado con 2 decimales
    cout << fixed << setprecision(2);  // Esto garantiza que se muestren 2 decimales
    cout << "El egreso en sueldos de empleados del dia es: $" << egresos <<endl;

    return egresos;
}




float calcularSaldoMesasActivas() {
    ArchivoMesas archivoM("mesas.dat");
    Mesa mesa;
    float sumaSaldoActivas = 0.0f;
    float sumaSaldoCerradas = 0.0f;

    /// Abrimos el archivo de mesas para calcular el saldo de mesas activas
    FILE *pMesas = fopen("mesas.dat", "rb");
    if (pMesas == nullptr) {
        cout << "No se pudo abrir el archivo mesas.dat." << endl;
        return 0.0f;
    }

    /// Recorremos cada registro del archivo de mesas
    while (fread(&mesa, sizeof(Mesa), 1, pMesas)) {
        /// Verificamos si la mesa está activa y tiene un ID válido
        if (mesa.getEstado() && mesa.getIdMesa() != -1) {
            sumaSaldoActivas += mesa.getSaldo(); /// Sumamos el saldo de mesas activas
        }
    }
    fclose(pMesas); /// Cerramos el archivo de mesas

    /// Mostramos el total de las mesas activas
    cout << "Saldo total de mesas activas: $" << fixed << setprecision(2) << sumaSaldoActivas << endl;

    /// Abrimos el archivo de ingresos del día para sumar los saldos de mesas cerradas
    FILE *pIngresos = fopen("ingresos_del_dia.dat", "rb");
    if (pIngresos != nullptr) {
        /// Leemos el valor acumulado de ingresos cerrados
        if (fread(&sumaSaldoCerradas, sizeof(float), 1, pIngresos) != 1) {
            cout << "Error al leer los ingresos del dia. Asumiendo $0.00." << endl;
            sumaSaldoCerradas = 0.0f;
        }

        /// Mensaje de depuración: mostramos el contenido leído
        cout << "Saldo total de mesas cerradas: $" << fixed << setprecision(2) << sumaSaldoCerradas << endl;

        fclose(pIngresos);
    } else {
        cout << "No se encontro el archivo de ingresos del dia. Asumiendo $0.00." << endl;
        sumaSaldoCerradas = 0.0f;
    }

    /// Calculamos el saldo total sumando mesas activas y cerradas
    float sumaTotal = sumaSaldoActivas + sumaSaldoCerradas;

    /// Mostramos el resultado total con dos decimales
    cout << "La suma total del saldo de mesas activas y cerradas es: $" << fixed << setprecision(2) << sumaTotal << endl;

    return sumaTotal;
}



void guardarIngresoDiario(float saldo) {
    FILE *pIngresos = fopen("ingresos_del_dia.dat", "rb+");
    if (pIngresos == nullptr) {
        /// Si no existe el archivo, lo creamos en modo escritura
        pIngresos = fopen("ingresos_del_dia.dat", "wb");
        if (pIngresos == nullptr) {
            cout << "No se pudo crear el archivo ingresos_del_dia.dat." << endl;
            return;
        }
        /// Escribimos el saldo inicial
        fwrite(&saldo, sizeof(float), 1, pIngresos);
    } else {
        /// Si existe, leemos el saldo acumulado actual
        float saldoAcumulado = 0.0f;
        fread(&saldoAcumulado, sizeof(float), 1, pIngresos);

        /// Sumamos el nuevo saldo al acumulado
        saldoAcumulado += saldo;

        /// Reposicionamos el puntero al inicio y actualizamos el archivo
        fseek(pIngresos, 0, SEEK_SET);
        fwrite(&saldoAcumulado, sizeof(float), 1, pIngresos);
    }

    fclose(pIngresos);  /// Cerramos el archivo
}




bool resetearSaldos() {
    FILE *pMesas = fopen("ingresos_del_dia.dat", "wb");
    if (pMesas == nullptr) {
        cout << "No se pudo abrir el archivo para resetear." << endl;
        system("pause");
        return false;
    }

    fclose(pMesas);
    cout << "El archivo de mesas ha sido reseteado exitosamente." << endl;
    system("pause");
    return true;
}
