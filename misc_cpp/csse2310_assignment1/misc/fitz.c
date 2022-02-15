#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 80
#define BIG_LINE_SIZE 1000
#define TILE_WIDTH 5
#define MAX_TILE 4
#define TILE_SIZE 25
#define TILE_OFFSET 2
#define INITIAL_TILES_CAPACITY 8
#define MAX_BOARD 999
#define MIN_BOARD 1

#define INVALID_ARGUMENTS_ERROR 1
#define TILE_FILE_ACCESS_ERROR 2
#define INVALID_TILE_FILE_CONTENTS 3
#define INVALID_PLAYER_TYPE 4
#define INVALID_DIMENSIONS 5
#define SAVE_FILE_ACCESS_ERROR 6
#define INVALID_SAVE_FILE_CONTENTS 7
#define END_OF_INPUT_ERROR 10


typedef struct {
    char rot0[TILE_WIDTH][TILE_WIDTH]; 
    char rot90[TILE_WIDTH][TILE_WIDTH];
    char rot180[TILE_WIDTH][TILE_WIDTH];
    char rot270[TILE_WIDTH][TILE_WIDTH];
} Tile;

typedef struct {
    // tiles
    Tile* tiles;
    int numTiles;
    int currTile;
    
    // board
    char* board;
    int width;
    int height;

    // current player '*' is player 1, '#' is player 2
    char player;
    char p1type;
    char p2type;
    
    // current move
    int x;
    int y;
    int rot;
    char* tile;
    
    // last move
    int lastMoveX;
    int lastMoveY;
    int p1LastMoveX;
    int p1LastMoveY;
    int p2LastMoveX;
    int p2LastMoveY;
    
    // line ending of input
    int lineEnding;

} Game;

char* read_line(FILE* file, int* lineEnding);
int error(int err);
int print_tile_rotations(Game* g);
void set_tile(Game* g);
int is_move_valid(Game* g);
void insert_tile(Game* g);
void change_player(Game* g);    
void rotate_tiles(Game* g);
int print_tile(Game* g);
void print_board(Game* g);
int is_any_move_valid(Game* g);
int load_tiles(Game* g, FILE* file);
int parse_dimensions(Game* g, char** argv);
int parse_player_types(Game* g, char** argv);
void init_board(Game* g);
int init_game(Game* g);
int load_game(Game* g, char* filename);
int save_game(char* filename, Game* g);
void set_move(Game* g, int r, int c, int rot);
int get_valid_move1(Game* g);
int get_valid_move21(Game* g);
int get_valid_move22(Game* g);
int get_valid_move2(Game* g);
int is_human(Game* g);
void print_game(Game* g);
int get_input(Game* g);
int get_valid_move_h(Game* g);
char get_player_type(Game* g);
int get_valid_move(Game* g);
int play_game(Game* g);
void special_ending(Game* g);

/* Read a line from a file and return a null byte terminated string.
ending integer gets newline or end of file for future checks */
char* read_line(FILE* file, int* lineEnding) {
    int size = LINE_SIZE;
    char* result = malloc(sizeof(char) * size);
    int position = 0;
    int next = 0;

    while (1) {
        
        if (position == size) {
            size = size * 2;
            // printf("\nREALLOC\n");
            result = realloc(result, sizeof(char) * size);
        }
        
        next = fgetc(file);
        if (next == EOF || next == '\n') {
            result[position] = '\0';
            *lineEnding = next;
            return result;
        } else {
            result[position++] = (char)next;
        }
    }
}

/* print error associated with error number according to 
specifications */
int error(int err) {
    switch (err) {
        case 1:
            fprintf(stderr, "Usage: fitz tilefile "
                    "[p1type p2type [height width | filename]]\n");
            break;
        case 2:
            fprintf(stderr, "Can't access tile file\n");
            break;
        case 3:
            fprintf(stderr, "Invalid tile file contents\n");
            break;
        case 4:
            fprintf(stderr, "Invalid player type\n");
            break;
        case 5:
            fprintf(stderr, "Invalid dimensions\n");
            break;
        case 6:
            fprintf(stderr, "Can't access save file\n");
            break;
        case 7:
            fprintf(stderr, "Invalid save file contents\n");
            break;
        case 10:
            fprintf(stderr, "End of input\n");
            break;
        default:
            fprintf(stderr, "Unknown error\n");
            break;
    }
    return err;
}

/* prints all tile rotations for all tiles loaded into the game */
int print_tile_rotations(Game* g) {

    Tile* tiles = g->tiles;
    int numTiles = g->numTiles;

    for(int k = 0; k < numTiles; ++k) {
        for(int i = 0; i < TILE_WIDTH; ++i) {
            for(int j = 0; j < TILE_WIDTH; ++j) {
                printf("%c", tiles[k].rot0[i][j]);
            }
            printf(" ");
            for(int j = 0; j < TILE_WIDTH; ++j) {
                printf("%c", tiles[k].rot90[i][j]);
            }
            printf(" ");
            for(int j = 0; j < TILE_WIDTH; ++j) {
                printf("%c", tiles[k].rot180[i][j]);
            }
            printf(" ");
            for(int j = 0; j < TILE_WIDTH; ++j) {
                printf("%c", tiles[k].rot270[i][j]);
            }
            printf("\n");
        }
        if (k + 1 != numTiles) {
            printf("\n");
        }
    }
    return 0;
}

/* set active tile according to the current tile and rotation
in game struct */
void set_tile(Game* g) {
    
    switch (g->rot) {
        case 0:
            g->tile = (char*)g->tiles[g->currTile].rot0;
            break;
        case 90:
            g->tile = (char*)g->tiles[g->currTile].rot90;
            break;
        case 180:
            g->tile = (char*)g->tiles[g->currTile].rot180;
            break;
        case 270:
            g->tile = (char*)g->tiles[g->currTile].rot270;
            break;
        default:
            printf("Error selecting tile");
    }    
}

/* return 0 if invalid move (outside board, on top of other move)
or 1 if valid move */
int is_move_valid(Game* g) {
    
    set_tile(g);
    char* tile = g->tile;
    int x = g->x;
    int y = g->y;

    /* printf("%d %d is outside the g->board, invalid move\n", i,j); */
    /* printf("%d %d is on top of another move, invalid move\n", i,j); */
    

    for (int j = 0; j < TILE_WIDTH; ++j) {
        for (int i = 0; i < TILE_WIDTH; ++i) {
            
            // posX, posY is the  position on the board
            int posX = x + i - TILE_OFFSET;
            int posY = y + j - TILE_OFFSET;
            int boardPos = g->width * posY + posX;
            int tilePos = TILE_WIDTH * j + i;
            
            if ((tile[tilePos] == '!') && (posX < 0 || g->width <= posX 
                    || posY < 0 || g->height <= posY)) {
                return 0;
            }
            if ((tile[tilePos] == '!') && g->board[boardPos] != '.') {
                return 0;
            }
            
            
        }
    }
    return 1;
}

/* insert a tile into the board, set last move variables */
void insert_tile(Game* g) {
    char* tile = g->tile;
    int x = g->x;
    int y = g->y;
    
    // insert tile, change player
    for (int j = 0; j < TILE_WIDTH; ++j) {
        for (int i = 0; i < TILE_WIDTH; ++i) {
            int posX = x - TILE_OFFSET + i;
            int posY = y - TILE_OFFSET + j;
            int boardPos = g->width * posY + posX;
            int tilePos = TILE_WIDTH * j + i;
            if (tile[tilePos] == '!') {
                g->board[boardPos] = g->player;
            }
        }
    }
    
    // initialize last moves
    g->lastMoveX = x;
    g->lastMoveY = y;
    if (g->player == '*') {
        g->p1LastMoveX = x;
        g->p1LastMoveY = y;
    } else if (g->player == '#') {
        g->p2LastMoveX = x;
        g->p2LastMoveY = y;        
    }
    
    // invalidate last move data
    g->x = -TILE_WIDTH;
    g->y = -TILE_WIDTH;
}

/* change active player to its character */
void change_player(Game* g) {    
    if (g->player == '*') {
        g->player = '#';
    } else {
        g->player = '*';
    }
    
}

/* increase current tile variable in game struct or 
set it to zero if it's beyond the maximum range of the tiles */
void rotate_tiles(Game* g) {
    g->currTile = g->currTile + 1;
    if (g->currTile == g->numTiles) {
        g->currTile = 0;
    }
}

/* print the current tile with zero rotation */
int print_tile(Game* g) {

    for(int i = 0; i < TILE_WIDTH; ++i) {
        for(int j = 0; j < TILE_WIDTH; ++j) {
            printf("%c", g->tiles[g->currTile].rot0[i][j]);
        }
        printf("\n");
    }
    return 0;
}

/* print all elements of the board in the appropriate dimensions */
void print_board(Game* g) {
    
    for(int y = 0; y < g->height; ++y) {
        for(int x = 0; x < g->width; ++x) {
            printf("%c", g->board[y * g->width + x]);
        }
        printf("\n");
    }
}

/* determine whether there is a valid move that can be played
return 1 if yes and 0 if no */
int is_any_move_valid(Game* g) {
    
    for(int y = -TILE_OFFSET; y < g->height - 1 + TILE_OFFSET; ++y) {
        for(int x = -TILE_OFFSET; x < g->width - 1 + TILE_OFFSET; ++x) {
            for (int rot = 0; rot <= 270; rot = rot + 90) {
                g->x = x;
                g->y = y;
                g->rot = rot;
                set_tile(g);
                if (is_move_valid(g)) {
                    // printf("%d %d %d is valid\n", y, x, rot);
                    return 1;
                }
            }
        }
    }
    return 0;
}

/* load tiles into tiles array in game struct from a file pointer */
int load_tiles(Game* g, FILE* file) {

    Tile* tiles;
    int cap = INITIAL_TILES_CAPACITY;
    int len = 0;
    tiles = malloc(cap * sizeof(Tile));
    char str[LINE_SIZE]; // ccccc\n\0

    while(1) {
        if(len == cap) {
            cap = 2 * cap;
            tiles = realloc(tiles, cap * sizeof(Tile));
        }
        // read 5 lines and add them to the tile struct
        for(int row = 0; row < TILE_WIDTH; ++row) {
            fgets(str, LINE_SIZE, file);
            if (str[strlen(str) - 1] != '\n') {
                return END_OF_INPUT_ERROR;
            }
            /* Checks: if str is wrong size, wrong chars, not newline 
            terminated then return error. */
            if ((strlen(str) != TILE_WIDTH + 1) || str[TILE_WIDTH] != '\n') {
                return INVALID_TILE_FILE_CONTENTS;
            }
            for(int col = 0; col < TILE_WIDTH; ++col) {

                if (!(str[col] == ',' || str[col] == '!')) {
                    return INVALID_TILE_FILE_CONTENTS;
                }
                tiles[len].rot0[row][col] = str[col];
                tiles[len].rot90[col][MAX_TILE - row] = str[col];
                tiles[len].rot180[MAX_TILE - row][MAX_TILE - col] = str[col];
                tiles[len].rot270[MAX_TILE - col][row] = str[col];
            }
        }
        len = len + 1;
        // read newline or EOF
        if (fgets(str, LINE_SIZE, file) == NULL) {
            break;
        }
    }
    // Package into struct
    g->tiles = tiles;
    g->numTiles = len;
    
    return 0;
}

/* initialize board dimensions in game struct from argv */
int parse_dimensions(Game* g, char** argv) {

    long int height = 0;
    long int width = 0;

    char* ptr;
    height = strtol(argv[4], &ptr, 10);
    if (strlen(ptr) != 0) {
        return TILE_WIDTH;
    }
    width = strtol(argv[TILE_WIDTH], &ptr, 10);
    if (strlen(ptr) != 0) {
        return TILE_WIDTH;
    }

    if (width < MIN_BOARD || MAX_BOARD < width || 
            height < MIN_BOARD || MAX_BOARD < height) {
        return TILE_WIDTH;
    }

    g->height = (int)height;
    g->width = (int)width;
    return 0;     
}

/* initialize player types in game struct from argv */
int parse_player_types(Game* g, char** argv) {
    
    if (strlen(argv[2]) != 1 || strlen(argv[3]) != 1) {
        return INVALID_PLAYER_TYPE;
    }
    char p1type = argv[2][0];
    char p2type = argv[3][0];
    if (!(p1type == 'h' || p1type == '1' || p1type == '2') 
            || !(p2type == 'h' || p2type == '1' || p2type == '2')) {
        return INVALID_PLAYER_TYPE;    
    }
    g->p1type = p1type;
    g->p2type = p2type;
    
    if (p1type == '2') {
        g->p1LastMoveX = -TILE_OFFSET;
        g->p1LastMoveY = -TILE_OFFSET;
    } else if (p2type == '2') {
        g->p2LastMoveX = g->width - 1 + TILE_OFFSET;
        g->p2LastMoveY = g->height - 1 + TILE_OFFSET;
    }
    
    return 0;
}

/* set all values of the board to '.' */
void init_board(Game* g) {

    g->board = malloc(g->width * g->height * sizeof(char*));
    for(int y = 0; y < g->height; ++y) {
        for(int x = 0; x < g->width; ++x) {
            g->board[g->width * y + x] = '.';
        }
    }
}

/* initialize and allocate other variables in game struct */
int init_game(Game* g) {
    g->currTile = 0;    
    g->player = '*';
    g->x = -TILE_OFFSET;
    g->y = -TILE_OFFSET;
    g->rot = 0;
    g->tile = malloc(TILE_SIZE * sizeof(char));
    
    return 0;
}

/* load game from filename */
int load_game(Game* g, char* filename) {
    
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return SAVE_FILE_ACCESS_ERROR;
    }

    int playerNumber;
    // readline, do checks !!!
    
    
    int ret = fscanf(file, "%d %d %d %d\n", &(g->currTile), &(playerNumber), 
            &(g->height), &(g->width));
    if (ret != 4) {
        return INVALID_SAVE_FILE_CONTENTS; // invalid save file contents
    }
    
    g->board = malloc(g->width * g->height * sizeof(char*));
    for(int y = 0; y < g->height; ++y) {
        for(int x = 0; x < g->width; ++x) {
            fscanf(file, "%c", &(g->board[y * g->width + x]));
        }
        fscanf(file, "\n");
    }
    
    if (playerNumber == 0) {
        g->player = '*';
    } else {
        g->player = '#';
    }
    
    fclose(file);
    return 0;
}

/* save game to filename */
int save_game(char* filename, Game* g) {
    
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return SAVE_FILE_ACCESS_ERROR;
    }
    int playerNumber;
    if (g->player == '*') {
        playerNumber = 0;
    } else {
        playerNumber = 1;
    }
    fprintf(file, "%d %d %d %d\n", g->currTile, playerNumber, 
            g->height, g->width);
    
    for(int y = 0; y < g->height; ++y) {
        for(int x = 0; x < g->width; ++x) {
            fprintf(file, "%c", g->board[y * g->width + x]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return 0;
}

/* Set the current move, used for automated players */
void set_move(Game* g, int r, int c, int rot) {
    g->y = r;
    g->x = c;
    g->rot = rot;
    set_tile(g);
}

/* Print the current move formatted as a computer move */
void print_automove(Game* g) {
    printf("Player %c => %d %d rotated %d\n", 
            g->player, g->y, g->x, g->rot);
}

/* Find a valid move using automatic player algorithm 1.
Return 1 if a valid move is found and 0 if one is not */
int get_valid_move1(Game* g) {
    
    int rStart = g->lastMoveY;
    int cStart = g->lastMoveX;

    int r = rStart;
    int c = cStart;
    int rot = 0;

    while (1) {
        while (1) {
            set_move(g, r, c, rot);
            if (is_move_valid(g)) {
                print_automove(g);
                g->lastMoveY = g->y;
                g->lastMoveX = g->x;
                return 1;
            }
            ++c;
            if (c > (g->width - 1 + TILE_OFFSET)) { // ??? max column(+2)
                c = -TILE_OFFSET;
                ++r;
            }
            if (r > g->height - 1 + TILE_OFFSET) {
                r = -TILE_OFFSET;
            }
            if (r == rStart && c == cStart) {
                break;
            }
        }
        rot = rot + 90;
        if (rot > 270) {
            break;
        }
    }
    return 0;
}

/* Find a valid move using automatic player algorithm 2 with player 1.
Return 1 if a valid move is found and 0 if one is not */
int get_valid_move21(Game* g) {
    
    int rStart = g->p1LastMoveY;
    int cStart = g->p1LastMoveX;
    int r = rStart;
    int c = cStart;
    int rot = 0;
    
    while (1) {
        rot = 0;
        while (1) {
            set_move(g, r, c, rot);
            if (is_move_valid(g)) {
                print_automove(g);
                g->p1LastMoveY = g->y;
                g->p1LastMoveX = g->x;
                g->lastMoveY = g->y;
                g->lastMoveX = g->x;
                return 1;
            }
            rot = rot + 90;
            if (rot > 270) {
                break;
            }
        }
        ++c;
        if (c > (g->width - 1 + TILE_OFFSET)) { // ??? max column(+2)
            c = -TILE_OFFSET;
            ++r;
        }
        if (r > g->height - 1 + TILE_OFFSET) {
            r = -TILE_OFFSET;
        }
        if (r == rStart && c == cStart) {
            break;
        }
    }
    return 0;
}

/* Find a valid move using automatic player algorithm 2 with player 2.
Return 1 if a valid move is found and 0 if one is not */
int get_valid_move22(Game* g) {
    
    int rStart = g->p2LastMoveY;
    int cStart = g->p2LastMoveX;
    int r = rStart;
    int c = cStart;
    int rot = 0;
    
    while (1) {
        rot = 0;
        while (1) {
            set_move(g, r, c, rot);
            if (is_move_valid(g)) {
                print_automove(g);
                g->p2LastMoveY = g->y;
                g->p2LastMoveX = g->x;
                g->lastMoveY = g->y;
                g->lastMoveX = g->x;
                return 1;
            }
            rot = rot + 90;
            if (rot > 270) {
                break;
            }
        }
        --c;
        if (c < -TILE_OFFSET) {
            c = g->width - 1 + TILE_OFFSET;
            --r;
        }
        if (r < -TILE_OFFSET) {
            r = g->height - 1 + TILE_OFFSET;
        }
        if (r == rStart && c == cStart) {
            break;
        }
    }
    return 0;
}

/* Find a valid move using automatic player algorithm 2 
for either player number.
Return 1 if a valid move is found and 0 if one is not */
int get_valid_move2(Game* g) {
    
    if (g->player == '*') {
        return get_valid_move21(g);
    } else if (g->player == '#') {
        return get_valid_move22(g);
    }
    return 0;
}

/* Return if current player is human */
int is_human(Game* g) {
    if (g->player == '*' && g->p1type == 'h') {
        return 1;
    }
    if (g->player == '#' && g->p2type == 'h') {
        return 1;
    }
    return 0;
}

/* Print the board and optionally the tile */
void print_game(Game* g) {
    
    print_board(g);
    if (is_human(g)) {
        print_tile(g);
    }

}

/* Execute alternate ending for game if a valid move is made 
with an EOF termination */
void special_ending(Game* g) {
    if (is_move_valid(g)) {
        insert_tile(g);
        rotate_tiles(g);
        change_player(g);
        printf("\n");
        print_game(g);
        if (0 == is_any_move_valid(g)) {
            printf("Player %c wins\n", g->player);
        } else {
            if (get_player_type(g) == 'h') {
                printf("Player %c] ", g->player);
            }
        }
        exit(0);
    }
    if (g->lineEnding == EOF && !is_move_valid(g)) {
        fprintf(stderr, "End of input\n");
        exit(END_OF_INPUT_ERROR);
    }
}

/* respond to input from the human player. 
set current move variables if a valid move
save the game if it's a save command */
int get_input(Game* g) {
    int err;
    char* str;
    g->x = -TILE_WIDTH; // invalidate previous move
    g->y = -TILE_WIDTH;    
    while(1) {
        printf("Player %c] ", g->player);
        str = read_line(stdin, &(g->lineEnding));
        if (strlen(str) == 0 && g->lineEnding == EOF) {
            fprintf(stderr, "End of input\n");
            exit(END_OF_INPUT_ERROR);
        }
        if (0 == strncmp(str, "save", 4)) {   
            char filename[LINE_SIZE];
            sscanf(str, "save%s", filename);
            err = save_game(filename, g);
            if (err != 0) {
                return err;
            }
            if (err == 0) {
                printf("Saved the game!\n");
            }
        } else if (strstr(str, "rotated") != 0) {
            
            int ret = sscanf(str, "%d %d rotated %d", &(g->y), 
                    &(g->x), &(g->rot));    
            if ((ret == 3) && (g->rot % 90 == 0) && (0 <= g->rot)
                    && (g->rot <= 270) && is_move_valid(g)) {
                break;
            }
            
        } else {
            int ret = sscanf(str, "%d %d %d", &(g->y), &(g->x), 
                    &(g->rot));
            if ((ret == 3) && (g->rot % 90 == 0) && (0 <= g->rot) 
                    && (g->rot <= 270) && is_move_valid(g)) {
                
                break;
            }
        }
        if (g->lineEnding == EOF) {
            break;
        }
    }
    if (g->lineEnding == EOF) {
        special_ending(g);
    }
    free(str); // !!! other frees needed
    return 0;
}

/* Get valid move from human player
return 0 if none are available and 1 if a valid move is selected */
int get_valid_move_h(Game* g) {
    int err;
    if (0 == is_any_move_valid(g)) {
        return 0;
    }
    err = get_input(g); // from stdin
    if (err != 0) {
        return err;
    }
    set_tile(g); // from rot
    return 1;
}

/* Return current player type */
char get_player_type(Game* g) {
    char playerType;
    if (g->player == '*') {
        playerType = g->p1type;
    } else {
        playerType = g->p2type;
    }
    return playerType;
}

/* Get a valid move from the current player 
and put it in the game struct current position and tile variables.
Return 0 if no move is available and 1 if a move is returned */
int get_valid_move(Game* g) {

    switch (get_player_type(g)) {
        case 'h':
            return get_valid_move_h(g);
        case '1':
            return get_valid_move1(g);
        case '2':
            return get_valid_move2(g);
        default:
            printf("get_valid_move error\n");
            return 0;
    }
}

/* Play game according to settings initialized in game struct.
Return error number or zero if no error.*/
int play_game(Game* g) {
   
    while(1) {
        print_game(g);
        // no moves left
        if (0 == get_valid_move(g)) {
            change_player(g);
            printf("Player %c wins\n", g->player);
            break;
        }
        
        /* printf("is move valid?: %d\n", is_move_valid(g));
         printf("Player %c => %d %d rotated %d\n", 
        g->player, g->y, g->x, g->rot);
        */
        
        insert_tile(g);
        // invalidate working coordinates
        g->x = -TILE_WIDTH;
        g->y = -TILE_WIDTH;
        rotate_tiles(g);
        change_player(g);
    }    
    return 0;
}


/* Main entry point: Parse bash arguments, initialize game, 
play game, return appropriate errors */
int main(int argc, char** argv) {
    
    Game g;
    int err;
    if (argc != 2 && argc != TILE_WIDTH && argc != 6) {
        return error(INVALID_ARGUMENTS_ERROR); // wrong number of arguments
    }
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        return error(TILE_FILE_ACCESS_ERROR); // can't access file
    }
    err = load_tiles(&g, file);
    if (err != 0) {
        return error(err); // invalid file contents
    }
    if (argc == 2) {    
        return print_tile_rotations(&g);
    }
    if (argc == 6) {
        if (0 != parse_dimensions(&g, argv)) {
            return error(INVALID_DIMENSIONS); // invalid dimensions
        }
        if (0 != parse_player_types(&g, argv)) {
            return error(INVALID_PLAYER_TYPE); // invalid player types
        }

        init_board(&g);
    } else if (argc == 5) {
        err = load_game(&g, argv[4]);
        if (err != 0) {
            return error(err);
        }
        if (0 != parse_player_types(&g, argv)) {
            return error(INVALID_PLAYER_TYPE); // invalid player types
        }
    }
    
    init_game(&g);
    err = play_game(&g); // change to play_game2() to test autoplay
    if (err != 0) {
        return error(err);
    }
    
    return 0;
}


