1. Uruchomić w gdb

2. Dać breakpoint na puts (b *puts) (inne breakpointy też prawdopodobnie działają, puts jest widoczne w debugerze)

3. Stack:
```
00:0000│ eax esp 0x85f6134 (stack+2096884) —▸ 0x804b3d6 (main+8442) ◂— mov dword ptr [0x804d100], eax
01:0004│         0x85f6138 (stack+2096888) —▸ 0x804d0c8 ◂— jp 0x804d136 /* 0xa656c7a; 'zle\n' */
02:0008│         0x85f613c (stack+2096892) ◂— 0x7d /* '}' */
```
widać że na 0x85f613c jest koniec flagi

4.  rwatch *(int *) 0x85f613c

5. odczytać kolejne wartości z Value: [wartość] i zamienić na chr (np. w pythonie)

6. profit

7. solve script:

```python
#gdb -x solve.py
#podac jako flage cokolwiek
import pwndbg
import pwndbg.commands
import gdb
file = './chall'
address = 0x85f613c
values = []
def print_value(event):
    value = gdb.parse_and_eval(f'*(int *) {address}')
    print(f'Value at address {hex(address)} changed to: {value}')
    values.append(chr(value))
    print(values)
    gdb.execute("c")
# Set a read-write watchpoint on the address
gdb.execute(f'rwatch *(int *) {address}')

# Connect the event handler to the watchpoint event
gdb.events.stop.connect(print_value)

# Load the binary file
gdb.execute(f'file ./{file}')

# Run the program
gdb.execute('run')
gdb.execute('c')
gdb.execute('c')

```

output po gdb -x solve.py
```
Hardware read watchpoint 1: *(int *) 140468540

Value = 32
0xf7fd01d7 in _dl_lookup_symbol_x (undef_name=0x80481e3 "exit", undef_map=0xf7ffda40, ref=0x85f61f8, symbol_scope=<optimized out>, version=0xf7fbeab0, type_class=1, flags=1, skip_map=0x0) at ./elf/dl-lookup.c:842
842     ./elf/dl-lookup.c: No such file or directory.
Value at address 0x85f613c changed to: 32
['\x00', '\x00', 'z', 'e', 'r', 'o', 'd', 'a', 'y', '{', 'e', 'x', 'a', 'm', 'p', 'l', 'e', '_', 'f', 'l', 'a', 'g', '}', ' ']
[Inferior 1 (process 69272) exited with code 01]

```