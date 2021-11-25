#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#define MAX_CHAR_NOMBRE 128
#define MAX_REINTENTOS 5
#define EMPLOYEE_INIT_ID 10000
#define EMPLOYEE_MAX_ID 99999
#define MIN_SUELDO 20000
#define MAX_SUELDO 500000
#define MIN_HORAS_TRABAJADAS 50
#define MAX_HORAS_TRABAJADAS 200

typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idStr, char* nombreStr, char* horasTrabajadasStr, char* sueldo);

int employee_criteriaFunction(void* item1, void* item2);
int employee_initArray(Employee* array, int size);
void employee_delete();

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

#endif
