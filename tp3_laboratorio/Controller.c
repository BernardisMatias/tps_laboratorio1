#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "Parser.h"


/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int result = -1;
	printf("ID\t\t\tNOMBRE\t\tHORAS TRABAJADAS\tSUELDO\n");
	for(int i=0; i< ll_len(pArrayListEmployee); i++){
		if(ll_get(pArrayListEmployee, i) != NULL){
			employee_showEmployee((Employee*) ll_get(pArrayListEmployee, i));
			result = 0;
		}
	}
	return result;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee){

	FILE *pFile;
	int result = -1;
	if(path != NULL){
		pFile = fopen("data.csv", "r");
		if(pFile != NULL && pArrayListEmployee != NULL){
			result = parser_EmployeeFromText(pFile, pArrayListEmployee);
		}
	}
	fclose(pFile);
    return result;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	FILE *pFile;
	int result = -1;
	if(path != NULL){
		pFile = fopen("data_exported.bin","rb");
		if(pFile != NULL && pArrayListEmployee != NULL){
			result = parser_EmployeeFromBinary(pFile, pArrayListEmployee);
		}
	}
	fclose(pFile);
	return result;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int result = -1;
	int horas;
	int sueldo;
	int id;
	char idAux[10];
	char sueldoAux[10];
	char horasAux[10];
	char nombreAux[128];
	Employee* aux;
	fflush(stdin);
	GetString(nombreAux, "Ingrese nombre: ", "Error, reingrese nombre", MAX_CHAR_NOMBRE, MAX_REINTENTOS);
	fflush(stdin);
	GetEntero(&horas, "Ingrese horas trabajadas: ", 40, 250, MAX_REINTENTOS);
	fflush(stdin);
	GetEntero(&sueldo, "Ingrese sueldo (solo entero): ", 20000, 250000, MAX_REINTENTOS);
	id = parser_getLastIdFromFile() + 1;
	aux = employee_newParametros(itoa(id, idAux, 10), nombreAux, itoa(horas, horasAux, 10), itoa(sueldo, sueldoAux, 10));
	if(aux != NULL){
		ll_add(pArrayListEmployee, aux);
		parser_saveLastIdInFile(id);
		result = 0;
	}
	return result;
}

int ultimoIdDeLaLista(LinkedList* pArrayListEmployee){
	int idMaximo = 0;
	int idAux;
	for(int i=0;i<ll_len(pArrayListEmployee);i++){
		Employee* aux = ll_get(pArrayListEmployee, i);
		employee_getId(aux, &idAux);
		if(idAux > idMaximo){
			idMaximo = idAux;
		}
	}
	return idMaximo;
}


/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int opcion;
	int result = -1;
	int horas;
	int sueldo;
	char nombre[128];
	int idAux;
	Employee* auxEmp;
	controller_ListEmployee(pArrayListEmployee);
	if(GetEntero(&idAux, "Ingrese ID de Empleado a modificar: ", 1, EMPLOYEE_MAX_ID, 5) == 0){
		auxEmp = employee_getEmployeeById(pArrayListEmployee, idAux);
		if(auxEmp != NULL) {
			printf("\nModificar empleado");
			printf("\n 1. Modificar nombre");
			printf("\n 2. Modificar horas trabajadas");
			printf("\n 3. Modificar sueldo\n");
			GetEntero(&opcion, "Ingrese una opcion: ", 1, 3, 5);
			fflush(stdin);
			switch(opcion){
				case 1:
					if(GetString(nombre, "Ingrese nombre: ", "Error, reingrese nombre", MAX_CHAR_NOMBRE, MAX_REINTENTOS) == -1){
						break;
					}
					employee_setNombre(auxEmp, nombre);
					result = 0;
					break;
				case 2:
					if(GetEntero(&horas, "Ingrese horas trabajadas: ", 40, 250, MAX_REINTENTOS) == -1){
						break;
					}
					employee_setHorasTrabajadas(auxEmp, horas);
					result = 0;
					break;
				case 3:
					if(GetEntero(&sueldo, "Ingrese sueldo (solo entero): ", 20000, 250000, MAX_REINTENTOS) == -1){
						break;
					}
					employee_setSueldo(auxEmp, sueldo);
					result = 0;
					break;
				default:
					printf("\nError. Opcion invalida.");
					break;
			}
		}
	}
	return result;
}


/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int result = -1;
	int idAux;
	int opcion;
	Employee* aux;
	controller_ListEmployee(pArrayListEmployee);
	if(GetEntero(&idAux, "Ingrese ID de Empleado a eliminar: ", 1, EMPLOYEE_MAX_ID, 5) == 0){
		aux = employee_getEmployeeById(pArrayListEmployee, idAux);
		if(aux != NULL){
			printf("\nEsta seguro que desea eliminar a este empleado?: ");
			printf("\n1. Si, eliminar");
			printf("\n2. No, cancelar");
			if(GetEntero(&opcion, "Opcion: ", 1, 2, 5) == 0){
				if(opcion == 1){
					ll_remove(pArrayListEmployee, ll_indexOf(pArrayListEmployee, aux));
					result = 0;
				} else{
					printf("\nNo se elimino al empleado");
				}
			}
		} else {
			printf("\nError ID empleado inexistente.");
		}
	}
	return result;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int result = -1;
	int opcion;
	int criterio;
	printf("\nDesea ordenar la lista por orden alfabetico ascendente o descendente?");
	printf("\n1. Ascendente");
	printf("\n2. Descendente");
	if(GetEntero(&opcion, "Opcion: ", 1, 2, 5) == 0){
		if(opcion == 1){
			criterio = 1;
		} else {
			criterio = 0;
		}
		printf("\nOrdenando...");
		if(ll_sort(pArrayListEmployee, employee_criteriaFunction, criterio) == 0){
			printf("\nLista de empleados ordenada satisfactoriamente.");
			result = 0;
		}
	}
    return result;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	Employee* aux;
	FILE* pFile;
	int i;
	int result = -1;
	int id;
	char nombre[129];
	int horas;
	int sueldo;
	i = 0;
	int length;
	pFile = fopen("data_exported.csv", "w");
	if(pFile != NULL && pArrayListEmployee != NULL){
		length = ll_len(pArrayListEmployee);
		fprintf(pFile, "ID,NOMBRE,HORAS TRABAJADAS,SUELDO\n");
		for(i=0;i<length;i++){
			aux = (Employee*) ll_get(pArrayListEmployee, i);
			if(employee_getId(aux, &id) == 0
					&& employee_getNombre(aux, nombre) == 0
						&& employee_getHorasTrabajadas(aux, &horas) == 0
							&& employee_getSueldo(aux, &sueldo) == 0){
				fprintf(pFile, "%d,%s,%d,%d\n", id, nombre, horas, sueldo);
				result = 0;
			}
		}
	}
	fclose(pFile);
    return result;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	Employee* pEmployeeAux;
	FILE* pFile;
	int i;
	int result = -1;
	int id;
	char nombre[129];
	int horas;
	int sueldo;
	i = 0;
	int length;
	pFile = fopen("data_exported.bin", "wb");
	if(pFile != NULL && pArrayListEmployee != NULL){
		length = ll_len(pArrayListEmployee);
		//fprintf(pFile, "ID,NOMBRE,HORAS TRABAJADAS,SUELDO\n");
		for(i=0;i<length;i++){
			pEmployeeAux = (Employee*) ll_get(pArrayListEmployee, i);
			if(employee_getId(pEmployeeAux, &id) == 0
					&& employee_getNombre(pEmployeeAux, nombre) == 0
						&& employee_getHorasTrabajadas(pEmployeeAux, &horas) == 0
							&& employee_getSueldo(pEmployeeAux, &sueldo) == 0){
				fwrite(pEmployeeAux, sizeof(Employee), 1, pFile);
				result = 0;
			}
		}
	}
	fclose(pFile);
	return result;
}

