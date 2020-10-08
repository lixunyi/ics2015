#ifndef __REG_H__
#define __REG_H__

#include "common.h"

// 匿名枚举，可以直接引用枚举属性值(全局范围)，这样做的好处是可以自动给他们赋值默认值
//例如下面 R_EAX = 0 R_ECX=1
enum { R_EAX, R_ECX, R_EDX, R_EBX, R_ESP, R_EBP, R_ESI, R_EDI };
enum { R_AX, R_CX, R_DX, R_BX, R_SP, R_BP, R_SI, R_DI };
enum { R_AL, R_CL, R_DL, R_BL, R_AH, R_CH, R_DH, R_BH };

/* TODO: Re-organize the `CPU_state' structure to match the register
 * encoding scheme in i386 instruction format. For example, if we
 * access cpu.gpr[3]._16, we will get the `bx' register; if we access
 * cpu.gpr[1]._8[1], we will get the 'ch' register. Hint: Use `union'.
 * For more details about the register encoding scheme, see i386 manual.
 */

typedef struct {

	    union {
		    uint32_t _32;
		    uint16_t _16;
		    uint8_t _8[2];
	    } gpr[8];

	    /* Do NOT change the order of the GPRs' definitions. */
		//定义一个结构体用来存储 以下通用寄存器的？值
	    struct {
	        uint32_t eax, ecx, edx, ebx, esp, ebp, esi, edi;
	    };

	    //定义一个结构体用来存储 以下通用寄存器的？值
	    struct {
	        uint32_t EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI;
	    };
	    
		swaddr_t eip;

} CPU_state;

//引入 reg.c 中初始化的结构体变量
extern CPU_state cpu;

/*
关键字 inline 告诉编译器，任何地方只要调用内联函数，就直接把该函数的机器码插入到调用它的地方。
这样程序执行更有效率，就好像将内联函数中的语句直接插入到了源代码文件中需要调用该函数的地方一样。

static 修饰函数 表示该函数仅在当前文件有效
 */
static inline int check_reg_index(int index) {
	assert(index >= 0 && index < 8);//如果结果为0 就退出程序
	return index;
}

//定义方便获取指定寄存器属性值的宏
#define reg_l(index) (cpu.gpr[check_reg_index(index)]._32)
#define reg_w(index) (cpu.gpr[check_reg_index(index)]._16)
// index >> 2 表示取 index的高2位 的值，例如 index = {0，2，3} 那么 值均为0
//例如 index = {4，5，6，7} 那么 值均为1
#define reg_b(index) (cpu.gpr[check_reg_index(index) & 0x3]._8[index >> 2])

extern const char* regsl[];
extern const char* regsw[];
extern const char* regsb[];

#endif
