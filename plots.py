import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

# Data
data = {
    'N': [2, 4, 6, 8, 10, 12, 14, 16, 18],
    'B&B': [0.000000154, 0.000000212, 0.000003440, 0.000058098, 
            0.001270906, 0.023070399, 0.544380185, 4.153794033, 57.614417081],
    'Brute Force': [0.000000129, 0.000000112, 0.000000905, 0.000035848, 
                    0.002245874, 0.267688224, 48.495318664, None, None]
}

# Create DataFrame
df = pd.DataFrame(data)

# Melt DataFrame for Seaborn
df_melted = df.melt(id_vars='N', var_name='Algorithm', value_name='Average Time')

# Set the style
sns.set(style="whitegrid")

# Create the plot
plt.figure(figsize=(12, 6))
sns.scatterplot(data=df_melted, x='N', y='Average Time', hue='Algorithm', style='Algorithm', s=100)
plt.yscale('log')  # Set y-axis to logarithmic scale
plt.xlabel('Number of Cities (N)')
plt.ylabel('Average Time (s, log scale)')
plt.title('Average Execution Times of ATSP Algorithms')
plt.xticks(df['N'])  # Set x ticks to be the values of N
plt.legend(title='Algorithm')
plt.grid(True)

# Save the plot as a PNG file
plt.savefig('atsp_execution_times_log_line.png', dpi=300, bbox_inches='tight')


