

cude: cude.o 
	g++ -o cude cude.o -lglut

cude.o: cude.cpp
	g++ -c cude.cpp

clean:
	rm -f *.o cude
