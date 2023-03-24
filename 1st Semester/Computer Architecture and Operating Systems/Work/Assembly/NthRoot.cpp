unsigned int radical(unsigned int, unsigned ord) {
	_asm {
		
		cmp [ebp + 8], 0
		je return_0

		cmp [ebp + 8], 1
		je return_1

		cmp [ebp + 12], 0
		je return_1

		mov ecx, 1

		mov esi, 1
		while_1:
			cmp ecx, [ebp + 8]
			jg return_nr

			mov eax, 1

			mov edi, 1
			while_2:
				cmp edi, [ebp + 12]
				jg stop_while_2

				mul esi

				inc edi
				jmp while_2

			stop_while_2:

			mov ecx, eax

			inc esi
			jmp while_1

		return_nr:
			sub esi, 2
			mov eax, esi
			jmp return_

		return_0:
			mov eax, 0
			jmp return_

		return_1:
			mov eax, 1

		return_:

	}
}
