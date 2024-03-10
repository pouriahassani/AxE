#include <stdio.h>

void binary_to_hex(FILE *input_file, FILE *output_file) {
    int byte;
    printf("\n reading file");
    byte = fgetc(input_file);
    int i = 1;
    while (byte  != EOF) {
    printf("%d: 0x%02x\n",i,byte);
    
        fprintf(output_file, "0x%02X, ", byte); // Write each byte as a two-digit hexadecimal number
        byte = fgetc(input_file);
        i++;
        
    }
}

int main() {
    const char *input_filename = "/home/eclectx01/Desktop/Codes/AxE/Dev/AxE/soc_frame/sw/programs/telecomm/adpcm/data/small.pcm"; // Path to the binary input file
    const char *output_filename = "output.hex"; // Path to the hexadecimal output file

    // Open the binary input file for reading
    FILE *input_file = fopen(input_filename, "rb");
    if (input_file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Open the output file for writing
    FILE *output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return 1;
    }

    // Convert binary to hexadecimal and write to output file
    binary_to_hex(input_file, output_file);

    // Close the files
    fclose(input_file);
    fclose(output_file);

    printf("Binary file \"%s\" converted to hexadecimal and written to \"%s\".\n", input_filename, output_filename);
    return 0;
}

