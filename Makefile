main: main.o Object.o GameCharacter.o Item.o Player.o NPC.o Monster.o Environment.o Room.o Dungeon.o 
	g++ -o main main.o Object.o GameCharacter.o Item.o Player.o NPC.o Monster.o Environment.o Room.o Dungeon.o

main.o: main.cpp Dungeon.h Object.h Item.h Environment.h Room.h Player.h NPC.h Monster.h GameCharacter.h

	g++ -c main.cpp

Dungeon.o: Dungeon.cpp Dungeon.h Object.h Item.h Environment.h Room.h Player.h NPC.h Monster.h GameCharacter.h

	g++ -c Dungeon.cpp

# Record.o: Record.c Record.h

# 	gcc -c Record.c

Monster.o: Monster.cpp Monster.h GameCharacter.h Player.h

	g++ -c Monster.cpp

NPC.o: NPC.cpp NPC.h GameCharacter.h Player.h Item.h

	g++ -c NPC.cpp

Player.o: Player.cpp Player.h GameCharacter.h Room.h Item.h

	g++ -c Player.cpp

GameCharacter.o: GameCharacter.cpp GameCharacter.h Object.h 

	g++ -c GameCharacter.cpp

Room.o: Room.cpp Room.h Object.h Environment.h

	g++ -c Room.cpp

Environment.o: Environment.cpp Environment.h Object.h Player.h NPC.h Item.h

	g++ -c Environment.cpp

Item.o: Item.cpp Item.h Object.h Player.h

	g++ -c Item.cpp

Object.o: Object.cpp Object.h

	g++ -c Object.cpp

.PHONY: clean
clean:

	rm -f main.o Dungeon.o Monster.o NPC.o Player.o GameCharacter.o Room.o Item.o Object.o main