import numpy as np


def calculate_b(A, s):
    n, _ = A.shape
    b = []
    for i in range(n):
        element = 0
        for j in range(n):
            element += s[j] * A[i][j]
        b.append(element)
    return b


def qr_householder(A):
    m, n = A.shape
    R = A.copy()
    Q = np.identity(m)
    for k in range(n):
        # Compute the Householder reflection vector
        x = R[k:, k]
        e = np.zeros_like(x)
        e[0] = np.sign(x[0])
        v = np.linalg.norm(x) * e + x
        v = v / np.linalg.norm(v)

        # Apply the Householder reflection to R
        R[k:, :] -= 2 * np.outer(v, v.T @ R[k:, :])

        # Apply the Householder reflection to Q
        Q[:, k:] -= 2 * Q[:, k:] @ np.outer(v, v.T)

    return Q, R


def solve_qr(Q, R, b):
    y = Q.T @ b
    x = np.linalg.solve(R, y)
    return x


def inverse_qr(A):
    Q, R = np.linalg.qr(A)
    n = A.shape[0]
    A_inv = np.zeros((n, n))
    for i in range(n):
        e = np.zeros(n)
        e[i] = 1
        y = Q.T @ e
        x = np.linalg.solve(R, y)
        A_inv[:, i] = x
    return A_inv


def init_values():
    # n = 3
    # eps = 10 ** -16
    # A = np.array([
    #     [1, 2, 3],
    #     [4, 5, 6],
    #     [7, 8, 10]
    # ])
    # A = A.astype('float64')
    # s = np.array([1, 2, 3])
    n = int(np.random.uniform(3, 100))
    eps = 10 ** -16
    A = np.random.uniform(-10, 10, size=(n, n))

    while np.linalg.det(A) == 0:
        A = np.random.uniform(-10, 10, size=(n, n))
    s = np.random.uniform(-10, 10, size=n)
    return n, eps, A, s


if __name__ == "__main__":
    n, eps, A, s = init_values()

    if A.shape[0] != s.shape[0] != n:
        print("Invalid measurements")
        raise Exception
    # 1
    b = calculate_b(A, s)
    print("B = ", b)
    # 2
    Q, R = qr_householder(A)
    Q_real, R_real = np.linalg.qr(A)
    print("Q:\n", Q)
    print("Q Real:\n", Q_real)
    print("R:\n", R)
    print("R Real:\n", R_real)
    # 3
    x_householder = solve_qr(Q, R, b)
    x_qr = solve_qr(Q_real, R_real, b)

    print("\nX_HOUSEHOLDER:", x_householder)
    print("X-qr", x_qr)
    print("Norm: ", np.linalg.norm(x_householder - x_qr))

    # 4
    print("\n\nA*x_householder - b = ", np.linalg.norm(np.dot(A, x_householder) - b))
    print("A*x_qr - b = ", np.linalg.norm(np.dot(A, x_householder) - b))
    print("x_householder -s / s = ", np.linalg.norm(x_householder - s) / np.linalg.norm(s))
    print("x_qr - s / s = ", np.linalg.norm(x_qr - s) / np.linalg.norm(s))

    # 5
    A_householder = inverse_qr(A)
    A_library = np.linalg.inv(A)
    print("\n\nA**-1 householder - A library = ", np.linalg.norm(A_householder - A_library))