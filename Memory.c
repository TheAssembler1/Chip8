#include "Memory.h"

void LoadGame(char* file_name) {
	FILE* fp;
	long file_size;

	fp = fopen(file_name, "rb");
	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	rewind(fp);

	fread(memory + PROGRAM_ROM, file_size, 1, fp);
	fclose(fp);
}

void SetupMemory() {
	for (int i = 0; i < MEMORY_SIZE; i++)
		memory[i] = 0;
	for (int i = 0; i < FONT_DATA_SIZE; i++)
		memory[i + FONT_DATA_LOCATION] = font_data[i];
}

void DumpMemory() {
	for (int i = 0; i < MEMORY_SIZE; i++) {
		printf("%X", memory[i]);
	}
	printf("\n");
}