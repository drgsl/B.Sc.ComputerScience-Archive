#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
using namespace std;

void scriere_fprintf()
{
    FILE *fptr = fopen("lab9.abc", "w");
    int num;
    printf("Enter num: ");
    scanf("%d",&num);
    if(fptr == NULL) perror("Error on writing! Error message: "), exit(1);

    fprintf(fptr,"%d",num);

    fclose(fptr);
}

void citire_fscanf()
{
    FILE *fptr = fopen("lab9.abc", "r");
    int num;
    fscanf(fptr,"%d", &num);
    if(fptr == NULL) perror("Error on reading! Error message: "), exit(1);

    printf("Value of n=%d", num);

    fclose(fptr);
}

void scriere_fwrite()
{
    FILE *fptr = fopen("lab9.abc", "wb");

    if (fptr == NULL)        perror("Error! opening file"),exit(1);
    for(int n = 1; n < 5; ++n)
    {
        fwrite(&n, sizeof(int), 1, fptr);
    }
    fclose(fptr);
}

void citire_fread()
{
    FILE *fptr = fopen("lab9.abc", "rb");

    if (fptr == NULL)        perror("Error! opening file"),exit(1);
    for(int n = 1; n < 5; ++n)
    {
        int num;
        fread(&num, sizeof(int), 1, fptr);
        printf("%d", num);
    }
    fclose(fptr);
}

void cautare_fseek()
{
    FILE *fptr = fopen("lab9.abc", "rb");

    if (fptr == NULL)        perror("Error! opening file"),exit(1);

    // Moves the cursor to the end of the file
    fseek(fptr, -sizeof(int), SEEK_END);

    for(int n = 1; n < 5; ++n)
    {
        int num;
        fread(&num, sizeof(int), 1, fptr);
        printf("%d", num);
        fseek(fptr, -2*sizeof(int), SEEK_CUR);
    }
    fclose(fptr);
}

/// Probleme Lab9 ///

///9.1
// un fisier ce contine mai multe randuri de text
// afiseaza pe ecran doar randurile de ordin impar.
// Fisierul va fi inchis, la sfarsit
void afiseaza_randuri_impare()
{
    FILE *fptr = fopen("91.abc", "w+");
    for(int i = 0; i<=100; i++)
    {
        fprintf(fptr, "%d \n", i);
    }
    fclose(fptr);

    fptr = fopen("91.abc", "r");
    char inCharArr[10];

    for(int i = 0; i<=100; i++)
    {
        fscanf(fptr,"%s", &inCharArr);
        if(i %2 == 0)
            printf("%s\n", inCharArr);
    }
    fclose(fptr);
}

///9.2
//deschide un fisier ce contine mai multe randuri de text
//salveaza in alt fisier randurile ce contin un numar par de vocale.

void copiaza_randuri_cu_nr_par_vocale()
{
    FILE *fptr = fopen("92.abc", "w");
    for(int i = 0; i<=25; i++)
    {
        for(int j = 'a'; j<='a'+i; j++)
            fprintf(fptr, "%c", (char)j);
        fprintf(fptr, "\n");
    }
    fclose(fptr);

    fptr = fopen("92.abc", "r");
    char inCharArr[100];

    for(int i = 0; i<=25; i++)
    {
        fscanf(fptr,"%s", &inCharArr);

        int voc = 0;
        int cons = 0;

        for(int j = 0; j<strlen(inCharArr); j++)
        {
            if(strchr("aeiou", inCharArr[j])!= NULL)
                voc ++;
            else
                cons ++;
        }
        if(voc == cons)
            printf("%d,%s\n", i, inCharArr);
    }
    fclose(fptr);
}
///9.3
//fisier text cu mai multe propozitii
//scrie in alt fisier propozitiile in ordine inversa.
void copiaza_propozitiile_in_ordine_inversa()
{
    FILE *fptr = fopen("93.abc", "r");
    char inCharArr[100];

    while(!feof(fptr))
    {
        char aux[100];
        fgets(aux, sizeof(aux), fptr);
        strcat(inCharArr, aux);
        printf("%s\n",inCharArr);
    }
    fclose(fptr);
}

///9.4
//Copie octet cu octet
void copiaza_octet_cu_octet()
{

    FILE *fptrR = fopen("92.abc", "r");
    FILE *fptrW = fopen("94.abc", "w");
    while(1)
    {
        char ch=getc(fptrR);
        if(ch==EOF)
            break;
        fprintf(fptrW, "%c ", ch);
    }
    fclose(fptrR);
    fclose(fptrW);
}

///9.5
//un tablou de numere intregi
//dintr-un fisier text separate prin spatii
//salveaza tabloul in fisier binar.
void copie_tablou_in_binar()
{
    FILE *fptrR = fopen("951.abc", "r");
    FILE *fptrW = fopen("952.abc", "wb");
    for(int i = 0; i<2; i++)
    {
        for(int i = 0; i<2; i++)
        {
            unsigned int num;
            fscanf(fptrR,"%d", &num);
            fwrite(&num, sizeof(unsigned int), 1, fptrW);
        }
    }
    fclose(fptrR);
    fclose(fptrW);
}

///9.6
// defineste o structura de tip imagine
//genereaza o imagine, o salveaza
//o restaureaza dintr-un fisier, o afiseaza pe ecran.
//Structura va stoca: latimea si inaltimea imaginii, o matrice de culori (cu valori intre 0 si 16).

#define MAX_BMP_LEN 10
#define MAX_BMP_HEIGHT 10

struct bmp
{
    short file_type;
    short len;
    short height;
    short rezerv_aplicatie;
    short rezerv_aplicatie_extindere;

    short colors[MAX_BMP_LEN][MAX_BMP_HEIGHT];
};
bmp generare_bmp()
{
    bmp img1;

    img1.file_type = 0x4D42;

    img1.len = MAX_BMP_LEN;
    img1.height = MAX_BMP_HEIGHT;

    img1.rezerv_aplicatie = 0;
    img1.rezerv_aplicatie_extindere = 0;

    int prev = 0;
    for(int i = 0; i<img1.len; i++)
    {
        for(int j = 0; j<img1.height; j++)
        {
            img1.colors[i][j] = prev++;
            //prev %=16;
        }
    }
    return img1;
}
void salvare_bmp(bmp img1)
{
    FILE *img = fopen("96.bmp", "wb");

    fwrite(&img1.file_type, sizeof(img1.file_type),1,img);

    fwrite(&img1.len, sizeof(img1.len),1,img);
    fwrite(&img1.height, sizeof(img1.height),1,img);

    fwrite(&img1.rezerv_aplicatie, sizeof(img1.rezerv_aplicatie),1,img);
    fwrite(&img1.rezerv_aplicatie_extindere, sizeof(img1.rezerv_aplicatie_extindere),1,img);

    for(int i = 0; i<img1.len; i++)
    {
        for(int j = 0; j<img1.height; j++)
        {
            fwrite(&img1.colors[i][j], sizeof(img1.colors[i][j]),1,img);
        }
    }
    fclose(img);
}
bmp citire_bmp()
{
    FILE *img = fopen("96.bmp", "rb");

    bmp img2;

    fread(&img2.file_type, sizeof(short), 1, img);

    fread(&img2.len, sizeof(short), 1, img);

    fread(&img2.height, sizeof(short), 1, img);

    fread(&img2.rezerv_aplicatie, sizeof(short), 1, img);

    fread(&img2.rezerv_aplicatie_extindere, sizeof(short), 1, img);

    for(int i = 0; i < img2.len; i++)
        for(int j = 0; j < img2.height; j++)
            fread(&img2.colors[i][j], sizeof(short), 1, img);

    fclose(img);

    return img2;
}
void afisare_bmp(bmp img2)
{
    printf("image file type: %02X \n", img2.file_type);
    printf("image length: %02X \n", img2.len);
    printf("image height: %02X \n", img2.height);
    printf("image reserved: %02X \n", img2.rezerv_aplicatie);
    printf("image extended reserved: %02X \n", img2.rezerv_aplicatie_extindere);
    printf("\n");
    printf("image matrix: \n");

    for(int i = 0; i < img2.len; i++)
    {
        for(int j = 0; j < img2.height; j++)
        {
            printf("%02X ", img2.colors[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    //scriere_fprintf();
    //citire_fscanf();

    //scriere_fwrite();
    //citire_fread();
    //cautare_fseek();

    //afiseaza_randuri_impare();
    //copiaza_randuri_cu_nr_par_vocale();
    //copiaza_propozitiile_in_ordine_inversa();
    //copiaza_octet_cu_octet();
    //copie_tablou_in_binar();

    bmp img1 = generare_bmp();
    salvare_bmp(img1);

    bmp img2 = citire_bmp();
    afisare_bmp(img2);
    return 0;
}
