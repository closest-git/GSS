**GSS --- best CPU/GPU sparse solver for large sparse matrices**

**GSS**(GRUS SPARSE SOLVER) is an adaptive parallel direct solver.
To get solution of sparse linear systems:**Ax=b**, where A is large and sparse,
GSS uses adaptive computing technology, which will run both CPU and GPUs to get more performance.
The high performance and generality of GSS has been verified by many commercial users and many testing sets.

![gss_pardiso](http://www.grusoft.com/wp-content/uploads/2013/11/gss_pardiso.jpg)



**2-3 times faster than PARDISO**

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

 

GSS is an adaptive parallel direct solver to get solution of sparse linear systems
**Ax=b**, where A is large and sparse.

For large matrices, LU factorization takes most computational time. The powerful GPUs bring new possibility for further improvement. But GPU computing technique is very complex and many users have no experience in different computing hardware. So adaptive computing is very important and GSS take it as main target. After divides LU factorization into many parallel tasks, GSS will use adaptive strategy to run these tasks in different hardware (CPU, GPU …). That is, if GPU have high computing power, then it will run more tasks automatically. If CPU is more powerful, then GSS will give it more tasks. And furthermore, if CPU is free (have finished all tasks) and GPU still run a task, then GSS will divide this task to some small tasks then assign some child-task to CPU, then CPU do computing again. So get higher parallel efficiency. GSS will also do some testing to get best parameters for different hardware. In short, GSS is an adaptive black-box solver that hides all complex algorithms on scheduling, synchronization, data transfer and commutation, task assign and refinement… So users just call some simple functions then get extra high performance from GPUs.
