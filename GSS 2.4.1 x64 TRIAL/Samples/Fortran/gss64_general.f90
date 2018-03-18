!
!	����GSS-64bit version ���ϡ�����
!	ϡ��������ѹ���и�ʽ�洢���±��1��ʼ,ע�����GSSʱ�±�ת���Ĺ���
!
!	ѹ���и�ʽ����{ptr,ind,val}��¼ϡ�����ķ���Ԫ��
!	����N����nnz������Ԫ�ľ�����˵:
!	ind, val�ĳ�����nnz������˳���¼ÿ������Ԫ���б����ֵ��
!	ptr�ĳ�����N+1��ptr[i]��¼��i�е�һ������Ԫ��λ��,���һ��Ԫ��ptr[N+1]=nnz+1��
!		������i�еĳ��Ⱦ���   ptr[i+1]-ptr[i]��
!
!	�����������3�׵ľ���
!		1.0  0.0  5.0
!		0.0  3.0  6.0
!		2.0  4.0  7.0
!   �� 	ptr[4]={1,3,5,8}
!		ind[7]={1,3,2,3,1,2,3}
!		val[7]={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0}
!   
!   Copyright (c) 2006-present ��Ӣʱ(YingShiChen).    All Rights Reserved. 
!	Any problem,contact gsp@grusoft.com
!

MODULE GSS_64_INTERFACE

      implicit none    
            INTERFACE 
		subroutine GRUS_init_heapinfo( );
 		!DEC$ ATTRIBUTES ALIAS:'GRUS_init_heapinfo' :: grus_init_heapinfo
		!DEC$ ATTRIBUTES C :: GRUS_init_heapinfo
		end subroutine !GRUS_init_heapinfo 

		subroutine GRUS_exit_heapinfo( );
 		!DEC$ ATTRIBUTES ALIAS:'GRUS_exit_heapinfo' :: grus_exit_heapinfo
		!DEC$ ATTRIBUTES C :: GRUS_exit_heapinfo
		end subroutine !GRUS_exit_heapinfo 
				
		function GSS_init_ld(nRow,nCol,ptr,ind,val,m_type,setting)
		!DEC$ ATTRIBUTES ALIAS:'GSS_init_ld' :: GSS_init_ld
		!DEC$ ATTRIBUTES C :: GSS_init_ld
			INTEGER GSS_init_ld
			INTEGER nRow,nCol,ptr(*),ind(*),m_type
			REAL(8) val(*),setting(32)
		end function !GSS_init_ld

		function GSS_symbol_ld( nRow,nCol,ptr,ind,val )
		!DEC$ ATTRIBUTES ALIAS:'GSS_symbol_ld' :: GSS_symbol_ld
		!DEC$ ATTRIBUTES C :: GSS_symbol_ld
			INTEGER*8 GSS_symbol_ld
			INTEGER nRow,nCol,ptr(*),ind(*)
			REAL(8) val(*)
		end function !GSS_symbol_udi

		function GSS_numeric_ld( nRow,nCol,ptr,ind,val,hGSS )
		!DEC$ ATTRIBUTES ALIAS:'GSS_numeric_ld' :: GSS_numeric_ld
		!DEC$ ATTRIBUTES C :: GSS_numeric_ld
			INTEGER*8 hGSS
            INTEGER GSS_numeric_ld
			INTEGER nRow, nCol, ptr(*), ind(*)
			REAL(8) val(*)
		end function !GSS_numeric_udi

		function GSS_solve_ld( hGSS,nRow,nCol,ptr,ind,val,x )
		!DEC$ ATTRIBUTES ALIAS:'GSS_solve_ld' :: GSS_solve_ld
		!DEC$ ATTRIBUTES C :: GSS_solve_ld
			INTEGER*8 hGSS
            INTEGER GSS_solve_ld,nRow,nCol,ptr(*),ind(*)
			REAL(8) val(*),x(*)
		end function !GSS_solve_ld

		function GSS_clear_ld( hGSS )
		!DEC$ ATTRIBUTES ALIAS:'GSS_clear_ld' :: GSS_clear_ld
		!DEC$ ATTRIBUTES C :: GSS_clear_ld
			INTEGER*8 hGSS
            INTEGER GSS_clear_ld
		end function !GSS_clear_ld
	END    INTERFACE 
END MODULE GSS_64_INTERFACE

	subroutine GSS_DEMO_C_( dim,ptr,ind,val,rhs,flag )	
! Copyright (c) 2006-present ��Ӣʱ(YingShiChen)
	use GSS_64_INTERFACE			!��������	use GSS_64_INTERFACE
	implicit none    
	integer dim,nnz,ptr(*),ind(*),loop,ret,flag
!	double complex x(:),val(*),rhs(*)
	double precision x(:),val(*),rhs(*)
    double precision t_symbol,t_numeric,t_solve,start
	double precision  err,rhs_norm,setting(32)
	allocatable:: x
	INTEGER*8 hGSS			!ָ�������,64λ�汾��������ΪINTEGER*8����
	integer i,j,r,strategy,nIterRefine,info,m_type
!	clock_t start;
	
	loop=1
	t_numeric=0.0;		t_solve=0.0
	nnz = ptr(dim+1)-1 
	m_type=0            !�ǶԳƾ�������Ϊ0
	write( *,* ), "dim=",dim,"nnz=",nnz,"m_type=",m_type
!/*************���������******************/
	strategy=0;		info=0
	hGSS = 0
!�±�ת��
	ptr(1:dim+1)=ptr(1:dim+1)-1
	ind(1:nnz)=ind(1:nnz)-1
	setting=0.0
	ret = GSS_init_ld( dim,dim,ptr,ind,val,m_type,setting )
	if( ret/=0 )	then
		write(*,*) "        ERROR at init GSS solver. ERROR CODE",ret
		goto 100;
	endif
	start=SECNDS(0.0) 
	hGSS = GSS_symbol_ld( dim,dim,ptr,ind,val )	
	t_symbol = SECNDS(start)
	write( *,* ),"symbol time=",t_symbol 
	if( hGSS==0 )	then
		write(*,*) "        ERROR at symbol."
		goto 100;
	endif
	start=SECNDS(0.0) 
	do i = 1,loop
		ret = GSS_numeric_ld( dim,dim,ptr,ind,val,hGSS )
		if( ret /= 0 )	then
			write(*,*) "        ERROR at numeric. ERROR CODE",ret
			hGSS=0;			!�������,GSS���Զ��ͷ��ڴ�
			goto 100		
		endif
	end do 
	t_numeric = SECNDS(start)/loop
	write( *,* ),"numeric time=",t_numeric 
	
	allocate( x(dim) )
	start = SECNDS(0.0) 
	do i = 1,loop
		x(1:dim)=rhs(1:dim)
		ret = GSS_solve_ld( hGSS,dim,dim,ptr,ind,val,x )
	end do
	t_solve = SECNDS(start)/loop
	write( *,* ), "solve time=",t_solve 
	ret = GSS_clear_ld( hGSS )		!�ͷ�ռ�õ��ڴ�
	write( *,* ), "x=",x(1:dim)  
	write( *,* ), "b=",rhs(1:dim) 

100	continue
	!�±긴ԭ
	ptr(1:dim+1)=ptr(1:dim+1)+1
	ind(1:nnz)=ind(1:nnz)+1
!/*************||Ax-b||******************/
	if( hGSS/=0 )	then
		rhs_norm=0.0;			err=0.0
		do i = 1,dim	
			rhs_norm = rhs_norm+(rhs(i)*rhs(i))
		enddo
		rhs_norm = sqrt(rhs_norm);
		do i = 1,dim	
			do j = ptr(i), ptr(i+1)-1
				r = ind(j)
				rhs(r) = rhs(r)-val(j)*x(i)
				if( (m_type==11 .or. m_type==12) .and. r/=i )	then
					rhs(i) = rhs(i)-val(j)*x(r)
				endif
			enddo		
		end do
		do i = 1,dim	
			err = err+(rhs(i)*rhs(i))
		end do
		err = sqrt(err)	
		write( *,* ), "Residual |Ax-b|=",err,"|b|=",rhs_norm 			
		deallocate( x )
	endif

	end subroutine	

!
!	����GSS��ϡ�����
!	ϡ��������ѹ���и�ʽ�洢���±��1��ʼ,ע�����GSSʱ�±�ת���Ĺ���
!
!	ѹ���и�ʽ����{ptr,ind,val}��¼ϡ�����ķ���Ԫ��
!	����N����nnz������Ԫ�ľ�����˵:
!	ind, val�ĳ�����nnz������˳���¼ÿ������Ԫ���б����ֵ��
!	ptr�ĳ�����N+1��ptr[i]��¼��i�е�һ������Ԫ��λ��,���һ��Ԫ��ptr[N+1]=nnz+1��
!		������i�еĳ��Ⱦ���   ptr[i+1]-ptr[i]��
!
!	�����������3�׵ľ���
!		1.0  0.0  5.0
!		0.0  3.0  6.0
!		2.0  4.0  7.0
!   �� 	ptr[4]={1,3,5,8}
!		ind[7]={1,3,2,3,1,2,3}
!		val[7]={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0}
!   
!   Copyright (c) 2006-present ��Ӣʱ(YingShiChen).    All Rights Reserved. 
!	Any problem,contact gsp@grusoft.com
!    
    program gss_for_demo

    implicit none

    ! Variables
    integer NEQ;
    integer ptr(4),ind(7)
 !   double complex A_val(7),rhs(3)
 !   data A_val /(1.0,0),(2.0,0),(3.0,0),(4.0,0),(5.0,0),(6.0,0),(7.0,0)/
    double precision A_val(7),rhs(3)
    data A_val /1.0,2.0,3.0,4.0,5.0,6.0,7.0/
    data NEQ /3/
    data ptr /1,3,5,8/
    data ind /1,3,2,3,1,2,3/
    data A_val /1.0,2.0,3.0,4.0,5.0,6.0,7.0/
  
    rhs = 1.0    
    call GSS_DEMO_C_( NEQ,ptr,ind,A_val,rhs,0 )

    end program gss_for_demo
