// the function draws the border of a rectangle into a matrix
void DrawRectangle(int*, int width, int height, int left, int top, int right, int bottom) {
	_asm {
		mov ebx, [ebp + 8]

		mov esi, [ebp + 24]
		mov edi, [ebp + 20]

		; ------ top
		while_1:
			cmp edi, [ebp + 28]
			jg stop_while_1

			mov eax, [ebp + 12]
			mul esi
			add eax, edi
			mov [ebx + eax * 4], 1

			inc edi
			jmp while_1


		stop_while_1:

		mov esi, [ebp + 24]
		mov edi, [ebp + 20]

		; ||||| left
		while_2:
			cmp esi, [ebp + 32]
			jl stop_while_2

			mov eax, [ebp + 12]
			mul esi
			add eax, edi
			mov [ebx + eax * 4], 1

			dec esi
			jmp while_2


		stop_while_2:


		; ------ bottom 
		mov esi, [ebp + 32]
		mov edi, [ebp + 28]

		while_3:
			cmp edi, [ebp + 20]
			jl stop_while_3

			mov eax, [ebp + 12]
			mul esi
			add eax, edi
			mov [ebx + eax * 4], 1

			dec edi
			jmp while_3


		stop_while_3:


		; ||||||| right 
		mov esi, [ebp + 32]
		mov edi, [ebp + 28]

		while_4:
			cmp esi, [ebp + 24]
			jg stop_while_4

			mov eax, [ebp + 12]
			mul esi
			add eax, edi
			mov [ebx + eax * 4], 1

			inc esi
			jmp while_4


		stop_while_4:

	}
}
