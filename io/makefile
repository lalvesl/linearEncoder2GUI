flagsDev = -g -W -Wall -ansi -pedantic -std=c99
libs = -lpthread
libsLinux = $(libs)
libsWindows = $(libs)
appFolder = build
aplicationName = io
aplication = build/$(aplicationName)
aplicationWindows = $(aplication).exe
mainObj = build/main.o
mainPrg = src/main.c

build:objMain
	gcc -o $(aplication) $(mainObj) -O3 $(libsLinux) 

windows:objMain
	gcc -o $(aplicationWindows) $(mainObj) -O3 $(libsWindows) 

dev:objMain
	gcc $(mainPrg) -c -o $(aplication) $(flagsDev) $(libsLinux)  

devWindows:objMain
	gcc -o $(aplicationWindows) $(mainObj) $(flagsDev) $(libsWindows) 

objMain:buildFolder
	gcc -c $(mainPrg)  -o $(mainObj) -O3

windowsLinux: buildFolder
	i686-w64-mingw32-gcc -c $(mainPrg)  -o $(mainObj) -O3
	i686-w64-mingw32-gcc -o $(aplicationWindows) $(mainObj) -O3 $(libsWindows)

buildFolder:
	@mkdir -p $(appFolder)

run:
	bash -c "if [ -z $$(stat -c "%A" $(aplication) | grep "x$$") ]; then sudo chmod 777 $(aplication);fi"
	mv $(aplication) $(aplicationName)
	sudo ./$(aplicationName)
	

runWindows:
	@false
	@./$(aplicationWindows)

valgrind: build
	valgrind $(aplication)

clear: 
	rm -rf $(appFolder)
	rm -rf *.o

sprites2c: buildFolder
	gcc dev/sprites/sprites2c.c $(flagsDev) -o $(appFolder)/sprites2c 
	rm -f src/sprites.h
	./build/sprites2c > src/sprites.h

devrun:build run
	
maketmpfs:
	mkdir -p "mem"
	sudo mount -t tmpfs -o size=20m tmpfs ./mem
	echo "" > ./mem/io

#forcePriority:
#for i in $(ps -aux  | grep "sudo \./io" | awk '{print $2}');do sudo renice -n -15 -p $i;done && ps -al  | grep "sudo \./io"