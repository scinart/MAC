(ql:quickload 'trivial-dump-core)

;; humidex = temperature + h
;; h = (0.5555)× (e - 10.0)
;; e = 6.11 × exp [5417.7530 × ((1/273.16) - (1/(dewpoint+273.16)))]

(defun main ()
  (loop for line = (read *standard-input* nil :eof) until (eq line 'E) do
       (let* ((TT (read))
	      (junk (read))
	      (DD (read))
	      (e (* 6.11 (exp (* 5417.7530 (- (/ 1 273.16)
					      (/ 1 (+ DD 273.16)))))))
	      (h (* 0.5555 (- e 10.0)))
	      (humidex (+ TT h)))
	 (format t "~A~%" humidex))))

(sb-ext:save-lisp-and-die "poj3299-cl"
			  :toplevel 'main
			  :executable t)


; (trivial-dump-core::sbcl-save-slime-and-die "poj3299-cl" #'MAIN)

