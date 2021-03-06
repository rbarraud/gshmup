(define-module (gshmup init)
  #:use-module (gshmup core)
  #:use-module (gshmup shooter))

(set! *debug-mode* #f)
(set-asset-path '("data"))

;; Set preferred keybindings.
(bind-key 'up 'up)
(bind-key 'down 'down)
(bind-key 'left 'left)
(bind-key 'right 'right)
(bind-key 'shoot 'z)
(bind-key 'bomb 'x)
(bind-key 'start 'enter)

;; Splash screen settings
(set! *splash-screen-background* "splash_background.png")
(set! *splash-screen-title* "splash_title.png")

;; Player settings.
(set! *num-credits* 1)
(set! *lives-per-credit* 10)
(set! *player-speed* 3.5)
