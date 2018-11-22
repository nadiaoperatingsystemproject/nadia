extern isr_handler, irq_handler
global gdt_up, idt_up, isr_common_int, irq_common_int, asm_irq_ign, asm_isr_def


gdt_up:
   mov eax, [esp+4]  ; recuperer le pointeur de la GDT, passe en parametre.
   lgdt [eax]        ; chargement de la GDT

   mov ax, 0x10      ; 0x10 entree de la GDT, Segment de donnees 
   mov ds, ax        
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov ss, ax
   jmp 0x08:.done   
.done:
   ret

idt_up:
   mov eax, [esp+4]  ; recuperer le pointeur de la IDT, passe en parametre.
   lidt [eax]        ; chargement de la IDT
   ret

; Cette macro sauvegarde les registres du context d'une tache
%macro   SAVE_REGS 0
   pusha
   mov ax, ds
   push eax
   
   mov ax,0x10
   mov ds,ax
   mov es,ax
   mov fs,ax
   mov gs,ax
%endmacro

; Cette macro restaure les registres du context d'une tache
%macro   RESTORE_REGS 0
   pop eax
   mov ds,ax
   mov es,ax
   mov fs,ax
   mov gs,ax
   popa
   add esp, 8
%endmacro

isr_common_int:
   SAVE_REGS
   call isr_handler
   RESTORE_REGS
   sti
   iret

irq_common_int:
   SAVE_REGS
   call irq_handler
   RESTORE_REGS
   sti
   iret

asm_int_ign:
   cli
   push byte 0
   push byte 0x70
   jmp isr_common_int

asm_isr_def:
   cli
   push byte 0
   push byte 0x71
   jmp isr_common_int

;routine d'exception

%macro ISR_HANDLER_NOERRCODE 1  
   [GLOBAL asm_isr_%1]
   asm_isr_%1:
      cli
      push byte 0
      push byte %1
      jmp isr_common_int
%endmacro

%macro ISR_HANDLER_ERRCODE 1
   [GLOBAL asm_isr_%1]
   asm_isr_%1:
      cli
      push byte %1
      jmp isr_common_int
%endmacro

;routine materielle et logicielle(appel systeme) 

%macro IRQ_HANDLER 2  
   [GLOBAL asm_irq_%1]
   asm_irq_%1:
      cli
      push byte 0
      push byte %2
      jmp irq_common_int
%endmacro

; interruption exception

ISR_HANDLER_NOERRCODE 0
ISR_HANDLER_NOERRCODE 1
ISR_HANDLER_NOERRCODE 2
ISR_HANDLER_NOERRCODE 3
ISR_HANDLER_NOERRCODE 4
ISR_HANDLER_NOERRCODE 5
ISR_HANDLER_NOERRCODE 6
ISR_HANDLER_NOERRCODE 7
ISR_HANDLER_ERRCODE 8
ISR_HANDLER_NOERRCODE 9
ISR_HANDLER_ERRCODE 10
ISR_HANDLER_ERRCODE 11
ISR_HANDLER_ERRCODE 12
ISR_HANDLER_ERRCODE 13
ISR_HANDLER_ERRCODE 14
ISR_HANDLER_NOERRCODE 15
ISR_HANDLER_NOERRCODE 16
ISR_HANDLER_NOERRCODE 17
ISR_HANDLER_NOERRCODE 18
ISR_HANDLER_NOERRCODE 19
ISR_HANDLER_NOERRCODE 20
ISR_HANDLER_NOERRCODE 21
ISR_HANDLER_NOERRCODE 22
ISR_HANDLER_NOERRCODE 23
ISR_HANDLER_NOERRCODE 24
ISR_HANDLER_NOERRCODE 25
ISR_HANDLER_NOERRCODE 26
ISR_HANDLER_NOERRCODE 27
ISR_HANDLER_NOERRCODE 28
ISR_HANDLER_NOERRCODE 29
ISR_HANDLER_NOERRCODE 30
ISR_HANDLER_NOERRCODE 31

; interruptions materielles

IRQ_HANDLER 0, 32
IRQ_HANDLER 1, 33
IRQ_HANDLER 2, 34
IRQ_HANDLER 3, 35
IRQ_HANDLER 4, 36
IRQ_HANDLER 5, 37
IRQ_HANDLER 6, 38
IRQ_HANDLER 7, 39
IRQ_HANDLER 8, 40
IRQ_HANDLER 9, 41
IRQ_HANDLER 10, 42
IRQ_HANDLER 11, 43
IRQ_HANDLER 12, 44
IRQ_HANDLER 13, 45
IRQ_HANDLER 14, 46
IRQ_HANDLER 15, 47
IRQ_HANDLER 16, 96