#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>    // necesar pentru functia getpwuid
#include <grp.h>    // necesar pentru functia getgrgid
#include <limits.h> // necesar pentru PATH_MAX


void parcurgere_director(char *cale);
/* Declarația funcției recursive pentru parcurgerea în adâncime a subarborelui de fișiere.
   Definiția ei urmează mai jos, după funcția main() care o apelează.
*/

int main(int argc, char *argv[])
{
    struct stat st;

    if(1 == argc)
    {
         fprintf(stderr,"Usage: %s director de procesat!\n",argv[0]);
         exit(1);
    }

    if(0 != stat(argv[1],&st) )
    {
        fprintf(stderr,"Eroare la stat pentru %s .\t", argv[1]);  perror("Cauza este");
        exit(2);
    }

    if( ! S_ISDIR(st.st_mode) )
    {
        fprintf(stderr,"Eroare: %s nu este director!\n",argv[1]);
        exit(3);
    }

    printf("Analizam directorul: %s\n",argv[1]);
    parcurgere_director(argv[1]);

    return 0;
}

int afisare_fileinfo(char* cale);
/* Declarația funcției de afișare a informațiilor, cerute în enunț, despre un fișier (sau director) oarecare.
   Definiția ei urmează mai jos, după funcția parcurgere_director() care o apelează.
*/

void parcurgere_director(char *cale)
/*
  Definiția funcției recursive pentru parcurgerea în adâncime a subarborelui de fișiere.
  Notă: argumentul funcției va fi numele unui fișier de oricare tip posibil (i.e. poate fi ori director, ori de tip fișier normal, ori de celelalte 4 tipuri existente în UNIX/Linux).
*/
{
    DIR *dir;
    struct dirent *de;
    struct stat st;
    char nume[PATH_MAX];
    int isFolder;

    /* Mai întâi afișăm informațiile despre fișierul (de orice tip) primit ca și argument și aflăm dacă e director sau nu */
    isFolder = afisare_fileinfo(cale);

    /* Iar apoi, numai dacă argumentul primit este de tip director, îl parcurgem recursiv pentru a procesa conținutul său */
    if(isFolder != 1)
    {
        return;   /* dacă nu-i director, nu terminăm execuția cu exit(), ci revenim în apelant pentru a continua cu ceea ce a mai rămas de procesat */
    }
    else  /* dacă argumentul primit este director */
    {
        if(NULL == (dir = opendir(cale)) )
        {
            fprintf(stderr,"Eroare deschidere director %s .\t",cale);  perror("Cauza este");
            return;   /* nu terminăm execuția cu exit(), ci revenim în apelant pentru a continua cu ceea ce a mai rămas de procesat */
        }

        /* parcurgerea pe orizontală a primului nivel, i.e. descendenții direcți ai argumentului primit de această funcție */
        while(NULL != (de = readdir(dir)) )
        {
            if( strcmp(de->d_name,".") && strcmp(de->d_name,"..") )  /* ignorăm intrările implicite "." și ".." din orice director */
            {
                sprintf(nume,"%s/%s",cale,de->d_name);  /* construim calea nouă, ca și concatenare de string-uri */
                /* Notă: alternativ, puteam gestiona calea cu apeluri chdir(), similar ideii de la exercițiile de parcurgere recursivă cu scripuri, din lab.5 */
                parcurgere_director(nume);              /* apelul recursiv pentru parcurgerea intrării curente */
            }
        }

        closedir(dir);
    }
}

int afisare_fileinfo(char* cale)
/* Definiția funcției de afișare a informațiilor, cerute în enunț, despre un fișier (sau subdirector) oarecare.
   Valoarea întoarsă este 1 dacă argumentul este un director, respectiv altă valoare în caz contrar.
*/
{
    struct stat st;             /* această structură o vom folosi pentru a afla, cu apelul stat, metadatele asociate unui fișier */
    struct passwd *pwd;         /* această structură o vom folosi pentru a afla username-ul asociat unui UID */
    struct group *grp;          /* această structură o vom folosi pentru a afla groupname-ul asociat unui GID */
    char perm[10]="---------";  /* aici vom construi forma simbolică pentru permisiunile fișierului */
    int result=0;

    if(0 != stat(cale,&st) )
    {
        fprintf(stderr,"Eroare la stat pentru %s .\t", cale);  perror("Cauza este");
        return 2;   /* aici nu terminăm execuția cu exit(), ci revenim în apelant pentru a continua cu ceea ce a mai rămas de procesat */
    }

    printf("Analizam fisierul/directorul: %s\n",cale);
    printf("\tTipul acestui fisier: ");
    switch(st.st_mode & S_IFMT)
    {
        case S_IFDIR : printf("Director\n"); result=1; break;
        case S_IFREG : printf("Fisier obisnuit\n"); break;
        case S_IFLNK : printf("Link\n"); break;
        case S_IFIFO : printf("FIFO\n"); break;
        case S_IFSOCK: printf("Socket\n"); break;
        case S_IFBLK : printf("Block device\n"); break;
        case S_IFCHR : printf("Character device\n"); break;
        default: printf("Unknown file type");
    }

    printf("\tNumarul de nume alternative (i.e., link-uri hard) ale fisierului: %d octeti\n", st.st_nlink );

    printf("\tDimensiunea acestuia: %lld octeti\n", (long long)st.st_size );
    printf("\tSpatiul ocupat de disc pentru stocarea acestuia: %lld sectoare (blocuri de 512 octeti)\n", (long long)st.st_blocks );


    printf("\tPermisiunile acestuia, in notatie octala: %o\n", st.st_mode & 0777 );

    if( S_IRUSR & st.st_mode )  perm[0]='r';
    if( S_IWUSR & st.st_mode )  perm[1]='w';
    if( S_IXUSR & st.st_mode )  perm[2]='x';
    if( S_IRGRP & st.st_mode )  perm[3]='r';
    if( S_IWGRP & st.st_mode )  perm[4]='w';
    if( S_IXGRP & st.st_mode )  perm[5]='x';
    if( S_IROTH & st.st_mode )  perm[6]='r';
    if( S_IWOTH & st.st_mode )  perm[7]='w';
    if( S_IXOTH & st.st_mode )  perm[8]='x';

    printf("\tPermisiunile acestuia, in notatie simbolica: %s\n", perm );

    if(NULL != (pwd = getpwuid(st.st_uid)) )
        printf("\tProprietarul acestuia: %s (cu UID-ul: %ld)\n", pwd->pw_name, (long)st.st_uid );
    else
        printf("\tProprietarul acestuia are UID-ul: %ld\n", (long)st.st_uid );

    if(NULL != (grp = getgrgid(st.st_gid)) )
        printf("\tGrupul proprietar al acestuia: %s (cu GID-ul: %ld)\n", grp->gr_name, (long)st.st_gid );
    else
        printf("\tGrupul proprietar al acestuia are GID-ul: %ld\n", (long)st.st_gid );

    return result;
}
