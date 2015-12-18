class Poly:
    """Polys are polynomials over a single variable, i.e. are of the form
    c0 + c1 x + … + cn x**n, with cn ≠ 0 and n the degree of the polynomial
    """
    # Attribute coeff is the list of coefficients, such that for each
    # non-empty polynomial, coeff[-1] != 0

    def __init__(self):
        """create empty polynomial"""
        self.coeff = []

    def degree(self):
        """return the degree of the polynomial, i.e. the exponent of
        the highest non-zero coefficient"""
        return len(self.coeff)-1

    def __getitem__(self, e):
        """get the coefficient of the term with exponent e >= 0"""
        return self.coeff[e] if e < len(self.coeff) else 0

    def __setitem__(self, e, c):
        """set the coefficient of the term with exponent e to c"""
        # first pad coeff with 0's as necessary
        self.coeff.extend((e+1-len(self.coeff))*[0])
        self.coeff[e] = c # now coeff[e] can be assigned
        # if this set the highest coefficient to 0, shorten coeff
        while len(self.coeff) > 0 and self.coeff[-1] == 0:
            self.coeff.pop()

    def __add__(self, other):
        """add two polynomials; the degree of the resulting polynomial is
        less than or equal to the greater degree of the two polynomials"""
        if len(self.coeff) < len(other.coeff):
            s, l = self.coeff, other.coeff
        else: s, l = other.coeff, self.coeff
        # now s is the shorter list of coefficients, l the longer list
        d = len(l)-1 # new degree is the larger degree
        if d == len(s)-1: # unless the addition leads to trailing zeros
            while d >= 0 and l[d] == -s[d]: d = d-1
        # create new Poly with degree d
        r = Poly()
        r.coeff = [s[i]+l[i] if i < len(s) else l[i] for i in range(d+1)]
        return r

    def __mul__(self, other):
        """multiply two non-empty polynomials; the degree of the resulting
        polynomial is the sum of the degrees of the two polynomials"""
        d = len(self.coeff) + len(other.coeff)
        z = Poly()
        temp = [0 for i in range(d)]
        for x in range(len(self.coeff)):
            for y in range(len(other.coeff)):
                temp[x+y] += self.coeff[x] * other.coeff[y]
        z.coeff = temp
        return z


    def __eq__(self, other):
        return self.coeff == other.coeff

    def __str__(self):
        """print the polynomial or 'Empty Poly'"""
        if self.degree() == -1:
            return 'Empty Poly'
        else:
            # initial s contains the constant term of the polynomial if the constant term is not 0
            s = 'Poly: %s'%(['' if self.coeff[0] == 0 else self.coeff[0]][-1]) 
            for i in range(1, self.degree() + 1):
                coeff = self.coeff[i]
                if coeff != 0:
                    # if coeff is negative, then use the sign of the number
                    # if coeff is position, then use '+'
                    s += '%s%ix**%i'%(['+' if coeff > 0 else ''][-1], coeff, i)
            return s.replace('x**0','').replace('x**1','x')


p = Poly(); print(p)
p.degree()
p[0] = 2; print(p)
p[2] = 5; print(p)
q = Poly(); q[1] = -3; print(q)
p.coeff, q.coeff
r = p+q; print(r)
r[2] = -5; print(r)
s = p+r; print(s)
(p.coeff, q.coeff, r.coeff, s.coeff)
t = p*s; print(t)
