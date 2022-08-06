#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char board[9] =
{
    ' ', ' ', ' ',
    ' ', ' ', ' ',
    ' ', ' ', ' '
};

typedef enum _pos {
    pos1 = 0, pos2 = 1, pos3 = 2,
    pos4 = 3, pos5 = 4, pos6 = 5,
    pos7 = 6, pos8 = 7, pos9 = 8
} pos;

char board_display[] =
"\
+---+---+---+\n\
|   |   |   |\n\
+---+---+---+\n\
|   |   |   |\n\
+---+---+---+\n\
|   |   |   |\n\
+---+---+---+\
";

void display_board() {
    puts("Current Board");
    board_display[16] = board[pos1];
    board_display[20] = board[pos2];
    board_display[24] = board[pos3];
    board_display[44] = board[pos4];
    board_display[48] = board[pos5];
    board_display[52] = board[pos6];
    board_display[72] = board[pos7];
    board_display[76] = board[pos8];
    board_display[80] = board[pos9];
    puts(board_display);
}

char cur_player = 'X';
void switch_player() {
    if (cur_player == 'X') {
        cur_player = 'O';
    } else {
        cur_player = 'X';
    }
}

pos get_position() {
    static char buffer[3];
    static char *status;
    input:
        printf("%c's move: ", cur_player);
        status = fgets(buffer, 3, stdin);
        if (status == NULL) {
            fputs("An error occured!", stderr);
            exit(EXIT_FAILURE);
        }
        // Nothing is entered
        if (buffer[0] == '\n') {
            puts("Please enter a valid move (1-9)");
            goto input;
        }
        // Input is longer than 1 character
        if (buffer[1] != '\n') {
            puts("Please enter a valid move (1-9)");
            // Drain stdin
            while (getchar() != '\n') {
                continue;
            }
            goto input;
        }
    switch (buffer[0]) {
        case '1':
            return pos1;
        case '2':
            return pos2;
        case '3':
            return pos3;
        case '4':
            return pos4;
        case '5':
            return pos5;
        case '6':
            return pos6;
        case '7':
            return pos7;
        case '8':
            return pos8;
        case '9':
            return pos9;
        default:
            puts("Please enter a valid move (1-9)");
            goto input;
    }
}

bool connect(pos x, pos y, pos z) {
    return board[x] != ' ' && board[x] == board[y] && board[y] == board[z];
}

bool player_win() {
    if (
        connect(pos1, pos2, pos3)
        ||
        connect(pos4, pos5, pos6)
        ||
        connect(pos7, pos8, pos9)
        ||
        connect(pos1, pos4, pos7)
        ||
        connect(pos2, pos5, pos8)
        ||
        connect(pos3, pos6, pos9)
        ||
        connect(pos1, pos5, pos9)
        ||
        connect(pos3, pos5, pos7)
    ) {
        return true;
    } else {
        return false;
    }
}

// Game result
typedef enum _res {
    win, not_over, draw
} res;

res play(pos position) {
    static int remaining_slot = 9;
    if (board[position] != ' ') {
        puts("Slot taken, please enter another move");
        return not_over;
    }
    board[position] = cur_player;
    remaining_slot--;
    display_board();
    if (player_win()) {
        return win;
    } else if (remaining_slot == 0) {
        return draw;
    } else {
        switch_player();
        return not_over;
    }
}

 int main() {
    display_board();
    res result;
    do {
        pos position = get_position();
        result = play(position);
    } while (result == not_over);
    if (result == win) {
        printf("Game ended, %c wins!", cur_player);
    } else {
        fputs("Draw, no one wins...", stdout);
    }
    return EXIT_SUCCESS;
 }