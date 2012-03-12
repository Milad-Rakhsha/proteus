${PROTEUS_PYTHON} ./config/configure.py \
--useThreads=0 \
--with-pic=1 \
--with-pthread=1 \
--with-clanguage=C \
--with-cc=mpicc \
--with-cxx=mpicxx \
--with-fc=mpif90 \
--with-mpi-compilers=1 \
--with-shared-libraries=1 \
--with-blas-lapack-lib=\[${TACC_MKL_LIB}/libmkl_lapack.so,${TACC_MKL_LIB}/libmkl_intel_lp64.so,${TACC_MKL_LIB}/libmkl_sequential.so,${TACC_MKL_LIB}/libmkl_core.so\] \
--download-cmake=1 \
--download-metis=1 \
--download-parmetis=1 \
--download-blacs=1 \
--download-scalapack=1 \
--download-mumps=1 \
--download-superlu=1 \
--download-superlu_dist=1 \
--download-hypre=1 \
--prefix=${PROTEUS_PREFIX} \
--PETSC_ARCH=${PROTEUS_ARCH} \
--PETSC_DIR=${PROTEUS}/externalPackages/petsc
