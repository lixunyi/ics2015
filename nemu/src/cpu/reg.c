#include "nemu.h"
#include <stdlib.h>
#include <time.h>

// 初始化一个cpu结构体
CPU_state cpu;

const char *regsL[] = {"EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"};
const char *regsl[] = {"eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"};
const char *regsw[] = {"ax", "cx", "dx", "bx", "sp", "bp", "si", "di"};
const char *regsb[] = {"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"};

const char *seg_regs[] = {"es", "cs", "ss", "ds", "fs", "gs"}; // R_ES, R_CS, R_SS, R_DS, R_FS, R_GS 

void reg_test() {

#ifndef DEBUG
    return;
#endif

	srand(time(0));//随机数生成器
	uint32_t sample[8];// ??
	uint32_t eip_sample = rand();//随机生存一个32位的无符号正整数
	cpu.eip = eip_sample;

	// 循环给所有寄存器都初始化一个32位的值
	int i;
	for(i = R_EAX; i <= R_EDI; i ++) {
		sample[i] = rand();//创建一个随机的32位的随机数
		reg_l(i) = sample[i];// 将创建的随机数赋值给 指定寄存器容器gpr中的32位存储值
		//截取sample里面的后4位来做对比
		// 因为上面一行代码 将32位随机数给了_32 变量，由于将结构体改成了共用体的关系，会共享内存
		assert(reg_w(i) == (sample[i] & 0xffff));
	}

	assert(reg_b(R_AL) == (sample[R_EAX] & 0xff));
	assert(reg_b(R_AH) == ((sample[R_EAX] >> 8) & 0xff));
	assert(reg_b(R_BL) == (sample[R_EBX] & 0xff));
	assert(reg_b(R_BH) == ((sample[R_EBX] >> 8) & 0xff));
	assert(reg_b(R_CL) == (sample[R_ECX] & 0xff));
	assert(reg_b(R_CH) == ((sample[R_ECX] >> 8) & 0xff));
	assert(reg_b(R_DL) == (sample[R_EDX] & 0xff));
	assert(reg_b(R_DH) == ((sample[R_EDX] >> 8) & 0xff));

	assert(sample[R_EAX] == cpu.eax);
	assert(sample[R_ECX] == cpu.ecx);
	assert(sample[R_EDX] == cpu.edx);
	assert(sample[R_EBX] == cpu.ebx);
	assert(sample[R_ESP] == cpu.esp);
	assert(sample[R_EBP] == cpu.ebp);
	assert(sample[R_ESI] == cpu.esi);
	assert(sample[R_EDI] == cpu.edi);

	
	assert(eip_sample == cpu.eip);
}

