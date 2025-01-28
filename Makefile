all: generation prolific explorer slug slugrace
generation: generation.c
	gcc -o generation generation.c
prolific: prolific.c
	gcc -o prolific prolific.c
explorer: explorer.c 
	gcc -o explorer explorer.c
slug: slug.c
	gcc -o slug slug.c
slugrace: slugrace.c
	gcc -o slugrace slugrace.c -lrt
clean: 
	rm -f prolific generation explorer slug slugrace

