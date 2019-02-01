

                      Summary of the input process
                      ----------------------------

Grammar file name = pmk.pmk
Activated options = Recovery Single, Multiple, Panic;
Optimize Lr0;
Actionpack RDS;
Gotopack RDS;
List Grammar, Items, Tables, Statistics;
Resolve SR;
No Verbose;
Target 'ansi-c';
Escape '`';

Productions       = 98
Terminals         = 35
Non terminals     = 61
Attributes        = 19
Semantic actions  = 75

                                 T H E   V O C A B U L A R Y

T E R M I N A L S

  1.  EndOfText                 =   1  (icost = 255, dcost = 255)
  2.  IDENTIFIER                =   2  (icost = 1, dcost = 1)
  3.  STRING                    =   3  (icost = 1, dcost = 1)
  4.  ANG_BRACK_STRING          =   4  (icost = 1, dcost = 1)
  5.  INTEGER                   =   5  (icost = 1, dcost = 1)
  6.  '%%'                      =  99  (icost = 3, dcost = 2, => %%...%%)
  7.  '='                       = 100  (icost = 1, dcost = 1)
  8.  ';'                       = 101  (icost = 1, dcost = 1)
  9.  ','                       = 102  (icost = 1, dcost = 1)
 10.  '('                       = 103  (icost = 1, dcost = 1)
 11.  ')'                       = 104  (icost = 1, dcost = 1)
 12.  '!'                       = 105  (icost = 1, dcost = 1)
 13.  '|'                       = 106  (icost = 1, dcost = 1)
 14.  '{'                       = 107  (icost = 1, dcost = 1)
 15.  '}'                       = 108  (icost = 1, dcost = 1)
 16.  '['                       = 109  (icost = 1, dcost = 1)
 17.  ']'                       = 110  (icost = 1, dcost = 1)
 18.  '=>'                      = 111  (icost = 1, dcost = 1)
 19.  '%+'                      = 112  (icost = 1, dcost = 1)
 20.  '%-'                      = 113  (icost = 1, dcost = 1)
 21.  'META'                    = 114  (icost = 1, dcost = 1)
 22.  'SKIP'                    = 115  (icost = 1, dcost = 1)
 23.  '%%END'                   = 116  (icost = 1, dcost = 1)
 24.  '%%RULES'                 = 117  (icost = 1, dcost = 1)
 25.  'FIDUCIAL'                = 118  (icost = 1, dcost = 1)
 26.  '%%EXPORT'                = 119  (icost = 1, dcost = 1)
 27.  SKIPHEADER                = 120  (icost = 1, dcost = 1)
 28.  'SEPARATOR'               = 121  (icost = 1, dcost = 1)
 29.  '%%SCANNER'               = 122  (icost = 1, dcost = 1)
 30.  '%%RECOVERY'              = 123  (icost = 1, dcost = 1)
 31.  '%%TERMINALS'             = 124  (icost = 1, dcost = 1)
 32.  '%%ATTRIBUTES'            = 125  (icost = 1, dcost = 1)
 33.  '%%DECLARATIONS'          = 126  (icost = 1, dcost = 1)
 34.  '%%INSERTSYMBOL'          = 127  (icost = 1, dcost = 1)
 35.  '%%DELETESYMBOL'          = 128  (icost = 1, dcost = 1)


N O N   T E R M I N A L S

 36.  rhs
 37.  rule
 38.  rhss
 39.  rules
 40.  endOpt
 41.  symbol
 42.  action
 43.  terminal
 44.  skip_aux
 45.  modifier
 46.  attribute
 47.  meta_part
 48.  skip_part
 49.  meta_name
 50.  terminals
 51.  modifiers
 52.  __genSym#0
 53.  token_code
 54.  attributes
 55.  __genSym#1
 56.  <+red_aux>
 57.  <-red_aux>
 58.  insert_cost
 59.  delete_cost
 60.  nonterminal
 61.  pmk_document
 62.  skip_section
 63.  rule_section
 64.  print_symbol
 65.  recovery_aux
 66.  fiducial_aux
 67.  Alternatives
 68.  skip_sections
 69.  other_section
 70.  TERMINALS_aux
 71.  optional_decl
 72.  recovery_part
 73.  fiducial_part
 74.  separator_aux
 75.  other_sections
 76.  export_section
 77.  recovery_parts
 78.  separator_part
 79.  scanner_section
 80.  term_or_nonterm
 81.  meta_definition
 82.  repair_terminal
 83.  reduce_modifier
 84.  meta_definitions
 85.  symbol_or_action
 86.  attribute_section
 87.  symbols_or_actions
 88.  declaration_section
 89.  terminal_definition
 90.  error_recovery_data
 91.  reduce_not_modifier
 92.  insertsymbol_section
 93.  deletesymbol_section
 94.  terminal_definitions
 95.  error_handling_section
 96.  scanner_interface_section


A T T R I B U T E S

 97.  srcp
 98.  code
 99.  sval
100.  ival
101.  fpos
102.  length
103.  sval2
104.  q_str
105.  nullf
106.  icost
107.  dcost
108.  red_set
109.  rhslist
110.  nored_set
111.  altr_node
112.  altr_last
113.  rule_elnode
114.  rhslist_last
115.  rule_elnode_last
                               T H E   P R O D U C T I O N S

  1. pmk_document = skip_sections __genSym#0 other_sections 
                  ;

  2. __genSym#0 = 
                ;

  3. skip_sections = 
  4.               ! skip_sections skip_section 
                   ;

  5. other_sections = other_section 
  6.                ! other_sections other_section 
                    ;

  7. other_section = error_handling_section 
  8.               ! declaration_section 
  9.               ! export_section 
 10.               ! scanner_section 
 11.               ! insertsymbol_section 
 12.               ! deletesymbol_section 
 13.               ! attribute_section 
 14.               ! rule_section 
 15.               ! scanner_interface_section 
                   ;

 16. declaration_section = '%%DECLARATIONS' endOpt 
                         ;

 17. scanner_interface_section = TERMINALS_aux terminal_definitions endOpt 
                               ;

 18. TERMINALS_aux = '%%TERMINALS' 
                   ;

 19. terminal_definitions = terminal_definition 
 20.                      ! terminal_definitions terminal_definition 
                          ;

 21. terminal_definition = terminal '=' token_code error_recovery_data ';' 
                         ;

 22. terminal = symbol 
              ;

 23. symbol = term_or_nonterm 
 24.        ! STRING 
            ;

 25. term_or_nonterm = IDENTIFIER 
 26.                 ! ANG_BRACK_STRING 
                     ;

 27. token_code = INTEGER 
                ;

 28. error_recovery_data = 
 29.                     ! ',' insert_cost ',' delete_cost print_symbol 
                         ;

 30. insert_cost = 
 31.             ! INTEGER 
                 ;

 32. delete_cost = 
 33.             ! INTEGER 
                 ;

 34. print_symbol = 
 35.              ! '=>' terminal 
                  ;

 36. attribute_section = '%%ATTRIBUTES' attributes ';' endOpt 
                       ;

 37. attributes = attribute 
 38.            ! attributes ',' attribute 
                ;

 39. attribute = IDENTIFIER optional_decl 
               ;

 40. optional_decl = 
 41.               ! '%%' 
                   ;

 42. error_handling_section = recovery_aux recovery_parts endOpt 
                            ;

 43. recovery_aux = '%%RECOVERY' 
                  ;

 44. recovery_parts = 
 45.                ! recovery_parts recovery_part 
                    ;

 46. recovery_part = separator_part 
 47.               ! fiducial_part 
 48.               ! skip_part 
 49.               ! meta_part 
                   ;

 50. meta_part = 'META' meta_definitions 
               ;

 51. meta_definitions = meta_definition 
 52.                  ! meta_definitions meta_definition 
                      ;

 53. meta_definition = meta_name '=' '(' terminals ')' repair_terminal ';' 
                     ;

 54. meta_name = terminal 
               ;

 55. terminals = terminal 
 56.           ! terminals ',' terminal 
               ;

 57. repair_terminal = 
 58.                 ! '=>' terminal 
                     ;

 59. separator_part = separator_aux '(' terminals ')' ';' 
                    ;

 60. separator_aux = 'SEPARATOR' 
                   ;

 61. fiducial_part = fiducial_aux '(' terminals ')' ';' 
                   ;

 62. fiducial_aux = 'FIDUCIAL' 
                  ;

 63. skip_part = skip_aux '(' terminals ')' ';' 
               ;

 64. skip_aux = 'SKIP' 
              ;

 65. rule_section = '%%RULES' __genSym#1 rules endOpt 
                  ;

 66. __genSym#1 = 
                ;

 67. rules = rule 
 68.       ! rules rule 
           ;

 69. rule = nonterminal '=' rhss ';' 
          ;

 70. nonterminal = term_or_nonterm 
                 ;

 71. rhss = rhs 
 72.      ! rhss '!' rhs 
          ;

 73. rhs = symbols_or_actions modifiers 
         ;

 74. symbols_or_actions = 
 75.                    ! symbols_or_actions symbol_or_action 
                        ;

 76. Alternatives = modifiers symbols_or_actions modifiers 
 77.              ! Alternatives '|' modifiers symbols_or_actions modifiers 
                  ;

 78. symbol_or_action = symbol 
 79.                  ! '{' modifiers symbols_or_actions modifiers '}' 
 80.                  ! '[' modifiers symbols_or_actions modifiers ']' 
 81.                  ! '(' Alternatives ')' 
 82.                  ! modifiers action modifiers 
                      ;

 83. modifiers = 
 84.           ! modifiers modifier 
               ;

 85. modifier = reduce_modifier 
 86.          ! reduce_not_modifier 
              ;

 87. reduce_modifier = <+red_aux> '(' terminals ')' 
                     ;

 88. <+red_aux> = '%+' 
                ;

 89. reduce_not_modifier = <-red_aux> '(' terminals ')' 
                         ;

 90. <-red_aux> = '%-' 
                ;

 91. action = '%%' 
            ;

 92. export_section = '%%EXPORT' endOpt 
                    ;

 93. scanner_section = '%%SCANNER' endOpt 
                     ;

 94. insertsymbol_section = '%%INSERTSYMBOL' endOpt 
                          ;

 95. deletesymbol_section = '%%DELETESYMBOL' endOpt 
                          ;

 96. skip_section = SKIPHEADER endOpt 
                  ;

 97. endOpt = 
 98.        ! '%%END' 
            ;

                      L A L R ( 1 )  S E T S  O F  I T E M S



State:    1   !  Continuation: '%%RULES'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           R3 ! skip_sections --> .
              !                   {'%%RULES' '%%EXPORT' SKIPHEADER '%%SCANNER' 
              !                    '%%RECOVERY' '%%TERMINALS' '%%ATTRIBUTES' 
              !                    '%%DECLARATIONS' '%%INSERTSYMBOL' 
              !                    '%%DELETESYMBOL' }
            3 ! pmk_document --> .skip_sections __genSym#0 other_sections 
            2 ! Unknown --> .pmk_document 
            3 ! skip_sections --> .skip_sections skip_section 


State:    2   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           R0 ! Unknown --> pmk_document .
              !             {EndOfText }


State:    3   !  Continuation: '%%RULES'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           R2 ! __genSym#0 --> .
              !                {'%%RULES' '%%EXPORT' '%%SCANNER' '%%RECOVERY' 
              !                 '%%TERMINALS' '%%ATTRIBUTES' '%%DECLARATIONS' 
              !                 '%%INSERTSYMBOL' '%%DELETESYMBOL' }
          SR4 ! skip_sections --> skip_sections .skip_section 
            4 ! pmk_document --> skip_sections .__genSym#0 other_sections 
           85 ! skip_section --> .SKIPHEADER endOpt 


State:    4   !  Continuation: '%%RECOVERY'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            5 ! pmk_document --> skip_sections __genSym#0 .other_sections 
          SR5 ! other_sections --> .other_section 
          SR7 ! other_section --> .error_handling_section 
            6 ! error_handling_section --> .recovery_aux recovery_parts endOpt 
         SR43 ! recovery_aux --> .'%%RECOVERY' 
          SR8 ! other_section --> .declaration_section 
           30 ! declaration_section --> .'%%DECLARATIONS' endOpt 
          SR9 ! other_section --> .export_section 
           31 ! export_section --> .'%%EXPORT' endOpt 
         SR10 ! other_section --> .scanner_section 
           32 ! scanner_section --> .'%%SCANNER' endOpt 
         SR11 ! other_section --> .insertsymbol_section 
           33 ! insertsymbol_section --> .'%%INSERTSYMBOL' endOpt 
         SR12 ! other_section --> .deletesymbol_section 
           34 ! deletesymbol_section --> .'%%DELETESYMBOL' endOpt 
         SR13 ! other_section --> .attribute_section 
           35 ! attribute_section --> .'%%ATTRIBUTES' attributes ';' endOpt 
         SR14 ! other_section --> .rule_section 
           40 ! rule_section --> .'%%RULES' __genSym#1 rules endOpt 
         SR15 ! other_section --> .scanner_interface_section 
           74 ! scanner_interface_section --> .TERMINALS_aux 
              !                               terminal_definitions endOpt 
         SR18 ! TERMINALS_aux --> .'%%TERMINALS' 
            5 ! other_sections --> .other_sections other_section 


State:    5   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           R1 ! pmk_document --> skip_sections __genSym#0 other_sections .
              !                  {EndOfText }
          SR6 ! other_sections --> other_sections .other_section 
          SR7 ! other_section --> .error_handling_section 
            6 ! error_handling_section --> .recovery_aux recovery_parts endOpt 
         SR43 ! recovery_aux --> .'%%RECOVERY' 
          SR8 ! other_section --> .declaration_section 
           30 ! declaration_section --> .'%%DECLARATIONS' endOpt 
          SR9 ! other_section --> .export_section 
           31 ! export_section --> .'%%EXPORT' endOpt 
         SR10 ! other_section --> .scanner_section 
           32 ! scanner_section --> .'%%SCANNER' endOpt 
         SR11 ! other_section --> .insertsymbol_section 
           33 ! insertsymbol_section --> .'%%INSERTSYMBOL' endOpt 
         SR12 ! other_section --> .deletesymbol_section 
           34 ! deletesymbol_section --> .'%%DELETESYMBOL' endOpt 
         SR13 ! other_section --> .attribute_section 
           35 ! attribute_section --> .'%%ATTRIBUTES' attributes ';' endOpt 
         SR14 ! other_section --> .rule_section 
           40 ! rule_section --> .'%%RULES' __genSym#1 rules endOpt 
         SR15 ! other_section --> .scanner_interface_section 
           74 ! scanner_interface_section --> .TERMINALS_aux 
              !                               terminal_definitions endOpt 
         SR18 ! TERMINALS_aux --> .'%%TERMINALS' 


State:    6   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R44 ! recovery_parts --> .
              !                    {EndOfText 'META' 'SKIP' '%%END' '%%RULES' 
              !                     'FIDUCIAL' '%%EXPORT' 'SEPARATOR' 
              !                     '%%SCANNER' '%%RECOVERY' '%%TERMINALS' 
              !                     '%%ATTRIBUTES' '%%DECLARATIONS' 
              !                     '%%INSERTSYMBOL' '%%DELETESYMBOL' }
            7 ! error_handling_section --> recovery_aux .recovery_parts endOpt 
            7 ! recovery_parts --> .recovery_parts recovery_part 


State:    7   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R97 ! endOpt --> .
              !            {EndOfText '%%RULES' '%%EXPORT' '%%SCANNER' 
              !             '%%RECOVERY' '%%TERMINALS' '%%ATTRIBUTES' 
              !             '%%DECLARATIONS' '%%INSERTSYMBOL' '%%DELETESYMBOL' }
         SR45 ! recovery_parts --> recovery_parts .recovery_part 
         SR42 ! error_handling_section --> recovery_aux recovery_parts .endOpt 
         SR98 ! endOpt --> .'%%END' 
         SR46 ! recovery_part --> .separator_part 
            8 ! separator_part --> .separator_aux '(' terminals ')' ';' 
         SR60 ! separator_aux --> .'SEPARATOR' 
         SR47 ! recovery_part --> .fiducial_part 
           13 ! fiducial_part --> .fiducial_aux '(' terminals ')' ';' 
         SR62 ! fiducial_aux --> .'FIDUCIAL' 
         SR48 ! recovery_part --> .skip_part 
           17 ! skip_part --> .skip_aux '(' terminals ')' ';' 
         SR64 ! skip_aux --> .'SKIP' 
         SR49 ! recovery_part --> .meta_part 
           21 ! meta_part --> .'META' meta_definitions 


State:    8   !  Continuation: '('
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            9 ! separator_part --> separator_aux .'(' terminals ')' ';' 


State:    9   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           10 ! separator_part --> separator_aux '(' .terminals ')' ';' 
         SR55 ! terminals --> .terminal 
         SR22 ! terminal --> .symbol 
         SR23 ! symbol --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
         SR24 ! symbol --> .STRING 
           10 ! terminals --> .terminals ',' terminal 


State:   10   !  Continuation: ')'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           11 ! separator_part --> separator_aux '(' terminals .')' ';' 
           12 ! terminals --> terminals .',' terminal 


State:   11   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR59 ! separator_part --> separator_aux '(' terminals ')' .';' 


State:   12   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR56 ! terminals --> terminals ',' .terminal 
         SR22 ! terminal --> .symbol 
         SR23 ! symbol --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
         SR24 ! symbol --> .STRING 


State:   13   !  Continuation: '('
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           14 ! fiducial_part --> fiducial_aux .'(' terminals ')' ';' 


State:   14   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           15 ! fiducial_part --> fiducial_aux '(' .terminals ')' ';' 
         SR55 ! terminals --> .terminal 
         SR22 ! terminal --> .symbol 
         SR23 ! symbol --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
         SR24 ! symbol --> .STRING 
           15 ! terminals --> .terminals ',' terminal 


State:   15   !  Continuation: ')'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           16 ! fiducial_part --> fiducial_aux '(' terminals .')' ';' 
           12 ! terminals --> terminals .',' terminal 


State:   16   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR61 ! fiducial_part --> fiducial_aux '(' terminals ')' .';' 


State:   17   !  Continuation: '('
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           18 ! skip_part --> skip_aux .'(' terminals ')' ';' 


State:   18   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           19 ! skip_part --> skip_aux '(' .terminals ')' ';' 
         SR55 ! terminals --> .terminal 
         SR22 ! terminal --> .symbol 
         SR23 ! symbol --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
         SR24 ! symbol --> .STRING 
           19 ! terminals --> .terminals ',' terminal 


State:   19   !  Continuation: ')'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           20 ! skip_part --> skip_aux '(' terminals .')' ';' 
           12 ! terminals --> terminals .',' terminal 


State:   20   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR63 ! skip_part --> skip_aux '(' terminals ')' .';' 


State:   21   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           22 ! meta_part --> 'META' .meta_definitions 
         SR51 ! meta_definitions --> .meta_definition 
           23 ! meta_definition --> .meta_name '=' '(' terminals ')' 
              !                     repair_terminal ';' 
         SR54 ! meta_name --> .terminal 
         SR22 ! terminal --> .symbol 
         SR23 ! symbol --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
         SR24 ! symbol --> .STRING 
           22 ! meta_definitions --> .meta_definitions meta_definition 


State:   22   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R50 ! meta_part --> 'META' meta_definitions .
              !               {EndOfText 'META' 'SKIP' '%%END' '%%RULES' 
              !                'FIDUCIAL' '%%EXPORT' 'SEPARATOR' '%%SCANNER' 
              !                '%%RECOVERY' '%%TERMINALS' '%%ATTRIBUTES' 
              !                '%%DECLARATIONS' '%%INSERTSYMBOL' 
              !                '%%DELETESYMBOL' }
         SR52 ! meta_definitions --> meta_definitions .meta_definition 
           23 ! meta_definition --> .meta_name '=' '(' terminals ')' 
              !                     repair_terminal ';' 
         SR54 ! meta_name --> .terminal 
         SR22 ! terminal --> .symbol 
         SR23 ! symbol --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
         SR24 ! symbol --> .STRING 


State:   23   !  Continuation: '='
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           24 ! meta_definition --> meta_name .'=' '(' terminals ')' 
              !                     repair_terminal ';' 


State:   24   !  Continuation: '('
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           25 ! meta_definition --> meta_name '=' .'(' terminals ')' 
              !                     repair_terminal ';' 


State:   25   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           26 ! meta_definition --> meta_name '=' '(' .terminals ')' 
              !                     repair_terminal ';' 
         SR55 ! terminals --> .terminal 
         SR22 ! terminal --> .symbol 
         SR23 ! symbol --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
         SR24 ! symbol --> .STRING 
           26 ! terminals --> .terminals ',' terminal 


State:   26   !  Continuation: ')'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           27 ! meta_definition --> meta_name '=' '(' terminals .')' 
              !                     repair_terminal ';' 
           12 ! terminals --> terminals .',' terminal 


State:   27   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R57 ! repair_terminal --> .
              !                     {';' }
           28 ! meta_definition --> meta_name '=' '(' terminals ')' .
              !                     repair_terminal ';' 
           29 ! repair_terminal --> .'=>' terminal 


State:   28   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR53 ! meta_definition --> meta_name '=' '(' terminals ')' 
              !                     repair_terminal .';' 


State:   29   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR58 ! repair_terminal --> '=>' .terminal 
         SR22 ! terminal --> .symbol 
         SR23 ! symbol --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
         SR24 ! symbol --> .STRING 


State:   30   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R97 ! endOpt --> .
              !            {EndOfText '%%RULES' '%%EXPORT' '%%SCANNER' 
              !             '%%RECOVERY' '%%TERMINALS' '%%ATTRIBUTES' 
              !             '%%DECLARATIONS' '%%INSERTSYMBOL' '%%DELETESYMBOL' }
         SR16 ! declaration_section --> '%%DECLARATIONS' .endOpt 
         SR98 ! endOpt --> .'%%END' 


State:   31   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R97 ! endOpt --> .
              !            {EndOfText '%%RULES' '%%EXPORT' '%%SCANNER' 
              !             '%%RECOVERY' '%%TERMINALS' '%%ATTRIBUTES' 
              !             '%%DECLARATIONS' '%%INSERTSYMBOL' '%%DELETESYMBOL' }
         SR92 ! export_section --> '%%EXPORT' .endOpt 
         SR98 ! endOpt --> .'%%END' 


State:   32   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R97 ! endOpt --> .
              !            {EndOfText '%%RULES' '%%EXPORT' '%%SCANNER' 
              !             '%%RECOVERY' '%%TERMINALS' '%%ATTRIBUTES' 
              !             '%%DECLARATIONS' '%%INSERTSYMBOL' '%%DELETESYMBOL' }
         SR93 ! scanner_section --> '%%SCANNER' .endOpt 
         SR98 ! endOpt --> .'%%END' 


State:   33   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R97 ! endOpt --> .
              !            {EndOfText '%%RULES' '%%EXPORT' '%%SCANNER' 
              !             '%%RECOVERY' '%%TERMINALS' '%%ATTRIBUTES' 
              !             '%%DECLARATIONS' '%%INSERTSYMBOL' '%%DELETESYMBOL' }
         SR94 ! insertsymbol_section --> '%%INSERTSYMBOL' .endOpt 
         SR98 ! endOpt --> .'%%END' 


State:   34   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R97 ! endOpt --> .
              !            {EndOfText '%%RULES' '%%EXPORT' '%%SCANNER' 
              !             '%%RECOVERY' '%%TERMINALS' '%%ATTRIBUTES' 
              !             '%%DECLARATIONS' '%%INSERTSYMBOL' '%%DELETESYMBOL' }
         SR95 ! deletesymbol_section --> '%%DELETESYMBOL' .endOpt 
         SR98 ! endOpt --> .'%%END' 


State:   35   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           36 ! attribute_section --> '%%ATTRIBUTES' .attributes ';' endOpt 
         SR37 ! attributes --> .attribute 
           39 ! attribute --> .IDENTIFIER optional_decl 
           36 ! attributes --> .attributes ',' attribute 


State:   36   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           37 ! attribute_section --> '%%ATTRIBUTES' attributes .';' endOpt 
           38 ! attributes --> attributes .',' attribute 


State:   37   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R97 ! endOpt --> .
              !            {EndOfText '%%RULES' '%%EXPORT' '%%SCANNER' 
              !             '%%RECOVERY' '%%TERMINALS' '%%ATTRIBUTES' 
              !             '%%DECLARATIONS' '%%INSERTSYMBOL' '%%DELETESYMBOL' }
         SR36 ! attribute_section --> '%%ATTRIBUTES' attributes ';' .endOpt 
         SR98 ! endOpt --> .'%%END' 


State:   38   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR38 ! attributes --> attributes ',' .attribute 
           39 ! attribute --> .IDENTIFIER optional_decl 


State:   39   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R40 ! optional_decl --> .
              !                   {';' ',' }
         SR39 ! attribute --> IDENTIFIER .optional_decl 
         SR41 ! optional_decl --> .'%%' 


State:   40   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R66 ! __genSym#1 --> .
              !                {IDENTIFIER ANG_BRACK_STRING }
           41 ! rule_section --> '%%RULES' .__genSym#1 rules endOpt 


State:   41   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           42 ! rule_section --> '%%RULES' __genSym#1 .rules endOpt 
         SR67 ! rules --> .rule 
           43 ! rule --> .nonterminal '=' rhss ';' 
         SR70 ! nonterminal --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
           42 ! rules --> .rules rule 


State:   42   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R97 ! endOpt --> .
              !            {EndOfText '%%RULES' '%%EXPORT' '%%SCANNER' 
              !             '%%RECOVERY' '%%TERMINALS' '%%ATTRIBUTES' 
              !             '%%DECLARATIONS' '%%INSERTSYMBOL' '%%DELETESYMBOL' }
         SR68 ! rules --> rules .rule 
         SR65 ! rule_section --> '%%RULES' __genSym#1 rules .endOpt 
         SR98 ! endOpt --> .'%%END' 
           43 ! rule --> .nonterminal '=' rhss ';' 
         SR70 ! nonterminal --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 


State:   43   !  Continuation: '='
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           44 ! rule --> nonterminal .'=' rhss ';' 


State:   44   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R74 ! symbols_or_actions --> .
              !                        {IDENTIFIER STRING ANG_BRACK_STRING 
              !                         '%%' ';' '(' '!' '{' '[' '%+' '%-' }
         SR71 ! rhss --> .rhs 
           47 ! rhs --> .symbols_or_actions modifiers 
           45 ! rule --> nonterminal '=' .rhss ';' 
           47 ! symbols_or_actions --> .symbols_or_actions symbol_or_action 
           45 ! rhss --> .rhss '!' rhs 


State:   45   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR69 ! rule --> nonterminal '=' rhss .';' 
           46 ! rhss --> rhss .'!' rhs 


State:   46   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R74 ! symbols_or_actions --> .
              !                        {IDENTIFIER STRING ANG_BRACK_STRING 
              !                         '%%' ';' '(' '!' '{' '[' '%+' '%-' }
           47 ! rhs --> .symbols_or_actions modifiers 
         SR72 ! rhss --> rhss '!' .rhs 
           47 ! symbols_or_actions --> .symbols_or_actions symbol_or_action 


State:   47   !  Continuation: '%%'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R83 ! modifiers --> .
              !               {'%%' ';' '!' '%+' '%-' }
         SR75 ! symbols_or_actions --> symbols_or_actions .symbol_or_action 
           48 ! rhs --> symbols_or_actions .modifiers 
           48 ! modifiers --> .modifiers modifier 
         SR78 ! symbol_or_action --> .symbol 
         SR23 ! symbol --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
         SR24 ! symbol --> .STRING 
           57 ! symbol_or_action --> .'{' modifiers symbols_or_actions 
              !                      modifiers '}' 
           61 ! symbol_or_action --> .'[' modifiers symbols_or_actions 
              !                      modifiers ']' 
           65 ! symbol_or_action --> .'(' Alternatives ')' 
           48 ! symbol_or_action --> .modifiers action modifiers 


State:   48   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R73 ! rhs --> symbols_or_actions modifiers .
              !         {';' '!' }
         SR84 ! modifiers --> modifiers .modifier 
           49 ! symbol_or_action --> modifiers .action modifiers 
         SR85 ! modifier --> .reduce_modifier 
           51 ! reduce_modifier --> .<+red_aux> '(' terminals ')' 
         SR88 ! <+red_aux> --> .'%+' 
         SR86 ! modifier --> .reduce_not_modifier 
           54 ! reduce_not_modifier --> .<-red_aux> '(' terminals ')' 
         SR90 ! <-red_aux> --> .'%-' 
         SR91 ! action --> .'%%' 


State:   49   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R83 ! modifiers --> .
              !               {IDENTIFIER STRING ANG_BRACK_STRING '%%' ';' '(' 
              !                ')' '!' '|' '{' '}' '[' ']' '%+' '%-' }
           50 ! symbol_or_action --> modifiers action .modifiers 
           50 ! modifiers --> .modifiers modifier 

*******  Shift-Reduce conflict in state   50 Symbol: '%+' Production:   82
         Resolved by modification (Shift: '%+')
*******  Shift-Reduce conflict in state   50 Symbol: '%-' Production:   82
         Resolved by modification (Shift: '%-')

State:   50   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R82 ! symbol_or_action --> modifiers action modifiers .
              !                      {IDENTIFIER STRING ANG_BRACK_STRING '%%' 
              !                       ';' '(' ')' '!' '|' '{' '}' '[' ']' }
         SR84 ! modifiers --> modifiers .modifier 
         SR85 ! modifier --> .reduce_modifier 
           51 ! reduce_modifier --> .<+red_aux> '(' terminals ')' 
         SR88 ! <+red_aux> --> .'%+' 
         SR86 ! modifier --> .reduce_not_modifier 
           54 ! reduce_not_modifier --> .<-red_aux> '(' terminals ')' 
         SR90 ! <-red_aux> --> .'%-' 


State:   51   !  Continuation: '('
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           52 ! reduce_modifier --> <+red_aux> .'(' terminals ')' 


State:   52   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           53 ! reduce_modifier --> <+red_aux> '(' .terminals ')' 
         SR55 ! terminals --> .terminal 
         SR22 ! terminal --> .symbol 
         SR23 ! symbol --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
         SR24 ! symbol --> .STRING 
           53 ! terminals --> .terminals ',' terminal 


State:   53   !  Continuation: ')'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR87 ! reduce_modifier --> <+red_aux> '(' terminals .')' 
           12 ! terminals --> terminals .',' terminal 


State:   54   !  Continuation: '('
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           55 ! reduce_not_modifier --> <-red_aux> .'(' terminals ')' 


State:   55   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           56 ! reduce_not_modifier --> <-red_aux> '(' .terminals ')' 
         SR55 ! terminals --> .terminal 
         SR22 ! terminal --> .symbol 
         SR23 ! symbol --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
         SR24 ! symbol --> .STRING 
           56 ! terminals --> .terminals ',' terminal 


State:   56   !  Continuation: ')'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR89 ! reduce_not_modifier --> <-red_aux> '(' terminals .')' 
           12 ! terminals --> terminals .',' terminal 


State:   57   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R83 ! modifiers --> .
              !               {IDENTIFIER STRING ANG_BRACK_STRING '%%' '(' '{' 
              !                '}' '[' '%+' '%-' }
           58 ! symbol_or_action --> '{' .modifiers symbols_or_actions 
              !                      modifiers '}' 
           58 ! modifiers --> .modifiers modifier 

*******  Shift-Reduce conflict in state   58 Symbol: '%+' Production:   74
         Resolved by modification (Shift: '%+')
*******  Shift-Reduce conflict in state   58 Symbol: '%-' Production:   74
         Resolved by modification (Shift: '%-')

State:   58   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R74 ! symbols_or_actions --> .
              !                        {IDENTIFIER STRING ANG_BRACK_STRING 
              !                         '%%' '(' '{' '}' '[' }
         SR84 ! modifiers --> modifiers .modifier 
           59 ! symbol_or_action --> '{' modifiers .symbols_or_actions 
              !                      modifiers '}' 
           59 ! symbols_or_actions --> .symbols_or_actions symbol_or_action 
         SR85 ! modifier --> .reduce_modifier 
           51 ! reduce_modifier --> .<+red_aux> '(' terminals ')' 
         SR88 ! <+red_aux> --> .'%+' 
         SR86 ! modifier --> .reduce_not_modifier 
           54 ! reduce_not_modifier --> .<-red_aux> '(' terminals ')' 
         SR90 ! <-red_aux> --> .'%-' 


State:   59   !  Continuation: '%%'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R83 ! modifiers --> .
              !               {'%%' '}' '%+' '%-' }
         SR75 ! symbols_or_actions --> symbols_or_actions .symbol_or_action 
           60 ! symbol_or_action --> '{' modifiers symbols_or_actions .
              !                      modifiers '}' 
           60 ! modifiers --> .modifiers modifier 
         SR78 ! symbol_or_action --> .symbol 
         SR23 ! symbol --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
         SR24 ! symbol --> .STRING 
           57 ! symbol_or_action --> .'{' modifiers symbols_or_actions 
              !                      modifiers '}' 
           61 ! symbol_or_action --> .'[' modifiers symbols_or_actions 
              !                      modifiers ']' 
           65 ! symbol_or_action --> .'(' Alternatives ')' 
           60 ! symbol_or_action --> .modifiers action modifiers 


State:   60   !  Continuation: '}'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR79 ! symbol_or_action --> '{' modifiers symbols_or_actions 
              !                      modifiers .'}' 
         SR84 ! modifiers --> modifiers .modifier 
           49 ! symbol_or_action --> modifiers .action modifiers 
         SR85 ! modifier --> .reduce_modifier 
           51 ! reduce_modifier --> .<+red_aux> '(' terminals ')' 
         SR88 ! <+red_aux> --> .'%+' 
         SR86 ! modifier --> .reduce_not_modifier 
           54 ! reduce_not_modifier --> .<-red_aux> '(' terminals ')' 
         SR90 ! <-red_aux> --> .'%-' 
         SR91 ! action --> .'%%' 


State:   61   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R83 ! modifiers --> .
              !               {IDENTIFIER STRING ANG_BRACK_STRING '%%' '(' '{' 
              !                '[' ']' '%+' '%-' }
           62 ! symbol_or_action --> '[' .modifiers symbols_or_actions 
              !                      modifiers ']' 
           62 ! modifiers --> .modifiers modifier 

*******  Shift-Reduce conflict in state   62 Symbol: '%+' Production:   74
         Resolved by modification (Shift: '%+')
*******  Shift-Reduce conflict in state   62 Symbol: '%-' Production:   74
         Resolved by modification (Shift: '%-')

State:   62   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R74 ! symbols_or_actions --> .
              !                        {IDENTIFIER STRING ANG_BRACK_STRING 
              !                         '%%' '(' '{' '[' ']' }
         SR84 ! modifiers --> modifiers .modifier 
           63 ! symbol_or_action --> '[' modifiers .symbols_or_actions 
              !                      modifiers ']' 
           63 ! symbols_or_actions --> .symbols_or_actions symbol_or_action 
         SR85 ! modifier --> .reduce_modifier 
           51 ! reduce_modifier --> .<+red_aux> '(' terminals ')' 
         SR88 ! <+red_aux> --> .'%+' 
         SR86 ! modifier --> .reduce_not_modifier 
           54 ! reduce_not_modifier --> .<-red_aux> '(' terminals ')' 
         SR90 ! <-red_aux> --> .'%-' 


State:   63   !  Continuation: '%%'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R83 ! modifiers --> .
              !               {'%%' ']' '%+' '%-' }
         SR75 ! symbols_or_actions --> symbols_or_actions .symbol_or_action 
           64 ! symbol_or_action --> '[' modifiers symbols_or_actions .
              !                      modifiers ']' 
           64 ! modifiers --> .modifiers modifier 
         SR78 ! symbol_or_action --> .symbol 
         SR23 ! symbol --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
         SR24 ! symbol --> .STRING 
           57 ! symbol_or_action --> .'{' modifiers symbols_or_actions 
              !                      modifiers '}' 
           61 ! symbol_or_action --> .'[' modifiers symbols_or_actions 
              !                      modifiers ']' 
           65 ! symbol_or_action --> .'(' Alternatives ')' 
           64 ! symbol_or_action --> .modifiers action modifiers 


State:   64   !  Continuation: ']'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR80 ! symbol_or_action --> '[' modifiers symbols_or_actions 
              !                      modifiers .']' 
         SR84 ! modifiers --> modifiers .modifier 
           49 ! symbol_or_action --> modifiers .action modifiers 
         SR85 ! modifier --> .reduce_modifier 
           51 ! reduce_modifier --> .<+red_aux> '(' terminals ')' 
         SR88 ! <+red_aux> --> .'%+' 
         SR86 ! modifier --> .reduce_not_modifier 
           54 ! reduce_not_modifier --> .<-red_aux> '(' terminals ')' 
         SR90 ! <-red_aux> --> .'%-' 
         SR91 ! action --> .'%%' 


State:   65   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R83 ! modifiers --> .
              !               {IDENTIFIER STRING ANG_BRACK_STRING '%%' '(' ')' 
              !                '|' '{' '[' '%+' '%-' }
           71 ! Alternatives --> .modifiers symbols_or_actions modifiers 
           66 ! symbol_or_action --> '(' .Alternatives ')' 
           71 ! modifiers --> .modifiers modifier 
           66 ! Alternatives --> .Alternatives '|' modifiers 
              !                  symbols_or_actions modifiers 


State:   66   !  Continuation: ')'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR81 ! symbol_or_action --> '(' Alternatives .')' 
           67 ! Alternatives --> Alternatives .'|' modifiers 
              !                  symbols_or_actions modifiers 


State:   67   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R83 ! modifiers --> .
              !               {IDENTIFIER STRING ANG_BRACK_STRING '%%' '(' ')' 
              !                '|' '{' '[' '%+' '%-' }
           68 ! Alternatives --> Alternatives '|' .modifiers 
              !                  symbols_or_actions modifiers 
           68 ! modifiers --> .modifiers modifier 

*******  Shift-Reduce conflict in state   68 Symbol: '%+' Production:   74
         Resolved by modification (Shift: '%+')
*******  Shift-Reduce conflict in state   68 Symbol: '%-' Production:   74
         Resolved by modification (Shift: '%-')

State:   68   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R74 ! symbols_or_actions --> .
              !                        {IDENTIFIER STRING ANG_BRACK_STRING 
              !                         '%%' '(' ')' '|' '{' '[' }
         SR84 ! modifiers --> modifiers .modifier 
           69 ! Alternatives --> Alternatives '|' modifiers .
              !                  symbols_or_actions modifiers 
           69 ! symbols_or_actions --> .symbols_or_actions symbol_or_action 
         SR85 ! modifier --> .reduce_modifier 
           51 ! reduce_modifier --> .<+red_aux> '(' terminals ')' 
         SR88 ! <+red_aux> --> .'%+' 
         SR86 ! modifier --> .reduce_not_modifier 
           54 ! reduce_not_modifier --> .<-red_aux> '(' terminals ')' 
         SR90 ! <-red_aux> --> .'%-' 


State:   69   !  Continuation: '%%'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R83 ! modifiers --> .
              !               {'%%' ')' '|' '%+' '%-' }
         SR75 ! symbols_or_actions --> symbols_or_actions .symbol_or_action 
           70 ! Alternatives --> Alternatives '|' modifiers symbols_or_actions .
              !                  modifiers 
           70 ! modifiers --> .modifiers modifier 
         SR78 ! symbol_or_action --> .symbol 
         SR23 ! symbol --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
         SR24 ! symbol --> .STRING 
           57 ! symbol_or_action --> .'{' modifiers symbols_or_actions 
              !                      modifiers '}' 
           61 ! symbol_or_action --> .'[' modifiers symbols_or_actions 
              !                      modifiers ']' 
           65 ! symbol_or_action --> .'(' Alternatives ')' 
           70 ! symbol_or_action --> .modifiers action modifiers 


State:   70   !  Continuation: ')'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R77 ! Alternatives --> Alternatives '|' modifiers symbols_or_actions 
              !                  modifiers .
              !                  {')' '|' }
         SR84 ! modifiers --> modifiers .modifier 
           49 ! symbol_or_action --> modifiers .action modifiers 
         SR85 ! modifier --> .reduce_modifier 
           51 ! reduce_modifier --> .<+red_aux> '(' terminals ')' 
         SR88 ! <+red_aux> --> .'%+' 
         SR86 ! modifier --> .reduce_not_modifier 
           54 ! reduce_not_modifier --> .<-red_aux> '(' terminals ')' 
         SR90 ! <-red_aux> --> .'%-' 
         SR91 ! action --> .'%%' 

*******  Shift-Reduce conflict in state   71 Symbol: '%+' Production:   74
         Resolved by modification (Shift: '%+')
*******  Shift-Reduce conflict in state   71 Symbol: '%-' Production:   74
         Resolved by modification (Shift: '%-')

State:   71   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R74 ! symbols_or_actions --> .
              !                        {IDENTIFIER STRING ANG_BRACK_STRING 
              !                         '%%' '(' ')' '|' '{' '[' }
         SR84 ! modifiers --> modifiers .modifier 
           72 ! Alternatives --> modifiers .symbols_or_actions modifiers 
           72 ! symbols_or_actions --> .symbols_or_actions symbol_or_action 
         SR85 ! modifier --> .reduce_modifier 
           51 ! reduce_modifier --> .<+red_aux> '(' terminals ')' 
         SR88 ! <+red_aux> --> .'%+' 
         SR86 ! modifier --> .reduce_not_modifier 
           54 ! reduce_not_modifier --> .<-red_aux> '(' terminals ')' 
         SR90 ! <-red_aux> --> .'%-' 


State:   72   !  Continuation: '%%'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R83 ! modifiers --> .
              !               {'%%' ')' '|' '%+' '%-' }
         SR75 ! symbols_or_actions --> symbols_or_actions .symbol_or_action 
           73 ! Alternatives --> modifiers symbols_or_actions .modifiers 
           73 ! modifiers --> .modifiers modifier 
         SR78 ! symbol_or_action --> .symbol 
         SR23 ! symbol --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
         SR24 ! symbol --> .STRING 
           57 ! symbol_or_action --> .'{' modifiers symbols_or_actions 
              !                      modifiers '}' 
           61 ! symbol_or_action --> .'[' modifiers symbols_or_actions 
              !                      modifiers ']' 
           65 ! symbol_or_action --> .'(' Alternatives ')' 
           73 ! symbol_or_action --> .modifiers action modifiers 


State:   73   !  Continuation: ')'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R76 ! Alternatives --> modifiers symbols_or_actions modifiers .
              !                  {')' '|' }
         SR84 ! modifiers --> modifiers .modifier 
           49 ! symbol_or_action --> modifiers .action modifiers 
         SR85 ! modifier --> .reduce_modifier 
           51 ! reduce_modifier --> .<+red_aux> '(' terminals ')' 
         SR88 ! <+red_aux> --> .'%+' 
         SR86 ! modifier --> .reduce_not_modifier 
           54 ! reduce_not_modifier --> .<-red_aux> '(' terminals ')' 
         SR90 ! <-red_aux> --> .'%-' 
         SR91 ! action --> .'%%' 


State:   74   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           75 ! scanner_interface_section --> TERMINALS_aux .
              !                               terminal_definitions endOpt 
         SR19 ! terminal_definitions --> .terminal_definition 
           76 ! terminal_definition --> .terminal '=' token_code 
              !                         error_recovery_data ';' 
         SR22 ! terminal --> .symbol 
         SR23 ! symbol --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
         SR24 ! symbol --> .STRING 
           75 ! terminal_definitions --> .terminal_definitions 
              !                          terminal_definition 


State:   75   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R97 ! endOpt --> .
              !            {EndOfText '%%RULES' '%%EXPORT' '%%SCANNER' 
              !             '%%RECOVERY' '%%TERMINALS' '%%ATTRIBUTES' 
              !             '%%DECLARATIONS' '%%INSERTSYMBOL' '%%DELETESYMBOL' }
         SR20 ! terminal_definitions --> terminal_definitions .
              !                          terminal_definition 
         SR17 ! scanner_interface_section --> TERMINALS_aux 
              !                               terminal_definitions .endOpt 
         SR98 ! endOpt --> .'%%END' 
           76 ! terminal_definition --> .terminal '=' token_code 
              !                         error_recovery_data ';' 
         SR22 ! terminal --> .symbol 
         SR23 ! symbol --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
         SR24 ! symbol --> .STRING 


State:   76   !  Continuation: '='
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           77 ! terminal_definition --> terminal .'=' token_code 
              !                         error_recovery_data ';' 


State:   77   !  Continuation: INTEGER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           78 ! terminal_definition --> terminal '=' .token_code 
              !                         error_recovery_data ';' 
         SR27 ! token_code --> .INTEGER 


State:   78   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R28 ! error_recovery_data --> .
              !                         {';' }
           79 ! terminal_definition --> terminal '=' token_code .
              !                         error_recovery_data ';' 
           80 ! error_recovery_data --> .',' insert_cost ',' delete_cost 
              !                         print_symbol 


State:   79   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR21 ! terminal_definition --> terminal '=' token_code 
              !                         error_recovery_data .';' 


State:   80   !  Continuation: ','
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R30 ! insert_cost --> .
              !                 {',' }
           81 ! error_recovery_data --> ',' .insert_cost ',' delete_cost 
              !                         print_symbol 
         SR31 ! insert_cost --> .INTEGER 


State:   81   !  Continuation: ','
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           82 ! error_recovery_data --> ',' insert_cost .',' delete_cost 
              !                         print_symbol 


State:   82   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R32 ! delete_cost --> .
              !                 {';' '=>' }
           83 ! error_recovery_data --> ',' insert_cost ',' .delete_cost 
              !                         print_symbol 
         SR33 ! delete_cost --> .INTEGER 


State:   83   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R34 ! print_symbol --> .
              !                  {';' }
         SR29 ! error_recovery_data --> ',' insert_cost ',' delete_cost .
              !                         print_symbol 
           84 ! print_symbol --> .'=>' terminal 


State:   84   !  Continuation: IDENTIFIER
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR35 ! print_symbol --> '=>' .terminal 
         SR22 ! terminal --> .symbol 
         SR23 ! symbol --> .term_or_nonterm 
         SR25 ! term_or_nonterm --> .IDENTIFIER 
         SR26 ! term_or_nonterm --> .ANG_BRACK_STRING 
         SR24 ! symbol --> .STRING 


State:   85   !  Continuation: '%%RULES'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R97 ! endOpt --> .
              !            {'%%RULES' '%%EXPORT' SKIPHEADER '%%SCANNER' 
              !             '%%RECOVERY' '%%TERMINALS' '%%ATTRIBUTES' 
              !             '%%DECLARATIONS' '%%INSERTSYMBOL' '%%DELETESYMBOL' }
         SR96 ! skip_section --> SKIPHEADER .endOpt 
         SR98 ! endOpt --> .'%%END' 




                  T H E  P A R S E R  A C T I O N  T A B L E


  TOP OF STACK                                                           INPUT SYMBOL
STATE NAME                !  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35
--------------------------!---------------------------------------------------------------------------------------------------------
  1   Unknown             !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X R3  X R3 R3  X R3 R3 R3 R3 R3 R3 R3 
  2   pmk_document        !  A  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
  3   skip_sections       !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X R2  X R2 S85 X R2 R2 R2 R2 R2 R2 R2 
  4   __genSym#0          !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S40 * S31 *  * S32-43-18S35S30S33S34
  5   other_sections      ! R1  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X S40 X S31 X  X S32-43-18S35S30S33S34
  6   recovery_aux        ! R44 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X R44R44R44R44R44R44 X R44R44R44R44R44R44R44R44
  7   recovery_parts      ! R97 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S21-64-98R97-62R97 * -60R97R97R97R97R97R97R97
  8   separator_aux       !  X  X  X  X  X  X  X  X  X S9  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
  9   '('                 !  X -25-24-26 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 10   terminals           !  X  X  X  X  X  X  X  X S12 X S11 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 11   ')'                 !  X  X  X  X  X  X  X -59 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 12   ','                 !  X -25-24-26 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 13   fiducial_aux        !  X  X  X  X  X  X  X  X  X S14 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 14   '('                 !  X -25-24-26 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 15   terminals           !  X  X  X  X  X  X  X  X S12 X S16 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 16   ')'                 !  X  X  X  X  X  X  X -61 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 17   skip_aux            !  X  X  X  X  X  X  X  X  X S18 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 18   '('                 !  X -25-24-26 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 19   terminals           !  X  X  X  X  X  X  X  X S12 X S20 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 20   ')'                 !  X  X  X  X  X  X  X -63 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 21   'META'              !  X -25-24-26 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 22   meta_definitions    ! R50-25-24-26 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X R50R50R50R50R50R50 X R50R50R50R50R50R50R50R50
 23   meta_name           !  X  X  X  X  X  X S24 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 24   '='                 !  X  X  X  X  X  X  X  X  X S25 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 25   '('                 !  X -25-24-26 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 26   terminals           !  X  X  X  X  X  X  X  X S12 X S27 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 27   ')'                 !  X  X  X  X  X  X  X R57 X  X  X  X  X  X  X  X  X S29 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 28   repair_terminal     !  *  *  *  *  *  *  * -53 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 29   '=>'                !  X -25-24-26 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 30   '%%DECLARATIONS'    ! R97 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -98R97 X R97 X  X R97R97R97R97R97R97R97
 31   '%%EXPORT'          ! R97 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -98R97 X R97 X  X R97R97R97R97R97R97R97
 32   '%%SCANNER'         ! R97 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -98R97 X R97 X  X R97R97R97R97R97R97R97
 33   '%%INSERTSYMBOL'    ! R97 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -98R97 X R97 X  X R97R97R97R97R97R97R97
 34   '%%DELETESYMBOL'    ! R97 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -98R97 X R97 X  X R97R97R97R97R97R97R97
 35   '%%ATTRIBUTES'      !  X S39 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 36   attributes          !  X  X  X  X  X  X  X S37S38 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 37   ';'                 ! R97 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -98R97 X R97 X  X R97R97R97R97R97R97R97
 38   ','                 !  X S39 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 39   IDENTIFIER          !  X  X  X  X  X -41 X R40R40 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 40   '%%RULES'           !  X R66 X R66 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 41   __genSym#1          !  * -25 * -26 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 42   rules               ! R97-25 X -26 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -98R97 X R97 X  X R97R97R97R97R97R97R97
 43   nonterminal         !  X  X  X  X  X  X S44 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 44   '='                 !  X R74R74R74 X R74 X R74 X R74 X R74 X R74 X R74 X  X R74R74 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 45   rhss                !  X  X  X  X  X  X  X -69 X  X  X S46 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 46   '!'                 !  X R74R74R74 X R74 X R74 X R74 X R74 X R74 X R74 X  X R74R74 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 47   symbols_or_actions  !  * -25-24-26 * R83 * R83 * S65 * R83 * S57 * S61 *  * R83R83 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 48   modifiers           !  *  *  *  *  * -91 * R73 *  *  * R73 *  *  *  *  *  * -88-90 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 49   action              !  X R83R83R83 X R83 X R83 X R83R83R83R83R83R83R83R83 X R83R83 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 50   modifiers           !  * R82R82R82 * R82 * R82 * R82R82R82R82R82R82R82R82 * -88-90 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 51   <+red_aux>          !  X  X  X  X  X  X  X  X  X S52 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 52   '('                 !  X -25-24-26 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 53   terminals           !  X  X  X  X  X  X  X  X S12 X -87 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 54   <-red_aux>          !  X  X  X  X  X  X  X  X  X S55 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 55   '('                 !  X -25-24-26 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 56   terminals           !  X  X  X  X  X  X  X  X S12 X -89 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 57   '{'                 !  X R83R83R83 X R83 X  X  X R83 X  X  X R83R83R83 X  X R83R83 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 58   modifiers           !  * R74R74R74 * R74 *  *  * R74 *  *  * R74R74R74 *  * -88-90 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 59   symbols_or_actions  !  * -25-24-26 * R83 *  *  * S65 *  *  * S57R83S61 *  * R83R83 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 60   modifiers           !  *  *  *  *  * -91 *  *  *  *  *  *  *  * -79 *  *  * -88-90 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 61   '['                 !  X R83R83R83 X R83 X  X  X R83 X  X  X R83 X R83R83 X R83R83 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 62   modifiers           !  * R74R74R74 * R74 *  *  * R74 *  *  * R74 * R74R74 * -88-90 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 63   symbols_or_actions  !  * -25-24-26 * R83 *  *  * S65 *  *  * S57 * S61R83 * R83R83 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 64   modifiers           !  *  *  *  *  * -91 *  *  *  *  *  *  *  *  *  * -80 * -88-90 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 65   '('                 !  X R83R83R83 X R83 X  X  X R83R83 X R83R83 X R83 X  X R83R83 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 66   Alternatives        !  *  *  *  *  *  *  *  *  *  * -81 * S67 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 67   '|'                 !  X R83R83R83 X R83 X  X  X R83R83 X R83R83 X R83 X  X R83R83 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 68   modifiers           !  * R74R74R74 * R74 *  *  * R74R74 * R74R74 * R74 *  * -88-90 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 69   symbols_or_actions  !  * -25-24-26 * R83 *  *  * S65R83 * R83S57 * S61 *  * R83R83 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 70   modifiers           !  *  *  *  *  * -91 *  *  *  * R77 * R77 *  *  *  *  * -88-90 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 71   modifiers           !  * R74R74R74 * R74 *  *  * R74R74 * R74R74 * R74 *  * -88-90 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 72   symbols_or_actions  !  * -25-24-26 * R83 *  *  * S65R83 * R83S57 * S61 *  * R83R83 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 73   modifiers           !  *  *  *  *  * -91 *  *  *  * R76 * R76 *  *  *  *  * -88-90 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 74   TERMINALS_aux       !  X -25-24-26 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 75   terminal_definitions! R97-25-24-26 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -98R97 X R97 X  X R97R97R97R97R97R97R97
 76   terminal            !  X  X  X  X  X  X S77 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 77   '='                 !  X  X  X  X -27 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 78   token_code          !  X  X  X  X  X  X  X R28S80 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 79   error_recovery_data !  *  *  *  *  *  *  * -21 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 80   ','                 !  X  X  X  X -31 X  X  X R30 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 81   insert_cost         !  *  *  *  *  *  *  *  * S82 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 82   ','                 !  X  X  X  X -33 X  X R32 X  X  X  X  X  X  X  X  X R32 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 83   delete_cost         !  *  *  *  *  *  *  * R34 *  *  *  *  *  *  *  *  * S84 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 84   '=>'                !  X -25-24-26 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 85   SKIPHEADER          !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -98R97 X R97R97 X R97R97R97R97R97R97R97



                         T H E  G O T O  T A B L E


  TOP OF STACK                                                                                                     SYMBOL
STATE NAME                ! 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96
--------------------------!---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  1   Unknown             !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S2  *  *  *  *  *  * S3  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
  2   pmk_document        !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
  3   skip_sections       !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S4  *  *  *  *  *  *  *  *  * -4  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
  4   __genSym#0          !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -14 * S6  *  *  * -5 S74 *  *  *  * S5 -9  *  * -10 *  *  *  *  *  * -13 * -8  *  *  * -11-12 * -7 -15
  5   other_sections      !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -14 * S6  *  *  * -6 S74 *  *  *  *  * -9  *  * -10 *  *  *  *  *  * -13 * -8  *  *  * -11-12 * -7 -15
  6   recovery_aux        !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S7  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
  7   recovery_parts      !  *  *  *  * -42 *  *  * S17 *  * -49-48 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S13 *  *  *  *  * -45-47S8  *  *  * -46 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
  8   separator_aux       !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
  9   '('                 !  *  *  *  *  * -22 * -55 *  *  *  *  *  * S10 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -23 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 10   terminals           !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 11   ')'                 !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 12   ','                 !  *  *  *  *  * -22 * -56 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -23 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 13   fiducial_aux        !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 14   '('                 !  *  *  *  *  * -22 * -55 *  *  *  *  *  * S15 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -23 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 15   terminals           !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 16   ')'                 !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 17   skip_aux            !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 18   '('                 !  *  *  *  *  * -22 * -55 *  *  *  *  *  * S19 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -23 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 19   terminals           !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 20   ')'                 !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 21   'META'              !  *  *  *  *  * -22 * -54 *  *  *  *  * S23 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -23-51 *  * S22 *  *  *  *  *  *  *  *  *  *  *  * 
 22   meta_definitions    !  *  *  *  *  * -22 * -54 *  *  *  *  * S23 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -23-52 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 23   meta_name           !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 24   '='                 !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 25   '('                 !  *  *  *  *  * -22 * -55 *  *  *  *  *  * S26 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -23 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 26   terminals           !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 27   ')'                 !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S28 *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 28   repair_terminal     !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 29   '=>'                !  *  *  *  *  * -22 * -58 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -23 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 30   '%%DECLARATIONS'    !  *  *  *  * -16 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 31   '%%EXPORT'          !  *  *  *  * -92 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 32   '%%SCANNER'         !  *  *  *  * -93 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 33   '%%INSERTSYMBOL'    !  *  *  *  * -94 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 34   '%%DELETESYMBOL'    !  *  *  *  * -95 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 35   '%%ATTRIBUTES'      !  *  *  *  *  *  *  *  *  *  * -37 *  *  *  *  *  *  * S36 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 36   attributes          !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 37   ';'                 !  *  *  *  * -36 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 38   ','                 !  *  *  *  *  *  *  *  *  *  * -38 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 39   IDENTIFIER          !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -39 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 40   '%%RULES'           !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S41 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 41   __genSym#1          !  * -67 * S42 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S43 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -70 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 42   rules               !  * -68 *  * -65 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S43 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -70 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 43   nonterminal         !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 44   '='                 ! -71 * S45 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S47 *  *  *  *  *  *  *  *  * 
 45   rhss                !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 46   '!'                 ! -72 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S47 *  *  *  *  *  *  *  *  * 
 47   symbols_or_actions  !  *  *  *  *  * -78 *  *  *  *  *  *  *  *  * S48 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -23 *  *  *  * -75 *  *  *  *  *  *  *  *  *  *  * 
 48   modifiers           !  *  *  *  *  *  * S49 *  * -84 *  *  *  *  *  *  *  *  *  * S51S54 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -85 *  *  *  *  *  *  * -86 *  *  *  *  * 
 49   action              !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S50 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 50   modifiers           !  *  *  *  *  *  *  *  *  * -84 *  *  *  *  *  *  *  *  *  * S51S54 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -85 *  *  *  *  *  *  * -86 *  *  *  *  * 
 51   <+red_aux>          !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 52   '('                 !  *  *  *  *  * -22 * -55 *  *  *  *  *  * S53 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -23 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 53   terminals           !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 54   <-red_aux>          !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 55   '('                 !  *  *  *  *  * -22 * -55 *  *  *  *  *  * S56 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -23 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 56   terminals           !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 57   '{'                 !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S58 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 58   modifiers           !  *  *  *  *  *  *  *  *  * -84 *  *  *  *  *  *  *  *  *  * S51S54 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -85 *  *  * S59 *  *  * -86 *  *  *  *  * 
 59   symbols_or_actions  !  *  *  *  *  * -78 *  *  *  *  *  *  *  *  * S60 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -23 *  *  *  * -75 *  *  *  *  *  *  *  *  *  *  * 
 60   modifiers           !  *  *  *  *  *  * S49 *  * -84 *  *  *  *  *  *  *  *  *  * S51S54 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -85 *  *  *  *  *  *  * -86 *  *  *  *  * 
 61   '['                 !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S62 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 62   modifiers           !  *  *  *  *  *  *  *  *  * -84 *  *  *  *  *  *  *  *  *  * S51S54 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -85 *  *  * S63 *  *  * -86 *  *  *  *  * 
 63   symbols_or_actions  !  *  *  *  *  * -78 *  *  *  *  *  *  *  *  * S64 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -23 *  *  *  * -75 *  *  *  *  *  *  *  *  *  *  * 
 64   modifiers           !  *  *  *  *  *  * S49 *  * -84 *  *  *  *  *  *  *  *  *  * S51S54 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -85 *  *  *  *  *  *  * -86 *  *  *  *  * 
 65   '('                 !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S71 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S66 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 66   Alternatives        !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 67   '|'                 !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S68 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 68   modifiers           !  *  *  *  *  *  *  *  *  * -84 *  *  *  *  *  *  *  *  *  * S51S54 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -85 *  *  * S69 *  *  * -86 *  *  *  *  * 
 69   symbols_or_actions  !  *  *  *  *  * -78 *  *  *  *  *  *  *  *  * S70 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -23 *  *  *  * -75 *  *  *  *  *  *  *  *  *  *  * 
 70   modifiers           !  *  *  *  *  *  * S49 *  * -84 *  *  *  *  *  *  *  *  *  * S51S54 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -85 *  *  *  *  *  *  * -86 *  *  *  *  * 
 71   modifiers           !  *  *  *  *  *  *  *  *  * -84 *  *  *  *  *  *  *  *  *  * S51S54 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -85 *  *  * S72 *  *  * -86 *  *  *  *  * 
 72   symbols_or_actions  !  *  *  *  *  * -78 *  *  *  *  *  *  *  *  * S73 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -23 *  *  *  * -75 *  *  *  *  *  *  *  *  *  *  * 
 73   modifiers           !  *  *  *  *  *  * S49 *  * -84 *  *  *  *  *  *  *  *  *  * S51S54 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -85 *  *  *  *  *  *  * -86 *  *  *  *  * 
 74   TERMINALS_aux       !  *  *  *  *  * -22 * S76 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -23 *  *  *  *  *  *  *  * -19 *  *  *  * S75 *  * 
 75   terminal_definitions!  *  *  *  * -17-22 * S76 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -23 *  *  *  *  *  *  *  * -20 *  *  *  *  *  *  * 
 76   terminal            !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 77   '='                 !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S78 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 78   token_code          !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S79 *  *  *  *  *  * 
 79   error_recovery_data !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 80   ','                 !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S81 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 81   insert_cost         !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 82   ','                 !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S83 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 83   delete_cost         !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -29 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 84   '=>'                !  *  *  *  *  * -22 * -35 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -23 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 85   SKIPHEADER          !  *  *  *  * -96 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 


           Summary of the table generation process
           ---------------------------------------

Number of states =   85
Total table space =  17223 bytes
     T-table =    5965 bytes
     NTS-table = 10566 bytes
     VOC-table =   692 bytes




               T H E   P A C K E D   A C T I O N   T A B L E


               Row Displacement Check Vector

Column       !  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
-------------!------------------------------------------------------------
Row Index    ! 22 22 22 22 38 73 52 52 52  2 73 39 73 39 39  7 27 54 73 73 

Column       ! 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
-------------!------------------------------------------------------------
Row Index    ! 22 22 22 22 22 22 27 22 22 22 22 22 22 22 22  7  7  7  7  7 

Column       ! 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60
-------------!------------------------------------------------------------
Row Index    !  7  6  7  7  7  7  7  7  7  7 55 55 55 29 29 29 12 12 12 36 

Column       ! 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80
-------------!------------------------------------------------------------
Row Index    ! 36  6  6  6  6  6  6 28  6  6  6  6  6  6  6  6 49 49 49 26 

Column       ! 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99100
-------------!------------------------------------------------------------
Row Index    ! 49 26 49 13 49 49 49 49 49 49 49 49 83 49 49 50 50 50 56 50 

Column       !101102103104105106107108109110111112113114115116117118119120
-------------!------------------------------------------------------------
Row Index    ! 56 50 83 50 50 50 50 50 50 50 50 20 50 50 75 75 75 75 48 43 

Column       !121122123124125126127128129130131132133134135136137138139140
-------------!------------------------------------------------------------
Row Index    ! 48 14 14 14 48 45  8 42 42 45 42 48 48 18 18 18 75 75 82 75 

Column       !141142143144145146147148149150151152153154155156157158159160
-------------!------------------------------------------------------------
Row Index    ! 34 82 75 75 75 75 75 75 75 42 42 82 42 37 11 42 42 42 42 42 

Column       !161162163164165166167168169170171172173174175176177178179180
-------------!------------------------------------------------------------
Row Index    ! 42 42 34 34 76 34 30 77 34 34 34 34 34 34 34 37 37 23 37 64 

Column       !181182183184185186187188189190191192193194195196197198199200
-------------!------------------------------------------------------------
Row Index    ! 79 37 37 37 37 37 37 37 30 30 64 30 64 64 30 30 30 30 30 30 

Column       !201202203204205206207208209210211212213214215216217218219220
-------------!------------------------------------------------------------
Row Index    ! 30 44 44 44 15 44 15 44 10 44 10 44 19 44 19 44 78 78 44 44 

Column       !221222223224225226227228229230231232233234235236237238239240
-------------!------------------------------------------------------------
Row Index    ! 46 46 46 40 46 40 46 80 46 24 46 80 46 41 46 41 31 46 46 47 

Column       !241242243244245246247248249250251252253254255256257258259260
-------------!------------------------------------------------------------
Row Index    ! 47 47 53 47 53 47 66 47 66 47 32 47 81 47 35 16 47 47 31 31 

Column       !261262263264265266267268269270271272273274275276277278279280
-------------!------------------------------------------------------------
Row Index    ! 17 31 51  X 31 31 31 31 31 31 31  X 32 32  X 32  X  X 32 32 

Column       !281282283284285286287288289290291292293294295296297298299300
-------------!------------------------------------------------------------
Row Index    ! 32 32 32 32 32 65 65 65  X 65 21 21 21 65 65  X 65 65  X 65 

Column       !301302303304305306307308309310311312313314315316317318319320
-------------!------------------------------------------------------------
Row Index    !  X  X 65 65 67 67 67  X 67 74 74 74 67 67  X 67 67  X 67  X 

Column       !321322323324325326327328329330331332333334335336337338339340
-------------!------------------------------------------------------------
Row Index    !  X 67 67 68 68 68  X 68  9  9  9 68 68  X 68 68  X 68  X  X 

Column       !341342343344345346347348349350351352353354355356357358359360
-------------!------------------------------------------------------------
Row Index    ! 68 68 69 69 69  X 69 84 84 84 69 69  X 69 69  X 69  X  X 69 

Column       !361362363364365366367368369370371372373374375376377378379380
-------------!------------------------------------------------------------
Row Index    ! 69 71 71 71  X 71 25 25 25 71 71  X 71 71  X 71  X 33 71 71 

Column       !381382383384385386387388389390391392393394395396397398399400
-------------!------------------------------------------------------------
Row Index    ! 72 72 72  X 72  X  X  X 72 72  X 72 72  X 72  X  X 72 72 33 

Column       !401402403404405406407408409410411412413414415416417418419420
-------------!------------------------------------------------------------
Row Index    ! 33  X 33  X  X 33 33 33 33 33 33 33 85 85  X 85 85  X 85 85 

Column       !421422423424425426427428429430431432433434435436437438439440
-------------!------------------------------------------------------------
Row Index    ! 85 85 85 85 85 63 63 63  X 63  X  X  X 63  X  X  X 63  X 63 

Column       !441442443444445446447448449450451452453454455456457458459460
-------------!------------------------------------------------------------
Row Index    ! 63  X 63 63  1  5  1  1  X  1  1  1  1  1  1  1  3  X  3  3 

Column       !461462463464465466467468469470471472473474475476477478479480
-------------!------------------------------------------------------------
Row Index    !  X  3  3  3  3  3  3  3  5  X  5  X  X  5  5  5  5  5  5  5 

Column       !481482483484485486487488489490491492493494495496497498499500
-------------!------------------------------------------------------------
Row Index    ! 57 57 57  X 57  X  X  X 57  X  X  X 57 57 57 60  X 57 57 58 

Column       !501502503504505506507508509510511512513514515516517518519520
-------------!------------------------------------------------------------
Row Index    ! 58 58  X 58 60  X  X 58 60 60  X 58 58 58  X  X 58 58 59 59 

Column       !521522523524525526527528529530531532533534535536537538539540
-------------!------------------------------------------------------------
Row Index    ! 59  X 59  X  X  X 59  X  X  X 59 59 59  X  X 59 59 61 61 61 

Column       !541542543544545546547548549550551552553554555556557558559560
-------------!------------------------------------------------------------
Row Index    !  X 61  X  X  X 61  X  X  X 61  X 61 61  X 61 61 62 62 62  X 

Column       !561562563564565566567568569570571572573574575576577578579580
-------------!------------------------------------------------------------
Row Index    ! 62  X  X  X 62  X  X  X 62  X 62 62  X 62 62  4  X  4  X  X 

Column       !581582583584585586587588589590591592593594595596597598599600
-------------!------------------------------------------------------------
Row Index    !  4  4  4  4  4  4  4 70  X  X  X  X 70  X 70  X  X  X  X  X 

Column       !601602603604605606607608609610611612613614615616617
-------------!---------------------------------------------------
Row Index    ! 70 70  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 

               Row mapping vector

Row          !  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85
-------------!---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Index        !422 10434553446 42 16118328201148 56 75121197249252133205105290  1172221366 72 10 61 53167237251378141254 53154  4  7223233128114201119220239114 76 95254  6235  9 50 91480499518491537556425175285237304323342583361380  1309115159164210174224245135 86347391

               Compressed ACTION table

Index        !  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
-------------!------------------------------------------------------------
Entry        ! R50-25-24-26S39-91-25-24-26 A R76-41R76R40R40R97R57S55-88-90

Index        ! 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
-------------!------------------------------------------------------------
Entry        ! R50R50R50R50R50R50S29R50R50R50R50R50R50R50R50S21-64-98R97-62

Index        ! 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60
-------------!------------------------------------------------------------
Entry        ! R97R44-60R97R97R97R97R97R97R97-25-24-26-25-24-26-25-24-26S37

Index        ! 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80
-------------!------------------------------------------------------------
Entry        ! S38R44R44R44R44R44R44-53R44R44R44R44R44R44R44R44R83R83R83S12

Index        ! 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99100
-------------!------------------------------------------------------------
Entry        ! R83S27R83S14R83R83R83R83R83R83R83R83R34R83R83R82R82R82S12R82

Index        !101102103104105106107108109110111112113114115116117118119120
-------------!------------------------------------------------------------
Entry        ! -89R82S84R82R82R82R82R82R82R82R82-63-88-90R97-25-24-26-91S44

Index        !121122123124125126127128129130131132133134135136137138139140
-------------!------------------------------------------------------------
Entry        ! R73-25-24-26R73-69S9 R97-25S46-26-88-90-25-24-26-98R97-33R97

Index        !141142143144145146147148149150151152153154155156157158159160
-------------!------------------------------------------------------------
Entry        ! R97R32R97R97R97R97R97R97R97-98R97R32R97R97-59R97R97R97R97R97

Index        !161162163164165166167168169170171172173174175176177178179180
-------------!------------------------------------------------------------
Entry        ! R97R97-98R97S77R97R97-27R97R97R97R97R97R97R97-98R97S24R97-91

Index        !181182183184185186187188189190191192193194195196197198199200
-------------!------------------------------------------------------------
Entry        ! -21R97R97R97R97R97R97R97-98R97-80R97-88-90R97R97R97R97R97R97

Index        !201202203204205206207208209210211212213214215216217218219220
-------------!------------------------------------------------------------
Entry        ! R97R74R74R74S12R74S16R74S12R74S11R74S12R74S20R74R28S80R74R74

Index        !221222223224225226227228229230231232233234235236237238239240
-------------!------------------------------------------------------------
Entry        ! R74R74R74R66R74R66R74-31R74S25R74R30R74-25R74-26R97R74R74-25

Index        !241242243244245246247248249250251252253254255256257258259260
-------------!------------------------------------------------------------
Entry        ! -24-26S12R83-87R83-81S65S67R83R97S57S82S61S39-61R83R83-98R97

Index        !261262263264265266267268269270271272273274275276277278279280
-------------!------------------------------------------------------------
Entry        ! S18R97S52 X R97R97R97R97R97R97R97 X -98R97 X R97 X  X R97R97

Index        !281282283284285286287288289290291292293294295296297298299300
-------------!------------------------------------------------------------
Entry        ! R97R97R97R97R97R83R83R83 X R83-25-24-26R83R83 X R83R83 X R83

Index        !301302303304305306307308309310311312313314315316317318319320
-------------!------------------------------------------------------------
Entry        !  X  X R83R83R83R83R83 X R83-25-24-26R83R83 X R83R83 X R83 X 

Index        !321322323324325326327328329330331332333334335336337338339340
-------------!------------------------------------------------------------
Entry        !  X R83R83R74R74R74 X R74-25-24-26R74R74 X R74R74 X R74 X  X 

Index        !341342343344345346347348349350351352353354355356357358359360
-------------!------------------------------------------------------------
Entry        ! -88-90-25-24-26 X R83-25-24-26S65R83 X R83S57 X S61 X  X R83

Index        !361362363364365366367368369370371372373374375376377378379380
-------------!------------------------------------------------------------
Entry        ! R83R74R74R74 X R74-25-24-26R74R74 X R74R74 X R74 X R97-88-90

Index        !381382383384385386387388389390391392393394395396397398399400
-------------!------------------------------------------------------------
Entry        ! -25-24-26 X R83 X  X  X S65R83 X R83S57 X S61 X  X R83R83-98

Index        !401402403404405406407408409410411412413414415416417418419420
-------------!------------------------------------------------------------
Entry        ! R97 X R97 X  X R97R97R97R97R97R97R97-98R97 X R97R97 X R97R97

Index        !421422423424425426427428429430431432433434435436437438439440
-------------!------------------------------------------------------------
Entry        ! R97R97R97R97R97-25-24-26 X R83 X  X  X S65 X  X  X S57 X S61

Index        !441442443444445446447448449450451452453454455456457458459460
-------------!------------------------------------------------------------
Entry        ! R83 X R83R83R3 R1 R3 R3  X R3 R3 R3 R3 R3 R3 R3 R2  X R2 S85

Index        !461462463464465466467468469470471472473474475476477478479480
-------------!------------------------------------------------------------
Entry        !  X R2 R2 R2 R2 R2 R2 R2 S40 X S31 X  X S32-43-18S35S30S33S34

Index        !481482483484485486487488489490491492493494495496497498499500
-------------!------------------------------------------------------------
Entry        ! R83R83R83 X R83 X  X  X R83 X  X  X R83R83R83-91 X R83R83R74

Index        !501502503504505506507508509510511512513514515516517518519520
-------------!------------------------------------------------------------
Entry        ! R74R74 X R74-79 X  X R74-88-90 X R74R74R74 X  X -88-90-25-24

Index        !521522523524525526527528529530531532533534535536537538539540
-------------!------------------------------------------------------------
Entry        ! -26 X R83 X  X  X S65 X  X  X S57R83S61 X  X R83R83R83R83R83

Index        !541542543544545546547548549550551552553554555556557558559560
-------------!------------------------------------------------------------
Entry        !  X R83 X  X  X R83 X  X  X R83 X R83R83 X R83R83R74R74R74 X 

Index        !561562563564565566567568569570571572573574575576577578579580
-------------!------------------------------------------------------------
Entry        ! R74 X  X  X R74 X  X  X R74 X R74R74 X -88-90S40 X S31 X  X 

Index        !581582583584585586587588589590591592593594595596597598599600
-------------!------------------------------------------------------------
Entry        ! S32-43-18S35S30S33S34-91 X  X  X  X R77 X R77 X  X  X  X  X 

Index        !601602
-------------!------
Entry        ! -88-90




                   T H E   P A C K E D   G O T O   T A B L E


               Row mapping vector

Row          !  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85
-------------!---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Index        ! 96 48 48 36 51120 94 42211 42 42130 42245 41 41 41200 40 40107 45 40 40 37 40 67 40 55 36 37 39 41 42 37 38 44 56 37 99 53202 37 36 37 49194 62 46177 37228 37 37234 37 52 95185113 38118187120 42 36 44136196138157205175118175 36126 94 36127 36130126216159

               Compressed GOTO table

Index        ! 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55
-------------!------------------------------------------------------------
Entry        ! -71 X S45 X -16-92-22-93-55-94-95-37-36-72-22S26-54S62-67S36

Index        ! 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75
-------------!------------------------------------------------------------
Entry        ! S42S71S23S68-22S50-58-14S4 S6 -38S58S49-5 S74-84-39S66-4 S5 

Index        ! 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95
-------------!------------------------------------------------------------
Entry        ! -9 S43-14-10S6 -23S51S54-6 S74-13S47-8 -23-52-9 -11-12-10-7 

Index        ! 96 97 98 99100101102103104105106107108109110111112113114115
-------------!------------------------------------------------------------
Entry        ! -15-70-42-23S47-13S17-8 -84-49-48-11-12-85-7 -15-22S28-54S51

Index        !116117118119120121122123124125126127128129130131132133134135
-------------!------------------------------------------------------------
Entry        ! S54-86S41S49S23S2 -84-22S13S76S49-84S3 -84-45-47S8 S51S54-22

Index        !136137138139140141142143144145146147148149150151152153154155
-------------!------------------------------------------------------------
Entry        ! -46-56S51S54S51S54-85S78S49-84S59-84S79S81-86-23-51S83-29S22

Index        !156157158159160161162163164165166167168169170171172173174175
-------------!------------------------------------------------------------
Entry        ! S51S54S51S54-85S7 -23-96 X -85-84-85-86S63 X -19 X -86-23-86

Index        !176177178179180181182183184185186187188189190191192193194195
-------------!------------------------------------------------------------
Entry        ! S75S51S54-17-22S49S76-85-84-85-84S69 X  X -78-86-78-86 X S51

Index        !196197198199200201202203204205206207208209210211212213214215
-------------!------------------------------------------------------------
Entry        ! S54S51S54-78S60-78S64-68-85-22-65-55S72S48-78S70-86 X S19 X 

Index        !216217218219220221222223224225226227228229230231232233234235
-------------!------------------------------------------------------------
Entry        ! -22 X -55-23S73-22-85-35-85S10S43 X -20-23-86-23-86-22-75-55

Index        !236237238239240241242243244245246247248249250251252253254255
-------------!------------------------------------------------------------
Entry        ! -75 X -23-22-23-55S53-75-23-75-70 X S56-23-22 X -55 X -75-23

Index        !256257258259260261262263264265266267268269270271272273274275
-------------!------------------------------------------------------------
Entry        !  X  X  X S15-23 X  X  X  X  X  X  X  X  X  X  X -23 X  X  X 

Index        !276277278279280281282283284285286287288289
-------------!------------------------------------------
Entry        !  X  X -23 X  X  X  X  X  X  X  X  X  X -23



                    Summary of the packing process
                    ------------------------------

Total table space =   3487 bytes
     T-table   =  2006 bytes
     NTS-table =   789 bytes
     VOC-table =   692 bytes

