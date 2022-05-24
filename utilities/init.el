(setq inhibit-startup-message t) ; removes welcome buffer

(scroll-bar-mode -1) ; Disable visible scrollbar
; (tool-bar-mode -1)   ; Disable the toolbar
(tooltip-mode -1)    ; Disable tooltips
(set-fringe-mode 10)
;(menu-bar-mode -1)   ; Disable the menu bar

(setq visible-bell t) ; Disables bell sound, adds screen flash

(set-face-attribute 'default nil :font "Liberation Mono" :height 140)

(load-theme 'tango-dark) ; Dark theme

;(split-window-right) Splits window in start up

(global-hl-line-mode) ; Highlights current line in buffer

(set-frame-parameter (selected-frame) 'fullscreen 'maximized) ; Defaults fullscreen in start-up
(set-cursor-color "blue")
(blink-cursor-mode -1) ;Cursor doesn't blink anymore.

; Adds line and column numbers
(line-number-mode 1)
(global-display-line-numbers-mode 1)
(column-number-mode 1)

; Sets tab size
(setq-default tab-width 4)

; C-style								 
(setq c-default-style "linux")
(setq c-basic-offset 4)
g(add-hook 'c-mode-common-hook
          (lambda ()
             (c-set-offset 'case-label '+)))

;; Make ESC quit prompts
(global-set-key (kbd "<escape>") 'keyboard-escape-quit)

; Sets different backup directory
(setq backup-directory-alist `(("." . "~/.saves")))

;Set default folder mainly for file visit purposes
(setq default-directory "c:/Projects/")
