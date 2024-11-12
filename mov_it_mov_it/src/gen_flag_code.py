from random import randint
flag = 'zeroday{example_flag}'
xor_values = [randint(0, 255) for _ in range(len(flag))]
encrypted_flag = [ord(flag[i]) ^ xor_values[i % len(xor_values)] for i in range(len(flag))]
print(f'int x1[{len(xor_values)}] = ', end='{')
print(', '.join(map(str, encrypted_flag)), end='')
print('};')
print(f'int x2[{len(encrypted_flag)}] = ', end="{")
print(', '.join(map(str, xor_values)), end='')
print('};')
print(f'int l = {len(xor_values)}, i = 0, f = 0;')
print(f'char flag[{len(encrypted_flag)}];')

#movcc  -Wf--no-mov-flow source.c -o chall
'''
#include <stdio.h>
int main() {
    //----

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
'''