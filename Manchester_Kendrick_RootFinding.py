# -*- coding: utf-8 -*-
"""
Created on Sun Nov 10 21:13:10 2024

@author: kmanc
"""
import numpy as np
import matplotlib.pyplot as plt


# Define the Secant Method function with tracking of iteration points
def ManchesterSecant(func, x0, x1, tol=1e-7, max_iter=30):
    x_values = [x0, x1]  # Track x values for plotting
    for i in range(max_iter):
        if abs(func(x1) - func(x0)) < tol:
            print("Divide by zero error in Secant Method.")
            return None
        x2 = x1 - func(x1) * (x1 - x0) / (func(x1) - func(x0))
        x_values.append(x2)  # Add current x2 to the tracking list
        if abs(x2 - x1) < tol:
            return x2, func(x2), i, x_values  # Return x values for plotting
        x0, x1 = x1, x2
    return x1, func(x1), max_iter, x_values  # Return x values for plotting

# Define the functions for Secant Method
def func1(x):
    return -x**3 + 2*x + 2

def func2(x):
    return np.exp(x) + x - 7

def func3(x):
    return np.exp(x) + np.cos(x) - 4

# Define initial guesses for the Secant Method
x0 = 1.0
x1 = 2.0

# Call ManchesterSecant with one of the functions (e.g., func1)
(xsoln, fxsoln, ea, n) = ManchesterSecant(func1, x0, x1)

# Print the results
print('The ManchesterSecant Solution is as follows: ')
print('Solution =', xsoln)
print('Function value at solution =', fxsoln)
print('Relative error =', ea)
print('Number of iterations = ', len(n))

# Generate a range of x values for plotting
x_vals = np.linspace(-3, 3, 400)

# Plot all three functions on the same graph
plt.plot(x_vals, func1(x_vals), label='func1', color='r')
plt.plot(x_vals, func2(x_vals), label='func2', color='g')
plt.plot(x_vals, func3(x_vals), label='func3', color='b')

# Optionally, plot the iteration points for better visualization
plt.plot(n, [func1(xi) for xi in n], 'ko')

# Add labels and title
plt.xlabel('x')
plt.ylabel('y')
plt.title('Manchester The Secant Method')
plt.legend()

# Show the plot
plt.show()

# Bisection Method with tracking for plotting
def ManchesterNameBisection(func, xl, xu, tol=0.1, max_iter=20):
    if func(xl) * func(xu) > 0:
        print("Initial estimates do not bracket solution")
        return None
    x_values = []  # Track x values for plotting
    xmold = xl
    for i in range(max_iter):
        xr = (xl + xu) / 2
        x_values.append(xr)  # Add midpoint to the list
        ea = abs((xr - xmold) / xr) * 100
        if ea < tol:
            break
        xmold = xr
        if func(xr) * func(xl) > 0:
            xl = xr
        else:
            xu = xr
    return xr, func(xr), ea, x_values  # Return x values for plotting

# False Position Method with tracking for plotting
def ManchesterFalsePosition(func, xl, xu, tol=0.1, max_iter=20):
    x_values = []  # Track x values for plotting
    for i in range(max_iter):
        xr = xu - (func(xu) * (xl - xu)) / (func(xl) - func(xu))
        x_values.append(xr)  # Add xr to the list
        if func(xr) == 0 or abs(func(xr)) < tol:
            break
        elif func(xl) * func(xr) < 0:
            xu = xr
        else:
            xl = xr
    return xr, func(xr), abs(func(xr)), x_values  # Return x values for plotting

# Define the functions for Bisection and False Position Methods
def func4(x):
    return x**3 - 9

def func5(x):
    return 3*x**3 + x**2 - x - 5

def func6(x):
    return np.cos(x)**2 - x + 6

# Initial guesses for Bisection and False Position Methods
xl_bisection = 2.0
xu_bisection = 3.0

xl_false_position = 1.0
xu_false_position = 2.0

# Call Bisection Method with func4
(xsoln_bisection, fxsoln_bisection, ea_bisection, n_bisection) = ManchesterNameBisection(func4, xl_bisection, xu_bisection)

# Call False Position Method with func4
(xsoln_false_position, fxsoln_false_position, ea_false_position, n_false_position) = ManchesterFalsePosition(func4, xl_false_position, xu_false_position)

# Print the results for Bisection and False Position
print('The Manchester Bisection Solution is as follows: ')
print('Solution =', xsoln_bisection)
print('Function value at solution =', fxsoln_bisection)
print('Relative error =', ea_bisection)
print('Number of iterations = ', len(n_bisection))

print('The Manchester False Position Solution is as follows: ')
print('Solution =', xsoln_false_position)
print('Function value at solution =', fxsoln_false_position)
print('Absolute error =', ea_false_position)
print('Number of iterations = ', len(n_false_position))

# Generate a range of x values for plotting the functions
x_vals = np.linspace(-3, 3, 400)

# Plot all three functions and the iteration points on the same graph
plt.plot(x_vals, func4(x_vals), label='func4', color='r')
plt.plot(x_vals, func5(x_vals), label='func5', color='g')
plt.plot(x_vals, func6(x_vals), label='func6', color='b')

# Plot the Bisection method iteration points for func4
plt.plot(n_bisection, [func4(xi) for xi in n_bisection], 'ko')

# Plot the False Position method iteration points for func4
plt.plot(n_false_position, [func4(xi) for xi in n_false_position], 'kx')

# Add labels and title
plt.xlabel('x')
plt.ylabel('y')
plt.title('Manchester False Position and Bisection Method')
plt.legend()

# Show the plot
plt.show()

# Newton's Method with tracking for plotting
def ManchesterNewton(func, dfunc, x0, tol=1e-7, max_iter=30):
    x_values = [x0]  # Track x values for plotting
    for i in range(max_iter):
        fx = func(x0)
        dfx = dfunc(x0)
        if abs(dfx) < tol:
            print("Divide by zero error in Newton's Method.")
            return None, None, None, x_values
        x1 = x0 - fx / dfx
        x_values.append(x1)  # Add x1 to the list
        if abs(x1 - x0) < tol:
            ea = abs(x1 - x0) / abs(x1)  # Relative error
            return x1, func(x1), ea, x_values  # Return x values for plotting
        x0 = x1
    return x0, func(x0), max_iter, x_values  # Return x values for plotting

# Define func7 and its derivative for Newton's Method
def func7(x):
    return 7 * np.sin(x) * np.exp(-x) - 1

def dfunc7(x):
    return 7 * (np.cos(x) - np.sin(x)) * np.exp(-x)

# Define initial guess for Newton's Method
x0 = 1  # Initial guess

# Call ManchesterNewton with func7 and its derivative
(xsoln, fxsoln, ea, n) = ManchesterNewton(func7, dfunc7, x0)

# Print the results
print('The ManchesterNewton Solution is as follows: ')
print('Solution =', xsoln)
print('Function value at solution =', fxsoln)
print('Relative error =', ea)
print('Number of iterations = ', len(n))

# Optionally, plot the iteration points for better visualization
plt.plot(range(len(n)), n)
plt.xlabel('x')
plt.ylabel('y')
plt.title('Manchester The Newton Method')
plt.show()