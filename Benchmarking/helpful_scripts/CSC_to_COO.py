import csv

def convert_to_coo(x_data_file, x_indices_file, x_indptr_file, coo_file):
    # Read x_data.csv
    with open(x_data_file, 'r') as file:
        x_data_reader = csv.reader(file)
        x_data = [float(row[0]) for row in x_data_reader]

    # Read x_indices.csv
    with open(x_indices_file, 'r') as file:
        x_indices_reader = csv.reader(file)
        x_indices = [int(row[0]) for row in x_indices_reader]

    # Read x_indptr.csv
    with open(x_indptr_file, 'r') as file:
        x_indptr_reader = csv.reader(file)
        x_indptr = [int(row[0]) for row in x_indptr_reader]

    # Write to COO matrix file
    with open(coo_file, 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(['row', 'col', 'value'])  # Write the header row

        for col, start_idx in enumerate(x_indptr):
            end_idx = x_indptr[col + 1] if col + 1 < len(x_indptr) else len(x_indices)
            for i in range(start_idx, end_idx):
                writer.writerow([i, x_indices[i], x_data[i]])

    print("Conversion completed successfully!")

# Example usage
x_data_file_path = 'X_data.txt'
x_indices_file_path = 'X_indices.txt'
x_indptr_file_path = 'X_indptr.txt'
coo_file_path = 'output.csv'

convert_to_coo(x_data_file_path, x_indices_file_path, x_indptr_file_path, coo_file_path)
