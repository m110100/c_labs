  .syntax unified        /* ARM Unified Assembler Language */
  .arch armv7e-m         /* ARM Cortex-M with DSP extensions */

  .text                  /* Code section (ROM, executable) */
  .thumb                 /* Use Thumb ISA */

  .global _start         /* Expose _start symbol globally */
  .type _start, %function /* Declare _start as a function */
  _start:
    b main               /* Branch to main */

  .thumb_func
  .global main
  .type main, %function
main:
  /* Example function call to strcat_asm:
     r0 contains the address of the destination string.
     r1 contains the address of the source string.
  */

  ldr r0, =buffer      /* Load the address of destination (buffer) into r0 */
  ldr r1, =str1        /* Load the address of source (str1) into r1 */

  bl strcat        /* Call the strcat_asm function */

  @ b stop               /* Infinite loop to stop program */
stop:
  b stop
  .ltorg

  .thumb_func
  .global strcat
  .type strcat, %function
strcat:
  /* Inputs:
     r0 - Address of the destination string (destination)
     r1 - Address of the source string (source)
   */

  /* Store the initial address of the destination in r4 for return */
  mov   r2, r0           /* r4 <- r0 (save destination pointer) */

@ .Lfind_next:
@   ldrb  r3, [r2]     /* Load byte from destination and increment r0 */
@   cbz   r3, .Lcopy_loop
@   adds  r2, #1
@   b     .Lfind_next

  /* Find the end of the destination string */
.Lfind_next:
  ldrb  r3, [r2], #1     /* Load byte from destination and increment r0 */
  cmp   r3, #0
  bne   .Lfind_next
  subs  r2, #1

  /* Copy source string to the destination */
.Lcopy_loop:
  ldrb  r3, [r1], #1    /* Load byte from source and increment r1 */
  strb  r3, [r2], #1    /* Store byte to destination and increment r0 */
  cmp   r3, #0           /* Check if the byte is the null terminator */
  bne   .Lcopy_loop        /* If not, continue copying */
  bx    lr

  .section .rodata       

  .type str1, %object
str1:
  .asciz "STR"         

  .section .data         

pad0:
  .space 8
var0:
  .byte 1, 2, 3, '4'
  .hword 0x0605, 0x0807
  .word 0x87654321
buffer:
  @ .space 16            /* Destination buffer (16 bytes allocated) */
  .asciz "DST"

.end
