#ifndef _GRUS_SPARSE_SOLVER_H_
#define _GRUS_SPARSE_SOLVER_H_

/*
	v2.3.0	YingShi Chen
		4/16/2012
*/
//定义双精度复数
#ifndef _GRUS_COMPLEX_STRUCT_
typedef struct			
{
    double component [2] ;	/* real and imaginary parts */

} _double_COMPLEX ;
//定义单精度复数
typedef struct			
{
    float component [2] ;	/* real and imaginary parts */

} _float_COMPLEX ;
#endif

//申明下列函数从DLL库引入
#ifdef WIN32
	#define GSS_IMPORT __declspec(dllimport)		
#else
	#define GSS_IMPORT 
#endif		

#ifdef __cplusplus
extern "C" {
#endif

/*
	Init

	Input
		nRow, nCol, ptr, ind, val  	storage SPD matrices. See storage format.
		type 						matrix type. 
		setting[32] 				control parameters.
	Return
		returns 0x0 if init successfully, otherwise return error code.

*/
GSS_IMPORT int GSS_init_id( int nRow,int nCol,int* ptr,int* ind,double *val,int type,double *setting  );
GSS_IMPORT int GSS_init_is( int nRow,int nCol,int* ptr,int* ind,float *val,int type,double *setting  );
GSS_IMPORT int GSS_init_iz( int nRow,int nCol,int* ptr,int* ind,_double_COMPLEX *val,int type,double *setting  );
GSS_IMPORT int GSS_init_ic( int nRow,int nCol,int* ptr,int* ind,_float_COMPLEX *val,int type,double *setting  );

GSS_IMPORT	int GSS_init_ld( int nRow,int nCol,int* ptr,int* ind,double *val,int type,double *setting  );
GSS_IMPORT	int GSS_init_ls( int nRow,int nCol,int* ptr,int* ind,float *val,int type,double *setting  );
GSS_IMPORT	int GSS_init_lc( int nRow,int nCol,int* ptr,int* ind,_float_COMPLEX *val,int type,double *setting  );
GSS_IMPORT	int GSS_init_lz( int nRow,int nCol,int* ptr,int* ind,_double_COMPLEX *val,int type,double *setting  );

/*
	符号分解

	int nRow,nCol	行数，列数
	int *ptr, int *ind, double *val	矩阵按压缩列格式存贮，(ptr,ind,val)为列指针，行下标和元素值	

	返回值：
					分解成功返回求解器的指针,否则返回0x0
*/
GSS_IMPORT void* GSS_symbol_id( int nRow,int nCol,int* ptr,int* ind,double *val );
GSS_IMPORT void* GSS_symbol_is( int nRow,int nCol,int* ptr,int* ind,float *val );
GSS_IMPORT void* GSS_symbol_iz( int nRow,int nCol,int* ptr,int* ind,_double_COMPLEX *val );
GSS_IMPORT void* GSS_symbol_ic( int nRow,int nCol,int* ptr,int* ind,_float_COMPLEX *val );

GSS_IMPORT	void* GSS_symbol_ld( int nRow,int nCol,int* ptr,int* ind,double *val );
GSS_IMPORT	void* GSS_symbol_ls( int nRow,int nCol,int* ptr,int* ind,float *val );
GSS_IMPORT	void* GSS_symbol_lc( int nRow,int nCol,int* ptr,int* ind,_float_COMPLEX *val );
GSS_IMPORT	void* GSS_symbol_lz( int nRow,int nCol,int* ptr,int* ind,_double_COMPLEX *val );

/*
	数值分解

	int nRow,nCol	行数，列数
	int *ptr, int *ind, double *val	矩阵按压缩列格式存贮，(ptr,ind,val)为列指针，行下标和元素值	
	void *hSolver		指向求解器的指针

	返回值：
					分解成功返回0x0, 否则返回错误代码
*/
GSS_IMPORT	int GSS_numeric_id( int nRow,int nCol,int* ptr,int* ind,double *val,void *hSolver );
GSS_IMPORT	int GSS_numeric_is( int nRow,int nCol,int* ptr,int* ind,float *val,void *hSolver );
GSS_IMPORT	int GSS_numeric_iz( int nRow,int nCol,int* ptr,int* ind,_double_COMPLEX *val,void *hSolver );
GSS_IMPORT	int GSS_numeric_ic( int nRow,int nCol,int* ptr,int* ind,_float_COMPLEX *val,void *hSolver );

GSS_IMPORT	int GSS_numeric_ls( int nRow,int nCol,int* ptr,int* ind,float *val,void *hSolver );
GSS_IMPORT	int GSS_numeric_ld( int nRow,int nCol,int* ptr,int* ind,double *val,void *hSolver );
GSS_IMPORT	int GSS_numeric_lc( int nRow,int nCol,int* ptr,int* ind,_float_COMPLEX *val,void *hSolver );
GSS_IMPORT	int GSS_numeric_lz( int nRow,int nCol,int* ptr,int* ind,_double_COMPLEX *val,void *hSolver );

/*
	回代求解

	void *hSolver	指向求解器的指针
	int nRow,nCol	行数，列数
	int *ptr, int *ind, double *val	矩阵按压缩列格式存贮，(ptr,ind,val)为列指针，行下标和元素值	
	double *rhs		方程组的右端项，返回的解也存储在rhs中

	返回值：
					完成求解返回0x0, 否则返回错误代码
*/
GSS_IMPORT	int GSS_solve_id( void *hSolver,int nRow,int nCol,int *ptr,int *ind,double *val,double *rhs );
GSS_IMPORT	int GSS_solve_is( void *hSolver,int nRow,int nCol,int *ptr,int *ind,float *val,double *rhs );
GSS_IMPORT	int GSS_solve_iz( void *hSolver,int nRow,int nCol,int *ptr,int *ind,_double_COMPLEX *val,_double_COMPLEX *rhs );
GSS_IMPORT	int GSS_solve_ic( void *hSolver,int nRow,int nCol,int *ptr,int *ind,_float_COMPLEX *val,_float_COMPLEX *rhs );

GSS_IMPORT	int GSS_solve_ls( void *hSolver,int nRow,int nCol,int *ptr,int *ind,float *val,float *rhs );
GSS_IMPORT	int GSS_solve_ld( void *hSolver,int nRow,int nCol,int *ptr,int *ind,double *val,double *rhs );
GSS_IMPORT	int GSS_solve_lc( void *hSolver,int nRow,int nCol,int *ptr,int *ind,_float_COMPLEX *val,_float_COMPLEX *rhs );
GSS_IMPORT	int GSS_solve_lz( void *hSolver,int nRow,int nCol,int *ptr,int *ind,_double_COMPLEX *val,_double_COMPLEX *rhs );

/*
	释放求解器占用的内存

	void *hSolver	指向求解器的指针

	返回值：
					完成释放返回0x0, 否则返回错误代码
*/
GSS_IMPORT	int GSS_clear_id( void* hSolver );
GSS_IMPORT	int GSS_clear_is( void* hSolver );
GSS_IMPORT	int GSS_clear_iz( void* hSolver );
GSS_IMPORT	int GSS_clear_ic( void* hSolver );

GSS_IMPORT	int GSS_clear_ls( void* hSolver );
GSS_IMPORT	int GSS_clear_ld( void* hSolver );
GSS_IMPORT	int GSS_clear_lc( void* hSolver );
GSS_IMPORT	int GSS_clear_lz( void* hSolver );

#ifdef __cplusplus
}
#endif

#endif