###GSS --- best CPU/GPU sparse solver for large sparse matrices###

**GSS**(GRUS SPARSE SOLVER) is an adaptive parallel direct solver.
To get solution of sparse linear systems:**Ax=b**, where A is large and sparse,
GSS uses adaptive computing technology, which will run both CPU and GPUs to get more performance.
The high performance and generality of GSS has been verified by many commercial users and many testing sets.

![gss_pardiso](http://www.grusoft.com/wp-content/uploads/2013/11/gss_pardiso.jpg)



**==2-3 times faster than PARDISO==**

In most case,1 minute is enough for the numerical factorization of 1000,000 unknowns.
The forward/backward substitution time is in seconds.

**CPU-GPU hybrid computing**

GSS is the first sparse solver that supports NVidia CUDA technology.
Novel algorithm to run CPU and GPU simultaneously.
For large matrices that need long time computing, GSS is about 2-3 times faster than PARDISO and other CPU based solvers.

**Robust**

Handle matrices with high condition number or strange patterns. Some ill-conditioned matrices only can be solved by GSS.

**Easy to use**

32 parameters with default value. Detailed documents and demo  codes. Supports user defined module.



###C Demo###

Some samples in the directory "==GSS 2.4.1 x64 TRIAL\Samples\C==".

###Fortran Demo###

Some samples in the directory "==GSS 2.4.1 x64 TRIAL\Samples\Fortran=="

### [**User Guide**](https://github.com/closest-git/GSS/blob/master/GSS%202.4.1%20x64%20TRIAL/doc/GSS%202.4%20quick%20start%20user%20guide.pdf)