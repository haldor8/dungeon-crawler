opt = -c 
element = entier

dungeon_crawler.exe : creation_salles.o affichage.o main.o tests.o
	gcc -o dungeon_crawler.exe creation_salles.o affichage.o main.o tests.o

tests.o : tests.c tests.h
	gcc ${opt} tests.c 

affichage.o : affichage.c affichage.h
	gcc ${opt} affichage.c

creation_salles.o : creation_salles.c creation_salles.h
	gcc ${opt} creation_salles.c

main.o : main.c
	gcc ${opt} main.c

clean:
	del *.exe
	del *.o

all : clean dungeon_crawler.exe