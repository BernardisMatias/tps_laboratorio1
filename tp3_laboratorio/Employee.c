#include "Employee.h"

Employee* employee_new(){
	return (Employee*) malloc(sizeof(Employee));
}

Employee* employee_newParametros(char* idStr, char* nombreStr, char* horasTrabajadasStr, char* sueldo){
	Employee* this = employee_new();
	employee_setId(this, atoi(idStr));
	employee_setNombre(this, nombreStr);
	employee_setHorasTrabajadas(this, atoi(horasTrabajadasStr));
	employee_setSueldo(this, atoi(sueldo));
	return this;
}

int employee_criteriaFunction(void* item1, void* item2){
	int result = -2;
	char nombre1[128];
	char nombre2[128];
	Employee* aux1;
	Employee* aux2;

	aux1 = (Employee*) item1;
	aux2 = (Employee*) item2;

	if(employee_getNombre(aux1, nombre1) == 0
		&& employee_getNombre(aux2, nombre2) == 0){
		result = strcmp(nombre1, nombre2);
	}
	return result;
}

int employee_setId(Employee* this, int id){
	this->id = id;
	return 0;
}

int employee_setNombre(Employee* this, char* nombre){
	strcpy(this->nombre, nombre);
	return 0;
}
int employee_setHorasTrabajadas(Employee* this, int horasTrabajadas){
	this->horasTrabajadas = horasTrabajadas;
	return 0;
}
int employee_setSueldo(Employee* this,int sueldo){
	this->sueldo = sueldo;
	return 0;
}

int employee_getNombre(Employee* this,char* nombre){
	int result = -1;
	if(this->nombre != NULL){
		result = 0;
		strcpy(nombre, this->nombre);
	}
	return result;
}

int employee_getSueldo(Employee* this,int* sueldo){
	int result = -1;
	if(this->sueldo >= 0){
		*sueldo = this->sueldo;
		result = 0;
	}
	return result;
}

int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas){
	int result = -1;
	if(this->horasTrabajadas >= 0){
		*horasTrabajadas = this->horasTrabajadas;
		result = 0;
	}
	return result;
}

int employee_getId(Employee* this, int* id){
	int result = -1;
	if(this->id > 0){
		result = 0;
		*id = this->id;
	}
	return result;
}
