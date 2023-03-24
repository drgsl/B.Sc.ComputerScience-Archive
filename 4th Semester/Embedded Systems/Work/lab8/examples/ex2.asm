; This program very simply echoes the
; switches on P2 to the LEDs on P1.

; When a switch is closed a logic 0 appears
; on that P2 pin, which is then copied to
; that P1 bit which turns on that LED.
; Therefore, a closed switch is seen as a lit
; LED and vice versa.

start:
	MOV P1, P2	; move data on P2 pins to P1
	JMP start	; and repeat