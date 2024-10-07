import os
import matplotlib.pyplot as plt
from PIL import Image
# Function to extract the string before "_run_idx" from the filename
def get_value_from_filename(filename):
    # Split by "_run_idx" and return the part before it
    # if "charge" in file_name:

    #     value = filename.split("charge_")[0]
    #     parts = value.split('_')
    #     return [parts[0], float(parts[1]),int(filename.split("charge_")[1])]
    if "_run_idx" in file_name:
        value = filename.split("_run_idx")[0]
        parts = value.split('_')
        return [float(parts[0])]
    # if "_E" in file_name:
    #     values = []
    #     value1 = filename.split("_E")[1]
    #     if "approx" in value1:
    #         values.append("_apprx")
    #         value2 = value1.split("_apprx")
    #         values.append(value2.split("_")[0])
    #         values.append(value2.split("_")[1])
    #         return values
    #     if "_exact" in value1:
    #         values.append("_exact")
    #         value2 = value1.split("_exact")
    #         values.append(value2.split("_")[0])
    #         values.append(value2.split("_")[1])
    #         return values
    # if "_U" in file_name:
    #     values = []
    #     value1 = filename.split("_E")[1]
    #     if "approx" in value1:
    #         values.append("_apprx")
    #         value2 = value1.split("_apprx")
    #         values.append(value2.split("_")[0])
    #         values.append(value2.split("_")[1])
    #         return values
    #     if "_exact" in value1:
    #         values.append("_exact")
    #         value2 = value1.split("_exact")
    #         values.append(value2.split("_")[0])
    #         values.append(value2.split("_")[1])
    #         return values

# Function to count the number of lines in a file
def count_lines_in_file(file_path):
    with open(file_path, 'r') as file:
        # Count the lines, assuming each line contains one number
        return sum(1 for line in file)

# Directories to iterate over (add your directory paths here)
directories = ["./FF","./BF","./WF"]
# directories =  ["./../AAb/data_AAb"]
# Dictionary to store the value and the corresponding line counts
data_0 = {}
data_1 = {}
i = -1

# Set up a color map for each directory
color_map = ['y', 'g', 'b', 'r']
marks = ['1','D','o','D']
labels = ["FF","BF","WF"]
# Create a single plot for all data
plt.figure(figsize=(10, 6))

# Loop through each directory
for directory in directories:
    # Loop through each file in the directory
    data_0 = {}
    data_1 = {}
    i += 1
    if "FF" in directory:
        la = labels[0]
    if "BF" in directory:
        la = labels[1]
    if "WF" in directory:
        la = labels[2]
    for file_name in os.listdir(directory):
        # Check if the file name contains "run_idx"

        if "run_idx" in file_name:
            # Get the full file path
            file_path = os.path.join(directory, file_name)
            # Extract the string before "_run_idx"
            values = get_value_from_filename(file_name)
            config = la
            value = values[0]

            # Count the lines in the file (each line is a number)
            line_count = count_lines_in_file(file_path)

            # Add the value and line count to the dictionary
            if config == '0':
                if value in data_0:
                    data_0[value] += line_count  # Sum counts if value already exists
                else:
                    data_0[value] = line_count

            else :
                if value in data_1:
                    data_1[value] += line_count  # Sum counts if value already exists
                else:
                    data_1[value] = line_count

        # if "_E_" in file_name:
        #             # Get the full file path
        #             file_path = os.path.join(directory, file_name)
        #             # Extract the string before "_run_idx"
        #             values = get_value_from_filename(file_name)
        #             print(values)
        #             config = values[0]
        #             value = values[1]
        #             node = values[2]
        #             # Count the lines in the file (each line is a number)
        #             line_count = count_lines_in_file(file_path)

        #             # Add the value and line count to the dictionary
        #             if config == '0':
        #                 if value in data_0:
        #                     data_0[value] += line_count  # Sum counts if value already exists
        #                 else:
        #                     data_0[value] = line_count

        #             if config == '1':
        #                 if value in data_1:
        #                     data_1[value] += line_count  # Sum counts if value already exists
        #                 else:
        #                     data_1[value] = line_count

        # if "charge" in file_name:
        #             # Get the full file path
        #             file_path = os.path.join(directory, file_name)
        #             # Extract the string before "_run_idx"
        #             values = get_value_from_filename(file_name)
        #             print(values)
        #             config = values[0]
        #             value = values[1]
        #             node = values[2]
        #             # Count the lines in the file (each line is a number)
        #             line_count = count_lines_in_file(file_path)

        #             # Add the value and line count to the dictionary
        #             if config == '0':
        #                 if value in data_0:
        #                     data_0[value] += line_count  # Sum counts if value already exists
        #                 else:
        #                     data_0[value] = line_count

        #             if config == '1':
        #                 if value in data_1:
        #                     data_1[value] += line_count  # Sum counts if value already exists
        #                 else:
        #                     data_1[value] = line_count

    # Plot data for config == '1'
    sorted_data = dict(sorted(data_1.items()))
    x_values = list(sorted_data.keys())
    y_values = list(sorted_data.values())
    y_values = [x / 100 for x in y_values]
    z =  0
    if x_values[0] > 1:
        z = (x_values[0]-1)/0.25
    for izer in range(int(z)):
        y_values.insert(0,0)
        x_values.insert(izer,0.25*izer+1)
    print(x_values)
    print(y_values)
    # Plot the data on the same graph
    plt.plot(x_values, y_values, marker=marks[i], color=
            color_map[i % len(color_map)], label=la,markersize=8, linewidth=4)

    # # Plot data for config == '0' only for the directory "AAb"
    # if "AAb" in directory:
    #     sorted_data = dict(sorted(data_0.items()))
    #     x_values = list(sorted_data.keys())
    #     y_values = list(sorted_data.values())
    #     y_values = [x / 100 for x in y_values]
    #     z = 0
    #     if x_values[0] > 5:
    #         z = (x_values[0]-5)/0.25
    #     for izer in range(int(z)):
    #         y_values.insert(0,0)
    #         x_values.insert(izer,0.25*izer+5)
    #     print(f"EXE:\t {sum(y_values)}")
    #     print(x_values)
    #     # Plot on the same graph
    #     plt.plot(x_values, y_values, color=color_map[3],
    #               linestyle='--', marker='*',label=labels[0],
    #               markersize=10, linewidth=4)

# Set up labels, title, and legend
plt.xlabel("min_range", fontdict={'fontsize': 16, 'fontweight': 'bold'})
plt.ylabel("Average parition success rate %",
           fontdict={'fontsize': 16, 'fontweight': 'bold'})#,labelpad=50)
# plt.title("Count of Elements in Files vs. Value from Filename")
plt.xticks(fontsize=10, ha='right')  # Rotate x-axis labels for better readability
plt.yticks(fontsize=10, ha='right')  # Rotate x-axis labels for better readability
plt.legend(loc="best", fontsize=15)  # Add a legend to differentiate datasets
plt.tight_layout()  # Adjust layout to make space for labels

# Show the plot
# plt.show()
# Save the plot as a PDF
# plt.savefig('./images/Success_rate.pdf', format='pdf', dpi=300)  # Set DPI to 300 for higher quality

# Optionally show the plot
plt.show()
# class MyClass:
#     def __init__(self, node_number, int_config, R):
#         self.data = []  # List of data
#         self.values = []  # List of values
#         self.node_number = node_number  # Node number
#         self.int_config = int_config  # Integer configuration
#         self.R = R  # Floating-point value R

#     def add_data(self, data_item):
#         """Add an item to the data list."""
#         self.data.append(data_item)

#     def add_value(self, value):
#         """Add a value to the values list."""
#         self.values.append(value)

# p= 0

# graph_list = {}
# graph_time = {}
# for directory in directories:
#     # Loop through each file in the directory
#     data_0 = {}
#     data_1 = {}
#     i += 1
#     for file_name in os.listdir(directory):
#         if "charge" in file_name:
#                     p = 0
#                     # Get the full file path
#                     file_path = os.path.join(directory, file_name)
#                     # Extract the string before "_run_idx"
#                     values = get_value_from_filename(file_name)
#                     config = values[0]
#                     value = values[1]
#                     node = values[2]
#                     key_list = [values[0],values[1]]
#                     key = tuple(key_list)
#                     with open(file_path, 'r') as file:
#                         lines = file.readlines()
#                         times = []
#                         values = []
#                         print(len(lines))
#                         for line in lines:
#                             time = []
#                             value = []
#                             line = line.strip()  # Remove any surrounding whitespace
#                             if ';' in line:  # Check if the line contains valid data
#                                 t = line.split(',')
#                                 for tk in t:
#                                     # print(tk)
#                                     c_rm = ']'
#                                     tk = tk.replace(c_rm,'')
#                                     tk = tk.replace('[','')
#                                     tk = tk.replace('\'','')
#                                     tk = tk.replace('"','')
#                                     tk  = tk.split(';')
                                    
#                                     time.append(int(tk[0]))  # Convert time to float for plotting
#                                     value.append(float(tk[1]))  # Convert value to float for plotting
#                             times.append(time)
#                             values.append(value)
 
#                         avg_vals = []
#                         avg_time = []
#                         max_l = 0
#                         for arr in values:
#                             max_l = max(max_l,len(arr))
#                         for t in times:
#                              if(max_l) == len(t):
#                                   avg_time = t

                      
#                         for i in range(max_l):
#                                 tmp = 0
#                                 for arr in values:
#                                      if len(arr) >= max_l:
#                                         tmp += arr[i]
#                                 avg_vals.append(tmp)
#                                 time.append
#                         if key in graph_list:
#                             # If the key exists, sum the new values element-wise with the existing list
#                             graph_list[key] = [x + y for x, y in zip(graph_list[key], avg_vals)]
#                         else:
#                             # If the key doesn't exist, add the new key with the list of values
#                             graph_list[key] = avg_vals
#                         graph_time[key] = avg_time                              
#                         # plt.plot(avg_time,avg_vals)
#                         # plt.show()
                                    
#                                 # print(t)
#                             # if ';' in line:  # Check if the line contains valid data
#                             #     t, v = line.split(';')
#                             #     time.append(float(t))  # Convert time to float for plotting
#                             #     values.append(float(v))  # Convert value to float for plotting
# # print(p)

# i = 0
# for key  in graph_list:
#     i+=1
#     if(key[0] == '0'):
#         SOC = "EXE"
#     else: 
#         SOC = "AXE"
#     plt.plot(graph_time[key],graph_list[key], color=color_map[(i + 1) % len(color_map)], label=f'AAB {SOC} R={key[1]}')


# plt.xlabel("Time")
# plt.ylabel("Charges")
# plt.title("CEnergy of all Batteries")
# plt.xticks(rotation=45, ha='right')  # Rotate x-axis labels for better readability
# plt.legend()  # Add a legend to differentiate datasets
# plt.tight_layout()  # Adjust layout to make space for labels





# plt.show()


