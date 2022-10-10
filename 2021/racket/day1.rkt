#lang racket

(define (all)

  (define (get-input)
    (with-input-from-file "../inputs/day1.txt"
      (λ ()
        (for/list ([l (in-lines)])
          (string->number (string-trim l))))))

  (define l (get-input))

  (define l2 (list-tail l 1))
  (define l3 (list-tail l2 1))
  (define l4 (list-tail l3 1))

  (define a (for/sum ([i l]
                      [j l2])
              (if (> (- j i) 0) 1 0)))

  (define b (for/sum ([i l]
                      [j l2]
                      [k l3]
                      [m l4])
              (let ([w1 (+ (+ i j) k)]
                    [w2 (+ (+ j k) m)])
                (if (> (- w2 w1) 0) 1 0))))
  (cons a b))

(all)
