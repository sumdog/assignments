;; -*- mode: emacs-lisp; unibyte: t; -*-
;; cobol.el --- Define Cobol mode for Emacs
;; Copyright (C) 1992-2000  Ehud karni <ehud@unix.simonwiesel.co.il>

;; This file is NOT part of GNU Emacs, distribution conditions below.
;;
;;              EHUD   KARNI            ינרק   דוהא
;;              Ben Gurion st'   14   ןוירוג ןב 'חר
;;              Kfar - Sava    44 257     אבס - רפכ
;;              ===================================
;;              <kehud@iname.com>  972-(0)9-7659599
;;              ===================================

;;     RCS: $Id$
;;
;;     LOG: $Log$
;;  Revision 1.103  2000/03/05  14:31:30  ehud
;;  Comment headers changes (NOT GNU)  +  Drop `fse-like-parse' (never used)
;;
;;  Revision 1.102  1998/03/15  17:41:50  ehud
;;  Last revision for 19.34
;;
;;  Revision 1.101  1996/02/19  10:12:16  ehud
;;  Emacs 19.30 version
;;
;;  Revision 1.100  1995/01/19  17:11:58  ehud
;;  SW initial version control for all el's

;;  This program is free software; you can redistribute it and/or modify
;;  it under the terms of the GNU General Public License as published by
;;  the Free Software Foundation; either version 2 of the License, or
;;  (at your option) any later version.
;;
;;  This program is distributed in the hope that it will be useful,
;;  but WITHOUT ANY WARRANTY; without even the implied warranty of
;;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;  GNU General Public License for more details.
;;
;;  You should have received a copy of the GNU General Public License
;;  along with this program; if not, write to the Free Software
;;  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


"  Cobol  Special  parsing  (constants)  "

(require 'compile)

;; all 1 char shortnames must be in lower case,
;; all full names shoud be in UPPER case
;; when called: lower (UPPER) case char produce lower (UPPER) case full name
;; to add abbreviations do: (setq Alist (cons '(<chr> <full-name>) Alist))
;;     e.g. (setq cobol-data-alist (cons '(?d "DEFINE  ") cobol-data-alist))
;; The help will show the added words automaticly, to show them sorted do:
;;   (setq cobol-data-alist (cobol-sort-alist (cons '(?d "DEFINE  ") cobol-data-alist)))

(defconst cobol-data-alist
       '((?a  "ASSIGN  ")
         (?c  "  COMP-")
         (?f  "FILLER  ")
         (?i  "INDEXED  BY  ")
         (?j  "JUST  ")
         (?l  "LINE  ")
         (?n  "RENAMES  ")
         (?o  "OCCURS  ")
         (?p  "PIC  ")
         (?r  "REDEFINES  ")
         (?t  "THRU  ")
         (?u  "USING  ")
         (?v  "  VALUE  ")
         (?x  "PIC  X(00)")
         (?9  "PIC  9(00)")) "Cobol DATA DIVISION words alist")

(defconst cobol-proc-alist
       '((?a  "ACCEPT  ")
         (?b  "  BY  ")
         (?c  "COMPUTE  ")
         (?d  "DISPLAY  ")
         (?e  "ELSE  ")
         (?f  "  FROM  ")
         (?g  "GO  TO  ")
         (?i  "INSPECT  ")
         (?j  "SET  ")
         (?k  "  TO  TRUE")
         (?m  "MOVE  ")
         (?n  "NOT  ")
         (?p  "PERFORM  ")
         (?r  "ROUNDED  ")
         (?s  "  SECTION.")
         (?t  "  TO  ")
         (?u  "UNTIL  ")
         (?v  "VARYING  ")
         (?9  "99999"))        "Cobol PROCDEURE DIVISION words alist")


(defun cobol-sort-alist (Olist) "sort cobol-data-alist or cobol-proc-alist"
       (let (Nlist elm tlist ch1 chm   )
           (while Olist
               (setq chm -300)         ;dummy char (less than any real one)
               (setq tlist Olist)
               (while tlist
                   (setq ch1 (car (car tlist)))
                   (setq tlist (cdr tlist))
                   (if (> ch1 chm)
                       (setq chm ch1)))
               (setq elm (assoc chm Olist))
               (setq Olist (delq elm Olist))
               (setq Nlist (cons elm Nlist)))
           Nlist))


(defun parse-cobol () "Add cobol word according to double chars:
        1st char d - DATA word,   p - PROCEDURE word
if the 2nd char is unknown automatic help is provided" (interactive)
       (let ((char (read-char)))
           (cond
               ((= char ?d)
                   (parse-cobol-data))
               ((= char ?p)
                   (parse-cobol-proc))
               ((= 1 1)
                   (message "Cobol parsing not data (d) or proc (p)")))))


(defun parse-cobol-data () "Add 1 Cobol data division word"
  (interactive)
       (parse-cobol-div "data" cobol-data-alist))

(defun parse-cobol-proc () "Add 1 Cobol procedure division word"
  (interactive)
       (parse-cobol-div "procedure" cobol-proc-alist))


(defun parse-cobol-div (div words-alist)
  "Add word for Cobol DIV division, availble words are in WORDS-ALIST.
if the user typed char is unknown automatic help is provided"
       (let (char word chl)
           (while (not word)
               (message (format "Type 1 character for COBOL %s division " div))
               (setq char (read-char))
               (setq chl (downcase char))
               (setq word (assoc chl words-alist))
               (if (not word)
                   (cobol-help div words-alist)
                   (setq word (car (cdr word)))
                   (if (= chl char)
                       (setq word (downcase word)))
                   (put-string word)))))

(defun cobol-help (kot words-alist)
  "Help for cobol KOT division, availble words are in WORDS-ALIST."
       (if (string-equal (buffer-name) "*Help*")
           (other-window 1))
       (switch-to-buffer-other-window "*Help*")
       (delete-region (point-min) (point-max))
       (insert-string "  The  following  characters  are  availble  for  COBOL  data  division:\n")
       (let ((ix 0)
             (noc (/ (+ 2 (length words-alist)) 3))
             acw word lng)
           (while (< ix noc)
               (setq acw (nth ix words-alist))
               (setq word (car (cdr acw)))
               (setq lng  (- 17 (length word)))
               (insert-string (format "\n %c  =  \"%s\"%s" (car acw) word (make-string lng ? )))
               (setq acw (nth (+ ix noc) words-alist))
               (and acw
                   (setq word (car (cdr acw)))
                   (setq lng  (- 17 (length word)))
                   (insert-string (format " %c  =  \"%s\"%s" (car acw) word (make-string lng ? ))))
               (setq acw (nth (+ (+ ix noc) noc) words-alist))
               (and acw
                   (setq word (car (cdr acw)))
                   (insert-string (format " %c  =  \"%s\"" (car acw) word)))
               (setq ix (1+ ix))))
       (other-window 1))


(defun cobol-mode ()
  "Major mode for editing text intended for Cobol programs.
Turning on Cobol mode runs `text-mode-hook', then `cobol-mode-hook'."
  (interactive)
       (setq mode-name "Cobol")
       (setq major-mode 'cobol-mode)
       (run-hooks 'text-mode-hook 'cobol-mode-hook))


(defun cobol-1 () "set environment for Microfocus Cobol 1.3"
  (interactive)
       (setenv "COBDIR" "/usr/opt/mfcobol/mfcobol_1.3"))

(defun cobol-3 () "set environment for Microfocus Cobol 3.1"
  (interactive)
       (setenv "COBDIR" "/usr/opt/mfcobol3.1"))


(or (assoc "\\.cbl$" auto-mode-alist)
    (setq auto-mode-alist
          (cons '("\\.cbl$" . cobol-mode) auto-mode-alist)))

(or (assoc "\\.eco$" auto-mode-alist)
    (setq auto-mode-alist
          (cons '("\\.eco$" . cobol-mode) auto-mode-alist)))

(or (assoc "\\.cp[^.]*$" auto-mode-alist)
    (setq auto-mode-alist
          (cons '("\\.cp[^.]*$" . cobol-mode) auto-mode-alist)))

;; for error parsing by `next-error' - for MicroFocus errors list
(let ((rgxp "\n\\(.*\\.cbl\\) [ ]* \\([0-9]+\\) \\([0-9]+\\): "))
        (or (assoc rgxp compilation-error-regexp-alist)
            (setq compilation-error-regexp-alist (cons (list rgxp 1 2 3) compilation-error-regexp-alist))))

;;=================== end of cobol.el =======================
