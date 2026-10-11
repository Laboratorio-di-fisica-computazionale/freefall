import numpy as np
import matplotlib.pyplot as plt


t, y_anal, y_eul = np.loadtxt("freefall.dat", unpack=True)

plt.figure()
plt.plot(t, y_anal, linestyle='-', color='yellow', label='y analitica')
plt.plot(t, y_eul, linestyle='--', color='orange', label='y eulero')


plt.xlabel(r'$t \ (s)$')
plt.ylabel(r'$y \ (m)$')
plt.title(r'Caduta libera corpo con $Y0=100m$')
plt.legend()

# Salvataggio dell'immagine e chiusura
plt.savefig("freefall.png")
plt.show()
