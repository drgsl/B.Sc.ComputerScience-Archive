struct Struct {
	short lower = 0;
	int upper = 0;
};

void countLowerUpper(char*, Struct*) {
	_asm {
		mov eax, [ebp + 8]
		mov ebx, [ebp + 12]

		mov esi, 0

		while_1:
			cmp [eax + 1 * esi], 0
			je return_t

			cmp [eax + 1 * esi], 'z'
			jle ver_lower
			
			next_ver:

			cmp [eax + 1 * esi], 'A'
			jge ver_upper


			continue_1:

			inc esi
			jmp while_1


		ver_lower:
			cmp [eax + 1 * esi], 'a'
			jl next_ver
			inc [ebx + 0]
			jmp continue_1

		ver_upper:
			cmp [eax + 1 * esi], 'Z'
			jg cont_2
			inc [ebx + 4]
			cont_2:
			jmp continue_1

		return_t:

	}
}
