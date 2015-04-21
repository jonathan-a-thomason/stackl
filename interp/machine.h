#pragma once

#define INTERRUPT_VECTOR    0
#define TRAP_VECTOR         1

typedef struct
{
    int BP;         // Base Pointer: base addr for mem
    int LP;         // Limit Pointer: high water mark for mem
    int IP;         // Instructino Pionter
    int SP;         // Stack Pointer
    int FP;         // Frame Pointer
    int FLAG;       // FLAG register (bits defined above)
} Machine_State;

int Get_Word(int address);
void Set_Word(int address, int value);
int Get_Byte(int address);
void Set_Byte(int address, int value);
void *Get_Addr(int addess);

int Is_User_Mode();
int Set_User_Mode(int value);

void Init_Machine();
void Get_Machine_State(Machine_State *cpu);
void Set_Machine_State(Machine_State *cpu);
void Machine_Execute();
void Machine_Check(const char *fmt, ...);
void Machine_Signal_Interrupt();

