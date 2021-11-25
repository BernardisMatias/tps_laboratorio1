#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "funciones.h"
#include "parser.h"

int main()
{
	setbuf(stdout, NULL);
	int opcion;
	int idEmployee = 1;
	int cantEmpleados = 0;
	//int flagGuardoEnArchivo = 0;
    LinkedList* listaEmpleados = ll_newLinkedList();
	parser_saveLastIdInFile(idEmployee);
    do{
    	printf("\n -- SISTEMA DE REGISTRO DE EMPLEADOS --");
    	printf("\n 1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).");
    	printf("\n 2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).");
        printf("\n 3. Alta de empleado");
    	printf("\n 4. Modificar datos de empleado");
    	printf("\n 5. Baja de empleado");
    	printf("\n 6. Listar empleados");
        printf("\n 7. Ordenar empleados");
    	printf("\n 8. Guardar los datos de los empleados en el archivo data.csv (modo texto).");
    	printf("\n 9. Guardar los datos de los empleados en el archivo data.csv (modo binario).");
    	printf("\n 10. Salir\n");
        GetEntero(&opcion, "Ingrese una opcion: ", 1, 10, 20);

        switch(opcion){
			case 1:
				if(controller_loadFromText("", listaEmpleados) > 0){
					cantEmpleados += ll_len(listaEmpleados);
					printf("\nEmpleados cargados con exito.");
				} else {
					printf("\nError cargando los empleados (csv).");
				}
				break;
			case 2:
				if(controller_loadFromBinary("", listaEmpleados) > 0){
					cantEmpleados += ll_len(listaEmpleados);
					printf("\nEmpleados cargados con exito.");
				}else {
					printf("\nError cargando los empleados (bin).");
				}
				break;
			case 3:
				if(controller_addEmployee(listaEmpleados) == 0){
					cantEmpleados++;
					printf("\nEmpleado guardado exitosamente");
				} else {
					printf("\nError al guardar un empleado.");
				}
				break;
			case 4:
				if(controller_editEmployee(listaEmpleados) == 0){
					printf("\nEmpleado modificado exitosamente");
				} else {
					printf("\nError al modificar un empleado.");
				}
				break;
			case 5:
				if(controller_removeEmployee(listaEmpleados) == 0){
					cantEmpleados--;
					printf("\nEmpleado eliminado exitosamente");
				} else {
					printf("\nError al eliminar un empleado.");
				}
				break;
			case 6:
				controller_ListEmployee(listaEmpleados);
				break;
			case 7:
				if(controller_sortEmployee(listaEmpleados) == 0){
					printf("\nEmpleados ordenados exitosamente.");
				}
				break;
			case 8:
				if(controller_saveAsText("", listaEmpleados) == 0){
					printf("\nArchivo .csv exportado exitosamente.");
				} else {
					printf("\nOcurrio un error exportando el archivo.");
				}
				break;
			case 9:
				if(controller_saveAsBinary("", listaEmpleados) == 0){
					printf("\nArchivo .bin exportado exitosamente.");
				} else {
					printf("\nOcurrio un error exportando el archivo.");
				}
				break;
			case 10:
				printf("\nGracias! Adios");
				break;
			default:
				printf("\nPor favor ingrese una opcion valida");
				break;
        }
    }while(opcion != 10);
    return 0;
}

