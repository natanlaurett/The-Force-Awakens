forceAwakens:	forceAwakens.o
	gcc forceAwakens.o -o forceAwakens

forceAwakens.o: forceAwakens.c
	gcc -c forceAwakens.c

clean:
	rm *.o