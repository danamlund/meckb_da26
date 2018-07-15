LDFLAGS = -lncurses

tinybasic_test: tinybasic_test.c ../da26/keymaps/default/TinyBASIC.cpp
	gcc -I../da26/keymaps/default/ -g -o tinybasic_test tinybasic_test.c -lncurses

clean:
	rm -f tinybasic_test

