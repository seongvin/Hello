#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define BUF_SIZE 100000

// by using quick sort, but the result is different to solution or rtarget.
void quick_sort(int *data, int start, int end){
	if(start >= end) return;
	
	int pivot = start;
	int i = pivot + 1;
	int j = end;
	int temp;

	while(i <= j){
		while(i <= end && data[i] <= data[pivot]){
			i++;
		}
		while(j > start && data[j] >= data[pivot]){
			j--;
		}

		if(i > j){
			temp = data[j];
			data[j] = data[pivot];
			data[pivot] = temp;
		} else{
			temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
	}

	quick_sort(data, start, j-1);
	quick_sort(data, j+1, end);
}

int main(int argc, char **argv){
	int num;
	int fd;
	char buf[BUF_SIZE];
	char *temp;
	clock_t start, end;
	
	start = clock();
	fd = open(argv[1],O_RDONLY);
	if(fd<0){ printf("file open error\n"); exit(1); }
	int n = read(fd, buf, BUF_SIZE);
	temp = strtok(buf, "\n ");
	int i=0;
	while(temp != NULL){
		num = atoi(temp);
		temp = strtok(NULL, "\n ");
		i++;
	}
	srand(5);
	int real[num];
	for(i=0;i<num;i++) { real[i]=rand()%num+1; printf("%d\n",real[i]); }
	quick_sort(real, 0, 10000);
	end = clock();
	
	printf("running time this program is %.3f sec \n",(float)(end - start)/CLOCKS_PER_SEC);
	close(fd);
}
