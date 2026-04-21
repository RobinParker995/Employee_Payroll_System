#include <stdio.h>
#include<string.h>
#include <stdlib.h>

struct Employee
{
    int id;
    char name[50];
    float basicSalary;
    float hra;
    float da;
    float grossSalary;
    float tax;
    float netSalary;
};

int main()
{
     setbuf(stdout, NULL);

    int n, i;
    char buffer[100];

    printf("Enter number of employees: ");
    fgets(buffer, sizeof(buffer), stdin);
    n = (int)strtol(buffer, NULL, 10);

    struct Employee emp[n];

    for (i = 0; i < n; i++)
    {
        printf("\n--- Enter details for Employee %d ---\n", i + 1);

        // ID
        printf("Enter ID: ");
        fgets(buffer, sizeof(buffer), stdin);
        emp[i].id = (int)strtol(buffer, NULL, 10);

        // Name
        printf("Enter Name: ");
        fgets(emp[i].name, sizeof(emp[i].name), stdin);

        // Remove newline from name
        emp[i].name[strcspn(emp[i].name, "\n")] = '\0';

        // Basic Salary
        printf("Enter Basic Salary: ");
        fgets(buffer, sizeof(buffer), stdin);
        emp[i].basicSalary = strtof(buffer, NULL);

        // Calculations
        emp[i].hra = 0.20 * emp[i].basicSalary;
        emp[i].da = 0.10 * emp[i].basicSalary;
        emp[i].grossSalary = emp[i].basicSalary + emp[i].hra + emp[i].da;

        if (emp[i].grossSalary > 50000)
            emp[i].tax = 0.10 * emp[i].grossSalary;
        else
            emp[i].tax = 0.05 * emp[i].grossSalary;

        emp[i].netSalary = emp[i].grossSalary - emp[i].tax;
    }

    printf("\n\n===== Employee Payroll Details =====\n");

    for (i = 0; i < n; i++)
    {
        printf("\nEmployee %d\n", i + 1);
        printf("ID: %d\n", emp[i].id);
        printf("Name: %s\n", emp[i].name);
        printf("Basic Salary: %.2f\n", emp[i].basicSalary);
        printf("HRA: %.2f\n", emp[i].hra);
        printf("DA: %.2f\n", emp[i].da);
        printf("Gross Salary: %.2f\n", emp[i].grossSalary);
        printf("Tax: %.2f\n", emp[i].tax);
        printf("Net Salary: %.2f\n", emp[i].netSalary);
    }

    return 0;
}
