# %%
import numpy as np
from scipy import integrate
from matplotlib import pyplot as plt

# %% [markdown]
# # ∫ (xdx) / (x^4 + 3x^2 + 2)
# # от –5 до 5;

# %%
def f_int(x):
    return (x) / (x**4+3*x**2+2)

ans1 = integrate.quad(f_int, -5, 0)[0]
ans2 = integrate.quad(f_int, 0, 5)[0]

integral_res = abs(ans1) + abs(ans2)
integral_res

# %% [markdown]
# # 3y' = 2 - x^2
# # при y(0)=1;

# %%
def f(y, x):
    return (2 - x**2) / 3
y0 = 1

# %%
xi = np.linspace(0, 1, 1000)
scipy_sol = integrate.odeint(f, y0, xi)

# %%
def real_f(x):
    return -1 * x**3 / 9 + 2 * x / 3 + 1

real_sol = real_f(xi)
plt.plot(xi, real_sol,
            linestyle='-.',
            color='blue',
            linewidth=1,
            markersize=3.0,
            label='real solution')

plt.plot(xi, scipy_sol,
            linestyle='--',
            color='red',
            linewidth=1,
            markersize=3.0,
            label='scipy solution')

plt.title('ODE solution')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.show()