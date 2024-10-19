#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "car_rental.txt"

typedef struct
{
    char name[20];
    char model[20];
    int year;
    float price;
    int isAvailable;
} Car;

void addCar();
void removeCar();
void listCars();
void rentCar();
void returnCar();

int main()
{
    int choice;

    do
    {
        printf("\n***** Car Rental System *****\n");
        printf("1. Add a Car\n");
        printf("2. Remove a Car\n");
        printf("3. List Cars\n");
        printf("4. Rent a Car\n");
        printf("5. Return a Car\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addCar();
            break;
        case 2:
            removeCar();
            break;
        case 3:
            listCars();
            break;
        case 4:
            rentCar();
            break;
        case 5:
            returnCar();
            break;
        case 6:
            printf("Exiting the program. Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
            break;
        }
    } while (choice != 6);

    return 0;
}

void addCar()
{
    Car car;
    FILE *file = fopen(FILE_NAME, "a");

    printf("\nEnter Car Details:\n");
    printf("Name: ");
    scanf("%s", car.name);
    printf("Model: ");
    scanf("%s", car.model);
    printf("Year: ");
    scanf("%d", &car.year);
    printf("Price: ");
    scanf("%f", &car.price);

    car.isAvailable = 1;

    fprintf(file, "%s %s %d %.2f %d\n", car.name, car.model, car.year, car.price, car.isAvailable);
    fclose(file);

    printf("\nCar added successfully!\n");
}

void removeCar()
{
    int found = 0;
    char name[20];
    Car car;
    FILE *file = fopen(FILE_NAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    printf("\nEnter the model of the car to be removed: ");
    scanf("%s", name);

    while (fscanf(file, "%s %s %d %f %d", car.name, car.model, &car.year, &car.price, &car.isAvailable) != EOF)
    {
        if (strcmp(car.name, name) != 0)
        {
            fprintf(tempFile, "%s %s %d %.2f %d\n", car.name, car.model, car.year, car.price, car.isAvailable);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
    {
        printf("\nCar removed successfully!\n");
    }
    else
    {
        printf("\nCar not found!\n");
    }
    
}

void listCars()
{
    int option;
    char searchName[20];
    char searchModel[20];
    Car car;
    FILE *file = fopen(FILE_NAME, "r");

    printf("\n1. List all cars\n");
    printf("2. Search for a car by name\n");
    printf("Enter your option: ");
    scanf("%d", &option);

    if (option == 1)
    {
        printf("\nList of Available Cars:\n");
        while (fscanf(file, "%s %s %d %f %d", car.name, car.model, &car.year, &car.price, &car.isAvailable) != EOF)
        {
            if (car.isAvailable)
            {
                printf("Name: %s, Model: %s, Year: %d, Price: %.2f\n", car.name, car.model, car.year, car.price);
            }
        }
    }
    else if (option == 2)
    {
        printf("\nEnter the name of the car to search for: ");
        scanf("%s", searchName);
        printf("\nEnter the model of the car to search for: ");
        scanf("%s", searchModel);

        int found = 0;
        while (fscanf(file, "%s %s %d %f %d", car.name, car.model, &car.year, &car.price, &car.isAvailable) != EOF)
        {
            if (car.isAvailable && strcmp(car.name, searchName) == 0 && strcmp(car.model, searchModel) == 0)
            {
                printf("\nCar Found:\n");
                printf("Name: %s, Model: %s, Year: %d, Price: %.2f\n", car.name, car.model, car.year, car.price);
                found = 1;
                break;
            }
        }

        if (!found)
        {
            printf("\nCar not found!\n");
        }
    }
    else
    {
        printf("\nInvalid option!\n");
    }

    fclose(file);
}

void rentCar()
{
    char model[20];
    char name[20];
    Car car;
    FILE *file = fopen(FILE_NAME, "r+");
    FILE *tempFile = fopen("temp.txt", "w");
    int found = 0;

    printf("\nEnter the name of the car to be rented: ");
    scanf("%s", name);
    getchar();
    printf("\nEnter the model of the car to be rented: ");
    scanf("%s", model);

    while (fscanf(file, "%s %s %d %f %d", car.name, car.model, &car.year, &car.price, &car.isAvailable) != EOF)
    {
        if ((strcmp(car.model, model) == 0) && (strcmp(car.name, name) == 0))
        {
            if (car.isAvailable)
            {
                car.isAvailable = 0;

                found = 1;
                printf("\nCar rented successfully!\n");
            }
            else
            {
                printf("\nThe car is currently unavailable!\n");
            }
        }

        fprintf(tempFile, "%s %s %d %.2f %d\n", car.name, car.model, car.year, car.price, car.isAvailable);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (!found)
    {
        printf("\nCar not found!\n");
    }
}

void returnCar()
{
    char model[20];
    char name[20];
    Car car;
    FILE *file = fopen(FILE_NAME, "r+");
    FILE *tempFile = fopen("temp.txt", "w");
    int found = 0;

    printf("\nEnter the name of the car to be returned: ");
    scanf("%s", name);

    printf("\nEnter the model of the car to be returned: ");
    scanf("%s", model);

    while (fscanf(file, "%s %s %d %f %d", car.name, car.model, &car.year, &car.price, &car.isAvailable) != EOF)
    {
        if ((strcmp(car.model, model) == 0) && (strcmp(car.name, name) == 0))
        {
            if (!car.isAvailable)
            {
                car.isAvailable = 1;

                found = 1;
                printf("\nCar returned successfully!\n");
            }
            else
            {
                printf("\nThe car is already available!\n");
            }
        }

        fprintf(tempFile, "%s %s %d %.2f %d\n", car.name, car.model, car.year, car.price, car.isAvailable);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (!found)
    {
        printf("\nCar not found!\n");
    }
}
