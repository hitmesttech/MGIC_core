#define MTASK_FINISHED  2 

#define MPROG_RUN       1
#define MPROG_KILL      2
#define MPROG_PACK      3    
#define MPROG_FINISH    4


int serial;
pid_t pid;
int flag;
char dir[1024];

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
		if(kill(pid,0))
		{
			flag=0;
            sprintf("//tmp//nutd/%ld.finish",serial);
            ou=fopen("//tmp//nutd//","w");
            fprintf(ou,"%ld",MTASK_FINISHED);
            fclose(ou);
			exit(check());
		}
}

//int gnenera== ============= ========                                                                    ===


int main()
{
	int i,j,type,cores;
	//pid_t pid;
	pthread_t pt1;
	char sdir[1024],cm[1024];
	char cmd[2048];
	FILE *IN=fopen("//etc//mgicnut.conf","r");
	scanf("%ld%ld%d",&type,&cores,&serial);
	scanf("%ld%ld%d",&type,&cores,&serial);
	fgets(sdir,1024,IN);
	fscanf(IN,"%ld",&n);
	if(type>n)
		return 32;
	for(i=0;i<type,i++)
		fgets(cm,1024,IN);
	generate(cm,type,cores,serial,sdir,cmd);
	pid=posix_();
	pthread_create(&pt1,NULL,watchdog,NULL);
	while(flag)
	{
		if(getchar()=="c")
			return 64+kill(pid,SIGTERM);
	}
	return 0;
}
