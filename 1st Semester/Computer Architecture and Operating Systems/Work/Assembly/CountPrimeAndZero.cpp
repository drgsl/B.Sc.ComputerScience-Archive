// counts the numbers witch are prime or equal to zero into a struct
struct Struct {
	int nr_prime = 0;
	int zero = 0;
};

int prim(int) {
	_asm {

		cmp [ebp + 8], 1
		jle return_F

		mov esi, 2

		while_1:
			cmp esi, [ebp + 8]
			je return_t

			mov edx, 0
			mov eax, [ebp + 8]
			div esi
			cmp edx, 0
			je return_F

			inc esi
			jmp while_1

		jmp return_T

		return_F :
			mov eax, 0
			jmp return_

		return_T :
			mov eax, 1

		return_ :
	}
}


int compute(int*, int, Struct*) {
	_asm {
		mov ebx, [ebp + 8]
		mov ecx, [ebp + 16]

		mov esi, 0
		while_1:
			cmp esi, [ebp + 12]
			je return_t

			mov edi, 0
			while_2:
				cmp edi, [ebp + 12]
				je stop_while_2

				mov eax, [ebp + 12]
				mul esi
				add eax, edi

			    mov eax, [ebx + eax * 4]
				cmp eax, 0
				je inc_zero

				push eax
				push ecx

				push eax
				call prim
				add esp, 4

				cmp eax, 1
				je inc_prim
				pop ecx
				add esp, 4

				jump_:

				inc edi
				jmp while_2

				stop_while_2:

			inc esi
			jmp while_1


		inc_prim:
			pop ecx
			add esp, 4
			inc [ecx]
			jmp jump_

		inc_zero:
			inc [ecx + 4]
			jmp jump_

		return_t:
			
	}
}
