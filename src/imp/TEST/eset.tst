-- Vanlig tilldelning ett element
%%ESET V1 (11)
%%(V1)
11                                          * * * FACIT * * *   
-- Ut|ka med tv} element
%%ESET V1 (,12,13)
%%(V1)
11,12,13                                    * * * FACIT * * *   
-- Vanlig tilldelning ett element
%%ESET V1 (11)
%%(V1)
11                                          * * * FACIT * * *  
%%ESET NULL ()
"%%(NULL)"
""                                          * * * FACIT * * *
%%ESET SUBLIST (1, {2,3},4)
%%(SUBLIST)
1,{2,3},4                                   * * * FACIT * * *
%%ESET V22 (12)
%%ESET A (V1 ,V22, V3)
%%(A)
11,12,`%%(V3)                                * * * FACIT * * *
%%ESET V1 (21)
%%ESET V22 (22)
%%(A)
11,12,`%%(V3)                                * * * FACIT * * *
%%ESET V1 (31)
%%ESET V22 (32)
%%(A)
11,12,`%%(V3)                                * * * FACIT * * *
%%ESET V1 (1,2)
%%ESET V3 (V1)
%%ESET A (V1, V2, V3)
%%ESET %%(VAR) (V1, V2, V3)
`%%SET `%%(VAR) (1,2,`%%(V2),V1)               * * * FACIT * * * 
%%ESET %%(VAR2) (V1, 6*87+9-VAR3, V3)
`%%SET `%%(VAR2) (1,2,`%%(531-VAR3),V1)        * * * FACIT * * * 
%%(A)
1,2,`%%(V2),V1                               * * * FACIT * * *
%%ESET V2 (3)
%%(A)
1,2,3,V1                                    * * * FACIT * * *
%%SET SUBLIST (1, 2, {3,4})
%%(SUBLIST)
1,2,{3,4}                                   * * * FACIT * * *
%%({1,2})
{1,2}                                       * * * FACIT * * *
%%({1,{3,4,fem},2})
{1,{3,4,fem},2}                             * * * FACIT * * *
%%ESET SUBLIST (1, {2,3},4)
%%(SUBLIST[0])
3                                           * * * FACIT * * *
%%(SUBLIST[1])
1                                           * * * FACIT * * *
%%(SUBLIST[2])
{2,3}                                       * * * FACIT * * *
%%(SUBLIST[3])
4                                           * * * FACIT * * *
%%(SUBLIST[4])
`%%(SUBLIST[4])                              * * * FACIT * * *
%%(SUBLIST[5])
`%%(SUBLIST[5])                              * * * FACIT * * *
%%(SUBLIST)
1,{2,3},4                                   * * * FACIT * * *
%%ESET SUBLIST (1, 2, {3,4})
%%(SUBLIST[0])
3                                           * * * FACIT * * *
%%(SUBLIST[1])
1                                           * * * FACIT * * *
%%(SUBLIST[2])
2                                           * * * FACIT * * *
%%(SUBLIST[3])
{3,4}                                       * * * FACIT * * *
%%(SUBLIST[4])
`%%(SUBLIST[4])                              * * * FACIT * * *
%%(SUBLIST[5])
`%%(SUBLIST[5])                              * * * FACIT * * *
%%(SUBLIST)
1,2,{3,4}                                   * * * FACIT * * *
%%ESET EXPR ({1}+{2})
%%(EXPR)
3                                           * * * FACIT * * *
%%SET NULL ()
%%({11}+{2, %%(NULL)}-EXPR)
10                                          * * * FACIT * * *
%%(16+4)
20                                          * * * FACIT * * *
%%(16-4)
12                                          * * * FACIT * * *
%%(16/4)
4                                           * * * FACIT * * *
%%(16*4)
64                                          * * * FACIT * * *
%%(4+16)
20                                          * * * FACIT * * *
%%(4-16)
-12                                         * * * FACIT * * *
%%(4/16)
0                                           * * * FACIT * * *
%%(4*16)
64                                          * * * FACIT * * *
%%SET VAR2 (Bottom Level)
%%SET VAR1 (VAR2)
%%ESET VAR%%(4*16) (VAR1)
%%(VAR64)
VAR2                                        * * * FACIT * * *
%%(%%(VAR64))
BottomLevel                                 * * * FACIT * * *
%%(%%(%%(VAR64)))
`%%(BottomLevel)                             * * * FACIT * * *
%%(%%(%%(%%(VAR64))))
`%%(`%%(BottomLevel))                         * * * FACIT * * *

