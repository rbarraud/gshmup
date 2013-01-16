(define-module (gshmup shooter)
  #:use-module (gshmup core)
  #:export (init-shooter))

(define (init-shooter)
  (display "testing")
  (newline))

(add-hook! player-shoot-hook
           (lambda ()
             (let ((speed 15))
               (let ((p (player-position)))
                 (emit-bullet p speed 268)
                 (emit-bullet p speed 270)
                 (emit-bullet p speed 272)
                 (emit-bullet p speed 0)
                 (emit-bullet p speed 180))
               (let ((p (vector2-sub (player-position)
                                     (make-vector2 0 32))))
                 (emit-bullet p speed 268)
                 (emit-bullet p speed 270)
                 (emit-bullet p speed 272)))))
