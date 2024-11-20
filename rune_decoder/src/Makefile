.PHONY: all

FLAGS=-fstack-protector -Wl,-z,relro,-z,now -z noexecstack -no-pie -Wall -Wextra

all:
	gcc $(FLAGS) rune_decoder.c -o rune_decoder

