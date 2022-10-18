inverse = lambda x, p: pow(x, p - 2, p)


class EllipticCurve:
    a, b, p = 0, -4, 257
    is_inf = lambda x: x is None
    gen_inf = lambda: None

    @classmethod
    def include(cls, P):
        x, y = P
        return (x ** 3 + cls.a * x + cls.b - y ** 2) % cls.p == 0

    @classmethod
    def add(cls, P, Q):
        if cls.is_inf(P): return Q
        if cls.is_inf(Q): return P
        xp, yp = P
        xq, yq = Q
        if xp == xq:
            if (yp + yq) % cls.p == 0:
                return cls.gen_inf()
            else:
                return cls.double(P)
        else:  # xp != xq
            lamb = ((yq - yp) * inverse((xq - xp) % cls.p, cls.p)) % cls.p
            xr = (lamb ** 2 - xp - xq) % cls.p
            return xr, (lamb * (xp - xr) - yp) % cls.p

    @classmethod
    def double(cls, P):
        if cls.is_inf(P): return
        x, y = P
        if y == 0: return cls.gen_inf()
        lamb = ((3 * (x ** 2)) + cls.a) * inverse((2 * y) % cls.p, cls.p) % cls.p
        xr = (lamb ** 2 - 2 * x) % cls.p
        yr = (lamb * (x - xr) - y) % cls.p
        return xr, yr

    @classmethod
    def smul_a(cls, n: int, P):
        A = cls.gen_inf()
        for i in range(n):
            A = cls.add(A, P)
        return A

    @classmethod
    def smul_d(cls, n: int, P):
        mask = 1 << 9  # mask to get i-th bit of scalar
        A = cls.gen_inf()
        for i in range(9):
            if n & mask != 0:
                A = cls.add(A, P)
            A = cls.double(A)
            mask >>= 1
        if n & mask:
            A = cls.add(A, P)
        return A




def q1():
    Zp_rational_lst = [(x, y) for x in range(257) for y in range(257) if EllipticCurve.include((x, y))]
    print("Number of Zp-rational point on the elliptic curve:", len(Zp_rational_lst))
    print(Zp_rational_lst)
    return

def q2():
    P = (2, 2)
    # method 1
    lst1 = []
    for i in range(2, 301):
        lst1.append(EllipticCurve.smul_a(i, P))

    # method 2
    lst2 = []
    for i in range(2, 301):
        lst2.append(EllipticCurve.smul_d(i, P))

    lst3 = []
    A = P
    for i in range(2, 301):
        A = EllipticCurve.add(A, P)
        lst3.append(A)

    print(lst1 == lst2 == lst3)
    print(lst1)
    return

if __name__ == '__main__':
    q1()
    q2()