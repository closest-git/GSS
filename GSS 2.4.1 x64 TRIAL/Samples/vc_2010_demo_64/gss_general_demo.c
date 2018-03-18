/*
	Show the use of the GSS 2.4 to solve sparse matrices.

	The matrices are stored in compressed column storage, which use 5 parameters in GSS as follows:
	int nRow,nCol	
		The numbers of row and column.
	int *ptr, int *ind, double *val 
		where ind stores the row indices of each nonzero, ptr stores the first element position of each column 
		and val vector stores the values of the nonzero elements of the matrix.
	For symmetrical matrices, only lower triangle (include diagonals) are stored.

	For example, for a simple unsymmetrical 3*3 matrix 
		1.0  0.0  5.0
		0.0  3.0  6.0
		2.0  4.0  7.0
   Then
		ptr[4]={0,2,4,7};
		ind[7]={0,2,1,2,0,1,2};
		val[7]={1.0, 2.0, 3.0, 4.0, 5.0,6.0,7.0};

	There are 5 matrix types supported by GSS. 
		0£º		General Matrices
		10:		Structurally Symmetric Matrices
				Support CPU/GPU hybrid computing
		11£º		Positive Definite Symmetric (Hermitian) matrices
				Support CPU/GPU hybrid computing
		12£º	Indefinite Symmetric matrices
		13£º	Complex Symmetric matrices


   Copyright (c) 2005-present by YingShi Chen.    All Rights Reserved. 
   Any problem,contact gsp@grusoft.com	
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grus_sparse_solver.h"

/*
	int nRow	The numbers of row	
	int nCol	The numbers of column.
	int *ptr, int *ind, double *val
		compressed column storage of sparse matrix

	int type	Matrix Type
		0£º		General Matrices
		10:		Structurally Symmetric Matrices
				Support CPU/GPU hybrid computing
		11£º		Positive Definite Symmetric (Hermitian) matrices
				Support CPU/GPU hybrid computing
		12£º	Indefinite Symmetric matrices
		13£º	Complex Symmetric matrices

	int cpu_gpu	CPU computing or CPU_GPU hybrid computing
		0 	Only CPU computing
		5	Hybrid GPU-CPU computing. Only for two matrix type: Structurally Symmetric Matrices(10) and Positive Definite Symmetric matrices(11)

	v0.1	cys
		4/18/2014
*/
void GSS_demo( int nRow,int nCol,int *ptr,int *ind,double *val,double *rhs,int type,int cpu_gpu )	
{
	int l=0,i,j,r,nRet;
	double t_symbolic=0.0,t_solve=0.0,t_numeric=0.0;
	double *x,err=0.0,rhs_norm=0.0,setting[32];
	void *hSolver=NULL;
	clock_t start;

/************* symbolic factorization ******************/
	start = clock();
/************* 32 control parameters to,all the default value is zero.	******************/ 
	for( i = 0; i < 32; i++ )	setting[i]=0.0;
	setting[5]=65791;			//dump infomation
	setting[20] = cpu_gpu;			//Hybrid GPU-CPU computing
	//	setting[23] = 2;			//Set maximum number of iterative-refine step.
	//	setting[24] = 4;			//Set number of  threads
#ifdef _WIN64
		nRet = GSS_init_ld( nRow,nCol,ptr,ind,val,type,setting );
#else
		nRet = GSS_init_id( nRow,nCol,ptr,ind,val,type,setting );
#endif
	if( nRet != 0x0 )	{
		printf( "\tERROR at init GSS solver. ERROR CODE:%d\r\n",nRet );
		return;
	}
#ifdef _WIN64
		hSolver = GSS_symbol_ld( nRow,nCol,ptr,ind,val );	
#else
		hSolver = GSS_symbol_id( nRow,nCol,ptr,ind,val );	
#endif
	t_symbolic = (clock()-start)*1.0/CLOCKS_PER_SEC;
	printf( "\tSymbol Analysis......\tTime=%g\r\n",t_symbolic );
	if( hSolver == NULL )	{
		printf( "\tERROR at SYMBOLIC ANALYSIS.\r\n" );
		goto EXIT;
	}
/************* numerical factorization ******************/
	start = clock( );
#ifdef _WIN64
	nRet = GSS_numeric_ld( nRow,nCol,ptr,ind,val,hSolver );
#else
	nRet = GSS_numeric_id( nRow,nCol,ptr,ind,val,hSolver );
#endif
	t_numeric = (clock()-start)*1.0/CLOCKS_PER_SEC;
	printf( "\r\tNumerical Factorization......\tTime=%g\t\t\r\n",t_numeric );
	if( nRet != 0x0 )	{
		printf( "\r\n\tERROR at NUMERIC FACTORIZATION. ERROR CODE:%d\r\n",nRet );
		hSolver=NULL;		//must set hSolver to NULL
		goto EXIT;		
	}

	x = (double*)calloc( sizeof(double),nCol );
/************* forward/backward substitution ******************/
	for( i = 0; i < nCol; i++ )		{
		x[i] = rhs[i];	rhs_norm+=rhs[i]*rhs[i];
	}
	start = clock();
#ifdef _WIN64
		GSS_solve_ld( hSolver,nRow,nCol,ptr,ind,val,x );
#else
		GSS_solve_id( hSolver,nRow,nCol,ptr,ind,val,x );
#endif	
	t_solve = (clock()-start)*1.0/CLOCKS_PER_SEC;
	printf( "\t\tsolve time=%g\r\n",t_solve );
	rhs_norm =sqrt(rhs_norm);
	err = 0.0;
	for( i = 0; i < nCol; i++ )	{
		for( j = ptr[i]; j < ptr[i+1]; j++ )	{
			r = ind[j];
			rhs[r] -= val[j]*x[i];
			if( (type==11 || type==12) && r!=i )	{
				rhs[i] -= val[j]*x[r];
			}
		}		
	}	
	err = sqrt(err);	
	printf( "\t\tResidual |Ax-b|=%g; |b|=%g\r\n",err,rhs_norm );		
	free( x );
EXIT:
/************* release memory ******************/
	if( hSolver != NULL )
#ifdef _WIN64
		GSS_clear_ld( hSolver );				
#else
		GSS_clear_id( hSolver );				
#endif
}

/*
	solve a simple unsymmetrical 3*3 matrix 
		1.0  0.0  5.0
		0.0  3.0  6.0
		2.0  4.0  7.0

int main( int argc, char* argv[] )
{
	int ptr[4]={0,2,4,7};
	int	ind[7]={0,2,1,2,0,1,2};
	double 	val[7]={1.0, 2.0, 3.0, 4.0, 5.0,6.0,7.0},b[3]={6.0,9.0,13.0};

    GSS_demo(3,3,ptr,ind,val,b,0,5);

	return 0x0;
}*/