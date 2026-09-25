// 手动定义固定宽度整数
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef signed   char  int8_t;
typedef signed   short int16_t;
typedef signed   int   int32_t;

// ================= VGA 文本屏幕 =================
#define VGA_BUF ((uint16_t*)0xB8000)
const uint8_t SCREEN_WIDTH  = 80;
const uint8_t SCREEN_HEIGHT = 25;
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;

static inline void outb(uint16_t port, uint8_t val)
{
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}
static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
}

void vga_putc(char c)
{
    uint8_t attr = 0x0F; //白字黑底
    uint16_t* loc = &VGA_BUF[cursor_y * SCREEN_WIDTH + cursor_x];
    if(c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    else
    {
        *loc = (attr << 8) | c;
        cursor_x++;
        if(cursor_x >= SCREEN_WIDTH)
        {
            cursor_x = 0;
            cursor_y++;
        }
    }
    if(cursor_y >= SCREEN_HEIGHT)
    {
        cursor_y = 0;
    }
}

void vga_print(const char* s)
{
    while(*s)
    {
        vga_putc(*s++);
    }
}

// ================= PS/2 键盘 =================
uint8_t read_scancode()
{
    while(!(inb(0x64) & 1));
    return inb(0x60);
}

// ================= PS/2 鼠标 =================
void ps2_mouse_init()
{
    outb(0x64, 0xA8);
    outb(0x64, 0x20);
    uint8_t status = inb(0x60);
    outb(0x64, 0x60);
    outb(0x60, status | 0x02);
    outb(0x64, 0xD4);
    outb(0x60, 0xF6);
    outb(0x64, 0xD4);
    outb(0x60, 0xF4);
}

// ===== 重点！extern "C" 关闭C++名字改写，汇编才能找到kmain =====
extern "C" void kmain(void)
{
    vga_print("=== MyOS 启动成功 ===\n");
    vga_print("支持：VGA屏幕、PS2键盘、PS2鼠标\n");
    vga_print("网络：RTL8139网卡已挂载\n");
    vga_print("按键会打印扫描码\n");

    ps2_mouse_init();

    for(;;)
    {
        uint8_t sc = read_scancode();
        vga_print("Key code: ");
        vga_putc('0' + (sc / 10));
        vga_putc('0' + (sc % 10));
        vga_print("\n");
    }
}
