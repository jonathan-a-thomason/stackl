#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "machine_def.h"
#include "io_handler.h"
#include "vmem.h"

#define DEFAULT_MEMORY_SIZE  20000

static char *Memory;
static int  Memory_Size = DEFAULT_MEMORY_SIZE;
static FILE *Mem_Log = NULL;
static int Log_Enabled = 0;
//***************************************
static void write_log(int address, int value, char *label)
{
    if (Log_Enabled)
    {
        if (Mem_Log == NULL) Mem_Log = fopen("mem.log", "w");
        fprintf(Mem_Log, "%5d %8d %08X %s\n", address, value, value, label);
    }
}
//***************************************
void VM_Enable_Log(int enabled)
{
    Log_Enabled = enabled;
}
//***************************************
int Mem_Size()
{
    return Memory_Size;
}
//***************************************
static int validate_address(Machine_State *regs, int address, int is_char)
{
    if (address < 0)
    {
        Machine_Check("Invalid address at %d\n", address);
    }

    if ( (address & 0x0003) && !is_char)
    {
        Machine_Check("misaligned address %d\n", address);
        exit(-1);
    }

    if (regs != NULL && (regs->FLAG & FL_USER_MODE))
    {
        if (address < 0 || (address+WORD_SIZE) > regs->LP - regs->BP)
        {
            Machine_Check("address %d out of bounds\n", address);
            exit(-1);
        } 

        address = regs->BP + address;
    }

    return address;
}
//***************************************
int Get_Word(Machine_State *cpu, int address)
{
    int value;

    address = validate_address(cpu, address, 0);
    if (address < Memory_Size)
        value = *(int *)&Memory[address];
    else
        value = IO_Get_Word(address);

    write_log(address, value, "Get_Word");
    return value;
}
//***************************************
void Set_Word(Machine_State *cpu, int address, int value)
{
    address = validate_address(cpu, address, 0);
    write_log(address, value, "Set_Word");
    if (address < Memory_Size)
        *(int *)&Memory[address] = value;
    else
        IO_Set_Word(address, value);
}
//***************************************
int Get_Byte(Machine_State *cpu, int address)
{
    int value;

    address = validate_address(cpu, address, 1);
    if (address < Memory_Size)
        value = Memory[address];
    else
        value = IO_Get_Byte(address);

    write_log(address, value, "Get_Byte");
    return value;
}
//***************************************
void Set_Byte(Machine_State *cpu, int address, int value)
{
    address = validate_address(cpu, address, 1);
    write_log(address, value, "Set_Byte");
    if (address < Memory_Size)
        Memory[address] = value;
    else
        IO_Set_Byte(address, value);
}
//***************************************
void *Get_Addr(Machine_State *cpu, int address)
{
    //int value = Get_Word(address);
    address = validate_address(cpu, address, 1);
    write_log(address, 0, "Get_Addr");
    return &Memory[address];
}
//***************************************
void Init_Memory(int mem_size)
{
    if (mem_size <= 0) mem_size = DEFAULT_MEMORY_SIZE;
    Memory_Size = mem_size;
    Memory = (char *)malloc(Memory_Size);
    memset(Memory, 0x79, Memory_Size);
}
//***************************************
int Abs_Get_Word(int address)
{
    return Get_Word(NULL, address);
}
//***************************************
void Abs_Set_Word(int address, int value)
{
    return Set_Word(NULL, address, value);
}
//***************************************
int Abs_Get_Byte(int address)
{
    return Get_Byte(NULL, address);
}
//***************************************
void Abs_Set_Byte(int address, int value)
{
    return Set_Byte(NULL, address, value);
}
//***************************************
void *Abs_Get_Addr(int address)
{
    return Get_Addr(NULL, address);
}
