main: src/main.c src/doubly_linked_list.c
	zig cc -o main src/main.c src/doubly_linked_list.c -I ./src

	# zig cc -o main src/main.c src/doubly_linked_list.c -I ./src
