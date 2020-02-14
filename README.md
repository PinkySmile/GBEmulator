# GBEmulator

## Installation
for using the Gameboy™ Emulator, you must compile it from source

    mkdir build
    cd build
    cmake ..
    make GBEmulator
    
## Utilisation

    ./GBEmulator path/to/rom

## Command line argument

#### -d
  Launch the Gameboy™ Emulator, see debug topic below for more information

#### -l \<port\>
  Open the port \<port\> for Gameboy™ link cable connection.

#### -c \<ip:port\>
  Connect to \<ip:port\> for Gameboy™ link cable connection.

## Debug mode

When the Gameboy™ Emulator is launched with a ``-d`` argument, a new window open with all the CPU's informations and a gdb-like prompt open in the terminal.
You can enter some commands in this prompt:

    help: Display all commands
    jump <addr>: make the Gameboy™ just to a specific adress.
    next: continue the instruction flow until the next line.
    step: execute the current instruction.
    continue: continue the instruction flow until the next breakpoint.
    ram [<border1> <border2>]: dump ram content from <border 1> to <border 2>.
    print <value>: if a register is passed, print value in this register, if an address is passed, print value at this address.
    registers: dump all registers value.
    break <addr>: set breakpoint at the given address

## Documentation

You can see the whole documentation here: https://gegel85.github.io/GBEmulator/annotated.html
