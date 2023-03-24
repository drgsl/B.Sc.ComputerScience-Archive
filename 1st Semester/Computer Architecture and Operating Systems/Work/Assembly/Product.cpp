// the product of two complex numbers
struct complex {
	int re;
	int im;
};

void produs(complex*, complex*, complex*) {
	_asm {
		mov ebx, [ebp + 8]
		mov ecx, [ebp + 12]
		mov esi, [ebp + 16]

		; ac - bd
		mov eax, [ebx]
		mov edx, [ecx]
		mul edx

		push eax

		mov eax, [ebx + 4]
		mov edx, [ecx + 4]
		mul edx

		pop edx
		sub edx, eax
		mov[esi], edx

		; i(ad + cb)

		mov eax, [ebx]
		mov edx, [ecx + 4]
		mul edx

		push eax

		mov eax, [ecx]
		mov edx, [ebx + 4]
		mul edx

		pop edx
		add eax, edx


		mov[esi + 4], eax

		mov eax, 1
		; celebrate
	}
}
