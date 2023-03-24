int EuclideanRecursive(int, int) {
    _asm {
        mov edx, 0
        mov eax, [ebp + 8]
        mov ebx, [ebp + 12]
        div ebx
        mov eax, edx

        cmp eax, 0
        jne return_t
        je return_f

        return_t:
            push eax
            push ebx
            call cmmdc
            add esp, 8

            jmp return_end
        
        return_f:
            mov eax, ebx
            jmp return_end

        return_end:
    }
}
