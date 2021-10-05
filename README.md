<!--
 * @Author: Yingshi Chen
 * 
 * @Date: 2021-10-05 15:54:55
 * @
# Description: 
-->
## GSS --- Fast CPU/GPU sparse solver for large sparse matrices on Q-Learning Scheduler

**GSS**(GRUS SPARSE SOLVER) is an adaptive parallel direct solver.
To get solution of sparse linear systems:**Ax=b**, where A is large and sparse,
GSS uses adaptive computing technology, which will run both CPU and GPUs to get more performance.
The high performance and generality of GSS has been verified by many commercial users and many testing sets.

![gss_pardiso](http://www.grusoft.com/wp-content/uploads/2013/11/gss_pardiso.jpg)



## `2-3 times faster than PARDISO`

For many large matrices, GSS is about 2-3 times faster than PARDISO and other CPU based solvers.

**CPU-GPU hybrid computing**

GSS is the first sparse solver that supports NVidia CUDA technology.
Novel algorithm to run CPU and GPU simultaneously.

**Robust**

Handle matrices with high condition number or strange patterns. Some ill-conditioned matrices only can be solved by GSS.

**Easy to use**

32 parameters with default value. Detailed documents and demo  codes. Supports user defined module.

### C Demo

Some samples in the directory "`GSS 2.4.1 x64 TRIAL\Samples\C`".

### Fortran Demo

Some samples in the directory "```GSS 2.4.1 x64 TRIAL\Samples\Fortran```"

### [User Guide](https://github.com/closest-git/GSS/blob/master/GSS%202.4.1%20x64%20TRIAL/doc/GSS%202.4%20quick%20start%20user%20guide.pdf)


### Citation

If you find this code useful, please consider citing:

```
Chen, Yingshi. "Learning the Markov Decision Process in the Sparse Gaussian Elimination." arXiv preprint arXiv:2109.14929 (2021).
```