import csv
from collections import defaultdict

def remove_lines(csv_file, output_file):
    counts = defaultdict(int)
    lines = []

    # Read the CSV file and count the occurrences of the first entry in each line
    with open(csv_file, 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            if row:
                entry = row[0]
                counts[entry] += 1
                lines.append(row)

    # Remove lines where the first entry is not present in exactly 5 separate lines
    filtered_lines = [row for row in lines if counts[row[0]] == 5]

    # Write the filtered lines to the output CSV file
    with open(output_file, 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(filtered_lines)

    print("Lines removed successfully!")


# Example usage
csv_file = 'rawTimeData.csv'  # Replace with the path to your CSV file
output_file = 'rawTimeData2.csv'  # Replace with the desired output file name

remove_lines(csv_file, output_file)

