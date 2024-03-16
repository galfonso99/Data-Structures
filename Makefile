main: src/main.c src/ring_buffer.c
	gcc -o main src/main.c src/ring_buffer.c -I ./src

