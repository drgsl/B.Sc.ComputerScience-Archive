int radical(int) {
    _asm{
        
        cmp [ebp + 8], 1
        jle return_dir
        
        mov ebx, [ebp + 8]
        mov esi, 1
        mov ecx, 1
        while_1:
            cmp ecx, ebx
            jg return_t
            mov eax, esi
            mul eax
            mov ecx, eax
            inc esi
            jmp while_1

        return_dir:
            mov eax, [ebp + 8]
            jmp return_

        return_t:
            sub esi, 2
            mov eax, esi

        return_:
           
    }
}
