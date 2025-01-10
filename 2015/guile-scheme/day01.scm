(add-to-load-path "./2015/guile-scheme/lib/")

(use-modules
 (utils)
 (srfi srfi-64))

(define (part-one input-str)
  (- (string-count input-str #\()
     (string-count input-str #\))))

(define (part-two input-str)
  (let loop ([i 0] [str input-str] [acc 0])
    (if (< acc 0)
        i
        (let ((front (string-take str 1)) (back (string-drop str 1)))
          (if (string=? front "(")
              (loop (+ 1 i) back (+ 1 acc))
              (loop (+ 1 i) back (- acc 1)))))))

(let ([input-str (read-all-lines "./2015/inputs/day01.txt")])
  (display
   (string-append "Part 1: " (number->string (part-one input-str)) "\n"))
  (display
   (string-append "Part 2: " (number->string (part-two input-str)) "\n")))
(newline)
(newline)

(test-begin "day01-test")

(test-eq "zero"
  0
  (part-one "(())"))

(test-eq "zero-again"
  0
  (part-one "()()"))

(test-eq "part-two-one"
  1
  (part-two ")"))

(test-eq "part-two-five"
  5
  (part-two "()())"))

(test-end "day01-test")
