int sumVect(int*, int) {
    _asm {
        mov eax, [ebp + 8]
        mov ebx, [ebp + 12]
        mov ecx, 0
        mov esi, 0

        while_1:
            cmp esi, ebx
            je return_t
            add ecx, [eax + 4 * esi]
            inc esi
            jmp while_1

        return_t:
            mov eax, ecx
        
    }
}
