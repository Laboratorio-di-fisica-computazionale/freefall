import matplotlib.pyplot as plt
import numpy as np

# unpack=True spacchetta automaticamente le colonne nelle variabili
t, y_euler, v_euler, y_exact, v_exact, error_y = np.loadtxt("traiettoria.dat", unpack=True)

# Tracciamento del grafico
plt.figure()
plt.plot(t, y_exact, label="Soluzione esatta")
plt.plot(t, y_euler, "o--", label="Eulero")

plt.xlabel("Tempo (s)")
plt.ylabel("Quota y (m)")
plt.legend()
plt.grid(True)

plt.savefig("plot.png")
