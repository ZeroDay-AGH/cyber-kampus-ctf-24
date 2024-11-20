#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 128

void setup(void)
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}

int letter2value(char letter)
{
    if(letter >= 'A' && letter <= 'Z')
    {
        return letter - 'A';
    }

    if(letter >= 'a' && letter <= 'z')
    {
        return letter - 'a' + 26;
    }

    if(letter >= '0' && letter <= '9')
    {
        return letter - '0' + 52;
    }

    if(letter == '+')
        return 62;
    
    if(letter == '/')
        return 63;

    if(letter == '=')
        return -1;

    puts("invalid character");
    exit(1);
}

void decode4bytes(char *encoded, char *decoded)
{
    int values[4] = {
        letter2value(*encoded),
        letter2value(*(encoded+1)),
        letter2value(*(encoded+2)),
        letter2value(*(encoded+3))
    };

    char first = 0;
    char second = 0;
    char third = 0;

    if(values[0] != -1)
    {
        first = (values[0] << 2);
    }

    if(values[1] != -1)
    {
        first |= (values[1] >> 4);
        second = (values[1] << 4);
    }

    if(values[2] != -1)
    {
        second |= (values[2] >> 2);
        third = (values[2] << 6);
    }

    if(values[3] != -1)
    {
        third |= (values[3]);
    }

    if(values[0] != -1 && values[1] != -1)
    {
        *decoded = (char)(first & 0xff);
    }
        
    if(values[1] != -1 && values[2] != -1)
    {
        *(decoded+1) = (char)(second & 0xff);
    }
        
    if(values[2] != -1 && values[3] != -1)
    {
        *(decoded+2) = (char)(third & 0xff);
    }
}

void b64decode(char *encoded, char *decoded)
{
    int enc_len = strlen(encoded);
    write(1, "decoding string: ", 17);
    write(1, encoded, enc_len);
    puts("");

    if(enc_len % 4 != 0)
    {
        puts("invalid size");
        exit(1);
    }

    for(int i = 0, j = 0; i < enc_len; i+=4, j+=3)
    {
        decode4bytes(encoded+i, decoded+j);
    }
}

void __attribute__((naked)) strip(char *data)
{
    asm("push %rdi");
    char *p = data;
    size_t i = 0;
    while(*p != '\n' && i++ < (BUFSIZE*2))
        p++;

    *p = 0;
    
    // make sure there is 'pop rdi; ret' gadget
    asm("pop %rdi; ret");
}

void read_base64(char *buf)
{
    puts("Encoded spell: ");
    fgets(buf, BUFSIZE*2, stdin);
    strip(buf); 
}

struct Bufs
{
    char encoded[BUFSIZE*2];
    char decoded[BUFSIZE];
};

int main(void)
{
    struct Bufs bufs;

    setup();
    memset(bufs.encoded, 0, BUFSIZE*2);

    puts("The ancient wizards used magical runes to encode their spells, protecting their secrets from outsiders.");
    puts("These runes are based on a mystical system REALLY similar to Base64 encoding.");
    puts("Here you can use one of the runes to decode spells.");

    read_base64(bufs.encoded);

    b64decode(bufs.encoded, bufs.decoded);

    printf("Decoded: %s", bufs.decoded);
    puts("\nOkay bye!");

    return 0;
}