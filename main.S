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

  bl strcat_asm        /* Call the strcat_asm function */

  b stop               /* Infinite loop to stop program */

.thumb_func
.global strcat_asm
.type strcat_asm, %function
strcat_asm:
  /* Inputs:
     r0 - Address of the destination string (destination)
     r1 - Address of the source string (source)
   */

  /* Save r4 and link register to the stack */
  push {r4, lr}        /* Preserve r4 and return address */

  /* Store the initial address of the destination in r4 for return */
  mov r4, r0           /* r4 <- r0 (save destination pointer) */

  /* Find the end of the destination string */
find_end:
  ldrb r2, [r0], #1    /* Load byte from destination and increment r0 */
  cmp r2, #0           /* Check if the byte is the null terminator */
  bne find_end         /* If not, continue searching */
  sub r0, r0, #1       /* Adjust r0 back to the null terminator */

  /* Copy source string to the destination */
copy_loop:
  ldrb r2, [r1], #1    /* Load byte from source and increment r1 */
  strb r2, [r0], #1    /* Store byte to destination and increment r0 */
  cmp r2, #0           /* Check if the byte is the null terminator */
  bne copy_loop        /* If not, continue copying */

  /* Restore r4 and return the destination pointer */
  mov r0, r4           /* r0 <- r4 (return value: destination pointer) */
  pop {r4, pc}         /* Restore r4 and return to the caller */

stop:
  b stop               /* Infinite loop for program termination */

.section .rodata       /* Read-only data section */

.type str1, %object
str1:
  .asciz "STR"         /* Source string */

.section .data         /* Data section (RAM) */

pad0:
  .space 8
var0:
  .byte 1, 2, 3, '4'
  .hword 0x0605, 0x0807
  .word 0x87654321
buffer:
  .space 16            /* Destination buffer (16 bytes allocated) */

.end
