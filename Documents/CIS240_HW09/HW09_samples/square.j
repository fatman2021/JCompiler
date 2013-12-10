;;
;; Simple j program
;;

defun square ; called with parameter n
3 pick ;  n
dup *  ; (n*n)
return

defun main
4 square printnum endl ; print 4 squared
5 square printnum endl ; print 5 squared
return