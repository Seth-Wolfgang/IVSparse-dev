import scipy.io
import matplotlib.pyplot as plt

matrix = scipy.io.mmread('/mnt/c/Users/wolfg/vscodeProjects/Research/diagonal.mtx')
newMatrix = matrix.todense()

#grab the first 50 rows and columns and convert back to scipy
newMatrix = newMatrix[0:400, 0:400]
matrix = scipy.sparse.csr_matrix(newMatrix)

plt.spy(matrix, markersize=0.5)
plt.savefig("G48.pdf")

