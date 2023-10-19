


# make a script that prints every combination of four arrays in a string in the format "1_2_3_4"



formats = ["VCSC", "IVCSC"]
type1 = ["int8t", "uint8t", "int16t", "uint16t", "int32t", "uint32t", "int64t", "uint64t", "float", "double"]

type2 = ["int8t", "uint8t", "int16t", "uint16t", "int32t", "uint32t", "int64t", "uint64t"
]
colMajor = ["true", "false"]


for x in formats:
    for y in type1:
        for z in type2:
            for w in colMajor:
                print("[" + "\"" + x + "_" + y + "_" + z + "_" + w + "\"" + "],")