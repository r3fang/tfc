all:
		$(CC) -g -O2 src/main.c src/name2fasta.c src/kstring.c -o tfc -lz  -lm