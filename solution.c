#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define BUF_SIZE 100000
#define LEFT_CHILD(x) (2*x + 1)
#define RIGHT_CHILD(x) (2*x + 2)
#define PARENT(x) ((x-1)/2)
#define SWAP(a,b) {int t; t=a; a=b; b=t;}

int findmaxindex(int *base, int n, int now);
void initheap(int *base, int n){
	int pa = 0;
	int now;
	int im;
	for(im=1;im<n;im++){
		now = im;
		while(now>0){
			pa=PARENT(now);
			if(base[now]>base[pa]){
				SWAP(base[now],base[pa]);
				now = pa;
			} else{
				break;
			}
		}
	}
}

void makeheap(int *base, int n){
	int now =0;
	int mp =0;
	while(LEFT_CHILD(now) < n){
		int mp = findmaxindex(base, n, now);
		if (mp == now){
			break;
		}
		if(base[mp] > base[now]){
			SWAP(base[mp], base[now]);
		}
		now = mp;
	}
}

int findmaxindex(int *base, int n, int now){
	int lc = LEFT_CHILD(now);
	int rc = RIGHT_CHILD(now);
	if(rc >= n){
		if(base[now]<base[lc]){
			return lc;
		}
		return now;
	}
	if(base[lc]<base[rc]) return rc;
	return lc;
}
void heapsort(int *base, int n){
	int on = n;
	initheap(base, n);
	n--;
	SWAP(base[0], base[n]);
	while(n>1){
		makeheap(base, n);
		n--;
		SWAP(base[0], base[n]);
	}
}

int main(int argc, char **argv){
	int num;
	char buf[BUF_SIZE];
	char *temp;
	clock_t start, end;

	start = clock();
	int fd = open(argv[1],O_RDONLY);
	if(fd<0){ printf("file open error\n"); exit(1); }
	int n = read(fd, buf, BUF_SIZE);
	temp = strtok(buf, "\0");
	num = atoi(temp);
	srand(2);
	int real[num];
	for(int i=0;i<num;i++){ real[i]=rand()%num+1; printf("%d\n",real[i]);  }
	heapsort(real, num);
	for(int i=0;i<num;i++){ printf("%d\n",real[i]); }
	end = clock();
	
	printf("running time of this program is %.3f sec \n",(float)(end-start)/CLOCKS_PER_SEC);
	close(fd);
	return 0;
}

