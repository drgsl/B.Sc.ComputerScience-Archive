int fibRecursive(int) {
	_asm {
		mov ebx, [ebp + 8]
		cmp ebx, 0
		je return_t
		cmp ebx, 1
		je return_t

		dec ebx
		push ebx
		call fib
		pop ebx

		dec ebx

		push eax
		push ebx
		call fib
		pop ebx

		pop edx
		add eax, edx
		jmp return_final


		return_t:
			mov eax, 1
	
		return_final:


	}
}
