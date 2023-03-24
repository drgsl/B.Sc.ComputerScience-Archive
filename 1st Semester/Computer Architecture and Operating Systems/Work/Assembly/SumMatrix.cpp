int sumMatrix(int*, int) {
    _asm {
        mov ebx, [ebp + 8]
        mov ecx, 0; suma
        mov esi, 0
        mov edi, 0
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
	
                add ecx, [ebx + eax * 4]

                inc edi
                jmp while_2

            stop_while_2:
            inc esi
            jmp while_1

        return_t:
            mov eax, ecx
    }
}
