import matplotlib.pyplot as plt
import numpy as np

# Data for plotting
functions = ['fir', 'fir2', 'fir3', 'cfir', 'cfir1', 'cfir2']
signals = ['sinusoidal', 'step', 'random', 'pulse']
fixed_point_data = {
    'fir': [0.062067, 0.062057, 0.062424, 0.062299],
    'fir2': [0.062092, 0.062195, 0.062229, 0.062293],
    'fir3': [0.058134, 0.058153, 0.058264, 0.058324],
    'cfir': [0.069834, 0.069826, 0.069927, 0.069985],
    'cfir1': [0.072011, 0.072210, 0.072012, 0.071994],
    'cfir2': [0.091437, 0.092066, 0.091541, 0.091388]
}
floating_point_data = {
    'fir': [0.064360, 0.064714, 0.064682, 0.064632],
    'fir2': [0.064145, 0.064531, 0.064768, 0.064617],
    'fir3': [0.052343, 0.052683, 0.052832, 0.052796],
    'cfir': [0.064183, 0.064691, 0.064796, 0.064276],
    'cfir1': [0.062948, 0.063287, 0.063225, 0.062685],
    'cfir2': [0.079866, 0.080104, 0.080025, 0.079443]
}

# Number of groups
n_groups = len(signals)

# Create the figure and the axes
fig, ax = plt.subplots(figsize=(15, 8))

# Index for the bar positions
index = np.arange(n_groups)

# Bar width
bar_width = 0.1

# Transparency for the bars
opacity = 0.8
# Adjusting the plot to have function type on the X-axis and making the bars thinner



# Number of function types

n_functions = len(functions)



# New figure and axes

fig, ax = plt.subplots(figsize=(15, 8))



# New index for the bar positions

index = np.arange(n_functions)



# Thinner bar width

bar_width = 0.1



# Choose a colormap
cmap = plt.cm.get_cmap('viridis')  # You can replace 'viridis' with your colormap of choice

# Generate a color for each bar
colors = [cmap(i) for i in np.linspace(0, 1, len(signals) * 2 + 2)]

# Loop through each signal type to plot

for i, text in [(0, "Floating"),(1, "Fixed")]:
    for j, signal in enumerate(signals):

        # Get the values for the signal
        fixed_values = [fixed_point_data[function][j] for function in functions]

        floating_values = [floating_point_data[function][j] for function in functions]
        vals = [floating_values, fixed_values]

        # Plot the bars for fixed point data
        plt.bar(index + bar_width * j + bar_width * i * 4, vals[i], bar_width, alpha=opacity, label=f'{signal} ({text})', color=colors[(j + i * 6)])



# Adding labels and titles

plt.xlabel('Function Type')

plt.ylabel('Mean Execution Time (seconds)')

plt.title('Benchmarking of FIR Functions with Different Signals')

plt.xticks(index + bar_width * len(signals), functions)

plt.legend()

# now set the plot color scheme
plt.rcParams['axes.prop_cycle'] = plt.cycler(color=plt.cm.get_cmap('tab20').colors)


# Show the plot

plt.tight_layout()

plt.show()
