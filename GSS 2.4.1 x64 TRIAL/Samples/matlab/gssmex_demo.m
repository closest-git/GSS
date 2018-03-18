% GSSMEX is a MATLAB mexFunction for solving sparse linear systems. 
% 
%
% Usage: [x,RET] = GSSMEX(A, b);
% which solves a sparse linear system Ax=b, returning the solution x .A must be sparse ,
% square and real array. b must be a full real vector. If ret=0.0, 
% the function succeeds. Please see gssmex_demo.m
% 
% GSSMEX , Copyright (c) 2005 by CYS.
% All Rights Reserved.  Type gssmex_license for License.
% Any problem,contact gsp@grusoft.com or see http://www.grusoft.com/gssmex.htm
sTestSet=[
    'E:\Test\umfpack\Sym\torso2.mat         ';
    'E:\Test\umfpack\Sym\olafu.mat          ';
    'E:\Test\umfpack\Sym\venkat01.mat       ';
    'E:\Test\umfpack\Sym\af23560.mat        ';
    'E:\Test\umfpack\Sym\raefsky3.mat       '
    'E:\Test\umfpack\Sym\Zhao1.mat          ';
    'E:\Test\umfpack\Sym\Zhao2.mat          ';
    'E:\Test\umfpack\Sym\ex11.mat           ';
    'E:\Test\umfpack\Sym\raefsky4.mat       ';
    'E:\Test\umfpack\Sym\wang4.mat          ';
    'E:\Test\umfpack\Sym\xenon1.mat         ';
    'E:\Test\umfpack\Sym\cage10.mat         '; 
    'E:\Test\umfpack\Sym\stomach.mat        ';
    'E:\Test\umfpack\2by2\goodwin.mat       ';
    'E:\Test\umfpack\2by2\epb2.mat          ';
    'E:\Test\umfpack\2by2\garon2.mat        ';
    'E:\Test\umfpack\2by2\rim.mat           ';
    'E:\Test\umfpack\2by2\heart2.mat        ';
    'E:\Test\umfpack\2by2\epb3.mat          ';
    'E:\Test\umfpack\2by2\rma10.mat         ';
    'E:\Test\umfpack\2by2\heart1.mat        ';
    'E:\Test\umfpack\2by2\psmigr_1.mat      ';
    'E:\Test\umfpack\Unsym\onetone2.mat     ';
    'E:\Test\umfpack\Unsym\graham1.mat      ';
    'E:\Test\umfpack\Unsym\lhr34c.mat       ';
    'E:\Test\umfpack\Unsym\e40r0100.mat     ';
    'E:\Test\umfpack\Unsym\lhr71c.mat       ';
    'E:\Test\umfpack\Unsym\ex40.mat         ';
    'E:\Test\umfpack\Unsym\onetone1.mat     ';
    'E:\Test\umfpack\Unsym\av41092.mat      ';
    'E:\Test\umfpack\Unsym\twotone.mat      ';
    'E:\Test\umfpack\Unsym\psmigr_2.mat     ';
    'E:\Test\umfpack\Unsym\bbmat.mat        ';
    'E:\Test\umfpack\Unsym\g7jac200sc.mat   ';
    'E:\Test\umfpack\Unsym\mark3jac140sc.mat';   
    ];
nTest=size(sTestSet,1);
t=ones(nTest,1);
err=ones(nTest,1);
ret = 0;
for i=1:nTest
    sPath=deblank(sTestSet(i,:));
    load ( sPath ); 
    A=Problem.A;
%    spy(A);
    nRow=size(A,1);       
    B=A*ones(nRow,1);    
    tic;
%	X=A\B;
	[X,ret]=gssmex(A,B);
    t(i) = toc;
    if( ret == 0 )
        err(i)=norm(A*X-B);
    end
    fprintf('%d:\t"%s",\tdim=%d,nnz=%d,time=%g,err=%g\n',i,sPath,nRow,nnz(A),t(i),err(i) );
     
end
