#include <stdio.h>

typedef struct {
    char model[50];
    int year;
    int price;
} Car;

int main() {

    Car cars[] = {{"Toyota Camry", 2020, 24000},
                  {"Honda Accord", 2021, 26000},
                  {"Ford Mustang", 2019, 35000}};

    printf("Car 1: %s, Year: %d, Price: $%d\n", cars[0].model, cars[0].year, cars[0].price);
    printf("Car 2: %s, Year: %d, Price: $%d\n", cars[1].model, cars[1].year, cars[1].price);
    printf("Car 3: %s, Year: %d, Price: $%d\n", cars[2].model, cars[2].year, cars[2].price);
 
    return 0;

}
