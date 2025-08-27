# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    README.md                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/27 16:35:13 by jcummins          #+#    #+#              #
#    Updated: 2025/08/27 18:03:49 by jcummins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NOTES:

From OliverStem Foundations of Assembly Programming Youtube Playlist

## Binary Basics 1:
Base 2 Compared to base 10 decimal. Don't need to make notes here.

## Binary Basics 2:

### Adding binary
Simply base 2. carry the 1 if 1 + 1
e.g. 1+1 == 10

### Signed binary numbers:
Typically group in 8 bits = byte, further divide into two halves of 4 bits each.

The TOPMOST bit represents the sign: 1 signifies negative, 0 signifies positive.
```
1000 0010 = -2
0000 0000 = 2
```
We would like, as with decimal, binary to folow the rule A + (-A) = 0
```
but 1000 0010 (-2) + 0000 0010 (2) =/= 1000 0100 (4)
```
So we apply 'two's complement' to negative values.
We start by inverting all the bits (one's complement)
```
0000 0010 +
1111 1101 (one's complement)
+		1
---------
0000 0010 (two's complement)
```
This version of the number now satisfies the above expression
```
0000 0010 +
1111 1101 =
---------
0000 0000
```
The one that is carried reflects the sign of the number, but in assembly would jsut go offinto another registry called the 'carry registry'
So if you see some massive looking numbers with loads of 1111, it's probably a negative number using one's complement.

## Hex Basics:

Represent binary numbers in a more compact format with base 16.
```
0 -> 0
A -> 10
H -> 15
```
This is effective at representing binary numbers because each maps to 4 bits
Therefore a whole byte is only two characters in hex. Very basic.

## x86 Processor Architecture:

How things are fetched from memory, how it processes instructions.
```
CPU: ALU (arithmetic logic unit), Control Unit, Clock, Registers
Memory
I/O decive
```
## Busses

Ways that the cpu communicates with other devices - over buses
```
Control Bus: Helps synchronise all actions attached to the bus
Address Bus: Holds Addresses in data, pointing to different locations where things will move
Data Bus: Handles transfer of data between places
```

## CPU:
### Architecture
```
High Frequency Clock - Cycles between off and on (one whole cycle) to synchronise between the CPU and bus
Control Unit - Decode binary and direct operations to other units
ALU (Arithmetic logic unit) - Carries out logical operations
Registers (Storage Locations) - Fast Storage that's very close to the CPU
```
### Instruction Execution Cycle
The CPU completes apredefined set of steps to execute an instruction
This is called a **Fetch decode execute procedure**
```
1.	Fetch an instruction from the instruction queue
2.	Decode the instruction and check for operands
3.	If operands are involved, fetch the operands from memory/registers
4.	Execute the instruction and update status flags
5.	Store the result if required
```
### Reading from Memory
Memory access is slower than register access
Requires the following steps:
1. Place the address of the value you want to read on the address bus
2. Changes the processor's RD pin (called assert)
3. Wait one clock cylce for memory to respond
4. Copy the data from the data bus to the destination
Each step takes approcimately one clock cycle
To compare, register access usually takes only one clock cycle because it is direct

### Caching
To reduce read/write time for memory, caches are used
In x86:
* Level-1 cache is stored on the CPU
* Level-2 cache is stored outside and accessed by high-speed data bus
Constructed using static RAM, which does not need to be refreshed constantly vs dynamic ram

# x86 Processor and Features
### Modes of Operation
* Protected Mode:
	* The native processor state.
	* Keeps you within the memory bounds assigned to the process
	* Safer and more restrictive
* Real Address Mode:
	* Allows you to directly access hardware addresses
	* Implements early Intel programming environment with the ability to swirch modes
* System Management Mode:
	* Provides an operation system with mechanisms for power management and security	
	* If we're designing a system for a chip we might use this to build something specific for that processor

### Register Fundamentals
* x86 is a 32-bit processor, each register is 32 bits in size
* Eaxmple Registers: EAX, EBX, ECX, EDX
	* You can access just 16 bits by dropping the E, giving AX, BX, CX, DX
	* You can access 8-bit high: AH,BH,CH,DH
	* You can access 8-bit low: AL,BL,CL,DL
* If you have a lot of 8-bit numbers you can store them compactly in the same 32-bit registers

### Registers
| Name | Decription |
| --- | --- |
| EAX | Extended Accumulator, automatically used by multiplication and division instructions |
| EBX | General Purpose |
| ECX | Used as a loop counter by the CPU |
| EDX | General purpose |
| ESI | High speed memory transfer |
| EDI | High speed memory transfer |
| EBP | Used to reference function parameters and local variables on the stack |
| ESP | A pointer to the current stack address, most recent available |

### Special Puporse Registers
* EIP: The instruction pointer, pointes to the address of the next instruction
* EFLAGS: Flags to denote the status of an operation:
	* CF (carry flag)
	* OF (overflow flag)
	* SF (sign flag)
	* ZF (zero flag)
	* AC (auxiliary carry)
	* PF (parity flag)

# Writing pragrams using NASM
* NASM creates simplified syntax based on intel. Linux tends to use AT&T internally which is more complex and hard to learn
Here's a sample program - it stores 1 in both eax and ebx registers, and calls the system to exit (eax) with return code 1 (ebx)
```
section .data ; stores variables

section .text ; code to run
global _start ; _start is a label for a section of code
			; exporting _start with global which tells the computer where to start the program.
_start:
	MOV eax,1	; MOV moves data from one location to another
	MOV ebx,1
	INT 80h		; interrupt makes system call based on the value in EAX.
				; 1 indicates EXIT system call.
				; The status code is whatever is in EBX
```
To create a program, compile then link.
* Compile: nasm -f elf -o object.o inputfile.s
* Link: ld -m elf_i386 -o outputfile object.o
	* -m specifies the assembly language (x86 vs 64 etc)

### Debug with GDB
* Start GDB with program as normal
* Layout asm
* break _start, run
* stepi	- step one instruction forward
* info registers eax - prints the contents of eax register, obviously
* a dollar sign is the literal address or number - without, it gets the value at that address instead

# Storing Numeric Data
Declaring variables, we need 3 things:
* Name
* Type (really just the size)
	* num DB (Define Byte - 8 bits)
	* num DW (Define Word - 2 bytes - 16 bits)
	* num DD (4 bytes, 32 bits)
	* num DQ (8 bytes, 64 bits)
	* num DT (10 bytes, 80 bits)
	* we're just storing binary so there is no distinction other than size
* Initial Value

# Working with Byte and Word Data
In the following we store two bytes (DB) and they are next to each other in memory
So in GDB looking at the register bx we see 513 because 0x00000201 is 513.
Using instead info registers bh and lh we can split this into lower and upper half to see the 0x01 and 0x02
Using x/x <data address> we can see the full 32 bit memory address.
```
section .data
	num DB 1
	num2 DB 2

section .text
global _start

_start:
	MOV ebx,[num]	; moves the whole 32 bits at that address
	MOV ecx,[num2]
	MOV eax,1
	INT 80h
```
registers are just a, b, c, d.
ebx = 32 bit
bx = 16 bit
bl = lower 8 bit (less significant figures)
bh = higher 8 bit (more significant figures)

So, instead we use MOV bl,[num] and MOV cl,[num2]

# Characters, Strings and Lists
Some of the different data types in assembly.
To look at GDB in intel instead of AT&T, "set disassembly-flavor intel"
To declare a list 
```
section .data
	list DB 1,2,3,4,0

section .text

global _start

_start:
	MOV bl,[list]
	MOV eax,1
	INT 80h
```
And in GDB:
* BYTE PTR ds:0x8041000	- just means it's a byte per item and like a C pointer
* x/x 0x804a000 - shows the list in memory as 04030201 (per byte, little endian)
* x/2x - shows two memory addresses in order, but the byte order is not direct
* x/4bx - the b separates each byte so we can see their true order in memory

### Lists in assembly
* you always need something to mark the end of the list.
* In strings this is usually null but it could be different for other data types
* Need to add the null terminator manually:
```
section .data
	string1 DB "ABA",0
```

# Uninitialized Data
How to set data aside without putting anything in it (I guess like malloc)
Need to add a .bss section (block starting symbol)
```
section .bss	; block starting symbol, declared, not initialized
	num RESB 3

section .data	; initializes to default value
	num2 DB 3 DUP(2) ; writes 2 into memory 3 times

section .text

global _start

_start:
;	MOV [num],1	; won't work - assembly has no understanding of variable size
	MOV bl,1		; put the number in a register first
	MOV [num],bl	; move register to reserved space, giving info about variable size
	MOV [num+1],bl	; access second byte
	MOV [num+2],bl	; access third byte.
;	For larger variables you must be accurate about number of bytes, unlike C pointers
;	But you can do [array + ebx*4] to explicitly scale the number with the register size
	MOV eax,1
	INT 80h
```

# Arithmetic Instructions
Looking at the ADD operation and how it interacts with the EFLAGS register
* After an ADD operation 1 and 3, you can see the eflags register in gdb
* The flags gives information about thge operation that was just run
* GDB: info registers eflags
* In this case you can see PF and IF. Bits are set on or off for each flag
	* PF - Parity Flag is on if the result is odd, off if it is even
	* IF - Interrupt Flag is on if interrupts are allowed and is usually on anyway
	* Why would we care about parity? Well, it's a common thing to check
	* We often use even and odd values to determine errors in data tranfers
		* If a bit flips, it indicates an issue in transmitting data

## Direct Binary Input
MOV eax,0b11111111	; 0b denotes direct binary in assembly

## Overflowing register size
* CF - Carry Flag - shows that the previous operation resulted in a carried number
	* This number will be in the carry register
* AF - Auxiliary Flag - when there is a carry or borrow out of the third bit
* ZF - if the result of the operation in zero

## How do we get the value out of the carry?
* ADC - 'Add with Carry' instruction
* ADC ah,0 ; ADC adds a given number AND what's in the carry register
* two n-bit registers added together will only ever result in n+1 bits so the flag is all that's needed
* Adding the carry flag to ah means it's given the correct significant figure 
```
section .data

section .text

global _start

_start:
	MOV al,0b11111111
	MOV bl,0b0001
	ADD al,bl	; adds both and stores in eax
	ADC ah,0	; adds the carry and zero into the higher register of a
	INT 80h
```

# Subraction and Sign Flags
It's easier in some ways because you don't need to carry.
You need to be aware of negative numbers but it's usually not terribly complex
* 0xfffffffe could clearly be a very large number instead of negative.
* If it is negative as the result of a calculation, the eflag will be set to denote it.
	* CF - carry flag for addition doubles as BORROW flag for subtraction
	* SF - Sign Flag - operation produced negative output
Negative numbers work very similarly to decimal negative numbers
```
section .data

section .text
global _start

_start:
	MOV eax,3
	MOV ebx,5
	SUB eax,ebx	; takes ebx (5) from eax and stores -2 in eax
	INT 80h
```

# Multiplying Values
### Unsigned Multiplication with MUL and IMUL
Uses the MUL instruction primarily with unsigned values
```
section .text
global _start

_start:
	MOV al,2
	MOV bl,3
	MUL bl	; MUL instruction automatically applies using the a register
			; a is a special purpose register 'accumulator' where multiplication results go
	INT 80h
```
What happens if the multiplication result is bigger than the register?
* It expands the size of the destination to fit the value you're storing
* E.g. it will make al into ax to accomodate 255 * 2

### Signed Multiplication
Uses the IMUL instruction with signed values
```
section .text
global _start

_start:
	MOV bl,2
	MOV al,0xFF	; without IMUL, this could be 255
	IMUL bl		; but it gets trated as -1
	INT 80h
```

# Dividing Values with DIV and IDIV
* Similar to multiplication, the main operand is the accumulator eax (to be divided)
* The remainder goes by convention into the edx register (I guess just d in general)
```
section .text
global _start

_start:
	MOV eax,11	; accumulator register to be divided
	MOV ecx,2
	DIV ecx		; eax gets the result 5, edx gets the remainder 1
	INT 0x80	; 0x like h denotes hex value
```

### Signed Division
Much like IDIV assumes that operands are signed

# Logical Operators
```
section .text
global _start

_start:
	MOV eax,0b1010
	MOV ebx,0b1100
	AND eax,ebx		; logical &
	MOV eax,0b1010
	MOV ebx,0b1100
	OR eax,ebx		; logical |
	MOV eax,0b1010
	NOT eax			; flips bits
		; BUT negating eax negates ALL of eax, including the unused 0 bits,
		; resulting in 0xfffffff5 (-11) instead of the expected 0b0101 (5)
	AND eax,0b1111	; so we then bit mask the result to clear everything but the last 4 bits
		; could also use 0xF instead of the literal binary
	MOV eax,0b1010
	MOV ebx,0b1100
	XOR eax,ebx		; Only 1 if one of the bits is on. Not both or 0
					; So this results in 0b0110 (6)
	INT 0x80
```

# Bit Shifts
Take a binary value and shift all the bits to the right or left
```
section .text
global _start

_start:
	MOV eax,2
	SHR eax,1	; shifts all bits 1 to the right (divides by 2)
	SHL eax,3	; multiplies by 2 three times (x8) = x2^3
	MOV ebx,-2
	SAR	ebx,1	; arithmetic shift right - preserves the signed bit
	SAL	ebx,3	; arithmetic shift left
	MOV eax,-2
	INT 0x80
```

# Comparisons and Jumps
```
	CMP eax,ebx	; cmp subtracts the registers and discards the result but flags
				; whether it's positive, negative, or 0
	JL	lesser	; jl = jump lesser, jump if eax is less than ebc
	JLE lequals	; jle = jump if lessor or equals to
	JE	equals	; je = jump equals
	JNE nequals	; jne = jump if not equals
	JG	greater	; jg = jump if greater
	JGE gequals	; jge = greater than or equals
	JZ	iszero	; jz = if result is zero
	JNZ isnzero	; jnz = jump if results isn't zero
	JMP	end		; jmp always runs if execution reaches this point
lesser:			; would always fall through to this command if JMP wasn't used
	MOV ecx,1
	JMP end
lequals:
	MOV ecx,2
	JMP end
equals:
	MOV ecx,3
	JMP end
```

# Loops
```
section .data
	list DB 1,2,3,4

section .text
global _start

_start:
	MOV eax,0	;	use this as an index
	MOV cl,0	;	becaue the list is bytes, use a single byte register

loop:
	MOV bl,[list + eax]	;	indexing through the list
	ADD cl,bl	;	adding the number retreived from the list to the accumulation
;	ADD eax,1	;	increment index
	INC eax		;	alternative increment instruction
	CMP eax,4	;	check to see if we are at the end of the array
;	JE	end		;	if so, jump to end
;	JMP loop	;	return to start of loop
	JNE loop	;	this sums both above commands in a more efficient way
end:
	MOV eax,1	;	need to give eax and ebx numbers that interrupt expects
	MOV ebx,1
	INT 0x80
```

# Floats
* Single precision - 32 bits. Double requires 64-bit.
* In GDB, using info registers on float registers like xmm1 outputs a lot of info about various interpretations of the binary kept there.
* Use print $xmm1.v4_float[0] to access the number as a decimal
* Obviously IEEE floats are not exact for all numbers because they are based on powers of two.
```
section .data
	x DD 3.14
	y DD 2.1

section .text
global _start

_start:
	MOVSS xmm0,[x]	; SS = Scalar Singleprecision
				; registers xmm0 to xmm15 are designed to hold decimal values
				; Scalar is a single decimal value
				; registers can work with packed data, multiple values together
				; recall that [x] means the value held at address x in .data
	MOVSS xmm1,[y]
	ADDSS xmm0,xmm1	; specific instruction name for decimal values
	MOV ebx,1
	INT 0x80
```

# Comparing floats
* There are similarly functioning but differently named commands for float comparison
* JE still works the same as equals, though.
```
section .data
	x DD 3.14
	y DD 2.1

section .text
global _start

_start:
	MOVSS xmm0,[x]
	MOVSS xmm1,[y]
;	CMP	; Won't work with floats
	UCOMISS xmm0,xmm1	; comparison AND jumps are different
	JB jumpbelow 	; jump below, equivalent to 'less than'
;	JBE jbelowequal	; below or equals
;	JA jumpabove	; equivalent to 'greater than'
;	JAE jaboveequal ; etc
;	JE jumpequals	; works the same on floats and bits
	JMP end

jumpbelow:
	MOV ecx,1
	JMP end

end:
	MOV eax,1
	MOV ebx,1
	INT 0x80

```

# Calling Standard C functions
* If we're running an object file created from assembly through gcc, we need main instead of _start.
* To compile the object with gcc we need
	* -no-pie 	- NOT position independant executable
		* PIC position independant code is a body of machine code that executes properly regardless of its memory address.
		* commonly used for shared libraries
		* was also used by older machines that lacked MMU memory management unit
		* instructions that refer to specific memory addresses sometimes execute faster
		* modern processors make the difference negligible
	* -m32		- explicitly an x86 architecture
```
extern exit
extern printf

section .data
	msg DD "Hello World!",0
	fmt DB "Output is: %s",10,0
section .text
global main

main:	; putting arguments on the FILO stack
	PUSH msg	; First in, Last out
	PUSH fmt
	CALL printf
	PUSH 1		; pushing the argument to exit
	CALL exit
```

# Calling Nonstandard C Functions
* Use extern to define an externally available function in C
* Also use extern to retreive an externally available function in assembly
```
extern test	; the function we defined as extern in test.c
extern exit	; standard c function

section .data

section .text
global main

main:
	PUSH 1	; putting 1 as the second argument onto the stack
	PUSH 2	; putting 2 as the first argument onto the stack
	CALL test ; return value automaticall stored in eax
	PUSH eax
	CALL exit
```

# Functions/Procedures
* A procedure is basically a function in x86
* How can we create functions in x86
* When you run the call, it saves the NEXT line of code after the CALL in ESP
* Apparently also on the stack? Maybe stack first, then into esp
	* Find this with info register esp
	* then x/wx $esp	// what does the w do? //
	* set {unsigned int}$esp = 0x08049184 to chagne the return address
* ESP is used to resume the calling process after RET
* There are security exploits around this idea, overwriting the stack return address
	* This can be done via buffer overflow
	* Typically you would return to libc to execute code
```
section .data

section .text
global main

addTwo:
	ADD eax,ebx
	RET	; returns eax to the calling location

main:
	MOV eax,4
	MOV ebx,1
	CALL addTwo
	MOV ebx,eax	; preserving that returned value
	MOV eax,1
	INT 0x80
```

# Function Arguments
* Often data must be put onto the stack because registers are a finite and precious resource
* Requires a little intricacy

