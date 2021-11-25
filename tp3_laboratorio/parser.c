#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "Controller.h"

void employee_showEmployee(Employee* employee){
	char nombre[128];
	int horas;
	int sueldo;
	int id;
	if(employee_getId(employee, &id) == 0
			&& employee_getNombre(employee, nombre) == 0
				&& employee_getHorasTrabajadas(employee, &horas) == 0
					&& employee_getSueldo(employee, &sueldo) == 0){
		printf("%d\t%22s\t%24d\t$%5d\n", id, nombre, horas, sueldo);
	}
}

int parser_getLastIdFromFile(void){
	FILE* pFile;
	int id = 0;
	pFile = fopen("data_lastId.csv", "r");
	if(pFile != NULL){
		fscanf(pFile, "%d", &id);
	}
	fclose(pFile);
    return id;
}

void parser_saveLastIdInFile(int id){
	FILE* pFile;
	pFile = fopen("data_lastId.csv", "w");
	if(pFile != NULL){
		fprintf(pFile, "%d", id);
	}
	fclose(pFile);
}


Employee* employee_getEmployeeById(LinkedList* listaEmpleados, int idEmployee){
	Employee* aux;
	Employee* result;
	for(int i=0; i< ll_len(listaEmpleados); i++){
		aux = (Employee*) ll_get(listaEmpleados, i);
		if(aux != NULL){
			if(aux->id == idEmployee){
				result = aux;
				break;
			}
		}
	}
	return result;
}


int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee){
	Employee* aux;
	int i = 0;
	int r;
	int result;
	char id[50];
	char nombre[129];
	char horas[10];
	char sueldo[50];
	result = -1;

	if(pFile != NULL && pArrayListEmployee != NULL){
		r = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, nombre, horas, sueldo);
		do{
			r = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, nombre, horas, sueldo);
			if(r == 4){
				aux = employee_newParametros(id, nombre, horas, sueldo);
				if(ll_add(pArrayListEmployee, aux) == 0){
					parser_saveLastIdInFile(atoi(id));
					i++;
					result = i;
				}
			}
		}while(!feof(pFile));
	}
    return result;
}



int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{

	int result = -1;
	Employee* aux;
	result = -1;
	if(pFile != NULL && pArrayListEmployee != NULL){
		do{
			aux = employee_new();
			fread(aux,sizeof(Employee),1,pFile);
			if(aux != NULL){
				ll_add(pArrayListEmployee, aux);
				result++;
			}
		}while(!feof(pFile));
	}
	return result;
}
