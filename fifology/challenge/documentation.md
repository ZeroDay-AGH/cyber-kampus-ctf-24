# FIFO-ASM

FIFO-ASM is a simple assembly language that operates on a FIFO queue. It is designed to be simple and easy to understand while providing a basic set of instructions to perform arithmetic operations, data movement, and control flow, as well as system calls.

Now you can push a string letter by letter onto queue, pop them one by one and get the string in correct order!

---

## Registers and queue
- **A**, **B**, **C**: Three general-purpose registers that can store integer values.
- All registers can store integer values and are accessible through mnemonics or their indices.
- **flag**: A special register that stores the result of comparison operations.
- **fd** (File Descriptor): A special register that stores the file descriptor of the currently open file.
- **Queue**: A FIFO queue that stores integer values. The queue is used to pass arguments to system calls and store data. Values can be pushed to the back of the queue and popped from the front (First In First Out).
---

## Mnemonics

### 1. Data Movement

#### **PUSH**
- **Description**: Adds a value to the queue.
- **Syntax**: `PUSH <value or register>`
- **Examples**:
  - `PUSH 10` → Pushes the value `10` into the queue.
  - `PUSH A` → Pushes the value in register `A` into the queue.

#### **POP**
- **Description**: Removes a value from the queue.
- **Syntax**:
  - `POP` → Removes the front of the queue without storing it.
  - `POP <register>` → Removes the front of the queue and stores it in a register.
- **Examples**:
  - `POP` → Removes the first value from the queue.
  - `POP B` → Stores the first value of the queue in register `B`.

### **GET**
- **Description**: Retrieves a value from the queue at a specific index and stores it in a register. The index can be specified as either a register or a direct value.
- **Syntax**: `GET <destination register> <index (register or value)>`
- **Examples**:
  - `GET A 2` → Retrieves the value at index `2` of the queue and stores it in register `A`.
  - `GET B C` → Uses the value in register `C` as the index, retrieves the corresponding value from the queue, and stores it in register `B`.
  - The index is 0-based, meaning `queue[0]` corresponds to the front of the queue.


#### **MOV**
- **Description**: Copies a value between registers or assigns a constant to a register.
- **Syntax**: `MOV <destination register> <source (register or value)>`
- **Examples**:
  - `MOV A B` → Copies the value of register `B` into register `A`.
  - `MOV C 10` → Assigns the value `10` to register `C`.

---

### 2. Arithmetic Operations

#### **ADD**
- **Description**: Adds two values and stores the result in the destination register.
- **Syntax**: `ADD <destination register> <source (register or value)>`
- **Examples**:
  - `ADD A B` → Adds the values of `A` and `B`, stores the result in `A`.
  - `ADD C 5` → Adds `5` to the value in `C`.

#### **SUB**
- **Description**: Subtracts the second value from the first and stores the result in the destination register.
- **Syntax**: `SUB <destination register> <source (register or value)>`
- **Examples**:
  - `SUB A B` → Subtracts the value of `B` from `A`, stores the result in `A`.
  - `SUB C 3` → Subtracts `3` from the value in `C`.

#### **MUL**
- **Description**: Multiplies two values and stores the result in the destination register.
- **Syntax**: `MUL <destination register> <source (register or value)>`
- **Examples**:
  - `MUL A B` → Multiplies the values of `A` and `B`, stores the result in `A`.

#### **DIV**
- **Description**: Divides the first value by the second and stores the result in the destination register.
- **Syntax**: `DIV <destination register> <source (register or value)>`
- **Examples**:
  - `DIV A B` → Divides the value of `A` by `B`, stores the result in `A`.

---

### 3. Bitwise Operation

#### **XOR**
- **Description**: Performs a bitwise XOR operation between two values and stores the result in the destination register.
- **Syntax**: `XOR <destination register> <source (register or value)>`
- **Examples**:
  - `XOR A B` → XORs the values of `A` and `B`, stores the result in `A`.

---

### 4. Comparison

#### **CMP**
- **Description**: Compares two values and sets the `flag` register.
  - `flag = 0` → Values are equal.
  - `flag = 1` → First value is greater.
  - `flag = 2` → Second value is greater.
- **Syntax**: `CMP <value1 (register or value)> <value2 (register or value)>`
- **Examples**:
  - `CMP A B` → Compares the values of `A` and `B`.
  - `CMP C 10` → Compares the value of `C` with `10`.

---

### 5. Control Flow

#### **JMP**
- **Description**: Jumps to a specific instruction.
- **Syntax**: `JMP <instruction number (register or value)>`
- **Examples**:
  - `JMP 5` → Jumps to instruction 5.
  - `JMP A` → Jumps to the instruction indicated by register `A`.

#### **JZ**
- **Description**: Jumps if the `flag` is `0` (values are equal).
- **Syntax**: `JZ <instruction number (register or value)>`
- **Examples**:
  - `JZ 3` → Jumps to instruction 3 if the `flag` is `0`.

#### **JNZ**
- **Description**: Jumps if the `flag` is not `0`.
- **Syntax**: `JNZ <instruction number (register or value)>`
- **Examples**:
  - `JNZ 8` → Jumps to instruction 8 if the `flag` is not `0`.

- **IMPORTANT NOTE**: The instruction number is 0-based, meaning the first instruction is at index 0.
---

### 6. System Calls

#### **SYSCALL**
- **Description**: Executes various system-level operations based on a **queue** value. The queue shoud contain the system call id followed by the required parameters.
- **Syntax**: `SYSCALL`
- **Operations**:
  - **Print**: `id = 0`
    - Expects the queue to contain the following:
      - `buf_len`: Number of characters to print.
      - `buf`: ASCII values of characters to print.
      - `buf_len` should be pushed first followed by the ASCII values of the characters to print `buf`.
    - Example: `PUSH 0; PUSH 1; PUSH 65;SYSCALL` will print `A`.
  - **Open File**: `id = 1`
    - Expects the queue to contain the following:
      - `filename_len`: Number of characters in the filename.
      - `filename`: ASCII values of the filename.
      - `filename_len` should be pushed first followed by the ASCII values of the filename `filename`.
    - Sets the `fd` register to the file descriptor of the opened file.
    - Example `PUSH 1; PUSH 4; PUSH 116; PUSH 101; PUSH 114; PUSH 116; SYSCALL` will open the file `test` and store the file descriptor in `fd`.
  - **Read File**: `id = 2`
    - Reads from the opened file (stored at `fd`) and pushes its length and content into the queue in this order.
    - Example: `PUSH 2; SYSCALL` will read from the file previously opened and push the length and content of the file into the queue.
  - **Close File**: `id = 3`
    - Closes the currently open file.
    - Example: `PUSH 3; SYSCALL` will close the file previously opened.
  - **Input from Stdin**: `id = 4`
    - Reads input from the user and pushes its length and content into the queue in this order.
    - Example: `PUSH 4; SYSCALL` will read input from the user and push the length and content of the input into the queue.
  - **IMPORTANT NOTE**: System calls depend only on the queue values !
---

### 7. Program Termination

#### **END**
- **Description**: Terminates program execution.
- **Syntax**: `END`
- **Example**:
  - `END` → Ends the program.

---

## Example Programs

### 1. Hello World
```assembly
PUSH 0;
PUSH 11;
PUSH 72;
PUSH 101;
PUSH 108;
PUSH 108;
PUSH 111;
PUSH 32;
PUSH 119;
PUSH 111;
PUSH 114;
PUSH 108;
PUSH 100;
SYSCALL;
END
```
Output: `Hello world`

### Printing numbers from 4 to 0 in a loop

```assembly
MOV A 5;
CMP A 0;
JZ 10;
MOV B A;
ADD B 47;
PUSH 0;
PUSH 1;
PUSH B;
SYSCALL;
SUB A 1;
JMP 0;
END
```

### Read user input and open file with that name, then print its content

```assembly
PUSH 4;
PUSH 1;
SYSCALL;
SYSCALL;
PUSH 2;
PUSH 0;
SYSCALL;
SYSCALL;
END
```



