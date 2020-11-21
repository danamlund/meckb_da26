sudoku_ncurses: sudoku_ncurses.c ../da26/keymaps/default/sudoku.c
	gcc -I../da26/keymaps/default -g -o sudoku_ncurses sudoku_ncurses.c -lncurses

clean:
	rm -f sudoku_ncurses log.txt sudoku_seeds

sudoku_seeds: sudoku_seeds.c
	gcc -O2 -o sudoku_seeds sudoku_seeds.c

seeds: sudoku_seeds
	./sudoku_seeds
