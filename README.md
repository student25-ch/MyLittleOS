# MyLittleOS
A simple hobby x86 bare-metal operating system written for learning OS development.

## 项目介绍
MyLittleOS 是一个个人学习用的简易x86裸机操作系统，从零手写内核。
- 没有依赖 libc，属于独立裸机程序
- 实现 VGA 文本缓冲区输出
- PS/2 键盘扫描码读取
- PS/2 鼠标基础初始化
- RTL8139 网卡驱动占位（待开发）

> ⚠️ 本项目仅用于学习操作系统底层原理，不适合作为日常使用系统。

## 编译环境
- Host: Windows
- 编译器：i686-elf 交叉编译器
- 汇编器：NASM
- 模拟器：QEMU

## 编译步骤
```bash
# 编译汇编与C代码，生成kernel.elf
build.bat
# 在QEMU中启动系统
qemu-system-i386 -kernel kernel.elf
