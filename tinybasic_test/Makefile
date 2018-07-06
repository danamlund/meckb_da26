LDFLAGS = -lncurses

tinybasic_test: tinybasic_test.c ../da26/keymaps/default/tinybasic03.c
	gcc -I../da26/keymaps/default/ -g -o tinybasic_test tinybasic_test.c -lncurses

clean:
	rm -f tinybasic_test

