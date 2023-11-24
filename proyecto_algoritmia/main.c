#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

// variable = opcion != 'c';

#define MAX_PRODUCT_NAME_LENGTH 25

const short int red=100, green=010, blue=001, yellow=110, cyan=011, original=111;
const char create='c', read='r', update='u', delete='d'; // CRUD

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

void welcome_message(){
    font_colour(yellow);
    printf("Bienvenido! Antes de comenzar, se necesita que ingrese los datos para los ");
    font_colour(green);
    printf("productos, vendedores y zonas");
    font_colour(yellow);
    printf(". Una vez finalizado este proceso podra comenzar a utilizar el programa.\n\n");
}

/*MENUS*/
void show_main_menu(){
    font_colour(blue);
    printf("\n\n\n-- MENU --\n");
    font_colour(original);
    printf("(1) Insertar\n(2) Mostrar\n(3) Actualizar\n(4) Eliminar\n\n");
    font_colour(yellow);
    printf("Ingrese \"0\" para salir");
    font_colour(original);
    printf("\n> ");
}

void show_sec_actions_menu(char action){
    font_colour(blue);
    if(action=='c'){
        printf("\t-- INSERTAR --\n");
    } else if (action=='r'){
        printf("\t-- MOSTRAR --\n");
    } else if (action=='u') {
        printf("\t-- ACTUALIZAR --\n");
    } else if (action=='d') {
        printf("\t-- ELIMINAR --\n");
    }
    font_colour(original);
    printf("\t(1) Producto\n\t(2) Vendedor\n\t(3) Zona\n");
    font_colour(yellow);
    printf("Ingrese \"0\" para salir");
    font_colour(original);
    printf("\n> ");
}

void show_product_menu(char action, short int id[5], char *name[5]){
    short int i;
    printf("Escriba el ID del producto que desea ");
    if (action == 'u') {
        printf("modificar:\n");
    } else if (action == 'd') {
        printf("eliminar:\n");
    }
    font_colour(cyan);
    for(i=0; i<5; i++){
        printf("\t(%d) %s\n", id[i], name[i]);
    }
    font_colour(yellow);
    printf("Ingrese \"0\" para salir");
    font_colour(original);
    printf("\n> ");
}

void show_seller_menu(char action, short int id[5], char *name[5]){
    short int i;
    printf("Escriba el ID del vendedor que desea ");
    if (action == 'u') {
        printf("modificar:\n");
    } else if (action == 'd') {
        printf("eliminar:\n");
    }
    font_colour(cyan);
    for(i=0; i<10; i++){
        printf("\t(%d) %s\n", id[i], name[i]);
    }
    font_colour(yellow);
    printf("Ingrese \"0\" para salir");
    font_colour(original);
    printf("\n> ");
}

void show_zone_menu(char action, short int id[5], char *name[5]){
    short int i;
    printf("Escriba el ID de la zona que desea ");
    if (action == 'u') {
        printf("modificar:\n");
    } else if (action == 'd') {
        printf("eliminar:\n");
    }
    font_colour(cyan);
    for(i=0; i<5; i++){
        printf("\t(%d) %s\n", id[i], name[i]);
    }
    font_colour(yellow);
    printf("Ingrese \"0\" para salir");
    font_colour(original);
    printf("\n> ");
}

//delete
/*MOSTRAR*/
void print_products(short int id[5], char *name[5], char *type[5], float purchPrice[5], float sellPrice[5], float revenue[5], short int amountSold[5]) {
    short int i;
    font_colour(cyan);
    printf("\n{\n\t\"Productos\": [\n");
    for (i = 0; i < 5; i++) {
        printf("\t\t{\n\t\t\tID: %hd,\n", id[i]);
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

/*ACTUALIZAR*/
// Similar a insertar, colocando los valores anteriores del campo para modificarlos
/*En funciones void, las variables tomadas como parametro solo se afectan de forma local,
  es decir, dentro de la funcion. Pero al pasar un array o una referencia a un array (un pointer)
  el cambio realizado a la variable dentro de la funcion tambien afectara a la variable original.

  En este caso, name y type hacen referencia a sus arrays, ademas, sell/purchPrice y revenue son
  pasadas como pointers para que los cambios hechos a estas se conserven. Los cambios a sell/purchPrice
  y revenue se deben hacer con * (en lugar de &), que representa un operador deferencia que cambiara el
  valor de la variable a la que hace referencia. Las posiciones de arrays (como idProd[2]) se toman como
  variables normales, por ende no aplican como array, por lo que su valor no se cambiaria  por la funcion,
  por ello se usan pointer para cambiar su valor en el array.
  */

void updateProductData(short int id, char *name, char *type, float *purchPrice, float *sellPrice, float *revenue) {
    font_colour(green);
    printf("\nProducto no. %hd:\n", id + 1);
    font_colour(original);

    font_colour(yellow);
    printf("\tNombre        > (%s) ", name);
    font_colour(original);
    scanf("%s", name);

    font_colour(yellow);
    printf("\tTipo          > (%s) ", type);
    font_colour(original);
    scanf("%s", type);

    font_colour(yellow);
    printf("\tPrecio_compra > (%.2f) ", *purchPrice);
    font_colour(original);
    scanf("%f", purchPrice);

    font_colour(yellow);
    printf("\tPrecio_venta  > (%.2f) ", *sellPrice);
    font_colour(original);
    scanf("%f", sellPrice);

    *revenue = *sellPrice - *purchPrice;

    font_colour(green);
    printf("\nProducto actualizado correctamente\n");
    font_colour(original);
}

/* Lo anterior podria llegar a aplicarse en estas 2 funciones tambien */
void updateSellerData(short int id, char *name) {
    font_colour(green);
    printf("\nVendedor no. %hd:\n", id + 1);
    font_colour(original);

    font_colour(yellow);
    printf("\tNombre        > (%s) ", name);
    font_colour(original);
    scanf("%s", name);

    font_colour(green);
    printf("\nVendedor actualizado correctamente\n");
    font_colour(original);
}

void updateZoneData(short int id, char *name) {
    font_colour(green);
    printf("\nZona no. %hd:\n", id + 1);
    font_colour(original);

    font_colour(yellow);
    printf("\tNombre        > (%s) ", name);
    font_colour(original);
    scanf("%s", name);

    font_colour(green);
    printf("\nZona actualizada correctamente\n");
    font_colour(original);
}

/*ELIMINAR*/
void deleteProduct(short int id, char *name, char *type, float *purchPrice, float *sellPrice, float *revenue, short int *amountSold){
    *name='\0';
    *type='\0';
    *purchPrice=0;
    *sellPrice=0;
    *revenue=0;
    *amountSold=0;

    font_colour(green);
    printf("\nProducto eliminado correctamente.\nPara volver a insertar un nuevo producto en esta posicion, debera ir a la seccion de \"Actualizar\" en el menu principal.\n");
    font_colour(original);
}

void deleteSeller(short int id, char *name, short int *amountSold, float *revenue){
    *name='\0';
    *revenue=0;
    *amountSold=0;

    font_colour(green);
    printf("\nVendedor eliminado correctamente.\nPara volver a insertar un nuevo vendedor en esta posicion, debera ir a la seccion de \"Actualizar\" en el menu principal.\n");
    font_colour(original);
}

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
    short int id;
    short int opc, i;

    welcome_message();

    font_colour(blue);
    printf("-- PRODUCTOS --\n");
    font_colour(original);
    for (i = 0; i < 5; i++) {
        enterProductData(i, prodName, prodType, prodPurchPrice, prodSellPrice, prodRevenue);
    }

    font_colour(blue);
    printf("\n\n-- VENDEDORES --\n");
    font_colour(original);
    for (i = 0; i < 10; i++) {
        enterSellerData(i, sellerName);
    }

    font_colour(blue);
    printf("\n\n-- ZONAS --\n");
    font_colour(original);
    for (i = 0; i < 5; i++) {
        enterZoneData(i, zoneName);
    }

    while (repeat) {
        show_main_menu();
        scanf("%hd", &opc);
        switch (opc) {
        case 1: // INSERTAR -------------------------------------------------------
            show_sec_actions_menu(create);
            scanf("%hd", &opc);
            if(opc==1){
                for (i = 0; i < 5; i++) {
                    enterProductData(i, prodName, prodType, prodPurchPrice, prodSellPrice, prodRevenue);
                }
                // print_products(idProd, prodName, prodType, prodPurchPrice, prodSellPrice, prodRevenue, prodAmountSold);
            } else if (opc==2){
                for (i = 0; i < 10; i++) {
                    enterSellerData(i, sellerName);
                }
                // print_sellers(idSeller, sellerName, sellerAmountSold, sellerRevenue);
            } else if (opc==3){
                for (i = 0; i < 5; i++) {
                    enterZoneData(i, zoneName);
                }
                // print_zones(idZone, zoneName, zoneAmountSold, zoneRevenue);
            } else if (opc==0){
                repeat=false;
            }
            break;

        case 2: // MOSTRAR--------------------------------------------------------
            show_sec_actions_menu(read);
            scanf("%hd", &opc);
            if (opc == 1) {
                print_products(idProd, prodName, prodType, prodPurchPrice, prodSellPrice, prodRevenue, prodAmountSold);
            } else if (opc == 2){
                print_sellers(idSeller, sellerName, sellerAmountSold, sellerRevenue);
            } else if (opc == 3){
                print_zones(idZone, zoneName, zoneAmountSold, zoneRevenue);
            } else if (opc==0){
                repeat=false;
            }
            break;

        case 3: // ACTUAIZAR -----------------------------------------------------
            show_sec_actions_menu(update);
            scanf("%hd", &opc);
            if(opc==1){
                show_product_menu(update, idProd, prodName);
                scanf("%hd", &id);

                if(id>=1 && id<=5) {
                    updateProductData(idProd[id-1], prodName[id-1], prodType[id-1], &prodPurchPrice[id-1], &prodSellPrice[id-1], &prodRevenue[id-1]);
                } else {
                    font_colour(red);
                    printf("\nValor invalido.\n");
                    font_colour(original);
                }
            } else if (opc==2){
                show_seller_menu(update, idSeller, sellerName);
                scanf("%hd", &id);

                if(id>=1 && id<=10) {
                    updateSellerData(idSeller[id-1], sellerName[id-1]);
                } else {
                    font_colour(red);
                    printf("\nValor invalido.\n");
                    font_colour(original);
                }
            } else if (opc==3){
                show_zone_menu(update, idZone, zoneName);
                scanf("%hd", &id);

                if(id>=1 && id<=5) {
                    updateZoneData(idZone[id-1], zoneName[id-1]);
                } else {
                    font_colour(red);
                    printf("\nValor invalido.\n");
                    font_colour(original);
                }
            } else if (opc==0){
                repeat=false;
                break;
            }
            break;

        case 4: // ELIMINAR -------------------------------------------------------
            show_sec_actions_menu(delete);
            scanf("%hd", &opc);

            if(opc==1){
                show_product_menu(delete, idProd, prodName);
                scanf("%hd", &id);

                if(id>=1 && id<=5) {
                    deleteProduct(idProd[id-1], prodName[id-1], prodType[id-1], &prodPurchPrice[id-1], &prodSellPrice[id-1], &prodRevenue[id-1], &prodAmountSold[id-1]);
                } else {
                    font_colour(red);
                    printf("\nValor invalido.\n");
                    font_colour(original);
                }
            } else if (opc==2){
                show_seller_menu(delete, idSeller, sellerName);
                scanf("%hd", &id);

                if(id>=1 && id<=10) {
                    deleteSeller(idSeller[id-1], sellerName[id-1], &sellerAmountSold[id-1], &sellerRevenue[id-1]);
                } else {
                    font_colour(red);
                    printf("\nValor invalido.\n");
                    font_colour(original);
                }
            } else if (opc==0){
                repeat=false;
            }
            break;
        default:
            repeat=false;
            break;
        }
    }
    return 0;
}
