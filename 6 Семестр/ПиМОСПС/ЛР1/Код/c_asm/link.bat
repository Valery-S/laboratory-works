C:\TASM\BIN\TASM -la -zi %1
pause
C:\BorlandC\BIN\bcc -c -S -v -IC:\BorlandC\INCLUDE %2
pause
C:\TASM\BIN\TASM  %2
pause
C:\BorlandC\BIN\TLINK –v C:\BorlandC\LIB\c0s.obj+%1+%2,c_asm.exe,c_asm.map,C:\BorlandC\LIB\cs.lib
pause
c_asm


