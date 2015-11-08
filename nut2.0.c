#include <spawn.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int a,char *b[])
{
	char a*,*d[255];
    int i;
    b[0]="mpiexec";
    execvp("mpiexec",b);
}
