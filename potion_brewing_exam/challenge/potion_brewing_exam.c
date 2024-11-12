#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

const char *banner[] = {"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@@@@@@@@@@@&,//*,..  .@@@@@@@@@@@@@@@@@@@&@@@@",
                        "@@@@@@@@@@@@@@@@@@@@@@@@@@@ ...    @@@@@@@@@@@@@@@@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@@@@@@@@@@/// %#/*...//@@@@@@@@@@@@@@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@@@@@@@@@@@@,,...   *@@@@@@@@@@@@@@@@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@@@@@@@@@@@@&&**//#@%@@@@@@@@@@@@@@@@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@@@@@@@@@@@@(@&%#//((@@@@@@@@@@@@@@@@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@@@@@@@@@@@##(((((*/(*/@@@@@@@@@@@@@@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@@@@@@@@&/&&((((///***/,&@@@@@@@@@@@@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@@@@@&#((@@,    (///**(*,,%(@@@@@@@&@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@@@@@/@@@#,,  (((((//***/,,.#(@@@@@@@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@@(***@@####  .##((((//**/*..,(@@@@@@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@@(*/@@######%#%%###((//**/,../*@@@@@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@*&*,***//(#%#%%%%%##((/**/*.. ,@@@@@@@@@&@@@@",
                        "@@@@@@@@@@@@@@@@%..,**//((%%%(/(%%##(////,..(.@@@@@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@@*@.,,*  .*.,,**,,..,..,/,,*..@@@@@@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@@@@.(,    ......../..    ,...@@@@@@@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@@@@@&    .,,,....,,,,,.    @@@@@@@@@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@@@@@   .&/*/////**,,..... ,@@@@@@@@@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
                        "@@@@@@@@@@@@@@@@@@@&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&@@@@@@@@@@"};


void setup(void)
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}

void display_banner(void)
{
    for(int i = 0; i < (sizeof(banner)/sizeof(banner[0])); i++)
    {
        puts(banner[i]);
        usleep(40000);
    }
}

void get_ancient_power(void)
{
    char buf[128] = {0};

    int fd = open("flag.txt", O_RDONLY);
    if(fd == -1)
    {
        puts("Can't find flag.txt");
    }

    read(fd, buf, 128);
    puts(buf);

    close(fd);
}

void cast_spell(int mana)
{
    puts("Great, now let's test your potion!");
    puts("Drink it and cast a spell!");

    char spell[200];
    read(0, spell, mana);
}

int main(void)
{
    int mana = 0;

    setup();
    display_banner();
    
    puts("Welcome to your final potion brewing exam!");
    puts("You must mix the correct ingredients to create a mana potion.");
    puts("Be careful! If you don't follow the recipes, there might be unexpected consequences.");
    puts("You can add up to 4 ingredients.\n");

    for(int i = 0; i < 4; i++)
    {
        char ingredient[32];
        int mana_boost = 0;

        printf("> %d <\n", i+1);
        printf("ingredient: ");
        scanf("%30s", ingredient);
        printf("mana boost: ");
        scanf("%d", &mana_boost);
        if(mana_boost > 50)
        {
            puts("You can't add that ingredient!");
            puts("The potion will be unstable and we don't know what could happen.");
            puts("Exam is over!");
            exit(1);
        }

        mana += mana_boost;
    }

    cast_spell(mana);

    return 0;
}