[bits 32] ; protected mode

section .text:

global interrupt_load_idt
interrupt_load_idt:
    push ebp
    mov ebp,esp
    push eax
    mov eax,[ebp+8]
    lidt [eax]
    pop eax
    pop ebp
    ret

%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
    push    dword 0                     ; push 0 as error code
    push    dword %1                    ; push the interrupt number
    jmp     common_interrupt_handler    ; jump to the common handler
%endmacro

%macro error_code_interrupt_handler 1
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

global null_handler
null_handler:
    iret
  
no_error_code_interrupt_handler 0x20       ; create handler for interrupt 0x20
no_error_code_interrupt_handler 0x21       ; create handler for interrupt 0x21
no_error_code_interrupt_handler 0x22       ; create handler for interrupt 0x22
no_error_code_interrupt_handler 0x23       ; create handler for interrupt 0x23
no_error_code_interrupt_handler 0x24       ; create handler for interrupt 0x24
no_error_code_interrupt_handler 0x25       ; create handler for interrupt 0x25
no_error_code_interrupt_handler 0x26       ; create handler for interrupt 0x26
no_error_code_interrupt_handler 0x27       ; create handler for interrupt 0x27
error_code_interrupt_handler    0x28       ; create handler for interrupt 0x28
no_error_code_interrupt_handler 0x29       ; create handler for interrupt 0x29
error_code_interrupt_handler    0x3A       ; create handler for interrupt 0x30
error_code_interrupt_handler    0x3B       ; create handler for interrupt 0x31
error_code_interrupt_handler    0x3C       ; create handler for interrupt 0x32
error_code_interrupt_handler    0x3D       ; create handler for interrupt 0x33
error_code_interrupt_handler    0x3E       ; create handler for interrupt 0x34
no_error_code_interrupt_handler 0x3F       ; create handler for interrupt 0x35