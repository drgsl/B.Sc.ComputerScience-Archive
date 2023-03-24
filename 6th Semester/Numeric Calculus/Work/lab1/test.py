
import numpy as np

def split(array, nrows, ncols):
    """Split a matrix into sub-matrices."""

    r, h = array.shape
    return (array.reshape(h//nrows, nrows, -1, ncols)
                 .swapaxes(1, 2)
                 .reshape(-1, nrows, ncols))
                 
array = np.array([
    [1, 1, 2, 2],
    [3, 3, 4, 4],
    [5, 5, 6, 6],
    [7, 7, 8, 8]])

A, B, C, D =  split(array, 2, 2)
# A = 
# [[1 1]
#  [3 3]]

# B = 
# [[2 2]
#  [4 4]]

# C = 
# [[5 5]
#  [7 7]]

# D =
# [[6 6]
#  [8 8]]
print('A = \n{}\n\n'
      'B = \n{}\n\n'
      'C = \n{}\n\n'
      'D =\n{}'.format(A, B, C, D))


      