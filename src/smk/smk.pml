

                      Summary of the input process
                      ----------------------------

Grammar file name = smk.pmk
Activated options = Recovery Single, Multiple, Panic;
Optimize Lr0;
Actionpack RDS;
Gotopack RDS;
List Grammar, Items, Tables, Statistics;
Resolve SR;
No Verbose;
Target 'ansi-c';
Escape '`';

Productions       = 102
Terminals         = 41
Non terminals     = 54
Attributes        = 7
Semantic actions  = 55

                                 T H E   V O C A B U L A R Y

T E R M I N A L S

  1.  EndOfText                       =   1  (icost = 255, dcost = 255)
  2.  '%%'                            =  99  (icost = 3, dcost = 2, => %%...%%)
  3.  '='                             = 100  (icost = 1, dcost = 1)
  4.  ';'                             = 101  (icost = 1, dcost = 1)
  5.  ':'                             = 102  (icost = 1, dcost = 1)
  6.  '/'                             = 103  (icost = 1, dcost = 1)
  7.  '!'                             = 104  (icost = 1, dcost = 1)
  8.  '*'                             = 105  (icost = 1, dcost = 1)
  9.  '+'                             = 106  (icost = 1, dcost = 1)
 10.  '?'                             = 107  (icost = 1, dcost = 1)
 11.  '{'                             = 108  (icost = 1, dcost = 1)
 12.  '}'                             = 109  (icost = 1, dcost = 1)
 13.  '-'                             = 110  (icost = 1, dcost = 1)
 14.  '.'                             = 111  (icost = 1, dcost = 1)
 15.  '('                             = 112  (icost = 1, dcost = 1)
 16.  ')'                             = 113  (icost = 1, dcost = 1)
 17.  Class                           = 114  (icost = 1, dcost = 1)
 18.  '%%DO'                          = 115  (icost = 1, dcost = 1)
 19.  String                          = 116  (icost = 1, dcost = 1)
 20.  Number                          = 117  (icost = 1, dcost = 1)
 21.  '%%END'                         = 118  (icost = 1, dcost = 1)
 22.  '%%SET'                         = 119  (icost = 1, dcost = 1)
 23.  '%%MAP'                         = 120  (icost = 1, dcost = 1)
 24.  '%%RULE'                        = 121  (icost = 1, dcost = 1)
 25.  '%%SKIP'                        = 122  (icost = 1, dcost = 1)
 26.  SKIPHEADER                      = 123  (icost = 1, dcost = 1)
 27.  '%%EXPORT'                      = 124  (icost = 1, dcost = 1)
 28.  '%%READER'                      = 125  (icost = 1, dcost = 1)
 29.  '%%ACTION'                      = 126  (icost = 1, dcost = 1)
 30.  '_UNKNOWN'                      = 127  (icost = 1, dcost = 1)
 31.  Identifier                      = 128  (icost = 1, dcost = 1)
 32.  '%%CONTEXT'                     = 129  (icost = 1, dcost = 1)
 33.  '%%PREHOOK'                     = 130  (icost = 1, dcost = 1)
 34.  '%%SCANNER'                     = 131  (icost = 1, dcost = 1)
 35.  '%%POSTHOOK'                    = 132  (icost = 1, dcost = 1)
 36.  '%%UNDEFINE'                    = 133  (icost = 1, dcost = 1)
 37.  '_ENDOFTEXT'                    = 134  (icost = 1, dcost = 1)
 38.  '%%SCREENING'                   = 135  (icost = 1, dcost = 1)
 39.  '%%DEFINITION'                  = 136  (icost = 1, dcost = 1)
 40.  '%%VOCABULARY'                  = 137  (icost = 1, dcost = 1)
 41.  '%%DECLARATION'                 = 138  (icost = 1, dcost = 1)


N O N   T E R M I N A L S

 42.  <map>
 43.  <goal>
 44.  <maps>
 45.  <class>
 46.  <token>
 47.  <number>
 48.  <string>
 49.  <end opt>
 50.  <operand>
 51.  __genSym#0
 52.  __genSym#1
 53.  __genSym#2
 54.  __genSym#3
 55.  __genSym#4
 56.  __genSym#5
 57.  <identifier>
 58.  <token name>
 59.  <tokens opt>
 60.  <action opt>
 61.  <concat rule>
 62.  <skip section>
 63.  <code section>
 64.  <scanner name>
 65.  <closure rule>
 66.  <token section>
 67.  <selection rule>
 68.  <token sections>
 69.  <lookahead rule>
 70.  <scanner section>
 71.  <scanner sections>
 72.  <skip sections opt>
 73.  <code sections opt>
 74.  <definition section>
 75.  <vocabulary section>
 76.  <vocabulary sections>
 77.  <scanner inherit opt>
 78.  <undefined token name>
 79.  <screening definition>
 80.  <definition definition>
 81.  <vocabulary definition>
 82.  <screening section opt>
 83.  <set definition section>
 84.  <map definition section>
 85.  <definition definitions>
 86.  <vocabulary definitions>
 87.  <definition sections opt>
 88.  <set definition sections>
 89.  <external vocabulary name>
 90.  <internal vocabulary name>
 91.  <undefined token names opt>
 92.  <screening definitions opt>
 93.  <undefine token section opt>
 94.  <set definition sections opt>
 95.  <definition definition section>


A T T R I B U T E S

 96.  srcp
 97.  name
 98.  action
 99.  fnumber
100.  inumber
101.  code
102.  ast
                               T H E   P R O D U C T I O N S

  1. <goal> = <skip sections opt> __genSym#0 <code sections opt> 
              <set definition sections opt> __genSym#1 
              <definition sections opt> <vocabulary sections> 
            ;

  2. __genSym#0 = 
                ;

  3. __genSym#1 = 
                ;

  4. <skip sections opt> = 
  5.                     ! <skip sections opt> <skip section> 
                         ;

  6. <skip section> = SKIPHEADER <end opt> 
                    ;

  7. <code sections opt> = 
  8.                     ! <code sections opt> <code section> 
                         ;

  9. <set definition sections opt> = 
 10.                               ! <set definition sections> 
                                   ;

 11. <set definition sections> = <set definition section> 
 12.                           ! <set definition sections> 
                                 <set definition section> 
                               ;

 13. <definition sections opt> = 
 14.                           ! <definition sections opt> 
                                 <definition section> 
                               ;

 15. <definition section> = <map definition section> 
 16.                      ! <definition definition section> 
                          ;

 17. <end opt> = 
 18.           ! '%%END' 
               ;

 19. <code section> = '%%DECLARATION' <end opt> 
 20.                ! '%%CONTEXT' <end opt> 
 21.                ! '%%EXPORT' <end opt> 
 22.                ! '%%READER' <end opt> 
 23.                ! '%%PREHOOK' <end opt> 
 24.                ! '%%ACTION' <end opt> 
 25.                ! '%%POSTHOOK' <end opt> 
                    ;

 26. <set definition section> = '%%SET' <end opt> 
                              ;

 27. <map definition section> = '%%MAP' <maps> <end opt> 
                              ;

 28. <maps> = <map> 
 29.        ! <maps> <map> 
            ;

 30. <map> = <class> '=' <class> ';' 
           ;

 31. <definition definition section> = '%%DEFINITION' 
                                       <definition definitions> <end opt> 
                                     ;

 32. <definition definitions> = <definition definition> 
 33.                          ! <definition definitions> 
                                <definition definition> 
                              ;

 34. <definition definition> = <identifier> '=' <selection rule> ';' 
 35.                         ! <identifier> '=' '%%' ';' 
 36.                         ! <identifier> '=' <selection rule> '%%' ';' 
                             ;

 37. <vocabulary sections> = <vocabulary section> 
 38.                       ! <vocabulary sections> <vocabulary section> 
                           ;

 39. <vocabulary section> = '%%VOCABULARY' <external vocabulary name> 
                            <scanner sections> 
 40.                      ! '%%VOCABULARY' <internal vocabulary name> 
                            <vocabulary definitions> <scanner sections> 
                          ;

 41. <external vocabulary name> = <identifier> 
                                ;

 42. <internal vocabulary name> = <identifier> 
                                ;

 43. <vocabulary definitions> = <vocabulary definition> 
 44.                          ! <vocabulary definitions> 
                                <vocabulary definition> 
                              ;

 45. <vocabulary definition> = <token name> '=' <number> ';' 
                             ;

 46. <scanner sections> = <scanner section> 
 47.                    ! <scanner sections> <scanner section> 
                        ;

 48. <scanner section> = '%%SCANNER' <scanner name> <scanner inherit opt> 
                         __genSym#2 <screening section opt> 
                         <undefine token section opt> <token sections> 
                       ;

 49. __genSym#2 = 
                ;

 50. <scanner name> = <identifier> 
                    ;

 51. <scanner inherit opt> = 
 52.                       ! ':' <identifier> 
                           ;

 53. <undefine token section opt> = 
 54.                              ! '%%UNDEFINE' <undefined token names opt> 
                                    <end opt> 
                                  ;

 55. <undefined token names opt> = 
 56.                             ! <undefined token names opt> 
                                   <undefined token name> 
                                 ;

 57. <undefined token name> = <token name> ';' 
                            ;

 58. <screening section opt> = 
 59.                         ! '%%SCREENING' __genSym#3 
                               <screening definitions opt> <end opt> 
                             ;

 60. __genSym#3 = 
                ;

 61. <screening definitions opt> = 
 62.                             ! <screening definitions opt> 
                                   <screening definition> 
                                 ;

 63. <screening definition> = <token name> ';' 
                            ;

 64. <token sections> = <token section> 
 65.                  ! <token sections> <token section> 
                      ;

 66. <token section> = '%%RULE' __genSym#4 <tokens opt> <end opt> 
 67.                 ! '%%SKIP' __genSym#5 <tokens opt> <end opt> 
                     ;

 68. __genSym#4 = 
                ;

 69. __genSym#5 = 
                ;

 70. <tokens opt> = 
 71.              ! <tokens opt> <token> 
                  ;

 72. <token> = <token name> '=' <lookahead rule> <action opt> ';' 
 73.         ! <token name> '=' '_ENDOFTEXT' <action opt> ';' 
 74.         ! <token name> '=' '_UNKNOWN' <action opt> ';' 
             ;

 75. <token name> = <identifier> 
 76.              ! <string> 
                  ;

 77. <action opt> = 
 78.              ! '%%DO' <identifier> 
 79.              ! '%%' 
                  ;

 80. <lookahead rule> = <selection rule> 
 81.                  ! <selection rule> '/' <selection rule> 
                      ;

 82. <selection rule> = <concat rule> 
 83.                  ! <selection rule> '!' <concat rule> 
                      ;

 84. <concat rule> = <closure rule> 
 85.               ! <concat rule> <closure rule> 
                   ;

 86. <closure rule> = <operand> 
 87.                ! <operand> '*' 
 88.                ! <operand> '+' 
 89.                ! <operand> '?' 
 90.                ! <operand> '{' <number> '}' 
 91.                ! <operand> '{' '-' <number> '}' 
 92.                ! <operand> '{' <number> '-' '}' 
 93.                ! <operand> '{' <number> '-' <number> '}' 
                    ;

 94. <operand> = <identifier> 
 95.           ! <string> 
 96.           ! <class> 
 97.           ! '.' 
 98.           ! '(' <selection rule> ')' 
               ;

 99. <identifier> = Identifier 
                  ;

100. <string> = String 
              ;

101. <number> = Number 
              ;

102. <class> = Class 
             ;

                      L A L R ( 1 )  S E T S  O F  I T E M S



State:    1   !  Continuation: '%%SET'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           R4 ! <skip sections opt> --> .
              !                         {'%%SET' '%%MAP' SKIPHEADER '%%EXPORT' 
              !                          '%%READER' '%%ACTION' '%%CONTEXT' 
              !                          '%%PREHOOK' '%%POSTHOOK' 
              !                          '%%DEFINITION' '%%VOCABULARY' 
              !                          '%%DECLARATION' }
            3 ! <goal> --> .<skip sections opt> __genSym#0 <code sections opt> 
              !            <set definition sections opt> __genSym#1 
              !            <definition sections opt> <vocabulary sections> 
            2 ! Unknown --> .<goal> 
            3 ! <skip sections opt> --> .<skip sections opt> <skip section> 


State:    2   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           R0 ! Unknown --> <goal> .
              !             {EndOfText }


State:    3   !  Continuation: '%%SET'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           R2 ! __genSym#0 --> .
              !                {'%%SET' '%%MAP' '%%EXPORT' '%%READER' 
              !                 '%%ACTION' '%%CONTEXT' '%%PREHOOK' 
              !                 '%%POSTHOOK' '%%DEFINITION' '%%VOCABULARY' 
              !                 '%%DECLARATION' }
          SR5 ! <skip sections opt> --> <skip sections opt> .<skip section> 
            4 ! <goal> --> <skip sections opt> .__genSym#0 <code sections opt> 
              !            <set definition sections opt> __genSym#1 
              !            <definition sections opt> <vocabulary sections> 
           86 ! <skip section> --> .SKIPHEADER <end opt> 


State:    4   !  Continuation: '%%SET'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           R7 ! <code sections opt> --> .
              !                         {'%%SET' '%%MAP' '%%EXPORT' '%%READER' 
              !                          '%%ACTION' '%%CONTEXT' '%%PREHOOK' 
              !                          '%%POSTHOOK' '%%DEFINITION' 
              !                          '%%VOCABULARY' '%%DECLARATION' }
            5 ! <goal> --> <skip sections opt> __genSym#0 .<code sections opt> 
              !            <set definition sections opt> __genSym#1 
              !            <definition sections opt> <vocabulary sections> 
            5 ! <code sections opt> --> .<code sections opt> <code section> 


State:    5   !  Continuation: '%%MAP'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           R9 ! <set definition sections opt> --> .
              !                                   {'%%MAP' '%%DEFINITION' 
              !                                    '%%VOCABULARY' }
          SR8 ! <code sections opt> --> <code sections opt> .<code section> 
            6 ! <goal> --> <skip sections opt> __genSym#0 <code sections opt> .
              !            <set definition sections opt> __genSym#1 
              !            <definition sections opt> <vocabulary sections> 
           77 ! <set definition sections opt> --> .<set definition sections> 
         SR11 ! <set definition sections> --> .<set definition section> 
           78 ! <set definition section> --> .'%%SET' <end opt> 
           77 ! <set definition sections> --> .<set definition sections> 
              !                               <set definition section> 
           79 ! <code section> --> .'%%DECLARATION' <end opt> 
           80 ! <code section> --> .'%%CONTEXT' <end opt> 
           81 ! <code section> --> .'%%EXPORT' <end opt> 
           82 ! <code section> --> .'%%READER' <end opt> 
           83 ! <code section> --> .'%%PREHOOK' <end opt> 
           84 ! <code section> --> .'%%ACTION' <end opt> 
           85 ! <code section> --> .'%%POSTHOOK' <end opt> 


State:    6   !  Continuation: '%%MAP'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           R3 ! __genSym#1 --> .
              !                {'%%MAP' '%%DEFINITION' '%%VOCABULARY' }
            7 ! <goal> --> <skip sections opt> __genSym#0 <code sections opt> 
              !            <set definition sections opt> .__genSym#1 
              !            <definition sections opt> <vocabulary sections> 


State:    7   !  Continuation: '%%MAP'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R13 ! <definition sections opt> --> .
              !                               {'%%MAP' '%%DEFINITION' 
              !                                '%%VOCABULARY' }
            8 ! <goal> --> <skip sections opt> __genSym#0 <code sections opt> 
              !            <set definition sections opt> __genSym#1 .
              !            <definition sections opt> <vocabulary sections> 
            8 ! <definition sections opt> --> .<definition sections opt> 
              !                               <definition section> 


State:    8   !  Continuation: '%%VOCABULARY'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            9 ! <goal> --> <skip sections opt> __genSym#0 <code sections opt> 
              !            <set definition sections opt> __genSym#1 
              !            <definition sections opt> .<vocabulary sections> 
         SR14 ! <definition sections opt> --> <definition sections opt> .
              !                               <definition section> 
         SR37 ! <vocabulary sections> --> .<vocabulary section> 
           10 ! <vocabulary section> --> .'%%VOCABULARY' 
              !                          <external vocabulary name> 
              !                          <scanner sections> 
           10 ! <vocabulary section> --> .'%%VOCABULARY' 
              !                          <internal vocabulary name> 
              !                          <vocabulary definitions> 
              !                          <scanner sections> 
            9 ! <vocabulary sections> --> .<vocabulary sections> 
              !                           <vocabulary section> 
         SR15 ! <definition section> --> .<map definition section> 
           65 ! <map definition section> --> .'%%MAP' <maps> <end opt> 
         SR16 ! <definition section> --> .<definition definition section> 
           70 ! <definition definition section> --> .'%%DEFINITION' 
              !                                     <definition definitions> 
              !                                     <end opt> 


State:    9   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           R1 ! <goal> --> <skip sections opt> __genSym#0 <code sections opt> 
              !            <set definition sections opt> __genSym#1 
              !            <definition sections opt> <vocabulary sections> .
              !            {EndOfText }
         SR38 ! <vocabulary sections> --> <vocabulary sections> .
              !                           <vocabulary section> 
           10 ! <vocabulary section> --> .'%%VOCABULARY' 
              !                          <external vocabulary name> 
              !                          <scanner sections> 
           10 ! <vocabulary section> --> .'%%VOCABULARY' 
              !                          <internal vocabulary name> 
              !                          <vocabulary definitions> 
              !                          <scanner sections> 


State:   10   !  Continuation: Identifier
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           11 ! <vocabulary section> --> '%%VOCABULARY' .
              !                          <external vocabulary name> 
              !                          <scanner sections> 
           58 ! <vocabulary section> --> '%%VOCABULARY' .
              !                          <internal vocabulary name> 
              !                          <vocabulary definitions> 
              !                          <scanner sections> 
           64 ! <external vocabulary name> --> .<identifier> 
         SR99 ! <identifier> --> .Identifier 
           64 ! <internal vocabulary name> --> .<identifier> 


State:   11   !  Continuation: '%%SCANNER'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           12 ! <vocabulary section> --> '%%VOCABULARY' 
              !                          <external vocabulary name> .
              !                          <scanner sections> 
         SR46 ! <scanner sections> --> .<scanner section> 
           13 ! <scanner section> --> .'%%SCANNER' <scanner name> 
              !                       <scanner inherit opt> __genSym#2 
              !                       <screening section opt> 
              !                       <undefine token section opt> 
              !                       <token sections> 
           12 ! <scanner sections> --> .<scanner sections> <scanner section> 


State:   12   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R39 ! <vocabulary section> --> '%%VOCABULARY' 
              !                          <external vocabulary name> 
              !                          <scanner sections> .
              !                          {EndOfText '%%VOCABULARY' }
         SR47 ! <scanner sections> --> <scanner sections> .<scanner section> 
           13 ! <scanner section> --> .'%%SCANNER' <scanner name> 
              !                       <scanner inherit opt> __genSym#2 
              !                       <screening section opt> 
              !                       <undefine token section opt> 
              !                       <token sections> 


State:   13   !  Continuation: Identifier
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           14 ! <scanner section> --> '%%SCANNER' .<scanner name> 
              !                       <scanner inherit opt> __genSym#2 
              !                       <screening section opt> 
              !                       <undefine token section opt> 
              !                       <token sections> 
         SR50 ! <scanner name> --> .<identifier> 
         SR99 ! <identifier> --> .Identifier 


State:   14   !  Continuation: '%%RULE'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R51 ! <scanner inherit opt> --> .
              !                           {'%%RULE' '%%SKIP' '%%UNDEFINE' 
              !                            '%%SCREENING' }
           15 ! <scanner section> --> '%%SCANNER' <scanner name> .
              !                       <scanner inherit opt> __genSym#2 
              !                       <screening section opt> 
              !                       <undefine token section opt> 
              !                       <token sections> 
           57 ! <scanner inherit opt> --> .':' <identifier> 


State:   15   !  Continuation: '%%RULE'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R49 ! __genSym#2 --> .
              !                {'%%RULE' '%%SKIP' '%%UNDEFINE' '%%SCREENING' }
           16 ! <scanner section> --> '%%SCANNER' <scanner name> 
              !                       <scanner inherit opt> .__genSym#2 
              !                       <screening section opt> 
              !                       <undefine token section opt> 
              !                       <token sections> 


State:   16   !  Continuation: '%%RULE'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R58 ! <screening section opt> --> .
              !                             {'%%RULE' '%%SKIP' '%%UNDEFINE' }
           17 ! <scanner section> --> '%%SCANNER' <scanner name> 
              !                       <scanner inherit opt> __genSym#2 .
              !                       <screening section opt> 
              !                       <undefine token section opt> 
              !                       <token sections> 
           53 ! <screening section opt> --> .'%%SCREENING' __genSym#3 
              !                             <screening definitions opt> 
              !                             <end opt> 


State:   17   !  Continuation: '%%RULE'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R53 ! <undefine token section opt> --> .
              !                                  {'%%RULE' '%%SKIP' }
           18 ! <scanner section> --> '%%SCANNER' <scanner name> 
              !                       <scanner inherit opt> __genSym#2 
              !                       <screening section opt> .
              !                       <undefine token section opt> 
              !                       <token sections> 
           50 ! <undefine token section opt> --> .'%%UNDEFINE' 
              !                                  <undefined token names opt> 
              !                                  <end opt> 


State:   18   !  Continuation: '%%RULE'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           19 ! <scanner section> --> '%%SCANNER' <scanner name> 
              !                       <scanner inherit opt> __genSym#2 
              !                       <screening section opt> 
              !                       <undefine token section opt> .
              !                       <token sections> 
         SR64 ! <token sections> --> .<token section> 
           20 ! <token section> --> .'%%RULE' __genSym#4 <tokens opt> 
              !                     <end opt> 
           47 ! <token section> --> .'%%SKIP' __genSym#5 <tokens opt> 
              !                     <end opt> 
           19 ! <token sections> --> .<token sections> <token section> 


State:   19   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R48 ! <scanner section> --> '%%SCANNER' <scanner name> 
              !                       <scanner inherit opt> __genSym#2 
              !                       <screening section opt> 
              !                       <undefine token section opt> 
              !                       <token sections> .
              !                       {EndOfText '%%SCANNER' '%%VOCABULARY' }
         SR65 ! <token sections> --> <token sections> .<token section> 
           20 ! <token section> --> .'%%RULE' __genSym#4 <tokens opt> 
              !                     <end opt> 
           47 ! <token section> --> .'%%SKIP' __genSym#5 <tokens opt> 
              !                     <end opt> 


State:   20   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R68 ! __genSym#4 --> .
              !                {EndOfText String '%%END' '%%RULE' '%%SKIP' 
              !                 Identifier '%%SCANNER' '%%VOCABULARY' }
           21 ! <token section> --> '%%RULE' .__genSym#4 <tokens opt> 
              !                     <end opt> 


State:   21   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R70 ! <tokens opt> --> .
              !                  {EndOfText String '%%END' '%%RULE' '%%SKIP' 
              !                   Identifier '%%SCANNER' '%%VOCABULARY' }
           22 ! <token section> --> '%%RULE' __genSym#4 .<tokens opt> 
              !                     <end opt> 
           22 ! <tokens opt> --> .<tokens opt> <token> 


State:   22   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R17 ! <end opt> --> .
              !               {EndOfText '%%RULE' '%%SKIP' '%%SCANNER' 
              !                '%%VOCABULARY' }
         SR71 ! <tokens opt> --> <tokens opt> .<token> 
         SR66 ! <token section> --> '%%RULE' __genSym#4 <tokens opt> .
              !                     <end opt> 
         SR18 ! <end opt> --> .'%%END' 
           23 ! <token> --> .<token name> '=' <lookahead rule> <action opt> 
              !             ';' 
         SR75 ! <token name> --> .<identifier> 
         SR99 ! <identifier> --> .Identifier 
         SR76 ! <token name> --> .<string> 
        SR100 ! <string> --> .String 
           23 ! <token> --> .<token name> '=' '_ENDOFTEXT' <action opt> ';' 
           23 ! <token> --> .<token name> '=' '_UNKNOWN' <action opt> ';' 


State:   23   !  Continuation: '='
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           24 ! <token> --> <token name> .'=' <lookahead rule> <action opt> 
              !             ';' 
           24 ! <token> --> <token name> .'=' '_ENDOFTEXT' <action opt> ';' 
           24 ! <token> --> <token name> .'=' '_UNKNOWN' <action opt> ';' 


State:   24   !  Continuation: Identifier
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           25 ! <token> --> <token name> '=' .<lookahead rule> <action opt> 
              !             ';' 
           28 ! <token> --> <token name> '=' .'_ENDOFTEXT' <action opt> ';' 
           30 ! <token> --> <token name> '=' .'_UNKNOWN' <action opt> ';' 
           32 ! <lookahead rule> --> .<selection rule> 
           44 ! <selection rule> --> .<concat rule> 
         SR84 ! <concat rule> --> .<closure rule> 
           35 ! <closure rule> --> .<operand> 
         SR94 ! <operand> --> .<identifier> 
         SR99 ! <identifier> --> .Identifier 
         SR95 ! <operand> --> .<string> 
        SR100 ! <string> --> .String 
         SR96 ! <operand> --> .<class> 
        SR102 ! <class> --> .Class 
         SR97 ! <operand> --> .'.' 
           42 ! <operand> --> .'(' <selection rule> ')' 
           35 ! <closure rule> --> .<operand> '*' 
           35 ! <closure rule> --> .<operand> '+' 
           35 ! <closure rule> --> .<operand> '?' 
           35 ! <closure rule> --> .<operand> '{' <number> '}' 
           35 ! <closure rule> --> .<operand> '{' '-' <number> '}' 
           35 ! <closure rule> --> .<operand> '{' <number> '-' '}' 
           35 ! <closure rule> --> .<operand> '{' <number> '-' <number> '}' 
           44 ! <concat rule> --> .<concat rule> <closure rule> 
           32 ! <selection rule> --> .<selection rule> '!' <concat rule> 
           32 ! <lookahead rule> --> .<selection rule> '/' <selection rule> 


State:   25   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R77 ! <action opt> --> .
              !                  {';' }
           26 ! <token> --> <token name> '=' <lookahead rule> .<action opt> 
              !             ';' 
           27 ! <action opt> --> .'%%DO' <identifier> 
         SR79 ! <action opt> --> .'%%' 


State:   26   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR72 ! <token> --> <token name> '=' <lookahead rule> <action opt> .
              !             ';' 


State:   27   !  Continuation: Identifier
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR78 ! <action opt> --> '%%DO' .<identifier> 
         SR99 ! <identifier> --> .Identifier 


State:   28   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R77 ! <action opt> --> .
              !                  {';' }
           29 ! <token> --> <token name> '=' '_ENDOFTEXT' .<action opt> ';' 
           27 ! <action opt> --> .'%%DO' <identifier> 
         SR79 ! <action opt> --> .'%%' 


State:   29   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR73 ! <token> --> <token name> '=' '_ENDOFTEXT' <action opt> .';' 


State:   30   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R77 ! <action opt> --> .
              !                  {';' }
           31 ! <token> --> <token name> '=' '_UNKNOWN' .<action opt> ';' 
           27 ! <action opt> --> .'%%DO' <identifier> 
         SR79 ! <action opt> --> .'%%' 


State:   31   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR74 ! <token> --> <token name> '=' '_UNKNOWN' <action opt> .';' 


State:   32   !  Continuation: '%%'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R80 ! <lookahead rule> --> <selection rule> .
              !                      {'%%' ';' '%%DO' }
           33 ! <selection rule> --> <selection rule> .'!' <concat rule> 
           45 ! <lookahead rule> --> <selection rule> .'/' <selection rule> 


State:   33   !  Continuation: Identifier
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           34 ! <selection rule> --> <selection rule> '!' .<concat rule> 
         SR84 ! <concat rule> --> .<closure rule> 
           35 ! <closure rule> --> .<operand> 
         SR94 ! <operand> --> .<identifier> 
         SR99 ! <identifier> --> .Identifier 
         SR95 ! <operand> --> .<string> 
        SR100 ! <string> --> .String 
         SR96 ! <operand> --> .<class> 
        SR102 ! <class> --> .Class 
         SR97 ! <operand> --> .'.' 
           42 ! <operand> --> .'(' <selection rule> ')' 
           35 ! <closure rule> --> .<operand> '*' 
           35 ! <closure rule> --> .<operand> '+' 
           35 ! <closure rule> --> .<operand> '?' 
           35 ! <closure rule> --> .<operand> '{' <number> '}' 
           35 ! <closure rule> --> .<operand> '{' '-' <number> '}' 
           35 ! <closure rule> --> .<operand> '{' <number> '-' '}' 
           35 ! <closure rule> --> .<operand> '{' <number> '-' <number> '}' 
           34 ! <concat rule> --> .<concat rule> <closure rule> 


State:   34   !  Continuation: '%%'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R83 ! <selection rule> --> <selection rule> '!' <concat rule> .
              !                      {'%%' ';' '/' '!' ')' '%%DO' }
         SR85 ! <concat rule> --> <concat rule> .<closure rule> 
           35 ! <closure rule> --> .<operand> 
         SR94 ! <operand> --> .<identifier> 
         SR99 ! <identifier> --> .Identifier 
         SR95 ! <operand> --> .<string> 
        SR100 ! <string> --> .String 
         SR96 ! <operand> --> .<class> 
        SR102 ! <class> --> .Class 
         SR97 ! <operand> --> .'.' 
           42 ! <operand> --> .'(' <selection rule> ')' 
           35 ! <closure rule> --> .<operand> '*' 
           35 ! <closure rule> --> .<operand> '+' 
           35 ! <closure rule> --> .<operand> '?' 
           35 ! <closure rule> --> .<operand> '{' <number> '}' 
           35 ! <closure rule> --> .<operand> '{' '-' <number> '}' 
           35 ! <closure rule> --> .<operand> '{' <number> '-' '}' 
           35 ! <closure rule> --> .<operand> '{' <number> '-' <number> '}' 


State:   35   !  Continuation: '%%'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R86 ! <closure rule> --> <operand> .
              !                    {'%%' ';' '/' '!' '.' '(' ')' Class '%%DO' 
              !                     String Identifier }
         SR87 ! <closure rule> --> <operand> .'*' 
         SR88 ! <closure rule> --> <operand> .'+' 
         SR89 ! <closure rule> --> <operand> .'?' 
           36 ! <closure rule> --> <operand> .'{' <number> '}' 
           36 ! <closure rule> --> <operand> .'{' '-' <number> '}' 
           36 ! <closure rule> --> <operand> .'{' <number> '-' '}' 
           36 ! <closure rule> --> <operand> .'{' <number> '-' <number> '}' 


State:   36   !  Continuation: Number
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           37 ! <closure rule> --> <operand> '{' .<number> '}' 
           40 ! <closure rule> --> <operand> '{' .'-' <number> '}' 
           37 ! <closure rule> --> <operand> '{' .<number> '-' '}' 
           37 ! <closure rule> --> <operand> '{' .<number> '-' <number> '}' 
        SR101 ! <number> --> .Number 


State:   37   !  Continuation: '}'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR90 ! <closure rule> --> <operand> '{' <number> .'}' 
           38 ! <closure rule> --> <operand> '{' <number> .'-' '}' 
           38 ! <closure rule> --> <operand> '{' <number> .'-' <number> '}' 


State:   38   !  Continuation: '}'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR92 ! <closure rule> --> <operand> '{' <number> '-' .'}' 
           39 ! <closure rule> --> <operand> '{' <number> '-' .<number> '}' 
        SR101 ! <number> --> .Number 


State:   39   !  Continuation: '}'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR93 ! <closure rule> --> <operand> '{' <number> '-' <number> .'}' 


State:   40   !  Continuation: Number
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           41 ! <closure rule> --> <operand> '{' '-' .<number> '}' 
        SR101 ! <number> --> .Number 


State:   41   !  Continuation: '}'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR91 ! <closure rule> --> <operand> '{' '-' <number> .'}' 


State:   42   !  Continuation: Identifier
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           43 ! <operand> --> '(' .<selection rule> ')' 
           44 ! <selection rule> --> .<concat rule> 
         SR84 ! <concat rule> --> .<closure rule> 
           35 ! <closure rule> --> .<operand> 
         SR94 ! <operand> --> .<identifier> 
         SR99 ! <identifier> --> .Identifier 
         SR95 ! <operand> --> .<string> 
        SR100 ! <string> --> .String 
         SR96 ! <operand> --> .<class> 
        SR102 ! <class> --> .Class 
         SR97 ! <operand> --> .'.' 
           42 ! <operand> --> .'(' <selection rule> ')' 
           35 ! <closure rule> --> .<operand> '*' 
           35 ! <closure rule> --> .<operand> '+' 
           35 ! <closure rule> --> .<operand> '?' 
           35 ! <closure rule> --> .<operand> '{' <number> '}' 
           35 ! <closure rule> --> .<operand> '{' '-' <number> '}' 
           35 ! <closure rule> --> .<operand> '{' <number> '-' '}' 
           35 ! <closure rule> --> .<operand> '{' <number> '-' <number> '}' 
           44 ! <concat rule> --> .<concat rule> <closure rule> 
           43 ! <selection rule> --> .<selection rule> '!' <concat rule> 


State:   43   !  Continuation: ')'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR98 ! <operand> --> '(' <selection rule> .')' 
           33 ! <selection rule> --> <selection rule> .'!' <concat rule> 


State:   44   !  Continuation: '%%'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R82 ! <selection rule> --> <concat rule> .
              !                      {'%%' ';' '/' '!' ')' '%%DO' }
         SR85 ! <concat rule> --> <concat rule> .<closure rule> 
           35 ! <closure rule> --> .<operand> 
         SR94 ! <operand> --> .<identifier> 
         SR99 ! <identifier> --> .Identifier 
         SR95 ! <operand> --> .<string> 
        SR100 ! <string> --> .String 
         SR96 ! <operand> --> .<class> 
        SR102 ! <class> --> .Class 
         SR97 ! <operand> --> .'.' 
           42 ! <operand> --> .'(' <selection rule> ')' 
           35 ! <closure rule> --> .<operand> '*' 
           35 ! <closure rule> --> .<operand> '+' 
           35 ! <closure rule> --> .<operand> '?' 
           35 ! <closure rule> --> .<operand> '{' <number> '}' 
           35 ! <closure rule> --> .<operand> '{' '-' <number> '}' 
           35 ! <closure rule> --> .<operand> '{' <number> '-' '}' 
           35 ! <closure rule> --> .<operand> '{' <number> '-' <number> '}' 


State:   45   !  Continuation: Identifier
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           46 ! <lookahead rule> --> <selection rule> '/' .<selection rule> 
           44 ! <selection rule> --> .<concat rule> 
         SR84 ! <concat rule> --> .<closure rule> 
           35 ! <closure rule> --> .<operand> 
         SR94 ! <operand> --> .<identifier> 
         SR99 ! <identifier> --> .Identifier 
         SR95 ! <operand> --> .<string> 
        SR100 ! <string> --> .String 
         SR96 ! <operand> --> .<class> 
        SR102 ! <class> --> .Class 
         SR97 ! <operand> --> .'.' 
           42 ! <operand> --> .'(' <selection rule> ')' 
           35 ! <closure rule> --> .<operand> '*' 
           35 ! <closure rule> --> .<operand> '+' 
           35 ! <closure rule> --> .<operand> '?' 
           35 ! <closure rule> --> .<operand> '{' <number> '}' 
           35 ! <closure rule> --> .<operand> '{' '-' <number> '}' 
           35 ! <closure rule> --> .<operand> '{' <number> '-' '}' 
           35 ! <closure rule> --> .<operand> '{' <number> '-' <number> '}' 
           44 ! <concat rule> --> .<concat rule> <closure rule> 
           46 ! <selection rule> --> .<selection rule> '!' <concat rule> 


State:   46   !  Continuation: '%%'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R81 ! <lookahead rule> --> <selection rule> '/' <selection rule> .
              !                      {'%%' ';' '%%DO' }
           33 ! <selection rule> --> <selection rule> .'!' <concat rule> 


State:   47   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R69 ! __genSym#5 --> .
              !                {EndOfText String '%%END' '%%RULE' '%%SKIP' 
              !                 Identifier '%%SCANNER' '%%VOCABULARY' }
           48 ! <token section> --> '%%SKIP' .__genSym#5 <tokens opt> 
              !                     <end opt> 


State:   48   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R70 ! <tokens opt> --> .
              !                  {EndOfText String '%%END' '%%RULE' '%%SKIP' 
              !                   Identifier '%%SCANNER' '%%VOCABULARY' }
           49 ! <token section> --> '%%SKIP' __genSym#5 .<tokens opt> 
              !                     <end opt> 
           49 ! <tokens opt> --> .<tokens opt> <token> 


State:   49   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R17 ! <end opt> --> .
              !               {EndOfText '%%RULE' '%%SKIP' '%%SCANNER' 
              !                '%%VOCABULARY' }
         SR71 ! <tokens opt> --> <tokens opt> .<token> 
         SR67 ! <token section> --> '%%SKIP' __genSym#5 <tokens opt> .
              !                     <end opt> 
         SR18 ! <end opt> --> .'%%END' 
           23 ! <token> --> .<token name> '=' <lookahead rule> <action opt> 
              !             ';' 
         SR75 ! <token name> --> .<identifier> 
         SR99 ! <identifier> --> .Identifier 
         SR76 ! <token name> --> .<string> 
        SR100 ! <string> --> .String 
           23 ! <token> --> .<token name> '=' '_ENDOFTEXT' <action opt> ';' 
           23 ! <token> --> .<token name> '=' '_UNKNOWN' <action opt> ';' 


State:   50   !  Continuation: String
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R55 ! <undefined token names opt> --> .
              !                                 {String '%%END' '%%RULE' 
              !                                  '%%SKIP' Identifier }
           51 ! <undefine token section opt> --> '%%UNDEFINE' .
              !                                  <undefined token names opt> 
              !                                  <end opt> 
           51 ! <undefined token names opt> --> .<undefined token names opt> 
              !                                 <undefined token name> 


State:   51   !  Continuation: '%%RULE'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R17 ! <end opt> --> .
              !               {'%%RULE' '%%SKIP' }
         SR56 ! <undefined token names opt> --> <undefined token names opt> .
              !                                 <undefined token name> 
         SR54 ! <undefine token section opt> --> '%%UNDEFINE' 
              !                                  <undefined token names opt> .
              !                                  <end opt> 
         SR18 ! <end opt> --> .'%%END' 
           52 ! <undefined token name> --> .<token name> ';' 
         SR75 ! <token name> --> .<identifier> 
         SR99 ! <identifier> --> .Identifier 
         SR76 ! <token name> --> .<string> 
        SR100 ! <string> --> .String 


State:   52   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR57 ! <undefined token name> --> <token name> .';' 


State:   53   !  Continuation: String
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R60 ! __genSym#3 --> .
              !                {String '%%END' '%%RULE' '%%SKIP' Identifier 
              !                 '%%UNDEFINE' }
           54 ! <screening section opt> --> '%%SCREENING' .__genSym#3 
              !                             <screening definitions opt> 
              !                             <end opt> 


State:   54   !  Continuation: String
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R61 ! <screening definitions opt> --> .
              !                                 {String '%%END' '%%RULE' 
              !                                  '%%SKIP' Identifier 
              !                                  '%%UNDEFINE' }
           55 ! <screening section opt> --> '%%SCREENING' __genSym#3 .
              !                             <screening definitions opt> 
              !                             <end opt> 
           55 ! <screening definitions opt> --> .<screening definitions opt> 
              !                                 <screening definition> 


State:   55   !  Continuation: '%%RULE'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R17 ! <end opt> --> .
              !               {'%%RULE' '%%SKIP' '%%UNDEFINE' }
         SR62 ! <screening definitions opt> --> <screening definitions opt> .
              !                                 <screening definition> 
         SR59 ! <screening section opt> --> '%%SCREENING' __genSym#3 
              !                             <screening definitions opt> .
              !                             <end opt> 
         SR18 ! <end opt> --> .'%%END' 
           56 ! <screening definition> --> .<token name> ';' 
         SR75 ! <token name> --> .<identifier> 
         SR99 ! <identifier> --> .Identifier 
         SR76 ! <token name> --> .<string> 
        SR100 ! <string> --> .String 


State:   56   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR63 ! <screening definition> --> <token name> .';' 


State:   57   !  Continuation: Identifier
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR52 ! <scanner inherit opt> --> ':' .<identifier> 
         SR99 ! <identifier> --> .Identifier 


State:   58   !  Continuation: Identifier
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           59 ! <vocabulary section> --> '%%VOCABULARY' 
              !                          <internal vocabulary name> .
              !                          <vocabulary definitions> 
              !                          <scanner sections> 
         SR43 ! <vocabulary definitions> --> .<vocabulary definition> 
           61 ! <vocabulary definition> --> .<token name> '=' <number> ';' 
         SR75 ! <token name> --> .<identifier> 
         SR99 ! <identifier> --> .Identifier 
         SR76 ! <token name> --> .<string> 
        SR100 ! <string> --> .String 
           59 ! <vocabulary definitions> --> .<vocabulary definitions> 
              !                              <vocabulary definition> 


State:   59   !  Continuation: '%%SCANNER'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           60 ! <vocabulary section> --> '%%VOCABULARY' 
              !                          <internal vocabulary name> 
              !                          <vocabulary definitions> .
              !                          <scanner sections> 
         SR44 ! <vocabulary definitions> --> <vocabulary definitions> .
              !                              <vocabulary definition> 
         SR46 ! <scanner sections> --> .<scanner section> 
           13 ! <scanner section> --> .'%%SCANNER' <scanner name> 
              !                       <scanner inherit opt> __genSym#2 
              !                       <screening section opt> 
              !                       <undefine token section opt> 
              !                       <token sections> 
           60 ! <scanner sections> --> .<scanner sections> <scanner section> 
           61 ! <vocabulary definition> --> .<token name> '=' <number> ';' 
         SR75 ! <token name> --> .<identifier> 
         SR99 ! <identifier> --> .Identifier 
         SR76 ! <token name> --> .<string> 
        SR100 ! <string> --> .String 


State:   60   !  Continuation: EndOfText
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R40 ! <vocabulary section> --> '%%VOCABULARY' 
              !                          <internal vocabulary name> 
              !                          <vocabulary definitions> 
              !                          <scanner sections> .
              !                          {EndOfText '%%VOCABULARY' }
         SR47 ! <scanner sections> --> <scanner sections> .<scanner section> 
           13 ! <scanner section> --> .'%%SCANNER' <scanner name> 
              !                       <scanner inherit opt> __genSym#2 
              !                       <screening section opt> 
              !                       <undefine token section opt> 
              !                       <token sections> 


State:   61   !  Continuation: '='
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           62 ! <vocabulary definition> --> <token name> .'=' <number> ';' 


State:   62   !  Continuation: Number
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           63 ! <vocabulary definition> --> <token name> '=' .<number> ';' 
        SR101 ! <number> --> .Number 


State:   63   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR45 ! <vocabulary definition> --> <token name> '=' <number> .';' 


State:   64   !  Continuation: '%%SCANNER'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R41 ! <external vocabulary name> --> <identifier> .
              !                                {'%%SCANNER' }
          R42 ! <internal vocabulary name> --> <identifier> .
              !                                {String Identifier }


State:   65   !  Continuation: Class
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           66 ! <map definition section> --> '%%MAP' .<maps> <end opt> 
         SR28 ! <maps> --> .<map> 
           67 ! <map> --> .<class> '=' <class> ';' 
        SR102 ! <class> --> .Class 
           66 ! <maps> --> .<maps> <map> 


State:   66   !  Continuation: '%%MAP'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R17 ! <end opt> --> .
              !               {'%%MAP' '%%DEFINITION' '%%VOCABULARY' }
         SR29 ! <maps> --> <maps> .<map> 
         SR27 ! <map definition section> --> '%%MAP' <maps> .<end opt> 
         SR18 ! <end opt> --> .'%%END' 
           67 ! <map> --> .<class> '=' <class> ';' 
        SR102 ! <class> --> .Class 


State:   67   !  Continuation: '='
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           68 ! <map> --> <class> .'=' <class> ';' 


State:   68   !  Continuation: Class
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           69 ! <map> --> <class> '=' .<class> ';' 
        SR102 ! <class> --> .Class 


State:   69   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR30 ! <map> --> <class> '=' <class> .';' 


State:   70   !  Continuation: Identifier
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           71 ! <definition definition section> --> '%%DEFINITION' .
              !                                     <definition definitions> 
              !                                     <end opt> 
         SR32 ! <definition definitions> --> .<definition definition> 
           72 ! <definition definition> --> .<identifier> '=' <selection rule> 
              !                             ';' 
         SR99 ! <identifier> --> .Identifier 
           72 ! <definition definition> --> .<identifier> '=' '%%' ';' 
           72 ! <definition definition> --> .<identifier> '=' <selection rule> 
              !                             '%%' ';' 
           71 ! <definition definitions> --> .<definition definitions> 
              !                              <definition definition> 


State:   71   !  Continuation: '%%MAP'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R17 ! <end opt> --> .
              !               {'%%MAP' '%%DEFINITION' '%%VOCABULARY' }
         SR33 ! <definition definitions> --> <definition definitions> .
              !                              <definition definition> 
         SR31 ! <definition definition section> --> '%%DEFINITION' 
              !                                     <definition definitions> .
              !                                     <end opt> 
         SR18 ! <end opt> --> .'%%END' 
           72 ! <definition definition> --> .<identifier> '=' <selection rule> 
              !                             ';' 
         SR99 ! <identifier> --> .Identifier 
           72 ! <definition definition> --> .<identifier> '=' '%%' ';' 
           72 ! <definition definition> --> .<identifier> '=' <selection rule> 
              !                             '%%' ';' 


State:   72   !  Continuation: '='
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           73 ! <definition definition> --> <identifier> .'=' <selection rule> 
              !                             ';' 
           73 ! <definition definition> --> <identifier> .'=' '%%' ';' 
           73 ! <definition definition> --> <identifier> .'=' <selection rule> 
              !                             '%%' ';' 


State:   73   !  Continuation: Identifier
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           74 ! <definition definition> --> <identifier> '=' .<selection rule> 
              !                             ';' 
           76 ! <definition definition> --> <identifier> '=' .'%%' ';' 
           74 ! <definition definition> --> <identifier> '=' .<selection rule> 
              !                             '%%' ';' 
           44 ! <selection rule> --> .<concat rule> 
         SR84 ! <concat rule> --> .<closure rule> 
           35 ! <closure rule> --> .<operand> 
         SR94 ! <operand> --> .<identifier> 
         SR99 ! <identifier> --> .Identifier 
         SR95 ! <operand> --> .<string> 
        SR100 ! <string> --> .String 
         SR96 ! <operand> --> .<class> 
        SR102 ! <class> --> .Class 
         SR97 ! <operand> --> .'.' 
           42 ! <operand> --> .'(' <selection rule> ')' 
           35 ! <closure rule> --> .<operand> '*' 
           35 ! <closure rule> --> .<operand> '+' 
           35 ! <closure rule> --> .<operand> '?' 
           35 ! <closure rule> --> .<operand> '{' <number> '}' 
           35 ! <closure rule> --> .<operand> '{' '-' <number> '}' 
           35 ! <closure rule> --> .<operand> '{' <number> '-' '}' 
           35 ! <closure rule> --> .<operand> '{' <number> '-' <number> '}' 
           44 ! <concat rule> --> .<concat rule> <closure rule> 
           74 ! <selection rule> --> .<selection rule> '!' <concat rule> 


State:   74   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR34 ! <definition definition> --> <identifier> '=' <selection rule> .
              !                             ';' 
           75 ! <definition definition> --> <identifier> '=' <selection rule> .
              !                             '%%' ';' 
           33 ! <selection rule> --> <selection rule> .'!' <concat rule> 


State:   75   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR36 ! <definition definition> --> <identifier> '=' <selection rule> 
              !                             '%%' .';' 


State:   76   !  Continuation: ';'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         SR35 ! <definition definition> --> <identifier> '=' '%%' .';' 


State:   77   !  Continuation: '%%MAP'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R10 ! <set definition sections opt> --> <set definition sections> .
              !                                   {'%%MAP' '%%DEFINITION' 
              !                                    '%%VOCABULARY' }
         SR12 ! <set definition sections> --> <set definition sections> .
              !                               <set definition section> 
           78 ! <set definition section> --> .'%%SET' <end opt> 


State:   78   !  Continuation: '%%SET'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R17 ! <end opt> --> .
              !               {'%%SET' '%%MAP' '%%DEFINITION' '%%VOCABULARY' }
         SR26 ! <set definition section> --> '%%SET' .<end opt> 
         SR18 ! <end opt> --> .'%%END' 


State:   79   !  Continuation: '%%SET'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R17 ! <end opt> --> .
              !               {'%%SET' '%%MAP' '%%EXPORT' '%%READER' 
              !                '%%ACTION' '%%CONTEXT' '%%PREHOOK' '%%POSTHOOK' 
              !                '%%DEFINITION' '%%VOCABULARY' '%%DECLARATION' }
         SR19 ! <code section> --> '%%DECLARATION' .<end opt> 
         SR18 ! <end opt> --> .'%%END' 


State:   80   !  Continuation: '%%SET'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R17 ! <end opt> --> .
              !               {'%%SET' '%%MAP' '%%EXPORT' '%%READER' 
              !                '%%ACTION' '%%CONTEXT' '%%PREHOOK' '%%POSTHOOK' 
              !                '%%DEFINITION' '%%VOCABULARY' '%%DECLARATION' }
         SR20 ! <code section> --> '%%CONTEXT' .<end opt> 
         SR18 ! <end opt> --> .'%%END' 


State:   81   !  Continuation: '%%SET'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R17 ! <end opt> --> .
              !               {'%%SET' '%%MAP' '%%EXPORT' '%%READER' 
              !                '%%ACTION' '%%CONTEXT' '%%PREHOOK' '%%POSTHOOK' 
              !                '%%DEFINITION' '%%VOCABULARY' '%%DECLARATION' }
         SR21 ! <code section> --> '%%EXPORT' .<end opt> 
         SR18 ! <end opt> --> .'%%END' 


State:   82   !  Continuation: '%%SET'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R17 ! <end opt> --> .
              !               {'%%SET' '%%MAP' '%%EXPORT' '%%READER' 
              !                '%%ACTION' '%%CONTEXT' '%%PREHOOK' '%%POSTHOOK' 
              !                '%%DEFINITION' '%%VOCABULARY' '%%DECLARATION' }
         SR22 ! <code section> --> '%%READER' .<end opt> 
         SR18 ! <end opt> --> .'%%END' 


State:   83   !  Continuation: '%%SET'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R17 ! <end opt> --> .
              !               {'%%SET' '%%MAP' '%%EXPORT' '%%READER' 
              !                '%%ACTION' '%%CONTEXT' '%%PREHOOK' '%%POSTHOOK' 
              !                '%%DEFINITION' '%%VOCABULARY' '%%DECLARATION' }
         SR23 ! <code section> --> '%%PREHOOK' .<end opt> 
         SR18 ! <end opt> --> .'%%END' 


State:   84   !  Continuation: '%%SET'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R17 ! <end opt> --> .
              !               {'%%SET' '%%MAP' '%%EXPORT' '%%READER' 
              !                '%%ACTION' '%%CONTEXT' '%%PREHOOK' '%%POSTHOOK' 
              !                '%%DEFINITION' '%%VOCABULARY' '%%DECLARATION' }
         SR24 ! <code section> --> '%%ACTION' .<end opt> 
         SR18 ! <end opt> --> .'%%END' 


State:   85   !  Continuation: '%%SET'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R17 ! <end opt> --> .
              !               {'%%SET' '%%MAP' '%%EXPORT' '%%READER' 
              !                '%%ACTION' '%%CONTEXT' '%%PREHOOK' '%%POSTHOOK' 
              !                '%%DEFINITION' '%%VOCABULARY' '%%DECLARATION' }
         SR25 ! <code section> --> '%%POSTHOOK' .<end opt> 
         SR18 ! <end opt> --> .'%%END' 


State:   86   !  Continuation: '%%SET'
- - - - - - - ! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          R17 ! <end opt> --> .
              !               {'%%SET' '%%MAP' SKIPHEADER '%%EXPORT' 
              !                '%%READER' '%%ACTION' '%%CONTEXT' '%%PREHOOK' 
              !                '%%POSTHOOK' '%%DEFINITION' '%%VOCABULARY' 
              !                '%%DECLARATION' }
          SR6 ! <skip section> --> SKIPHEADER .<end opt> 
         SR18 ! <end opt> --> .'%%END' 




                  T H E  P A R S E R  A C T I O N  T A B L E


  TOP OF STACK                                                                    INPUT SYMBOL
STATE NAME                !  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41
--------------------------!---------------------------------------------------------------------------------------------------------------------------
  1   Unknown             !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X R4 R4  X  X R4 R4 R4 R4  X  X R4 R4  X R4  X  X  X R4 R4 R4 
  2   <goal>              !  A  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
  3   <skip sections opt> !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X R2 R2  X  X S86R2 R2 R2  X  X R2 R2  X R2  X  X  X R2 R2 R2 
  4   __genSym#0          !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * R7 R7  *  *  * R7 R7 R7  *  * R7 R7  * R7  *  *  * R7 R7 R7 
  5   <code sections opt> !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S78R9  *  *  * S81S82S84 *  * S80S83 * S85 *  *  * R9 R9 S79
  6   <set definition sect!  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * R3  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * R3 R3  * 
  7   __genSym#1          !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * R13 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * R13R13 * 
  8   <definition sections!  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S65 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S70S10 * 
  9   <vocabulary sections! R1  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X S10 X 
 10   '%%VOCABULARY'      !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -99 X  X  X  X  X  X  X  X  X  X 
 11   <external vocabulary!  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S13 *  *  *  *  *  *  * 
 12   <scanner sections>  ! R39 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X S13 X  X  X  X  X R39 X 
 13   '%%SCANNER'         !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -99 X  X  X  X  X  X  X  X  X  X 
 14   <scanner name>      !  X  X  X  X S57 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X R51R51 X  X  X  X  X  X  X  X  X  X R51 X R51 X  X  X 
 15   <scanner inherit opt!  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * R49R49 *  *  *  *  *  *  *  *  *  * R49 * R49 *  *  * 
 16   __genSym#2          !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * R58R58 *  *  *  *  *  *  *  *  *  * R58 * S53 *  *  * 
 17   <screening section o!  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * R53R53 *  *  *  *  *  *  *  *  *  * S50 *  *  *  *  * 
 18   <undefine token sect!  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S20S47 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 19   <token sections>    ! R48 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X S20S47 X  X  X  X  X  X  X  X R48 X  X  X  X  X R48 X 
 20   '%%RULE'            ! R68 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X R68 X R68 X  X R68R68 X  X  X  X  X R68 X  X R68 X  X  X  X  X R68 X 
 21   __genSym#4          ! R70 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * R70 * R70 *  * R70R70 *  *  *  *  * R70 *  * R70 *  *  *  *  * R70 * 
 22   <tokens opt>        ! R17 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -100 * -18 *  * R17R17 *  *  *  *  * -99 *  * R17 *  *  *  *  * R17 * 
 23   <token name>        !  X  X S24 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 24   '='                 !  X  X  X  X  X  X  X  X  X  X  X  X  X -97S42 X -102 X -100 X  X  X  X  X  X  X  X  X  X S30-99 X  X  X  X  X S28 X  X  X  X 
 25   <lookahead rule>    !  * -79 * R77 *  *  *  *  *  *  *  *  *  *  *  *  * S27 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 26   <action opt>        !  *  *  * -72 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 27   '%%DO'              !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -99 X  X  X  X  X  X  X  X  X  X 
 28   '_ENDOFTEXT'        !  X -79 X R77 X  X  X  X  X  X  X  X  X  X  X  X  X S27 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 29   <action opt>        !  *  *  * -73 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 30   '_UNKNOWN'          !  X -79 X R77 X  X  X  X  X  X  X  X  X  X  X  X  X S27 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 31   <action opt>        !  *  *  * -74 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 32   <selection rule>    !  * R80 * R80 * S45S33 *  *  *  *  *  *  *  *  X  * R80 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 33   '!'                 !  X  X  X  X  X  X  X  X  X  X  X  X  X -97S42 X -102 X -100 X  X  X  X  X  X  X  X  X  X  X -99 X  X  X  X  X  X  X  X  X  X 
 34   <concat rule>       !  X R83 X R83 X R83R83 X  X  X  X  X  X -97S42R83-102R83-100 X  X  X  X  X  X  X  X  X  X  X -99 X  X  X  X  X  X  X  X  X  X 
 35   <operand>           !  X R86 X R86 X R86R86-87-88-89S36 X  X R86R86R86R86R86R86 X  X  X  X  X  X  X  X  X  X  X R86 X  X  X  X  X  X  X  X  X  X 
 36   '{'                 !  X  X  X  X  X  X  X  X  X  X  X  X S40 X  X  X  X  X  X -101 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 37   <number>            !  X  X  X  X  X  X  X  X  X  X  X -90S38 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 38   '-'                 !  X  X  X  X  X  X  X  X  X  X  X -92 X  X  X  X  X  X  X -101 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 39   <number>            !  X  X  X  X  X  X  X  X  X  X  X -93 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 40   '-'                 !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -101 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 41   <number>            !  X  X  X  X  X  X  X  X  X  X  X -91 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 42   '('                 !  X  X  X  X  X  X  X  X  X  X  X  X  X -97S42 X -102 X -100 X  X  X  X  X  X  X  X  X  X  X -99 X  X  X  X  X  X  X  X  X  X 
 43   <selection rule>    !  *  X  *  X  *  X S33 *  *  *  *  *  *  *  * -98 *  X  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 44   <concat rule>       !  X R82 X R82 X R82R82 X  X  X  X  X  X -97S42R82-102R82-100 X  X  X  X  X  X  X  X  X  X  X -99 X  X  X  X  X  X  X  X  X  X 
 45   '/'                 !  X  X  X  X  X  X  X  X  X  X  X  X  X -97S42 X -102 X -100 X  X  X  X  X  X  X  X  X  X  X -99 X  X  X  X  X  X  X  X  X  X 
 46   <selection rule>    !  * R81 * R81 *  X S33 *  *  *  *  *  *  *  *  X  * R81 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 47   '%%SKIP'            ! R69 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X R69 X R69 X  X R69R69 X  X  X  X  X R69 X  X R69 X  X  X  X  X R69 X 
 48   __genSym#5          ! R70 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * R70 * R70 *  * R70R70 *  *  *  *  * R70 *  * R70 *  *  *  *  * R70 * 
 49   <tokens opt>        ! R17 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -100 * -18 *  * R17R17 *  *  *  *  * -99 *  * R17 *  *  *  *  * R17 * 
 50   '%%UNDEFINE'        !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X R55 X R55 X  X R55R55 X  X  X  X  X R55 X  X  X  X  X  X  X  X  X  X 
 51   <undefined token nam!  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -100 * -18 *  * R17R17 *  *  *  *  * -99 *  *  *  *  *  *  *  *  *  * 
 52   <token name>        !  X  X  X -57 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 53   '%%SCREENING'       !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X R60 X R60 X  X R60R60 X  X  X  X  X R60 X  X  X  X R60 X  X  X  X  X 
 54   __genSym#3          !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * R61 * R61 *  * R61R61 *  *  *  *  * R61 *  *  *  * R61 *  *  *  *  * 
 55   <screening definitio!  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -100 * -18 *  * R17R17 *  *  *  *  * -99 *  *  *  * R17 *  *  *  *  * 
 56   <token name>        !  X  X  X -63 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 57   ':'                 !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -99 X  X  X  X  X  X  X  X  X  X 
 58   <internal vocabulary!  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -100 *  *  *  *  *  *  *  *  *  *  * -99 *  *  *  *  *  *  *  *  *  * 
 59   <vocabulary definiti!  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -100 X  X  X  X  X  X  X  X  X  X  X -99 X  X S13 X  X  X  X  X  X  X 
 60   <scanner sections>  ! R40 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X S13 X  X  X  X  X R40 X 
 61   <token name>        !  X  X S62 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 62   '='                 !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -101 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 63   <number>            !  X  X  X -45 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 64   <identifier>        !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X R42 X  X  X  X  X  X  X  X  X  X  X R42 X  X R41 X  X  X  X  X  X  X 
 65   '%%MAP'             !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -102 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 66   <maps>              !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -102 X  X  X -18 X R17 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X R17R17 X 
 67   <class>             !  X  X S68 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 68   '='                 !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -102 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 69   <class>             !  X  X  X -30 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 70   '%%DEFINITION'      !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -99 X  X  X  X  X  X  X  X  X  X 
 71   <definition definiti!  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -18 X R17 X  X  X  X  X  X  X -99 X  X  X  X  X  X  X R17R17 X 
 72   <identifier>        !  X  X S73 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 73   '='                 !  X S76 X  X  X  X  X  X  X  X  X  X  X -97S42 X -102 X -100 X  X  X  X  X  X  X  X  X  X  X -99 X  X  X  X  X  X  X  X  X  X 
 74   <selection rule>    !  * S75 * -34 *  X S33 *  *  *  *  *  *  *  *  X  *  X  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 75   '%%'                !  X  X  X -36 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 76   '%%'                !  X  X  X -35 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X 
 77   <set definition sect!  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X S78R10 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X R10R10 X 
 78   '%%SET'             !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -18R17R17 X  X  X  X  X  X  X  X  X  X  X  X  X  X  X R17R17 X 
 79   '%%DECLARATION'     !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -18R17R17 X  X  X R17R17R17 X  X R17R17 X R17 X  X  X R17R17R17
 80   '%%CONTEXT'         !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -18R17R17 X  X  X R17R17R17 X  X R17R17 X R17 X  X  X R17R17R17
 81   '%%EXPORT'          !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -18R17R17 X  X  X R17R17R17 X  X R17R17 X R17 X  X  X R17R17R17
 82   '%%READER'          !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -18R17R17 X  X  X R17R17R17 X  X R17R17 X R17 X  X  X R17R17R17
 83   '%%PREHOOK'         !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -18R17R17 X  X  X R17R17R17 X  X R17R17 X R17 X  X  X R17R17R17
 84   '%%ACTION'          !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -18R17R17 X  X  X R17R17R17 X  X R17R17 X R17 X  X  X R17R17R17
 85   '%%POSTHOOK'        !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -18R17R17 X  X  X R17R17R17 X  X R17R17 X R17 X  X  X R17R17R17
 86   SKIPHEADER          !  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X -18R17R17 X  X R17R17R17R17 X  X R17R17 X R17 X  X  X R17R17R17



                         T H E  G O T O  T A B L E


  TOP OF STACK                                                                                           SYMBOL
STATE NAME                ! 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95
--------------------------!------------------------------------------------------------------------------------------------------------------------------------------------------------------
  1   Unknown             !  * S2  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S3  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
  2   <goal>              !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
  3   <skip sections opt> !  *  *  *  *  *  *  *  *  * S4  *  *  *  *  *  *  *  *  *  * -5  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
  4   __genSym#0          !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S5  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
  5   <code sections opt> !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -8  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -11 *  *  *  * S77 *  *  *  *  * S6  * 
  6   <set definition sect!  *  *  *  *  *  *  *  *  *  * S7  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
  7   __genSym#1          !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S8  *  *  *  *  *  *  *  * 
  8   <definition sections!  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -14-37S9  *  *  *  *  *  *  * -15 *  *  *  *  *  *  *  *  *  * -16
  9   <vocabulary sections!  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -38 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 10   '%%VOCABULARY'      !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S64 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S11S58 *  *  *  *  * 
 11   <external vocabulary!  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -46S12 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 12   <scanner sections>  !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -47 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 13   '%%SCANNER'         !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -50 *  *  *  *  *  * S14 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 14   <scanner name>      !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S15 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 15   <scanner inherit opt!  *  *  *  *  *  *  *  *  *  *  * S16 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 16   __genSym#2          !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S17 *  *  *  *  *  *  *  *  *  *  *  *  * 
 17   <screening section o!  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S18 *  * 
 18   <undefine token sect!  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -64 * S19 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 19   <token sections>    !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -65 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 20   '%%RULE'            !  *  *  *  *  *  *  *  *  *  *  *  *  * S21 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 21   __genSym#4          !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S22 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 22   <tokens opt>        !  *  *  *  * -71 * -76-66 *  *  *  *  *  *  * -75S23 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 23   <token name>        !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 24   '='                 !  *  *  * -96 *  * -95 * S35 *  *  *  *  *  * -94 *  *  * S44 *  *  * -84 * S32 * S25 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 25   <lookahead rule>    !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S26 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 26   <action opt>        !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 27   '%%DO'              !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -78 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 28   '_ENDOFTEXT'        !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S29 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 29   <action opt>        !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 30   '_UNKNOWN'          !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S31 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 31   <action opt>        !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 32   <selection rule>    !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 33   '!'                 !  *  *  * -96 *  * -95 * S35 *  *  *  *  *  * -94 *  *  * S34 *  *  * -84 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 34   <concat rule>       !  *  *  * -96 *  * -95 * S35 *  *  *  *  *  * -94 *  *  *  *  *  *  * -85 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 35   <operand>           !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 36   '{'                 !  *  *  *  *  * S37 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 37   <number>            !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 38   '-'                 !  *  *  *  *  * S39 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 39   <number>            !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 40   '-'                 !  *  *  *  *  * S41 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 41   <number>            !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 42   '('                 !  *  *  * -96 *  * -95 * S35 *  *  *  *  *  * -94 *  *  * S44 *  *  * -84 * S43 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 43   <selection rule>    !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 44   <concat rule>       !  *  *  * -96 *  * -95 * S35 *  *  *  *  *  * -94 *  *  *  *  *  *  * -85 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 45   '/'                 !  *  *  * -96 *  * -95 * S35 *  *  *  *  *  * -94 *  *  * S44 *  *  * -84 * S46 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 46   <selection rule>    !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 47   '%%SKIP'            !  *  *  *  *  *  *  *  *  *  *  *  *  *  * S48 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 48   __genSym#5          !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S49 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 49   <tokens opt>        !  *  *  *  * -71 * -76-67 *  *  *  *  *  *  * -75S23 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 50   '%%UNDEFINE'        !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S51 *  *  *  * 
 51   <undefined token nam!  *  *  *  *  *  * -76-54 *  *  *  *  *  *  * -75S52 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -56 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 52   <token name>        !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 53   '%%SCREENING'       !  *  *  *  *  *  *  *  *  *  *  *  * S54 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 54   __genSym#3          !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S55 *  *  * 
 55   <screening definitio!  *  *  *  *  *  * -76-59 *  *  *  *  *  *  * -75S56 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -62 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 56   <token name>        !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 57   ':'                 !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -52 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 58   <internal vocabulary!  *  *  *  *  *  * -76 *  *  *  *  *  *  *  * -75S61 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -43 *  *  *  * S59 *  *  *  *  *  *  *  *  * 
 59   <vocabulary definiti!  *  *  *  *  *  * -76 *  *  *  *  *  *  *  * -75S61 *  *  *  *  *  *  *  *  *  *  * -46S60 *  *  *  *  *  *  *  *  * -44 *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 60   <scanner sections>  !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -47 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 61   <token name>        !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 62   '='                 !  *  *  *  *  * S63 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 63   <number>            !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 64   <identifier>        !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 65   '%%MAP'             ! -28 * S66S67 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 66   <maps>              ! -29 *  * S67 *  *  * -27 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 67   <class>             !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 68   '='                 !  *  *  * S69 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 69   <class>             !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 70   '%%DEFINITION'      !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * S72 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -32 *  *  *  * S71 *  *  *  *  *  *  *  *  *  * 
 71   <definition definiti!  *  *  *  *  *  *  * -31 *  *  *  *  *  *  * S72 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -33 *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 72   <identifier>        !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 73   '='                 !  *  *  * -96 *  * -95 * S35 *  *  *  *  *  * -94 *  *  * S44 *  *  * -84 * S74 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 74   <selection rule>    !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 75   '%%'                !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 76   '%%'                !  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 77   <set definition sect!  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * -12 *  *  *  *  *  *  *  *  *  *  *  * 
 78   '%%SET'             !  *  *  *  *  *  *  * -26 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 79   '%%DECLARATION'     !  *  *  *  *  *  *  * -19 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 80   '%%CONTEXT'         !  *  *  *  *  *  *  * -20 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 81   '%%EXPORT'          !  *  *  *  *  *  *  * -21 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 82   '%%READER'          !  *  *  *  *  *  *  * -22 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 83   '%%PREHOOK'         !  *  *  *  *  *  *  * -23 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 84   '%%ACTION'          !  *  *  *  *  *  *  * -24 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 85   '%%POSTHOOK'        !  *  *  *  *  *  *  * -25 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 
 86   SKIPHEADER          !  *  *  *  *  *  *  * -6  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  * 


           Summary of the table generation process
           ---------------------------------------

Number of states =   86
Total table space =  17362 bytes
     T-table =    7070 bytes
     NTS-table =  9492 bytes
     VOC-table =   800 bytes




               T H E   P A C K E D   A C T I O N   T A B L E


               Row Displacement Check Vector

Column       !  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
-------------!------------------------------------------------------------
Row Index    !  2 35 61 35 14 35 35 35 35 35 35 37 37 35 35 35 35 35 35 62 

Column       ! 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
-------------!------------------------------------------------------------
Row Index    ! 86 86 86 14 14 86 86 86 86 63 35 86 86  7 86 14 38 14 86 86 

Column       ! 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60
-------------!------------------------------------------------------------
Row Index    ! 86  1  1 65 38  1  1  1  1  7  7  1  1 59  1 79 79 79  1  1 

Column       ! 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80
-------------!------------------------------------------------------------
Row Index    !  1 79 79 79 26 59 79 79 59 79 80 80 80 79 79 79 80 80 80 18 

Column       ! 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99100
-------------!------------------------------------------------------------
Row Index    ! 18 80 80 64 80 81 81 81 80 80 80 81 81 81 67 64 81 81 64 81 

Column       !101102103104105106107108109110111112113114115116117118119120
-------------!------------------------------------------------------------
Row Index    ! 82 82 82 81 81 81 82 82 82 68 69 82 82 58 82 83 83 83 82 82 

Column       !121122123124125126127128129130131132133134135136137138139140
-------------!------------------------------------------------------------
Row Index    ! 82 83 83 83 70 58 83 83 27 83 84 84 84 83 83 83 84 84 84  9 

Column       !141142143144145146147148149150151152153154155156157158159160
-------------!------------------------------------------------------------
Row Index    ! 72 84 84 13 84 85 85 85 84 84 84 85 85 85 36 29 85 85  8 85 

Column       !161162163164165166167168169170171172173174175176177178179180
-------------!------------------------------------------------------------
Row Index    ! 75 36 76 85 85 85  3  3 17 17  3  3  3  3  8  8  3  3  9  3 

Column       !181182183184185186187188189190191192193194195196197198199200
-------------!------------------------------------------------------------
Row Index    ! 17  5  5  3  3  3  5  5  5 39 52  5  5 43  5 73 19 40  5  5 

Column       !201202203204205206207208209210211212213214215216217218219220
-------------!------------------------------------------------------------
Row Index    !  5 34 43 34 41 34 34 73 73 25 73 25 73 34 34 34 34 34 34 19 

Column       !221222223224225226227228229230231232233234235236237238239240
-------------!------------------------------------------------------------
Row Index    ! 19  4  4 10 73 25  4  4  4 19 34  4  4 56  4 19 57 31  4  4 

Column       !241242243244245246247248249250251252253254255256257258259260
-------------!------------------------------------------------------------
Row Index    !  4 44 22 44 23 44 44 33 33 11 33  X 33 44 44 44 44 44 44 47 

Column       !261262263264265266267268269270271272273274275276277278279280
-------------!------------------------------------------------------------
Row Index    ! 22  X 22  X 33 22 22 48  X 74 44 74 22  X 74 22  X 47  X 47 

Column       !281282283284285286287288289290291292293294295296297298299300
-------------!------------------------------------------------------------
Row Index    !  X 22 47 47 49 48  X 48  X 47 48 48 47 77 77 20  X 48 47  X 

Column       !301302303304305306307308309310311312313314315316317318319320
-------------!------------------------------------------------------------
Row Index    ! 48  X 49  X 49  X 48 49 49 21 77 77  X 20 49 20  X 49 20 20 

Column       !321322323324325326327328329330331332333334335336337338339340
-------------!------------------------------------------------------------
Row Index    !  X 24 24 49 24 20 24 21 20 21  X  X 21 21 20  X  X 24 24 21 

Column       !341342343344345346347348349350351352353354355356357358359360
-------------!------------------------------------------------------------
Row Index    ! 60 53 21 53 24  X 53 53 21 54  X 54  X 53 54 54  X 55 53 55 

Column       !361362363364365366367368369370371372373374375376377378379380
-------------!------------------------------------------------------------
Row Index    !  6 54 55 55  X 71 54 71  X 55 78 78 78 60 55 71  6  6  X 60 

Column       !381382383384385386387388389390391392393394395396397398399400
-------------!------------------------------------------------------------
Row Index    ! 50  X 50 71 71 50 50  X 78 78  X 51 50 51 15 15 51 51  X 42 

Column       !401402403404405406407408409410411412413414415416417418419420
-------------!------------------------------------------------------------
Row Index    ! 42  X 42 51 42 32 15 32 15 32 32 12 45 45 66 45 42 45 66  X 

Column       !421422423424425426427428429430431432433434435436437438439440
-------------!------------------------------------------------------------
Row Index    ! 66 32  X 46  X 46 16 16 46 45 28 30 28 30  X  X 66 66 16 46 

Column       !441442443444445446447448449450451452453454455456457458459460
-------------!------------------------------------------------------------
Row Index    ! 16  X  X  X 12  X 28 30  X  X 12  X  X  X  X  X  X  X  X  X 

Column       !461462463464465466467468469470471
-------------!---------------------------------
Row Index    !  X  X  X  X  X  X  X  X  X  X  X 

               Row mapping vector

Row          !  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86
-------------!------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Index        ! 21  1146201161339 12137140194217412114  1372404146 57197296310243243309209 62 99430153431235405235201  1143  1 26179179194387188241400423260268285363374188324332340231207 96 36341  1  1 27 66 28399 93 94108 95346139195269158160273351 36 51 66 81 96111126  1

               Compressed ACTION table

Index        !  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
-------------!------------------------------------------------------------
Entry        !  A R86S62R86S57R86R86-87-88-89S36-90S38R86R86R86R86R86R86-101

Index        ! 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
-------------!------------------------------------------------------------
Entry        ! -18R17R17R51R51R17R17R17R17-45R86R17R17R13R17R51-92R51R17R17

Index        ! 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60
-------------!------------------------------------------------------------
Entry        ! R17R4 R4 -102-101R4 R4 R4 R4 R13R13R4 R4 -100R4 -18R17R17R4 R4 

Index        ! 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80
-------------!------------------------------------------------------------
Entry        ! R4 R17R17R17-72-99R17R17S13R17-18R17R17R17R17R17R17R17R17S20

Index        ! 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99100
-------------!------------------------------------------------------------
Entry        ! S47R17R17R42R17-18R17R17R17R17R17R17R17R17S68R42R17R17R41R17

Index        !101102103104105106107108109110111112113114115116117118119120
-------------!------------------------------------------------------------
Entry        ! -18R17R17R17R17R17R17R17R17-102-30R17R17-100R17-18R17R17R17R17

Index        !121122123124125126127128129130131132133134135136137138139140
-------------!------------------------------------------------------------
Entry        ! R17R17R17R17-99-99R17R17-99R17-18R17R17R17R17R17R17R17R17R1 

Index        !141142143144145146147148149150151152153154155156157158159160
-------------!------------------------------------------------------------
Entry        ! S73R17R17-99R17-18R17R17R17R17R17R17R17R17S40-73R17R17S65R17

Index        !161162163164165166167168169170171172173174175176177178179180
-------------!------------------------------------------------------------
Entry        ! -36-101-35R17R17R17R2 R2 R53R53S86R2 R2 R2 S70S10R2 R2 S10R2 

Index        !181182183184185186187188189190191192193194195196197198199200
-------------!------------------------------------------------------------
Entry        ! S50S78R9 R2 R2 R2 S81S82S84-93-57S80S83S33S85S76R48-101R9 R9 

Index        !201202203204205206207208209210211212213214215216217218219220
-------------!------------------------------------------------------------
Entry        ! S79R83-98R83-91R83R83-97S42-79-102R77-100-97S42R83-102R83-100S20

Index        !221222223224225226227228229230231232233234235236237238239240
-------------!------------------------------------------------------------
Entry        ! S47R7 R7 -99-99S27R7 R7 R7 R48-99R7 R7 -63R7 R48-99-74R7 R7 

Index        !241242243244245246247248249250251252253254255256257258259260
-------------!------------------------------------------------------------
Entry        ! R7 R82R17R82S24R82R82-97S42S13-102 X -100-97S42R82-102R82-100R69

Index        !261262263264265266267268269270271272273274275276277278279280
-------------!------------------------------------------------------------
Entry        ! -100 X -18 X -99R17R17R70 X S75-99-34-99 X S33R17 X R69 X R69

Index        !281282283284285286287288289290291292293294295296297298299300
-------------!------------------------------------------------------------
Entry        !  X R17R69R69R17R70 X R70 X R69R70R70R69S78R10R68 X R70R69 X 

Index        !301302303304305306307308309310311312313314315316317318319320
-------------!------------------------------------------------------------
Entry        ! R70 X -100 X -18 X R70R17R17R70R10R10 X R68-99R68 X R17R68R68

Index        !321322323324325326327328329330331332333334335336337338339340
-------------!------------------------------------------------------------
Entry        !  X -97S42R17-102R68-100R70R68R70 X  X R70R70R68 X  X S30-99R70

Index        !341342343344345346347348349350351352353354355356357358359360
-------------!------------------------------------------------------------
Entry        ! R40R60R70R60S28 X R60R60R70R61 X R61 X R60R61R61 X -100R60-18

Index        !361362363364365366367368369370371372373374375376377378379380
-------------!------------------------------------------------------------
Entry        ! R3 R61R17R17 X -18R61R17 X -99-18R17R17S13R17-99R3 R3  X R40

Index        !381382383384385386387388389390391392393394395396397398399400
-------------!------------------------------------------------------------
Entry        ! R55 X R55R17R17R55R55 X R17R17 X -100R55-18R49R49R17R17 X -97

Index        !401402403404405406407408409410411412413414415416417418419420
-------------!------------------------------------------------------------
Entry        ! S42 X -102-99-100R80R49R80R49S45S33R39-97S42-102-102-99-100-18 X 

Index        !421422423424425426427428429430431432433434435436437438439440
-------------!------------------------------------------------------------
Entry        ! R17R80 X R81 X R81R58R58S33-99-79-79R77R77 X  X R17R17R58R81

Index        !441442443444445446447448449450451
-------------!---------------------------------
Entry        ! S53 X  X  X S13 X S27S27 X  X R39




                   T H E   P A C K E D   G O T O   T A B L E


               Row mapping vector

Row          !  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86
-------------!------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Index        !138 49117110115167133110133 57117 75 62116143118113 85147160157 48 44 42162 43166164 43 78 43 43 91132 43 42 43 54 43144 43 43 43 92 67 43145143112116114 43157120116 43157118 73147 43171 43 42 78 53 42176 42 70110 42 68 42 42 42142177178179180181182183184185

               Compressed GOTO table

Index        ! 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61
-------------!------------------------------------------------------------
Entry        !  X  X  X -96-96S37-95-95S35S35-71-29-76-66S67-94-94S39-27S44

Index        ! 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81
-------------!------------------------------------------------------------
Entry        ! S44-75S23-84-84S32S43S25-96-96S64-95-95S35S35-50-28-76S66S67

Index        ! 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99100101
-------------!------------------------------------------------------------
Entry        ! -94-94S14S72S44S44-75S61-84-84S46S74-96-96S31-95-95S35S35-46

Index        !102103104105106107108109110111112113114115116117118119120121
-------------!------------------------------------------------------------
Entry        ! S60-47S11S58-94-94-32-64S34S19-44S71-84-85-71-31-76-67-76-54

Index        !122123124125126127128129130131132133134135136137138139140141
-------------!------------------------------------------------------------
Entry        ! -76-59-76S72S4 -75S23-75S52-75S56-75S61-96-8 -5 -95S2 S35S5 

Index        !142143144145146147148149150151152153154155156157158159160161
-------------!------------------------------------------------------------
Entry        ! -14-37S9 -46S12-94-33S41-56S15-15-62S16-85-11-43S17S48S49S77

Index        !162163164165166167168169170171172173174175176177178179180181
-------------!------------------------------------------------------------
Entry        ! S59-16S18S51-38S6 S3 S54S55-65-52S21S22-47S63S7 S8 S69S26-78

Index        !182183184185186187188189190191192
-------------!---------------------------------
Entry        ! S29-12-26-19-20-21-22-23-24-25-6 



                    Summary of the packing process
                    ------------------------------

Total table space =   2955 bytes
     T-table   =  1563 bytes
     NTS-table =   592 bytes
     VOC-table =   800 bytes

