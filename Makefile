libdht.so: dht.o
	gcc -shared -o libdht.so dht.o -lwiringPi -Wall
dht.o: dht.c
	gcc -c -Wall -fpic dht.c
clean:
	rm -f *.o && rm -f *.so && rm -f test
test:
	gcc -o test test.c -Wall -L. -ldht -std=c99 
