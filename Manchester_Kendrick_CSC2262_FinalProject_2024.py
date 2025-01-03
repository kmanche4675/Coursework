# -*- coding: utf-8 -*-
"""
Created on Tue Dec 10 12:19:19 2024

@author: kmanc
"""
import numpy as np
import csv
import matplotlib.pyplot as plt 


def read_csv(file_name):
    t, edr = [], []
    try:
        with open(file_name, 'r') as file:
            reader = csv.reader(file)
            next(reader)  # Skip header
            for row in reader:
                t.append(round(float(row[0]), 2))
                edr.append(float(row[1]))
    except Exception as e:
        print(f"Error reading CSV file: {e}")
    return np.array(t), np.array(edr)

def Manchester_Simpon_Rule(t, edr):
    n = len(t) - 1
    h = (t[-1] - t[0]) / n
    result = edr[0] + edr[-1]
    for i in range(1, n):
        result += (4 * edr[i]) if i % 2 != 0 else (2 * edr[i])
    result *= h / 3
    return result

def Manchester_trapuneq(t, edr):
    integral = 0
    for i in range(len(t) - 1):
        h = t[i + 1] - t[i]
        integral += h * (edr[i] + edr[i + 1]) / 2
    return integral

def fit_cubic_polynomial(t, edr):
    coefficients = np.polyfit(t, edr, 3)
    integral_poly = np.polyint(coefficients)
    integral_value = np.polyval(integral_poly, t[-1]) - np.polyval(integral_poly, t[0])
    return coefficients, integral_value

def cspline(x, y, xx):
    n = len(x)
    if len(y) != n:
        return 'input arrays must be the same length'
    if xx < x[0] or xx > x[n - 1]:
        return 'input value out of range of table'
    h = np.zeros((n - 1))
    for i in range(n - 1):
        h[i] = x[i + 1] - x[i]
    df = np.zeros((n - 1))
    for i in range(n - 1):
        df[i] = (y[i + 1] - y[i]) / h[i]
    e, f, g, const = np.zeros((n)), np.zeros((n)), np.zeros((n)), np.zeros((n))
    f[0], f[n - 1] = 1, 1
    for i in range(1, n - 1):
        e[i], f[i], g[i] = h[i - 1], 2 * (h[i - 1] + h[i]), h[i]
    for i in range(1, n - 1):
        const[i] = 3 * (df[i] - df[i - 1])
    c = np.linalg.solve(np.diag(f) + np.diag(e[1:], k=-1) + np.diag(g[:-1], k=1), const)
    b, d = np.zeros((n - 1)), np.zeros((n - 1))
    for i in range(n - 1):
        b[i] = (y[i + 1] - y[i]) / h[i] - h[i] / 3 * (2 * c[i] + c[i + 1])
        d[i] = (c[i + 1] - c[i]) / (3 * h[i])
    for i in range(n):
        if xx == x[i]:
            return y[i]
        elif x[i] > xx:
            i2 = i - 1
            break
    return y[i2] + b[i2] * (xx - x[i2]) + c[i2] * (xx - x[i2])**2 + d[i2] * (xx - x[i2])**3

def plot_cubic_spline(t, edr, start=0.25, end=5.75):
    xx = np.linspace(t[0], t[-1], 500)
    yy = np.array([cspline(t, edr, x) for x in xx])
    plt.figure(figsize=(10, 6))
    plt.plot(xx, yy, 'k-', label='Manchester Cubic Spline Interpolation')
    plt.scatter(t, edr, color='black', marker='s')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()
    plt.grid(True)
    plt.xlim(start, end)
    plt.show()

def Manchester_Lagrange(t, edr, x_val):
    result = 0
    for i in range(len(t)):
        term = edr[i]
        for j in range(len(t)):
            if i != j:
                term *= (x_val - t[j]) / (t[i] - t[j])
        result += term
    return result

def Manchester_Integration_Trap():
    def func(x):
        return x**3 / (x**4 - 1)**0.5

    a, b, n = 2, 3, 11
    h = (b - a) / n
    result = 0
    for i in range(n):
        x1, x2 = a + i * h, a + (i + 1) * h
        result += h * (func(x1) + func(x2)) / 2
    return result

def main():
    t, edr = read_csv("dataFinalProjectUpdatedS2024.csv")
   
    coefficients, integral_value = fit_cubic_polynomial(t, edr)
    avg_edr = np.mean(edr)

    while True:
        print("\nManchester MENU --------------------------------------------------------")
        print("1 - Manchester Simpson_Rule")
        print("2 - Manchester Trap Unequally Spaced Data")
        print("3 - Manchester Function Integration Method Using Trap")
        print("4 - Manchester Cubic Spline Interpolation")
        print("5 - Manchester Lagrange Polynomial Interpolation")
        print("6- EXIT")
        choice = input("Enter your choice: ")

        if choice == '1':
            print("The Simpson's Rule is", Manchester_Simpon_Rule(t, edr))
        elif choice == '2':
            trap_integral = Manchester_trapuneq(t, edr)
            print("Integral Estimate Using Trap Unequally Spaced Data =", trap_integral)
            print("Cubic fitted polynomial coefficients:")
            print(coefficients)
            print("Integration of cubic polynomial =", round(integral_value, 2))
            print("Average EDR =", round(avg_edr, 3))
            print("Evaluation of cubic polynomial using numpy eval =", np.polyval(coefficients, t[len(t) // 2]))
        
        elif choice == '3':
            print("***************************************")
            print("Manchester's Integration Method Using The Trap Function")
            print("The Trap Rule is", Manchester_Integration_Trap())
        elif choice == '4':
            plot_cubic_spline(t, edr)      
            x_val = t[0]
            print("The Interpolation of an ECG-derived respiration (EDR) rate in mV (millivolt)")
            print("Using Cubic Spline Is", cspline(t, edr, x_val))
        elif choice == '5':
            x_val = t[0]
            print("Lagrange Output is", Manchester_Lagrange(t, edr, x_val))
        elif choice == '6':
            break
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()
