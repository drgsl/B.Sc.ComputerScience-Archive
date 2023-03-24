void bubbleSort(int*, int) {
    _asm {
        mov eax, [ebp + 8]
        mov ebx, [ebp + 12]
        dec ebx
        mov esi, 0
        
        for_1:
            cmp esi, ebx
            je return_t


            mov edi, ebx ; n - i - 1
            sub edi, esi

            push esi

            mov esi, edi

            mov edi, 0
            for_2:
                cmp edi, esi
                je stop_for_2
                    
                mov ecx, [eax + edi * 4]
                mov edx, [eax + edi * 4 + 4]

                cmp ecx, edx
                jl continue_1
                mov [eax + edi * 4], edx
                mov [eax + edi * 4 + 4], ecx
              
                continue_1:

                inc edi
                jmp for_2

            
            stop_for_2:

            pop esi

            inc esi
            jmp for_1


        return_t:
            
    }
}
