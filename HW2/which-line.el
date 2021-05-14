(defun which-line ()
  "Print the current line number (in the buffer) of point and the total number
of lines."
  (interactive)
  (save-restriction
    (widen)
    (save-excursion
      (beginning-of-line)
      (if (/= (char-before (point-max)) 10) ;if last char is not a newline
	  (message "Line %d of %d" (1+ (count-lines 1 (point))) (-(line-number-at-pos (point-max)) 1)) ;minus 1 from line number at max point (last line)
        (message "Line %d of %d" (1+ (count-lines 1 (point))) (line-number-at-pos (point-max))))))) ;else total line = line number at max point
