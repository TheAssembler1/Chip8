#include "Computer.h"

void SetupComputer() {
	for (int i = 0; i < REGISTER_SIZE; i++)
		registers[i] = 0;

	index_register = 0;
	program_counter_register = PROGRAM_ROM;

	for (int i = 0; i < STACK_SIZE; i++)
		stack[i] = 0;

	stack_pointer = 0;

	delay_timer = 0;
	sound_timer = 0;

	opcode = 0;
}

void UpdateTimers() {
	//FIXME::PLAY SOUND WHEN TIMER IS ABOVE WHEN
	if (delay_timer > 0)
		delay_timer--;
	if (sound_timer > 0) {
		PlayBeep();
		sound_timer--;
	}
	else {
		StopBeep();
	}
}

void FetchInstruction() {
	opcode = memory[program_counter_register] << 8 | memory[program_counter_register + 1];
}

void PrintRegisters() {
	for (int i = 0; i < REGISTER_SIZE; i++) {
		printf("REGISTER %d", i); printf(" EQUALS %X\n", registers[i]);
	}
}

void ExecuteInsruction(char* draw_flag) {
	//variables for switch statement
	unsigned short position_x;
	unsigned short position_y;
	unsigned short height;
	unsigned short pixel;
	unsigned char set;
	unsigned char final_x;
	unsigned char final_y;
	unsigned char reg;
	unsigned char value;

	switch (opcode & 0xF000) {
		case 0x0000:
			switch (0x00FF & opcode) {
				case 0x00E0: //CLS
					SetupScreen();
					program_counter_register += 2;
					break;
				case 0x00EE: //RET
					stack_pointer--;
					program_counter_register = stack[stack_pointer];
					program_counter_register += 2;
					break;
				default:
					printf("Opcode doesn't exist! %X\n", opcode);
					exit(-1);
			}
			break;
		case 0x1000: //JP addr
			program_counter_register = 0x0FFF & opcode;
			break;
		case 0x2000: //CALL addr
			stack[stack_pointer] = program_counter_register;
			stack_pointer++;
			program_counter_register = 0x0FFF & opcode;
			break;
		case 0x3000: //SE Vx, byte
			if (registers[(0x0F00 & opcode) >> 8] == (0x00FF & opcode))
				program_counter_register += 2;
			program_counter_register += 2;
			break;
		case 0x4000: //SE Vx, byte
			if (registers[(0x0F00 & opcode) >> 8] != (0x00FF & opcode))
				program_counter_register += 2;
			program_counter_register += 2;
			break;
		case 0x5000: //SE Vx, Vy
			if (registers[(0x0F00 & opcode) >> 8] == registers[(0x00F0 & opcode) >> 4])
				program_counter_register += 2;
			program_counter_register += 2;
			break;
		case 0x6000: //LD, Vx, byte
			registers[(0x0F00 & opcode) >> 8] = 0x00FF & opcode;
			program_counter_register += 2;
			break;
		case 0x7000: //ADD Vx, byte
			registers[(0x0F00 & opcode) >> 8] += 0x00FF & opcode;
			program_counter_register += 2;
			break;
		case 0x8000: 
			switch (0x000F & opcode) {
				case 0x0000: //LD Vx, Vy
					registers[(0x0F00 & opcode) >> 8] = registers[(0x00F0 & opcode) >> 4];
					program_counter_register += 2;
					break;
				case 0x0001: //OR Vx, Vy
					registers[(0x0F00 & opcode) >> 8] |= registers[(0x00F0 & opcode) >> 4];
					program_counter_register += 2;
					break;
				case 0x0002: //AND Vx, Vy
					registers[(0x0F00 & opcode) >> 8] &= registers[(0x00F0 & opcode) >> 4];
					program_counter_register += 2;
					break;
				case 0x0003: //XOR Vx, Vy
					registers[(0x0F00 & opcode) >> 8] ^= registers[(0x00F0 & opcode) >> 4];
					program_counter_register += 2;
					break;
				case 0x0004: //ADD Vx, Vy
					if (registers[(0x0F00 & opcode) >> 8] + registers[(0x00F0 & opcode) >> 4] > 255)
						registers[0xF] = 1;
					else
						registers[0xF] = 0;
					registers[(0x0F00 & opcode) >> 8] += registers[(0x00F0 & opcode) >> 4];
					program_counter_register += 2;
					break;
				case 0x0005: //SUB Vx, Vy
					if (registers[(0x0F00 & opcode) >> 8] > registers[(0x00F0 & opcode) >> 4])
						registers[0xF] = 1;
					else
						registers[0xF] = 0;
					registers[(0x0F00 & opcode) >> 8] -= registers[(0x00F0 & opcode) >> 4];
					program_counter_register += 2;
					break;
				case 0x0006: //SHR Vx {, Vy}
					reg = (0x0F00 & opcode) >> 8;
					registers[0xF] = registers[reg] & 0x1;
					registers[reg] >>= 1;
					program_counter_register += 2;
					break;
				case 0x0007: //SUBN Vx, Vy
					if (registers[(0x00F0 & opcode) >> 4] > registers[(0x0F00 & opcode) >> 8])
						registers[0xF] = 1;
					else
						registers[0xF] = 0;
					registers[(0x0F00 & opcode) >> 8] = registers[(0x00F0 & opcode) >> 4] - registers[(0x0F00 & opcode) >> 8];
					program_counter_register += 2;
					break;
				case 0x000E: //SHL Vx {, Vy}
					reg = (0x0F00 & opcode) >> 8;
					registers[0xF] = (registers[reg] & 0x80) >> 7;
					registers[reg] <<= 1;
					program_counter_register += 2;
					break;
				default:
					printf("Opcode doesn't exist! %X\n", opcode);
					exit(-1);
			}
			break;
		case 0x9000: //SNE Vx, Vy
			if (registers[(0x0F00 & opcode) >> 8] != registers[(0x00F0 & opcode) >> 4])
				program_counter_register += 2;
			program_counter_register += 2;
			break;
		case 0xA000: //LD I, addr
			index_register = 0x0FFF & opcode;
			program_counter_register += 2;
			break;
		case 0xB000: //JP v0, addr
			program_counter_register = registers[0] + (0x0FFF & opcode);
			break;
		case 0xC000:
			registers[(0x0F00 & opcode) >> 8] = GenerateRandByte() & (0x00FF & opcode);
			program_counter_register += 2;
			break;
		case 0xD000: //DRW Vx, Vy nibble
			position_x = registers[(0x0F00 & opcode) >> 8];
			position_y = registers[(0x00F0 & opcode) >> 4];
			height = 0x000F & opcode;

			registers[0xF] = 0;
			for (int yline = 0; yline < height; yline++){
				pixel = memory[index_register + yline];
				for (int xline = 0; xline < 8; xline++){
					if ((pixel & (0x80 >> xline)) != 0){
						final_x = (position_x + xline) % WINDOW_WIDTH_RES;
						final_y = (position_y + yline) % WINDOW_HEIGHT_RES;
						if (screen[(final_y * WINDOW_WIDTH_RES) + final_x])
							registers[0xF] = 1;
						screen[(final_y * WINDOW_WIDTH_RES) + final_x] ^= 1;
					}
				}
			}

			*draw_flag = 1;
			program_counter_register += 2;
			break;
		case 0xE000:
			switch(0x00FF & opcode){
				case 0x009E: //SKP Vx
					if (keys[registers[(0x0F00 & opcode) >> 8]] == 1)
						program_counter_register += 2;
					program_counter_register += 2;
					break;
				case 0x00A1: //SKNP Vx
					if (keys[registers[(0x0F00 & opcode) >> 8]] != 1) {
						program_counter_register += 2;
					}
					program_counter_register += 2;
					break;
				default:
					printf("Opcode doesn't exist! %X\n", opcode);
					exit(-1);
			}
			break;
		case 0xF000: 
			switch (0x00FF & opcode) {
				case 0x0007: //LD Vx, DT
					registers[(0x0F00 & opcode) >> 8] = delay_timer;
					program_counter_register += 2;
					break;
				case 0x000A: //LD Vx, K
					reg = (0x0F00 & opcode) >> 8;
					set = 0;
					for (int i = 0; i < KEY_SIZE; i++) {
						if (keys[i] == 1) {
							set = 1;
							registers[reg] = i;
						}
					}
					if (set != 0)
						program_counter_register += 2;
					break;
				case 0x0015: //LD DT, Vx
					delay_timer = registers[(0x0F00 & opcode) >> 8];
					program_counter_register += 2;
					break;
				case 0x0018: //LD ST, Vx
					sound_timer = registers[(0x0F00 & opcode) >> 8];
					program_counter_register += 2;
					break;
				case 0x001E: //ADD I, Vx
					index_register += registers[(0x0F00 & opcode) >> 8];
					program_counter_register += 2;
					break;
				case 0x0029: //LD F, Vx
					index_register = FONT_DATA_LOCATION + (registers[(0x0F00 & opcode) >> 8] * FONT_CHARACTER_SIZE);
					program_counter_register += 2;
					break;
				case 0x0033: //LD B, Vx
					reg = (0x0F00 & opcode) >> 8;
					value = registers[reg];

					memory[index_register + 2] = value % 10;
					value /= 10;
					memory[index_register + 1] = value % 10;
					value /= 10;
					memory[index_register] = value % 10;

					program_counter_register += 2;
					break;
				case 0x0055: //LD [I], Vx
					reg = (0x0F00 & opcode) >> 8;
					
					for (int i = 0; i <= reg; i++)
						memory[index_register + i] = registers[i];
					program_counter_register += 2;
					break;
				case 0x0065: //LD Vx, [I]
					reg = (0x0F00 & opcode) >> 8;

					for (int i = 0; i <= reg; i++)
						registers[i] = memory[index_register + i];

					program_counter_register += 2;
					break;
				default:
					printf("Opcode doesn't exist! %X\n", opcode);
					exit(-1);
			}
			break;
		default:
			printf("Opcode doesn't exist! %X\n", opcode);
			exit(-1);
	}
}

int GenerateRandByte() {
	return rand() % 255;
}