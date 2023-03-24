#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define BLOCK_SIZE 4096  /* !!! exact dimensiunea paginii de memorie, din motive de eficiență a operațiilor cu discul !!! */


int copie_opts_i_u(char *nume_sursa, char *nume_dest, int flag_opt_i, int flag_opt_u);
// Declarația funcției de copiere cu opțiuni. Definiția ei urmează mai jos, după funcția main() care o apelează.


int main(int argc, char *argv[])
{
    int i, flag_opt_i=0, flag_opt_u=0;
    char *nume_sursa=NULL;
    char *nume_dest =NULL;

    if (argc < 3)
    {
        fprintf(stderr,"Usage: %s [-i] [-u] fisier-sursa fisier-destinatie\n",argv[0]);
        exit(1);
    }

    /* Prelucrăm argumentele din linia de comandă pentru a identifica prezența opțiunilor -i și/sau -u,
       precum și a numelor fișierelor sursă și destinație.
       Observație: vom permite ca opțiunile -i și -u să apară în orice poziție în linia de comandă.
    */
    for(i = 1; i < argc; i++)
    {
        if( strcmp(argv[i],"-i") == 0 )   {  flag_opt_i = 1;  continue;  }
        if( strcmp(argv[i],"-u") == 0 )   {  flag_opt_u = 1;  continue;  }

        if( nume_sursa == NULL )  {  nume_sursa = argv[i];  continue;  }
        if( nume_dest  == NULL )  {  nume_dest  = argv[i];  continue;  }

        fprintf(stderr, "Eroare: nu ati respectat formatul impus pentru argumentele din linia de comanda.\n");
        exit(2);
    }

    if( nume_sursa == NULL )  { fprintf(stderr, "Eroare: nu ati specificat fisierul sursa.\n"); exit(3); }

    if( nume_dest  == NULL )  { fprintf(stderr, "Eroare: nu ati specificat fisierul destinatie.\n"); exit(4); }


    /* Acum urmează apelul unei funcții care implementează funcționalitatea efectivă de copiere cerută în enunț */

    return copie_opts_i_u(nume_sursa, nume_dest, flag_opt_i, flag_opt_u);
}


int copie_simpla(char *nume_sursa, char *nume_dest);
// Declarația funcției de copiere propriu-zisă. Definiția ei urmează mai jos, după funcția copie_opts_i_u() care o apelează.


int copie_opts_i_u(char *nume_sursa, char *nume_dest, int flag_opt_i, int flag_opt_u)
{
    if( access(nume_sursa,R_OK) != 0 )
    {
        fprintf(stderr,"Eroare: fisierul sursa %s nu este accesibil (i.e. nu exista, sau nu am drept de citire, sau ce?)\t",nume_sursa);
        perror("Cauza exacta este");
        return 10;
    }

    int flag_dest_exista = access(nume_dest,F_OK)==0 ? 1 : 0 ;  // operatorul condițional din C

    int flag_abort_copiere = 0;

    if( flag_dest_exista )
    {
        /* Trebuie să verificăm vechimea destinației ? (opțiunea -u) */

        if(flag_opt_u)
        {
            struct stat st_sursa, st_dest;

            if(0 != stat(nume_sursa,&st_sursa) )
            {
                fprintf(stderr,"Eroare la stat pentru fisierul sursa %s .\t", nume_sursa);  perror("Cauza este");  return 11;
            }
            if(0 != stat(nume_dest,&st_dest) )
            {
                fprintf(stderr,"Eroare la stat pentru fisierul destinatie %s .\t", nume_dest);  perror("Cauza este");  return 12;
            }

            if(st_sursa.st_mtime > st_dest.st_mtime)
            {
                printf("\tSursa %s are 'last modified time': %s", nume_sursa, ctime(&st_sursa.st_mtime) );
                printf("\tDestinatia %s are 'last modified time': %s", nume_dest, ctime(&st_dest.st_mtime));
                printf("Notify message: copierea se va face cu suprascrierea destinatiei (deoarece sursa este mai recenta decat destinatia).\n");
            }
            else
            {
                flag_abort_copiere = 1;
                printf("Sursa %s nu este mai recenta decat destinatia %s. Deci NU suprascriu destinatia cu sursa!\n", nume_sursa, nume_dest);
            }
        }

        /* Mai trebuie să interogăm utilizatorul ? (optiunea -i) */
		
        if( !flag_abort_copiere && flag_opt_i)
        {  
            char raspuns;

            printf("Fisierul destinatie %s exista deja (dar este mai vechi decat sursa). Vreti sa-l suprascrieti? (D/N)\n",nume_dest);
            do{
                scanf("%c",&raspuns);
            }while( (raspuns != 'D') && (raspuns != 'N') );

            if(raspuns == 'N')
                flag_abort_copiere = 1;
            else
                printf("Notify message: copierea se va face cu suprascrierea destinatiei (cu acceptul utilizatorului).\n");
        }
        else
        {
            /* Vom da prioritate opțiunii -u : dacă destinația este mai recentă decât sursa, nu mai întrebăm utilizatorul, ci anulăm copierea. */
        }
    }

    if(! flag_abort_copiere)
    {
        return copie_simpla(nume_sursa, nume_dest);
    }
    else
    {
        fprintf(stderr, "Copierea lui %s in %s nu s-a mai efectuat.\n", nume_sursa, nume_dest);
        return 13;
    }
}


int copie_simpla(char *nume_sursa, char *nume_dest)
{
    int input_fd, output_fd;
    ssize_t bytes_in, bytes_out;
    char buffer[BLOCK_SIZE];

    if( -1 == (input_fd = open(nume_sursa, O_RDONLY)) )
    {
        fprintf(stderr,"Eroare la deschiderea fisierului sursa %s\n",nume_sursa);
        perror("Cauza este");  return 20;
    }

    if( -1 == (output_fd = open(nume_dest, O_WRONLY|O_CREAT|O_TRUNC, 0600)) )
    {
        fprintf(stderr,"Eroare la deschiderea fisierului destinatie %s\n",nume_dest);
        perror("Cauza este");  return 21;
    }

    /* Process the input file a record at atime. */

    while (1)
    {
        if( -1 == (bytes_in = read(input_fd, buffer, BLOCK_SIZE)) )
        {
            fprintf(stderr,"Eroare la citirea din fisierul %s\n",nume_sursa);
            perror("Cauza este");  return 22;
        }
        if(bytes_in == 0) break; // am ajuns la EOF in fisierul de intrare
		
        if( -1 == (bytes_out = write(output_fd, buffer, bytes_in)) )
        {
            fprintf(stderr,"Eroare la scrierea in fisierul %s\n",nume_dest);
            perror("Cauza este");  return 23;
        }			
        if (bytes_out != bytes_in)
        {
            fprintf(stderr, "Fatal write error: scriere incompleta!");  return 24;
        }
    }

    close(input_fd);
	close(output_fd);

    printf("Am copiat cu succes fisierul sursa %s in destinatia %s\n", nume_sursa, nume_dest);
    return 0;
}
