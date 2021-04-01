#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define BUF_SIZE 100000

void quick_sort(int *data, int start, int end){
	if(start >= end) return;

	int pivot = start;
	int i = pivot +1;
	int j =end;
	int temp;

	while(i <= j){
		while(i <= end && data[i] <= data[pivot]){
			i++;
		}
		while(j > start && data[j] >= data[pivot]){
			j--;
		}
		if(i>j){
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

int main(char *textfile){
	int num, fd;
	char buf[BUF_SIZE];
	char *temp;
	clock_t start, end;

	start = clock();
	fd = open(textfile,O_RDONLY);
	if(fd<0) exit(1);
	int n = read(fd, buf, BUF_SIZE);
	temp = strtok(buf, "\0");
	num = atoi(temp);

	srand(2);
	int real[num];
	for(int i=0;i<num;i++){ real[i]=rand()%num+1; printf("%d\n",real[i]); }
	quick_sort(real, 0, 100000);
	end = clock();

	printf("running time of this program is %.3f sec \n",(float)(end - start)/CLOCKS_PER_SEC);	
	close(fd);
}

