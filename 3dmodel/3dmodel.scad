hole=14;
socket=19;
rim=(socket - hole) / 2;
holeHeight=1;
socketHeight=10;

row2x = socket * 0.25;
row3x = socket * 0.75;
    

module key(x, y) {
    translate([x, y, 0]) {
        translate ([0, 0, socketHeight - holeHeight]) {
            difference() {
                cube ([socket, socket, holeHeight]);
                translate ([rim, rim, 0]) {
                    cube ([hole, hole, holeHeight]);
                }
            }
        }
    }
}

module legs(startx, y, endx, width, length) {
    for (x = [startx : 2*(hole + rim*width) : endx] ) {
        translate ([x, y, 0]) {
            cube ([rim * width, rim * length, socketHeight - holeHeight]);
        }
    }
}

union() {
    for (i = [0 : 9]) {
        key(i * socket, 0);
    }
    for (i = [0 : 8]) {
        key(row2x + i * socket, -socket);
    }
    for (i = [0 : 6]) {
        key(row3x + i * socket, -socket*2);
    }
}

union() {
    legs(hole+rim, -rim, 9*socket, 2, 2);
    legs(hole+rim + row2x, -rim - socket, 8*socket, 2, 2);
}

edge=1;
union() {
    translate ([0, socket - edge, 0]) {
        cube ([10*socket, edge, socketHeight - holeHeight]);
    }
    translate ([0, 0, 0]) {
        cube ([row2x, edge, socketHeight - holeHeight]);
    }
    translate ([row2x + (9 * socket), 0, 0]) {
        cube ([socket - row2x, edge, socketHeight - holeHeight]);
    }
    translate ([row2x, -socket, 0]) {
        cube ([row3x - row2x, edge, socketHeight - holeHeight]);
    }
    translate ([row3x + 7*socket, -socket, 0]) {
        cube ([row3x - row2x + socket, edge, socketHeight - holeHeight]);
    }
    translate ([row3x, -2*socket, 0]) {
        cube ([7*socket, edge, socketHeight - holeHeight]);
    }

    translate ([0, edge, 0]) {
        cube ([edge, socket - 2 * edge, socketHeight - holeHeight]);
    }
    translate ([socket*10 - edge, edge, 0]) {
        cube ([edge, socket - 2 * edge, socketHeight - holeHeight]);
    }

    translate ([row2x, - socket + edge, 0]) {
        cube ([edge, socket, socketHeight - holeHeight]);
    }
    translate ([row2x + 9*socket - edge, - socket, 0]) {
        cube ([edge, socket + edge, socketHeight - holeHeight]);
    }

    translate ([row3x, - 2*socket + edge, 0]) {
        cube ([edge, socket, socketHeight - holeHeight]);
    }
    translate ([row3x + 7*socket - edge, - 2*socket + edge, 0]) {
        cube ([edge, socket, socketHeight - holeHeight]);
    }
}
