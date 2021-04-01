#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUF_SIZE 100000

void compile(char *after, char *before){
	execl("/usr/bin/gcc", "gcc", "-o", after, before, (char *)0x0);
}

int main(int argc, char **argv) {
	/*
		0. fork() -> wait()
		1. Compile the files including solution and target by using gcc.
		2. By using fork() and wait() function, solution and target file execute.
		fork() -> wait()
		
	*/
	
	int pipes_t[2];
	int pipes_s[2];
	int dir = 0;
	int out = 0;
	int temp = 12;

	for(int i=1;i < argc;i+=2){
		if(argv[i][0] == '-'){
			switch(argv[i][1]){
				case 'i':
					dir = i+1;
					break;
				case 't':
					out = i+1;
					break;
			}
		}
	}

	temp -= dir + out;
	int sol = out+1;
	printf("%d\t %d\t %d\n", dir, out, temp);
	printf("%s\t %s\t %s\n", argv[dir], argv[sol], argv[temp]);
	
	pid_t child_target_pid;
	pid_t child_solution_pid;

	int exit_code;
	child_target_pid = fork();
	/* compile child of target file */
	if(child_target_pid == 0){
		compile("target", argv[temp]);
	}
	else if(child_target_pid < 0) printf("Wrong!\n");
	else{ 
		wait(0);
	}

	child_solution_pid = fork();
	/* compile child of solution file */
	if(child_solution_pid == 0){
		compile("solution", argv[sol]);
	}
	else if(child_solution_pid < 0) printf("Wrong!\n");
	else { 
		wait(0);
	}
	
	// create pipe for target
	if(pipe(pipes_t) != 0){
		perror("Error");
		exit(1);
	}
	// create pipe for solution
	if(pipe(pipes_s) != 0){
		perror("Error");
		exit(1);
	}

	/* execute child of solution and target files */	
	child_target_pid = fork();
	if(child_target_pid == 0){
		dup2(pipes_t[1], 1);
		printf("%s", argv[dir]);
		execl("./target ","target", argv[dir], (char *)0x0);	
	}
	else wait(0);

	child_solution_pid = fork();
	if(child_solution_pid == 0){
		dup2(pipes_s[1], 1);
		printf("%s", argv[dir]);
		execl("./solution ","solution", argv[dir], (char *)0x0);
	}
	else wait(0);

	close(pipes_t[1]); close(pipes_s[1]);
	
	char buf_t[32];
	char buf_s[32];
	ssize_t st, ss;
	
	while(((st = read(pipes_t[0], buf_t, 31)) > 0 ) && ((ss = read(pipes_s[0], buf_s, 31)) > 0)){
		buf_t[st+1] = 0x0;
		buf_s[ss+1] = 0x0;
		
		printf("%s\n",buf_t);
	}
	close(pipes_t[0]); close(pipes_s[0]);

	
	return 0;
}
