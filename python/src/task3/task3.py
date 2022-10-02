# %%
from scipy import integrate
from math import pow, isclose
from numpy import linspace, vectorize, ndarray
from numpy import array as np_array

# %%
from typing import Final
lhs: Final[float] = 0.0
rhs: Final[float] = 5.0
CONST_REAL_ANSWER: Final[float] = 0.655406852577098
x_dist: Final[ndarray] = linspace(lhs, rhs, 2**20+1)

# %%
f = lambda x: x/((x**4) + (3*x**2) + 2)

# %%
def check_is_close(method, value, CONST_REAL_ANSWER, accur=1e-7):
    return str(accur), isclose(2 * value, CONST_REAL_ANSWER, rel_tol=accur), str(method), value

# %%
methods = {
    'quad': integrate.quad,
    'trapezoid': integrate.trapezoid,
    'simpson': integrate.simpson,
    'romb': integrate.romb,
}

# %%
for acc in [1/x for x in (10**2, 10**9, 10**11, 10**12, 10**13, 10**14, 10**15, 10**16, 10**17, 10**18)]:
    print(check_is_close('quad', methods['quad'](f, lhs, rhs)[0], CONST_REAL_ANSWER, accur=acc))
    print(check_is_close('trapezoid', methods['trapezoid'](vectorize(f)(x_dist), x_dist), CONST_REAL_ANSWER, accur=acc))
    print(check_is_close('simpson', methods['simpson'](vectorize(f)(x_dist), x_dist), CONST_REAL_ANSWER, accur=acc))
    print(check_is_close('romb', methods['romb']((x_dist)), CONST_REAL_ANSWER, accur=acc))


