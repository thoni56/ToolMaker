                                 T H E   V O C A B U L A R Y

T E R M I N A L S

  1.  EndOfText            =   1  (icost = 255, dcost = 255)
  2.  '('                  =   2  (icost = 1, dcost = 1)
  3.  ')'                  =   3  (icost = 1, dcost = 1)
  4.  ','                  =   4  (icost = 1, dcost = 1)
  5.  '='                  =   5  (icost = 1, dcost = 1)
  6.  '#'                  =   6  (icost = 1, dcost = 1)
  7.  '>'                  =   7  (icost = 1, dcost = 1)
  8.  '<'                  =   8  (icost = 1, dcost = 1)
  9.  '?'                  =   9  (icost = 1, dcost = 1)
 10.  '*'                  =  10  (icost = 1, dcost = 1)
 11.  '+'                  =  11  (icost = 1, dcost = 1)
 12.  '-'                  =  12  (icost = 1, dcost = 1)
 13.  '/'                  =  13  (icost = 1, dcost = 1)
 14.  '['                  =  14  (icost = 1, dcost = 1)
 15.  ']'                  =  15  (icost = 1, dcost = 1)
 16.  '{'                  =  16  (icost = 1, dcost = 1)
 17.  '}'                  =  17  (icost = 1, dcost = 1)
 18.  TEXT                 =  18  (icost = 1, dcost = 1)
 19.  '<='                 =  19  (icost = 1, dcost = 1)
 20.  'OR'                 =  20  (icost = 1, dcost = 1)
 21.  '>='                 =  21  (icost = 1, dcost = 1)
 22.  '?R'                 =  22  (icost = 1, dcost = 1)
 23.  '?V'                 =  23  (icost = 1, dcost = 1)
 24.  '%%('                =  24  (icost = 1, dcost = 1)
 25.  'AND'                =  25  (icost = 1, dcost = 1)
 26.  'NOT'                =  26  (icost = 1, dcost = 1)
 27.  '%%IF'               =  27  (icost = 1, dcost = 1)
 28.  '%%SET'              =  28  (icost = 1, dcost = 1)
 29.  '%%END'              =  29  (icost = 1, dcost = 1)
 30.  INTEGER              =  30  (icost = 1, dcost = 1)
 31.  '%%KEEP'             =  31  (icost = 1, dcost = 1)
 32.  '%%ESET'             =  32  (icost = 1, dcost = 1)
 33.  '%%ELSE'             =  33  (icost = 1, dcost = 1)
 34.  '%%LOOP'             =  34  (icost = 1, dcost = 1)
 35.  '%%ENDIF'            =  35  (icost = 1, dcost = 1)
 36.  '%%ELSIF'            =  36  (icost = 1, dcost = 1)
 37.  '%%BEGIN'            =  37  (icost = 1, dcost = 1)
 38.  '%%ENDLOOP'          =  38  (icost = 1, dcost = 1)
 39.  '%%MESSAGE'          =  39  (icost = 1, dcost = 1)
 40.  '%%INCLUDE'          =  40  (icost = 1, dcost = 1)
 41.  '%%PROCESS'          =  41  (icost = 1, dcost = 1)
 42.  QUOT_STRING          =  42  (icost = 1, dcost = 1)
 43.  '%%EINCLUDE'         =  43  (icost = 1, dcost = 1)
 44.  'IMP$SYSTEM'         =  44  (icost = 1, dcost = 1)
 45.  UNQUOT_STRING        =  45  (icost = 1, dcost = 1)


N O N   T E R M I N A L S

 46.  goal
 47.  term
 48.  ident
 49.  value
 50.  idents
 51.  factor
 52.  values
 53.  operand
 54.  literal
 55.  variable
 56.  statement
 57.  condition
 58.  else_part
 59.  file_name
 60.  index_opt
 61.  values_opt
 62.  expression
 63.  locals_opt
 64.  value_list
 65.  system_call
 66.  if_statement
 67.  set_statement
 68.  quoted_string
 69.  and_condition
 70.  not_condition
 71.  statements_opt
 72.  keep_statement
 73.  eset_statement
 74.  loop_statement
 75.  parameters_opt
 76.  unquoted_string
 77.  insert_statement
 78.  region_statement
 79.  eval_expressions
 80.  message_statement
 81.  include_statement
 82.  process_statement
 83.  einclude_statement
 84.  boolean_expression
 85.  quoted_string_tail
 86.  quoted_string_item
 87.  eval_expressions_opt
 88.  unquoted_string_item


A T T R I B U T E S

 89.  srcp
 90.  end
 91.  code
 92.  text
 93.  begin
 94.  ast
                               T H E   P R O D U C T I O N S

  1. goal = statements_opt 
          ;

  2. statements_opt = 
  3.                ! statements_opt statement 
                    ;

  4. statement = TEXT 
  5.           ! keep_statement 
  6.           ! insert_statement 
  7.           ! include_statement 
  8.           ! einclude_statement 
  9.           ! process_statement 
 10.           ! set_statement 
 11.           ! eset_statement 
 12.           ! message_statement 
 13.           ! if_statement 
 14.           ! region_statement 
 15.           ! loop_statement 
               ;

 16. keep_statement = '%%KEEP' 
                    ;

 17. set_statement = '%%SET' ident '(' values_opt ')' 
 18.               ! '%%SET' ident '(' ',' values_opt ')' 
                   ;

 19. eset_statement = '%%ESET' ident '(' eval_expressions_opt ')' 
 20.                ! '%%ESET' ident '(' ',' eval_expressions_opt ')' 
                    ;

 21. insert_statement = '%%(' expression ')' 
                      ;

 22. if_statement = '%%IF' '(' condition ')' statements_opt else_part 
                    '%%ENDIF' 
                  ;

 23. else_part = 
 24.           ! '%%ELSE' statements_opt 
 25.           ! '%%ELSIF' '(' condition ')' statements_opt else_part 
               ;

 26. loop_statement = '%%LOOP' '(' ident '<=' expression ')' statements_opt 
                      '%%ENDLOOP' '(' ident ')' 
 27.                ! '%%LOOP' '(' ident ',' variable ')' statements_opt 
                      '%%ENDLOOP' '(' ident ')' 
                    ;

 28. message_statement = '%%MESSAGE' '(' expression ')' 
                       ;

 29. region_statement = '%%BEGIN' '(' ident parameters_opt locals_opt ')' 
                        statements_opt '%%END' '(' ident ')' 
                      ;

 30. parameters_opt = 
 31.                ! '(' idents ')' 
                    ;

 32. locals_opt = 
 33.            ! ',' idents 
                ;

 34. include_statement = '%%INCLUDE' '(' ')' 
 35.                   ! '%%INCLUDE' '(' ident ')' 
 36.                   ! '%%INCLUDE' '(' quoted_string ')' 
 37.                   ! '%%INCLUDE' '(' ident '(' values_opt ')' ')' 
                       ;

 38. einclude_statement = '%%EINCLUDE' '(' ')' 
 39.                    ! '%%EINCLUDE' '(' ident ')' 
 40.                    ! '%%EINCLUDE' '(' quoted_string ')' 
 41.                    ! '%%EINCLUDE' '(' ident '(' eval_expressions_opt ')' 
                          ')' 
                        ;

 42. process_statement = '%%PROCESS' '(' file_name ')' 
 43.                   ! '%%PROCESS' '(' file_name ',' file_name ')' 
                       ;

 44. condition = and_condition 
 45.           ! condition 'OR' and_condition 
               ;

 46. and_condition = not_condition 
 47.               ! and_condition 'AND' not_condition 
                   ;

 48. not_condition = boolean_expression 
 49.               ! 'NOT' boolean_expression 
                   ;

 50. boolean_expression = expression '=' expression 
 51.                    ! expression '#' expression 
 52.                    ! expression '>' expression 
 53.                    ! expression '<' expression 
 54.                    ! expression '>=' expression 
 55.                    ! expression '<=' expression 
 56.                    ! variable '(' values_opt ')' 
 57.                    ! variable '(' '?R' ')' 
 58.                    ! variable '(' '?V' ')' 
 59.                    ! variable '(' '?' ')' 
 60.                    ! variable '(' '*' ')' 
 61.                    ! '(' condition ')' 
 62.                    ! system_call 
                        ;

 63. system_call = 'IMP$SYSTEM' '(' ident ',' ident ')' 
 64.             ! 'IMP$SYSTEM' '(' quoted_string ',' ident ')' 
                 ;

 65. eval_expressions_opt = 
 66.                      ! eval_expressions 
                          ;

 67. eval_expressions = expression 
 68.                  ! eval_expressions ',' expression 
                      ;

 69. expression = term 
 70.            ! expression '+' term 
 71.            ! expression '-' term 
                ;

 72. term = factor 
 73.      ! term '*' factor 
 74.      ! term '/' factor 
          ;

 75. factor = operand 
 76.        ! '-' factor 
            ;

 77. operand = quoted_string 
 78.         ! variable 
 79.         ! '(' expression ')' 
             ;

 80. variable = ident index_opt 
 81.          ! value_list index_opt 
              ;

 82. index_opt = 
 83.           ! '[' expression ']' 
               ;

 84. idents = ident 
 85.        ! idents ',' ident 
            ;

 86. ident = unquoted_string 
           ;

 87. unquoted_string = unquoted_string_item 
 88.                 ! unquoted_string unquoted_string_item 
                     ;

 89. unquoted_string_item = UNQUOT_STRING 
 90.                      ! INTEGER 
 91.                      ! insert_statement 
                          ;

 92. value_list = '{' values_opt '}' 
                ;

 93. values_opt = 
 94.            ! values 
                ;

 95. values = value 
 96.        ! values ',' value 
            ;

 97. value = literal 
 98.       ! unquoted_string 
           ;

 99. literal = quoted_string 
100.         ! value_list 
             ;

101. file_name = 
102.           ! quoted_string 
103.           ! unquoted_string 
               ;

104. quoted_string = QUOT_STRING quoted_string_tail 
                   ;

105. quoted_string_tail = 
106.                    ! quoted_string_tail quoted_string_item 
                        ;

107. quoted_string_item = QUOT_STRING 
108.                    ! insert_statement 
                        ;

