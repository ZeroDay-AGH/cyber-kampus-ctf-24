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

