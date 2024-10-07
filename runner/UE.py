import os
import matplotlib.pyplot as plt
from PIL import Image
from collections import defaultdict
# Function to extract the string before "_run_idx" from the filename
def get_value_from_filename(filename):
    # Split by "_run_idx" and return the part before it
    if "charge" in file_name:

        value = filename.split("charge_")[0]
        parts = value.split('_')
        return [parts[0], float(parts[1]),int(filename.split("charge_")[1])]
    if "_run_idx" in file_name:
        value = filename.split("_run_idx")[0]
        parts = value.split('_')
        return [parts[0], float(parts[1])]
    if "_E" in file_name:
        values = []
        value1 = filename.split("_E")[0]
        if "apprx" in value1:
            values.append("apprx")
            value2 = value1.split("_apprx")[0]
            values.append(value2.split("_")[0])
            values.append(value2.split("_")[1])
            return values
        if "_exact" in value1:
            values.append("exact")
            value2 = value1.split("_exact")[0]
            values.append(value2.split("_")[0])
            values.append(value2.split("_")[1])
            return values
        if "XE" in value1:
            str = "EXE_" + value1.split("_XE_")[1]
            values.append(str)
            value2 = value1.split("_XE_")[0]
            values.append(value2.split("_")[0])
            values.append(value2.split("_")[1])
            return values
        
    if "_U" in file_name:
        values = []
        value1 = filename.split("_U")[0]
        if "apprx" in value1:
            values.append("apprx")
            value2 = value1.split("_apprx")[0]
            values.append(value2.split("_")[0])
            values.append(value2.split("_")[1])
            return values
        if "_exact" in value1:
            values.append("exact")
            value2 = value1.split("_exact")[0]
            values.append(value2.split("_")[0])
            values.append(value2.split("_")[1])
            return values
        if "XE" in value1:
            str = "EXE_" + value1.split("_XE_")[1]
            values.append(str)
            value2 = value1.split("_XE_")[0]
            values.append(value2.split("_")[0])
            values.append(value2.split("_")[1])
            return values
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
for directory in directories:
    i = -1
    j+=1
    # Loop through each file in the directory
    data_1 = {}
    if "AAa" in directory:
        la = labels[1]
    if "AAb" in directory:
        la = labels[2]
    if "AAe" in directory:
        la = labels[3]
    for file_name in os.listdir(directory):
        a = 0
        metric = "U"
        if "_E" in file_name or "_U" in file_name:
            a = 1
        if a==1:
            if "_E" in file_name:
                continue
            # Get the full file path
            file_path = os.path.join(directory, file_name)
            # Extract the string before "_run_idx"
            values = get_value_from_filename(file_name)
            # print(values)
            config = values[0]
            value = values[1]
            node = values[2]
            if "_E" in file_name:
                values.insert(0,"E")
                metric = "E"
            if "_U" in file_name:
                values.insert(0,"U")
                metric = "U"
            # Count the lines in the file (each line is a number)
            key = tuple(values)
            avg_val = take_file_avergae(file_path)
            if "_E" in file_name:
                avg_val = avg_val/7
            data_1[key] = avg_val

        
            

    grouped_data = defaultdict(list)
    for key, value in data_1.items():
        # Grouping by first two elements of the key
        group_key = key[0:3]
        grouped_data[group_key].append((float(key[3]), value))

    # Sort the data in each group by the x value (key[3])
    for group_key in grouped_data:
        grouped_data[group_key].sort()
    
    # Plotting

    for group_key, values in grouped_data.items():
        i+=1
        x_vals = [item[0] for item in values]  # key[3] as x-axis
        y_vals = [item[1] for item in values]  # dictionary values as y-axis
        if directory == "./../AAb/data_AAb" and "EXE" in group_key[1]:
            # plt.plot(x_vals, y_vals, marker=marks[i], color=
            #     color_map[i % len(color_map)], label=la,markersize=5, linewidth=2)
            # plt.xlabel('min_range')
            # plt.ylabel('Processor Energy Utilization ')
            # plt.title(directory)
            # plt.legend()
            # plt.grid(True)
            continue
        if group_key[1] == "exact":
            la = "Exact_Core" 
            mark = 'g'
        else:
            la = "Approximate_Core"  
            mark = 'r'
        if "AAb" in directory :
            if group_key[1] == "exact":
                X_B_ECAXT = x_vals
                Y_B_ECAXT = y_vals
                type = "exact"
            else:
                X_B_App = x_vals
                Y_B_App = y_vals
                type = "appr"

        if "AAe" in directory :
            if group_key[1] == "exact":
                X_E_ECAXT = x_vals
                Y_E_ECAXT = y_vals
                type = "exact"
            else:
                X_E_App = x_vals
                Y_E_App = y_vals
                type = "appr"

print(Y_B_ECAXT)
plt.plot(X_B_ECAXT, Y_B_ECAXT, marker=marks[i+1], color='g', label="AAb Exact Core",markersize=5, linewidth=2)
plt.plot(X_E_ECAXT, Y_E_ECAXT, marker=marks[i], color='r', label="AAe Exact Core",markersize=5, linewidth=2)

# Set up labels, title, and legend
plt.xlabel("min_range", fontdict={'fontsize': 22, 'fontweight': 'bold'})
plt.ylabel("Processor Utilization",
    fontdict={'fontsize': 22, 'fontweight': 'bold'})#,labelpad=50)
# plt.title("Processor Utilization" )
plt.xticks(fontsize=18, ha='right')  # Rotate x-axis labels for better readability
plt.yticks(fontsize=18, ha='right')  # Rotate x-axis labels for better readability
plt.legend(loc="best", fontsize=15)  # Add a legend to differentiate datasets
plt.tight_layout()  # Adjust layout to make space for labels
plt.grid(True)
saved_location = "./images/" + metric+"_" + "exact"+ ".pdf"
plt.savefig(saved_location, format='pdf', dpi=300)  # Set DPI to 300 for higher quality

# Show the plot
plt.show()
plt.figure(figsize=(10, 6))

plt.plot(X_B_App, Y_B_App, marker=marks[i+1], color='g', label="AAb Approximate Core",markersize=5, linewidth=2)
plt.plot(X_E_App, Y_E_App, marker=marks[i], color='r', label="AAe Approximate Core",markersize=5, linewidth=2)

# Set up labels, title, and legend
plt.xlabel("min_range", fontdict={'fontsize': 22, 'fontweight': 'bold'})
plt.ylabel("Processor Utilization",
    fontdict={'fontsize': 22, 'fontweight': 'bold'})#,labelpad=50)
# plt.title("Processor Utilization" )
plt.xticks(fontsize=18, ha='right')  # Rotate x-axis labels for better readability
plt.yticks(fontsize=18, ha='right')  # Rotate x-axis labels for better readability
plt.legend(loc="best", fontsize=15)  # Add a legend to differentiate datasets
plt.tight_layout()  # Adjust layout to make space for labels
plt.grid(True)
saved_location = "./images/" + metric+"_" + "appr" + ".pdf"
plt.savefig(saved_location, format='pdf', dpi=300)  # Set DPI to 300 for higher quality


plt.show()


