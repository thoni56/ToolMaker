DOCUMENT XREFTEST;

DECLARE; 
!BEGIN SQL COMMON 0!

%%SET pzVersion("1.02 ")

%%SET tables()

%%SET tabNos()

%%SET remTables()

%%SET remTabNos()

%%SET tableOwner()

%%SET tableUser()

!END SQL!



! Test a PLEX-SQL statement direct after a plex statement !
c1 = c2;
!BEGIN SQL INCLUDE_TABLE 0!
!******************************************************************************!

!EXEC SQL INCLUDE TABLE table2!

!------------------------------------------------------------------------------!

%%SET remTables(,TABLE2)
%%SET remTabNos(,256)
%%SET cols256("DBNUM", "COL1", "COL2", "COL3", "COL4", "COL5", "COL6", "COL7", "COL8")
%%SET colLen256(2, 8, 1, 1, 8, 4, 16, 1, 8)
%%SET colNull256(0, 0, 0, 1, 1, 0, 1, 1, 1)
%%SET colTypes256("DBNUMBER", "STRING", "BITS", "BITS", "STRING", "NUMSTRING", "STRING", "SYMBOL", "PACKED NUMSTRING")
%%SET colSizes256(32, 15, 16, 16, 15, 7, 31, 1, 28)
%%SET bTrees256(2, 3, 4)
%%SET bTreeCols256_2(2)
%%SET bTreeCols256_3(5)
%%SET bTreeCols256_4(7)
%%SET symCols256(8)
%%SET symVals256_8(FALSE, TRUE)
%%SET symLits256_8(0, 1)


!******************************************************************************!
!END SQL!


! Test a PLEX-SQL statement direct after an end comment !
! xxxxx !
!BEGIN SQL INCLUDE 0!
!******************************************************************************!

!EXEC SQL INCLUDE PROTECTION!

!------------------------------------------------------------------------------!



!******************************************************************************!
!END SQL!



!BEGIN SQL INCLUDE_TABLE 0!
!******************************************************************************!

!EXEC SQL INCLUDE TABLE table3 CREATE!

!------------------------------------------------------------------------------!

%%SET tables(,TABLE3)
%%SET tabNos(,0)
%%SET tabSlogans(,"""""")
%%SET tabSaes(,"10")
%%SET tabMinSizes(,0)
%%SET tabMaxSizes(,65000)
%%SET tabDivDirs(,1)
%%SET tabRelDivs(,1)
%%SET tabDivConsts(,0)
%%SET workSaes(,"20")
%%SET workMinSizes(,0)
%%SET workMaxSizes(,500)
%%SET workDivDirs(,1)
%%SET workRelDivs(,1)
%%SET workDivConsts(,0)
%%SET tabRAuths(,0)
%%SET tabWAuths(,0)
%%SET tabChecks(,2)
%%SET cols0("DBNUM", "COL1", "COL2", "COL3", "COL4", "COL5", "COL6", "COL7", "COL8")
%%SET rnCols0(COL9)
%%SET bitsCols0(3, 4)
%%SET symCols0(8)
%%SET strCols0(2, 5, 7)
%%SET numCols0(6)
%%SET packNumCols0(9)
%%SET normCols0(1, 3, 4, 7, 8, 9)
%%SET colTypes0("DBNUMBER", "STRING", "BITS", "BITS", "STRING", "NUMSTRING", "STRING", "SYMBOL", "PACKED NUMSTRING")
%%SET colSizes0(32, 15, 16, 16, 15, 7, 31, 1, 28)
%%SET colProps0("", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD")
%%SET colNull0(0, 0, 0, 1, 1, 1, 1, 1, 1)
%%SET colLen0(2, 8, 1, 1, 8, 4, 16, 1, 8)
%%SET colSlogans0("""""", """column 1""", """column 2""", """column 3""", """column 4""", """""", """""", """""", """""")
%%SET colVis0("READWRITE", "READWRITE", "READWRITE", "READWRITE", "READWRITE", "READWRITE", "READWRITE", "READWRITE", "READWRITE")
%%SET colNonVol0(1, 1, 1, 1, 1, 1, 1, 1, 1)
%%SET defCols0(4, 5, 6, 7, 8, 9)
%%SET defVal0_4("NULL")
%%SET defVal0_5("""xxx""")
%%SET defVal0_6("NULL")
%%SET defVal0_7("NULL")
%%SET defVal0_8("NULL")
%%SET defVal0_9("NULL")
%%SET symVals0_8(FALSE, TRUE)
%%SET symLits0_8(0, 1)
%%SET bTrees0(2, 3, 4)
%%SET bTreeCols0_2(2)
%%SET bTreeCols0_3(5)
%%SET bTreeCols0_4(6)
%%SET aks0(3)
%%SET fks0()
%%SET schConst0_2(18)
%%SET schConst0_3(22)
%%SET schConst0_4(17)
%%SET prepLabel0(PREP1)
%%SET prepReturn0(PREPRET)
%%SET commLabel0(POST1)
%%SET commReturn0(POSTRET)
%%SET rollLabel0(ROLL1)
%%SET rollReturn0(ROLLRET)
%%SET scanPred0_1("", "SQLC_TABLE3_COL3_Data", "", "SQLM_TABLE3_OperRow", "0", "", "", "<", "False", "", "False")
%%SET scanPred0_2("", "SQLC_TABLE3_COL2_Data", "", "SQLM_TABLE3_OperRow", "0", "", "", "<", "False", "True", "False")
%%SET scanCols0_1(4)
%%SET scanCols0_2(3)
%%SET scanNulls0_1()
%%SET scanNulls0_2()
%%SET scanNullPtrs0_1()
%%SET scanNullPtrs0_2()
%%SET colMin0_3(0)
%%SET colMin0_4(0)
%%SET colMax0_3(65535)
%%SET colMax0_4(65535)


!******************************************************************************!
!END SQL!


VARIABLE a 16 DS;
VARIABLE b 16 DS;
VARIABLE c 16 DS;
VARIABLE d 16 DS;

!BEGIN SQL INCLUDE_TABLE 0!
!******************************************************************************!

!EXEC SQL INCLUDE TABLE table1!

!------------------------------------------------------------------------------!

%%SET remTables(,TABLE1)
%%SET remTabNos(,257)
%%SET cols257("DBNUM", "COL1", "COL2", "COL3", "COL4", "COL5", "COL6", "COL7", "COL8")
%%SET colLen257(2, 8, 1, 1, 8, 4, 16, 1, 8)
%%SET colNull257(0, 0, 0, 1, 1, 1, 1, 1, 1)
%%SET colTypes257("DBNUMBER", "STRING", "BITS", "BITS", "STRING", "NUMSTRING", "STRING", "SYMBOL", "PACKED NUMSTRING")
%%SET colSizes257(32, 15, 16, 16, 15, 7, 31, 1, 28)
%%SET bTrees257(2, 3, 4)
%%SET bTreeCols257_2(2)
%%SET bTreeCols257_3(5)
%%SET bTreeCols257_4(6)
%%SET symCols257(8)
%%SET symVals257_8(FALSE, TRUE)
%%SET symLits257_8(0, 1)


!******************************************************************************!
!END SQL!



!BEGIN SQL DECLARE_CURSOR 4!
!******************************************************************************!

!EXEC SQL DECLARE
cursor1
CURSOR
FOR
SELECT col1 FROM table1 WHERE col4 = "abc"!

!------------------------------------------------------------------------------!



!******************************************************************************!
!END SQL!
 

VARIABLE c1 16 DS;
VARIABLE c2 16 DS;
VARIABLE NO 1 DS;


!BEGIN SQL COMMON 0!

%%PROCESS ("CCL")

%%SET protInitSize(100)
%%SET tempSizes(7, 7)
%%SET tempUse1("STR")
%%SET tempUse2("STR")
%%BEGIN(userProtection)

%%END(userProtection)

%%BEGIN(towSymbols)

%%END(towSymbols)

%%SET curNames(CURSOR1)
%%SET curLocal(0)
%%SET curTabNos(257)
%%SET curTabNames(TABLE1)

%%SET curBlockRefs("")

%%INCLUDE (towDeclarations)

%%INCLUDE (tuDeclarations)

!END SQL!
END DECLARE;

DATA;

! Test a PLEX-SQL statement direct after a sector end !

!BEGIN SQL COMMON 0!
%%INCLUDE (towData("USER"))

%%INCLUDE (tuData("USER"))

!END SQL!
END DATA;
!BEGIN SQL SELECT 0!
!******************************************************************************!

!EXEC SQL SELECT col1 INTO `%a FROM table1 WHERE col4 = "abc"!

!------------------------------------------------------------------------------!

%%SET tabNo(257)
%%SET tabName(TABLE1)
%%SET keyNo(3)
%%SET keyExprs("SQLM_1")
%%SET keyPtrs("PROTECTEDP")
%%SET keyPrefix(1)
%%SET sigCount(0)
%%SET sigAssVars0("SQLM_1")
%%SET sigAssPtrs0("PROTECTEDP")
%%SET sigAssExprs0("""abc""")
%%SET sigCols0(2)
%%SET sigVars0("A")
%%SET sigPtrs0("")
%%SET sigNulls0("")
%%SET sigNullPtrs0("")
%%INCLUDE (remSelectStat)


!******************************************************************************!
!END SQL!
 

PROGRAM xreftest; PLEX;

! D A T A   M A N I P U L A T I O N   S T A T E M E N T S	!

! SINGLETON SELECT STATEMENT 					!


a = b;

! Test a PLEX-SQL statement direct after a plex signal statement !
ENTER STTOR WITH
   CRESTCASE,
   CPHASE,
   +,
   +,
   +,
   +,
   CSIGKEY;
!BEGIN SQL ENTER 0!
!******************************************************************************!


%%INCLUDE (comSttor("CRESTCASE", "CPHASE", "+", "+", "+", "+", "CSIGKEY"))


!******************************************************************************!
!END SQL!

!BEGIN SQL SELECT 1!
!******************************************************************************!

!EXEC SQL SELECT col1, col2 INTO `%c1, `%c2 FROM table1 
                    WHERE col1	 = "string"!

!------------------------------------------------------------------------------!

%%SET tabNo(257)
%%SET tabName(TABLE1)
%%SET keyNo(2)
%%SET keyExprs("SQLM_1")
%%SET keyPtrs("PROTECTEDP")
%%SET keyPrefix(1)
%%SET sigCount(0)
%%SET sigAssVars0("SQLM_1")
%%SET sigAssPtrs0("PROTECTEDP")
%%SET sigAssExprs0("""string""")
%%SET sigCols0(2, 3)
%%SET sigVars0("C1", "C2")
%%SET sigPtrs0("", "")
%%SET sigNulls0("", "")
%%SET sigNullPtrs0("", "")
%%INCLUDE (remSelectStat)


!******************************************************************************!
!END SQL!

! Ordinary SELECT with no errors !
c1 = c2;

! col1 not compatible with 36*7 !

!BEGIN SQL SELECT 9!
!******************************************************************************!

!EXEC
	 SQL

		SELECT col1, col2 INTO `%c1, 
 A couple of comments to confuse line counter 
 A couple of comments to confuse line counter 
 A couple of comments to confuse line counter 
`%c2 FROM table1 	
	WHERE col1 = 
		36*7!

!------------------------------------------------------------------------------!

%%SET tabNo(257)
%%SET tabName(TABLE1)
%%SET keyNo(2)
%%SET keyExprs("36 * 7")
%%SET keyPtrs("")
%%SET keyPrefix(1)
%%SET sigCount(0)
%%SET sigAssVars0()
%%SET sigAssPtrs0()
%%SET sigAssExprs0()
%%SET sigCols0(2, 3)
%%SET sigVars0("C1", "C2")
%%SET sigPtrs0("", "")
%%SET sigNulls0("", "")
%%SET sigNullPtrs0("", "")
%%INCLUDE (remSelectStat)


!******************************************************************************!
!END SQL!




!BEGIN SQL SELECT 3!
!******************************************************************************!

!EXEC SQL SELECT table2.col1, table1.col2 INTO `%c1, `%c2 

 FROM table1 AS table2
 WHERE table1.col1 = "string"!

!------------------------------------------------------------------------------!

%%SET tabNo(257)
%%SET tabName(TABLE1)
%%SET keyNo(2)
%%SET keyExprs("SQLM_1")
%%SET keyPtrs("PROTECTEDP")
%%SET keyPrefix(1)
%%SET sigCount(0)
%%SET sigAssVars0("SQLM_1")
%%SET sigAssPtrs0("PROTECTEDP")
%%SET sigAssExprs0("""string""")
%%SET sigCols0(2, 3)
%%SET sigVars0("C1", "C2")
%%SET sigPtrs0("", "")
%%SET sigNulls0("", "")
%%SET sigNullPtrs0("", "")
%%INCLUDE (remSelectStat)


!******************************************************************************!
!END SQL!


! UPDATE SINGLE ROW !
! col5 not compatible with "DIGITS" !

!BEGIN SQL UPDATE 7!
!******************************************************************************!

!EXEC SQL


UPDATE table1 SET

       

       col5 = "DIGITS" WHERE col1 = "string"!

!------------------------------------------------------------------------------!

%%SET tabNo(257)
%%SET tabName(TABLE1)
%%SET keyNo(2)
%%SET keyExprs("SQLM_1")
%%SET keyPtrs("PROTECTEDP")
%%SET keyPrefix(1)
%%SET sigCount(0)
%%SET sigAssVars0("SQLM_2", "SQLM_1")
%%SET sigAssPtrs0("PROTECTEDP", "PROTECTEDP")
%%SET sigAssExprs0("""DIGITS""", """string""")
%%SET sigCols0(6)
%%SET sigColOps0("=")
%%SET sigExprs0("SQLM_2")
%%SET sigPtrs0("PROTECTEDP")
%%SET sigNulls0("")
%%SET sigNullPtrs0("")
%%INCLUDE (updateStat)


!******************************************************************************!
!END SQL!



!BEGIN SQL UPDATE_VOLATILE 3!
!******************************************************************************!

!EXEC SQL


UPDATE table2 VOLATILE col5 = "DIGITS" WHERE col9 = 10!

!------------------------------------------------------------------------------!

%%SET tabNo(256)
%%SET tabName(TABLE2)
%%SET keyExprs("10")
%%SET sigCount(0)
%%SET sigAssVars0("SQLM_1")
%%SET sigAssPtrs0("PROTECTEDP")
%%SET sigAssExprs0("""DIGITS""")
%%SET sigCols0(6)
%%SET sigColOps0("=")
%%SET sigExprs0("SQLM_1")
%%SET sigPtrs0("PROTECTEDP")
%%SET sigNulls0("")
%%SET sigNullPtrs0("")
%%INCLUDE (remUpdateVolatileStat)


!******************************************************************************!
!END SQL!



;

a = b;

c


=


d;

! not compatible search conditions !

!BEGIN SQL UPDATE 7!
!******************************************************************************!

!EXEC SQL


UPDATE table1 SET

       col3 = 4,

       col5 = `%c WHERE col1 = 35432!

!------------------------------------------------------------------------------!

%%SET tabNo(257)
%%SET tabName(TABLE1)
%%SET keyNo(2)
%%SET keyExprs("35432")
%%SET keyPtrs("")
%%SET keyPrefix(1)
%%SET sigCount(0)
%%SET sigAssVars0()
%%SET sigAssPtrs0()
%%SET sigAssExprs0()
%%SET sigCols0(6, 4)
%%SET sigColOps0("=", "=")
%%SET sigExprs0("C", "4")
%%SET sigPtrs0("", "")
%%SET sigNulls0("", "")
%%SET sigNullPtrs0("", "")
%%INCLUDE (updateStat)


!******************************************************************************!
!END SQL!


! INSERT INTO table !


!BEGIN SQL INSERT 4!
!******************************************************************************!

!EXEC SQL INSERT into table1
(
col1, col2,

col5, col7) VALUES (1,2,3,4)!

!------------------------------------------------------------------------------!

%%SET tabNo(257)
%%SET tabName(TABLE1)
%%SET keyNo(2)
%%SET keyExprs("1")
%%SET keyPtrs("")
%%SET keyPrefix(1)
%%SET sigCount(1)
%%SET sigAssVars0()
%%SET sigAssVars1()
%%SET sigAssPtrs0()
%%SET sigAssPtrs1()
%%SET sigAssExprs0()
%%SET sigAssExprs1()
%%SET sigCols0(6, 3)
%%SET sigCols1(8)
%%SET sigExprs0("3", "2")
%%SET sigExprs1("4")
%%SET sigPtrs0("", "")
%%SET sigPtrs1("")
%%SET sigNulls0("", "")
%%SET sigNulls1("")
%%SET sigNullPtrs0("", "")
%%SET sigNullPtrs1("")
%%INCLUDE (insertStat)


!******************************************************************************!
!END SQL!


! DELETE FROM table !

!BEGIN SQL BEGIN 7!
!******************************************************************************!

!EXEC SQL BEGIN



PROTECTED


REGION!

!------------------------------------------------------------------------------!

%%INCLUDE (beginStat)


!******************************************************************************!
!END SQL!


!BEGIN SQL DELETE 5!
!******************************************************************************!

!EXEC SQL DELETE FROM  table3



WHERE
			col1 = `%c!

!------------------------------------------------------------------------------!

%%SET tabNo(0)
%%SET tabName(TABLE3)
%%SET keyNo(2)
%%SET keyExprs("C")
%%SET keyPtrs("")
%%SET keyPrefix(1)
%%SET sigAssVars0()
%%SET sigAssPtrs0()
%%SET sigAssExprs0()
%%INCLUDE (deleteStat)


!******************************************************************************!
!END SQL!



! CURSOR HANDLING !

!BEGIN SQL OPEN_CURSOR 0!
!******************************************************************************!

!EXEC SQL OPEN  cursor1!

!------------------------------------------------------------------------------!

%%SET tabNo(257)
%%SET tabName(TABLE1)
%%SET keyNo(3)
%%SET keyExprs("SQLM_1")
%%SET keyPtrs("PROTECTEDP")
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(1)
%%SET sigAssVars0("SQLM_1")
%%SET sigAssPtrs0("PROTECTEDP")
%%SET sigAssExprs0("""abc""")
%%INCLUDE (remOpenStat)


!******************************************************************************!
!END SQL!
 
!BEGIN SQL CLOSE_CURSOR 0!
!******************************************************************************!

!EXEC SQL CLOSE cursor1!

!------------------------------------------------------------------------------!

%%SET tabNo(257)
%%SET tabName(TABLE1)
%%SET curNo(1)
%%INCLUDE (remCloseStat)


!******************************************************************************!
!END SQL!



!BEGIN SQL FETCH 4!
!******************************************************************************!

!EXEC SQL FETCH
cursor1


INTO  COMMENT  `%a!

!------------------------------------------------------------------------------!

%%SET tabNo(257)
%%SET tabName(TABLE1)
%%SET keyNo(3)
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(1)
%%SET sigCount(0)
%%SET sigCols0(2)
%%SET sigVars0("A")
%%SET sigPtrs0("")
%%SET sigNulls0("")
%%SET sigNullPtrs0("")
%%SET sigPreds0()
%%INCLUDE (remFetchStat)


!******************************************************************************!
!END SQL!



!BEGIN SQL FETCH 0!
!******************************************************************************!

!EXEC SQL FETCH cursor1 INTO `%a!

!------------------------------------------------------------------------------!

%%SET tabNo(257)
%%SET tabName(TABLE1)
%%SET keyNo(3)
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(1)
%%SET sigCount(0)
%%SET sigCols0(2)
%%SET sigVars0("A")
%%SET sigPtrs0("")
%%SET sigNulls0("")
%%SET sigNullPtrs0("")
%%SET sigPreds0()
%%INCLUDE (remFetchStat)


!******************************************************************************!
!END SQL!
 
!BEGIN SQL FETCH 4!
!******************************************************************************!

!EXEC SQL FETCH cursor1 INTO 



`%a!

!------------------------------------------------------------------------------!

%%SET tabNo(257)
%%SET tabName(TABLE1)
%%SET keyNo(3)
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(1)
%%SET sigCount(0)
%%SET sigCols0(2)
%%SET sigVars0("A")
%%SET sigPtrs0("")
%%SET sigNulls0("")
%%SET sigNullPtrs0("")
%%SET sigPreds0()
%%INCLUDE (remFetchStat)


!******************************************************************************!
!END SQL!

!BEGIN SQL START 2!
!******************************************************************************!

!EXEC SQL START TRANSACTION

`%NISSE!

!------------------------------------------------------------------------------!

%%SET transId("NISSE")
%%INCLUDE (startStat)


!******************************************************************************!
!END SQL!


!BEGIN SQL PREPARE 0!
!******************************************************************************!

!EXEC SQL PREPARE TRANSACTION!

!------------------------------------------------------------------------------!

%%INCLUDE (prepareStat)


!******************************************************************************!
!END SQL!
 
!BEGIN SQL START 0!
!******************************************************************************!

!EXEC SQL START WORK!

!------------------------------------------------------------------------------!

%%SET transId("""""")
%%INCLUDE (startStat)


!******************************************************************************!
!END SQL!
 
!BEGIN SQL PREPARE 1!
!******************************************************************************!

!EXEC SQL PREPARE WORK
!

!------------------------------------------------------------------------------!

%%INCLUDE (prepareStat)


!******************************************************************************!
!END SQL!


!BEGIN SQL ROLLBACK 6!
!******************************************************************************!

!EXEC SQL ROLLBACK 





TRANSACTION!

!------------------------------------------------------------------------------!

%%INCLUDE (rollbackStat)


!******************************************************************************!
!END SQL!


!BEGIN SQL ROLLBACK 4!
!******************************************************************************!

!EXEC SQL ROLLBACK WORK



!

!------------------------------------------------------------------------------!

%%INCLUDE (rollbackStat)


!******************************************************************************!
!END SQL!


!BEGIN SQL COMMIT 2!
!******************************************************************************!

!EXEC SQL COMMIT

TRANSACTION!

!------------------------------------------------------------------------------!

%%INCLUDE (commitStat)


!******************************************************************************!
!END SQL!

!BEGIN SQL ROLLBACK 1!
!******************************************************************************!

!EXEC SQL ROLLBACK
TRANSACTION!

!------------------------------------------------------------------------------!

%%INCLUDE (rollbackStat)


!******************************************************************************!
!END SQL!


!BEGIN SQL UPDATE 2!
!******************************************************************************!

!EXEC SQL UPDATE table3 set col7 = `%a 
WHERE
CURRENT OF cursor1!

!------------------------------------------------------------------------------!

%%SET tabNo(0)
%%SET tabName(TABLE3)
%%SET keyNo(3)
%%SET keyExprs("SQLM_1")
%%SET keyPtrs("PROTECTEDP")
%%SET keyPrefix(1)
%%SET sigCount(0)
%%SET sigAssVars0()
%%SET sigAssPtrs0()
%%SET sigAssExprs0()
%%SET sigCols0(8)
%%SET sigColOps0("=")
%%SET sigExprs0("A")
%%SET sigPtrs0("")
%%SET sigNulls0("")
%%SET sigNullPtrs0("")
%%SET curNo(1)
%%INCLUDE (updateStat)


!******************************************************************************!
!END SQL!


!BEGIN SQL END 0!
!******************************************************************************!

!EXEC SQL END PROTECTED REGION!

!------------------------------------------------------------------------------!

%%INCLUDE (endStat)


!******************************************************************************!
!END SQL!


!BEGIN SQL GET_DB_NUMBER 9!
!******************************************************************************!

!EXEC
SQL GET
DBNUMBER 






INTO `%NO!

!------------------------------------------------------------------------------!

%%SET vars("NO")
%%SET ptrs("")
%%INCLUDE (getDbnumberStat)


!******************************************************************************!
!END SQL!


!BEGIN SQL FETCH 0!
!******************************************************************************!

!EXEC SQL FETCH cursor1 into `%a!

!------------------------------------------------------------------------------!

%%SET tabNo(257)
%%SET tabName(TABLE1)
%%SET keyNo(3)
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(1)
%%SET sigCount(0)
%%SET sigCols0(2)
%%SET sigVars0("A")
%%SET sigPtrs0("")
%%SET sigNulls0("")
%%SET sigNullPtrs0("")
%%SET sigPreds0()
%%INCLUDE (remFetchStat)


!******************************************************************************!
!END SQL!

!BEGIN SQL DELETE 0!
!******************************************************************************!

!EXEC SQL DELETE FROM  table3 WHERE current of cursor1!

!------------------------------------------------------------------------------!

%%SET tabNo(0)
%%SET tabName(TABLE3)
%%SET keyNo(3)
%%SET keyExprs("SQLM_1")
%%SET keyPtrs("PROTECTEDP")
%%SET keyPrefix(1)
%%SET sigAssVars0()
%%SET sigAssPtrs0()
%%SET sigAssExprs0()
%%SET curNo(1)
%%INCLUDE (deleteStat)


!******************************************************************************!
!END SQL!

!BEGIN SQL CLOSE_CURSOR 0!
!******************************************************************************!

!EXEC SQL CLOSE cursor1!

!------------------------------------------------------------------------------!

%%SET tabNo(257)
%%SET tabName(TABLE1)
%%SET curNo(1)
%%INCLUDE (remCloseStat)


!******************************************************************************!
!END SQL!



%c;

!BEGIN SQL CONTINUE 3!
!******************************************************************************!

!EXEC SQL CONTINUE AT

LEVEL B		
			DELAY 12 MS!

!------------------------------------------------------------------------------!

%%SET level("B")
%%SET exprs("12")
%%SET timeUnit("MS")
%%INCLUDE (continueStat)


!******************************************************************************!
!END SQL!

PREP1)
   
!BEGIN SQL SELECT 0!
!******************************************************************************!

!EXEC SQL SELECT col1,col3 into `%a,`%c FROM table3 WHERE CURRENT OF WORK!

!------------------------------------------------------------------------------!

%%SET tabNo(0)
%%SET tabName(TABLE3)
%%SET keyNo(1)
%%SET keyExprs("WORK")
%%SET keyPtrs("")
%%SET keyPrefix(0)
%%SET cols(2, 4)
%%SET vars("A", "C")
%%SET ptrs("", "")
%%SET nulls("", "")
%%SET nullPtrs("", "")
%%INCLUDE (locSelectStat)


!******************************************************************************!
!END SQL!

   
!BEGIN SQL SELECT 0!
!******************************************************************************!

!EXEC SQL SELECT col1,col3 into `%a,`%c FROM table3 WHERE CURRENT OF ORIGINAL!

!------------------------------------------------------------------------------!

%%SET tabNo(0)
%%SET tabName(TABLE3)
%%SET keyNo(1)
%%SET keyExprs("ORIGINAL")
%%SET keyPtrs("")
%%SET keyPrefix(0)
%%SET cols(2, 4)
%%SET vars("A", "C")
%%SET ptrs("", "")
%%SET nulls("", "")
%%SET nullPtrs("", "")
%%INCLUDE (locSelectStat)


!******************************************************************************!
!END SQL!

   GOTO PREPRET;

POST1)
   
!BEGIN SQL SELECT 0!
!******************************************************************************!

!EXEC SQL SELECT col1,col3 into `%a,`%c FROM table3 WHERE CURRENT OF WORK!

!------------------------------------------------------------------------------!

%%SET tabNo(0)
%%SET tabName(TABLE3)
%%SET keyNo(1)
%%SET keyExprs("WORK")
%%SET keyPtrs("")
%%SET keyPrefix(0)
%%SET cols(2, 4)
%%SET vars("A", "C")
%%SET ptrs("", "")
%%SET nulls("", "")
%%SET nullPtrs("", "")
%%INCLUDE (locSelectStat)


!******************************************************************************!
!END SQL!

   
!BEGIN SQL SELECT 0!
!******************************************************************************!

!EXEC SQL SELECT col1,col3 into `%a,`%c FROM table3 WHERE CURRENT OF ORIGINAL!

!------------------------------------------------------------------------------!

%%SET tabNo(0)
%%SET tabName(TABLE3)
%%SET keyNo(1)
%%SET keyExprs("ORIGINAL")
%%SET keyPtrs("")
%%SET keyPrefix(0)
%%SET cols(2, 4)
%%SET vars("A", "C")
%%SET ptrs("", "")
%%SET nulls("", "")
%%SET nullPtrs("", "")
%%INCLUDE (locSelectStat)


!******************************************************************************!
!END SQL!

   GOTO POSTRET;

ROLL1)
   
!BEGIN SQL SELECT 0!
!******************************************************************************!

!EXEC SQL SELECT col1,col3 into `%a,`%c FROM table3 WHERE CURRENT OF WORK!

!------------------------------------------------------------------------------!

%%SET tabNo(0)
%%SET tabName(TABLE3)
%%SET keyNo(1)
%%SET keyExprs("WORK")
%%SET keyPtrs("")
%%SET keyPrefix(0)
%%SET cols(2, 4)
%%SET vars("A", "C")
%%SET ptrs("", "")
%%SET nulls("", "")
%%SET nullPtrs("", "")
%%INCLUDE (locSelectStat)


!******************************************************************************!
!END SQL!

   
!BEGIN SQL SELECT 0!
!******************************************************************************!

!EXEC SQL SELECT col1,col3 into `%a,`%c FROM table3 WHERE CURRENT OF ORIGINAL!

!------------------------------------------------------------------------------!

%%SET tabNo(0)
%%SET tabName(TABLE3)
%%SET keyNo(1)
%%SET keyExprs("ORIGINAL")
%%SET keyPtrs("")
%%SET keyPrefix(0)
%%SET cols(2, 4)
%%SET vars("A", "C")
%%SET ptrs("", "")
%%SET nulls("", "")
%%SET nullPtrs("", "")
%%INCLUDE (locSelectStat)


!******************************************************************************!
!END SQL!

   GOTO ROLLRET;



!BEGIN SQL COMMON 0!
%%INCLUDE (comGiveFs())

%%INCLUDE (comContFs())

%%INCLUDE (comSetFs())

%%INCLUDE (towPlexCode)

%%INCLUDE (tuPlexCode)
!END SQL!
END PROGRAM;
!BEGIN SQL COMMON 0!
%%INCLUDE (towAsaCode)

%%INCLUDE (tuAsaCode)
!END SQL!


END DOCUMENT;
