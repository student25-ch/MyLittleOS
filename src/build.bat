@echo off
set "PATH=F:\dawasd\bin;C:\osdev\bin;%PATH%"

echo.
echo ========== 汇编 boot.asm ==========
nasm -f elf32 boot.asm -o boot.o
if %errorlevel% neq 0 (
    echo 汇编出错！
    pause
    exit /b
)

echo.
echo ========== 编译 kmain.cpp ==========
i686-elf-g++ -ffreestanding -m32 -fno-exceptions -fno-rtti -c kmain.cpp -o kmain.o
if %errorlevel% neq 0 (
    echo C++编译出错！
    pause
    exit /b
)

echo.
echo ========== 链接内核 ==========
i686-elf-ld -m elf_i386 -T linker.ld boot.o kmain.o -o kernel.elf
if %errorlevel% neq 0 (
    echo 链接出错！
    pause
    exit /b
)

echo.
echo ========== 启动QEMU（图形窗口，支持鼠标键盘） ==========
:: 开启图形窗口，PS2键鼠，rtl8139网卡
qemu-system-i386 -kernel kernel.elf -device ps2-mouse -device rtl8139,netdev=net0 -netdev user,id=net0
