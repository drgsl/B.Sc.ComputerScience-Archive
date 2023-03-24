 #include <stdlib.h>
  #include <stdio.h>
    #include <errno.h>
    #include <string.h>
    #include <fcntl.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <sys/socket.h>

    int vlogin(char cmd[])
    {
        if(cmd[0]=='l' && cmd[1]=='o' && cmd[2]=='g' && cmd[3]=='i' && cmd[4]=='n' && cmd[5]==' ' && cmd[6]==':' && cmd[7]==' ')
            return 1;
        return 0;
    }
    int vpid(char cmd[])
    {
        if(cmd[0]=='g' && cmd[1]=='e' && cmd[2]=='t' && cmd[3]=='-' && cmd[4]=='p')
            if(cmd[5]=='r' && cmd[6]=='o' && cmd[7]=='c' && cmd[8]=='-' && cmd[9]=='i' && cmd[10]=='n')
                if(cmd[11]=='f' && cmd[12]=='o' && cmd[13]==' ' && cmd[14]==':' && cmd[15]==' ')
                    return 1;
        return 0;
    }

    int main(){

        char cmd[50],s[256],raspuns[256],x[256];
        int fd1,fd2,i,nr=0,logat=0,m=0;

        //citesc in array numele utilizatorilor
        FILE* log=fopen("log","r");
        if (log==NULL) perror("Eroare la open");
        while(fgets(s,sizeof(s),log))
        {
            nr++;
            if(strlen(s)>m) m=strlen(s);
        } 
        char arr[nr][m];
        rewind(log);
        for(i=0;i<nr;i++)
        {
            fgets(s, sizeof(s),log);           
            strcpy(arr[i],s);
            arr[i][strlen(s)-1]='\0';
        }

        //leg client-server
        mknod("fifo1", S_IFIFO | 0666, 0);        
        fd1 = open("fifo1", O_RDONLY);
        fd2=open("fifo2", O_WRONLY);

        do{
            raspuns[0]='\0';
            if ((m = read(fd1, cmd, 50)) == -1)
                perror("Eroare la citirea din FIFO1!");
            else if(strcmp(cmd,"quit")==0) exit(1);
            else
            {
                cmd[m] = '\0'; 
                
                int socketp[2],verif,pid,p[2],pp[2],len=0,j,sp[2];
                char ok[2],da[256];
                socketpair(AF_UNIX, SOCK_STREAM, 0, socketp);
                if(pipe(p)==-1) perror("Eroare la pipe1");
                if(pipe(pp)==-1) perror("Eroare la pipe2");
                socketpair(AF_UNIX, SOCK_STREAM, 0, sp);
                
                pid=fork();
                if(pid)
                {
                    if(vlogin(cmd))
                    {
                        close(p[1]);
                        read(p[0],ok,1);
                        if(ok[0]=='1') strcpy(raspuns, "Bine ati venit");
                        else if(ok[0]=='0') strcpy(raspuns, "Utilizator inexistent");
                        else strcpy(raspuns, "Deja e un utilizator logat");
                    }
                    else
                    if(strcmp(cmd,"logout")==0) 
                    {
                        close(pp[1]);
                        read(pp[0],ok,1);
                        if(ok[0]=='1') strcpy(raspuns, "V-ati deconectat cu succes");
                        else strcpy(raspuns, "Nu exista utilizator logat");

                    }
                    else
                    if(vpid(cmd))
                    {
                        close(socketp[0]);
                        read(socketp[1],x,256);
                        strcpy(raspuns,x);
                    }
                    else
                    if(strcmp(cmd,"get-logged-users")==0)
                    {
                        close(sp[0]);
                        read(sp[1],x,256);
                        strcpy(raspuns,x);
                    }
                    else strcpy(raspuns,"Comanda incorecta");
                }
                else if(!pid)
                {
                    if(vlogin(cmd))
                    {
                        close(p[0]);
                        
                        int len=0;verif=0; 
                        if(logat==1) verif=2;
                        else
                        {
                            for(i=8;i<strlen(cmd);i++)
                            {
                                s[i-8]=cmd[i];
                                len++;
                            }
                            s[len]='\0';    
                        //printf("%s\n",s);
                            
                            for(i=0;i<nr;i++)
                                if(strcmp(arr[i],s)==0) 
                                    verif=1; 
                        }           
                        
                        if(verif==1) 
                        {   
                            logat=1;
                            //printf("%d\n",logat);
                            write(p[1],"1",sizeof(char));
                        }
                        else 
                        {
                            if(verif==2) write(p[1],"2",sizeof(char));
                            else write(p[1],"0",sizeof(char));
                        }
                        
                    }
                    else
                    if(strcmp(cmd,"logout")==0)
                    {
                        close(pp[0]);
                        if(logat==1) write(pp[1],"1",sizeof(char));
                        else  write(pp[1],"0",sizeof(char));
                        logat=0;
                        //printf("%d\n",logat);
                    }
                    else
                    if(vpid(cmd))
                    {
                        close(socketp[1]);
                        if(logat==0) write(socketp[0],"Nu sunteti logat",50);
                        else
                        {
                            da[0]='\0';
                            for(i=16;i<strlen(cmd);i++)
                            {
                                x[i-16]=cmd[i];
                                len++;
                            }
                            x[len]='\0';  
                        
                       strcpy(s,"/proc/");
                       strcat(s,x);
                       strcat(s,"/status");
                       //printf("%s\n",s);
                        
                        if(access(s, F_OK)!=0) write(socketp[0],"Nu exista pid-ul",50);
                        FILE* pid=fopen(s,"r");
                        if (pid==NULL) write(socketp[0],"Eroare la deschidere fisier",50);
                        
                        
                        char pidd[5][50]; i=0,j=0;
                        while(fgets(x,sizeof(x),pid) && i<18)
                        {
                            
                            if(i==0 || i==2 || i==6 || i==8 || i==17)
                                strcpy(pidd[j++],x);
                            i++;
                            
                                
                        }
                       
                        for(i=0;i<5;i++) 
                            {
                                strcat(da,pidd[i]);
                                
                            }
                        
                        //printf("%s\n",da);
                        }
                        write(socketp[0],da,strlen(da)+1);
                    }
                    else
                    if(strcmp(cmd,"get-logged-users")==0)
                    {
                        close(sp[1]);
                        da[0]='\0';
                        if(logat==0) strcpy(da,"Nu sunteti logat");
                        else strcpy(da, "Informatii despre urilizatori");
                        da[strlen(da)]=NULL;
                        if(write(sp[0],da,strlen(da))==-1) perror("Eroare la scrierea in socket2");
                    }
                }
            if ((write(fd2, raspuns, strlen(raspuns))) == -1)
                    perror("Problema la scriere in FIFO2!");
            }
        } while(m>0);
    }
