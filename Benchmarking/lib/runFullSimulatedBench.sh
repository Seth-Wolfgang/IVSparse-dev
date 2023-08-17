

#change the line that says #define DENSITY 0.5 to #define DENSITY 0.1 in FullSimulatedBench.cpp

file="FullSimulatedBench.cpp"

#!/bin/bash

# Get the line number of the line with #define DENSITY
line_number=$(grep -n "#define DENSITY" $file | cut -d: -f1)

# Get the current value of DENSITY
old_value=$(sed -n "${line_number}p" $file | cut -d" " -f3)

# Get the new value of DENSITY
new_value=0.01

# Replace the line
sed -i "${line_number}s/#define DENSITY ${old_value}/#define DENSITY ${new_value}/" $file

# Check if the line was replaced successfully
if grep -q "#define DENSITY ${new_value}" $file; then
  g++ -O2 -w -I ~/eigen FullSimulatedBench.cpp -o 1density
else
  echo "The line was not replaced successfully."
fi

# Get the current value of DENSITY
old_value=$(sed -n "${line_number}p" $file | cut -d" " -f3)

# Get the new value of DENSITY
new_value=0.05

# Replace the line
sed -i "${line_number}s/#define DENSITY ${old_value}/#define DENSITY ${new_value}/" $file

# Check if the line was replaced successfully
if grep -q "#define DENSITY ${new_value}" $file; then
  g++ -O2 -w -I ~/eigen FullSimulatedBench.cpp -o 5density
else
  echo "The line was not replaced successfully."
fi

# Get the current value of DENSITY
old_value=$(sed -n "${line_number}p" $file | cut -d" " -f3)

# Get the new value of DENSITY
new_value=0.1

# Replace the line
sed -i "${line_number}s/#define DENSITY ${old_value}/#define DENSITY ${new_value}/" $file

# Check if the line was replaced successfully
if grep -q "#define DENSITY ${new_value}" $file; then
  g++ -O2 -w -I ~/eigen FullSimulatedBench.cpp -o 10density
else
  echo "The line was not replaced successfully."
fi

./1density ;   ./5density ;   ./10density

# rm 1density ;   rm 5density ;   rm 10density

