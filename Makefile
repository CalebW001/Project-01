all: generation prolific explorer slug
generation: generation.c
	gcc -o generation generation.c
prolific: prolific.c
	gcc -o prolific prolific.c
explorer: explorer.c 
	gcc -o explorer explorer.c
slug: slug.c
	gcc -o slug slug.c
clean: 
	rm -f prolific generation explorer slug

