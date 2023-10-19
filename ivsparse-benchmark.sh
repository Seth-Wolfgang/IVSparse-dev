#! /bin/bash

# change directory
cd ~/IVSparse-dev/Benchmarking/lib


#for nrows in 1000000 500000000
#for nrows in 10000, 25000, 50000, 100000, 250000, 500000, 1000000, 5000000, 10000000, 50000000, 100000000, 500000000, 1000000000, 10000000000

for density in 10
do
	for nrows in 5000 10000 50000 100000 500000 1000000 5000000 10000000 50000000 100000000 500000000
	do
		resultssuffix="float"
		filename="customized/${resultssuffix}/ivsparse-job-submission-${nrows}-${density}.sh"
		cpfname="customized/${resultssuffix}/simulatedBench_COO_${nrows}_${density}.cpp"
		rm ${cpfname} ${filename}
		cp simulatedBench_COO.cpp ${cpfname} 
		sed -i 's\"../../IVSparse/SparseMatrix"\"../../../IVSparse/SparseMatrix"\' ${cpfname}

		echo "#!/bin/bash" >> ${filename}	
		
		echo "#SBATCH --job-name=${nrows}-${density}" >> ${filename}
		#echo "#SBATCH --partition=bigmem" >> ${filename} 
		echo "#SBATCH -p bigmem" >> ${filename} 
		echo "#SBATCH --nodes=1" >> ${filename}
		echo "#SBATCH --tasks-per-node=1" >> ${filename}
		echo "#SBATCH -o results-${resultssuffix}/output/${nrows}_${density}.out" >> ${filename}
		echo "#SBATCH -e results-${resultssuffix}/output/${nrows}_${density}.err" >> ${filename}
		#echo "#SBATCH --time=2-00:00:00" >> ${filename}
		echo "#SBATCH --time=5-00:00:00" >> ${filename}
		echo "#SBATCH --mail-type=begin" >> ${filename}
		echo "#SBATCH --mail-type=end" >> ${filename}
		echo "#SBATCH --mail-type=fail" >> ${filename}
		echo "#SBATCH --mail-user=carrieer@gvsu.edu" >> ${filename}
		echo "#SBATCH --mem=0" >> ${filename}
		echo "#SBATCH --exclusive" >> ${filename}
		
		echo "source ~/.bashrc" >> ${filename}	
		echo "workon vcsc" >> ${filename}

		echo "srun python mat-gen-mem-calc.py $nrows $density results-${resultssuffix}/${nrows}_${density}_ ${cpfname}" >> ${filename}
		
		echo "rm ${cpfname}" >> ${filename}
		echo "rm ${cpfname%.*}.out" >> ${filename}
		echo "rm ${filename}" >> ${filename}
		
		chmod u+x ${filename}
		#sbatch --job-name=${nrows}-${density} --partition=bigmem --nodes=1 --tasks-per-node=1 --mem=0 --time=10:00 --exclusive -o output/${nrows}_${density}.out -e output/${nrows}_${density}.err --mail-type=end --mail-type=begin --mail-type=fail --mail-user=carrieer@gvsu.edu ./${filename}
		sbatch ./${filename}

	done
done

