import os
import matplotlib.pyplot as plt
from PIL import Image
from collections import defaultdict
import numpy as np
# Function to extract the string before "_run_idx" from the filename
def get_value_from_filename(filename):
    # Split by "_run_idx" and return the part before it
    if "sched" in file_name:
        value = filename.split("_sched")[0]
        parts = value.split('_')
        return [parts[0], float(parts[1])]
  
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
directories = ["./../AAb/EXE_AAb/data_AAb","./../AAa/data_AAa", "./../AAb/AXE_AAb/data_AAb", "./../AAe/data_AAe"]
# directories =  ["./../AAb/data_AAb"]
# Dictionary to store the value and the corresponding line counts
data_0 = {}
data_1 = {}


# Set up a color map for each directory
color_map = ['y', 'g', 'b', 'r']
marks = ['1','D','o','D']
labels = ["FAxE AA-a","FAxE AA-b","FAxE AA-e","ExE EH-RA"]
# Create a single plot for all data
# plt.figure(figsize=(10, 6))
j = -1

X_B_ECAXT = []
Y_B_ECAXT = []
X_B_App = []
Y_B_App = []

X_E_ECAXT = []
Y_E_ECAXT = []
X_E_App = []
Y_E_App = []

type = "exact"
# Loop through each directory
bar_x = [10,10.5,11,11.5,12]
bar_y_aae = []
bar_y_aaa = []
bar_y_aab_e = []
bar_y_aab_a = []
bar_width = 0.1 
fig, ax = plt.subplots() 
i = -2
BAR = []
for directory in directories:
    
    j+=1


    # Loop through each file in the directory
    data_1 = {}
    if "AAa" in directory:
        la = 0
    if "AXE_AAb" in directory:
        la = 1
    if "EXE_AAb" in directory:
        la = 3
    if "AAe" in directory:
        la = 2
    
    for file_name in os.listdir(directory):
        if "sched" in file_name:
            # Get the full file path
            file_path = os.path.join(directory, file_name)
            # Extract the string before "_run_idx"
            values = get_value_from_filename(file_name)
            # print(values)
            config = values[0]
            min_range = values[1]
            # Count the lines in the file (each line is a number)
            key = config
            avg_val = take_file_avergae(file_path)
            xy_pair = [min_range, avg_val]
            if key in data_1:
                data_1[key].append(xy_pair)
            else: 
                data_1[key] = [xy_pair]



    for key in data_1:
        x_values = []
        y_values = []
        sorted_list = sorted(data_1[key], key=lambda item: item[0])

        for List in sorted_list:
            x_values.append(List[0])
            y_values.append(List[1]/1000)
        k = 0
        
        for x in x_values:
            if 10+k*0.5 > 12:
                break
            if x != 10+k*0.5:
                x_values.insert(k,10+k*0.5)
                y_values.insert(k,0)
            k+=1
        i+=1
        x_indices = np.arange(len(x_values))  # Group positions
        # if key == '0':
        #     pass
        #     # plt.plot(x_values, y_values, marker=marks[3], color=
        #     #     color_map[3], label=labels[3],markersize=5, linewidth=2)
        # else:
        print(x_values)
        print(y_values)
        if j == 0:
            bar_y_aab_e = y_values
        else:
            for itr in range(5):
                y_values[itr] = (y_values[itr]-bar_y_aab_e[itr])/bar_y_aab_e[itr]*100
            BAR.append(ax.bar([i*bar_width +x - bar_width for x in x_values], y_values, width=bar_width, label=labels[la], color=color_map[la+1]))

for bars in BAR:
    for bar in bars:
        if bar.get_height() == 0:  # Check if the height (y-value) is zero
            ax.text(bar.get_x() + bar.get_width() / 2, 0.02, '0', ha='center', va='bottom', fontsize=10)




# Set up labels, title, and legend
# Add labels, title, and grid
ax.set_xlabel('min_range',fontdict={'fontsize': 10, 'fontweight': 'bold'})
ax.set_ylabel('Improvement in Battery Lifespan (%)',fontdict={'fontsize': 10, 'fontweight': 'bold'})
# ax.set_title('Comparisiono')
# Change the font size of x-ticks and y-ticks
plt.xticks(fontsize=14)  # Change x-tick font size
plt.yticks(fontsize=14)  # Change y-tick font size
ax.set_xticks(x_values)
ax.set_xticklabels(x_values)
ax.legend()

# # Show the plot
# plt.tight_layout()
# # plt.show()
saved_location = "./images/" + "time_bar" + ".pdf"
plt.savefig(saved_location, format='pdf', dpi=300)  # Set DPI to 300 for higher quality

# Show the plot
plt.show()



