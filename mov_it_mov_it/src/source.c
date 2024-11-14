#include <stdio.h>
int main() {
    //----gen_flag_code.py
    int x1[56] = {226, 106, 179, 10, 180, 10, 91, 142, 210, 63, 12, 50, 243, 22, 168, 5, 84, 143, 132, 218, 192, 174, 205, 190, 12, 203, 69, 142, 87, 118, 122, 104, 6, 142, 21, 179, 185, 22, 246, 41, 71, 103, 124, 197, 13, 183, 35, 11, 97, 228, 184, 252, 50, 243, 148, 192};
    int x2[56] = {152, 15, 193, 101, 208, 107, 34, 245, 190, 15, 60, 89, 154, 120, 207, 90, 96, 251, 219, 183, 240, 216, 164, 208, 107, 148, 38, 230, 99, 4, 9, 55, 107, 186, 126, 128, 202, 73, 132, 25, 36, 12, 15, 154, 107, 219, 74, 108, 9, 144, 231, 200, 69, 146, 237, 189};
    int l = 56, i = 0, f = 0;
    char flag[56];
    //----
    puts("┳┳┓┏┓┓┏  ┳┏┳┓  ┳┳┓┏┓┓┏  ┳┏┳┓  ╻\n┃┃┃┃┃┃┃  ┃ ┃   ┃┃┃┃┃┃┃  ┃ ┃   ┃\n┛ ┗┗┛┗┛  ┻ ┻   ┛ ┗┗┛┗┛  ┻ ┻   •\n\nOH NO ! there is a boulder on the road !\ni need a spell that will help me to move it:");
    read(0, flag, 56);
    while(i < l) {
        char c = x1[i] ^ x2[i];
        if(flag[i] != c) {    
            f = 1;
        }
        i++;
    }
    if (f == 0){
        puts("thank you for helping me!\nnow i can continue my journey :)");
        return 0;
    } else {
        puts("i cant't move it move it :(\n");
        return 1;
    }
}
//movcc  -Wf--no-mov-flow source.c -o chall