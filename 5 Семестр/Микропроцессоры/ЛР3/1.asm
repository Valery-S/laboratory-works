lxi sp, 200h
:m1
ei
mvi a, 32h
out 01h
jmp m1

skip 20h
mvi a, 64h
out 01h
ret