# ASSP Final Project - Task 6 - Custom functional unit

For this task, we decided to implement a MAC (multiply-accumulate) unit.

## Specs
THE MAC needs to have:
- two inputs for the two operands
- one output to read the accumulator
- method to clear the accumulator (set to 0)
- - this could be a more generic "initialize" or "set" method to set the accumulator to arbitrary value

The MAC should support 16-bit signed integer number inputs and output, which means internally it needs to use 32-bit numbers.

## Design
What does a MAC actually do?
```math
a = a + ( b * c )
```

That's it. This should be fairly easy to implement as a OSAL behaviour definition.

See [the behaviour file](fir-tta-with-mac-src/mac.cc) for details.

## Usage
To see that the custom MAC functional unit works as expected, it should be included and used in some sample program.

A simple FIR filter with the following form could be adapted to use the MAC: [01-fir-basic-src](01-fir-basic-src/).

First step is to utilize TTA architecture: [02-fir-tta-src](02-fir-tta-src/).

Second step is to add a custom MAC unit and use it: [03-fir-tta-with-mac-src](03-fir-tta-with-mac-src/).

Third step is to implement the unit with VHDL so it can be synthesized: [04-fir-tta-with-mac-vhdl](04-fir-tta-with-mac-vhdl/).
