import numpy as np

def split(array, nrows, ncols):
    """Split a matrix into sub-matrices."""

    r, h = array.shape
    return (array.reshape(h//nrows, nrows, -1, ncols)
                 .swapaxes(1, 2)
                 .reshape(-1, nrows, ncols))
    # return array[q//2, q//2], array[q//2, q//2],
    # array[q//2, q//2], array[q//2, q//2]




def strassen(a, b, q, qmin):
    if(q == qmin):
        return a*b
    a11, a12, a21, a22 = split(a, 2, 2)
    b11, b12, b21, b22 = split(b, 2, 2)


    p1 = strassen(a11 + a22, b11 + b22, q-1, qmin)
    p2 = strassen(a21 + a22, b11, q-1, qmin)
    p3 = strassen(a11, b12 - b22, q-1, qmin)
    p4 = strassen(a22, b21 - b11, q-1, qmin)
    p5 = strassen(a11 + a12, b22, q-1, qmin)
    p6 = strassen(a21 - a11, b11 + b12, q-1, qmin)
    p7 = strassen(a12 - a22, b21 + b22, q-1, qmin)

    c11 = p1 + p4 - p5 + p7
    c12 = p3 + p5
    c21 = p2+p4
    c22 = p1+p3-p2+p6

    return np.array([
        [c11, c12],
        [c21, c22]
    ])


    




a = np.array([
    [1, 1, 2, 2],
    [3, 3, 4, 4],
    [5, 5, 6, 6],
    [7, 7, 8, 8]])

b = np.array([
    [1, 1, 2, 2],
    [3, 3, 4, 4],
    [5, 5, 6, 6],
    [7, 7, 8, 8]])

print(np.array([[a, b], [a, b]]))

print("A: ", a)
print("A splits: ", split(a, 2, 2))
print("B: ", b)
print("Boring multiplication: ", a * b)

print("Fancy multiplication: ", strassen(a, b, 3, 2))
