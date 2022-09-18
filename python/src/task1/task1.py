# %%
import numpy as np
import random

# %%
def linspace(start, stop, num=50, endpoint=True):
    num = int(num)
    start = start * 1.
    stop = stop * 1.

    if num == 1:
        yield stop
        return
    if endpoint:
        step = (stop - start) / (num - 1)
    else:
        step = (stop - start) / num

    for i in range(num):
        yield start + step * i

def matmult(a,b):
    zip_b = zip(*b)
    zip_b = list(zip_b)
    return [[sum(ele_a*ele_b for ele_a, ele_b in zip(row_a, col_b)) 
             for col_b in zip_b] for row_a in a]

# %%
import time
class Catchtime(object):

    def __init__(self, s):
        self.s = s

    def __enter__(self):
        self.ex = False
        self.t = time.time()
        return self

    def __exit__(self, type, value, traceback):
        self.ex = True
        self.t = time.time() - self.t
    
    def __str__(self):
        if not self.ex:
            diff = time.time() - self.t
        else:
            diff = self.t
        return f'Catchtime for {self.s}: {diff:.8f}'

# %% [markdown]
# # Task1

# %%
def task1_np(size_N):
    a1 = np.linspace(0, 100, size_N)
    a2 = np.linspace(0, 1, size_N)

    return a1 + a2

def task1_pure(size_N):
    a1 = list(linspace(0, 100, size_N))
    a2 = list(linspace(0, 1, size_N))
    
    return [x + y for x,y in zip(a1, a2)]

# %% [markdown]
# # Task2

# %%
def task2_np(m1_size_I, m1_size_J, m2_size_I, m2_size_J, size_N):
    a1 = np.linspace(0, 100, size_N)
    a2 = np.linspace(0, 1, size_N)

    m1 = np.array([np.random.choice(a1, size=m1_size_I, replace=True) for i in range(m1_size_J)])
    m2 = np.array([np.random.choice(a2, size=m2_size_J, replace=True) for i in range(m2_size_I)]).T

    return np.dot(m1, m2)

def task2_pure(m1_size_I, m1_size_J, m2_size_I, m2_size_J, size_N):
    a1 = list(linspace(0, 100, size_N))
    a2 = list(linspace(0, 1, size_N))

    m1 = []
    for m1_J in range(m1_size_J):
        m1.append(list())
        for m1_I in range(m1_size_I):
            m1[m1_J].append(random.choice(a1))
    m2 = []
    for m2_J in range(m2_size_J):
        m2.append(list())
        for m2_I in range(m2_size_I):
            m2[m2_J].append(random.choice(a2))
    return matmult(m1, m2)


# %%
from timeit import default_timer as timer
import numpy as np
import itertools

repeat_Task1 = 1000
size_N = 1000
m1_size_I, m1_size_J, m2_size_I, m2_size_J = (200, 300, 300, 200)

with Catchtime('t1_pure') as t1_pure:
    for _ in range(repeat_Task1):
        task1_pure(size_N)
    print(t1_pure)

with Catchtime('t1_np') as t1_np:
    for _ in range(repeat_Task1):
        task1_np(size_N)
    print(t1_np)

with Catchtime('t2_pure') as t2_pure:
    task2_pure(m1_size_I, m1_size_J, m2_size_I, m2_size_J, size_N)
    print(t2_pure)

with Catchtime('t2_np') as t2_np:
    task2_np(m1_size_I, m1_size_J, m2_size_I, m2_size_J, size_N)
    print(t2_np)


