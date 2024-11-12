1. Uruchomić w gdb
2. Dać breakpoint na puts (b *puts) (inne breakpointy też prawdopodobnie działają)
3. Stack:
00:0000│ eax esp 0x85f6134 (stack+2096884) —▸ 0x804b3d6 (main+8442) ◂— mov dword ptr [0x804d100], eax
01:0004│         0x85f6138 (stack+2096888) —▸ 0x804d0c8 ◂— jp 0x804d136 /* 0xa656c7a; 'zle\n' */
02:0008│         0x85f613c (stack+2096892) ◂— 0x7d /* '}' */
widać że na 0x85f613c jest koniec flagi
3.  rwatch *(int *) 0x85f613c
4. odczytać kolejne wartości z Value:

solve script:
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