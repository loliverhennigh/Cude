

cude: cude.o 
	g++ -o cude cude.o -lGL -lglut

cude.o: cude.cpp
	g++ -c cude.cpp

clean:
	rm -f *.o cude
