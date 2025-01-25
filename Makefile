all: generation prolific
generation: generation.c
	gcc -o generation generation.c
prolific: prolific.c
	gcc -o prolific prolific.c
clean: 
	rm -f prolific generation

