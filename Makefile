LOCAL=$(whereis libGL | awk -F' ' '{print $2}')


all:
	g++ -c ./src/glad.c -I ./headers -o ./obj/glad.o -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
	g++ -c ./src/cg_window.cpp -I ./headers -o ./obj/cg_window.o
	g++ -c ./src/transformations.cpp -I ./headers -o ./obj/transformations.o
	g++ -c ./src/DinamicaCatavento.cpp -I ./headers -o ./obj/DinamicaCatavento.o
	g++ -c ./src/CataventoOpenGl.cpp -I ./headers -o ./obj/CataventoOpenGl.o
	g++ ./src/main.cpp ./obj/*.o -I ./headers $(LOCAL) -lglfw -lGL -lX11 -lpthread -ldl -o ./app/main


run:
	./app/main

clean:
	rm ./obj/*.o
	rm ./app/*