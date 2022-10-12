CC = g++

gamefile = oHNO3.cpp

ifdef OS
   	exe = oHNO3win.exe

   	comp = -Wall -DUSEGLEW -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -mwindows -lfreeglut -lglew32 -lglu32 -lSOIL -lopengl32 -lm -o
else
   	ifeq ($(shell uname), Linux)
      	exe = oHNO3.exe 

	  	comp = -Wall -DUSEGLEW -lglut -lGLU -lGL -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lSOIL -lm -o
   	endif
endif

all: #make
	$(CC) $(gamefile) $(comp) $(exe) 

debug: #for debugging with gdb
	g++ -g oHNO3.cpp -o broken

debugtest: #run gdb
	gdb broken

run: #make run
	./$(exe)

clean: #only cleans in linux
	rm -f oHNO3win.exe oHNO3.exe 
