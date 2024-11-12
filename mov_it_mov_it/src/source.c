#include <stdio.h>
int main() {
    //----
    int x1[21] = {110, 29, 158, 193, 76, 235, 93, 30, 226, 146, 226, 183, 121, 139, 168, 46, 193, 106, 54, 109, 244};
    int x2[21] = {20, 120, 236, 174, 40, 138, 36, 101, 135, 234, 131, 218, 9, 231, 205, 113, 167, 6, 87, 10, 137};
    int l = 21, i = 0,f = 0;
    char flag[21];
    //----
    puts("podaj flage: ");
    scanf("%21s",flag);
    while(i < l) {
        char c = x1[i] ^ x2[i];
        if(flag[i] != c) {    
            f = 1;
        }
        i++;
    }
    if (f == 0){
        puts("dzieki za flage\n");
        return 0;
    } else {
        puts("zle\n");
        return 0;
    }
}
//movcc  -Wf--no-mov-flow source.c -o chall
// -no-mov-flow musi byc inaczej nie nie dziala w gdb
//https://github.com/xoreaxeaxeax/movfuscator