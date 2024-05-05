main: src/main.c src/generic_map.c src/map.c
	zig cc -o main src/main.c src/generic_map.c src/map.c -I ./src


#src/hash_map.c
