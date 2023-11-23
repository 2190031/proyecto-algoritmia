#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

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

/*MENUS*/
void show_main_menu(){
    font_colour(blue);
    printf("-- MENU --\n");
    font_colour(original);
    printf("(1) Insertar\n(2) Mostrar\n(3) Eliminar\n> ");
}

void show_insert_menu(){
    font_colour(blue);
    printf("\t-- INSERTAR --\n");
    font_colour(original);
    printf("\t(1) Producto\n\t(2) Vendedor\n\t(3) Zona\n> ");
}

void show_view_menu(){
    font_colour(blue);
    printf("\t-- MOSTRAR --\n");
    font_colour(original);
    printf("\t(1) Producto\n\t(2) Vendedor\n\t(3) Zona\n> ");
}

void show_delete_menu(){
    font_colour(blue);
    printf("\t-- ELIMINAR --\n");
    font_colour(original);
    printf("\t(1) Producto\n\t(2) Vendedor\n\t(3) Zona\n> ");
}

/*MOSTRAR*/
void print_products(short int id[5], char *name[5], char *type[5], float purchPrice[5], float sellPrice[5], float revenue[5], short int amountSold[5]) {
    short int i;
    font_colour(cyan);
    printf("\n{\n\t\"Productos\": [\n");
    for (i = 0; i < 5; i++) {
        printf("\t\t{\n\t\t\t\"ID\": %hd,\n", id[i]);
        printf("\t\t\tNombre: \"%s\",\n", name[i]);
        printf("\t\t\tTipo: \"%s\",\n", type[i]);
        printf("\t\t\tPrecio_compra: %.2f,\n", purchPrice[i]);
        printf("\t\t\tPrecio_venta: %.2f,\n", sellPrice[i]);
        printf("\t\t\tGanancia: %.2f,\n", revenue[i]);
        if (i<4) {
            printf("\t\t\tCantidad_vendida: %hd\n\t\t},\n", amountSold[i]);
        } else if (i==4) {
            printf("\t\t\tCantidad_vendida: %hd\n\t\t}\n", amountSold[i]);
        }
    }
    printf("\t]\n}\n");
    font_colour(original);
}

void print_sellers(short int id[5], char *name[5], short int amountSold[5], float revenue[5]) {
    short int i;
    font_colour(cyan);
    printf("\n{\n\t\"Vendedores\": [\n");
    for (i = 0; i < 10; i++) {
        printf("\t\t{\n\t\t\t\"ID\": %hd,\n", id[i]);
        printf("\t\t\tNombre: \"%s\",\n", name[i]);
        printf("\t\t\tCantidad_ventas: %hd,\n", amountSold[i]);
        if (i<9) {
            printf("\t\t\tGanancias: %.2f\n\t\t},\n", revenue[i]);
        } else if (i==9) {
            printf("\t\t\tGanancias: %.2f\n\t\t}\n", revenue[i]);
        }
    }
    printf("\t]\n}\n");
    font_colour(original);
}

void print_zones(short int id[5], char *name[5], short int amountSold[5], float revenue[5]) {
    short int i;
    font_colour(cyan);
    printf("\n{\n\t\"Zonas\": [\n");
    for (i = 0; i < 5; i++) {
        printf("\t\t{\n\t\t\t\"ID\": %hd,\n", id[i]);
        printf("\t\t\tNombre: \"%s\",\n", name[i]);
        printf("\t\t\tCantidad_ventas: %hd,\n", amountSold[i]);
        if (i<4) {
            printf("\t\t\tGanancias: %.2f\n\t\t},\n", revenue[i]);
        } else if (i==4) {
            printf("\t\t\tGanancias: %.2f\n\t\t}\n", revenue[i]);
        }
    }
    printf("\t]\n}\n");
    font_colour(original);
}

/*INSERTAR*/
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

void enterSellerData(short int i, char *name[5]) {
    name[i] = (char *)malloc(MAX_PRODUCT_NAME_LENGTH + 1);

    if (name[i] == NULL) {
        // Handle allocation failure
        font_colour(red);
        fprintf(stderr, "Memory allocation failed.\n");
        font_colour(original);
        exit(EXIT_FAILURE);
    }

    font_colour(green);
    printf("\nVendedor no. %hd:\n", i + 1);
    font_colour(original);

    font_colour(yellow);
    printf("\tNombre        > ");
    font_colour(original);
    scanf("%s", name[i]);
}

void enterZoneData(short int i, char *name[5]) {
    name[i] = (char *)malloc(MAX_PRODUCT_NAME_LENGTH + 1);

    if (name[i] == NULL) {
        // Handle allocation failure
        font_colour(red);
        fprintf(stderr, "Memory allocation failed.\n");
        font_colour(original);
        exit(EXIT_FAILURE);
    }

    font_colour(green);
    printf("\nZona no. %hd:\n", i + 1);
    font_colour(original);

    font_colour(yellow);
    printf("\tNombre        > ");
    font_colour(original);
    scanf("%s", name[i]);
}

/*ELIMINAR*/
int main() {
    bool repeat = true;

    short int idSeller [10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    short int idProd [5] = {1, 2, 3, 4, 5};
    short int idZone [5] = {1, 2, 3, 4, 5};

    char *sellerName [10], *prodName [5], *zoneName [5], *prodType [5];

    short int sellerAmountSold [10] = {0,0,0,0,0,0,0,0,0,0};
    short int prodAmountSold [5] = {0,0,0,0,0};
    short int zoneAmountSold [5] = {0,0,0,0,0};

    float prodPurchPrice [5], prodSellPrice [5];
    float sellerRevenue [10] = {0,0,0,0,0,0,0,0,0,0}, prodRevenue [5], zoneRevenue [5] = {0,0,0,0,0};

    int short sales [10][2];

    short int opc, i;
    while (repeat) {
        show_main_menu();
        scanf("%hd", &opc);
        switch (opc) {
        case 1:
            show_insert_menu();
            scanf("%hd", &opc);
            switch (opc) {
            case 1:
                for (i = 0; i < 5; i++) {
                    enterProductData(i, prodName, prodType, prodPurchPrice, prodSellPrice, prodRevenue);
                }
                // print_products(idProd, prodName, prodType, prodPurchPrice, prodSellPrice, prodRevenue, prodAmountSold);
                break;
            case 2:
                for (i = 0; i < 10; i++) {
                    enterSellerData(i, sellerName);
                }
                // print_sellers(idSeller, sellerName, sellerAmountSold, sellerRevenue);
                break;
            case 3:
                for (i = 0; i < 5; i++) {
                    enterZoneData(i, zoneName);
                }
                // print_zones(idZone, zoneName, zoneAmountSold, zoneRevenue);
                break;
            default:
                break;
            }
        case 2:
            show_view_menu();
            scanf("%hd", &opc);
            switch (opc) {
            case 1:
                print_products(idProd, prodName, prodType, prodPurchPrice, prodSellPrice, prodRevenue, prodAmountSold);
                break;
            case 2:
                print_sellers(idSeller, sellerName, sellerAmountSold, sellerRevenue);
                break;
            case 3:
                print_zones(idZone, zoneName, zoneAmountSold, zoneRevenue);
                break;
            default:
                break;
            }
        case 3:
        show_delete_menu();
            scanf("%hd", &opc);
            switch (opc) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                break;
            }
            break;
        default:
            repeat=false;
            break;
        }
    }
    return 0;
}
