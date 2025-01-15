import matplotlib.pyplot as plt

# Dane
num_cities = [47, 64, 70, 124, 170, 323, 443]
times_simulated_annealing = [0.16, 0.32, 0.40, 0.94, 3.77, 27.0, 71.5]
times_genetic_algorithm = [0.89, 1.07, 1.14, 1.48, 2.33, 5.07, 7.09]

# Tworzenie wykresu
plt.figure(figsize=(12, 8))  # Większy rozmiar wykresu

# Wykres dla symulowanego wyżarzania
plt.scatter(num_cities, times_simulated_annealing, color='b', label='Symulowane wyżarzanie', marker='o', s=100)

# Wykres dla algorytmu genetycznego
plt.scatter(num_cities, times_genetic_algorithm, color='r', label='Algorytm genetyczny', marker='s', s=100)

# Oznaczenia osi
plt.xlabel('Liczba miast', fontsize=30)
plt.ylabel('Czas obliczeń [s]', fontsize=30)
plt.title('Zależność czasu obliczeń od liczby miast (skala logarytmiczna)', fontsize=32)

# Zwiększenie rozmiaru ticków na osiach
plt.tick_params(axis='both', which='major', labelsize=22)
plt.tick_params(axis='both', which='minor', labelsize=18)

# Skala logarytmiczna
plt.xscale('log')
plt.yscale('log')

# Siatka i legenda
plt.grid(True, linestyle='--', linewidth=0.8, alpha=0.7)
plt.legend(fontsize=30)

# Wyświetlanie wykresu
plt.tight_layout()
plt.show()
