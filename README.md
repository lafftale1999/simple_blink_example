# embedded_project_template
An easy project template for building and flashing firmware onto ATMega328p. Used in the cpp_for_developers course.

## main.cpp
This file contains the entrypoint for our program. Here we find the:

**DECLARATION**

This is where you declare all the global variables used in your program.
```cpp
// Our LED is connected to Digital Pin 13 - which is mapped
// to pin 5 on PORT B. Therefore, we define LED_PIN as PB5.
#define LED_PIN PB5 // PB5 is defined in the AVR library
```

---

**SETUP**

This is where you initialize your program properly.
```cpp
// SETUP
// 1. Initializes the millis library - starting to count
// milliseconds from the start of our program.
millis_init();

// 2. Enable global interrupts. This enables the hardware
// to cause interrupts.
sei();

// 3. Initialize the LED PIN.
// 3.1. We set the correct bit for the LED_PIN in the Data
// Direction Register for PORT B. See example #1 for visual
// representation.
DDRB |= (1 << LED_PIN);

// 3.2. Make sure that the output on our LED_PIN is set to low
// at start by unsetting it in the Port Register for PORT B.
// See example #2 for visual representation.
PORTB &= ~(1 << LED_PIN);
```

---

**SUPER-LOOP**

This is where your program runs and performs its logic.
```cpp
// SUPER-LOOP
// while(1) = run while true, which will be forever.
while(1) {

    // We toggle the output high and low on our LED_PIN.
    // See example #3 for visual representation.
    PORTB ^= (1 << LED_PIN);

    // A non-blocking delay from the millis.h library
    millis_wait_ms(1000);
}
```


## Makefile

This file contains all the instructions for compiling your program. For now it is set for running on ATMega328p.

You might have to configure the paths for the following variables in the Makefile:
```makefile
CC=C:\avr\bin\avr-g++
LD=C:\avr\bin\avr-ld
OBJCOPY="C:\avr\bin\avr-objcopy"
OBJDUMP="C:\avr\bin\avr-objdump"
AVRSIZE="C:\avr\bin\avr-size"
OBJISP="C:\avr\bin\avrdude"
```

## millis
Courtesy of Zak Kemble - a library to keep track of time in the AVR mcu space.

# Bitmanipulation

## Example #1: Setting a bit
When we are setting a bit to HIGH in a register we use the `|`-operator. In the code we do this here:

```cpp
// 3. Initialize the LED PIN.
// 3.1. We set the correct bit for the LED_PIN in the Data
// Direction Register for PORT B. See example #1 for visual
// representation.
DDRB |= (1 << LED_PIN);
```

### `|`-operator (or)
The `or`-operator will compare two bits in the same position and return results based on the following scenarios:
* One of the bits are 1 - return 1
* None of the bits are 1 - return 0

This is very similar to how `||` evaluate in control statements

### Expression
The line `DDRB |= (1 <<< LED_PIN);` is executed in the following way:

![Display of how a bit is set within a register](./resources/Setting%20a%20register.png)

>**Note:** If you think about this, if any other bit is set to HIGH in the register, this operation will not change its value - since the `|`-operator only needs one of the bits to be `1` to return `1`.

## Example #2: Unsetting a bit
When we are unsetting a bit, also known as setting a bit to LOW, we use the `&`-operator. In the code we do this here:

```cpp
// 3.2. Make sure that the output on our LED_PIN is set to low
// at start by unsetting it in the Port Register for PORT B.
// See example #2 for visual representation.
PORTB &= ~(1 << LED_PIN);
```

### `&`-operator (and)
The `and`-operator will compare two bits in the same position and return results based on the following scenarios:
* Both of the bits are 1 - return 1
* Only one of the bits are 1 - return 0
* None of the bits are 1 - return 0

### Expression
The line `PORTB &= ~(1 <<< LED_PIN)` is executed the following way:

![Display of how a bit is unset within a register](./resources/Unsetting%20a%20bit.png)

>**Note:** If you think about this, if any other bit is set to HIGH in the register, this operation will not change its value - since the `&`-operator only needs both of bits to be `1` to return `1`.

## Example #3: Toggling a bit
Using the `^`-operator (xor) we can toggle a bit in a register. In this example, I will ommit the way we shift `(1 << LED_PIN)`, you can find how this is performed in the previous examples.

We are toggling a bit in this line of code:

```cpp
// We toggle the output high and low on our LED_PIN.
// See example #3 for visual representation.
PORTB ^= (1 << LED_PIN);
```

### `^`-operator (xor)
The `xor`-operator will compare two bits in the same position and return results based on the following scenarios:
* The bits have different values - return 1
* The bits have same values - return 0

### Expression
The line `PORTB ^= (1 << LED_PIN)` is executed in the following way:

![Display on how to toggle a bit within a register](./resources/Toggling%20a%20bit.png)