# Tests
## Test 1
Test of basic execution and proper syscall reinterpretation.
Result: `Success`
    * Correct interception of syscalls (blocking them from going straight to kernel)
    * Correct reinterpretation of `write` and `exit` syscalls
```bash
┌──(bogdan㉿DESKTOP-VOVUFNJ)-[~/projects/virtkernel2]
└─$ make rebuild -j10
make[1]: Entering directory '/home/kali/projects/virtkernel2'
[+] Built runproc.o (x64)                
[+] Built main.o (x64)                
[+] Built trace.o                
[+] Built startup.o (x64)                
[+] Built exit_handler.o (x64)                
[+] Built procmanger.o (x64)                
[+] Linked main.exe (x64)                
[+] x64 Build completed!



[+] Build completed!
make[1]: Leaving directory '/home/kali/projects/virtkernel2'

┌──(bogdan㉿DESKTOP-VOVUFNJ)-[~/projects/virtkernel2]
└─$ ./scripts/t_1.sh 

┌──(bogdan㉿DESKTOP-VOVUFNJ)-[~/projects/virtkernel2]
└─$ cd ./dist/linux_x64/

┌──(bogdan㉿DESKTOP-VOVUFNJ)-[~/projects/virtkernel2/dist/linux_x64]
└─$ ./main.exe ./temp
PID != 0
Pid 0
[enter] syscall 1
[USER OUTPUT]Hello, World![exit] syscall 60 -> 18446744073709551578
[USER] exit(0)
```