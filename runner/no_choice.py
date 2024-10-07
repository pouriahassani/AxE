import os
import matplotlib.pyplot as plt
from PIL import Image
from collections import defaultdict
# Function to extract the string before "_run_idx" from the filename
def count_lines_in_file(file_path):
    with open(file_path, 'r') as file:
            return sum(1 for line in file)

# Function to count the number of lines in a file
def take_file_avergae(file_path):
    with open(file_path, 'r') as file:
        # Count the lines, assuming each line contains one number
        sum  = 0
        count = 0
        for line in file:
            float_value = float(line.strip()) 
            sum += float_value
            count +=1
    return sum/count

# Directories to iterate over (add your directory paths here)
directories = ["./../AAa/data_AAa", "./../AAb/data_AAb", "./../AAe/data_AAe"]
# directories =  ["./../AAb/data_AAb"]
# Dictionary to store the value and the corresponding line counts
data_0 = {}
data_1 = {}


# Set up a color map for each directory
color_map = ['y', 'g', 'b', 'r']
marks = ['1','D','o','D']
labels = ["FAxE AA-a","FAxE AA-b","FAxE AA-e","ExE EH-RA"]
# Create a single plot for all data
plt.figure(figsize=(10, 6))

# Loop through each directory
for directory in directories:
    # Loop through each file in the directory
    data_1 = {}
    if "AAa" in directory:
        la = labels[0]
        j = 0
    if "AAb" in directory:
        la = labels[1]
        j = 1
    if "AAe" in directory:
        la = labels[2]
        j = 2
    for file_name in os.listdir(directory):
        a = 0
        metric = "No choice"
        if "no" in file_name:
            a = 1
        if a==1:
            # Get the full file path
            file_path = os.path.join(directory, file_name)
            # Extract the string before "_run_idx"
            num_lines = count_lines_in_file(file_path)
            # print(values)
            values = file_name.split("_no")
            list = values[0].split("_")
            config = list[0]
            min_range = float((values[0].split("_"))[1])

            # Count the lines in the file (each line is a number)
            key = min_range
            avg_val = num_lines/1000
            data_1[key] = avg_val
    sorted_data = dict(sorted(data_1.items(), key=lambda item: item[0]))
    x_values = []
    y_values = []
    if config == '1':
        for key in sorted_data:
            x_values.append(key)
            y_values.append(sorted_data[key])
        if x_values[-1] < 15:
            z = int((15-x_values[-1])/0.25)
            for k in range(z):
                x_values.append(x_values[-1]+0.25)
                y_values.append(0)
        plt.plot(x_values, y_values, marker=marks[j], color=
                color_map[j % len(color_map)], label=la,markersize=5, linewidth=2)
    # if config == '0':
    #     for key in sorted_data:
    #         x_values.append(key)
    #         y_values.append(sorted_data[key])

    #     plt.plot(x_values, y_values, marker=marks[j], color=
    #             color_map[j % len(color_map)], label=la,markersize=5, linewidth=2)

    # Set up labels, title, and legend
plt.xlabel("min_range", fontdict={'fontsize': 16, 'fontweight': 'bold'})
plt.ylabel("%",
        fontdict={'fontsize': 16, 'fontweight': 'bold'})#,labelpad=50)

plt.xticks(fontsize=14, ha='right')  # Rotate x-axis labels for better readability
plt.yticks(fontsize=14, ha='right')  # Rotate x-axis labels for better readability
plt.legend(loc="best", fontsize=15)  # Add a legend to differentiate datasets
plt.tight_layout()  # Adjust layout to make space for labels
# plt.title("Percent of Partitioning failed due to no available exact node for exact program")
plt.grid(True)
saved_location = "./images/" + "no_choice.pdf"
plt.savefig(saved_location, format='pdf', dpi=300)  # Set DPI to 300 for higher quality

# Show the plot
plt.show()