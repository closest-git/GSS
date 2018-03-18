!
!	Show the use of the GSS_spd to solve double precision matrices.
!
!	The matrices are stored in compressed column storage. That is (ptr,ind,val)
!	where ind stores the row indices of each nonzero, ptr stores the first element position of each column 
!		and val vector stores the values of the nonzero elements of the matrix.
!     For symmetrical matrices, only lower triangle (include diagonals) are stored.
!
!     For example, for a simple 3*3 matrix
!		1.0  0.0  2.0
!		0.0  5.0  3.0
!		2.0  3.0  10.0
!    then
! 	  ptr[4]={1,3,5,6}
!		ind[5]={1,3,2,3,3}
!		val[5]={1.0, 2.0, 5.0, 3.0, 10.0}
!   
!    Copyright (c) 2005-present by YingShiChen.    All Rights Reserved. 
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


	subroutine GSS_SPD_DEMO_( dim,ptr,ind,val,rhs,m_type )	
! Copyright (c) 2005-present by YingShiChen.    All Rights Reserved. 
	use GSS_64_INTERFACE			!Must use GSS_64_INTERFACE
	implicit none    
	integer dim,nnz,ptr(*),ind(*),loop,ret
	double precision val(*),rhs(*),start,setting(32)

	double precision  t_symbol,t_numeric,t_solve,x(:),err,rhs_norm
	allocatable:: x
	INTEGER*8 hGSS			!指向求解器,64位版本必须申明为INTEGER*8类型
	integer i,j,r,strategy,nIterRefine,info,m_type
!	clock_t start;
	
	loop=1
	t_numeric=0.0;		t_solve=0.0
	nnz = ptr(dim+1)-1 
	write( *,* ), "dim=",dim,"nnz=",nnz,"m_type=",m_type
!/*******************************/
	strategy=0;		info=0
	hGSS = 0
	m_type=11;		        !always 11 for GSS_spd	
!FORTRAN=>C
	do i = 1,dim+1
		ptr(i)=ptr(i)-1
	end do
	do i = 1,nnz
		ind(i)=ind(i)-1
	enddo	
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
			hGSS=0;			!must set hGSS to zero
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
	ret = GSS_clear_ld( hGSS )		!

100	continue
	!C=>FORTRAN
	do i = 1,dim+1
		ptr(i)=ptr(i)+1
	enddo
	do i = 1,nnz
		ind(i)=ind(i)+1
	enddo	
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

      end subroutine	!GSS_demo_6
      
!
!	调用GSS 2.3求解对称正定稀疏矩阵
!	稀疏矩阵采用压缩列格式存储，下标从1开始,注意调用GSS时下标转化的过程
!
!	压缩列格式采用{ptr,ind,val}记录稀疏矩阵的非零元。
!	对称正定只需存储下三角(含对角线)!
!	对于N阶有nnz个非零元的矩阵来说:
!	ind, val的长度是nnz。按列顺序记录每个非零元的行标和数值。
!	ptr的长度是N+1。ptr[i]记录第i列第一个非零元的位置,最后一个元素ptr[N+1]=nnz+1。
!		这样第i列的长度就是   ptr[i+1]-ptr[i]。
!
!	例如对于如下3阶的矩阵
!		1.0  0.0  2.0
!		0.0  3.0  4.0
!		2.0  4.0  10.0
!   则 	ptr[4]={1,3,5,6}
!		ind[5]={1,3,2,3,3}
!		val[5]={1.0, 2.0, 3.0, 4.0, 10.0}
!   
!   Copyright (c) 2006-present 陈英时(YingShiChen).    All Rights Reserved. 
!	Any problem,contact gsp@grusoft.com
!    
      program gss_for_demo

      implicit none

    ! Variables
      integer NEQ;
      integer ptr(4),ind(5),m_type
 
      double precision A_val(5),rhs(3)
      data NEQ /3/
      data ptr /1,3,5,6/
      data ind /1,3,2,3,3/
      data A_val /1.0, 2.0, 3.0, 4.0, 10.0/
  
      rhs = 1.0   
      m_type=11           !对称正定矩阵的类型总是为11
      call GSS_SPD_DEMO_( NEQ,ptr,ind,A_val,rhs,m_type )

      end program gss_for_demo

