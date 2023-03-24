int prim(int n) {
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


		return_F:
			mov eax, 0
			jmp return_

		return_T:
			mov eax, 1
			
		return_:
	}
}
