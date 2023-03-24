/*
* Program: get_limits_ex.c
*
* Funcționalitate: ilustrează câteva dintre informațiile și limitele ce le putem obține cu apelurile sysconf() și getrlimit().
*/
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/resource.h>


#define handle_error(msg) \
    { perror(msg); exit(EXIT_FAILURE); }


int main(void)
{
/*
   Informații despre limitele de mai jos puteți afla din următoarele pagini de documentație:
   man 3 sysconf
   man 2 getrlimit
*/

    struct rlimit my_limits;

    //       struct rlimit {
    //           rlim_t rlim_cur;  /* Soft limit */
    //           rlim_t rlim_max;  /* Hard limit (ceiling for rlim_cur) */
    //       };
    // Notes: The glibc getrlimit() and setrlimit() wrapper functions use a 64-bit rlim_t data type, even on 32-bit platforms. 


/* Limite referitoare la utilizatori și grupuri */

    long UsernameMax = sysconf(_SC_LOGIN_NAME_MAX);
    if (UsernameMax == -1)
        handle_error("Error at sysconf");
    printf("\nThe maximum length of a login name, including the terminating null byte, is: %ld caracters.\n", UsernameMax);
    printf("   Note: the POSIX standard defines the minimum value for this limit as: %d.\n", _POSIX_LOGIN_NAME_MAX);

    long NGroupsMax = sysconf(_SC_NGROUPS_MAX);
    if (NGroupsMax == -1)
        handle_error("Error at sysconf");
    printf("\nThe maximum number of supplementary group IDs is: %ld groups.\n", NGroupsMax);


/* Limite referitoare la configurația hardware a sistemului dvs. */

    long NProcConf = sysconf(_SC_NPROCESSORS_CONF); //These values also exist, but may not be standard.
    if (NProcConf == -1)
        handle_error("Error at sysconf");
    long NProcAvail = sysconf(_SC_NPROCESSORS_ONLN); //These values also exist, but may not be standard.
    if (NProcAvail == -1)
        handle_error("Error at sysconf");
    printf("\nThe number of processors configured / currently online (available) are: %ld, respectively %ld,  processors.\n", NProcConf, NProcAvail);
    // See also get_nprocs_conf(3).



/* Limite referitoare la administrarea memoriei */

    long PhysPages = sysconf(_SC_PHYS_PAGES); //These values also exist, but may not be standard.
    if (PhysPages == -1)
        handle_error("Error at sysconf");
    printf("\nThe number of pages of physical memory is: %ld pages.\n", PhysPages);

    long AvailPhysPages = sysconf(_SC_AVPHYS_PAGES); //These values also exist, but may not be standard.
    if (AvailPhysPages == -1)
        handle_error("Error at sysconf");
    printf("The number of currently available pages of physical memory is: %ld pages.\n", AvailPhysPages);


    /* Determinăm dimensiunea paginilor corespunzătoare arhitecturii hardware a calculatorului dvs. */
    long PageSize = sysconf(_SC_PAGE_SIZE);
    if (PageSize == -1)
        handle_error("Error at sysconf");
    printf("\nThe page size on your hardware system is: %ld bytes.\n", PageSize);

    if(-1 == getrlimit(RLIMIT_AS, &my_limits) )
        handle_error("Error at getrlimit");
    printf("\nThe soft/hard limits for RLIMIT_AS (i.e., the maximum size of the process's virtual memory (address space)), "\
           "configured for your system, are: %ld, respectively %ld, bytes.\n", my_limits.rlim_cur, my_limits.rlim_max);
    /* Dacă valorile returnate sunt -1 (aka RLIM_INFINITY), înseamnă de fapt că această resursă este nelimitată.
       Pentru a impune o limită asupra acestei resurse, folosiți apelul setrlimit() pentru resursa RLIMIT_AS.  */

    if(-1 == getrlimit(RLIMIT_DATA, &my_limits) )
        handle_error("Error at getrlimit");
    printf("\nThe soft/hard limits for RLIMIT_DATA (i.e., the maximum size of the process's data segment (initialized data, uninitialized data, and heap)), "\
           "configured for your system, are: %ld, respectively %ld, bytes.\n", my_limits.rlim_cur, my_limits.rlim_max);
    /* Dacă valorile returnate sunt -1 (aka RLIM_INFINITY), înseamnă de fapt că această resursă este nelimitată.
       Pentru a impune o limită asupra acestei resurse, folosiți apelul setrlimit() pentru resursa RLIMIT_DATA.  */

    if(-1 == getrlimit(RLIMIT_STACK, &my_limits) )
        handle_error("Error at getrlimit");
    printf("\nThe soft/hard limits for RLIMIT_STACK (i.e., the maximum size of the process stack, in bytes), "\
           "configured for your system, are: %ld, respectively %ld, bytes.\n", my_limits.rlim_cur, my_limits.rlim_max);
    /* Dacă valorile returnate sunt -1 (aka RLIM_INFINITY), înseamnă de fapt că această resursă este nelimitată.
       Pentru a impune o limită asupra acestei resurse, folosiți apelul setrlimit() pentru resursa RLIMIT_STACK.  */

    if(-1 == getrlimit(RLIMIT_MEMLOCK, &my_limits) )
        handle_error("Error at getrlimit");
    printf("\nThe soft/hard limits for RLIMIT_MEMLOCK (i.e., the maximum number of bytes of memory that may be locked into RAM), "\
           "configured for your system, are: %ld, respectively %ld, bytes.\n", my_limits.rlim_cur, my_limits.rlim_max);



/* Limite referitoare la gestiunea execuției programelor */

    /* Determinăm numărul maxim de procese active permis per utilizator. */
    long ChildMax = sysconf(_SC_CHILD_MAX);
    // The maximum number of simultaneous processes per user ID.  Must not be less than _POSIX_CHILD_MAX (25).
    if (ChildMax == -1)
        handle_error("Error at sysconf");
    printf("\nThe maximum number of simultaneous processes per user ID, configured for your system, is: %ld processes/user.\n", ChildMax);
    printf("   Note: the POSIX standard defines the minimum value for this limit as: %d.\n", _POSIX_CHILD_MAX);
    /*
       Avertizare: aveți grijă când scrieți programe recursive ce folosesc apelul fork(), să nu faceți greșeli de genul 'recursie infinită'...
       Pentru a micșora impactul unei astfel de greșeli, vă puteți micșora limita _SC_CHILD_MAX folosind apelul setrlimit() pentru resursa RLIMIT_NPROC.
    */

    if(-1 == getrlimit(RLIMIT_NPROC, &my_limits) )
        handle_error("Error at getrlimit");
    printf("\nThe soft/hard limits for RLIMIT_NPROC (i.e., maximum number of simultaneous processes per user ID), "\
           "configured for your system, are: %ld, respectively %ld, processes/user.\n", my_limits.rlim_cur, my_limits.rlim_max);

    /* Determinăm timpul maxim de execuție pe CPU a unui proces (poate fi și nelimitat). */
    if(-1 == getrlimit(RLIMIT_CPU, &my_limits) )
        handle_error("Error at getrlimit");
    printf("\nThe soft/hard limits for RLIMIT_CPU (i.e., the limit, in seconds, on the amount of CPU time that the process can consume), "\
           "configured for your system, are: %ld, respectively %ld, seconds.\n", my_limits.rlim_cur, my_limits.rlim_max);
    /* Dacă valorile returnate sunt -1 (aka RLIM_INFINITY), înseamnă de fapt că această resursă este nelimitată.
       Pentru a impune o limită asupra acestei resurse, folosiți apelul setrlimit() pentru resursa RLIMIT_CPU.  */



/* Limite referitoare la gestiunea fișierelor create/accesate de programe */

    long OpenFilesMax = sysconf(_SC_OPEN_MAX);
    // The maximum number of files that a process can have open at any time.  Must not be less than _POSIX_OPEN_MAX (20).
    if (OpenFilesMax == -1)
        handle_error("Error at sysconf");
    printf("\nThe maximum number of simultaneous open files per process, configured for your system, is: %ld open files/process.\n", OpenFilesMax);
    printf("   Note: the POSIX standard defines the minimum value for this limit as: %d.\n", _POSIX_OPEN_MAX);

    if(-1 == getrlimit(RLIMIT_NOFILE, &my_limits) )
        handle_error("Error at getrlimit");
    printf("\nThe soft/hard limits for RLIMIT_NOFILE (i.e., this specifies a value one greater than the maximum file descriptor number that can be opened by this process), "\
           "configured for your system, are: %ld, respectively %ld.\n", my_limits.rlim_cur, my_limits.rlim_max);

    if(-1 == getrlimit(RLIMIT_FSIZE, &my_limits) )
        handle_error("Error at getrlimit");
    printf("\nThe soft/hard limits for RLIMIT_FSIZE (i.e., the maximum size in bytes for any file that the process may create), "\
           "configured for your system, are: %ld, respectively %ld, seconds.\n", my_limits.rlim_cur, my_limits.rlim_max);
    /* Dacă valorile returnate sunt -1 (aka RLIM_INFINITY), înseamnă de fapt că această resursă este nelimitată.
       Pentru a impune o limită asupra acestei resurse, folosiți apelul setrlimit() pentru resursa RLIMIT_FSIZE.  */

    if(-1 == getrlimit(RLIMIT_LOCKS, &my_limits) )
        handle_error("Error at getrlimit");
    printf("\nThe soft/hard limits for RLIMIT_LOCKS (i.e., the limit on the combined number of flock(2) locks and fcntl(2) leases that this "\
           "process may establish), are: %ld, respectively %ld, seconds.\n", my_limits.rlim_cur, my_limits.rlim_max);
    /* Dacă valorile returnate sunt -1 (aka RLIM_INFINITY), înseamnă de fapt că această resursă este nelimitată.
       Pentru a impune o limită asupra acestei resurse, folosiți apelul setrlimit() pentru resursa RLIMIT_LOCKS.  */



/* Alte tipuri de limite impuse asupra unor resurse... */

    long clock_ticks = sysconf(_SC_CLK_TCK);
    //  The number of clock ticks per second.  The corresponding variable is obsolete.  It was of course called CLK_TCK.
    //  (Note: the macro CLOCKS_PER_SEC does not give information: it must equal 1000000.)
    /*
       Citiți paragraful "The software clock, HZ, and jiffies" din pagina de manual:  man 7 time
       unde se specifică semnificația constantei USER_HZ (folosită în kernel), a cărei valoare este returnată de acest apel.
    */  
    if (clock_ticks == -1)
        handle_error("Error at sysconf");
    printf("\nNotification: The number of clock ticks per second (aka kernel constant USER_HZ), configured for your system's kernel, "\
           "is: %ld clock ticks/second.\n", clock_ticks);


    return 0;
}
