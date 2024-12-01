//gcc source.c -lssl -lcrypto -o chall
//solution: dwdwaawddddwdddwddddddwdwawddddddwdwddaaaaa
//flag: zeroday{goblin_also_cant_see_in_the_dark}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <openssl/sha.h>
const int MAX_X = 30;
const int MAX_Y = 10;
//start point
int p_x = 0;
int p_y = 7;
//goblin start point 
int g_x = 11;
int g_y = 7;
int g_dir = 1; // 1: right, -1: left
const int8_t MAP[10][30] = {
/// map[y][x]:
//x axis 0  1  2  3                                                                             //y axis
    {0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //0
    {0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, //1
    {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, //2
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {1, 1, 0, 0, 0, 0, 2, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 1, 9, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 1, 0, 0, 2, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 0},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2} 
};
// 0: empty, 1: brick, 2: lava(deadly), 9: flag
// d: right, a: left, wd: jump right, wa: jump left
// jump right: (y-1,x+1) -> (y-1,x+1) two diagonal moves
// jump left: (y-1,x-1) -> (y-1,x-1)
// shortest path -> moves string -> check if reached flag -> yes-> sha256 -> xor with secret -> flag
//     ~     #  #    ############
//   ~~~~~                #
//   ####    #  #    ####
//            ##
//   ####~         #     ## # #
//       ~                    #
// ##    ~##   ####  #   ######
// P     ~    G       #~~#F
// ## #  ~  ########  #~~#######
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// void print_map() {
//     for (int i = 0; i < 10; i++) {
//         for (int j = 0; j < 30; j++) {
//             if (i == p_y && j == p_x) {
//                 printf("P");
//             } else if (i == g_y && j == g_x) {
//                 printf("G");
//             } else if (MAP[i][j] == 0) {
//                 printf(" ");
//             } else if (MAP[i][j] == 1) {
//                 printf("#");
//             } else if (MAP[i][j] == 2) {
//                 printf("~");
//             } else if (MAP[i][j] == 9) {
//                 printf("F");
//             } 
//         }
//         printf("\n");
//     }
// }
int is_on_map(int next_y,int next_x){
    if(next_x < 0 || next_x >= MAX_X || next_y < 0 || next_y >= MAX_Y){
        return 0;
    }
    return 1;
}
void gravity(){
    while(MAP[p_y+1][p_x] == 0){
        p_y++;
    }
}
void move_right(){
    if(MAP[p_y][p_x+1] != 1 && is_on_map(p_y, p_x+1)){
        p_x++;
    }
}
void move_left(){
    if(MAP[p_y][p_x-1] != 1 && is_on_map(p_y, p_x-1)){
        p_x--;
    }
}
void jump_right(){
    if(MAP[p_y-1][p_x+1] != 1 && is_on_map(p_y-1, p_x+1)){
        p_x++;
        p_y--;
    }
    if(MAP[p_y-1][p_x+1] != 1 && is_on_map(p_y-1, p_x+1)){
        p_x++;
        p_y--;
    }
}
void jump_left(){
    if(MAP[p_y-1][p_x-1] != 1 && is_on_map(p_y-1, p_x-1)){
        p_x--;
        p_y--;
    }
    if(MAP[p_y-1][p_x-1] != 1 && is_on_map(p_y-1, p_x-1)){
        p_x--;
        p_y--;
    }
}
void goblin_move(){ //goblin moves right and left on the platform (it needs to be kinda trapped)
    if(g_x == p_x && g_y == p_y){
        printf("Lost in the dark for eternity...\n");
        exit(0);
    }
    if(MAP[g_y+1][g_x+g_dir] != 1){
        g_dir *= -1;
    }
    if(MAP[g_y][g_x+g_dir] == 0 && is_on_map(g_y, g_x+g_dir)){
        g_x += g_dir;
    }
    if(g_x == p_x && g_y == p_y){
        printf("Lost in the dark for eternity...\n");
        exit(0);
    }
}
void touching_lava(){
    if(MAP[p_y+1][p_x] == 2 || MAP[p_y][p_x] == 2){
        printf("Lost in the dark for eternity...\n");
        exit(0);
    }
}
// void print_hash(unsigned char *hash, size_t length) {
//     for (size_t i = 0; i < length; i++) {
//         printf("%02x", hash[i]);
//     }
//     printf("\n");
// }
void on_flag(char *moves){
    if(MAP[p_y][p_x+1] == 9 || MAP [p_y][p_x-1] == 9 || MAP[p_y+1][p_x] == 9 || MAP[p_y-1][p_x] == 9){
        printf("Thank you for helping poor mage, in return you can see what he found.\n");

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256((unsigned char *)moves, strlen(moves), hash);
        //print_hash(hash, SHA256_DIGEST_LENGTH);

        int s[] = {21, 1, 219, 168, 78, 186, 174, 230, 239, 179, 252, 33, 76, 212, 48, 31, 83, 250, 8, 155, 237, 254, 175, 24, 143, 92, 158, 171, 168, 68, 39, 217};
        //char * flag =  "goblin_also_cant_see_in_the_dark";
        printf("zeroday{");
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            //s[i] = hash[i] ^ flag[i];
            printf("%c", hash[i] ^ s[i]);
        }
        printf("}\n");
        exit(0);
    }
        
}
void decode_moves(char *moves){
    for(int i = 0; moves[i] != '\0'; i++){
        if(moves[i] == 'd'){
            move_right();
        }else if(moves[i] == 'a'){
            move_left();
        }else if(moves[i] == 'w'){
            if(moves[i+1] == 'd'){
                jump_right();
            }else if(moves[i+1] == 'a'){
                jump_left();
            }
            i++;
        }else{
            printf("He cant do it.\n");
            exit(0);
        }
        gravity();
        goblin_move();
        touching_lava();
        on_flag(moves);
    }
}
int main(){
    char moves[43] ={0};
    //print_map();
    printf(" ██▓ ███▄    █    ▄▄▄█████▓ ██░ ██ ▓█████    ▓█████▄  ▄▄▄       ██▀███   ██ ▄█▀\n▓██▒ ██ ▀█   █    ▓  ██▒ ▓▒▓██░ ██▒▓█   ▀    ▒██▀ ██▌▒████▄    ▓██ ▒ ██▒ ██▄█▒ \n▒██▒▓██  ▀█ ██▒   ▒ ▓██░ ▒░▒██▀▀██░▒███      ░██   █▌▒██  ▀█▄  ▓██ ░▄█ ▒▓███▄░ \n░██░▓██▒  ▐▌██▒   ░ ▓██▓ ░ ░▓█ ░██ ▒▓█  ▄    ░▓█▄   ▌░██▄▄▄▄██ ▒██▀▀█▄  ▓██ █▄ \n░██░▒██░   ▓██░     ▒██▒ ░ ░▓█▒░██▓░▒████▒   ░▒████▓  ▓█   ▓██▒░██▓ ▒██▒▒██▒ █▄\n░▓  ░ ▒░   ▒ ▒      ▒ ░░    ▒ ░░▒░▒░░ ▒░ ░    ▒▒▓  ▒  ▒▒   ▓▒█░░ ▒▓ ░▒▓░▒ ▒▒ ▓▒\n ▒ ░░ ░░   ░ ▒░       ░     ▒ ░▒░ ░ ░ ░  ░    ░ ▒  ▒   ▒   ▒▒ ░  ░▒ ░ ▒░░ ░▒ ▒░\n ▒ ░   ░   ░ ░      ░       ░  ░░ ░   ░       ░ ░  ░   ░   ▒     ░░   ░ ░ ░░ ░ \n ░           ░              ░  ░  ░   ░  ░      ░          ░  ░   ░     ░  ░   \n                                              ░                                \n");
    printf("Fellow mage lost in the darkness, he needs your guidance to find the flag as fast as possible and survive... \n");
    scanf("%43s", moves);
    decode_moves(moves);
    //print_map();
    printf("Lost in the dark for eternity...\n");
    exit(0);
}