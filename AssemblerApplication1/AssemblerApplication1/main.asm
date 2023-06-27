;
; AssemblerApplication1.asm
;
; Created: 14/04/2023 10:18:51
; Author : aurel
;


; Replace with your application code

start:
    ldi r16,0b00100000
	out DDRB, r16

again:
	ldi r16,0b00100000
	out PORTB, r16

	ldi r16, 0b00000000
	out PORTB, r16

	rjmp again


