#include <limits.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void addCity(char[], double);
void addItem(char[], double);
void printSummary();
void top3City();
void bottom3City();
void top3Item();
void bottom3Item();
void writereport (char[], char[]);

struct City {
    char name[50];
    double sales;
};

struct Item {
    char itemName[50];
    double sales;
};

// Declare Global Variables
struct City cities[105]; // create struct array
struct Item items[105]; // create struct array

/* for counting cities */
double numCity = 0;
double total = 0;

double h1, h2, h3; // sales of top 3 cities
char *top1, *top2, *top3; // Name of top 3 cities
double l1, l2, l3; // sales of bottom 3 cities
char *bot1, *bot2, *bot3; // Name of bottom 3 cities

/* for counting item categories */
double numItem = 0;
double totalItemSales = 0;

double t1, t2, t3; // sales of top 3 item cat
char *high1, *high2, *high3; // Name of top 3 item cat
double b1, b2, b3; // sales of bottom 3 item cat
char *low1, *low2, *low3; // Name of bottom 3 item cat



int main(int argc, char * argv[]) {
    
    // Declare other variables
    const int SIZE = 255;
    char line[SIZE];
    char tempLine[SIZE];
    char *token;
    char *city;
    char *item;
    double sales;
    int size;
    FILE *fp; 
    
    /* check for argument passed */
    if (argc != 2) {
        printf("No file name passed in!\n");
        printf("Usage : %s <input file>\n", argv[0]);
        exit(0);
    }
    
    /* get filename from prompt */
    fp = fopen(argv[1], "r");

    if (fp == NULL) { // if no file exit program
        printf("File not found!\n");
        exit(0);
    }
    
    /* Check file size */
    fseek (fp, 0, SEEK_END); // pointer go through file 
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET); // reset pointer to beginning
    
    if (size == 0) { // If file empty exit program
        printf("File is empty!\n");
        exit(0);
    }

    /* if file conditions meet then run */
    
    // Declare time variable
    time_t startTime; 
	startTime=time(NULL);
    printf("%s",asctime(localtime(&startTime))); // Print program start time

    
    while(fgets(line, SIZE, fp) != NULL) {

        /* create tempLine to store the whole line */
        strcpy(tempLine, line);
        
        /* get tokens from each line of file */
        token = strtok(line, "\t"); //date
        token = strtok(NULL, "\t"); //time
        city = strtok(NULL, "\t"); //city
        item = strtok(NULL, "\t"); //item
        token = strtok(NULL, "\t"); //sales
        sales = atof(token); // Convert string to float

        /* adding city method */
        addCity(city, sales);
        total += sales;

        /* adding item method */
        addItem(item, sales);
        totalItemSales += sales;

        /* writereport method */
        writereport(city, tempLine);

    }   


    // List sales of top 3 and bottom 3 cities
    top3City();
    bottom3City();

    // List sales of top 3 and bottom 3 item categories
    top3Item();
    bottom3Item();

    // Print program summary
    printSummary();

    // Declare time variable
    time_t endTime; 
	endTime=time(NULL);
    printf("%s",asctime(localtime(&endTime))); // Print program start time

    fclose(fp); // Closes file
}

void writereport (char name[], char line[]) {
    FILE *output; // File pointer
    char fileName[255]; // For directory name

    /* output transactions to file */
    // Creates path "reports/cityName"
    strcpy(fileName, "reports/");
    strcat(fileName, name);

    output = fopen(fileName, "a");
    fprintf(output, "%s", line); // create file/append if exist
    fclose(output); // closes file

}

void addCity(char name[], double sales) {
    int i;
    for(i=0; i < numCity; i++) {
        
        if (strcmp(name, cities[i].name) == 0) {// string compare, returns 0 if same
            cities[i].sales += sales;
            return;

        }
    }
    
    strcpy(cities[i].name, name);
    cities[i].sales = sales;
    numCity++; //current number of cities in array
    
}

void addItem(char name[], double sales) {
    int i;
    for(i=0; i < numItem; i++) {
    
        if (strcmp(name, items[i].itemName) == 0) { // string compare, returns 0 if same
            items[i].sales += sales;
            return;

        }
    }

    strcpy(items[i].itemName, name);
    items[i].sales = sales;
    numItem++; //current number of items in array

}

void printSummary() {

    // Print main output of summary
    printf("Total Sales of the year is $%.2lf\n\n", total);
    printf("The Average Sales From\t%0.lf Cities:\n", numCity);
    printf("%46.2lf\n\n", total/numCity);
    printf("Top Three Cities\n");
    printf("==============================================\n");
    printf("%-23s%23.2lf\n", top1, h1);
    printf("%-23s%23.2lf\n", top2, h2);
    printf("%-23s%23.2lf\n", top3, h3);
    printf("==============================================\n\n");
    printf("Bottom Three Cities\n");
    printf("==============================================\n");
    printf("%-23s%23.2lf\n", bot3, l3);
    printf("%-23s%23.2lf\n", bot2, l2);
    printf("%-23s%23.2lf\n", bot1, l1);
    printf("==============================================\n\n");
    printf("The Average Sales From\t%0.lf Item Categories:\n", numItem);
    printf("%46.2lf\n\n", totalItemSales/numItem);
    printf("Top Three Item Categories\n");
    printf("==============================================\n");
    printf("%-23s%23.2lf\n", high1, t1);
    printf("%-23s%23.2lf\n", high2, t2);
    printf("%-23s%23.2lf\n", high3, t3);
    printf("==============================================\n\n");
    printf("Bottom Three Item Categories\n");
    printf("==============================================\n");
    printf("%-23s%23.2lf\n", low3, b3);
    printf("%-23s%23.2lf\n", low2, b2);
    printf("%-23s%23.2lf\n", low1, b1);
    printf("==============================================\n\n");
}

void top3City() {

    // Find first largest element 
    h1 = cities[0].sales;
    for (int i = 1; i < numCity ; i++){ 

        /* Check if current element is more than h1,
           then update h1 to be the current element
           if true */
        if (cities[i].sales > h1) {
            h1 = cities[i].sales; 
            top1 = cities[i].name;
        } 
    }
    // Find second largest element 
    h2 = INT_MIN;
    for (int i = 0; i < numCity ; i++) {

        /* Check if current element is more than h2
           and less than h1, then update h2 to be 
           the current element if true */
        if (cities[i].sales > h2 && cities[i].sales < h1) {
            h2 = cities[i].sales; 
            top2 = cities[i].name;
        }
    }

    // Find third largest element 
    h3 = INT_MIN;
    for (int i = 0; i < numCity ; i++) {

        /* Check if current element is more than h3
           and less than h2, then update h3 to be 
           the current element if true */
        if (cities[i].sales > h3 && cities[i].sales < h2) {
            h3 = cities[i].sales; 
            top3 = cities[i].name;
        }
    }

}

void bottom3City() {

    // Find first smallest element 
    l1 = cities[0].sales;
    for (int i = 1; i < numCity ; i++){ 

        /* Check if current element is less than l1,
           then update l1 to be the current element
           if true */
        if (cities[i].sales < l1) {
            l1 = cities[i].sales; 
            bot1 = cities[i].name;
        }
    }
    // Find second smallest element 
    l2 = INT_MAX;
    for (int i = 0; i < numCity ; i++) {

        /* Check if current element is less than l2
           and more than l1, then update l2 to be 
           the current element if true */
        if (cities[i].sales < l2 && cities[i].sales > l1) {
            l2 = cities[i].sales; 
            bot2 = cities[i].name;
        }
    }

    // Find third smallest element 
    l3 = INT_MAX;
    for (int i = 0; i < numCity ; i++) {

        /* Check if current element is less than l3
           and more than l2, then update l3 to be 
           the current element if true */
        if (cities[i].sales < l3 && cities[i].sales > l2) {
            l3 = cities[i].sales; 
            bot3 = cities[i].name;
        }
    }

}

void top3Item() {

    // Find first largest element 
    t1 = items[0].sales;
    for (int i = 1; i < numItem ; i++){ 

        /* Check if current element is more than t1,
           then update t1 to be the current element
           if true */
        if (items[i].sales > t1) {
            t1 = items[i].sales; 
            high1 = items[i].itemName;
        }
    }
    // Find second largest element 
    t2 = INT_MIN;
    for (int i = 0; i < numItem ; i++) {

        /* Check if current element is more than t2
           and less than t1, then update t2 to be 
           the current element if true */
        if (items[i].sales > t2 && items[i].sales < t1) {
            t2 = items[i].sales; 
            high2 = items[i].itemName;
        }
    }

    // Find third largest element 
    t3 = INT_MIN;
    for (int i = 0; i < numItem ; i++) {

        /* Check if current element is more than t3
           and less than t2, then update t3 to be 
           the current element if true */
        if (items[i].sales > t3 && items[i].sales < t2) {
            t3 = items[i].sales; 
            high3 = items[i].itemName;
        }
    }

}

void bottom3Item() {

    // Find first smallest element 
    b1 = items[0].sales;
    for (int i = 1; i < numItem ; i++){ 

        /* Check if current element is less than b1,
           then update b1 to be the current element
           if true */
        if (items[i].sales < b1) {
            b1 = items[i].sales; 
            low1 = items[i].itemName;

        }

    }
    // Find second smallest element 
    b2 = INT_MAX;
    for (int i = 0; i < numItem ; i++) {

        /* Check if current element is less than b2
           and more than b1, then update b2 to be 
           the current element if true */
        if (items[i].sales < b2 && items[i].sales > b1) {
            b2 = items[i].sales; 
            low2 = items[i].itemName;

        }

    }

    // Find third smallest element 
    b3 = INT_MAX;
    for (int i = 0; i < numItem ; i++) {

        /* Check if current element is less than b3
           and more than b2, then update b3 to be 
           the current element if true */
        if (items[i].sales < b3 && items[i].sales > b2) {
            b3 = items[i].sales; 
            low3 = items[i].itemName;
        }
    }

}