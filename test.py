import PyVSparse
import scipy as sp
import numpy as np


print("hello world")

print(dir(PyVSparse))
print(dir(PyVSparse.VCSC_i_h_2_Row))

scipySparseMat = sp.sparse.random(50, 50, format='csr', dtype = np.int32)

test = PyVSparse.VCSC_i_h_2_Row(scipySparseMat)

test.print()

# assert scipySparseMat.sum() == test.sum()