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
#ifndef _GSS_DLL_6_
	#define _GSS_DLL_6_ __declspec(dllimport)
#endif	
	
#ifdef _WIN64
	#define GSS_lu_d		GSS_lu_ld
	#define GSS_lu_z		GSS_lu_lz
	
	#define GSS_solve_d		GSS_solve_ld
	#define GSS_solve_z		GSS_solve_lz
	
	#define GSS_clear_d		GSS_clear_ld
	#define GSS_clear_z		GSS_clear_lz
#else
	#define GSS_lu_d		GSS_lu_id
	#define GSS_lu_z		GSS_lu_iz

	#define GSS_solve_d		GSS_solve_id
	#define GSS_solve_z		GSS_solve_iz

	#define GSS_clear_d		GSS_clear_id
	#define GSS_clear_z		GSS_clear_iz
#endif

#ifdef __cplusplus
extern "C" {
#endif



_GSS_DLL_6_ void* GSS_lu_d( void *,int nCol,int* ptr,int* ind,double *val,double *b,double *x,int hpu,int mType,int phase,double *param  );
_GSS_DLL_6_ void* GSS_lu_z( void *,int nCol,int* ptr,int* ind,_double_COMPLEX *val,_double_COMPLEX *b,_double_COMPLEX *x,int hpu,int mType,int phase,double *param  );



/*
	��ʼ��

	int nRow,nCol	����������
	int *ptr, int *ind, double *val	����ѹ���и�ʽ������(ptr,ind,val)Ϊ��ָ�룬���±��Ԫ��ֵ	
	type	�������ͣ��������¡�	
		0��		ȱʡֵΪ0
		11��	�Գ���������(ptr, ind, val)Ϊ����������(���Խ���)�����ݡ�
		12��	�ԳƲ�������(ptr, ind, val)Ϊ����������(���Խ���)�����ݡ�
	setting[32]		���Ʋ�������ʼֵ������Ϊ0!	���庬�弰���òμ��û��ֲ�

	����ֵ��
		��ʼ���ɹ�����0x0,���򷵻ش������
*/
_GSS_DLL_6_ int GSS_init_id( int nRow,int nCol,int* ptr,int* ind,double *val,int type,double *setting  );
_GSS_DLL_6_ int GSS_init_is( int nRow,int nCol,int* ptr,int* ind,float *val,int type,double *setting  );
_GSS_DLL_6_ int GSS_init_iz( int nRow,int nCol,int* ptr,int* ind,_double_COMPLEX *val,int type,double *setting  );
_GSS_DLL_6_ int GSS_init_ic( int nRow,int nCol,int* ptr,int* ind,_float_COMPLEX *val,int type,double *setting  );

_GSS_DLL_6_	int GSS_init_ld( int nRow,int nCol,int* ptr,int* ind,double *val,int type,double *setting  );
_GSS_DLL_6_	int GSS_init_ls( int nRow,int nCol,int* ptr,int* ind,float *val,int type,double *setting  );
_GSS_DLL_6_	int GSS_init_lc( int nRow,int nCol,int* ptr,int* ind,_float_COMPLEX *val,int type,double *setting  );
_GSS_DLL_6_	int GSS_init_lz( int nRow,int nCol,int* ptr,int* ind,_double_COMPLEX *val,int type,double *setting  );

/*
	���ŷֽ�

	int nRow,nCol	����������
	int *ptr, int *ind, double *val	����ѹ���и�ʽ������(ptr,ind,val)Ϊ��ָ�룬���±��Ԫ��ֵ	

	����ֵ��
					�ֽ�ɹ������������ָ��,���򷵻�0x0
*/
_GSS_DLL_6_ void* GSS_symbol_id( int nRow,int nCol,int* ptr,int* ind,double *val );
_GSS_DLL_6_ void* GSS_symbol_is( int nRow,int nCol,int* ptr,int* ind,float *val );
_GSS_DLL_6_ void* GSS_symbol_iz( int nRow,int nCol,int* ptr,int* ind,_double_COMPLEX *val );
_GSS_DLL_6_ void* GSS_symbol_ic( int nRow,int nCol,int* ptr,int* ind,_float_COMPLEX *val );

_GSS_DLL_6_	void* GSS_symbol_ld( int nRow,int nCol,int* ptr,int* ind,double *val );
_GSS_DLL_6_	void* GSS_symbol_ls( int nRow,int nCol,int* ptr,int* ind,float *val );
_GSS_DLL_6_	void* GSS_symbol_lc( int nRow,int nCol,int* ptr,int* ind,_float_COMPLEX *val );
_GSS_DLL_6_	void* GSS_symbol_lz( int nRow,int nCol,int* ptr,int* ind,_double_COMPLEX *val );

/*
	��ֵ�ֽ�

	int nRow,nCol	����������
	int *ptr, int *ind, double *val	����ѹ���и�ʽ������(ptr,ind,val)Ϊ��ָ�룬���±��Ԫ��ֵ	
	void *hSolver		ָ���������ָ��

	����ֵ��
					�ֽ�ɹ�����0x0, ���򷵻ش������
*/
_GSS_DLL_6_	int GSS_numeric_id( int nRow,int nCol,int* ptr,int* ind,double *val,void *hSolver );
_GSS_DLL_6_	int GSS_numeric_is( int nRow,int nCol,int* ptr,int* ind,float *val,void *hSolver );
_GSS_DLL_6_	int GSS_numeric_iz( int nRow,int nCol,int* ptr,int* ind,_double_COMPLEX *val,void *hSolver );
_GSS_DLL_6_	int GSS_numeric_ic( int nRow,int nCol,int* ptr,int* ind,_float_COMPLEX *val,void *hSolver );

_GSS_DLL_6_	int GSS_numeric_ls( int nRow,int nCol,int* ptr,int* ind,float *val,void *hSolver );
_GSS_DLL_6_	int GSS_numeric_ld( int nRow,int nCol,int* ptr,int* ind,double *val,void *hSolver );
_GSS_DLL_6_	int GSS_numeric_lc( int nRow,int nCol,int* ptr,int* ind,_float_COMPLEX *val,void *hSolver );
_GSS_DLL_6_	int GSS_numeric_lz( int nRow,int nCol,int* ptr,int* ind,_double_COMPLEX *val,void *hSolver );

/*
	�ش����

	void *hSolver	ָ���������ָ��
	int nRow,nCol	����������
	int *ptr, int *ind, double *val	����ѹ���и�ʽ������(ptr,ind,val)Ϊ��ָ�룬���±��Ԫ��ֵ	
	double *rhs		��������Ҷ�����صĽ�Ҳ�洢��rhs��

	����ֵ��
					�����ⷵ��0x0, ���򷵻ش������
*/
_GSS_DLL_6_	int GSS_solve_id( void *hSolver,int nRow,int nCol,int *ptr,int *ind,double *val,double *rhs );
_GSS_DLL_6_	int GSS_solve_is( void *hSolver,int nRow,int nCol,int *ptr,int *ind,float *val,double *rhs );
_GSS_DLL_6_	int GSS_solve_iz( void *hSolver,int nRow,int nCol,int *ptr,int *ind,_double_COMPLEX *val,_double_COMPLEX *rhs );
_GSS_DLL_6_	int GSS_solve_ic( void *hSolver,int nRow,int nCol,int *ptr,int *ind,_float_COMPLEX *val,_float_COMPLEX *rhs );

_GSS_DLL_6_	int GSS_solve_ls( void *hSolver,int nRow,int nCol,int *ptr,int *ind,float *val,float *rhs );
_GSS_DLL_6_	int GSS_solve_ld( void *hSolver,int nRow,int nCol,int *ptr,int *ind,double *val,double *rhs );
_GSS_DLL_6_	int GSS_solve_lc( void *hSolver,int nRow,int nCol,int *ptr,int *ind,_float_COMPLEX *val,_float_COMPLEX *rhs );
_GSS_DLL_6_	int GSS_solve_lz( void *hSolver,int nRow,int nCol,int *ptr,int *ind,_double_COMPLEX *val,_double_COMPLEX *rhs );

/*
	�ͷ������ռ�õ��ڴ�

	void *hSolver	ָ���������ָ��

	����ֵ��
					����ͷŷ���0x0, ���򷵻ش������
*/
_GSS_DLL_6_	int GSS_clear_id( void* hSolver );
_GSS_DLL_6_	int GSS_clear_is( void* hSolver );
_GSS_DLL_6_	int GSS_clear_iz( void* hSolver );
_GSS_DLL_6_	int GSS_clear_ic( void* hSolver );

_GSS_DLL_6_	int GSS_clear_ls( void* hSolver );
_GSS_DLL_6_	int GSS_clear_ld( void* hSolver );
_GSS_DLL_6_	int GSS_clear_lc( void* hSolver );
_GSS_DLL_6_	int GSS_clear_lz( void* hSolver );


_GSS_DLL_6_ void GSS_dump_id( void *hDump,char *sTitle );
_GSS_DLL_6_ void GSS_dump_ld( void *hDump,char *sTitle );
_GSS_DLL_6_ void GSS_dump_iz( void *hDump,char *sTitle );
_GSS_DLL_6_ void GSS_dump_lz( void *hDump,char *sTitle );

_GSS_DLL_6_ int GBIN_Write_id( char *sPath_0,int nRow,int nCol,int *ptr,int *ind,double *val,int flag );
_GSS_DLL_6_ int GBIN_Write_ld( char *sPath_0,int nRow,int nCol,int *ptr,int *ind,double *val,int flag );
_GSS_DLL_6_ int GBIN_Write_iz( char *sPath_0,int nRow,int nCol,int *ptr,int *ind,_double_COMPLEX *val,int flag );
_GSS_DLL_6_ int GBIN_Write_lz( char *sPath_0,int nRow,int nCol,int *ptr,int *ind,_double_COMPLEX *val,int flag );
_GSS_DLL_6_ int GBIN_Read_id( char *sBinPath,int* nrow,int* ncol,int* nnz,int** colptr,int** rowind,double** g_val,double**rhs,int flag );	
_GSS_DLL_6_ int GBIN_Read_ld( char *sBinPath,int* nrow,int* ncol,int* nnz,int** colptr,int** rowind,double** g_val,double**rhs,int flag );
_GSS_DLL_6_ int GBIN_Read_iz( char *sBinPath,int* nrow,int* ncol,int* nnz,int** colptr,int** rowind,_double_COMPLEX** g_val,_double_COMPLEX**rhs,int flag );
_GSS_DLL_6_ int GBIN_Read_lz( char *sBinPath,int* nrow,int* ncol,int* nnz,int** colptr,int** rowind,_double_COMPLEX** g_val,_double_COMPLEX**rhs,int flag );	
#ifdef __cplusplus
}
#endif

#endif