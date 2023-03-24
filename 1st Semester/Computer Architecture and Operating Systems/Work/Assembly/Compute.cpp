// a * b / c
int compute(int, int, int) {
    _asm {

        cmp [ebx + 16], 0
        je return_f

        mov eax, [ebp + 8]
        mov ebx, [ebp + 12]
        mul ebx
        
        mov edx, 0

        div [ebp + 16]

        return_f:
    }
}
