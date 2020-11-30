#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double write(const char *filename);
double read(const char *filename);

int main() {
    
    double time_spent_write_ram = write("example.txt");
    double time_spent_write_sf = write("/dev/sda1/example.txt");
    double time_spent_read_ram = read("example.txt");
    double time_spent_read_sf = read("/dev/sda1/example.txt");

    printf("%-35s\t %-30lf\n", "Temps escriptura fitxer RAM:", time_spent_write_ram);
    printf("%-35s\t %-30lf\n\n", "Temps escriptura fitxer del sf:", time_spent_write_sf);
    printf("%-35s\t %-30lf\n", "Temps lectura fitxer RAM:", time_spent_read_ram);
    printf("%-35s\t %-30lf\n", "Temps lectura fitxer fitxer del sf:", time_spent_read_sf);

    return 0;
}

double write(const char *filename)        
{
    clock_t begin = clock();

    FILE *fptr;
    if ((fptr = fopen(filename, "w+")) == NULL) {
        printf("Error while opening the file!");
        exit(1);
    }
    for (int i = 1; i<100; i++){ fprintf(fptr,"%d\n", i); }
    fclose(fptr);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    return time_spent;             
}

double read(const char *filename)        
{
    clock_t begin = clock();
    
    char ch;
    FILE *fptr;
    if ((fptr = fopen(filename, "r")) == NULL) {
        printf("Error while opening the file!");
        exit(1);
    }
    while((ch = fgetc(fptr)) != EOF) 
    fclose(fptr);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    return time_spent;             
}
