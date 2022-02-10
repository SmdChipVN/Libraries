#define USING_PUSH_POP

  EXTERN RTOS_GetCurrentCPU                     //CPU_TypeDef* RTOS_GetCurrentCPU();
  EXTERN RTOS_GetNextCPU                        //CPU_TypeDef* RTOS_GetNextCPU();

  PUBLIC SVC_Handler  
  PUBLIC RTOS_ASM_Begin                         //void RTOS_ASM_ASM_Begin(CPU_TypeDef* CPU);
  
  SECTION rtos_function:CODE
  SVC_Handler:  
  //PUSH in SP when interrupt
  //Here - R0 - R1 - R2 - R3 - R12 - BACK_LR - BACK_PC - EAPSR
  PUSH          {LR}
  BL            RTOS_GetCurrentCPU
  CMP           R0, #0
  BEQ           BREAK                           //if (NULL): back to current task
  BL            RTOS_ASM_SaveCurrentCPU

  BL            RTOS_GetNextCPU
  CMP           R0, #0
  BEQ           BREAK                           //if (NULL): back to current task
  B             RTOS_ASM_SwitchNextCPU
BREAK:
  POP           {PC}
//===================================
  RTOS_ASM_Begin:                               //R0: CPU_TypeDef* MainCPU
  PUSH          {R1, LR}
  STR           LR , [R0, #28]
  STR           R1 , [R0, #24]
  ADDS          R1 , R0, #24
  MOV           SP , R1
  BL            RTOS_ASM_SaveCurrentCPU  
  POP           {R1, PC}
//===================================
  RTOS_ASM_SaveCurrentCPU:                      //R0: CPU_TypeDef* CurrentCPU
#ifdef USING_PUSH_POP
  MOVS          R1 , SP
  STR           SP , [R0, #(4 * 16)]
  ADDS          R0 , R0, #(4 * 16)
  MOVS          SP , R0
  PUSH          {R4-R11}
  MOVS          SP , R1
#else
  STR           R4 , [R0, #(4 * 8 )]
  STR           R5 , [R0, #(4 * 9 )]
  STR           R6 , [R0, #(4 * 10)]
  STR           R7 , [R0, #(4 * 11)]
  STR           R8 , [R0, #(4 * 12)]
  STR           R9 , [R0, #(4 * 13)]
  STR           R10, [R0, #(4 * 14)]
  STR           R11, [R0, #(4 * 15)]
  STR           SP , [R0, #(4 * 16)]  
#endif
  BX            LR
//===================================
  RTOS_ASM_SwitchNextCPU:                       //R0: CPU_TypeDef* NextCPU
#ifdef USING_PUSH_POP
  ADDS          R1 , R0, #(4 * 8)
  MOVS          SP , R1
  POP           {R4-R11}
  LDR           SP , [R0, #(4 * 16)]
#else
  LDR           R4 , [R0, #(4 * 8 )]
  LDR           R5 , [R0, #(4 * 9 )]
  LDR           R6 , [R0, #(4 * 10)]
  LDR           R7 , [R0, #(4 * 11)]
  LDR           R8 , [R0, #(4 * 12)]
  LDR           R9 , [R0, #(4 * 13)]
  LDR           R10, [R0, #(4 * 14)]
  LDR           R11, [R0, #(4 * 15)]
  LDR           SP , [R0, #(4 * 16)]
#endif
  POP           {PC}  
//===================================

/*
//==============  RTOS function  ==============
void RTOS_InitTask(Task_TypeDef* Task, void(*MainFunction)(), void(*EndFunction)())
{
  Task->CPU.R0 = 0;
  Task->CPU.R1 = 0;
  Task->CPU.R2 = 0;
  Task->CPU.R3 = 0;
  Task->CPU.R4 = 0;
  Task->CPU.R5 = 0;
  Task->CPU.R6 = 0;
  Task->CPU.R7 = 0;
  Task->CPU.R8 = 0;
  Task->CPU.R9 = 0;
  Task->CPU.R10 = 0;
  Task->CPU.R11 = 0;
  Task->CPU.R12 = 0;
  Task->Stack[255] = 0xFFFFFFF9;
  Task->CPU.SP = (unsigned int)(&(Task->Stack[255]));
  Task->CPU.EAPSR = 0x61000000;
  Task->CPU.PC = (unsigned int)MainFunction - 1;
  Task->CPU.LR = (unsigned int)EndFunction;
}
*/

  END