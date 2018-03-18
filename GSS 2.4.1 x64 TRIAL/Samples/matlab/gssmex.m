function [out1, out2] = gssmex(in1, in2, in3) %#ok
%gssmex computes x=A\b for a sparse real matrix A
%
% Usage: [x,RET] = GSSMEX(A, b,type);
% which solves a sparse linear system Ax=b, returning the solution x .
% A must be sparse ,square and real array. b must be a full real vector. 
% For Symmetric Positive Definite matrices, type is 11, otherwise, type is 0.
% If ret=0.0,  the function succeeds. 
% 
% The core of gssmex is GSS, which is an adaptive parallel direct solver. 
% Its adaptive computing technology will use both CPU and GPUs to get more performance. 
% The latest version is at http://www.grusoft.com/product/.  
%
% Copyright (c) 2005-2014 by Yingshi Chen. All Rights Reserved.  
% Any problem,contact gsp@grusoft.com.
%
help gssmex
error ('gssmex mexFunction not found') ;

