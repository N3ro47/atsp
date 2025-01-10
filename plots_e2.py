import matplotlib.pyplot as plt

# Dane
num_cities = [47, 64, 70, 124, 170, 323, 443]
times = [0.16, 0.32, 0.40, 0.94, 3.77, 27.0, 71.5]

# Tworzenie wykresu
plt.figure(figsize=(12, 8))  # Większy rozmiar wykresu
plt.plot(num_cities, times, 'o', label='Czas obliczeń', color='b', markersize=10, linewidth=2.0)

# Oznaczenia osi
plt.xlabel('Liczba miast', fontsize=30)
plt.ylabel('Czas obliczeń [s]', fontsize=30)
plt.title('Zależność czasu obliczeń od liczby miast (skala liniowa)', fontsize=32)

# Zwiększenie rozmiaru ticków na osiach
plt.tick_params(axis='both', which='major', labelsize=22)
plt.tick_params(axis='both', which='minor', labelsize=18)

# Siatka i legenda
plt.grid(True, linestyle='--', linewidth=0.8, alpha=0.7)
plt.legend(fontsize=30)

# Wyświetlanie wykresu
plt.tight_layout()
plt.show()
