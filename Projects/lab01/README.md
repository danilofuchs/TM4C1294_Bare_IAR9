# Lab 01

## Goal

Build a blinking LED using delay loops, instead of timer interrupts.

Analyze how different compiler optimization levels can break the implementation.

## Implementation

A naive implementation of a delay loop considering the system clock, a period and
how many clocks it takes for the CPU to compute a single loop iteration.

```c
uint32_t counter_max = PERIOD_SECONDS * SYSTEM_CLOCK / CLOCKS_PER_EMPTY_LOOP;

for (uint32_t counter = 0; counter < counter_max; counter++) {}
```

To blink the LED every 1 second, we must simply configure the GPIO ports, run an infinite
loop which waits for 1 second and flips the LED output.

## Analysis

For each combination of system clock and optimization level, the `CLOCKS_PER_EMPTY_LOOP`
constant was tweaked empirically to reach a period of 1 second.

| System Clock | Optimization Level | Clock cycles per loop | Does it work? |
| ------------ | ------------------ | --------------------- | ------------- |
| 24MHz        | low                | 5                     | ✔️            |
| 24MHz        | medium             | 5                     | ✔️            |
| 24MHz        | high               | 0                     | ❌            |
|              |                    |                       |               |
| 120Mhz       | low                | 5                     | ✔️            |
| 120Mhz       | medium             | 5                     | ✔️            |
| 120Mhz       | high               | 0                     | ❌            |

On high optimization level, the compiler removes the delay loop completely, as it
could be considered _dead code_, thus making our implementation invalid.

> Note: On high optimization level, it only starts to work if we add a Log Breakpoint,
> as the communication with the debugger adds a delay on the code. However, the loop
> is never present in the compiled code itself

Analyzing the disassembly, the empty loop runs the following compiled
instructions:

```arm
ADDS    R0, R0, #1  ; ??main_1
CMP     R0, R5
BCC.N   ??main_1
```

It is possible to assume that the Cortex M4 core takes 5 clock cycles to run
these 3 instructions.
