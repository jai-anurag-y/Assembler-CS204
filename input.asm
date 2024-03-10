.data
var: .word 0x12345678
str: .asciiz "demo"


.text
lw x15, var
addi x10, x10, 20
Label:
blt x10, x20, Label