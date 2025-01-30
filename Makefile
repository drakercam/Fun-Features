opts = -lsfml-graphics -lsfml-window -lsfml-system
dependencies = main.o game.o game_object.o player_game_object.o enemy_game_object.o  timer.o menu.o

game: ${dependencies}
	g++ -o game ${dependencies} ${opts}

main.o: main.cpp
	g++ -c main.cpp ${opts}

game_object.o: game_object.cpp game_object.h
	g++ -c game_object.cpp ${opts}

player_game_object.o: player_game_object.cpp player_game_object.h
	g++ -c player_game_object.cpp ${opts}

enemy_game_object.o: enemy_game_object.cpp enemy_game_object.h
	g++ -c enemy_game_object.cpp ${opts}

timer.o: timer.cpp timer.h
	g++ -c timer.cpp ${opts}

menu.o: menu.cpp menu.h
	g++ -c menu.cpp ${opts}

run:
	./game

clean:
	rm -f ${dependencies} game