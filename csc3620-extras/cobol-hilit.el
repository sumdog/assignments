;; -*- mode: emacs-lisp; unibyte: t; -*-
;; cobol-hilit.el is part of ekhilit.el

;; ekhilit.el --- added functions to hilit19 - mainly for cobol mode
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
;;  Revision 1.103  2000/03/05  14:35:52  ehud
;;  Comment headers changes (NOT GNU)  +  added CC and Newsgroups to messages
;;
;;  Revision 1.102  1998/11/11  12:07:04  ehud
;;  Add blue-under face, mode-patterns for messages, dired.
;;  Really last revision for 19.34.
;;
;;  Revision 1.101  1998/03/15  16:08:19  ehud
;;  Last revision for 19.34
;;
;;  Revision 1.100  1996/02/19  10:40:04  ehud
;;  Emacs 19.30 version (Initial RCS version)

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


(require 'hilit19)
(setq hilit-auto-highlight-maxout 40000)
(setq-default hilit-auto-rehighlight 45)
(setq hilit-auto-rehighlight-fallback '(10000 . 40))

;; for C & COBOL & others - change to whatever faces you want
(hilit-translate   label 'red      type 'purple-bold       const 'ForestGreen-italic
                   redef 'italic   extra 'modeline         cond 'ForestGreen
                   operator 'black-bold   url 'blue-under  msg-to 'blue-italic)


;; add cobol-mode =============================================================
(defconst Cobol-words '(
       "ACCEPT" "ACCESS" "ADD" "ADDRESS" "ADVANCING" "ADVANCING." "AND" "ARE"
       "ASCENDING" "ASSIGN" "AT"
       "BEGIN" "BLANK" "BLOCK" "BWZ" "BY"
       "CALL" "CANCEL" "CHAIN" "CLOSE" "COMMIT"
       "COMP" "COMP-1" "COMP-1." "COMP-2" "COMP-2." "COMP-3" "COMP-3." "COMP-4"
       "COMP-4." "COMP-5" "COMP-5." "COMP-6" "COMP-6." "COMP-X" "COMP-X." "COMP."
       "COMPUTATIONAL" "COMPUTATIONAL-1" "COMPUTATIONAL-1." "COMPUTATIONAL-2"
       "COMPUTATIONAL-2." "COMPUTATIONAL-3" "COMPUTATIONAL-3." "COMPUTATIONAL-4"
       "COMPUTATIONAL-4." "COMPUTATIONAL-5" "COMPUTATIONAL-5." "COMPUTATIONAL-6"
       "COMPUTATIONAL-6." "COMPUTATIONAL-X" "COMPUTATIONAL-X." "COMPUTATIONAL."
       "COMPUTE" "CONTENT" "CONTINUE" "CURRENT-DATE"
       "DELETE" "DELIMITED" "DEPENDING" "DESCENDING" "DISABLE" "DISK" "DISK."
       "DISPLAY" "DIVIDE" "DOWN"
       "ELSE" "ENABLE" "END" "END-ACCEPT" "END-ADD" "END-CALL" "END-DELETE"
       "END-DISPLAY" "END-DIVIDE" "END-EVALUATE" "END-EXEC" "END-EXEC." "END-IF"
       "END-MULTIPLY" "END-PERFORM" "END-READ" "END-RETURN" "END-REWRITE"
       "END-SEARCH" "END-START" "END-SUBTRACT" "END-WRITE" "ENTER" "ENTRY"
       "EVALUATE" "EXAMINE" "EXEC" "EXHIBIT" "EXIT" "EXIT." "EXTEND"
       "FALSE" "FALSE." "FILLER" "FROM"
       "GENERATE" "GIVING" "GO" "GOBACK"
       "I-O" "IF" "IN" "INDEXED" "INITIALIZE" "INITIATE" "INPUT" "INSPECT" "INTO"
       "INVALID" "IS"
       "JUST" "JUST." "JUSTIFIED" "JUSTIFIED."
       "KEY"
       "LABEL" "LEADING" "LEADING." "LINAGE" "LINE" "LINES" "LOCK"
       "MERGE" "MODE" "MOVE" "MULTIPLY"
       "NEXT" "NO" "NOT" "NOTE" "NUMERIC"
       "OCCURS" "OF" "ON" "OPEN" "OR" "ORGANIZATION" "OUTPUT"
       "PERFORM" "PIC" "PICTURE" "POINTER" "POINTER." "PREVIOUS" "PURGE"
       "READ" "READY" "RECEIVE" "RECORD" "RECORDING" "REFERENCE" "RELEASE"
       "REPLACING" "RESET" "RETURN" "REWRITE" "ROLLBACK" "RUN"
       "SEARCH" "SELECT" "SEND" "SENTENCE" "SENTENCE." "SEPARATE" "SEPARATE."
       "SEQUENTIAL" "SEQUENTIAL." "SET" "SIGN" "SIZE" "SORT" "START" "STOP" "STRING"
       "SUBTRACT" "SUPPRESS" "SYNC" "SYNC." "SYNCHRONIZED" "SYNCHRONIZED."
       "TALLYING" "TERMINATE" "TO" "TRACE" "TRANSFORM" "TRUE" "TRUE."
       "UNLOCK" "UNSTRING" "UNTIL" "UP" "UPON" "USAGE" "USE" "USING"
       "VALUE" "VARYING"
       "WHEN" "WITH" "WRITE"))

(defun words-list-build-vector (words-list)
  "add vector of 0 1 to WORDS-LIST as the last element"
;;     (message "words-list-build-vector called")
       (let* ((wrd-lst (symbol-value words-list))
              (lng (length wrd-lst))
              (vc (make-string 729 ? ))            ;A-Z * A-Z (27*27=729)
              wrd ix)
           (while (> lng 0)                        ;do for each word
               (setq lng (1- lng))                 ;next element
               (setq wrd (nth lng wrd-lst))        ;get word
               (setq ix (+ (* 27 (aref wrd 0)) (aref wrd 1) -1820))  ;get index -(?A*27+?A)
               (aset vc ix ?1))                    ;set must check value
           (set words-list (append wrd-lst (list vc)))))   ;add as last word


(defun ekhilit-search-word (words-list)
  "looks for next cobol reservd word and returns (start . end) or NIL.
the words must be whitespace delimeted.
The words in the list must be in UPPER CASE ONLY and sorted so a binary search can be done.
The found string is always changed to upper case before compare is done"
       (let* ((wrd-lst (symbol-value words-list))
              (lng (length wrd-lst))
              (vct (nth (1- lng) wrd-lst))
              ix st en wrd lb ub)
           (if (= (length vct) 729)
               (setq lng (1- lng))
               (words-list-build-vector words-list)
               (setq vct (nth lng (symbol-value words-list))))
           (while (and (search-forward-regexp "[ \t][^ \t\n]" nil t)
                       (goto-char (setq st (1- (point))))                  ;start of word
                       (search-forward-regexp "[^ \t\n][ \t\n]" nil t)
                       (goto-char (setq en (1- (point))))                  ;end of word
                       (if (overlays-at st)
                           t                                               ;ignore word if overlay on
                           (setq wrd (upcase (buffer-substring st en)))    ;word (UPPER CASE)
                           (if (not (and (> (length wrd) 1)
                                         (setq ix (+ (* 27 (aref wrd 0)) (aref wrd 1) -1820))
                                         (>= ix 0)
                                         (< ix 729)
                                         (= (aref vct ix) ?1)))                        ;is the index " "
                               (setq wrd nil)                              ;not found in hash
                       ;;      (message "Inp word is |%s| (%d-%d)" wrd st en)
                               (setq lb 0)                                     ;lower bound
                               (setq ub lng)                                   ;upper bound
                               (while (> (- ub lb) 1)                          ;search until
                                   (setq ix (/ (+ lb ub) 2))                   ;current index
                                   (if (string< wrd (nth ix (symbol-value words-list)))
                                       (setq ub ix)                            ;less, set upper bound
                                       (setq lb ix)))                          ;>=, set lower bound
                               (if (string= wrd (nth lb (symbol-value words-list)))    ;found !!!
                                   (setq wrd (cons st en))                     ;word to return
                                   (setq wrd nil)))                            ;not cobol word
                           (not wrd))))                                    ;negate found switch
           wrd))                                                           ;return cons or nil


(hilit-set-mode-patterns
 'cobol-mode
 '(("^......\\*.*$" nil comment)
   ("\\('[^'\n]*'\\|\"[^\"\n]*\"\\|\\([ \t]\\(\\(HIGH\\|LOW\\)-VALUE\\)\\|QUOTE\\|ZERO\\)[S]?[. \t\n]\\)"              nil string)      ;;' ', " " & Figurative constants
   ("[ \t]+COPY[ \t]+.*$" nil include)
   ("\\([+=()*/<>,:]\\|[ \t]-[ \t\n]\\)" nil operator)     ;; - must be soraunded by spaces
   ("^...... [ \t]*\\(66[ \t]+[^ \t]+[ \t]+RENAMES\\|[0-5]?[0-9][ \t]+[^ \t]+[ \t]+REDEFINES\\)[ \t]+.*$" nil redef)             ;;renames/redefines
   ("^...... [ \t]*\\(01\\|77\\|FD\\|CD\\|RD\\|FD\\|SD\\)[ \t]+[^ \t]*" nil defun)     ;;data division
   ("^......\\([ \t]\\|  \\|   \\|    \\)[^ \t]+[ \t]+SECTION.*$" nil defun)           ;;procedure division
   ("^......\\([ \t]\\|  \\|   \\|    \\)[^ \t]+[.][ \t\n]" nil redef)                 ;;paragraph name
   ("^...... [ \t]*\\([1-4][0-9]\\|0+[2-9]\\)[ \t]+" nil define)
   ("^......[ \t]+78[ \t]+[^ ]+[ \t]+VALUE[ \t]+.*$" nil const)                        ;;78 values
   ("^......[ \t]+88[ \t]+[^ ]+[ \t]+VALUE[ \t]+.*$" nil cond)                         ;;88 values
   ("[ \t]FUNCTION[ \t]+\\(ACOS\\|ANNUITY\\|ASIN\\|ATAN\\|CHAR\\|COS\\|DATE-OF-INTEGER\\|DAY-OF-INTEGER\\|FACTORIAL\\|INTEGER\\|INTEGER-OF-DATE\\|INTEGER-OF-DAY\\|INTEGER-PART\\|LENGTH\\|LOG\\|LOG10\\|LOWER-CASE\\|MAX\\|MEAN\\|MEDIAN\\|MIDRANGE\\|MIN\\|MOD\\|NUMVAL\\|NUMVAL-C\\|ORD\\|ORD-MAX\\|ORD-MIN\\|PRESENT-VALUE\\|RANDOM\\|RANGE\\|REM\\|REVERSE\\|SIN\\|SQRT\\|STANDARD-DEVIATION\\|SUM\\|TAN\\|UPPER-CASE\\|VARIANCE\\|WHEN-COMPILED\\)[ \t]+(" nil extra)
   (ekhilit-search-word Cobol-words keyword)                                   ;;all reserved cobol words
   )
 nil 'case-insensitive)

;;===================== end of ek-hilit ===================================
