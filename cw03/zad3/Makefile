CC=gcc

test: tree_rec.c
	$(CC) tree_rec.c -o tree_rec
	./tree_rec test_dir/ aaabbbccc
	./tree_rec ../ aaabbbccc
	./tree_rec /root aaabbbccc
	./tree_rec Makefile aaabbbccc 
	
clean:
	rm -f tree_rec

