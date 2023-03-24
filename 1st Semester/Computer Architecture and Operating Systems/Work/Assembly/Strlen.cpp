int strlen(char*) {
    _asm {
        mov eax, [ebp + 8]
        mov esi, 0

        while_1:
            cmp [eax + esi * 1], 0
            je return_t
            inc esi
            jmp while_1

        return_t:
           mov eax, esi

    }
}
