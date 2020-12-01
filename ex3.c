#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

double write_t(const char *filename);
double read_t(const char *filename);

int main() {
   
    double time_spent_write_ram = write_t("example2.txt");
    printf("Done Writing...\n");
    double time_spent_write_sf = write_t("/tmp/ramdisk/example.txt");
    printf("Done Writing...\n");
    double time_spent_read_ram = read_t("example2.txt");
    double time_spent_read_sf = read_t("/tmp/ramdisk/example.txt");

    printf("%-35s\t %-30lf\n", "Temps escriptura fitxer RAM:", time_spent_write_ram);
    printf("%-35s\t %-30lf\n\n", "Temps escriptura fitxer del sf:", time_spent_write_sf);
    printf("%-35s\t %-30lf\n", "Temps lectura fitxer RAM:", time_spent_read_ram);
    printf("%-35s\t %-30lf\n", "Temps lectura fitxer fitxer del sf:", time_spent_read_sf);

    return 0;
}

double write_t(const char *filename)        
{
    clock_t begin = clock();
    int i;

    FILE *fptr;
    if ((fptr = fopen(filename, "w+")) == NULL) {
        printf("Error while opening the file!\n");
        exit(1);
    }
    int fd = fileno(fptr);
    for (i = 1; i<10000000; i++){ write(fd, "a", 1); }
    write(fd,"\n", 1);
    fclose(fptr);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    return time_spent;            
}

double read_t(const char *filename)        
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