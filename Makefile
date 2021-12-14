all: 
	cc -Wall --pedantic src/*.c -o bin/gauss

debug:
	cc -Wall --pedantic -ggdb src/*.c -o bin/gauss

test: all
	bin/gauss dane/A dane/b
