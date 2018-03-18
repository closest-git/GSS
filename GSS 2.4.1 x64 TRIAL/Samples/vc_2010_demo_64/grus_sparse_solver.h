#ifndef _GRUS_SPARSE_SOLVER_H_
#define _GRUS_SPARSE_SOLVER_H_

/*
	v2.3.0	YingShi Chen
		4/16/2012
*/
//����˫���ȸ���
#ifndef _GRUS_COMPLEX_STRUCT_
typedef struct			
{
    double component [2] ;	/* real and imaginary parts */

} _double_COMPLEX ;
//���嵥���ȸ���
typedef struct			
{
    float component [2] ;	/* real and imaginary parts */

} _float_COMPLEX ;
#endif

//�������к�����DLL������
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
	���ŷֽ�

	int nRow,nCol	����������
	int *ptr, int *ind, double *val	����ѹ���и�ʽ������(ptr,ind,val)Ϊ��ָ�룬���±��Ԫ��ֵ	

	����ֵ��
					�ֽ�ɹ������������ָ��,���򷵻�0x0
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
	��ֵ�ֽ�

	int nRow,nCol	����������
	int *ptr, int *ind, double *val	����ѹ���и�ʽ������(ptr,ind,val)Ϊ��ָ�룬���±��Ԫ��ֵ	
	void *hSolver		ָ���������ָ��

	����ֵ��
					�ֽ�ɹ�����0x0, ���򷵻ش������
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
	�ش����

	void *hSolver	ָ���������ָ��
	int nRow,nCol	����������
	int *ptr, int *ind, double *val	����ѹ���и�ʽ������(ptr,ind,val)Ϊ��ָ�룬���±��Ԫ��ֵ	
	double *rhs		��������Ҷ�����صĽ�Ҳ�洢��rhs��

	����ֵ��
					�����ⷵ��0x0, ���򷵻ش������
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
	�ͷ������ռ�õ��ڴ�

	void *hSolver	ָ���������ָ��

	����ֵ��
					����ͷŷ���0x0, ���򷵻ش������
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