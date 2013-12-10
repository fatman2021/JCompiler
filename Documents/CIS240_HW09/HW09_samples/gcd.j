;;
;; gcd - Compute the greatest common divisor of two numbers using the Eucldiean algorithm
;;

defun gcd  ;  b, a
4 pick 	   ;  b, a, RV, RA, FP, b
0 eq   	   ;  b, a, RV, RA, FP, (b == 0)
if   
3 pick     ;  b, a, RV, RA, FP, a
else
4 pick	   ;  b, a, RV, RA, FP, b
4 pick 	   ;  b, a, RV, RA, FP, b, a
% 	   ;  b, a, RV, RA, FP, (a % b)
5 pick 	   ;  b, a, RV, RA, FP, (a % b), b
gcd        ;  b, a, RV, RA, FP, (a % b), b, gcd(a,b)
endif
return


;;
;; main function - note that this calls 2 procedures, printnum and endl that are
;; actually written in C
;;

defun main
462 1071 gcd printnum endl ; print the gcd of 1071 and 462 which should be 21
return