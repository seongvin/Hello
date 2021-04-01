all: solution target pctest

solution: solution.c
	gcc -o solution solution.c
target: target.c
	gcc -o target target.c
pctest: pctest.c
	gcc -o pctest pctest.c
clean:
	rm solution target
