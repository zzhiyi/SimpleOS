[bits 32] ; protected mode

global interrupt_idt
interrupt_idt: 
  times 256*8 db 0x0

; Pointer argument for lidt
interrupt_idtr: 
  dw 255
  dd interrupt_idt

global interrupt_load_idt
interrupt_load_idt:
    lidt [interrupt_idtr]
    ret

%macro no_error_code_interrupt_handler %1
global interrupt_handler_%1
interrupt_handler_%1:
    push    dword 0                     ; push 0 as error code
    push    dword %1                    ; push the interrupt number
    jmp     common_interrupt_handler    ; jump to the common handler
%endmacro

%macro error_code_interrupt_handler %1
global interrupt_handler_%1
interrupt_handler_%1:
    push    dword %1                    ; push the interrupt number
    jmp     common_interrupt_handler    ; jump to the common handler
%endmacro

[extern interrupt_handler] ; Declate that we will be referencing the external symbol 'interrupt_handler',
common_interrupt_handler:               ; the common parts of the generic interrupt handler
    ; save the registers
    push    esp
    push    ebp
    push    esi
    push    edi
    push    edx
    push    ecx
    push    ebx
    push    eax
    call    interrupt_handler
    pop     eax
    pop     ebx
    pop     ecx
    pop     edx
    pop     edi
    pop     esi
    pop     ebp
    pop     esp
    ; restore the esp
    add     esp, 8
    ; return to the code that got interrupted
    iret
  
no_error_code_interrupt_handler 20       ; create handler for interrupt 20
no_error_code_interrupt_handler 21       ; create handler for interrupt 21
no_error_code_interrupt_handler 22       ; create handler for interrupt 22
no_error_code_interrupt_handler 23       ; create handler for interrupt 23
no_error_code_interrupt_handler 24       ; create handler for interrupt 24
no_error_code_interrupt_handler 25       ; create handler for interrupt 25
no_error_code_interrupt_handler 26       ; create handler for interrupt 26
no_error_code_interrupt_handler 27       ; create handler for interrupt 27
error_code_interrupt_handler    28       ; create handler for interrupt 28
no_error_code_interrupt_handler 29       ; create handler for interrupt 29
error_code_interrupt_handler    30       ; create handler for interrupt 30
error_code_interrupt_handler    31       ; create handler for interrupt 31
error_code_interrupt_handler    32       ; create handler for interrupt 32
error_code_interrupt_handler    33       ; create handler for interrupt 33
error_code_interrupt_handler    34       ; create handler for interrupt 34
no_error_code_interrupt_handler 35       ; create handler for interrupt 35
no_error_code_interrupt_handler 36       ; create handler for interrupt 36
error_code_interrupt_handler    37       ; create handler for interrupt 37