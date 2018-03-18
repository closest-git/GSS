/*
	Show the use of the 64-bit GSS to solve Positive Symmetric Definite matrices.

	The matrices are stored in compressed column storage, which use 5 parameters in GSS as follows:
	int nRow,nCol	
		The numbers of row and column¡£
	int *ptr, int *ind, double *val 
		where ind stores the row indices of each nonzero, ptr stores the first element position of each column 
		and val vector stores the values of the nonzero elements of the matrix.
	For symmetrical matrices, only lower triangle (include diagonals) are stored.

	For example, for a simple 3*3 matrix (It's symmetric positive definite).
		1.0  0.0  2.0
		0.0  5.0  3.0
		2.0  3.0  10.0
   Then
		ptr[4]={0,2,4,5};
		ind[5]={0,2,1,2,2};
		val[5]={1.0, 2.0, 5.0, 3.0, 10.0};

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

	int type	always 11 for Positive Definite Symmetric (Hermitian) matrices
	int cpu_gpu	CPU computing or CPU_GPU hybrid computing
		0 	Only CPU computing
		5	Hybrid GPU-CPU computing. Only for two matrix type: Structurally Symmetric Matrices(10) and Positive Definite Symmetric matrices(11)

   Copyright (c) 2005-present by YingShiChen.    All Rights Reserved. 
*/

void GSS_spd_demo_( int nRow,int nCol,int *ptr,int *ind,double *val,double *rhs,int type,int cpu_gpu )	{
	int l=0,i,j,r,nRet;
	double t_symbolic=0.0,t_solve=0.0,t_numeric=0.0;
	double *x,err=0.0,rhs_norm=0.0,setting[32];
	void *hSolver=NULL;
	clock_t start;

/************* symbolic factorization ******************/
/************* 32 control parameters to,all the default value is zero.	******************/ 
	for( i = 0; i < 32; i++ )	setting[i]=0.0;
		setting[5]=65791;			//dump infomation
		setting[20] = cpu_gpu;			//Hybrid GPU-CPU computing
	//	setting[23] = 2;			//Set maximum number of iterative-refine step.
	//	setting[24] = 4;			//Set number of  threads
	start = clock();
	nRet = GSS_init_ld( nRow,nCol,ptr,ind,val,type,setting );
	if( nRet != 0x0 )	{
		printf( "\tERROR at init GSS solver. ERROR CODE:%d\r\n",nRet );
		return;
	}
	hSolver = GSS_symbol_ld( nRow,nCol,ptr,ind,val );	
	t_symbolic = (clock()-start)/CLOCKS_PER_SEC;
	printf( "\tSymbol Analysis......\tTime=%g\r\n",t_symbolic );
	if( hSolver == NULL )	{
		printf( "\tERROR at SYMBOLIC ANALYSIS.\r\n" );
		goto EXIT;
	}
/************* numerical factorization ******************/
	start = clock( );
	nRet = GSS_numeric_ld( nRow,nCol,ptr,ind,val,hSolver );
	if( nRet != 0x0 )	{
		printf( "\r\n\tERROR at NUMERIC FACTORIZATION. ERROR CODE:%d\r\n",nRet );
		hSolver=NULL;		//must set hSolver to NULL
		goto EXIT;		
	}
	t_numeric = (clock()-start)*1.0/CLOCKS_PER_SEC;
	printf( "\r\tNumerical Factorization......\tTime=%g\t\t\r\n",t_numeric );

	x = (double*)malloc( sizeof(double)*nCol );
	for( i = 0; i < nCol; i++ )		{
		x[i] = rhs[i];		
		rhs_norm += (rhs[i]*rhs[i]);
	}
	rhs_norm =sqrt(rhs_norm);
/************* forward/backward substitution ******************/
	start = clock();
	GSS_solve_ld( hSolver,nRow,nCol,ptr,ind,val,x );
	t_solve = (clock()-start)*1.0/CLOCKS_PER_SEC;
	printf( "\t\tsolve time=%g\r\n",t_solve );
/************* check residual ******************/
	for( i = 0; i < nCol; i++ )	{
		for( j = ptr[i]; j < ptr[i+1]; j++ )	{
			r = ind[j];
			rhs[r] -= val[j]*x[i];
			if( (type==11 || type==12) && r!=i )	{
				rhs[i] = rhs[i]-val[j]*x[r];
			}
		}		
	}
	for( i = 0; i < nRow; i++ )	
		err += (rhs[i]*rhs[i]);
	err = sqrt(err);	
	printf( "\t\tResidual |Ax-b|=%g; |b|=%g\r\n",err,rhs_norm );			
	free( x );

EXIT:
/************* release memory ******************/
	if( hSolver != NULL )
		GSS_clear_ld( hSolver );				
}

/*
	solve a simple Positive Symmetric Definite 5*5 matrix 
*/
int main( int argc, char* argv[] )
{
	int ptr[6]={0,3,6,8,9,10};
	int	ind[10]={0,1,4,1,2,3,2,4,3,4};
	double	val[10]={1, 2, -1, 5, -2, 1, 5,-4,9,31},b[5]={2,6,-1,10,26};

    GSS_spd_demo_(5,5,ptr,ind,val,b,11,5);

	return 0x0;
}