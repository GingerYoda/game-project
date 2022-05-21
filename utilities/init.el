(setq inhibit-startup-message t) ; removes welcome buffer

(scroll-bar-mode -1) ; Disable visible scrollbar
(tool-bar-mode -1)   ; Disable the toolbar
(tooltip-mode -1)    ; Disable tooltips
(set-fringe-mode 10) ; Give some breathing space

(menu-bar-mode -1)   ; Disable the menu bar

(setq visible-bell t) ; Disables bell sound, adds screen flash

(set-face-attribute 'default nil :font "Liberation Mono" :height 140)

(load-theme 'tango-dark) ; Dark theme

;(split-window-right) Splits window in start up

(global-hl-line-mode) ; Highlights current line in buffer

(set-frame-parameter (selected-frame) 'fullscreen 'maximized) ; Defaults fullscreen in start-up

; Adds line and column numbers
(column-number-mode)
(display-line-numbers-mode)

; Sets tab size
(setq-default tab-width 4)

;; Make ESC quit prompts
(global-set-key (kbd "<escape>") 'keyboard-escape-quit)
