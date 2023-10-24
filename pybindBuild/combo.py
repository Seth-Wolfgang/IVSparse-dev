


# make a script that prints every combination of four arrays in a string in the format "1_2_3_4"



# formats = ["VCSC", "IVCSC"]
# type1 = ["int8t", "uint8t", "int16t", "uint16t", "int32t", "uint32t", "int64t", "uint64t", "float", "double"]

# type2 = ["uint8t", "uint16t", "uint32t", "uint64t"]
# colMajor = ["Col", "Row"]

# for x in formats:
#     for y in type1:
#         for z in type2:
#             for w in colMajor:
#                 print("\"" + x + "_" + y + "_" + z + "_" + w + "\"")



# print all files located in /home/sethwolfgang/vscode/CSF-Matrix/IVSparse for all files in subdirecto
import os
import sys

path = "/home/sethwolfgang/vscode/CSF-Matrix/IVSparse"
files = []
for root, _, filenames in os.walk(path):
  for filename in filenames:
    files.append(os.path.join(root, filename))

for x in files:
    # remove the prefix /home/sethwolfgang/vscode/CSF-Matrix/
    x = x[37:]
    print("\"" + x + "\",")