#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

// variable = opcion != 'c';

#define MAX_STR_INPUT_LENGTH 25

const short int red=100, green=010, blue=001, yellow=110, cyan=011, original=111;
const char create='c', read='r', update='u', delete='d', sell='s'; // CRUD

/*Cambio de colores en la consola*/
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
    WORD attributes = 0;

    switch (colour) {
    case 100: // red
        attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
        break;
    case 010: // green
        attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        break;
    case 001: // blue
        attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        break;
    case 110: // yellow
        attributes = FOREGROUND_RED | FOREGROUND_GREEN;
        break;
    case 011: // cyan
        attributes = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        break;
    case 111: // white
        attributes = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
        break;
    default:
        attributes = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
    }
    SetConsoleTextAttribute(hConsole, attributes);
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
    printf("(1) Ventas\n(2) Mostrar\n(3) Actualizar\n(4) Eliminar\n(5) Estadisticas\n\n");
    font_colour(yellow);
    printf("Ingrese \"0\" para salir");
    font_colour(original);
    printf("\n> ");
}

void show_statistics_menu(){
    font_colour(blue);
    printf("\t-- ESTADISTICAS --\n");
    font_colour(original);
    printf("\t(1) Importe de ventas por vendedor\n\t(2) Mejor vendedor por zona\n\t(3) Mejor vendedor\n\t(4) Vendedores sin ventas\n");
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
    } else if (action=='u') {''
        printf("\t-- ACTUALIZAR --\n");
    } else if (action=='d') {
        printf("\t-- ELIMINAR --\n");
    }
    font_colour(original);
    if(action!='d'){
        printf("\t(1) Producto\n\t(2) Vendedor\n\t(3) Zona\n");
    } else {
        /*La zona no puede eliminarse*/
        printf("\t(1) Producto\n\t(2) Vendedor\n");
    }
    font_colour(yellow);
    printf("Ingrese \"0\" para salir");
    font_colour(original);
    printf("\n> ");
}

/*
Menu listado de productos, segun action cambiara el proposito del menu
Recibe los ID de los productos y sus nombres para mostrar
*/
void show_product_menu(char action, short int id[5], char *name[5]){
    short int i;
    printf("Escriba el ID del producto que ");
    if (action == 'u') {
        printf("desea modificar:\n");
    } else if (action == 'd') {
        printf("desea eliminar:\n");
    } else {
        printf("se vendio:\n");
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

/*
Lo mismo que lo anterior para los vendedores
*/
void show_seller_menu(char action, short int id[5], char *name[5]){
    short int i;
    printf("Escriba el ID del vendedor que ");
    if (action == 'u') {
        printf("desea modificar:\n");
    } else if (action == 'd') {
        printf("desea eliminar:\n");
    } else {
        printf("realizo la venta:\n");
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

/*
Lo mismo para las zonas. Las zonas no se eliminan, asi que no hay alternativas
*/
void show_zone_menu(char action, short int id[5], char *name[5]){
    short int i;
    if(action=='u'){
        printf("Escriba el ID de la zona que desea modificar:\n");
    } else {
        printf("Escriba el ID de la zona en la que se realizo la venta:\n");
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

// void show_sales_menu(){
//     font_colour(blue);
//     printf("-- VENTAS --");
//     font_colour(original);
//     printf("\t(1) Realizar venta\n\t(2) Consultar ventas\n\t(3)\n");
// }

/*MOSTRAR*/
/*
Toma todos los datos relacionados a los productos y los muestra en un formato definido, lo mismo para vendedores y zonas. El formato puede cambiarse
*/
void print_products(short int id[5], char *name[5], char *type[5], float purchPrice[5], float sellPrice[5], float revenue[5], float totalRevenue[5], short int amountSold[5], bool orderByRevenue) {
    short int i, j;
    if(orderByRevenue){
        short int order[5]={0,1,2,3,4};

        for(i=0; i<5-1; i++){
            for(j=0; j<5-1-i; j++){
                if(totalRevenue[order[j]]<totalRevenue[order[j+1]]){
                    int tempIndex = order[j];
                    order[j] = order[j+1];
                    order[j+1] = tempIndex;
                }
            }
        }

        font_colour(blue);
        printf("\nProductos:\n");
        font_colour(cyan);
        for(i = 0; i < 5; i++) {
            if(purchPrice[i]==0 && sellPrice[i]==0 && revenue[i]==0 && name[i]=='\0' && type[i]=='\0') {
                printf("\tEl producto %hd no existe", id[order[i]]);
            } else {
                printf("\tID: %hd,\n", id[order[i]]);
                printf("\tNombre: \"%s\",\n", name[order[i]]);
                printf("\tTipo: \"%s\",\n", type[order[i]]);
                printf("\tPrecio_compra: %.2f,\n", purchPrice[order[i]]);
                printf("\tPrecio_venta: %.2f,\n", sellPrice[order[i]]);
                printf("\tGanancia: %.2f,\n", revenue[order[i]]);
                printf("\tGanancia_generada: %.2f,\n", totalRevenue[order[i]]);
                printf("\tCantidad_vendida: %hd,\n", amountSold[order[i]]);
                printf("\tCantidad_vendida: %hd\n\n", amountSold[order[i]]);
            }
        }
    } else {
        font_colour(blue);
        printf("\nProductos:\n");
        font_colour(cyan);
        for(i = 0; i < 5; i++) {
            if(purchPrice[i]==0 && sellPrice[i]==0 && revenue[i]==0 && name[i]=='\0' && type[i]=='\0') {
                printf("\tEl producto %hd no existe", id[i]);
            } else {
                printf("\tID: %hd,\n", id[i]);
                printf("\tNombre: \"%s\",\n", name[i]);
                printf("\tTipo: \"%s\",\n", type[i]);
                printf("\tPrecio_compra: %.2f,\n", purchPrice[i]);
                printf("\tPrecio_venta: %.2f,\n", sellPrice[i]);
                printf("\tGanancia: %.2f,\n", revenue[i]);
                printf("\tGanancia_generada: %.2f,\n", totalRevenue[i]);
                printf("\tCantidad_vendida: %hd,\n", amountSold[i]);
                printf("\tCantidad_vendida: %hd\n\n", amountSold[i]);
            }
        }
    }
    // printf("\n");
    font_colour(original);
}

void print_sellers(short int id[10], char *name[10], short int amountSold[10], float revenue[10]) {
    short int i;
    font_colour(blue);
    printf("\nVendedores:\n");
    font_colour(cyan);
    for (i = 0; i < 10; i++) {
        printf("\tID: %hd,\n", id[i]);
        printf("\tNombre: \"%s\",\n", name[i]);
        printf("\tCantidad_ventas: %hd,\n", amountSold[i]);
        printf("\tGanancias: %.2f\n\n", revenue[i]);
    }
    printf("\n");
    font_colour(original);
}

void print_zones(short int id[5], char *name[5], short int amountSold[5], float revenue[5]) {
    short int i;
    font_colour(cyan);
    printf("\nZonas:\n");
    for (i = 0; i < 5; i++) {
        printf("\tID: %hd,\n", id[i]);
        printf("\tNombre: \"%s\",\n", name[i]);
        printf("\tCantidad_ventas: %hd,\n", amountSold[i]);
        printf("\tGanancias: %.2f\n\n", revenue[i]);
    }
    printf("\n");
    font_colour(original);
}

/*INSERTAR*/
/*
(Explicacion del funcionamiento de los void mas abajo)
Recolecta los datos de los productos, vendedores y zonas y los almacena en sus arrays
*/
void removeTrailingNewline(char *str) {
    size_t length = strlen(str);
    if (length > 0 && str[length - 1] == '\n') {
        str[length - 1] = '\0';
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void enterProductData(short int i, char *name[5], char *type[5], float purchPrice[5], float sellPrice[5], float revenue[5]) {
    name[i] = (char *)malloc(MAX_STR_INPUT_LENGTH + 1);
    type[i] = (char *)malloc(MAX_STR_INPUT_LENGTH + 1);

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
    fgets(name[i], MAX_STR_INPUT_LENGTH, stdin);
    removeTrailingNewline(name[i]);
    // Remove the trailing newline character, if present
    // size_t length = strlen(name[i]);
    // if (length > 0 && name[length - 1] == '\n') {
    //     name[i][length - 1] = '\0';
    // }

    font_colour(yellow);
    printf("\tTipo          > ");
    font_colour(original);
    fgets(type[i], MAX_STR_INPUT_LENGTH, stdin);
    removeTrailingNewline(type[i]);
    // Remove the trailing newline character, if present

    font_colour(yellow);
    printf("\tPrecio_compra > ");
    font_colour(original);
    scanf("%f", &purchPrice[i]);
    clearInputBuffer();

    font_colour(yellow);
    printf("\tPrecio_venta  > ");
    font_colour(original);
    scanf("%f", &sellPrice[i]);
    clearInputBuffer();

    // La ganancia se calcula automaticamente
    revenue[i] = sellPrice[i] - purchPrice[i];
}

void enterSellerData(short int i, char *name[5]) {
    name[i] = (char *)malloc(MAX_STR_INPUT_LENGTH + 1);

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
    fgets(name[i], MAX_STR_INPUT_LENGTH, stdin);
    removeTrailingNewline(name[i]);
}

void enterZoneData(short int i, char *name[5]) {
    name[i] = (char *)malloc(MAX_STR_INPUT_LENGTH + 1);

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
    fgets(name[i], MAX_STR_INPUT_LENGTH, stdin);
    removeTrailingNewline(name[i]);
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
    clearInputBuffer();
    fgets(name, MAX_STR_INPUT_LENGTH, stdin);
    removeTrailingNewline(name);

    font_colour(yellow);
    printf("\tTipo          > (%s) ", type);
    font_colour(original);
    fgets(type, MAX_STR_INPUT_LENGTH, stdin);
    removeTrailingNewline(type);

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
    clearInputBuffer();
    fgets(name, MAX_STR_INPUT_LENGTH, stdin);
    removeTrailingNewline(name);

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
    clearInputBuffer();
    fgets(name, MAX_STR_INPUT_LENGTH, stdin);
    removeTrailingNewline(name);

    font_colour(green);
    printf("\nZona actualizada correctamente\n");
    font_colour(original);
}

/*ELIMINAR*/
/*
"Eliminar" consiste en reiniciar todos los campos (sea a "" o a 0)
*/
void deleteProduct(short int id, char *name, char *type, float *purchPrice, float *sellPrice, float *revenue, short int *amountSold){
    *name='\0';
    *type='\0';
    *purchPrice=0;
    *sellPrice=0;
    *revenue=0;
    *amountSold=0;
    // Reiniciar los valores de las ventas a futuro, y unidades vendidas
    font_colour(green);
    printf("\nProducto eliminado correctamente.\nPara volver a insertar un nuevo producto en esta posicion, debera ir a la seccion de \"Actualizar\" en el menu principal.\n");
    font_colour(original);
}

void deleteSeller(short int id, char *name, short int *amountSold, float *revenue){
    *name='\0';
    *revenue=0;
    *amountSold=0;
    // Reiniciar los valores de las ventas a futuro, y unidades vendidas
    font_colour(green);
    printf("\nVendedor eliminado correctamente.\nPara volver a insertar un nuevo vendedor en esta posicion, debera ir a la seccion de \"Actualizar\" en el menu principal.\n");
    font_colour(original);
}

/*VENDER*/

int main() {
    /*Declaracion de variables*/
    bool repeat = true;

    short int idSeller [10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    short int idProd [5] = {1, 2, 3, 4, 5};
    short int idZone [5] = {1, 2, 3, 4, 5};

    char *sellerName [10], *prodName [5], *zoneName [5], *prodType [5];

    short int sellerAmountSold [10] = {0,0,0,0,0,0,0,0,0,0}; // %hd
    short int prodAmountSold [5] = {0,0,0,0,0};
    short int zoneAmountSold [5] = {0,0,0,0,0};

    short int amountSoldPerSellerZone1 [10];
    short int amountSoldPerSellerZone2 [10];
    short int amountSoldPerSellerZone3 [10];
    short int amountSoldPerSellerZone4 [10];
    short int amountSoldPerSellerZone5 [10];

    float prodPurchPrice [5], prodSellPrice [5];
    float sellerRevenue [10] = {0,0,0,0,0,0,0,0,0,0}, prodRevenue [5], zoneRevenue [5] = {0,0,0,0,0};
    float prodSumRev[5];

    int short sales [30][4]; // 0=idSeller, 1=idProd, 2=cant, 3=idZone
    // Cantidad de ventas limites, pueden hacerse menos de 30, o 30

    short int id;
    short int opc, i, j;

    for(i=0; i<30; i++){
        for(j=0; j<4; j++){
            sales[i][j] = 0;
        }
    }

    /*Mensaje de inicio, solo aparecera una vez*/
    welcome_message();

    /*Recoleccion de datos inicial para productos, vendedores y zonas*/
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

    short int idZ, idS, idP, amo;

    /*Menu repetitivo de inicio*/
    while (repeat) {
        show_main_menu();
        scanf("%hd", &opc);
        switch (opc) {
        case 1: // VENTAS ---------------------------------------------------------
            font_colour(blue);
            printf("\n-- VENTA --\n");
            font_colour(original);
            show_zone_menu(sell, idZone, zoneName);
            scanf("%hd", &idZ);

            if (idZ>=1 && idZ<=5){
                show_seller_menu(sell, idSeller, sellerName);
                scanf("%hd", &idS);

                if (idS>=1 && idS<=10){
                    show_product_menu(sell, idProd, prodName);
                    scanf("%hd", &idP);

                    font_colour(yellow);
                    printf("\nCantidad vendida > ");
                    font_colour(original);
                    scanf("%hd", &amo);

                    if (idP>=1 && idP<=5){
                        zoneAmountSold[idZ-1] += amo;
                        prodAmountSold[idP-1] += amo;
                        sellerAmountSold[idS-1] += amo;

                        prodSumRev[idP-1] += amo*prodRevenue[idP-1];
                        sellerRevenue[idS-1] += amo*prodRevenue[idP-1]; // Mayor IMPORTE de ventas

                        // Total de ventas hechas por cada vendedor en cada zona
                        // Mejor vendedor por zona segun total de ventas
                        // Cant vendedores que no han hecho ventas en x zona
                        amountSoldPerSellerZone1[idS-1] += (idZ==1) ? amo : 0;
                        amountSoldPerSellerZone2[idS-1] += (idZ==2) ? amo : 0;
                        amountSoldPerSellerZone3[idS-1] += (idZ==3) ? amo : 0;
                        amountSoldPerSellerZone4[idS-1] += (idZ==4) ? amo : 0;
                        amountSoldPerSellerZone5[idS-1] += (idZ==5) ? amo : 0;

                        for(i=0; i<30; i++){
                            if(sales[i][0]==0){
                                // Si cualquier posicion del arreglo es 0 entonces dicha posicion esta vacia
                                // Si la posicion [i][x] vacia entonces se insertan datos en dicha posicion
                                i=30;
                                sales[i][0]=idS;
                                sales[i][1]=idP;
                                sales[i][2]=amo;
                                sales[i][3]=idZ;
                            }
                        }

                        font_colour(green);
                        printf("Producto vendido correctamente.");
                        font_colour(original);

                    } else {
                        font_colour(red);
                        printf("\nValor fuera de rango\n");
                        font_colour(original);
                    }
                } else {
                    font_colour(red);
                    printf("\nValor fuera de rango\n");
                    font_colour(original);
                }
            } else {
                font_colour(red);
                printf("\nValor fuera de rango\n");
                font_colour(original);
            }
            break;
        /*
        case 2: // INSERTAR -------------------------------------------------------
            //Menu de insertar, se muestran las 3 opciones
            show_sec_actions_menu(create);
            scanf("%hd", &opc);
            if(opc==1){

                //Insertar > Producto
                for (i = 0; i < 5; i++) {
                    enterProductData(i, prodName, prodType, prodPurchPrice, prodSellPrice, prodRevenue);
                }
                // print_products(idProd, prodName, prodType, prodPurchPrice, prodSellPrice, prodRevenue, prodAmountSold);
            } else if (opc==2){

                //Insertar > Vendedor
                for (i = 0; i < 10; i++) {
                    enterSellerData(i, sellerName);
                }
                // print_sellers(idSeller, sellerName, sellerAmountSold, sellerRevenue);
            } else if (opc==3){

                //Insertar > Zona
                for (i = 0; i < 5; i++) {
                    enterZoneData(i, zoneName);
                }
                // print_zones(idZone, zoneName, zoneAmountSold, zoneRevenue);
            } else if (opc==0){
                repeat=false;
            }
            break;
        */

        case 2: // MOSTRAR--------------------------------------------------------

            /*Menu de mostrar, se muestran las 3 opciones*/
            show_sec_actions_menu(read);
            scanf("%hd", &opc);

            if (opc == 1) {
                /*Se muestran los 5 productos*/
                print_products(idProd, prodName, prodType, prodPurchPrice, prodSellPrice, prodRevenue, prodSumRev, prodAmountSold, false);
            } else if (opc == 2){

                /*Se muestran los 10 vendedores*/
                print_sellers(idSeller, sellerName, sellerAmountSold, sellerRevenue);
            } else if (opc == 3){

                /*Se muestran las 5 zonas*/
                print_zones(idZone, zoneName, zoneAmountSold, zoneRevenue);
            } else if (opc==0){
                repeat=false;
            }
            break;

        case 3: // ACTUAIZAR -----------------------------------------------------

            /*Menu de actualizar, se muestran las 3 opciones*/
            show_sec_actions_menu(update);
            scanf("%hd", &opc);
            if(opc==1){
                show_product_menu(update, idProd, prodName);
                scanf("%hd", &id);

                /*Si el id insertado esta dentro de rango, actualiza, sino muestra un mensaje de error*/
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

                /*Si el id insertado esta dentro de rango, actualiza, sino muestra un mensaje de error*/
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

                /*Si el id insertado esta dentro de rango, actualiza, sino muestra un mensaje de error*/
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

                /*Si el id insertado esta dentro de rango, elimina, sino muestra un mensaje de error*/
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

                /*Si el id insertado esta dentro de rango, elimina, sino muestra un mensaje de error*/
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

            /*La zona no puede eliminarse*/
            break;
        case 5:
            show_statistics_menu();
            scanf("%hd",&opc);
            switch (opc){
            case 1:
                // Importe total de ventas por vendedor en cada zona 
                break;
            case 2:
                // Mejor vendedor de zona por productos vendidos
                break;
            case 3:
                // Mejor vendedor y de que zona es (mayor importe)
                break;
            case 4:
                // Vendedores sin ventas por zona
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