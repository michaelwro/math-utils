"""
Print constants.

These print the constants values used in constants.h.

Code By: Michael Wrona
Created: 27 march 2023

"""
import math as m

# pi from https://www.britannica.com/science/pi-mathematics
pi = 3.141592653589793238462643383279502884197

print(f"pi = {pi:0.16f}")
print(f"2pi = {2.0*pi:0.16f}")
print(f"pi/2 = {0.5*pi:0.16f}")
print(f"pi/4 = {0.25*pi:0.16f}")

# WGS84 constants from https://www.unoosa.org/pdf/icg/2012/template/WGS_84.pdf
a = 6378137.0  # [m]
inv_f = 298.257223563

f = 1.0 / inv_f
print(f"f = {f:0.16f}")

ecc2 = 2 * f - f**2
print(f"ecc2 = {ecc2:0.16f}")

ecc = m.sqrt(ecc2)
print(f"ecc = {ecc:0.16f}")

b = a * (1 - f)
print(f"b = {b:0.16f}")  # [m]

radius = (2 * a + b) / 3
print(f"radius = {radius:0.16f}")  # [m]
