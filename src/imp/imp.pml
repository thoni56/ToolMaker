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
 27.  'MOD'                =  27  (icost = 1, dcost = 1)
 28.  '%%IF'               =  28  (icost = 1, dcost = 1)
 29.  '%%SET'              =  29  (icost = 1, dcost = 1)
 30.  '%%END'              =  30  (icost = 1, dcost = 1)
 31.  'BITOR'              =  31  (icost = 1, dcost = 1)
 32.  INTEGER              =  32  (icost = 1, dcost = 1)
 33.  '%%KEEP'             =  33  (icost = 1, dcost = 1)
 34.  '%%ESET'             =  34  (icost = 1, dcost = 1)
 35.  '%%ELSE'             =  35  (icost = 1, dcost = 1)
 36.  '%%LOOP'             =  36  (icost = 1, dcost = 1)
 37.  '%%EXIT'             =  37  (icost = 1, dcost = 1)
 38.  'BITAND'             =  38  (icost = 1, dcost = 1)
 39.  '%%ENDIF'            =  39  (icost = 1, dcost = 1)
 40.  '%%ELSIF'            =  40  (icost = 1, dcost = 1)
 41.  '%%BEGIN'            =  41  (icost = 1, dcost = 1)
 42.  '%%ENDLOOP'          =  42  (icost = 1, dcost = 1)
 43.  '%%MESSAGE'          =  43  (icost = 1, dcost = 1)
 44.  '%%INCLUDE'          =  44  (icost = 1, dcost = 1)
 45.  '%%PROCESS'          =  45  (icost = 1, dcost = 1)
 46.  QUOT_STRING          =  46  (icost = 1, dcost = 1)
 47.  '%%EINCLUDE'         =  47  (icost = 1, dcost = 1)
 48.  'IMP$SYSTEM'         =  48  (icost = 1, dcost = 1)
 49.  'IMP$STRLEN'         =  49  (icost = 1, dcost = 1)
 50.  UNQUOT_STRING        =  50  (icost = 1, dcost = 1)
 51.  'IMP$STRSEARCH'      =  51  (icost = 1, dcost = 1)


N O N   T E R M I N A L S

 52.  goal
 53.  term
 54.  ident
 55.  value
 56.  idents
 57.  factor
 58.  values
 59.  operand
 60.  literal
 61.  variable
 62.  statement
 63.  condition
 64.  else_list
 65.  else_part
 66.  file_name
 67.  index_opt
 68.  statements
 69.  values_opt
 70.  expression
 71.  elsif_list
 72.  locals_opt
 73.  value_list
 74.  system_call
 75.  stringmatch
 76.  if_statement
 77.  set_statement
 78.  quoted_string
 79.  and_condition
 80.  not_condition
 81.  statements_opt
 82.  keep_statement
 83.  eset_statement
 84.  loop_statement
 85.  exit_statement
 86.  parameters_opt
 87.  unquoted_string
 88.  insert_statement
 89.  region_statement
 90.  eval_expressions
 91.  message_statement
 92.  include_statement
 93.  process_statement
 94.  einclude_statement
 95.  boolean_expression
 96.  quoted_string_tail
 97.  quoted_string_item
 98.  eval_expressions_opt
 99.  unquoted_string_item


A T T R I B U T E S

100.  srcp
101.  end
102.  code
103.  text
104.  begin
105.  ast
106.  seq
107.  last
                               T H E   P R O D U C T I O N S

  1. goal = statements 
          ;

  2. statements = statements_opt 
                ;

  3. statements_opt = 
  4.                ! statements_opt statement 
                    ;

  5. statement = TEXT 
  6.           ! keep_statement 
  7.           ! insert_statement 
  8.           ! include_statement 
  9.           ! einclude_statement 
 10.           ! process_statement 
 11.           ! set_statement 
 12.           ! eset_statement 
 13.           ! message_statement 
 14.           ! exit_statement 
 15.           ! if_statement 
 16.           ! region_statement 
 17.           ! loop_statement 
               ;

 18. keep_statement = '%%KEEP' 
                    ;

 19. set_statement = '%%SET' ident '(' values_opt ')' 
 20.               ! '%%SET' ident '(' ',' values_opt ')' 
                   ;

 21. eset_statement = '%%ESET' ident '(' eval_expressions_opt ')' 
 22.                ! '%%ESET' ident '(' ',' eval_expressions_opt ')' 
                    ;

 23. insert_statement = '%%(' expression ')' 
                      ;

 24. if_statement = '%%IF' '(' condition ')' statements else_list '%%ENDIF' 
                  ;

 25. else_list = else_part 
 26.           ! elsif_list else_part 
               ;

 27. elsif_list = '%%ELSIF' '(' condition ')' statements 
 28.            ! elsif_list '%%ELSIF' '(' condition ')' statements 
                ;

 29. else_part = 
 30.           ! '%%ELSE' statements 
               ;

 31. loop_statement = '%%LOOP' '(' ident '<=' expression ')' statements 
                      '%%ENDLOOP' '(' ident ')' 
 32.                ! '%%LOOP' '(' ident ',' variable ')' statements 
                      '%%ENDLOOP' '(' ident ')' 
                    ;

 33. message_statement = '%%MESSAGE' '(' expression ')' 
                       ;

 34. region_statement = '%%BEGIN' '(' ident parameters_opt locals_opt ')' 
                        statements '%%END' '(' ident ')' 
                      ;

 35. parameters_opt = 
 36.                ! '(' idents ')' 
                    ;

 37. locals_opt = 
 38.            ! ',' idents 
                ;

 39. include_statement = '%%INCLUDE' '(' ')' 
 40.                   ! '%%INCLUDE' '(' ident ')' 
 41.                   ! '%%INCLUDE' '(' quoted_string ')' 
 42.                   ! '%%INCLUDE' '(' ident '(' values_opt ')' ')' 
                       ;

 43. einclude_statement = '%%EINCLUDE' '(' ')' 
 44.                    ! '%%EINCLUDE' '(' ident ')' 
 45.                    ! '%%EINCLUDE' '(' quoted_string ')' 
 46.                    ! '%%EINCLUDE' '(' ident '(' eval_expressions_opt ')' 
                          ')' 
                        ;

 47. process_statement = '%%PROCESS' '(' file_name ')' 
 48.                   ! '%%PROCESS' '(' file_name ',' file_name ')' 
                       ;

 49. exit_statement = '%%EXIT' '(' expression ',' expression ')' 
                    ;

 50. condition = and_condition 
 51.           ! condition 'OR' and_condition 
               ;

 52. and_condition = not_condition 
 53.               ! and_condition 'AND' not_condition 
                   ;

 54. not_condition = boolean_expression 
 55.               ! 'NOT' boolean_expression 
                   ;

 56. boolean_expression = expression '=' expression 
 57.                    ! expression '#' expression 
 58.                    ! expression '>' expression 
 59.                    ! expression '<' expression 
 60.                    ! expression '>=' expression 
 61.                    ! expression '<=' expression 
 62.                    ! variable '(' values_opt ')' 
 63.                    ! variable '(' '?R' ')' 
 64.                    ! variable '(' '?V' ')' 
 65.                    ! variable '(' '?' ')' 
 66.                    ! variable '(' '*' ')' 
 67.                    ! '(' condition ')' 
 68.                    ! system_call 
 69.                    ! stringmatch 
                        ;

 70. system_call = 'IMP$SYSTEM' '(' ident ',' ident ')' 
 71.             ! 'IMP$SYSTEM' '(' quoted_string ',' ident ')' 
                 ;

 72. stringmatch = 'IMP$STRSEARCH' '(' ident ',' ident ',' ident ')' 
 73.             ! 'IMP$STRSEARCH' '(' quoted_string ',' quoted_string ',' 
                   ident ')' 
 74.             ! 'IMP$STRSEARCH' '(' ident ',' quoted_string ',' ident ')' 
 75.             ! 'IMP$STRSEARCH' '(' quoted_string ',' ident ',' ident ')' 
                 ;

 76. eval_expressions_opt = 
 77.                      ! eval_expressions 
                          ;

 78. eval_expressions = expression 
 79.                  ! eval_expressions ',' expression 
                      ;

 80. expression = term 
 81.            ! expression '+' term 
 82.            ! expression '-' term 
 83.            ! expression 'BITAND' term 
 84.            ! expression 'BITOR' term 
                ;

 85. term = factor 
 86.      ! term '*' factor 
 87.      ! term '/' factor 
 88.      ! term 'MOD' factor 
          ;

 89. factor = operand 
 90.        ! '-' factor 
            ;

 91. operand = quoted_string 
 92.         ! variable 
 93.         ! '(' expression ')' 
 94.         ! 'IMP$STRLEN' '(' expression ')' 
             ;

 95. variable = ident index_opt 
 96.          ! value_list index_opt 
              ;

 97. index_opt = 
 98.           ! '[' expression ']' 
               ;

 99. idents = ident 
100.        ! idents ',' ident 
            ;

101. ident = unquoted_string 
102.       ! INTEGER 
           ;

103. unquoted_string = unquoted_string_item 
104.                 ! unquoted_string unquoted_string_item 
                     ;

105. unquoted_string_item = UNQUOT_STRING 
106.                      ! insert_statement 
                          ;

107. value_list = '{' values_opt '}' 
                ;

108. values_opt = 
109.            ! values 
                ;

110. values = value 
111.        ! values ',' value 
            ;

112. value = literal 
113.       ! unquoted_string 
           ;

114. literal = quoted_string 
115.         ! INTEGER 
116.         ! value_list 
117.         ! '-' literal 
             ;

118. file_name = 
119.           ! quoted_string 
120.           ! unquoted_string 
               ;

121. quoted_string = QUOT_STRING quoted_string_tail 
                   ;

122. quoted_string_tail = 
123.                    ! quoted_string_tail quoted_string_item 
                        ;

124. quoted_string_item = QUOT_STRING 
125.                    ! insert_statement 
                        ;

