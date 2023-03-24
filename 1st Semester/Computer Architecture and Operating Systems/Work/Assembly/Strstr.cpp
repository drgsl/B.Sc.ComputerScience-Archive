int strstr(char*, char*) {
	_asm {
		mov ebx, [ebp + 8]
		mov ecx, [ebp + 12]

		mov esi, 0
		while_1:
			cmp [ebx + 1 * esi], 0
			je return_f

			push esi

			mov edi, 0
			while_2:
				cmp [ecx + 1 * edi], 0
				je continue_
				mov al, [ebx + 1 * esi]
				cmp al, [ecx + 1 * edi]
				jne continue_
				inc esi
				inc edi
				jmp while_2

			continue_:

			pop esi

			cmp [ecx + 1 * edi], 0
			je return_t;

			inc esi
			jmp while_1

		return_f:
			mov eax, -1
			jmp return_

		return_t:
			mov eax, esi

		return_:

	}
}
