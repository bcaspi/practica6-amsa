#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double write(const char *filename);
double read(const char *filename);

int main() {
    
    double time_spent_write_ram = write("example2.txt");
    double time_spent_write_sf = write("/tmp/ramdisk/example.txt");
    double time_spent_read_ram = read("example2.txt");
    double time_spent_read_sf = read("/tmp/ramdisk/example.txt");

    printf("%-35s\t %-30lf\n", "Temps escriptura fitxer RAM:", time_spent_write_ram);
    printf("%-35s\t %-30lf\n\n", "Temps escriptura fitxer del sf:", time_spent_write_sf);
    printf("%-35s\t %-30lf\n", "Temps lectura fitxer RAM:", time_spent_read_ram);
    printf("%-35s\t %-30lf\n", "Temps lectura fitxer fitxer del sf:", time_spent_read_sf);

    return 0;
}

double write(const char *filename)        
{
    clock_t begin = clock();
    int i;

    FILE *fptr;
    if ((fptr = fopen(filename, "w+")) == NULL) {
        printf("Error while opening the file!\n");
        exit(1);
    }
    for (i = 1; i<100000000; i++){ fprintf(fptr,"%d", i); }
    fprintf(fptr,"\n");
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
