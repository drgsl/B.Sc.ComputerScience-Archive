int strAdd(char*, char*, int) {
	_asm {
		mov eax, [ebp + 8]
		mov ebx, [ebp + 12]

		; calculez in esi indexul de sfarsit al lui s
		mov esi, 0
		while_1:
			cmp [eax + 1 * esi], 0
			je stop_while_1
			inc esi
			jmp while_1

		stop_while_1:

		mov edi, 0
		while_2:
			cmp [ebx + 1 * edi], 0
			je return_t
			cmp esi, [ebp + 16]
			je return_f

			mov cl, [ebx + 1 * edi]
			mov [eax + 1 * esi], cl

			inc edi
			inc esi
			jmp while_2

		return_t:
			mov eax, 1
			jmp return_

		return_f:
			mov eax, 0

		return_:
	}
}
