#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define BUF_SIZE 100000

void bubble_sort(int arr[], int count){
	int temp;
	for(int i=0;i<count;i++){
		for(int j=0;j<count-1;j++){
			if(arr[j]>arr[j+1]){
				temp = arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}

int main(int argc, char **argv){
	int num, fd;
	char buf[BUF_SIZE];
	char *temp;
	clock_t start, end;
	int js = 0;
	
	start = clock();
	fd = open(argv[1],O_RDWR);
	if(fd<0){ printf("file open error\n"); exit(1); }
	int n = read(fd, buf, BUF_SIZE);

	temp = strtok(buf, "\0");
	num = atoi(temp);

	srand(2);
	int real[num];
	for(int i=0;i<num;i++){ real[i]=rand()%num+1; printf("%d\n",real[i]); }
	
	bubble_sort(real, BUF_SIZE);

	end=clock();
	printf("running time of this program is %.3f sec \n",(float)(end-start)/CLOCKS_PER_SEC);
	close(fd);
}
