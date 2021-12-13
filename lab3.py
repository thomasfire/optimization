class Vector:
    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y

    def length(self):
        return (self.x ** 2 + self.y ** 2) ** 0.5

    def __str__(self):
        return f"({self.x:.3f}, {self.y:.3f})"

    def __neg__(self):
        return Vector(-self.x, -self.y)

    def __mul__(self, v: float):
        return Vector(self.x * v, self.y * v)

    def __add__(self, v):
        return Vector(self.x + v.x, self.y + v.y)

    def __abs__(self):
        return Vector(abs(self.x), abs(self.y))


def func(vector): return vector.x**2 - 2 * vector.x * \
    vector.y**2 + vector.y**4 - vector.y**5


def dfdx(v: Vector):
    return 2*v.x - 2*v.y**2


def dfdy(v: Vector):
    return -5*v.y ** 4 + 4*v.y ** 3 - 4*v.x*v.y


def gradient(v: Vector):
    return Vector(dfdx(v), dfdy(v))


def calculate(v: Vector, step, eps, i=1):
    grad = -gradient(v)
    minV = v + grad * step
    print(f"Gradient is {grad}, Vector is {minV}")
    if i > 30 or abs(func(minV) - func(v)) < eps:
        return (v, i)
    else:
        calculate(minV, step, eps, i+1)


start = Vector(0.5, -0.5)
epsilon = 0.005
step = 0.5
calculate(start, step, epsilon)
