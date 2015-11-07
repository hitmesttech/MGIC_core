#include <spawn.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;
#define MTASK_FINISHED  2 

#define MPROG_RUN       1
#define MPROG_KILL      2
#define MPROG_PACK      3    
#define MPROG_FINISH    4


int serial;
pid_t pid;
int flag;
int totaltype=10;
char dir[1024];
extern char **environ;

int check()
{
	return 0;
}

int watchdog()
{
    FILE *ou;
    char finish_file_dir[2048];
	while(1)
	{
        sleep(1000);
		if(kill(pid,0))
		{
			flag=0;
            sprintf("/tmp/nutd/%ld.finish",serial);
            ou=fopen("/tmp/nutd/","w");
            fprintf(ou,"%ld",MTASK_FINISHED);
            fclose(ou);
			exit(check());
		}
}

//int gnenera== ============= ========                                                                    ===
int generate(char *cmd,char *argv[],int type,int cores,int serial,char *sdir)
{
    char cst_dir[2048],*t,f_dir[2048],tmp_str[2048],name[2048];
    FILE *tfp;
    sprintf(cst_dir,"/home/MPIC/storge/%ld/",serial);
    strcpy(f_dir,cst_dir);
    sprintf(tmp_dir,"ls /home/MPIC/storge/%ld/*.in",serial);
    tfp=popen(tmp_dir,"r");
    fgets(name,2048,tfp);
    strcat(f_dir,name);
    strcpy(cmd,"/usr/bin/mpiexec");
#define givestr(d,A) t=malloc(A);strcpy(strlen(A)+1);d=t;
    givstr(argv[0],"mpiexec");
    givestr(argv[1],"-n");
    sprintf(tmp_str,"%ld",cores);
    givestr(argv[2],tmp_str);
    givestr(argv[3],"/usr/bin/pw.x");
    strcpy(tmp_str+1,f_dir,name);
    tmp_str[0]='<';
    tmp_str[strlen(tmp_str)]='>';
    givestr(argv[4],tmp_str);
    sprintf(tmp_dir,"/home/MPIC/storge/result/%d.out",serial);
    givestr(argv[5],tmp_dir);
#undef givestr
}


int main()
{
	int i,j,type,cores;
	//pid_t pid;
	char sdir[1024],cmd[1024],tmp_str[2048];
	char *cargs[20];
    FILE *in;
    pthread_t pt1;
    posix_spawnattr_t attr;
    posix_spawn_file_actions_t fact;
	//FILE *IN=fopen("/etc/mgicnut.conf","r");
	scanf("%ld%ld%d",&type,&cores,&serial);
	//scanf("%ld%ld%d",&type,&cores,&serial);
	//fgets(sdir,1024,IN);
	//scanf(IN,"%ld",&n);
    sprintf(tmp_str,"7z x /home/MPIC/storge/%ld.7z",serial);
    in=popen(tmp_str,"r");
    while(!feof(tn))
    {
        fgetc(in);
    }
    pclose(in);
	if(type>totaltype)
		return 32;
	for(i=0;i<type,i++)
		fgets(cm,1024,IN);
	generate(cmd,cargs,type,cores,serial,sdir);
	pid=posix_spawn(&pid,cmd,&fact,&attr,cargs,environ);
	pthread_create(&pt1,NULL,watchdog,NULL);
	while(flag)
	{
		if(getchar()=="c")
			return 64+kill(pid,SIGTERM);
	}
	return 0;
}
