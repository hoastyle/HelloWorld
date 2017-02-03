# Compile
32 bit program on 64 bit cpu and os
`gcc -c -fno-builtin hello.c -m32`

# Link
32 bit program on 64 bit cpu and os
`ld -static -e nomain -m elf_i386 -o hello hello.o`

# Using link file
`ld -static -e nomain -m elf_i386 -T hello.lds -o hello_lds hello.o`

# Using bfd
First of all, install binutils-dev.
`gcc bfd_target.c -o bfd_target -lbfd`
