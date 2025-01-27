all: generation prolific explorer
generation: generation.c
	gcc -o generation generation.c
prolific: prolific.c
	gcc -o prolific prolific.c
explorer: explorer.c 
	gcc -o explorer explorer.c
clean: 
	rm -f prolific generation

