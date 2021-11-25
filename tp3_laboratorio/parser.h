

int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee);
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee);
int parser_getLastIdFromFile(void);
void parser_saveLastIdInFile(int id);
Employee* employee_getEmployeeById(LinkedList* listaEmpleados, int idEmployee);
void employee_showEmployee(Employee* employee);
