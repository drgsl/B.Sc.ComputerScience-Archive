// the maximum value in an array
int maxVect(int*, int) {
    _asm {
        mov eax, [ebp + 8]
        mov ebx, [ebp + 12]
        mov ecx, -2000000000
        mov esi, 0

        while_1:
            cmp esi, ebx
            je return_t
            cmp [eax + esi * 4], ecx
            jle continue_1
            mov ecx, [eax + esi * 4]
               
            continue_1:
            inc esi
            jmp while_1

        return_t:
            mov eax, ecx
    }
}
