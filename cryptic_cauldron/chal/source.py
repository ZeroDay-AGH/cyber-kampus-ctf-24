from Crypto.Util.number import getPrime, bytes_to_long
from sympy import nextprime
from secret import FLAG

p = getPrime(1024)
q = nextprime(p)
N = p * q

e = 65537

phi = (p - 1) * (q - 1)
d = pow(e, -1, phi)
message = bytes_to_long(FLAG)
ciphertext = pow(message, e, N)

with open("output.txt", "w") as f:
    f.write(f"N = {N}\n")
    f.write(f"e = {e}\n")
    f.write(f"ct = {ciphertext}\n")

