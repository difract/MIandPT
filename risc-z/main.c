#include <stdio.h>
#include "cpu.h"
#include "memory.h"

int main(int argc, const char *argv[])
{
    #ifdef DEBUG
    puts("DEBUG");
    #endif

    #ifdef NDEBUG
    puts("RELEASE");
    #endif

    rz_cpu_p pcpu = rz_create_cpu();
    printf("CPU Info: %s\n", rz_cpu_info(pcpu));

    // load dumps
    FILE *code_file = fopen(argv[1], "rb");

    fread(mem_access(TEXT_OFFSET), 1, TEXT_SIZE, code_file);
    fclose(code_file);

    while(rz_cycle(pcpu));

    rz_free_cpu(pcpu);

    return 0;
}
