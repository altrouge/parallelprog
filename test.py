#test.py
# coding: utf-8
import sys

#def generateDoComputation(numproc, size_mat, size_cac, output)
numproc = int(sys.argv[1])
size_mat = int(sys.argv[2])
size_cac = int(sys.argv[3])
output = sys.argv[4]

FILE = open(output,"w\n")
FILE.write("#include <omp.h>\n")
FILE.write("#include \"do_computations.h\"\n")

FILE.write("void do_computations(double** a, double** b, double** c, int Nproc, int size, int matsize)\n")
FILE.write("{\n")
FILE.write("// in this modification, we force the operations to be done on the register (but compilators seems to not)\n")
FILE.write("// really care for the “register” as they automatically take care of that)\n")
FILE.write("register int i;\n")
FILE.write("register int r = matsize/size;\n")
FILE.write("omp_set_num_threads(Nproc);\n")
FILE.write("\n")
FILE.write("// we now start the parallel computing, we will calculate different blocks with the processors.\n")
FILE.write("#pragma omp parallel for\n")
FILE.write("for(i=0;i<r*r; ++i) // size must then di\n")
FILE.write("{\n")

FILE.write("//register double ar[size][size];\n")
FILE.write("//register double br[size][size];\n")

FILE.write("double cr[%d][%d];\n" %(size_cac,size_cac))
for i in range(0,size_cac):
	for j in range(0,size_cac):
		FILE.write("cr[%d][%d] = c[(size*i / r) + %d][(size*i %% r)  + %d];\n" %(i,j,i,j))


FILE.write("int k;\n")
FILE.write("for(k=0;k<matsize;++k)\n")
FILE.write("{\n")
for i in range(0,size_cac):
	for j in range(0,size_cac):
			FILE.write("cr[%d][%d] += a[(size*i / r) + %d][k] * b[k][(size*i %% r) + %d];\n" %(i,j,i,j))
FILE.write("}\n")
for i in range(0,size_cac):
	for j in range(0,size_cac):
		FILE.write("c[(size*i / r) + %d][(size*i %% r)  + %d] = cr[%d][%d];\n" %(i,j,i,j))
FILE.write("}\n")
FILE.write("}\n")
