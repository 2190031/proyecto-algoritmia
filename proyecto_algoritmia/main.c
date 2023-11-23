#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define MAX_PRODUCT_NAME_LENGTH 25

const short int red=100, green=010, blue=001, yellow=110, cyan=011, original=111;

void font_colour(short int colour){
    /*
        (rgb) 100 -> (255,0,0)     rojo
        (rgb) 010 -> (0,255,0)     verde
        (rgb) 001 -> (0,0,255)     azul
        (rgb) 110 -> (255,255,0)   amarillo
        (rgb) 011 -> (0,255,255)   cyan
        (rgb) 111 -> (255,255,255) blanco
    */

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (colour) {
    case 100: // red
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        break;
    case 010: // green
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;
    case 001: // blue
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        break;
    case 110: // yellow
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        break;
    case 011: // cyan
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        break;
    case 111: // white
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
        break;
    default:
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    }
}

void show_main_menu(){
    font_colour(blue);
    printf("-- MENU --\n");
    font_colour(original);
    printf("(1) Insertar\n(2)...\n> ");
}

void print_products(
    short int idProd[5],
    char *prodName[5],
    char *prodType[5],
    float prodPurchPrice[5],
    float prodSellPrice[5],
    float prodRev[5],
    short int prodAmountSold[5]
    ) {
    short int i;
    font_colour(cyan);
    printf("\n{\n\t\"Productos\": [\n");
    for (i = 0; i < 5; i++) {
        if (i<4) {
            printf("\t\t{\n\t\t\t\"ID\": %hd,\n", idProd[i]);
            printf("\t\t\tNombre: \"%s\",\n", prodName[i]);
            printf("\t\t\tTipo: \"%s\",\n", prodType[i]);
            printf("\t\t\tPrecio_compra: %.2f,\n", prodPurchPrice[i]);
            printf("\t\t\tPrecio_venta: %.2f,\n", prodSellPrice[i]);
            printf("\t\t\tGanancia: %.2f,\n", prodRev[i]);
            printf("\t\t\tCantidad_vendida: %hd\n\t\t},\n", prodAmountSold[i]);
        } else if (i==4) {
            printf("\t\t{\n\t\t\t\"ID\": %hd,\n", idProd[i]);
            printf("\t\t\tNombre: \"%s\",\n", prodName[i]);
            printf("\t\t\tTipo: \"%s\",\n", prodType[i]);
            printf("\t\t\tPrecio_compra: %.2f,\n", prodPurchPrice[i]);
            printf("\t\t\tPrecio_venta: %.2f,\n", prodSellPrice[i]);
            printf("\t\t\tGanancia: %.2f,\n", prodRev[i]);
            printf("\t\t\tCantidad_vendida: %hd\n\t\t}\n", prodAmountSold[i]);
        }
    }
    printf("\t]\n}\n");
    font_colour(original);
}

void enterProductData(short int i, char *name[5], char *type[5], float purchPrice[5], float sellPrice[5], float revenue[5]) {
    name[i] = (char *)malloc(MAX_PRODUCT_NAME_LENGTH + 1);
    type[i] = (char *)malloc(MAX_PRODUCT_NAME_LENGTH + 1);

    if (name[i] == NULL || type[i] == NULL) {
        // Handle allocation failure
        font_colour(red);
        fprintf(stderr, "Memory allocation failed.\n");
        font_colour(original);
        exit(EXIT_FAILURE);
    }
    
    font_colour(green);
    printf("\nProducto no. %hd:\n", i + 1);
    font_colour(original);

    font_colour(yellow);
    printf("\tNombre        > ");
    font_colour(original);
    scanf("%s", name[i]);

    font_colour(yellow);
    printf("\tTipo          > ");
    font_colour(original);
    scanf("%s", type[i]);

    font_colour(yellow);
    printf("\tPrecio_compra > ");
    font_colour(original);
    scanf("%f", &purchPrice[i]);
    
    font_colour(yellow);
    printf("\tPrecio_venta  > ");
    font_colour(original);
    scanf("%f", &sellPrice[i]);

    revenue[i] = sellPrice[i] - purchPrice[i];
}

int main() {
    short int id_seller [10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    short int idProd [5] = {1, 2, 3, 4, 5};
    short int id_zone [5] = {1, 2, 3, 4, 5};

    char *sell_name [10], *prodName [5], *zone_name [5], *prodType [5];
    short int sell_amount_sold [10], prodAmountSold [5] = {0,0,0,0,0}, zone_amount_sold [5];
    float prodPurchPrice [5], prodSellPrice [5];
    float sell_rev [10], prodRev [5], zone_rev [5];

    int short sales [10][2];

    short int opc, i;
    show_main_menu();
    scanf("%hd", &opc);
    switch (opc) {
    case 1:
        for (i = 0; i < 5; i++) {
            enterProductData(i, prodName, prodType, prodPurchPrice, prodSellPrice, prodRev);
        }
        print_products(idProd, prodName, prodType, prodPurchPrice, prodSellPrice, prodRev, prodAmountSold);
        break;
    default:
        break;
    }
    return 0;
}
