DOCUMENT DBDDH;

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


!*****************************************************************************!
!*                                                                           *! 
!*             G L O B A L   S Y M B O L S                                   *!
!*                                                                           *!
!*****************************************************************************!


 ! GLOBAL NSYMB ZTOWFUCODE = 162  !
 
 
 
 
 
 
 
 
 
!*****************************************************************************!
!*                                                                           *! 
!*             L O C A L   S Y M B O L S                                     *!
!*                                                                           *!
!*****************************************************************************! 
 



! TEMPORARILY DECLARED PLEX SQL SYMBOL VALUES !


NSYMB ZTOWFUCODE = 162;



!  NSYMB TABLESSTATEBLOCKED=0
NSYMB TABLESSTATEWORKING=1  
NSYMB TABLESLOCATESINGLE=0
NSYMB TABLESLOCATEMULTI=1

NSYMB FIELDSVISIBILINVIS=0
NSYMB FIELDSVISIBILREADO=1
NSYMB FIELDSVISIBILREADWR=2

NSYMB FIELDSNULLPERFALSE=1
NSYMB FIELDSNULLPERTRUE=0

NSYMB FIELDSDATATYPBITS = 0
NSYMB FIELDSDATATYPSTRING = 1
NSYMB FIELDSDATATYPNUMSTR = 2
NSYMB FIELDSDATATYPPNUMSTR = 3
NSYMB FIELDSDATATYPSYMBOL = 4
NSYMB FIELDSDATATYPROWNUM = 5
NSYMB FIELDSDATATYPDBNUM = 6

NSYMB FIELDSCLEARYES = 0
NSYMB FIELDSCLEARNO = 1
NSYMB FIELDSRELOADYES = 0
NSYMB FIELDSRELOADNO = 1
NSYMB FIELDSDUMPYES = 0
NSYMB FIELDSDUMPNO = 1
NSYMB FIELDSSTATICYES = 0
NSYMB FIELDSSTATICNO = 1
NSYMB FIELDSVOLATILYES = 0
NSYMB FIELDSVOLATILNO = 1

NSYMB KEYSKEYTYPEPRIMKEY = 0
NSYMB KEYSKEYTYPEALTERN = 1
NSYMB KEYSKEYTYPEINDKEY = 2

NSYMB FOREIGNKEYSCONDRESTR = 0
NSYMB FOREIGNKEYSCONDCASCAD = 1
NSYMB FOREIGNKEYSCONDSETNULL = 2
NSYMB FOREIGNKEYSCONDSETDEF = 3     !



             
 
STRING ZFIELDS= "FIELDS";          ! USED IN PROGERROR !
STRING ZFOREIGNKEYS= "FOREIGNKEYS";! USED IN PROGERROR !
STRING ZTABLES= "TABLES";         ! USED IN PROGERROR !


                                        
                                        
NSYMB ZBITS=0;                              ! SYMBOL VALUE ACC. TO DDINITFLD   !
NSYMB ZBLOCKCAT = 2;                        ! BLOCK CATEGORY. USED IN STTOR    !
NSYMB ZCONGESTION=4;                        ! CONGESTION IN KEED.              !
NSYMB ZDBNUMBER=6;                          ! SYMBOL VALUE ACC. TO DDINITFLD   !
NSYMB ZDBSINTERNALPHASE1 = 1;
NSYMB ZDBSINTERNALPHASE2 = 2;
NSYMB ZDBSINTERNALPHASE3 = 3;
NSYMB ZDBSINTERNALPHASE4 = 4;
NSYMB ZDDFCSTA=0;                           ! CURRENT SIGNAL = DDFCSTA         !
NSYMB ZDDRESPART=1;                         ! CURRENT SIGNAL = DDRESPART       !
NSYMB ZDONOTLOG=1;                          ! DO NOT LOG THE TRANSACTION       !
NSYMB ZDONOTPARTICIPATE=1;                  ! BLOCK IS NOT INVOLVED IN RESTART !
NSYMB ZERROR=3;                             ! SQLCODE.VALUE FAULT RESOLUTION   !
NSYMB ZFIRSTFK=0;                           ! FIRST FOREIGN KEY OF TRANSACTION !
NSYMB ZFIRSTORDNO = 0;                      ! ORDINAL NUMBER OF FIRST FK TO TAB!
NSYMB ZFKFOUND = 0;                         ! A FOREIGN KEY IS FOUND           !
NSYMB ZFKNOTFOUND = 1;                      ! A FOREIGN KEY IS NOT FOUND       !
NSYMB ZFUNCTIONCHANGE=2;                    ! EVENT = FUNCTION CHANGE          !
NSYMB ZINFOONLEVELC=#1000;                  ! INFORMATION ON LEVEL C           !
NSYMB ZLARGERELOAD=2;                       ! LARGE RESTART WITH RELOAD        !
NSYMB ZLARGERESTART=1;                      ! LARGE RESTART WITHOUT RELOAD     !
NSYMB ZMAXNOFBLOCKS=65535;                  ! DETERMINES THE MAXIMUM NUMBER OF !
                                            ! BLOCKS THAT MAY BE AFFECTED BY A !
                                            ! FUNCTION CHANGE FOLLOWED BY A    !
                                      ! SPECIFY. SMALL RESTART.                !
NSYMB ZMAXNOFROWS = 65531;
NSYMB ZMAXORDNO = 255;                      ! MAXIMUM FOREIGN KEY ORDINAL NUMB.!
NSYMB ZMAXSYMVAL = 65535;
NSYMB ZNAMEALREADYEXISTS=0;                 ! TABLENAME ALREADY DEFINED        !
NSYMB ZNOMOREPHASES=255;                    ! LAST RESTART PHASE INDICATOR     !
NSYMB ZNOMORETABLES = 2;
NSYMB ZNOTABFOUNDFLAG=1;                    ! WHEN ANSWERING DDTABREF !
NSYMB ZNUMSTR=2;                         ! SYMBOL VALUE ACC. TO DDINITFLD   !
NSYMB ZOK=0;                   
NSYMB ZONEEVENT=1;                          ! INFO. ON ONE EVENT REQUESTED     !
NSYMB ZPACKEDNUMSTR=3;                      ! SYMBOL VALUE ACC. TO DDINITFLD   !
NSYMB ZPARTICIPATE=0;                       ! BLOCK IS INVOLVED IN THE RESTART !
NSYMB ZPROGERRORCODE1=0;             ! SPECIFY. FAULT CODE. DBDDH TABLE FULL     !
NSYMB ZPROGERRORCODE2=0;             ! SPECIFY. FAULT CODE. DUPLICATE TABLENAMES !
NSYMB ZPROGERRORCODE3=0;           ! SPECIFY. FAULT CODE.REFERRED TAB UNDEFINED!
NSYMB ZPROGERRORCODE4=0;           ! SPECIFY. FAULT CODE. CONGESTION IN TRH    !
NSYMB ZREQUESTACKN=0;
NSYMB ZROWINSERTED=0;                       ! A ROW IS SUCCESSFULLY INSERTED   !
NSYMB ZROWNOTALLOCATED = 6;                 ! INSERT FAILED. ROW NOT ALLOCATED !
NSYMB ZROWNUMBER=5;                         ! SYMBOL VALUE ACC. TO DDINITFLD   !
NSYMB ZSEARCHFAIL=2;                        ! SQLCODE.VALUE FAULT RESOLUTION   !
NSYMB ZSMALLRESTART=0;                      ! SMALL RESTART                    !
NSYMB ZSPH1DBDDH=2;                         ! FIRST RESTARTPHASE IN THIS BLOCK !
NSYMB ZSPH2DBDDH=3;                    ! SPECIFY. SECOND RESTART PHASE         !
NSYMB ZSPH3DBDDH=4;                    ! SPECIFY. THIRD  RESTART PHASE         !
NSYMB ZSPH4DBDDH=5;                    ! SPECIFY. FOURTH RESTART PHASE         !
NSYMB ZSPH5DBDDH=6;                    ! SPECIFY. FIFTH  RESTART PHASE         !
NSYMB ZSPH6DBDDH=7;                    ! SPECIFY. SIXTH  RESTART PHASE         !
NSYMB ZSTR=1;                            ! SYMBOL VALUE ACC. TO DDINITFLD   !
NSYMB ZSTTORRYVERSION=2;                    ! VERSION OF SIGNAL STTORRY        !
NSYMB ZSYMBOL=4;                            ! SYMBOL VALUE ACC. TO DDINITFLD   !
NSYMB ZSYMBOLFOUND=0;                       ! A SYMBOL VALUE IS RETURNED       !
NSYMB ZSYSTEMRESTART=36;                    ! EVENT = SYSTEM RESTART           !
NSYMB ZSYSTEMSTART=3;                       ! SYSTEM RESTART                   !
NSYMB ZSYSRESTFLAGCHANGED=#1024;            ! SYSTEM RESTART FLAG CHANGED      !
NSYMB ZTABCONGESTION = 8;                   ! NO WORK ROW FREE IN TABLE        !
NSYMB ZTABFULL=9;                           ! A TABLE IS FULL                  !
NSYMB ZTABLEFOUND = 0;
NSYMB ZTRHCONG=10;                          ! CONGESTION IN TRANSACTION HANDLER!
NSYMB ZTRHSAEID1= 0;              ! SPECIFY. CONGESTION IN TRH CAUSES PROGERROR!
NSYMB ZTRHSAEID2= 0;              ! SPECIFY. CONGESTION IN TRH CAUSES PROGERROR!

 
 
 
 
 
 
 
 
 




!*****************************************************************************!
!*                                                                           *! 
!*             R E C O R D S   A N D   F I L E S I Z E S                     *!
!*                                                                           *!
!*****************************************************************************! 
 

!BEGIN SQL INCLUDE 41!
!******************************************************************************!

!EXEC SQL INCLUDE PROTECTION WITH "
   VARIABLE BLKNUM 16 DS
   VARIABLE BLKREF 16 DS
   VARIABLE CONDITION 16 DS
   VARIABLE COUNTER 16 DS
   VARIABLE DELETEACTION 16 DS             FOREIGN KEY DELETE ACTION        
   VARIABLE FBLKREF 16 DS                  BLOCK REFERENCE OF REFERRING TAB 
   VARIABLE FKNUMBER 16 DS                 FOREIGN KEY NUMBER               
   VARIABLE FLDDATATYPE 16 DS              DATA TYPE OF COLUMN VARIABLE     
   VARIABLE FLDNUMBER 16 DS                FIELD NUMBER                     
   VARIABLE FLDPROTECTION 16 DS            FIELD PROTECTION/VISIBILITY      
   VARIABLE FLDSIZE 16 DS                  FIELD SIZE                       
   VARIABLE FROWNO 16 DS                   ROWNUMBER IN FIELDS TABLE        
   VARIABLE FTABREF 16 DS                  TABLE REFERENCE OF REFERRING TAB 
   VARIABLE KEYNO 16 DS                    ORDINAL KEY NUMBER               
   VARIABLE LOCATION 16 DS                 TABLE LOCATION (SINGLE/MULTIPLE) 
   VARIABLE MAXSYMLENGTH 16 DS             LONGEST SYMBOL VALUE NAME        
   VARIABLE NAMELENGTH 8 DS                LENGTH OF SYMBOL VALUE NAME      
   VARIABLE NEXTTOBEDELETED 16 DS          ROWNUMBER OF ROW TO BE DELETED   
   VARIABLE ORDNO 16 DS                    ORDINAL NUMBER                   
   VARIABLE PRWIDTH 16 DS                  PRINTOUT WIDTH OF COLUMN         
   VARIABLE RAUTHCAT 16 DS                 TABLE READ AUTHORITY CATEGORY    
   VARIABLE REF 16 DS                      RETURN SIGNAL REFERENCE          
   VARIABLE REFERREDTROWNO 16 DS           TABLE ROW NUMBER OF REFERRED TAB 
   VARIABLE SAMENAME 16 DS                 ROWNUMBER OF TABLE WITH SAME NAME
   VARIABLE SYMBOLVALUE 16 DS              NUMERICAL SYMBOL VALUE           
   VARIABLE TABREF 16 DS
   VARIABLE TOWBLKREF 16 DS                TABLE OWNER BLOCK REFERENCE      
   VARIABLE TOWTABREF 16 DS                TABLE OWNER TABLE REFERENCE      
   VARIABLE TRANSID 16 DS                  TRANSACTION IDENTITY             
   VARIABLE TROWNO 16 DS                   ROWNUMBER IN TABLES TABLE        
   VARIABLE USERP 16 DS                    USER'S POINTER                   
   VARIABLE VOLATIL 16 DS                  VARIABLE PROPERTY VOLATILE       
   VARIABLE WAUTHCAT 16 DS                 TABLE WRITE AUTHORITY CATEGORY   

   STRING VARIABLE FLDNAME 7 DS            COLUMN NAME                      
   STRING VARIABLE REFERREDTABNAME 15 DS   NAME OF REFERRED TABLE           
   STRING VARIABLE TABNAME 15 DS           TABLE NAME                       
                              
   SYMBOL VARIABLE SYMBOLFOUND=(FALSE, TRUE) DS
                                             NEW SYMBOL VALUE NAME FOUND?     
   "!

!------------------------------------------------------------------------------!



!******************************************************************************!
!END SQL!






!BEGIN SQL INCLUDE 0!
!******************************************************************************!

!EXEC SQL INCLUDE TEST!

!------------------------------------------------------------------------------!



!******************************************************************************!
!END SQL!












!*****************************************************************************!
!*                                                                           *! 
!*             C O M M O N   S T O R E D   V A R I A B L E S                 *!
!*                                                                           *!
!*****************************************************************************! 
 

VARIABLE CBLOCK ( 32768 ) 16 DS;    ! BLOCK NUMBERS/REFERENCES OF      !
                                            ! BLOCKS INVOLVED IN SMALL RESTART !
                                            ! SIZE = ZMAXNOFBLOCKS             !
VARIABLE CBLOCKCOUNT 16 DS;                 ! INDEX TO CBLOCK                  !
VARIABLE CK 16 DS;                          ! INDEX USED IN DIFFERENT LOOPS    !
VARIABLE CLOCALRESTARTPHASE 16 DS;
VARIABLE CMESSAGE 16 DS;                    ! MESSAGE CODE. SEE STRUCTURE      !
VARIABLE CNEXTFROWNO 16 DS;                 ! REMEMBERS NEXT AVAILABLE FROWNO  !
VARIABLE CNEXTTROWNO 16 DS;                 ! REMEMBERS NEXT AVAILABLE TROWNO  !
VARIABLE CNOFBLOCKS 16 DS;                  ! NUMBER OF BLOCKS INVOLVED IN FC  !
VARIABLE CNOFREQ 16 DS;                     ! NUMBER OF REQUESTS WITH FCHBNOOLD!
VARIABLE COWNREF 16 DS;                     ! OWN BLOCK REFERENCE              !
VARIABLE CPARTICIPATE 16 DS;                ! PARTICIPATE IN FUNCTION CHANGE?  !
VARIABLE CPHASE 8 DS;                       ! CURRENT RESTART PHASE            !
VARIABLE CREFERRINGFKORDNO 16 DS;           ! ORDINAL NUMBER OF REFERRING FK   !
VARIABLE CRESTCASE 4 DS;                    ! RESTART CASE                     !
VARIABLE CSIGKEY 16 DS;                     ! SIGNAL KEY                       !
VARIABLE CTEMPBLOCK (16) 16 DS;
VARIABLE CUSERBLKREF 16 DS;                 ! BLOCK REFERENCE OF DBDDH USER    !
VARIABLE CUSERP ( 2 ) 16 DS;                ! USERS POINTER                    !

!VARIABLE SQLCODE 16 DS !           ! ONLY FOR TEMP USE ! 

STRING VARIABLE CFLDNAME 7 DS;              ! NAME OF COLUMN/FIELD             !
STRING VARIABLE CREFERREDTABNAME 15 DS;     ! NAME OF REFERRED TABLE           !
STRING VARIABLE CSYMBOLNAME 7 DS;           ! SYMBOL VALUE NAME                !
STRING VARIABLE CTABNAME 15 DS;             ! TABLE NAME                       !

SYMBOL VARIABLE CALLTABSCLEARED = (FALSE, TRUE) DS;

SYMBOL VARIABLE CALLTABSRECEIVED = (FALSE, TRUE) DS;
                                           
SYMBOL VARIABLE CFC = (FALSE, TRUE) DS;
                                            ! REPORTS RECENT FUNCTION CHANGE   !

SYMBOL VARIABLE CMORETABSTODELETE = (FALSE, TRUE) DS;
SYMBOL VARIABLE CONLYSOMEBLOCKS = (FALSE, TRUE) DS;


SYMBOL VARIABLE CRETURNFROMCHECKSYMVALNAMELENGTH = (SYMDDINITFIELD10);
SYMBOL VARIABLE CRETURNFROMCLEARALLTABS = ( SYMWHICHRESTCASE10 );
SYMBOL VARIABLE CRETURNFROMCLEARSOMETABS = ( SYMWHICHRESTCASE10 );
SYMBOL VARIABLE CRETURNFROMTRIGTOWINITIATION = (SYMSTTOR10) DS;
SYMBOL VARIABLE CRETURNFROMTRHSTATRANSR = (SYMCLEARALLTABS30,
                                           SYMCLEARSOMETABS80,
                                           SYMDDINITTABLE20,
                                           SYMDDINITFIELD20,
                                           SYMDDINITFK10);
             
SYMBOL VARIABLE CRETURNFROMWHICHRESTCASE = (SYMSTTOR10) DS;
                                            ! RETURN ADDRESS FROM WHICHRESTCASE!
                               
SYMBOL VARIABLE CSIGNAL = (DDFCSTA, BLKREMST) DS;
                                            ! WHICH SIGNAL WILL BE ANSWERED    !
                               
SYMBOL VARIABLE CSMALLREST = (FALSE, TRUE) DS;
                                            ! IS THE CURRENT RESTART SMALL?    !






















!*****************************************************************************!
!*                                                                           *! 
!*             T E M P O R A R Y   V A R I A B L E S                         *!
!*                                                                           *!
!*****************************************************************************! 
 

VARIABLE TANSWER 16; 
VARIABLE TBLKNUM 16;                        ! BLOCK NUMBER                     !
VARIABLE TBLKREF 16;                        ! BLOCK REFERENCE                  !
VARIABLE TCOUNTER 16;
VARIABLE TDELETEACTION 16;                  ! FOREIGN KEY DELETE ACTION        !
VARIABLE TFCIND 16;                         ! FUNCTION CHANGE INDICATOR        !
VARIABLE TFKNUMBER 16;                      ! FOREIGN KEY NUMBER               !
VARIABLE TFLDDATATYPE 16;                   ! DATA TYPE OF CURRENT FIELD       !
VARIABLE TFLDNUMBER 16;                     ! FIELD NUMBER                     !
VARIABLE TFLDPROTECTION 16;                 ! FIELD PROTECTION/VISIBILITY      !
VARIABLE TFLDSIZE 16;                       ! FIELD SIZE                       !
VARIABLE TLOCATION 16;                      ! TABLE LOCATION (SINGLE/MULTIPLE) !
VARIABLE TNAMELENGTH 16;
VARIABLE TNOFRECEIVEDDATA 16;
VARIABLE TOWNREF 16;                        ! OWN BLOCK REFERENCE              !
VARIABLE TREADAUTHCAT 16 ;                  ! READ AUTHORITY CATEGORY OF TABLE !
VARIABLE TRETURNCODE 16;                    ! RETURN CODE                      !
VARIABLE TSAEID 16;                         ! SIZE ALTERNATION EVENT IDENTITY  !
VARIABLE TSTATEID 16;                       ! STATE IDENTITY                   !
VARIABLE TSYMLENGTH 8;                      ! SYMBOL VALUE NAME LENGTH         !
VARIABLE TTABREF 16;                        ! TABLE REFERENCE OF FULL TABLE    !
VARIABLE TTOWBLKREF 16;                     ! TABLE OWNER BLOCK REFERENCE      !
VARIABLE TTOWTABREF 16;                     ! TABLE OWNER TABLE REFERENCE      !
VARIABLE TTRID 16;                          ! TRANSACTION IDENTITY             !
VARIABLE TUSERP 16;                         ! USER'S POINTER                   !
VARIABLE TVOLATILE 16;                      ! VARIABLE PROPERTY VOLATILE       !
VARIABLE TWRITEAUTHCAT 16;                  ! WRITE AUTHORITY CATEGORY OF TABLE!























!*****************************************************************************!
!*                                                                           *! 
!*             S T R U C T U R E S                                           *!
!*                                                                           *!
!*****************************************************************************! 
 



STRUCTURE CMESSAGE =
   1 VALUE 8,
   1 SUBCODE 8;

!STRUCTURE SQLCODE =!       ! TO BE DELETED !
!   1 VALUE 8,
   1 SUBCODE 8     !























!*****************************************************************************!
!*                                                                           *! 
!*             S T A T E S   A N D   S Y M B O L S                           *!
!*                                                                           *!
!*****************************************************************************! 
 


!
BLKREMST            BLKREMSTRPY WILL BE RETURNED WHEN TRHSTOPTRANSR COMES
DDFCSTA             DDFCSTAR WILL BE RETURNED WHEN TRHSTOPTRANSR COMES 
FALSE               SYMBOL VARIABLE NAME STATEMENT IS FALSE
SYMCLEARALLTABS30   SYMBOL FOR A RETURN ADDRESS LABEL
SYMCLEARSOMETABS30  SYMBOL FOR A RETURN ADDRESS LABEL
SYMDDINITFIELD10    SYMBOL FOR A RETURN ADDRESS LABEL
SYMSTTOR10          SYMBOL FOR A RETURN ADDRESS LABEL
SYMSYSINITFK        RETURN TO SYSTEMTABLES VIA SIGNAL SYSRETURNTOFK
SYMSYSINITFLD       RETURN TO SYSTEMTABLES VIA SIGNAL SYSRETURNTOFLD
SYMSYSINITTAB       RETURN TO SYSTEMTABLES VIA SIGNAL SYSRETURNTOTAB
SYMWHICHRESTCASE10  SYMBOL FOR A RETURN ADDRESS LABEL
TRUE                SYMBOL VARIABLE NAME STATEMENT IS TRUE                  !

























!*****************************************************************************!
!*                                                                           *! 
!*             I N C L U D E D   T A B L E S                                 *!
!*                                                                           *!
!*****************************************************************************! 
                         

!BEGIN SQL INCLUDE_TABLE 1!
!******************************************************************************!

!EXEC SQL INCLUDE TABLE PROGRAMS 
   CREATE!

!------------------------------------------------------------------------------!

%%SET tables(,PROGRAMS)
%%SET tabNos(,0)
%%SET tabSlogans(,"""PROGRAM REFERENCES""")
%%SET tabSaes(,"21")
%%SET tabMinSizes(,30)
%%SET tabMaxSizes(,65000)
%%SET tabDivDirs(,1)
%%SET tabRelDivs(,1)
%%SET tabDivConsts(,0)
%%SET workSaes(,"22")
%%SET workMinSizes(,0)
%%SET workMaxSizes(,500)
%%SET workDivDirs(,1)
%%SET workRelDivs(,1)
%%SET workDivConsts(,0)
%%SET tabRAuths(,0)
%%SET tabWAuths(,0)
%%SET tabChecks(,1)
%%SET cols0("DBNUM", "NAME", "BLKREF")
%%SET rnCols0()
%%SET bitsCols0(3)
%%SET symCols0()
%%SET strCols0(2)
%%SET numCols0()
%%SET packNumCols0()
%%SET normCols0(1, 2)
%%SET colTypes0("DBNUMBER", "STRING", "BITS")
%%SET colSizes0(32, 7, 16)
%%SET colProps0("", "RELOAD", "RELOAD")
%%SET colNull0(0, 0, 0)
%%SET colLen0(2, 4, 1)
%%SET colSlogans0("""""", """BLOCK NAME""", """""")
%%SET colVis0("READWRITE", "READONLY", "READONLY")
%%SET colNonVol0(1, 1, 1)
%%SET defCols0()
%%SET bTrees0(2)
%%SET bTreeCols0_2(3)
%%SET aks0()
%%SET fks0()
%%SET schConst0_2(7)
%%SET scanPred0_1("", "SQLC_PROGRAMS_BLKREF_Data", "", "SQLM_PROGRAMS_OperRow", "1", "", "", ">=", "True", "False", "False")
%%SET scanCols0_1(3)
%%SET scanNulls0_1()
%%SET scanNullPtrs0_1()
%%SET colMin0_3(1)
%%SET colMax0_3(65535)


!******************************************************************************!
!END SQL!



!BEGIN SQL INCLUDE_TABLE 1!
!******************************************************************************!

!EXEC SQL INCLUDE TABLE TABLES 
   CREATE!

!------------------------------------------------------------------------------!

%%SET tables(,TABLES)
%%SET tabNos(,1)
%%SET tabSlogans(,"""TABLE DEFINITIONS""")
%%SET tabSaes(,"21")
%%SET tabMinSizes(,30)
%%SET tabMaxSizes(,65000)
%%SET tabDivDirs(,1)
%%SET tabRelDivs(,1)
%%SET tabDivConsts(,0)
%%SET workSaes(,"22")
%%SET workMinSizes(,0)
%%SET workMaxSizes(,500)
%%SET workDivDirs(,1)
%%SET workRelDivs(,1)
%%SET workDivConsts(,0)
%%SET tabRAuths(,0)
%%SET tabWAuths(,0)
%%SET tabChecks(,17)
%%SET cols1("DBNUM", "NAME", "BLKREF", "TABREF", "DESCR", "SAEIDT", "ESTEPT", "MAXST", "ALLOCST", "USEDST", "SAEIDW", "ESTEPW", "MAXSW", "ALLOCSW", "USEDSW", "STATE", "RAUCAT", "WAUCAT", "LOCATE", "NOFLTCO")
%%SET rnCols1(TROWNO)
%%SET bitsCols1(3, 4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17, 18, 20)
%%SET symCols1(16, 19)
%%SET strCols1(2, 5)
%%SET numCols1()
%%SET packNumCols1()
%%SET normCols1(1, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20)
%%SET colTypes1("DBNUMBER", "STRING", "BITS", "BITS", "STRING", "BITS", "BITS", "BITS", "BITS", "BITS", "BITS", "BITS", "BITS", "BITS", "BITS", "SYMBOL", "BITS", "BITS", "SYMBOL", "BITS")
%%SET colSizes1(32, 15, 16, 16, 31, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 1, 8, 8, 1, 8)
%%SET colProps1("", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD")
%%SET colNull1(0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0)
%%SET colLen1(2, 8, 1, 1, 16, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)
%%SET colSlogans1("""""", """TABLE NAME""", """""", """""", """TABLE DESCRIPTION""", """""", """""", """""", """""", """""", """""", """""", """""", """""", """""", """""", """READ AUTHORITY CATEGORY""", """WRITE AUTHORITY CATEGORY""", """TABLE LOCATION""", """NUMBER OF FAULT CODES""")
%%SET colVis1("READWRITE", "READONLY", "READONLY", "INVISIBLE", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READWRITE", "READWRITE", "READONLY", "READONLY")
%%SET colNonVol1(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)
%%SET defCols1(5, 6, 7, 8, 11, 12, 13, 16, 19)
%%SET defVal1_5("""  """)
%%SET defVal1_6("NULL")
%%SET defVal1_7("1")
%%SET defVal1_8("65531")
%%SET defVal1_11("NULL")
%%SET defVal1_12("1")
%%SET defVal1_13("65531")
%%SET defVal1_16("TABLESSTATEWORKING")
%%SET defVal1_19("TABLESLOCATESINGLE")
%%SET symVals1_16(BLOCKED, WORKING)
%%SET symVals1_19(SINGLE, MULTI)
%%SET symLits1_16(0, 1)
%%SET symLits1_19(0, 1)
%%SET bTrees1(3, 4)
%%SET bTreeCols1_3(2, 3)
%%SET bTreeCols1_4(3)
%%SET aks1(3)
%%SET fks1(4)
%%SET fkTab1_4(PROGRAMS)
%%SET fkAct1_4("RESTRICT")
%%SET schConst1_3(24)
%%SET schConst1_4(7)
%%SET scanPred1_1("", "SQLC_TABLES_WAUCAT_Data", "", "SQLM_TABLES_OperRow", "63", "", "", ">", "False", "", "False")
%%SET scanPred1_2("", "SQLC_TABLES_USEDSW_Data", "", "SQLM_TABLES_OperRow", "65531", "", "", ">", "False", "", "False")
%%SET scanPred1_3("", "SQLC_TABLES_USEDST_Data", "", "SQLM_TABLES_OperRow", "65531", "", "", ">", "False", "", "False")
%%SET scanPred1_4("", "SQLC_TABLES_SAEIDW_Data", "", "SQLM_TABLES_OperRow", "999", "", "", ">", "False", "", "False")
%%SET scanPred1_5("", "SQLC_TABLES_NOFLTCO_Data", "", "SQLM_TABLES_OperRow", "64", "", "", ">", "False", "", "False")
%%SET scanPred1_6("", "SQLC_TABLES_RAUCAT_Data", "", "SQLM_TABLES_OperRow", "63", "", "", ">", "False", "", "False")
%%SET scanPred1_7("", "SQLC_TABLES_SAEIDT_Data", "", "SQLM_TABLES_OperRow", "999", "", "", ">", "False", "", "False")
%%SET scanPred1_8("", "SQLC_TABLES_TABREF_Data", "", "SQLM_TABLES_OperRow", "4095", "", "", ">", "False", "", "False")
%%SET scanPred1_9("", "SQLC_TABLES_MAXSW_Data", "", "SQLM_TABLES_OperRow", "65531", "", "", ">", "False", "", "False")
%%SET scanPred1_10("", "SQLC_TABLES_ESTEPW_Data", "", "SQLM_TABLES_OperRow", "1", "", "", "<", "False", "", "False")
%%SET scanPred1_11("", "SQLC_TABLES_ESTEPW_Data", "", "SQLM_TABLES_OperRow", "65531", "", "", ">", "False", "", "False")
%%SET scanPred1_12("", "SQLC_TABLES_MAXST_Data", "", "SQLM_TABLES_OperRow", "65531", "", "", ">", "False", "", "False")
%%SET scanPred1_13("", "SQLC_TABLES_ESTEPT_Data", "", "SQLM_TABLES_OperRow", "1", "", "", "<", "False", "", "False")
%%SET scanPred1_14("", "SQLC_TABLES_ESTEPT_Data", "", "SQLM_TABLES_OperRow", "65531", "", "", ">", "False", "", "False")
%%SET scanPred1_15("", "SQLC_TABLES_ALLOCSW_Data", "", "SQLM_TABLES_OperRow", "65531", "", "", ">", "False", "", "False")
%%SET scanPred1_16("", "SQLC_TABLES_ALLOCST_Data", "", "SQLM_TABLES_OperRow", "65531", "", "", ">", "False", "", "False")
%%SET scanPred1_17("", "SQLC_TABLES_BLKREF_Data", "", "SQLM_TABLES_OperRow", "1", "", "", "<", "False", "True", "False")
%%SET scanCols1_1(18)
%%SET scanCols1_2(15)
%%SET scanCols1_3(10)
%%SET scanCols1_4(11)
%%SET scanCols1_5(20)
%%SET scanCols1_6(17)
%%SET scanCols1_7(6)
%%SET scanCols1_8(4)
%%SET scanCols1_9(13)
%%SET scanCols1_10(12)
%%SET scanCols1_11(12)
%%SET scanCols1_12(8)
%%SET scanCols1_13(7)
%%SET scanCols1_14(7)
%%SET scanCols1_15(14)
%%SET scanCols1_16(9)
%%SET scanCols1_17(3)
%%SET scanNulls1_1()
%%SET scanNulls1_2()
%%SET scanNulls1_3()
%%SET scanNulls1_4()
%%SET scanNulls1_5()
%%SET scanNulls1_6()
%%SET scanNulls1_7()
%%SET scanNulls1_8()
%%SET scanNulls1_9()
%%SET scanNulls1_10()
%%SET scanNulls1_11()
%%SET scanNulls1_12()
%%SET scanNulls1_13()
%%SET scanNulls1_14()
%%SET scanNulls1_15()
%%SET scanNulls1_16()
%%SET scanNulls1_17()
%%SET scanNullPtrs1_1()
%%SET scanNullPtrs1_2()
%%SET scanNullPtrs1_3()
%%SET scanNullPtrs1_4()
%%SET scanNullPtrs1_5()
%%SET scanNullPtrs1_6()
%%SET scanNullPtrs1_7()
%%SET scanNullPtrs1_8()
%%SET scanNullPtrs1_9()
%%SET scanNullPtrs1_10()
%%SET scanNullPtrs1_11()
%%SET scanNullPtrs1_12()
%%SET scanNullPtrs1_13()
%%SET scanNullPtrs1_14()
%%SET scanNullPtrs1_15()
%%SET scanNullPtrs1_16()
%%SET scanNullPtrs1_17()
%%SET colMin1_3(1)
%%SET colMin1_4(0)
%%SET colMin1_6(0)
%%SET colMin1_7(1)
%%SET colMin1_8(0)
%%SET colMin1_9(0)
%%SET colMin1_10(0)
%%SET colMin1_11(0)
%%SET colMin1_12(1)
%%SET colMin1_13(0)
%%SET colMin1_14(0)
%%SET colMin1_15(0)
%%SET colMin1_17(0)
%%SET colMin1_18(0)
%%SET colMin1_20(0)
%%SET colMax1_3(65535)
%%SET colMax1_4(4095)
%%SET colMax1_6(999)
%%SET colMax1_7(65531)
%%SET colMax1_8(65531)
%%SET colMax1_9(65531)
%%SET colMax1_10(65531)
%%SET colMax1_11(999)
%%SET colMax1_12(65531)
%%SET colMax1_13(65531)
%%SET colMax1_14(65531)
%%SET colMax1_15(65531)
%%SET colMax1_17(63)
%%SET colMax1_18(63)
%%SET colMax1_20(64)


!******************************************************************************!
!END SQL!

   

!BEGIN SQL INCLUDE_TABLE 1!
!******************************************************************************!

!EXEC SQL INCLUDE TABLE FIELDS 
   CREATE!

!------------------------------------------------------------------------------!

%%SET tables(,FIELDS)
%%SET tabNos(,2)
%%SET tabSlogans(,"""FIELD DEFINITIONS""")
%%SET tabSaes(,"1")
%%SET tabMinSizes(,200)
%%SET tabMaxSizes(,65000)
%%SET tabDivDirs(,1)
%%SET tabRelDivs(,1)
%%SET tabDivConsts(,0)
%%SET workSaes(,"2")
%%SET workMinSizes(,0)
%%SET workMaxSizes(,500)
%%SET workDivDirs(,1)
%%SET workRelDivs(,1)
%%SET workDivConsts(,0)
%%SET tabRAuths(,0)
%%SET tabWAuths(,0)
%%SET tabChecks(,9)
%%SET cols2("DBNUM", "NAME", "TABREF", "BLKREF", "FIELDNO", "DESCR", "VISIBIL", "PRWIDTH", "NULLPER", "DATATYP", "BADDRES", "MIN", "MAX", "SIZE", "DIDNR", "DIDPOS", "PCLEAR", "PRELOAD", "PDUMP", "PSTATIC", "VOLATIL", "DEFBITS", "DEFSTR", "DEFNSTR", "DEFPNS", "DEFSYMB", "TROWNO")
%%SET rnCols2(FROWNO)
%%SET bitsCols2(3, 4, 5, 8, 11, 12, 13, 14, 15, 16, 22, 27)
%%SET symCols2(7, 9, 10, 17, 18, 19, 20, 21, 26)
%%SET strCols2(2, 6, 23)
%%SET numCols2(24)
%%SET packNumCols2(25)
%%SET normCols2(1, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26)
%%SET colTypes2("DBNUMBER", "STRING", "BITS", "BITS", "BITS", "STRING", "SYMBOL", "BITS", "SYMBOL", "SYMBOL", "BITS", "BITS", "BITS", "BITS", "BITS", "BITS", "SYMBOL", "SYMBOL", "SYMBOL", "SYMBOL", "SYMBOL", "BITS", "STRING", "NUMSTRING", "PACKED NUMSTRING", "SYMBOL", "BITS")
%%SET colSizes2(32, 7, 16, 16, 16, 31, 2, 8, 1, 4, 16, 16, 16, 16, 16, 16, 1, 1, 1, 1, 1, 16, 31, 31, 28, 2, 16)
%%SET colProps2("", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD")
%%SET colNull2(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1)
%%SET colLen2(2, 4, 1, 1, 1, 16, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 16, 16, 8, 1, 1)
%%SET colSlogans2("""""", """FIELD NAME""", """""", """""", """""", """FIELD DESCRIPTION""", """""", """""", """NULL PERMITTED""", """""", """BASE ADDRESS""", """""", """""", """""", """""", """""", """""", """""", """""", """""", """""", """""", """""", """""", """""", """""", """""")
%%SET colVis2("READWRITE", "READONLY", "INVISIBLE", "INVISIBLE", "INVISIBLE", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY")
%%SET colNonVol2(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)
%%SET defCols2(6, 7, 12, 13, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27)
%%SET defVal2_6("""  """)
%%SET defVal2_7("FIELDSVISIBILREADWR")
%%SET defVal2_12("NULL")
%%SET defVal2_13("NULL")
%%SET defVal2_15("NULL")
%%SET defVal2_16("NULL")
%%SET defVal2_17("FIELDSPCLEARNO")
%%SET defVal2_18("FIELDSPRELOADYES")
%%SET defVal2_19("FIELDSPDUMPNO")
%%SET defVal2_20("FIELDSPSTATICNO")
%%SET defVal2_21("FIELDSVOLATILNO")
%%SET defVal2_22("NULL")
%%SET defVal2_23("NULL")
%%SET defVal2_24("NULL")
%%SET defVal2_25("NULL")
%%SET defVal2_26("NULL")
%%SET defVal2_27("NULL")
%%SET symVals2_7(INVIS, READO, READWR)
%%SET symVals2_9(TRUE, FALSE)
%%SET symVals2_10(BITS, STRING, NUMSTR, PNUMSTR, SYMBOL, ROWNUM, DBNUM)
%%SET symVals2_17(YES, NO)
%%SET symVals2_18(YES, NO)
%%SET symVals2_19(YES, NO)
%%SET symVals2_20(YES, NO)
%%SET symVals2_21(YES, NO)
%%SET symVals2_26(SYMBOL1, SYMBOL2, SYMBOL3)
%%SET symLits2_7(0, 1, 2)
%%SET symLits2_9(0, 1)
%%SET symLits2_10(0, 1, 2, 3, 4, 5, 6)
%%SET symLits2_17(0, 1)
%%SET symLits2_18(0, 1)
%%SET symLits2_19(0, 1)
%%SET symLits2_20(0, 1)
%%SET symLits2_21(0, 1)
%%SET symLits2_26(0, 1, 2)
%%SET bTrees2(3, 4, 5)
%%SET bTreeCols2_3(2, 3, 4)
%%SET bTreeCols2_4(3, 4, 5)
%%SET bTreeCols2_5(27)
%%SET aks2(3, 4)
%%SET fks2(5)
%%SET fkTab2_5(TABLES)
%%SET fkAct2_5("SET NULL")
%%SET schConst2_3(24)
%%SET schConst2_4(17)
%%SET schConst2_5(11)
%%SET scanPred2_1("", "SQLC_FIELDS_TROWNO_Data", "", "SQLM_FIELDS_OperRow", "65531", "", "", ">", "False", "", "False")
%%SET scanPred2_2("", "SQLC_FIELDS_PRWIDTH_Data", "", "SQLM_FIELDS_OperRow", "1", "", "", "<", "False", "", "False")
%%SET scanPred2_3("", "SQLC_FIELDS_PRWIDTH_Data", "", "SQLM_FIELDS_OperRow", "63", "", "", ">", "False", "", "False")
%%SET scanPred2_4("", "SQLC_FIELDS_TABREF_Data", "", "SQLM_FIELDS_OperRow", "4095", "", "", ">", "False", "", "False")
%%SET scanPred2_5("", "SQLC_FIELDS_FIELDNO_Data", "", "SQLM_FIELDS_OperRow", "1", "", "", "<", "False", "", "False")
%%SET scanPred2_6("", "SQLC_FIELDS_FIELDNO_Data", "", "SQLM_FIELDS_OperRow", "4096", "", "", ">", "False", "", "False")
%%SET scanPred2_7("", "SQLC_FIELDS_BADDRES_Data", "", "SQLM_FIELDS_OperRow", "1", "", "", "<", "False", "", "False")
%%SET scanPred2_8("", "SQLC_FIELDS_BADDRES_Data", "", "SQLM_FIELDS_OperRow", "4095", "", "", ">", "False", "", "False")
%%SET scanPred2_9("", "SQLC_FIELDS_BLKREF_Data", "", "SQLM_FIELDS_OperRow", "1", "", "", "<", "False", "True", "False")
%%SET scanCols2_1(27)
%%SET scanCols2_2(8)
%%SET scanCols2_3(8)
%%SET scanCols2_4(3)
%%SET scanCols2_5(5)
%%SET scanCols2_6(5)
%%SET scanCols2_7(11)
%%SET scanCols2_8(11)
%%SET scanCols2_9(4)
%%SET scanNulls2_1()
%%SET scanNulls2_2()
%%SET scanNulls2_3()
%%SET scanNulls2_4()
%%SET scanNulls2_5()
%%SET scanNulls2_6()
%%SET scanNulls2_7()
%%SET scanNulls2_8()
%%SET scanNulls2_9()
%%SET scanNullPtrs2_1()
%%SET scanNullPtrs2_2()
%%SET scanNullPtrs2_3()
%%SET scanNullPtrs2_4()
%%SET scanNullPtrs2_5()
%%SET scanNullPtrs2_6()
%%SET scanNullPtrs2_7()
%%SET scanNullPtrs2_8()
%%SET scanNullPtrs2_9()
%%SET colMin2_3(0)
%%SET colMin2_4(1)
%%SET colMin2_5(1)
%%SET colMin2_8(1)
%%SET colMin2_11(1)
%%SET colMin2_12(0)
%%SET colMin2_13(0)
%%SET colMin2_14(0)
%%SET colMin2_15(0)
%%SET colMin2_16(0)
%%SET colMin2_22(0)
%%SET colMin2_27(0)
%%SET colMax2_3(4095)
%%SET colMax2_4(65535)
%%SET colMax2_5(4096)
%%SET colMax2_8(63)
%%SET colMax2_11(4095)
%%SET colMax2_12(65535)
%%SET colMax2_13(65535)
%%SET colMax2_14(65535)
%%SET colMax2_15(65535)
%%SET colMax2_16(65535)
%%SET colMax2_22(65535)
%%SET colMax2_27(65531)


!******************************************************************************!
!END SQL!

   

!BEGIN SQL INCLUDE_TABLE 1!
!******************************************************************************!

!EXEC SQL INCLUDE TABLE KEYS 
   CREATE!

!------------------------------------------------------------------------------!

%%SET tables(,KEYS)
%%SET tabNos(,3)
%%SET tabSlogans(,"""KEY DEFINITIONS""")
%%SET tabSaes(,"3")
%%SET tabMinSizes(,0)
%%SET tabMaxSizes(,30)
%%SET tabDivDirs(,1)
%%SET tabRelDivs(,1)
%%SET tabDivConsts(,0)
%%SET workSaes(,"4")
%%SET workMinSizes(,0)
%%SET workMaxSizes(,500)
%%SET workDivDirs(,1)
%%SET workRelDivs(,1)
%%SET workDivConsts(,0)
%%SET tabRAuths(,0)
%%SET tabWAuths(,0)
%%SET tabChecks(,3)
%%SET cols3("DBNUM", "TROWNO", "KEYNO", "TABREF", "BLKREF", "KEYTYPE")
%%SET rnCols3()
%%SET bitsCols3(2, 3, 4, 5)
%%SET symCols3(6)
%%SET strCols3()
%%SET numCols3()
%%SET packNumCols3()
%%SET normCols3(1, 6)
%%SET colTypes3("DBNUMBER", "BITS", "BITS", "BITS", "BITS", "SYMBOL")
%%SET colSizes3(32, 16, 8, 16, 16, 2)
%%SET colProps3("", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD")
%%SET colNull3(0, 0, 0, 0, 0, 0)
%%SET colLen3(2, 1, 1, 1, 1, 1)
%%SET colSlogans3("""""", """""", """""", """""", """""", """""")
%%SET colVis3("READWRITE", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY")
%%SET colNonVol3(1, 1, 1, 1, 1, 1)
%%SET defCols3(2)
%%SET defVal3_2("1")
%%SET symVals3_6(PRIMKEY, ALTERN, INDKEY)
%%SET symLits3_6(0, 1, 2)
%%SET bTrees3(2, 3, 4)
%%SET bTreeCols3_2(2, 3)
%%SET bTreeCols3_3(5, 4, 3)
%%SET bTreeCols3_4(2)
%%SET aks3(3)
%%SET fks3(4)
%%SET fkTab3_4(TABLES)
%%SET fkAct3_4("SET DEFAULT")
%%SET schConst3_2(12)
%%SET schConst3_3(17)
%%SET schConst3_4(7)
%%SET scanPred3_1("", "SQLC_KEYS_TABREF_Data", "", "SQLM_KEYS_OperRow", "4095", "", "", ">", "False", "", "False")
%%SET scanPred3_2("", "SQLC_KEYS_BLKREF_Data", "", "SQLM_KEYS_OperRow", "1", "", "", "<", "False", "", "False")
%%SET scanPred3_3("", "SQLC_KEYS_TROWNO_Data", "", "SQLM_KEYS_OperRow", "65531", "", "", ">", "False", "True", "False")
%%SET scanCols3_1(4)
%%SET scanCols3_2(5)
%%SET scanCols3_3(2)
%%SET scanNulls3_1()
%%SET scanNulls3_2()
%%SET scanNulls3_3()
%%SET scanNullPtrs3_1()
%%SET scanNullPtrs3_2()
%%SET scanNullPtrs3_3()
%%SET colMin3_2(0)
%%SET colMin3_3(0)
%%SET colMin3_4(0)
%%SET colMin3_5(1)
%%SET colMax3_2(65531)
%%SET colMax3_3(255)
%%SET colMax3_4(4095)
%%SET colMax3_5(65535)


!******************************************************************************!
!END SQL!

   

!BEGIN SQL INCLUDE_TABLE 1!
!******************************************************************************!

!EXEC SQL INCLUDE TABLE KEYFIELDS
   CREATE!

!------------------------------------------------------------------------------!

%%SET tables(,KEYFIELDS)
%%SET tabNos(,4)
%%SET tabSlogans(,"""KEYFIELD DEFINITIONS""")
%%SET tabSaes(,"5")
%%SET tabMinSizes(,0)
%%SET tabMaxSizes(,30)
%%SET tabDivDirs(,1)
%%SET tabRelDivs(,1)
%%SET tabDivConsts(,0)
%%SET workSaes(,"6")
%%SET workMinSizes(,0)
%%SET workMaxSizes(,500)
%%SET workDivDirs(,1)
%%SET workRelDivs(,1)
%%SET workDivConsts(,0)
%%SET tabRAuths(,0)
%%SET tabWAuths(,0)
%%SET tabChecks(,6)
%%SET cols4("DBNUM", "TROWNO", "KEYNO", "TABREF", "BLKREF", "COMPNO", "FROWNO")
%%SET rnCols4()
%%SET bitsCols4(2, 3, 4, 5, 6, 7)
%%SET symCols4()
%%SET strCols4()
%%SET numCols4()
%%SET packNumCols4()
%%SET normCols4(1, 7)
%%SET colTypes4("DBNUMBER", "BITS", "BITS", "BITS", "BITS", "BITS", "BITS")
%%SET colSizes4(32, 16, 8, 16, 16, 8, 16)
%%SET colProps4("", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD")
%%SET colNull4(0, 0, 0, 0, 0, 0, 0)
%%SET colLen4(2, 1, 1, 1, 1, 1, 1)
%%SET colSlogans4("""""", """""", """""", """""", """""", """""", """""")
%%SET colVis4("READWRITE", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY")
%%SET colNonVol4(1, 1, 1, 1, 1, 1, 1)
%%SET defCols4()
%%SET bTrees4(2, 3)
%%SET bTreeCols4_2(2, 3, 6)
%%SET bTreeCols4_3(5, 4, 3, 6)
%%SET aks4(3)
%%SET fks4()
%%SET schConst4_2(17)
%%SET schConst4_3(23)
%%SET scanPred4_1("", "SQLC_KEYFIELDS_TABREF_Data", "", "SQLM_KEYFIELDS_OperRow", "4095", "", "", ">", "False", "", "False")
%%SET scanPred4_2("", "SQLC_KEYFIELDS_FROWNO_Data", "", "SQLM_KEYFIELDS_OperRow", "65531", "", "", ">", "False", "", "False")
%%SET scanPred4_3("", "SQLC_KEYFIELDS_COMPNO_Data", "", "SQLM_KEYFIELDS_OperRow", "1", "", "", "<", "False", "", "False")
%%SET scanPred4_4("", "SQLC_KEYFIELDS_COMPNO_Data", "", "SQLM_KEYFIELDS_OperRow", "16", "", "", ">", "False", "", "False")
%%SET scanPred4_5("", "SQLC_KEYFIELDS_BLKREF_Data", "", "SQLM_KEYFIELDS_OperRow", "1", "", "", "<", "False", "", "False")
%%SET scanPred4_6("", "SQLC_KEYFIELDS_TROWNO_Data", "", "SQLM_KEYFIELDS_OperRow", "65531", "", "", ">", "False", "True", "False")
%%SET scanCols4_1(4)
%%SET scanCols4_2(7)
%%SET scanCols4_3(6)
%%SET scanCols4_4(6)
%%SET scanCols4_5(5)
%%SET scanCols4_6(2)
%%SET scanNulls4_1()
%%SET scanNulls4_2()
%%SET scanNulls4_3()
%%SET scanNulls4_4()
%%SET scanNulls4_5()
%%SET scanNulls4_6()
%%SET scanNullPtrs4_1()
%%SET scanNullPtrs4_2()
%%SET scanNullPtrs4_3()
%%SET scanNullPtrs4_4()
%%SET scanNullPtrs4_5()
%%SET scanNullPtrs4_6()
%%SET colMin4_2(0)
%%SET colMin4_3(0)
%%SET colMin4_4(0)
%%SET colMin4_5(1)
%%SET colMin4_6(1)
%%SET colMin4_7(0)
%%SET colMax4_2(65531)
%%SET colMax4_3(255)
%%SET colMax4_4(4095)
%%SET colMax4_5(65535)
%%SET colMax4_6(16)
%%SET colMax4_7(65531)


!******************************************************************************!
!END SQL!

   

!BEGIN SQL INCLUDE_TABLE 1!
!******************************************************************************!

!EXEC SQL INCLUDE TABLE FOREIGNKEYS
   CREATE!

!------------------------------------------------------------------------------!

%%SET tables(,FOREIGNKEYS)
%%SET tabNos(,5)
%%SET tabSlogans(,"""FOREIGN KEY DEFINITIONS""")
%%SET tabSaes(,"7")
%%SET tabMinSizes(,30)
%%SET tabMaxSizes(,65000)
%%SET tabDivDirs(,1)
%%SET tabRelDivs(,1)
%%SET tabDivConsts(,0)
%%SET workSaes(,"8")
%%SET workMinSizes(,0)
%%SET workMaxSizes(,500)
%%SET workDivDirs(,1)
%%SET workRelDivs(,1)
%%SET workDivConsts(,0)
%%SET tabRAuths(,0)
%%SET tabWAuths(,0)
%%SET tabChecks(,6)
%%SET cols5("DBNUM", "TROWNO", "ORDNO", "BLKREF", "TABREF", "KEYNO", "FTROWNO", "FTABREF", "FBLKREF", "COND")
%%SET rnCols5()
%%SET bitsCols5(2, 3, 4, 5, 6, 7, 8, 9)
%%SET symCols5(10)
%%SET strCols5()
%%SET numCols5()
%%SET packNumCols5()
%%SET normCols5(1, 6, 8, 9, 10)
%%SET colTypes5("DBNUMBER", "BITS", "BITS", "BITS", "BITS", "BITS", "BITS", "BITS", "BITS", "SYMBOL")
%%SET colSizes5(32, 16, 8, 16, 16, 8, 16, 16, 16, 4)
%%SET colProps5("", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD", "RELOAD")
%%SET colNull5(0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
%%SET colLen5(2, 1, 1, 1, 1, 1, 1, 1, 1, 1)
%%SET colSlogans5("""""", """""", """""", """""", """""", """""", """""", """""", """""", """""")
%%SET colVis5("READWRITE", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY", "READONLY")
%%SET colNonVol5(1, 1, 1, 1, 1, 1, 1, 1, 1, 1)
%%SET defCols5()
%%SET symVals5_10(RESTR, CASCAD, SETNULL, SETDEF)
%%SET symLits5_10(0, 1, 2, 3)
%%SET bTrees5(2, 3, 4, 5)
%%SET bTreeCols5_2(2, 3)
%%SET bTreeCols5_3(3, 4, 5)
%%SET bTreeCols5_4(2)
%%SET bTreeCols5_5(7)
%%SET aks5(3)
%%SET fks5(4, 5)
%%SET fkTab5_4(TABLES)
%%SET fkTab5_5(TABLES)
%%SET fkAct5_4("CASCADE")
%%SET fkAct5_5("CASCADE")
%%SET schConst5_2(12)
%%SET schConst5_3(17)
%%SET schConst5_4(7)
%%SET schConst5_5(7)
%%SET scanPred5_1("", "SQLC_FOREIGNKEYS_TABREF_Data", "", "SQLM_FOREIGNKEYS_OperRow", "4095", "", "", ">", "False", "", "False")
%%SET scanPred5_2("", "SQLC_FOREIGNKEYS_FBLKREF_Data", "", "SQLM_FOREIGNKEYS_OperRow", "1", "", "", "<", "False", "", "False")
%%SET scanPred5_3("", "SQLC_FOREIGNKEYS_FTABREF_Data", "", "SQLM_FOREIGNKEYS_OperRow", "4095", "", "", ">", "False", "", "False")
%%SET scanPred5_4("", "SQLC_FOREIGNKEYS_FTROWNO_Data", "", "SQLM_FOREIGNKEYS_OperRow", "65531", "", "", ">", "False", "", "False")
%%SET scanPred5_5("", "SQLC_FOREIGNKEYS_BLKREF_Data", "", "SQLM_FOREIGNKEYS_OperRow", "1", "", "", "<", "False", "", "False")
%%SET scanPred5_6("", "SQLC_FOREIGNKEYS_TROWNO_Data", "", "SQLM_FOREIGNKEYS_OperRow", "65531", "", "", ">", "False", "True", "False")
%%SET scanCols5_1(5)
%%SET scanCols5_2(9)
%%SET scanCols5_3(8)
%%SET scanCols5_4(7)
%%SET scanCols5_5(4)
%%SET scanCols5_6(2)
%%SET scanNulls5_1()
%%SET scanNulls5_2()
%%SET scanNulls5_3()
%%SET scanNulls5_4()
%%SET scanNulls5_5()
%%SET scanNulls5_6()
%%SET scanNullPtrs5_1()
%%SET scanNullPtrs5_2()
%%SET scanNullPtrs5_3()
%%SET scanNullPtrs5_4()
%%SET scanNullPtrs5_5()
%%SET scanNullPtrs5_6()
%%SET colMin5_2(0)
%%SET colMin5_3(0)
%%SET colMin5_4(1)
%%SET colMin5_5(0)
%%SET colMin5_6(0)
%%SET colMin5_7(0)
%%SET colMin5_8(0)
%%SET colMin5_9(1)
%%SET colMax5_2(65531)
%%SET colMax5_3(255)
%%SET colMax5_4(65535)
%%SET colMax5_5(4095)
%%SET colMax5_6(255)
%%SET colMax5_7(65531)
%%SET colMax5_8(4095)
%%SET colMax5_9(65535)


!******************************************************************************!
!END SQL!

   

!BEGIN SQL INCLUDE_TABLE 1!
!******************************************************************************!

!EXEC SQL INCLUDE TABLE SYMBOLS 
   CREATE!

!------------------------------------------------------------------------------!

%%SET tables(,SYMBOLS)
%%SET tabNos(,6)
%%SET tabSlogans(,"""SYMBOL VALUES""")
%%SET tabSaes(,"9")
%%SET tabMinSizes(,0)
%%SET tabMaxSizes(,30)
%%SET tabDivDirs(,1)
%%SET tabRelDivs(,1)
%%SET tabDivConsts(,0)
%%SET workSaes(,"10")
%%SET workMinSizes(,0)
%%SET workMaxSizes(,500)
%%SET workDivDirs(,1)
%%SET workRelDivs(,1)
%%SET workDivConsts(,0)
%%SET tabRAuths(,0)
%%SET tabWAuths(,0)
%%SET tabChecks(,1)
%%SET cols6("DBNUM", "FROWNO", "SYMBOL", "SYMVAL")
%%SET rnCols6()
%%SET bitsCols6(2, 4)
%%SET symCols6()
%%SET strCols6(3)
%%SET numCols6()
%%SET packNumCols6()
%%SET normCols6(1)
%%SET colTypes6("DBNUMBER", "BITS", "STRING", "BITS")
%%SET colSizes6(32, 16, 7, 16)
%%SET colProps6("", "RELOAD", "RELOAD", "RELOAD")
%%SET colNull6(0, 0, 0, 0)
%%SET colLen6(2, 1, 4, 1)
%%SET colSlogans6("""""", """""", """SYMBOL NAME""", """SYMBOL VALUE""")
%%SET colVis6("READWRITE", "READONLY", "READONLY", "READONLY")
%%SET colNonVol6(1, 1, 1, 1)
%%SET defCols6()
%%SET bTrees6(2, 3)
%%SET bTreeCols6_2(2, 3)
%%SET bTreeCols6_3(2, 4)
%%SET aks6(3)
%%SET fks6()
%%SET schConst6_2(19)
%%SET schConst6_3(12)
%%SET scanPred6_1("", "SQLC_SYMBOLS_FROWNO_Data", "", "SQLM_SYMBOLS_OperRow", "65531", "", "", "=<", "True", "False", "False")
%%SET scanCols6_1(2)
%%SET scanNulls6_1()
%%SET scanNullPtrs6_1()
%%SET colMin6_2(0)
%%SET colMin6_4(0)
%%SET colMax6_2(65531)
%%SET colMax6_4(65535)


!******************************************************************************!
!END SQL!

   

!BEGIN SQL INCLUDE_TABLE 1!
!******************************************************************************!

!EXEC SQL INCLUDE TABLE TOWFAULTCODES 
   CREATE!

!------------------------------------------------------------------------------!

%%SET tables(,TOWFAULTCODES)
%%SET tabNos(,7)
%%SET tabSlogans(,"""TABLE OWNER FAULT CODES""")
%%SET tabSaes(,"13")
%%SET tabMinSizes(,0)
%%SET tabMaxSizes(,30)
%%SET tabDivDirs(,1)
%%SET tabRelDivs(,1)
%%SET tabDivConsts(,0)
%%SET workSaes(,"14")
%%SET workMinSizes(,0)
%%SET workMaxSizes(,500)
%%SET workDivDirs(,1)
%%SET workRelDivs(,1)
%%SET workDivConsts(,0)
%%SET tabRAuths(,0)
%%SET tabWAuths(,0)
%%SET tabChecks(,2)
%%SET cols7("DBNUM", "TROWNO", "FAULTNO", "FLTTEXT")
%%SET rnCols7()
%%SET bitsCols7(2, 3)
%%SET symCols7()
%%SET strCols7(4)
%%SET numCols7()
%%SET packNumCols7()
%%SET normCols7(1, 4)
%%SET colTypes7("DBNUMBER", "BITS", "BITS", "STRING")
%%SET colSizes7(32, 16, 8, 31)
%%SET colProps7("", "RELOAD", "RELOAD", "RELOAD")
%%SET colNull7(0, 0, 0, 0)
%%SET colLen7(2, 1, 1, 16)
%%SET colSlogans7("""""", """""", """""", """""")
%%SET colVis7("READWRITE", "READONLY", "READONLY", "READONLY")
%%SET colNonVol7(1, 1, 1, 1)
%%SET defCols7()
%%SET bTrees7(2)
%%SET bTreeCols7_2(2, 3)
%%SET aks7()
%%SET fks7()
%%SET schConst7_2(12)
%%SET scanPred7_1("", "SQLC_TOWFAULTCODES_FAULTNO_Data", "", "SQLM_TOWFAULTCODES_OperRow", "1", "", "", "<", "False", "", "False")
%%SET scanPred7_2("", "SQLC_TOWFAULTCODES_TROWNO_Data", "", "SQLM_TOWFAULTCODES_OperRow", "65531", "", "", ">", "False", "True", "False")
%%SET scanCols7_1(3)
%%SET scanCols7_2(2)
%%SET scanNulls7_1()
%%SET scanNulls7_2()
%%SET scanNullPtrs7_1()
%%SET scanNullPtrs7_2()
%%SET colMin7_2(0)
%%SET colMin7_3(1)
%%SET colMax7_2(65531)
%%SET colMax7_3(255)


!******************************************************************************!
!END SQL!

   

!BEGIN SQL INCLUDE_TABLE 1!
!******************************************************************************!

!EXEC SQL INCLUDE TABLE SYSFAULTCODES
   CREATE!

!------------------------------------------------------------------------------!

%%SET tables(,SYSFAULTCODES)
%%SET tabNos(,8)
%%SET tabSlogans(,"""""")
%%SET tabSaes(,"15")
%%SET tabMinSizes(,0)
%%SET tabMaxSizes(,65000)
%%SET tabDivDirs(,1)
%%SET tabRelDivs(,1)
%%SET tabDivConsts(,0)
%%SET workSaes(,"16")
%%SET workMinSizes(,0)
%%SET workMaxSizes(,500)
%%SET workDivDirs(,1)
%%SET workRelDivs(,1)
%%SET workDivConsts(,0)
%%SET tabRAuths(,0)
%%SET tabWAuths(,0)
%%SET tabChecks(,2)
%%SET cols8("DBNUM", "FAULTNO", "FLTTEXT")
%%SET rnCols8()
%%SET bitsCols8(2)
%%SET symCols8()
%%SET strCols8(3)
%%SET numCols8()
%%SET packNumCols8()
%%SET normCols8(1, 3)
%%SET colTypes8("DBNUMBER", "BITS", "STRING")
%%SET colSizes8(32, 16, 15)
%%SET colProps8("", "RELOAD", "RELOAD")
%%SET colNull8(0, 0, 0)
%%SET colLen8(2, 1, 8)
%%SET colSlogans8("""""", """""", """""")
%%SET colVis8("READWRITE", "READWRITE", "READWRITE")
%%SET colNonVol8(1, 1, 1)
%%SET defCols8()
%%SET bTrees8(2)
%%SET bTreeCols8_2(2)
%%SET aks8()
%%SET fks8()
%%SET schConst8_2(7)
%%SET scanPred8_1("", "SQLC_SYSFAULTCODES_FAULTNO_Data", "", "SQLM_SYSFAULTCODES_OperRow", "256", "", "", "<", "False", "", "False")
%%SET scanPred8_2("", "SQLC_SYSFAULTCODES_FAULTNO_Data", "", "SQLM_SYSFAULTCODES_OperRow", "511", "", "", ">", "False", "True", "False")
%%SET scanCols8_1(2)
%%SET scanCols8_2(2)
%%SET scanNulls8_1()
%%SET scanNulls8_2()
%%SET scanNullPtrs8_1()
%%SET scanNullPtrs8_2()
%%SET colMin8_2(256)
%%SET colMax8_2(511)


!******************************************************************************!
!END SQL!

   

!BEGIN SQL INCLUDE_TABLE 1!
!******************************************************************************!

!EXEC SQL INCLUDE TABLE SYSTEMFIELDS 
   CREATE!

!------------------------------------------------------------------------------!

%%SET tables(,SYSTEMFIELDS)
%%SET tabNos(,9)
%%SET tabSlogans(,"""""")
%%SET tabSaes(,"19")
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
%%SET tabChecks(,5)
%%SET cols9("DBNUM", "TROWNO", "ROWGEN", "LOCK")
%%SET rnCols9()
%%SET bitsCols9(2, 3, 4)
%%SET symCols9()
%%SET strCols9()
%%SET numCols9()
%%SET packNumCols9()
%%SET normCols9(1, 3, 4)
%%SET colTypes9("DBNUMBER", "BITS", "BITS", "BITS")
%%SET colSizes9(32, 16, 16, 16)
%%SET colProps9("", "RELOAD", "RELOAD", "RELOAD")
%%SET colNull9(0, 0, 0, 0)
%%SET colLen9(2, 1, 1, 1)
%%SET colSlogans9("""""", """""", """""", """""")
%%SET colVis9("READWRITE", "READONLY", "READONLY", "READONLY")
%%SET colNonVol9(1, 1, 1, 1)
%%SET defCols9()
%%SET bTrees9(2, 3)
%%SET bTreeCols9_2(2)
%%SET bTreeCols9_3(2)
%%SET aks9()
%%SET fks9(3)
%%SET fkTab9_3(TABLES)
%%SET fkAct9_3("RESTRICT")
%%SET schConst9_2(7)
%%SET schConst9_3(7)
%%SET scanPred9_1("", "SQLC_SYSTEMFIELDS_LOCK_Data", "", "SQLM_SYSTEMFIELDS_OperRow", "1", "", "", "<", "False", "", "False")
%%SET scanPred9_2("", "SQLC_SYSTEMFIELDS_LOCK_Data", "", "SQLM_SYSTEMFIELDS_OperRow", "4095", "", "", ">", "False", "", "False")
%%SET scanPred9_3("", "SQLC_SYSTEMFIELDS_ROWGEN_Data", "", "SQLM_SYSTEMFIELDS_OperRow", "1", "", "", "<", "False", "", "False")
%%SET scanPred9_4("", "SQLC_SYSTEMFIELDS_ROWGEN_Data", "", "SQLM_SYSTEMFIELDS_OperRow", "4095", "", "", ">", "False", "", "False")
%%SET scanPred9_5("", "SQLC_SYSTEMFIELDS_TROWNO_Data", "", "SQLM_SYSTEMFIELDS_OperRow", "65531", "", "", ">", "False", "True", "False")
%%SET scanCols9_1(4)
%%SET scanCols9_2(4)
%%SET scanCols9_3(3)
%%SET scanCols9_4(3)
%%SET scanCols9_5(2)
%%SET scanNulls9_1()
%%SET scanNulls9_2()
%%SET scanNulls9_3()
%%SET scanNulls9_4()
%%SET scanNulls9_5()
%%SET scanNullPtrs9_1()
%%SET scanNullPtrs9_2()
%%SET scanNullPtrs9_3()
%%SET scanNullPtrs9_4()
%%SET scanNullPtrs9_5()
%%SET colMin9_2(0)
%%SET colMin9_3(1)
%%SET colMin9_4(1)
%%SET colMax9_2(65531)
%%SET colMax9_3(4095)
%%SET colMax9_4(4095)


!******************************************************************************!
!END SQL!



! The includes below are only stated to make sure that all the
  grammar rules are used !


!BEGIN SQL INCLUDE_TABLE 1!
!******************************************************************************!

!EXEC SQL INCLUDE TABLE TEST1
   CREATE!

!------------------------------------------------------------------------------!

%%SET tables(,TEST1)
%%SET tabNos(,10)
%%SET tabSlogans(,"""test table no 1""")
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
%%SET tabChecks(,6)
%%SET cols10("COL10", "COL1", "COL2", "COL3", "COL4", "COL5", "COL6", "COL7", "COL8")
%%SET rnCols10(COL9)
%%SET bitsCols10(3, 4)
%%SET symCols10(8)
%%SET strCols10(2, 5, 7)
%%SET numCols10(6)
%%SET packNumCols10(9)
%%SET normCols10(1, 4, 5, 7, 8, 9)
%%SET colTypes10("DBNUMBER", "STRING", "BITS", "BITS", "STRING", "NUMSTRING", "STRING", "SYMBOL", "PACKED NUMSTRING")
%%SET colSizes10(0, 15, 16, 16, 15, 7, 31, 1, 28)
%%SET colProps10("", "RELOAD", "RELOAD", "RELOAD", "", "RELOAD", "RELOAD", "RELOAD", "RELOAD")
%%SET colNull10(0, 0, 0, 1, 0, 1, 1, 1, 1)
%%SET colLen10(2, 8, 1, 1, 8, 4, 16, 1, 8)
%%SET colSlogans10("""""", """column 1""", """column 2""", """column 3""", """column 4""", """""", """""", """""", """""")
%%SET colVis10("READWRITE", "READWRITE", "READWRITE", "READWRITE", "READWRITE", "READWRITE", "READWRITE", "READWRITE", "READWRITE")
%%SET colNonVol10(1, 1, 1, 1, 0, 1, 1, 1, 1)
%%SET defCols10(4, 5, 6, 7, 8, 9)
%%SET defVal10_4("NULL")
%%SET defVal10_5("""xxx""")
%%SET defVal10_6("NULL")
%%SET defVal10_7("NULL")
%%SET defVal10_8("NULL")
%%SET defVal10_9("NULL")
%%SET symVals10_8(FALSE, TRUE)
%%SET symLits10_8(0, 1)
%%SET bTrees10(2, 3)
%%SET bTreeCols10_2(2, 3)
%%SET bTreeCols10_3(6)
%%SET aks10()
%%SET fks10()
%%SET schConst10_2(24)
%%SET schConst10_3(17)
%%SET prepLabel10(XX)
%%SET commLabel10(YY)
%%SET rollLabel10(ZZ)
%%SET scanPred10_1("", "SQLC_TEST1_COL2_Data", "", "SQLM_TEST1_OperRow", "4", "", "", ">", "0", "", "2")
%%SET scanPred10_2("2", "SQLC_TEST1_COL1_Data", "", "SQLM_TEST1_OperRow", "(A * B) / C", "", "", "<", "2", "", "1")
%%SET scanPred10_3("", "D", "", "", "- 4", "", "", "/=", "2", "0", "")
%%SET scanPred10_4("1", "SQLC_TEST1_COL1_Data", "", "SQLM_TEST1_OperRow", "2", "", "", ">=", "False", "", "False")
%%SET scanPred10_5("0", "SQLC_TEST1_COL3_Data", "", "SQLM_TEST1_OperRow", "0", "", "", "<", "False", "", "False")
%%SET scanPred10_6("", "SQLC_TEST1_COL2_Data", "", "SQLM_TEST1_OperRow", "0", "", "", "<", "False", "True", "False")
%%SET scanCols10_1(3)
%%SET scanCols10_2(2)
%%SET scanCols10_3()
%%SET scanCols10_4(2)
%%SET scanCols10_5(4)
%%SET scanCols10_6(3)
%%SET scanNulls10_1()
%%SET scanNulls10_2()
%%SET scanNulls10_3()
%%SET scanNulls10_4()
%%SET scanNulls10_5()
%%SET scanNulls10_6()
%%SET scanNullPtrs10_1()
%%SET scanNullPtrs10_2()
%%SET scanNullPtrs10_3()
%%SET scanNullPtrs10_4()
%%SET scanNullPtrs10_5()
%%SET scanNullPtrs10_6()
%%SET colMin10_3(0)
%%SET colMin10_4(0)
%%SET colMax10_3(65535)
%%SET colMax10_4(65535)


!******************************************************************************!
!END SQL!



!BEGIN SQL INCLUDE_TABLE 0!
!******************************************************************************!

!EXEC SQL INCLUDE TABLE TEST2!

!------------------------------------------------------------------------------!

%%SET remTables(,TEST2)
%%SET remTabNos(,256)
%%SET cols256("COL10", "COL1", "COL2", "COL3", "COL4", "COL5", "COL6", "COL7", "COL8")
%%SET colLen256(2, 8, 1, 1, 8, 4, 16, 1, 8)
%%SET colNull256(0, 0, 0, 1, 0, 1, 1, 1, 1)
%%SET colTypes256("DBNUMBER", "STRING", "BITS", "BITS", "STRING", "NUMSTRING", "STRING", "SYMBOL", "PACKED NUMSTRING")
%%SET colSizes256(0, 15, 16, 16, 15, 7, 31, 1, 28)
%%SET bTrees256(2, 3)
%%SET bTreeCols256_2(2, 3)
%%SET bTreeCols256_3(6)
%%SET symCols256(8)
%%SET symVals256_8(FALSE, TRUE)
%%SET symLits256_8(0, 1)


!******************************************************************************!
!END SQL!



!BEGIN SQL INCLUDE_TABLE 0!
!******************************************************************************!

!EXEC SQL INCLUDE TABLE TEST3!

!------------------------------------------------------------------------------!

%%SET remTables(,TEST3)
%%SET remTabNos(,257)
%%SET cols257("COL10", "COL1", "COL2", "COL3", "COL4", "COL5", "COL6", "COL7", "COL8")
%%SET colLen257(2, 8, 1, 1, 8, 4, 16, 1, 8)
%%SET colNull257(0, 0, 0, 1, 0, 1, 1, 1, 1)
%%SET colTypes257("DBNUMBER", "STRING", "BITS", "BITS", "STRING", "NUMSTRING", "STRING", "SYMBOL", "PACKED NUMSTRING")
%%SET colSizes257(0, 15, 16, 16, 15, 7, 31, 1, 28)
%%SET bTrees257(2, 3, 4)
%%SET bTreeCols257_2(2, 3)
%%SET bTreeCols257_3(4)
%%SET bTreeCols257_4(6)
%%SET symCols257(8)
%%SET symVals257_8(FALSE, TRUE)
%%SET symLits257_8(0, 1)
%%SET multiNo257(5)


!******************************************************************************!
!END SQL!














!*****************************************************************************!
!*                                                                           *! 
!*             C U R S O R   D E C L A R A T I O N S                         *!
!*                                                                           *!
!*****************************************************************************! 
 



!BEGIN SQL DECLARE_CURSOR 3!
!******************************************************************************!

!EXEC SQL DECLARE EXTENSIVETABS CURSOR FOR
   SELECT TROWNO
   FROM TABLES
   WHERE NAME=`%PROTECTEDP:TABNAME!

!------------------------------------------------------------------------------!



!******************************************************************************!
!END SQL!
 
      

!BEGIN SQL DECLARE_CURSOR 5!
!******************************************************************************!

!EXEC SQL DECLARE FINDFK CURSOR FOR
   SELECT ORDNO, FBLKREF, FTABREF, KEYNO, COND 
   FROM FOREIGNKEYS
   WHERE  BLKREF = `%PROTECTEDP:TOWBLKREF AND 
       TABREF = `%PROTECTEDP:TOWTABREF
      AND  ORDNO = `%CREFERRINGFKORDNO!

!------------------------------------------------------------------------------!



!******************************************************************************!
!END SQL!

 

!BEGIN SQL DECLARE_CURSOR 3!
!******************************************************************************!

!EXEC SQL DECLARE FINDNEWTABLE CURSOR FOR
   SELECT TROWNO
   FROM TABLES
   WHERE TROWNO =< `%ZMAXNOFROWS!

!------------------------------------------------------------------------------!



!******************************************************************************!
!END SQL!



!BEGIN SQL DECLARE_CURSOR 3!
!******************************************************************************!

!EXEC SQL DECLARE FINDNEXTTABLE CURSOR FOR
   SELECT TROWNO
   FROM TABLES
   WHERE BLKREF = `%CBLOCK(`%CK)!

!------------------------------------------------------------------------------!



!******************************************************************************!
!END SQL!

         

!BEGIN SQL DECLARE_CURSOR 3!
!******************************************************************************!

!EXEC SQL DECLARE FINDORDNO CURSOR FOR
   SELECT ORDNO
   FROM FOREIGNKEYS
   WHERE TROWNO = `%PROTECTEDP:REFERREDTROWNO AND ORDNO =< `%ZMAXORDNO!

!------------------------------------------------------------------------------!



!******************************************************************************!
!END SQL!

         

!BEGIN SQL DECLARE_CURSOR 3!
!******************************************************************************!

!EXEC SQL DECLARE FINDTROWNO CURSOR FOR
   SELECT TROWNO
   FROM TABLES
   WHERE  NAME = `%PROTECTEDP:REFERREDTABNAME!

!------------------------------------------------------------------------------!



!******************************************************************************!
!END SQL!



!BEGIN SQL DECLARE_CURSOR 3!
!******************************************************************************!

!EXEC SQL DECLARE GETBLOCKANDTABREF CURSOR FOR
   SELECT BLKREF, TABREF
   FROM TABLES
   WHERE NAME = `%PROTECTEDP:TABNAME!

!------------------------------------------------------------------------------!



!******************************************************************************!
!END SQL!

         

!BEGIN SQL DECLARE_CURSOR 4!
!******************************************************************************!

!EXEC SQL DECLARE GETTROWNO CURSOR FOR
   SELECT TROWNO
   FROM TABLES
   WHERE BLKREF=`%PROTECTEDP:TOWBLKREF
   AND TABREF=`%PROTECTEDP:TOWTABREF!

!------------------------------------------------------------------------------!



!******************************************************************************!
!END SQL!

   
   
     
   

!BEGIN SQL COMMON 0!

%%PROCESS ("CCL")

%%SET protInitSize(100)
%%SET tempSizes(3, 3)
%%SET tempUse1("STR")
%%SET tempUse2("STR")
%%BEGIN(userProtection)

   VARIABLE BLKNUM 16 DS;
   VARIABLE BLKREF 16 DS;
   VARIABLE CONDITION 16 DS;
   VARIABLE COUNTER 16 DS;
   VARIABLE DELETEACTION 16 DS;            ! FOREIGN KEY DELETE ACTION        !
   VARIABLE FBLKREF 16 DS;                 ! BLOCK REFERENCE OF REFERRING TAB !
   VARIABLE FKNUMBER 16 DS;                ! FOREIGN KEY NUMBER               !
   VARIABLE FLDDATATYPE 16 DS;             ! DATA TYPE OF COLUMN VARIABLE     !
   VARIABLE FLDNUMBER 16 DS;               ! FIELD NUMBER                     !
   VARIABLE FLDPROTECTION 16 DS;           ! FIELD PROTECTION/VISIBILITY      !
   VARIABLE FLDSIZE 16 DS;                 ! FIELD SIZE                       !
   VARIABLE FROWNO 16 DS;                  ! ROWNUMBER IN FIELDS TABLE        !
   VARIABLE FTABREF 16 DS;                 ! TABLE REFERENCE OF REFERRING TAB !
   VARIABLE KEYNO 16 DS;                   ! ORDINAL KEY NUMBER               !
   VARIABLE LOCATION 16 DS;                ! TABLE LOCATION (SINGLE/MULTIPLE) !
   VARIABLE MAXSYMLENGTH 16 DS;            ! LONGEST SYMBOL VALUE NAME        !
   VARIABLE NAMELENGTH 8 DS;               ! LENGTH OF SYMBOL VALUE NAME      !
   VARIABLE NEXTTOBEDELETED 16 DS;         ! ROWNUMBER OF ROW TO BE DELETED   !
   VARIABLE ORDNO 16 DS;                   ! ORDINAL NUMBER                   !
   VARIABLE PRWIDTH 16 DS;                 ! PRINTOUT WIDTH OF COLUMN         !
   VARIABLE RAUTHCAT 16 DS;                ! TABLE READ AUTHORITY CATEGORY    !
   VARIABLE REF 16 DS;                     ! RETURN SIGNAL REFERENCE          !
   VARIABLE REFERREDTROWNO 16 DS;          ! TABLE ROW NUMBER OF REFERRED TAB !
   VARIABLE SAMENAME 16 DS;                ! ROWNUMBER OF TABLE WITH SAME NAME!
   VARIABLE SYMBOLVALUE 16 DS;             ! NUMERICAL SYMBOL VALUE           !
   VARIABLE TABREF 16 DS;
   VARIABLE TOWBLKREF 16 DS;               ! TABLE OWNER BLOCK REFERENCE      !
   VARIABLE TOWTABREF 16 DS;               ! TABLE OWNER TABLE REFERENCE      !
   VARIABLE TRANSID 16 DS;                 ! TRANSACTION IDENTITY             !
   VARIABLE TROWNO 16 DS;                  ! ROWNUMBER IN TABLES TABLE        !
   VARIABLE USERP 16 DS;                   ! USER'S POINTER                   !
   VARIABLE VOLATIL 16 DS;                 ! VARIABLE PROPERTY VOLATILE       !
   VARIABLE WAUTHCAT 16 DS;                ! TABLE WRITE AUTHORITY CATEGORY   !

   STRING VARIABLE FLDNAME 7 DS;           ! COLUMN NAME                      !
   STRING VARIABLE REFERREDTABNAME 15 DS;  ! NAME OF REFERRED TABLE           !
   STRING VARIABLE TABNAME 15 DS;          ! TABLE NAME                       !
                              
   SYMBOL VARIABLE SYMBOLFOUND=(FALSE, TRUE) DS;
                                            ! NEW SYMBOL VALUE NAME FOUND?     !
   
%%END(userProtection)

%%BEGIN(towSymbols)
NSYMB TABLESEAID = 10;
NSYMB WORKSAEID = 20;
STRING SLOG = ""test table no 1"";

%%END(towSymbols)

%%SET curNames(EXTENSIVETABS, FINDFK, FINDNEWTABLE, FINDNEXTTABLE, FINDORDNO, FINDTROWNO, GETBLOCKANDTABREF, GETTROWNO)
%%SET curLocal(1, 1, 1, 1, 1, 1, 1, 1)
%%SET curTabNos(1, 5, 1, 1, 5, 1, 1, 1)
%%SET curTabNames(TABLES, FOREIGNKEYS, TABLES, TABLES, FOREIGNKEYS, TABLES, TABLES, TABLES)

%%SET curBlockRefs("", "", "", "", "", "", "", "")

%%INCLUDE (towDeclarations)

%%INCLUDE (tuDeclarations)

!END SQL!
END DECLARE;

PROGRAM; PLEX;

!*****************************************************************************!
!*****************************************************************************!
!*****************************************************************************!
!*****************************************************************************!
!*                                                                           *! 
!*              D A T A   D I C T I O N A R Y   I N T E R F A C E            *!
!*                                                                           *!
!*****************************************************************************!
!*****************************************************************************!
!*****************************************************************************!
!*****************************************************************************!




!*****************************************************************************!
!*****************************************************************************!
!*****************************************************************************!
!*                                                                           *! 
!*              S I G N A L   E N T R I E S                                  *!
!*                                                                           *!
!*****************************************************************************!
!*****************************************************************************!
!*****************************************************************************!




!*****************************************************************************!
!*                                                                           *! 
!*             T R H S T A T R A N S R                                       *!
!*                                                                           *!
!*****************************************************************************!



   ENTER TRHSTATRANSR WITH
      PROTECTEDP,
      CMESSAGE,
      PROTECTEDP:SQL_SQLTID; 
      
   CASE CRETURNFROMTRHSTATRANSR IS
      WHEN SYMCLEARSOMETABS80 DO
         GOTO CLEARSOMETABS80;
         
      WHEN SYMCLEARALLTABS30 DO
         GOTO CLEARALLTABS30;
         
      WHEN SYMDDINITTABLE20 DO
         GOTO DDINITTABLE20;
         
      WHEN SYMDDINITFIELD20 DO
         GOTO DDINITFIELD20;
         
      WHEN SYMDDINITFK10 DO
         GOTO DDINITFK10;
         
      OTHERWISE DO;
   ESAC;
      






!*****************************************************************************!
!*                                                                           *! 
!*             T R H S T O P T R A N S R                                     *!
!*                                                                           *!
!*****************************************************************************!




! THIS ROUTINE ENTERS THE RETURN SIGNAL TO TRHSTOPTRANS. TRHSTOP- !
! TRANS MAY HAVE BEEN INITIATED BY EITHER DDFCSTA OR BLKREMST,    !
! AND CSIGNAL KNOWS WHICH ONE IT WAS.                             !

! INDATA:        CSIGNAL                                          !

! OUTDATA:       NONE                                             ! 

   ENTER TRHSTOPTRANSR;
   
   CASE CSIGNAL IS
      WHEN DDFCSTA DO
         SEND DDFCSTAR WITH
            CUSERP(ZDDFCSTA);
      WHEN BLKREMST DO
         SEND BLKREMSTRPY;
      OTHERWISE DO;
   ESAC;
   
   EXIT;               














!*****************************************************************************!
!*                                                                           *! 
!*             B L K R E M S T ,    D D F C S T A                            *!
!*                                                                           *!
!*****************************************************************************!




! THE OBJECTIVE OF THIS ROUTINE IS TO SEND THE SIGNAL TRHSTOP-    !
! TRANS, WHICH WILL STOP AND ROLL BACK ALL TRANSACTIONS THAT ARE  !
! CURRENTLY PERFORMED, AND WHICH WILL BLOCK RECEPTION OF NEW      !
! TRANSACTIONS. THE ROUTINE IS INITIATED EITHER BY RECEPTION OF   !
! THE SIGNAL DDFCSTA OR BY RECEPTION OF THE SIGNAL BLKREMST.      !

! INSIGNALS:         DDFCSTA OR BLKREMST                          !

! OUTSIGNAL:         TRHSTOPTRANS                                 !

! INDATA:            NONE                                         !

! OUTDATA:           CSIGNAL                                      !

  
   ENTER BLKREMST WITH
      +,
      +;
      
   CSIGNAL=BLKREMST;
   SEND TRHSTOPTRANS;
   EXIT;
   
   
   ENTER DDFCSTA WITH
      CUSERP(ZDDFCSTA),
      +,
      +;
      
   CSIGNAL=DDFCSTA;
   SEND TRHSTOPTRANS;
   EXIT;



   
   
      

!*****************************************************************************!
!*                                                                           *! 
!*             D D I N I T F I E L D                                         *!
!*                                                                           *!
!*****************************************************************************!




! A TABLE OWNER ASKS DD TO INITIATE A SPECIFIC FIELD I.E. TO      !
! INSERT THE FIELD DEFINITION IN THE FIELDS TABLE. DDINTERFACE    !
! RECEIVES THE SIGNAL DDINITFIELD, CALCULATES THE PRINTOUT WIDTH  !
! AS THE MAXIMUM WIDTH OF THE FIELD NAME AND THE FIELD VALUE,     !
! ASKS THE TABLES TABLE FOR THE CURRENT ROW NUMBER IN TABLES AND  !
! FORWARDS THE INFORMATION TO SYSTEMTABLES BY SENDING THE SIGNAL  !
! SYSINITFLD. !

! INDATA:        NONE                                             !

! OUTDATA:       NONE                                             !


   ENTER DDINITFIELD WITH
      TUSERP,
      TTOWBLKREF,
      TTOWTABREF,
      CFLDNAME,
      TFLDNUMBER,
      TFLDPROTECTION,
      TFLDDATATYPE,
      TFLDSIZE,
      TVOLATILE;
   
   
!BEGIN SQL BEGIN 0!
!******************************************************************************!

!EXEC SQL BEGIN PROTECTED REGION!

!------------------------------------------------------------------------------!

%%INCLUDE (beginStat)


!******************************************************************************!
!END SQL!


   
   PROTECTEDP:REF=TTOWBLKREF;
   PROTECTEDP:TOWBLKREF=TTOWBLKREF;
   PROTECTEDP:USERP=TUSERP;
   PROTECTEDP:TOWTABREF=TTOWTABREF;
   PROTECTEDP:FLDNAME=CFLDNAME;
   PROTECTEDP:FLDNUMBER=TFLDNUMBER;
   PROTECTEDP:FLDPROTECTION=TFLDPROTECTION;
   PROTECTEDP:FLDDATATYPE=TFLDDATATYPE;
   PROTECTEDP:FLDSIZE=TFLDSIZE;
   PROTECTEDP:VOLATIL=TVOLATILE;
   
   

   CHAR VX:CFLDNAME(N:0) TO VT:TNAMELENGTH;
   PROTECTEDP:NAMELENGTH=TNAMELENGTH;

   CASE PROTECTEDP:FLDDATATYPE IS
      WHEN ZBITS DO  
         CASE PROTECTEDP:FLDSIZE IS
            WHEN 1,2 DO
               PROTECTEDP:PRWIDTH=PROTECTEDP:NAMELENGTH;
            WHEN 4 DO
               IF PROTECTEDP:NAMELENGTH > 2 THEN
                  PROTECTEDP:PRWIDTH=PROTECTEDP:NAMELENGTH;
               ELSE
                  PROTECTEDP:PRWIDTH=2;
               FI; 
            WHEN 8 DO
               IF PROTECTEDP:NAMELENGTH > 3 THEN
                  PROTECTEDP:PRWIDTH=PROTECTEDP:NAMELENGTH;
               ELSE
                  PROTECTEDP:PRWIDTH=3;
               FI;
            WHEN 16 DO
               IF PROTECTEDP:NAMELENGTH > 5 THEN
                  PROTECTEDP:PRWIDTH=PROTECTEDP:NAMELENGTH;
               ELSE
                  PROTECTEDP:PRWIDTH=5;
               FI; 
            OTHERWISE DO;         
         ESAC;
   
      WHEN ZSTR, ZNUMSTR DO 
         CASE PROTECTEDP:FLDSIZE IS
            WHEN 1 DO
               PROTECTEDP:PRWIDTH=PROTECTEDP:NAMELENGTH;
            WHEN 3 DO
               IF PROTECTEDP:NAMELENGTH > 3 THEN 
                  PROTECTEDP:PRWIDTH=PROTECTEDP:NAMELENGTH;
               ELSE
                  PROTECTEDP:PRWIDTH=3;
               FI;
            OTHERWISE DO
               PROTECTEDP:PRWIDTH = PROTECTEDP:FLDSIZE;
         ESAC;
   
      WHEN ZPACKEDNUMSTR DO 
         PROTECTEDP:PRWIDTH=PROTECTEDP:FLDSIZE;
   
      WHEN ZSYMBOL DO 
         CRETURNFROMCHECKSYMVALNAMELENGTH = SYMDDINITFIELD10;
         GOTO CHECKSYMVALNAMELENGTH;         
                         
   
      WHEN ZROWNUMBER DO
         CASE PROTECTEDP:FLDSIZE IS
            WHEN 16 DO
               IF PROTECTEDP:NAMELENGTH > 5 THEN  
                  PROTECTEDP:PRWIDTH=PROTECTEDP:NAMELENGTH;
               ELSE
                  PROTECTEDP:PRWIDTH=5;
               FI;
            WHEN 20 DO                  ! ROWNUMBER WILL BE EXPANDED !
               PROTECTEDP:PRWIDTH=7;    ! TO 20 BITS IN THE FUTURE   !
            OTHERWISE DO;
         ESAC; 
   
      WHEN ZDBNUMBER DO
         PROTECTEDP:PRWIDTH=10;         ! THE PRINTOUT WIDTH IS !
      OTHERWISE DO;
   ESAC;                                ! DETERMINED !

DDINITFIELD10)
              

   
!BEGIN SQL OPEN_CURSOR 0!
!******************************************************************************!

!EXEC SQL OPEN GETTROWNO!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(4)
%%SET keyExprs("TOWBLKREF")
%%SET keyPtrs("PROTECTEDP")
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(8)
%%INCLUDE (locOpenStat)


!******************************************************************************!
!END SQL!

   
!BEGIN SQL FETCH 0!
!******************************************************************************!

!EXEC SQL FETCH GETTROWNO INTO `%PROTECTEDP:TROWNO!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(4)
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(8)
%%SET cols(0)
%%SET vars("TROWNO")
%%SET ptrs("PROTECTEDP")
%%SET nulls("")
%%SET nullPtrs("")
%%SET preds(1)
%%SET scanPred1("", "SQLC_TABLES_TABREF_Data", "", "SQLM_TABLES_OperRow", "TOWTABREF", "", "PROTECTEDP", "=", "True", "False", "False")
%%SET scanCols1(4)
%%SET scanNulls1()
%%SET scanNullPtrs1()
%%INCLUDE (locFetchStat)


!******************************************************************************!
!END SQL!

   
!BEGIN SQL CLOSE_CURSOR 0!
!******************************************************************************!

!EXEC SQL CLOSE GETTROWNO!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET curNo(8)
%%INCLUDE (locCloseStat)


!******************************************************************************!
!END SQL!

   !$EXEC SQL CONTINUE$!






     
! THIS ROUTINE ENTERS THE SIGNAL SYSINITFLD FROM THE DD INTERFACE !
! MODULE. THE OBJECTIVE IS TO INSERT A NEW ROW INTO THE FIELDS    !
! TABLE, AND THUS TO DEFINE A NEW USER FIELD. THE ROUTINE WILL    !
! SEND THE SIGNAL SYSINITFLDR TO DD INTERFACE AS AN ACKNOW-       !
! LEGDEMENT ONCE ALL ACTION IS TAKEN.                             !

! IF IT TURNS OUT THAT THE FIELDS TABLE IS FULL WHEN THE INSERT IS!
! ATTEMPTED, THE SIGNAL PROGERROR WILL BE SENT. THIS SIGNAL WILL  !
! CAUSE A NEW RESTART, MAKING THE OLD SYSTEM EXECUTIVE.           !

! INDATA:       CNEXTFROWNO          NEXT AVAILABLE PRIMARY KEY  !

! OUTDATA:      CNEXTFROWNO          NEXT AVAILABLE PRIMARY KEY  !                

 
                      




   PROTECTEDP:FROWNO=CNEXTFROWNO;
   CNEXTFROWNO=CNEXTFROWNO+1;
   

                


   CRETURNFROMTRHSTATRANSR = SYMDDINITFIELD20;        
   SEND TRHSTATRANS WITH
      PROTECTEDP,            ! OWN POINTER !
      COWNREF,
      ZDONOTLOG,
      +;     
   EXIT;

DDINITFIELD20)

   
!BEGIN SQL INSERT 27!
!******************************************************************************!

!EXEC SQL INSERT INTO FIELDS
     (FROWNO,
      NAME,
      TABREF,
      BLKREF,
      FIELDNO,
      VISIBIL,
      PRWIDTH,
      NULLPER,
      DATATYP,
      BADDRES,
      SIZE,
      VOLATIL,
      TROWNO)
   VALUES
     (`%PROTECTEDP:FROWNO,
      `%PROTECTEDP:FLDNAME,
      `%PROTECTEDP:TOWTABREF,
      `%PROTECTEDP:TOWBLKREF,
      `%PROTECTEDP:FLDNUMBER,
      `%PROTECTEDP:FLDPROTECTION,
      `%PROTECTEDP:PRWIDTH,
      TRUE,
      `%PROTECTEDP:FLDDATATYPE,
      1,
      `%PROTECTEDP:FLDSIZE,
      `%PROTECTEDP:VOLATIL,
      `%PROTECTEDP:TROWNO)!

!------------------------------------------------------------------------------!

%%SET tabNo(2)
%%SET tabName(FIELDS)
%%SET keyNo(2)
%%SET keyExprs("FROWNO")
%%SET keyPtrs("PROTECTEDP")
%%SET keyPrefix(1)
%%SET sigCount(1)
%%SET sigAssVars0()
%%SET sigAssVars1()
%%SET sigAssPtrs0()
%%SET sigAssPtrs1()
%%SET sigAssExprs0()
%%SET sigAssExprs1()
%%SET sigCols0(2, 3, 4, 5, 7)
%%SET sigCols1(8, 9, 10, 11, 14, 21, 27)
%%SET sigExprs0("FLDNAME", "TOWTABREF", "TOWBLKREF", "FLDNUMBER", "FLDPROTECTION")
%%SET sigExprs1("PRWIDTH", "0", "FLDDATATYPE", "1", "FLDSIZE", "VOLATIL", "TROWNO")
%%SET sigPtrs0("PROTECTEDP", "PROTECTEDP", "PROTECTEDP", "PROTECTEDP", "PROTECTEDP")
%%SET sigPtrs1("PROTECTEDP", "", "PROTECTEDP", "", "PROTECTEDP", "PROTECTEDP", "PROTECTEDP")
%%SET sigNulls0("", "", "", "", "")
%%SET sigNulls1("", "", "", "", "", "", "")
%%SET sigNullPtrs0("", "", "", "", "")
%%SET sigNullPtrs1("", "", "", "", "", "", "")
%%INCLUDE (insertStat)


!******************************************************************************!
!END SQL!

   
!BEGIN SQL COMMIT 0!
!******************************************************************************!

!EXEC SQL COMMIT TRANSACTION!

!------------------------------------------------------------------------------!

%%INCLUDE (commitStat)


!******************************************************************************!
!END SQL!
      


   CASE SQLCODE.VALUE IS
      WHEN ZROWINSERTED DO;
      
      WHEN ZSEARCHFAIL DO
         IF SQLCODE.SUBCODE = ZROWNOTALLOCATED THEN
            
!BEGIN SQL SELECT 3!
!******************************************************************************!

!EXEC SQL SELECT TABREF, SAEIDT
               INTO `%TTABREF, `%TSAEID
               FROM TABLES
               WHERE NAME = `%ZFIELDS AND BLKREF = `%COWNREF!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(3)
%%SET keyExprs("ZFIELDS", "COWNREF")
%%SET keyPtrs("", "")
%%SET keyPrefix(2)
%%SET cols(4, 6)
%%SET vars("TTABREF", "TSAEID")
%%SET ptrs("", "")
%%SET nulls("", "")
%%SET nullPtrs("", "")
%%INCLUDE (locSelectStat)


!******************************************************************************!
!END SQL!

                  
            SEND PROGERROR WITH
               ZPROGERRORCODE1,
               COWNREF,
               TTABREF,
               TSAEID;
            EXIT;
         FI;
         
      WHEN ZERROR DO
         CASE SQLCODE.SUBCODE IS
            WHEN ZTABFULL DO
               
!BEGIN SQL SELECT 3!
!******************************************************************************!

!EXEC SQL SELECT TABREF, SAEIDT
                  INTO `%TTABREF, `%TSAEID
                  FROM TABLES
                  WHERE NAME = `%ZFIELDS AND BLKREF = `%COWNREF!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(3)
%%SET keyExprs("ZFIELDS", "COWNREF")
%%SET keyPtrs("", "")
%%SET keyPrefix(2)
%%SET cols(4, 6)
%%SET vars("TTABREF", "TSAEID")
%%SET ptrs("", "")
%%SET nulls("", "")
%%SET nullPtrs("", "")
%%INCLUDE (locSelectStat)


!******************************************************************************!
!END SQL!

                  
               SEND PROGERROR WITH
                  ZPROGERRORCODE1,
                  COWNREF,
                  TTABREF,
                  TSAEID;
               EXIT;
               
            WHEN ZTRHCONG DO
               SEND PROGERROR WITH
                  ZPROGERRORCODE4,
                  ZTRHSAEID2;
               EXIT;

            OTHERWISE DO;
         ESAC;
         
      OTHERWISE DO;
   ESAC;
   
   SEND DDINITFIELDR REFERENCE PROTECTEDP:REF WITH
      PROTECTEDP:USERP;
   

   
!BEGIN SQL END 0!
!******************************************************************************!

!EXEC SQL END PROTECTED REGION!

!------------------------------------------------------------------------------!

%%INCLUDE (endStat)


!******************************************************************************!
!END SQL!

   EXIT;

         

                  
       










      

!*****************************************************************************!
!*                                                                           *! 
!*             D D I N I T F K                                               *!
!*                                                                           *!
!*****************************************************************************!




! A TABLE OWNER ASKS DD TO INITIATE A SPECIFIC FOREIGN KEY I.E.   !
! TO INSERT THE FOREIGN KEY DEFINITION IN THE FOREIGNKEYS TABLE.  !
! DDINTERFACE RECEIVES THE SIGNAL DDINITFK, TRANSLATES THE TABLE  !
! NAME OF THE REFERRED TABLE TO ITS ROWNUMBER IN THE TABLES TABLE !
! AND FORWARDS THE INFORMATION TO SYSTEMTABLES BY SENDING THE     !
! SIGNAL SYSINITFK.                                               !

! IF THE REFERRED TABLE IS NOT DEFINED IN THE TABLES TABLE, THE   !
! SIGNAL PROGERROR IS SENT. THIS SIGNAL WILL INITIATE A NEW       !
! RESTART, WHICH IMPLIES THAT THE OLD SYSTEM WILL BECOME          !
! EXECUTIVE.                                                      !

! INDATA:        NONE                                             !

! OUTDATA:       NONE                                             !


ENTER DDINITFK WITH
   TUSERP,
   TTOWBLKREF,
   TTOWTABREF,
   TFKNUMBER,
   CREFERREDTABNAME,
   TDELETEACTION;


!BEGIN SQL BEGIN 0!
!******************************************************************************!

!EXEC SQL BEGIN PROTECTED REGION!

!------------------------------------------------------------------------------!

%%INCLUDE (beginStat)


!******************************************************************************!
!END SQL!


PROTECTEDP:USERP=TUSERP;
PROTECTEDP:REF=TTOWBLKREF;
PROTECTEDP:TOWBLKREF=TTOWBLKREF;  
PROTECTEDP:TOWTABREF=TTOWTABREF;
PROTECTEDP:FKNUMBER=TFKNUMBER;
PROTECTEDP:REFERREDTABNAME=CREFERREDTABNAME;
PROTECTEDP:DELETEACTION=TDELETEACTION;
      

   
!BEGIN SQL OPEN_CURSOR 0!
!******************************************************************************!

!EXEC SQL OPEN FINDTROWNO!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(3)
%%SET keyExprs("REFERREDTABNAME")
%%SET keyPtrs("PROTECTEDP")
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(6)
%%INCLUDE (locOpenStat)


!******************************************************************************!
!END SQL!

   
!BEGIN SQL FETCH 0!
!******************************************************************************!

!EXEC SQL FETCH FINDTROWNO INTO `%PROTECTEDP:REFERREDTROWNO!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(3)
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(6)
%%SET cols(0)
%%SET vars("REFERREDTROWNO")
%%SET ptrs("PROTECTEDP")
%%SET nulls("")
%%SET nullPtrs("")
%%SET preds(0)
%%INCLUDE (locFetchStat)


!******************************************************************************!
!END SQL!

   !$EXEC SQL CONTINUE$!
   CASE SQLCODE.VALUE IS
      WHEN ZOK DO;
      WHEN ZSEARCHFAIL DO

         SEND PROGERROR WITH
            ZPROGERRORCODE3,
            PROTECTEDP:TOWBLKREF,
            PROTECTEDP:TOWTABREF;
         EXIT;
      OTHERWISE DO;                  ! DISCUSSIONS NEEDED !
   ESAC;                                
            
   
!BEGIN SQL CLOSE_CURSOR 0!
!******************************************************************************!

!EXEC SQL CLOSE FINDTROWNO!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET curNo(6)
%%INCLUDE (locCloseStat)


!******************************************************************************!
!END SQL!
       
                  
   
!BEGIN SQL OPEN_CURSOR 0!
!******************************************************************************!

!EXEC SQL OPEN GETTROWNO!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(4)
%%SET keyExprs("TOWBLKREF")
%%SET keyPtrs("PROTECTEDP")
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(8)
%%INCLUDE (locOpenStat)


!******************************************************************************!
!END SQL!

   
!BEGIN SQL FETCH 0!
!******************************************************************************!

!EXEC SQL FETCH GETTROWNO INTO `%PROTECTEDP:TROWNO!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(4)
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(8)
%%SET cols(0)
%%SET vars("TROWNO")
%%SET ptrs("PROTECTEDP")
%%SET nulls("")
%%SET nullPtrs("")
%%SET preds(1)
%%SET scanPred1("", "SQLC_TABLES_TABREF_Data", "", "SQLM_TABLES_OperRow", "TOWTABREF", "", "PROTECTEDP", "=", "True", "False", "False")
%%SET scanCols1(4)
%%SET scanNulls1()
%%SET scanNullPtrs1()
%%INCLUDE (locFetchStat)


!******************************************************************************!
!END SQL!

   
!BEGIN SQL CLOSE_CURSOR 0!
!******************************************************************************!

!EXEC SQL CLOSE GETTROWNO!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET curNo(8)
%%INCLUDE (locCloseStat)


!******************************************************************************!
!END SQL!

   !$EXEC SQL CONTINUE$!
            

   
! THIS ROUTINE ENTERS THE SIGNAL SYSINITFK FROM THE DD INTERFACE  !
! MODULE. THE OBJECTIVE IS TO INSERT A NEW ROW IN THE FOREIGNKEYS !
! TABLE, AND THUS DEFINE A NEW FOREIGN KEY RELATIONSHIP. THE ROU- !
! TINE WILL FIND THE NEXT AVAILABLE                               !
! ORDINAL NUMBER OF THE FOREIGN KEY AMONG THE FOREIGN KEYS THAT   !
! REFER TO THE REFERRED TABLE BY USING THE CURSOR FINDORDNO. ONCE !
! ALL DATA IS INSERTED INTO FOREIGNKEY, THE SIGNAL SYSINITFKR     !
! WILL BE SENT AS AN ACKNOWLEDGEMENT TO THE DD INTERFACE MODULE.  !

! IF THE INSERT FAILS BECASE THE FOREIGNKEYS TABLE IS UNDER-      !
! DIMENSIONED, THE SIGNAL PROGERROR WILL BE SENT. THIS SIGNAL     !
! WILL INITIATE A RESTART, WHICH IMPLIES THAT THE OLD SYSTEM WILL !
! BECOME EXECUTIVE.                                               !

      
   
   

   
!BEGIN SQL OPEN_CURSOR 0!
!******************************************************************************!

!EXEC SQL OPEN FINDORDNO!

!------------------------------------------------------------------------------!

%%SET tabNo(5)
%%SET tabName(FOREIGNKEYS)
%%SET keyNo(4)
%%SET keyExprs("REFERREDTROWNO")
%%SET keyPtrs("PROTECTEDP")
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(5)
%%INCLUDE (locOpenStat)


!******************************************************************************!
!END SQL!

   
!BEGIN SQL FETCH 0!
!******************************************************************************!

!EXEC SQL FETCH FINDORDNO INTO `%PROTECTEDP:ORDNO !

!------------------------------------------------------------------------------!

%%SET tabNo(5)
%%SET tabName(FOREIGNKEYS)
%%SET keyNo(4)
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(5)
%%SET cols(3)
%%SET vars("ORDNO")
%%SET ptrs("PROTECTEDP")
%%SET nulls("")
%%SET nullPtrs("")
%%SET preds(1)
%%SET scanPred1("", "SQLC_FOREIGNKEYS_ORDNO_Data", "", "SQLM_FOREIGNKEYS_OperRow", "ZMAXORDNO", "", "", "=<", "True", "False", "False")
%%SET scanCols1(3)
%%SET scanNulls1()
%%SET scanNullPtrs1()
%%INCLUDE (locFetchStat)


!******************************************************************************!
!END SQL!

   !$EXEC SQL CONTINUE$!
   
   CASE SQLCODE.VALUE IS
      WHEN ZOK DO
         PROTECTEDP:ORDNO=PROTECTEDP:ORDNO+1;
      WHEN ZSEARCHFAIL DO
         PROTECTEDP:ORDNO=ZFIRSTORDNO;
      OTHERWISE DO;
   ESAC;      
  
   
!BEGIN SQL CLOSE_CURSOR 0!
!******************************************************************************!

!EXEC SQL CLOSE FINDORDNO!

!------------------------------------------------------------------------------!

%%SET tabNo(5)
%%SET tabName(FOREIGNKEYS)
%%SET curNo(5)
%%INCLUDE (locCloseStat)


!******************************************************************************!
!END SQL!

   
   
!BEGIN SQL SELECT 3!
!******************************************************************************!

!EXEC SQL SELECT BLKREF, TABREF
      INTO `%PROTECTEDP:TOWBLKREF, `%PROTECTEDP:TOWTABREF
      FROM TABLES
      WHERE TROWNO = `%PROTECTEDP:REFERREDTROWNO!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(0)
%%SET keyExprs("REFERREDTROWNO")
%%SET keyPtrs("PROTECTEDP")
%%SET keyPrefix(1)
%%SET cols(3, 4)
%%SET vars("TOWBLKREF", "TOWTABREF")
%%SET ptrs("PROTECTEDP", "PROTECTEDP")
%%SET nulls("", "")
%%SET nullPtrs("", "")
%%INCLUDE (locSelectStat)


!******************************************************************************!
!END SQL!



   CRETURNFROMTRHSTATRANSR = SYMDDINITFK10;        
   SEND TRHSTATRANS WITH
      PROTECTEDP, 
      COWNREF,
      ZDONOTLOG,
      +;     
   EXIT;

DDINITFK10)

   
   
!BEGIN SQL INSERT 19!
!******************************************************************************!

!EXEC SQL INSERT INTO FOREIGNKEYS
     (TROWNO,
      ORDNO,
      BLKREF,
      TABREF,
      KEYNO,
      FTROWNO,
      FTABREF,
      FBLKREF,
      COND)
   VALUES
     (`%PROTECTEDP:REFERREDTROWNO,
      `%PROTECTEDP:ORDNO,
      `%PROTECTEDP:BLKREF,
      `%PROTECTEDP:TABREF,
      `%PROTECTEDP:FKNUMBER,
      `%PROTECTEDP:TROWNO,
      1,
      1,
      `%PROTECTEDP:DELETEACTION)!

!------------------------------------------------------------------------------!

%%SET tabNo(5)
%%SET tabName(FOREIGNKEYS)
%%SET keyNo(2)
%%SET keyExprs("REFERREDTROWNO", "ORDNO")
%%SET keyPtrs("PROTECTEDP", "PROTECTEDP")
%%SET keyPrefix(2)
%%SET sigCount(0)
%%SET sigAssVars0()
%%SET sigAssPtrs0()
%%SET sigAssExprs0()
%%SET sigCols0(4, 5, 6, 7, 8, 9, 10)
%%SET sigExprs0("BLKREF", "TABREF", "FKNUMBER", "TROWNO", "1", "1", "DELETEACTION")
%%SET sigPtrs0("PROTECTEDP", "PROTECTEDP", "PROTECTEDP", "PROTECTEDP", "", "", "PROTECTEDP")
%%SET sigNulls0("", "", "", "", "", "", "")
%%SET sigNullPtrs0("", "", "", "", "", "", "")
%%INCLUDE (insertStat)


!******************************************************************************!
!END SQL!
            
   
!BEGIN SQL COMMIT 0!
!******************************************************************************!

!EXEC SQL COMMIT TRANSACTION!

!------------------------------------------------------------------------------!

%%INCLUDE (commitStat)


!******************************************************************************!
!END SQL!
 


   CASE SQLCODE.VALUE IS
      WHEN ZROWINSERTED DO;
      
      WHEN ZSEARCHFAIL DO
         IF SQLCODE.SUBCODE = ZROWNOTALLOCATED THEN
            
!BEGIN SQL SELECT 3!
!******************************************************************************!

!EXEC SQL SELECT TABREF, SAEIDT
               INTO `%TTABREF, `%TSAEID
               FROM TABLES
               WHERE NAME = `%ZFOREIGNKEYS AND BLKREF = `%COWNREF!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(3)
%%SET keyExprs("ZFOREIGNKEYS", "COWNREF")
%%SET keyPtrs("", "")
%%SET keyPrefix(2)
%%SET cols(4, 6)
%%SET vars("TTABREF", "TSAEID")
%%SET ptrs("", "")
%%SET nulls("", "")
%%SET nullPtrs("", "")
%%INCLUDE (locSelectStat)


!******************************************************************************!
!END SQL!

                  
            SEND PROGERROR WITH
               ZPROGERRORCODE1,
               COWNREF,
               TTABREF,
               TSAEID;
            EXIT;
         FI;
         
      WHEN ZERROR DO
         CASE SQLCODE.SUBCODE IS
            WHEN ZTABFULL DO
               
!BEGIN SQL SELECT 3!
!******************************************************************************!

!EXEC SQL SELECT TABREF, SAEIDT
                  INTO `%TTABREF, `%TSAEID
                  FROM TABLES
                  WHERE NAME = `%ZFOREIGNKEYS AND BLKREF = `%COWNREF!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(3)
%%SET keyExprs("ZFOREIGNKEYS", "COWNREF")
%%SET keyPtrs("", "")
%%SET keyPrefix(2)
%%SET cols(4, 6)
%%SET vars("TTABREF", "TSAEID")
%%SET ptrs("", "")
%%SET nulls("", "")
%%SET nullPtrs("", "")
%%INCLUDE (locSelectStat)


!******************************************************************************!
!END SQL!

                  
               SEND PROGERROR WITH
                  ZPROGERRORCODE1,
                  COWNREF,
                  TTABREF,
                  TSAEID;
               EXIT;
               
            WHEN ZTRHCONG DO
               SEND PROGERROR WITH
                  ZPROGERRORCODE4,
                  ZTRHSAEID2;
               EXIT;

            OTHERWISE DO;
         ESAC;
         
      OTHERWISE DO;
   ESAC;

   
SEND DDINITFKR REFERENCE PROTECTEDP:REF WITH
   PROTECTEDP:USERP;
   

!BEGIN SQL END 0!
!******************************************************************************!

!EXEC SQL END PROTECTED REGION!

!------------------------------------------------------------------------------!

%%INCLUDE (endStat)


!******************************************************************************!
!END SQL!


EXIT;










!*****************************************************************************!
!*                                                                           *! 
!*             D D I N I T T A B L E                                         *!
!*                                                                           *!
!*****************************************************************************!




! A TABLE OWNER ASKS DD TO INITIATE A SPECIFIC TABLE I.E. TO      !
! INSERT THE TABLE DEFINITION IN THE TABLES TABLE. DDINTERFACE    !
! RECEIVES THE SIGNAL DDINITTABLE, STORES THE DATA IN THE         !
! PROTECTION FILE, AND SIMPLY FORWARDS THE PROTECTEDP POINTER TO   !
! SYSTEMTABLES BY SENDING THE SIGNAL SYSINITTAB.                  !

! INDATA:           NONE                                          !

! OUTDATA:          NONE                                          !


ENTER DDINITTABLE WITH
   TUSERP,
   TTOWBLKREF,
   TTOWTABREF,
   CTABNAME,
   TREADAUTHCAT,
   TWRITEAUTHCAT,
   TLOCATION;


!BEGIN SQL BEGIN 0!
!******************************************************************************!

!EXEC SQL BEGIN PROTECTED REGION!

!------------------------------------------------------------------------------!

%%INCLUDE (beginStat)


!******************************************************************************!
!END SQL!


PROTECTEDP:USERP=TUSERP;
PROTECTEDP:REF=TTOWBLKREF;
PROTECTEDP:TOWBLKREF=TTOWBLKREF;
PROTECTEDP:TOWTABREF=TTOWTABREF;
PROTECTEDP:TABNAME=CTABNAME;
PROTECTEDP:RAUTHCAT=TREADAUTHCAT;
PROTECTEDP:WAUTHCAT=TWRITEAUTHCAT;
PROTECTEDP:LOCATION=TLOCATION;


! THIS ROUTINE RECEIVES THE SIGNAL SYSINITTAB FROM THE DD INTER-  !
! FACE MODULE. THE OBJECTIVE IS TO INSERT A NEW ROW INTO THE      !
! TABLES TABLE, AND THUS TO DEFINE A NEW USER TABLE. HOWEVER      !
! PROBLEMS MAY ARISE AND THE SIGNAL PROGERROR MAY BE SENT IN THE  !
! FOLLOWING SITUATIONS:                                           !
! A. THE NAME OF THE TABLE WHICH REQUESTS TO BE DEFINED MAY       !
!    ALREADY BE OCCUPIED. IF THE LOCATION OF THE TABLE IS SINGLE, !
!    THE NAME MAY NOT OCCUR IN ANY OTHER BLOCK. IF THE LOCATION   !
!    OF THE TABLE IS MULTIPLE, A TABLE WITH THE SAME NAME MAY NOT !
!    APPEAR IN THE SAME BLOCK. HOWEVER, SUCH A FAULT WILL NOT     !
!    PASS THE PLEX-SQL PREPROCESSOR, AND THEREFORE NO CHECKS ARE  !
!    MADE ON MULTIPLE TABLES.                                     !
! B. IF THE ENTIRE ALLOCATED SIZE OF THE TABLE ALREADY IS USED,   !
!    THAT IS, THE TABLES TABLE IS ALREADY FULL, THE NEW TABLE     !
!    DEFINITION WILL NOT BE INCLUDED AND PROGERROR WILL BE SENT.  !
! THE SIGNAL PROGERROR WILL, IF IT IS SENT, CAUSE A RESTART,      !
! WHICH IMPLIES THAT THE OLD SYSTEM WILL BECOME EXECUTIVE.        ! 


! THE ROUTINE WILL ALWAYS END BY RETURNING THE SIGNAL SYSINITTABR !
! TO THE DD INTERFACE MODULE.                                     !

! INDATA:       CNEXTTROWNO          NEXT AVAILABLE ROWNUMBER IN !
!                                    TABLES.                     !

! OUTDATA:      CNEXTTROWNO          NEXT AVAILABLE ROWNUMBER IN !
!                                    TABLES (UPDATED).           !

! NORMAL ACTION: INSERT INDATA INTO THE TABLES TABLE.             !

! ALTERNATIVE ACTION: CAUSE A NEW RESTART BY SENDING PROGERROR.   !







   PROTECTEDP:TROWNO=CNEXTTROWNO;
   CNEXTTROWNO=CNEXTTROWNO+1;
      
          
   IF PROTECTEDP:LOCATION = TABLESLOCATEMULTI THEN      
      GOTO DDINITTABLE10;
   FI;
 
 
   
                                            ! BEGIN CHECK OF CASE A  !

   
!BEGIN SQL OPEN_CURSOR 0!
!******************************************************************************!

!EXEC SQL OPEN EXTENSIVETABS!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(3)
%%SET keyExprs("TABNAME")
%%SET keyPtrs("PROTECTEDP")
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(1)
%%INCLUDE (locOpenStat)


!******************************************************************************!
!END SQL!

   
!BEGIN SQL FETCH 0!
!******************************************************************************!

!EXEC SQL FETCH EXTENSIVETABS INTO `%PROTECTEDP:SAMENAME!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(3)
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(1)
%%SET cols(0)
%%SET vars("SAMENAME")
%%SET ptrs("PROTECTEDP")
%%SET nulls("")
%%SET nullPtrs("")
%%SET preds(0)
%%INCLUDE (locFetchStat)


!******************************************************************************!
!END SQL!

   !$EXEC SQL CONTINUE$!   
      
   CASE SQLCODE.VALUE IS
      WHEN ZNAMEALREADYEXISTS DO
            
!BEGIN SQL SELECT 3!
!******************************************************************************!

!EXEC SQL SELECT BLKREF
               INTO `%TBLKREF
               FROM TABLES
               WHERE TROWNO = `%PROTECTEDP.SAMENAME!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(0)
%%SET keyExprs("PROTECTEDP.SAMENAME")
%%SET keyPtrs("")
%%SET keyPrefix(1)
%%SET cols(3)
%%SET vars("TBLKREF")
%%SET ptrs("")
%%SET nulls("")
%%SET nullPtrs("")
%%INCLUDE (locSelectStat)


!******************************************************************************!
!END SQL!

            
            SEND PROGERROR WITH
               ZPROGERRORCODE2,
               PROTECTEDP:TOWBLKREF,
               PROTECTEDP:TOWTABREF,
               TBLKREF;
               
            EXIT;
            
      WHEN ZSEARCHFAIL DO;
      
      OTHERWISE DO;
   ESAC;
  
   
!BEGIN SQL CLOSE_CURSOR 0!
!******************************************************************************!

!EXEC SQL CLOSE EXTENSIVETABS!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET curNo(1)
%%INCLUDE (locCloseStat)


!******************************************************************************!
!END SQL!

                                         ! END CHECK OF CASE A    !







DDINITTABLE10)
                                
   CRETURNFROMTRHSTATRANSR = SYMDDINITTABLE20;        
   SEND TRHSTATRANS WITH
      PROTECTEDP,            ! OWN POINTER !
      COWNREF,
      ZDONOTLOG,
      +;     
   EXIT;

DDINITTABLE20)

   
!BEGIN SQL INSERT 25!
!******************************************************************************!

!EXEC SQL INSERT INTO TABLES
        (TROWNO,
         BLKREF,
         TABREF,
         NAME,
         ALLOCST,
         USEDST,
	 ALLOCSW,
	 USEDSW,
         RAUCAT,
         WAUCAT,
         LOCATE,
	 NOFLTCO)
      VALUES   
        (`%PROTECTEDP:TROWNO,
         `%PROTECTEDP:TOWBLKREF,
         `%PROTECTEDP:TOWTABREF,
         `%PROTECTEDP:TABNAME,
	 1,
	 1,
	 1,
	 1,
         `%PROTECTEDP:RAUTHCAT,
         `%PROTECTEDP:WAUTHCAT,
         `%PROTECTEDP:LOCATION,
	 1)!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(2)
%%SET keyExprs("TROWNO")
%%SET keyPtrs("PROTECTEDP")
%%SET keyPrefix(1)
%%SET sigCount(1)
%%SET sigAssVars0()
%%SET sigAssVars1()
%%SET sigAssPtrs0()
%%SET sigAssPtrs1()
%%SET sigAssExprs0()
%%SET sigAssExprs1()
%%SET sigCols0(2, 3, 4)
%%SET sigCols1(9, 10, 14, 15, 17, 18, 19, 20)
%%SET sigExprs0("TABNAME", "TOWBLKREF", "TOWTABREF")
%%SET sigExprs1("1", "1", "1", "1", "RAUTHCAT", "WAUTHCAT", "LOCATION", "1")
%%SET sigPtrs0("PROTECTEDP", "PROTECTEDP", "PROTECTEDP")
%%SET sigPtrs1("", "", "", "", "PROTECTEDP", "PROTECTEDP", "PROTECTEDP", "")
%%SET sigNulls0("", "", "")
%%SET sigNulls1("", "", "", "", "", "", "", "")
%%SET sigNullPtrs0("", "", "")
%%SET sigNullPtrs1("", "", "", "", "", "", "", "")
%%INCLUDE (insertStat)


!******************************************************************************!
!END SQL!

   
!BEGIN SQL COMMIT 0!
!******************************************************************************!

!EXEC SQL COMMIT TRANSACTION!

!------------------------------------------------------------------------------!

%%INCLUDE (commitStat)


!******************************************************************************!
!END SQL!



                                         ! BEGIN CHECK OF CASE B  !
   
   CASE SQLCODE.VALUE IS
      WHEN ZROWINSERTED DO;
      
      WHEN ZSEARCHFAIL DO
         IF SQLCODE.SUBCODE = ZROWNOTALLOCATED THEN
            
!BEGIN SQL SELECT 3!
!******************************************************************************!

!EXEC SQL SELECT TABREF, SAEIDT
                INTO `%TTABREF, `%TSAEID
                FROM TABLES
               WHERE NAME = `%ZTABLES AND BLKREF = `%COWNREF!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(3)
%%SET keyExprs("ZTABLES", "COWNREF")
%%SET keyPtrs("", "")
%%SET keyPrefix(2)
%%SET cols(4, 6)
%%SET vars("TTABREF", "TSAEID")
%%SET ptrs("", "")
%%SET nulls("", "")
%%SET nullPtrs("", "")
%%INCLUDE (locSelectStat)


!******************************************************************************!
!END SQL!

                  
            SEND PROGERROR WITH
               ZPROGERRORCODE1,
               COWNREF,
               TTABREF,
               TSAEID;
            EXIT;
         FI;
         
      WHEN ZERROR DO
         CASE SQLCODE.SUBCODE IS
            WHEN ZTABFULL DO
               
!BEGIN SQL SELECT 3!
!******************************************************************************!

!EXEC SQL SELECT TABREF, SAEIDT
                  INTO `%TTABREF, `%TSAEID
                  FROM TABLES
                  WHERE NAME = `%ZTABLES AND BLKREF = `%COWNREF!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(3)
%%SET keyExprs("ZTABLES", "COWNREF")
%%SET keyPtrs("", "")
%%SET keyPrefix(2)
%%SET cols(4, 6)
%%SET vars("TTABREF", "TSAEID")
%%SET ptrs("", "")
%%SET nulls("", "")
%%SET nullPtrs("", "")
%%INCLUDE (locSelectStat)


!******************************************************************************!
!END SQL!

                  
               SEND PROGERROR WITH
                  ZPROGERRORCODE1,
                  COWNREF,
                  TTABREF,
                  TSAEID;
               EXIT;
               
            WHEN ZTRHCONG DO
               SEND PROGERROR WITH
                  ZPROGERRORCODE4,
                  ZTRHSAEID2;
               EXIT;

            OTHERWISE DO;
         ESAC;
         
      OTHERWISE DO;
   ESAC;
                                         ! END CHECK OF CASE B    !

   
   
SEND DDINITTABLER REFERENCE PROTECTEDP:REF WITH
   PROTECTEDP:USERP;
   

!BEGIN SQL END 0!
!******************************************************************************!

!EXEC SQL END PROTECTED REGION!

!------------------------------------------------------------------------------!

%%INCLUDE (endStat)


!******************************************************************************!
!END SQL!

   
EXIT;














!*****************************************************************************!
!*                                                                           *! 
!*             D D H G E T N X T F K                                         *!
!*                                                                           *!
!*****************************************************************************!





! THE SIGNAL DDHGETNEXTFK IS A REQUEST FROM THE DBS TRANSACTION   !
! HANDLER TO SUPPLY IT WITH THE NEXT FOREIGN KEY, THAT REFERS TO  !
! A SPECIFIC TABLE. IF IT IS THE FIRST REQUEST FOR A FOREIGN KEY  !
! TO A SPECIFIC TABLE, THE CURSOR FINDFK IS OPENED. IT IS KEPT    !
! OPEN UNTIL NO MORE FK'S REFERRING TO THE CURRENT TABLE IS FOUND.!
! BETWEEN REQUESTS FOR FOREIGN KEYS TO THE SAME TABLE, THE OPEN   !
! CURSOR IS STORED IN THE PROTECTION FILE.                        !

! INSIGNAL:        DDHGETNEXTFK                                   !
! OUTSIGNAL:       DDHGETNEXTFKR                                  !

   ENTER DDHGETNXTFK WITH
      TTRID,
      PROTECTEDP,
      TTOWBLKREF,
      TTOWTABREF,
      CREFERRINGFKORDNO;
   



   IF CREFERRINGFKORDNO=ZFIRSTFK THEN
      
!BEGIN SQL BEGIN 0!
!******************************************************************************!

!EXEC SQL BEGIN PROTECTED REGION!

!------------------------------------------------------------------------------!

%%INCLUDE (beginStat)


!******************************************************************************!
!END SQL!

      PROTECTEDP:TRANSID=TTRID;
      PROTECTEDP:TOWBLKREF=TTOWBLKREF;
      PROTECTEDP:TOWTABREF=TTOWTABREF;
      
!BEGIN SQL OPEN_CURSOR 0!
!******************************************************************************!

!EXEC SQL OPEN FINDFK!

!------------------------------------------------------------------------------!

%%SET tabNo(5)
%%SET tabName(FOREIGNKEYS)
%%SET keyNo(3)
%%SET keyExprs("CREFERRINGFKORDNO", "TOWBLKREF", "TOWTABREF")
%%SET keyPtrs("", "PROTECTEDP", "PROTECTEDP")
%%SET keyPrefix(3)
%%SET keyOp(0)
%%SET curNo(2)
%%INCLUDE (locOpenStat)


!******************************************************************************!
!END SQL!

   FI;         


DDHGETNXTFK10)
   
   
!BEGIN SQL FETCH 5!
!******************************************************************************!

!EXEC SQL FETCH FINDFK INTO
      `%PROTECTEDP:ORDNO,
      `%PROTECTEDP:FBLKREF,
      `%PROTECTEDP:FTABREF,
      `%PROTECTEDP:KEYNO,
      `%PROTECTEDP:CONDITION!

!------------------------------------------------------------------------------!

%%SET tabNo(5)
%%SET tabName(FOREIGNKEYS)
%%SET keyNo(3)
%%SET keyPrefix(3)
%%SET keyOp(0)
%%SET curNo(2)
%%SET cols(3, 9, 8, 6, 10)
%%SET vars("ORDNO", "FBLKREF", "FTABREF", "KEYNO", "CONDITION")
%%SET ptrs("PROTECTEDP", "PROTECTEDP", "PROTECTEDP", "PROTECTEDP", "PROTECTEDP")
%%SET nulls("", "", "", "", "")
%%SET nullPtrs("", "", "", "", "")
%%SET preds(0)
%%INCLUDE (locFetchStat)


!******************************************************************************!
!END SQL!

   !$EXEC SQL CONTINUE$!   

   CASE SQLCODE.VALUE IS
      WHEN ZOK DO
         SEND DDHGETNXTFKR WITH
            PROTECTEDP:TRANSID,
            ZFKFOUND,
            PROTECTEDP,
            PROTECTEDP:ORDNO,
            PROTECTEDP:FBLKREF,
            PROTECTEDP:FTABREF,
            PROTECTEDP:KEYNO,
            PROTECTEDP:CONDITION;
            
      WHEN ZSEARCHFAIL DO
         SEND DDHGETNXTFKR WITH
            PROTECTEDP:TRANSID,
            ZFKNOTFOUND,
            +,
            +,
            +,
            +,
            +;
         
!BEGIN SQL CLOSE_CURSOR 0!
!******************************************************************************!

!EXEC SQL CLOSE FINDFK!

!------------------------------------------------------------------------------!

%%SET tabNo(5)
%%SET tabName(FOREIGNKEYS)
%%SET curNo(2)
%%INCLUDE (locCloseStat)


!******************************************************************************!
!END SQL!

         
!BEGIN SQL END 0!
!******************************************************************************!

!EXEC SQL END PROTECTED REGION!

!------------------------------------------------------------------------------!

%%INCLUDE (endStat)


!******************************************************************************!
!END SQL!

      
      WHEN ZERROR DO
         IF SQLCODE.SUBCODE = ZTABCONGESTION THEN
!            EXEC SQL DELAY 100 MS!
            GOTO DDHGETNXTFK10;
         FI;
            
      OTHERWISE DO;
   ESAC;
       
EXIT;                         
   










!*****************************************************************************!
!*                                                                           *! 
!*             D D H G E T R E F                                             *!
!*                                                                           *!
!*****************************************************************************!


! THE DBS TRANSACTION HANDLER ASKS FOR THE BLOCK REFERENCE TO     !
! THIS BLOCK.                                                     !
 
 
   RECEIVE DDHGETREF;
   
   LOADREF TOWNREF;
   
   RETURN DDHGETREFACK WITH
      TOWNREF;
 
   
















 



         
















!*****************************************************************************!
!*                                                                           *! 
!*             D D T A B R E F                                               *!
!*                                                                           *!
!*****************************************************************************!



   ENTER DDTABREF WITH
      TUSERP,
      TBLKREF,
      CTABNAME;
      
   
!BEGIN SQL BEGIN 0!
!******************************************************************************!

!EXEC SQL BEGIN PROTECTED REGION!

!------------------------------------------------------------------------------!

%%INCLUDE (beginStat)


!******************************************************************************!
!END SQL!

   
   PROTECTEDP:USERP=TUSERP;
   PROTECTEDP:REF=TBLKREF;
   PROTECTEDP:TABNAME=CTABNAME;
   
   
!BEGIN SQL OPEN_CURSOR 0!
!******************************************************************************!

!EXEC SQL OPEN GETBLOCKANDTABREF!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(3)
%%SET keyExprs("TABNAME")
%%SET keyPtrs("PROTECTEDP")
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(7)
%%INCLUDE (locOpenStat)


!******************************************************************************!
!END SQL!


DDTABREF10)

   
!BEGIN SQL FETCH 1!
!******************************************************************************!

!EXEC SQL FETCH GETBLOCKANDTABREF 
      INTO `%PROTECTEDP:BLKREF, `%PROTECTEDP:TABREF!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(3)
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(7)
%%SET cols(3, 4)
%%SET vars("BLKREF", "TABREF")
%%SET ptrs("PROTECTEDP", "PROTECTEDP")
%%SET nulls("", "")
%%SET nullPtrs("", "")
%%SET preds(0)
%%INCLUDE (locFetchStat)


!******************************************************************************!
!END SQL!

      
   CASE SQLCODE.VALUE IS
      WHEN ZTABLEFOUND DO
         SEND DDTABREFR REFERENCE PROTECTEDP:REF WITH
            PROTECTEDP:USERP,
            ZOK,
            PROTECTEDP:BLKREF,
            PROTECTEDP:TABREF;
            
      WHEN ZSEARCHFAIL DO
         SEND DDTABREFR REFERENCE PROTECTEDP:REF WITH
            PROTECTEDP:USERP,
            ZNOTABFOUNDFLAG,
            +,
            +;
            
      WHEN ZERROR DO
         IF SQLCODE.SUBCODE = ZTABCONGESTION THEN
!            EXEC SQL DELAY 100 MS!
            GOTO DDTABREF10;
         FI;
         
      OTHERWISE DO;
   ESAC;
   
   
!BEGIN SQL END 0!
!******************************************************************************!

!EXEC SQL END PROTECTED REGION!

!------------------------------------------------------------------------------!

%%INCLUDE (endStat)


!******************************************************************************!
!END SQL!

   EXIT;

      


!*****************************************************************************!
!*                                                                           *! 
!*             E V E N T M E S S A G E C                                     *!
!*                                                                           *!
!*****************************************************************************!




! EVENTMESSAGEC TELLS WHETHER OR NOT THE RECENT SYSTEM RESTART IS !
! DUE TO A FUNCTION CHANGE (FC) OR NOT. IN CASE OF A SMALL        !
! RESTART, THIS SIGNAL HAS TO BE ENTERED BEFORE ZSPH2DBDDH.       !

! OUTDATA:       CFC             INDICATES IF FC HAS OCCURRED     !

ENTER EVENTMESSAGEC WITH  
   TSTATEID,
   +,                                           
   +,
   +, 
   +,
   +,
   TFCIND;
   

IF TSTATEID = ZSYSTEMRESTART THEN
   IF TFCIND = ZFUNCTIONCHANGE THEN
      CFC=TRUE;
   FI;
FI;                      

EXIT;








!*****************************************************************************!
!*                                                                           *! 
!*             S T T O R                                                     *!
!*                                                                           *!
!*****************************************************************************!





! THIS ROUTINE WILL BE RUN ONCE IN EACH RESTART PHASE. THE SIGNAL !
! STTOR, WHICH INFORMS ABOUT THE CURRENT RESTART PHASE NUMBER, IS !
! ENTERED, THE APPROPRIATE ACTION IS PERFORMED, AND THE SIGNAL    !
! STTORRY IS RETURNED AS A RECEIPT THAT THE CURRENT RESTART PHASE !
! IS TAKEN CARE OF BY THIS BLOCK.                                 !

! OUTDATA:       CRESTCASE                      RESTART CASE      !
!                CRETURNFROMWHICHRESTCASE                         !

! POSSIBLE SUBROUTINECALLS:    EVENTREQ                           !
!                              WHICHRESTCASE                      !

   ENTER STTOR WITH 
      CRESTCASE,
      CPHASE,
      +,
      +,
      +,
      +,                      ! RESTART RANK !
      CSIGKEY;
!BEGIN SQL ENTER 0!
!******************************************************************************!


%%INCLUDE (comSttor("CRESTCASE", "CPHASE", "+", "+", "+", "+", "CSIGKEY"))


!******************************************************************************!
!END SQL!

             
   CASE CPHASE IS
      WHEN ZSPH1DBDDH DO DO EVENTREQ;
      WHEN ZSPH2DBDDH DO 
         CRETURNFROMWHICHRESTCASE=SYMSTTOR10;
         GOTO WHICHRESTCASE;
      WHEN ZSPH3DBDDH DO
         CRETURNFROMTRIGTOWINITIATION=SYMSTTOR10;
         CLOCALRESTARTPHASE = ZDBSINTERNALPHASE1;
         GOTO TRIGTOWINITIATION;
      WHEN ZSPH4DBDDH DO
         CRETURNFROMTRIGTOWINITIATION=SYMSTTOR10;
         CLOCALRESTARTPHASE = ZDBSINTERNALPHASE2;
         GOTO TRIGTOWINITIATION;
      WHEN ZSPH5DBDDH DO
         CRETURNFROMTRIGTOWINITIATION=SYMSTTOR10;
         CLOCALRESTARTPHASE = ZDBSINTERNALPHASE3;
         GOTO TRIGTOWINITIATION;
      WHEN ZSPH6DBDDH DO
         CRETURNFROMTRIGTOWINITIATION=SYMSTTOR10;
         CLOCALRESTARTPHASE = ZDBSINTERNALPHASE4;
         GOTO TRIGTOWINITIATION;
      OTHERWISE DO;
   ESAC;
          
STTOR10)
   SEND STTORRY WITH
      CSIGKEY,                ! RETURN DATA !
      ZBLOCKCAT, 
      ZSTTORRYVERSION,
      ZSPH1DBDDH,             ! WANTED RESTARTPHASE 1 !
      ZSPH2DBDDH,             ! WANTED RESTARTPHASE 2 !
      ZSPH3DBDDH,
      ZSPH4DBDDH,
      ZSPH5DBDDH,
      ZSPH6DBDDH,
      ZNOMOREPHASES;
             
   EXIT; 









!*****************************************************************************!
!*                                                                           *! 
!*             T O W R E S P A R T R                                         *!
!*                                                                           *!
!*****************************************************************************!



   ENTER TOWRESPARTR WITH
      PROTECTEDP,
      +;
      
   GOTO TRIGTOWINITIATIONS10;
   


   
   
   



!*****************************************************************************!
!*****************************************************************************!
!*****************************************************************************!
!*                                                                           *! 
!*             S U B R O U T I N E S   I N   P L E X                         *!
!*                                                                           *!
!*****************************************************************************!
!*****************************************************************************!
!*****************************************************************************!






!*****************************************************************************!
!*                                                                           *! 
!*             C H E C K S Y M V A L N A M E L E N G T H                     *!
!*                                                                           *!
!*****************************************************************************!




CHECKSYMVALNAMELENGTH)

   PROTECTEDP:MAXSYMLENGTH=0;
   PROTECTEDP:SYMBOLVALUE=ZMAXSYMVAL;
   PROTECTEDP:SYMBOLFOUND=TRUE; 
   
   IF PROTECTEDP:NAMELENGTH = 7 THEN
      PROTECTEDP:PRWIDTH= PROTECTEDP:NAMELENGTH;
      GOTO CHECKSYMVALNAMELENGTH30;
   FI;        
      
CHECKSYMVALNAMELENGTH10)                                   ! BEGIN LOOP !

   IF PROTECTEDP:SYMBOLFOUND = FALSE THEN
      IF PROTECTEDP:MAXSYMLENGTH  > PROTECTEDP:NAMELENGTH THEN
         PROTECTEDP:PRWIDTH=PROTECTEDP:MAXSYMLENGTH;
      ELSE
         PROTECTEDP:PRWIDTH=PROTECTEDP:NAMELENGTH;
      FI;      
      GOTO CHECKSYMVALNAMELENGTH30;
   FI;
      
   SEND TOWPRESYMBOL REFERENCE PROTECTEDP:REF WITH
      PROTECTEDP,
      PROTECTEDP:TOWTABREF,
      PROTECTEDP:FLDNUMBER, 
      PROTECTEDP:SYMBOLVALUE,
   WAIT FOR TOWPRESYMBOLACK IN CHECKSYMVALNAMELENGTH20;   
         
CHECKSYMVALNAMELENGTH20)
   RETRIEVE TOWPRESYMBOLACK WITH
      PROTECTEDP,
      TRETURNCODE,
      PROTECTEDP:SYMBOLVALUE,
      CSYMBOLNAME;
   
   
         
   IF TRETURNCODE = ZSYMBOLFOUND THEN
      CHAR VX:CSYMBOLNAME(N:0) TO VT:TSYMLENGTH;
      IF TSYMLENGTH > PROTECTEDP:MAXSYMLENGTH THEN
         PROTECTEDP:MAXSYMLENGTH=TSYMLENGTH;
      FI;
      PROTECTEDP:SYMBOLVALUE=PROTECTEDP:SYMBOLVALUE-1;
   ELSE
      PROTECTEDP:SYMBOLFOUND=FALSE;   
   FI;
      
   GOTO CHECKSYMVALNAMELENGTH10;                       ! END LOOP !

       
CHECKSYMVALNAMELENGTH30)

   BRANCH ON CRETURNFROMCHECKSYMVALNAMELENGTH
      TO DDINITFIELD10 IF SYMDDINITFIELD10
      ELSE TO DDINITFIELD10;       



















!*****************************************************************************!
!*                                                                           *! 
!*             C L E A R A L L T A B S                                       *!
!*                                                                           *!
!*****************************************************************************!




! THIS ROUTINE TAKES CARE OF THE CASES 'SYSTEM START', 'LARGE     !
! RESTART' AND 'LARGE RESTART WITH RELOAD'. THE OBJECTIVE IS TO   !
! DELETE ALL ROWS IN ALL TABLES IN DATA DICTIONARY. BY DELETING   !
! THE ENTIRE TABLES TABLE, ALL OTHERTABLES WILL BE DELETED DUE TO !
! THE FOREIGN KEY CONDITIONS.                                     !

! THE ROUTINE WORKS AS FOLLOWS. THE CURSOR FINDNEWTABLE IS OPENED !
! AND FETCHED. IF THE TABLES TABLE IS EMPTY, THE FLAG CALLTABS-   !
! CLEARED WILL BE SET TO TRUE AND VIA JUMPS TO CLEARALLTABS10 AND !
! -40 THE ROUTINE WILL BE ENDED.                                  !

! HOWEVER, IF THERE ARE MORE ROWS IN TABLES TO DELETE, A TRANS-   !
! ACTION WILL BE STARTED BY THE SIGNAL TRHSTATRANS. THE REASON    !
! FOR USING THE SIGNAL AND NOT THE START TRANSACTION INSTRUCTION  !
! IS THAT THE TRANSACTION SHOULD NOT BE LOGGED. THE DELETE IS     !
! PERFORMED AND THE PROGRAM EXECUTION CONTINUES AT CLEARALLTABS20 !

! IN THE CASE 'LARGE RESTART', PROBLEMS MAY OCCUR IN THE TRANS-   !
! ACTION HANDLER. THERE MAY BE A LINE OF TRANSACTIONS IN THE      !
! COMMIT PHASE STEMMING FROM BEFORE THE RESTART, WHICH ARE WAITING!
! TO BE COMMITTED. IF THESE TRANSACTIONS OCCUPY ALL TRANSACTION   !
! INDIVIDUALS, SQLCODE WILL REPORT TRH CONGESTION AND THE SIGNAL  !
! PROGERROR WILL BE SENT BECAUSE THE SYSTEM WILL NOT BE ABLE TO   !
! ADVANCE ANY FURTHER IN THE RESTART PROCEDURE.                   !

! INDATA:        NONE                                             !

! OUTDATA:       NONE                                             !

! RESULT:        ALL TABLES THAT ARE PHYSICALLY STORED IN DD ARE  !
!                DELETED.                                         !

CLEARALLTABS)

   
!BEGIN SQL BEGIN 0!
!******************************************************************************!

!EXEC SQL BEGIN PROTECTED REGION!

!------------------------------------------------------------------------------!

%%INCLUDE (beginStat)


!******************************************************************************!
!END SQL!
         
   CALLTABSCLEARED = FALSE;
   
CLEARALLTABS10)

   IF CALLTABSCLEARED = TRUE THEN          ! BEGIN LOOP !
      GOTO CLEARALLTABS40;
   FI;
   
   
!BEGIN SQL OPEN_CURSOR 0!
!******************************************************************************!

!EXEC SQL OPEN FINDNEWTABLE!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(0)
%%SET keyExprs("ZMAXNOFROWS")
%%SET keyPtrs("")
%%SET keyPrefix(1)
%%SET keyOp(2)
%%SET curNo(3)
%%INCLUDE (locOpenStat)


!******************************************************************************!
!END SQL!

   
!BEGIN SQL FETCH 0!
!******************************************************************************!

!EXEC SQL FETCH FINDNEWTABLE INTO `%PROTECTEDP:NEXTTOBEDELETED!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(0)
%%SET keyPrefix(1)
%%SET keyOp(2)
%%SET curNo(3)
%%SET cols(0)
%%SET vars("NEXTTOBEDELETED")
%%SET ptrs("PROTECTEDP")
%%SET nulls("")
%%SET nullPtrs("")
%%SET preds(0)
%%INCLUDE (locFetchStat)


!******************************************************************************!
!END SQL!



   CASE SQLCODE.VALUE IS
   
      WHEN ZTABLEFOUND DO
         
         CRETURNFROMTRHSTATRANSR=SYMCLEARALLTABS30;
         SEND TRHSTATRANS WITH
            PROTECTEDP,            ! OWN POINTER !
            COWNREF,
            ZDONOTLOG,
            +;     
         EXIT;
         
!        ACTION CONTINUES AT CLEARALLTABS30 BELOW                              !
         
      WHEN ZNOMORETABLES DO
         CALLTABSCLEARED = TRUE;
         
      OTHERWISE DO;
   ESAC;

CLEARALLTABS20)
   
   
!BEGIN SQL CLOSE_CURSOR 0!
!******************************************************************************!

!EXEC SQL CLOSE FINDNEWTABLE!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET curNo(3)
%%INCLUDE (locCloseStat)


!******************************************************************************!
!END SQL!

      
   GOTO CLEARALLTABS10;                     ! END LOOP !






!     CONTINUE EXECUTION OF 'CASE SQLCODE.VALUE IS WHEN ZTABLEFOUND DO'        !


CLEARALLTABS30)
            
   CASE CMESSAGE.VALUE IS
      WHEN ZOK DO;
      
      WHEN ZERROR DO
         IF CMESSAGE.SUBCODE = ZTRHCONG THEN
            SEND PROGERROR WITH
               ZPROGERRORCODE4,
               ZTRHSAEID1;
         FI;
         EXIT;
         
      OTHERWISE DO;
   ESAC;
   
   
!BEGIN SQL DELETE 2!
!******************************************************************************!

!EXEC SQL DELETE
      FROM TABLES
      WHERE TROWNO = `%PROTECTEDP:NEXTTOBEDELETED!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(0)
%%SET keyExprs("NEXTTOBEDELETED")
%%SET keyPtrs("PROTECTEDP")
%%SET keyPrefix(1)
%%SET sigAssVars0()
%%SET sigAssPtrs0()
%%SET sigAssExprs0()
%%INCLUDE (deleteStat)


!******************************************************************************!
!END SQL!


   CASE SQLCODE.VALUE IS
      WHEN ZOK DO;
      
      WHEN ZERROR DO
         IF SQLCODE.SUBCODE = ZTRHCONG THEN
            SEND PROGERROR WITH
               ZPROGERRORCODE4,
               ZTRHSAEID1;
         FI;
         EXIT;
         
      OTHERWISE DO;
   ESAC;
      
   
!BEGIN SQL PREPARE 0!
!******************************************************************************!

!EXEC SQL PREPARE TRANSACTION!

!------------------------------------------------------------------------------!

%%INCLUDE (prepareStat)


!******************************************************************************!
!END SQL!

   
   CASE SQLCODE.VALUE IS
      WHEN ZOK DO;
      
      WHEN ZERROR DO
         IF SQLCODE.SUBCODE = ZTRHCONG THEN
            SEND PROGERROR WITH
               ZPROGERRORCODE4,
               ZTRHSAEID1;
         FI;
         EXIT;
         
      OTHERWISE DO;
   ESAC;

   
!BEGIN SQL COMMIT 0!
!******************************************************************************!

!EXEC SQL COMMIT TRANSACTION!

!------------------------------------------------------------------------------!

%%INCLUDE (commitStat)


!******************************************************************************!
!END SQL!
            

   GOTO CLEARALLTABS20;


CLEARALLTABS40)

   
!BEGIN SQL END 0!
!******************************************************************************!

!EXEC SQL END PROTECTED REGION!

!------------------------------------------------------------------------------!

%%INCLUDE (endStat)


!******************************************************************************!
!END SQL!


   BRANCH ON CRETURNFROMCLEARALLTABS
      TO WHICHRESTCASE10 IF SYMWHICHRESTCASE10
      ELSE TO WHICHRESTCASE10;
      
!     END OF ROUTINE CLEARALLTABS                                              !














!*****************************************************************************!
!*                                                                           *! 
!*             C L E A R S O M E T A B S                                     *!
!*                                                                           *!
!*****************************************************************************!






! THIS ROUTINE TAKES CARE OF THE CASE 'SMALL RESTART DUE TO A     !
! FUNCTION CHANGE'. BY SENDING FCHBNOOLD2 AND RECEIVING FCHBNO-   !
! OLD2RPY, THE ROUTINE GETS ALL THE BLOCKNUMBERS TO THE BLOCKS    !
! THAT PARTICIPATE IN THE FUNCTION CHANGE. IT TRANSFORMS ALL THE  !
! BLOCK NUMBERS TO BLOCK REFERENCES AND IT DELETES ALL ROWS,      !
! WHICH ARE ASSOCIATED WITH THE CURRENT BLOCKS, FROM ALL DATA     !
! DICTIONARY TABLES.                                              !

! OUTDATA:          CNOFBLOCKS                                    !
!                   CBLOCK              ARRAY OF BLOCK REFERENCES !

CLEARSOMETABS)

   CNOFREQ=0;
   CBLOCKCOUNT = 0;
   CK=0;
   CALLTABSRECEIVED=FALSE;







CLEARSOMETABS10)                      ! BEGIN LOOP FOR EACH SIGNAL FCH.. !

   IF CALLTABSRECEIVED = TRUE THEN
      GOTO CLEARSOMETABS60;
   FI;   

   SEND FCHBNOOLD2 WITH
      CK,
      COWNREF,
      CNOFREQ;
   EXIT;
          
   ENTER FCHBNOOLD2RPY WITH
      CK,
      CNOFREQ,
      CNOFBLOCKS,
      CTEMPBLOCK( 0),
      CTEMPBLOCK( 1),
      CTEMPBLOCK( 2),
      CTEMPBLOCK( 3),
      CTEMPBLOCK( 4),
      CTEMPBLOCK( 5),
      CTEMPBLOCK( 6),
      CTEMPBLOCK( 7),
      CTEMPBLOCK( 8),
      CTEMPBLOCK( 9),
      CTEMPBLOCK( 10),
      CTEMPBLOCK( 11),
      CTEMPBLOCK( 12),
      CTEMPBLOCK( 13),
      CTEMPBLOCK( 14),
      CTEMPBLOCK( 15);
             

   TCOUNTER = 0;
   
CLEARSOMETABS20)          ! BEGIN LOOP FOR EACH BLOCK IN THE SIGNAL !

   IF TCOUNTER = 16 THEN
      GOTO CLEARSOMETABS50;
   FI;

   TNOFRECEIVEDDATA=CNOFREQ*16 + TCOUNTER + 1;
   
   IF TNOFRECEIVEDDATA =< CNOFBLOCKS  THEN
   
      TBLKNUM = CTEMPBLOCK(TCOUNTER) - 1;
      SEND NOFORFUCODE WITH
         TCOUNTER,
         ZTOWFUCODE,
         TBLKNUM,
      WAIT FOR NOFORFUCODEACK IN CLEARSOMETABS30;
      
   ELSE
   
      CALLTABSRECEIVED=TRUE;
      GOTO CLEARSOMETABS50;
      
   FI;
   
 
CLEARSOMETABS30)

   RETRIEVE NOFORFUCODEACK WITH
      TCOUNTER,
      TBLKNUM,
      TANSWER;
      
   CASE TANSWER IS
      WHEN ZOK DO
      
         IF TBLKNUM = CTEMPBLOCK(TCOUNTER) THEN
         
            TRANSFORM BLOCKNUMBER IN TEMP TBLKNUM
               TO BLOCKREF IN TEMP TBLKREF;
               
            CBLOCK(CBLOCKCOUNT) = TBLKREF;
            CBLOCKCOUNT = CBLOCKCOUNT+1;
         FI;
            
      OTHERWISE DO;
   ESAC; 
  
   TCOUNTER = TCOUNTER + 1;
   GOTO CLEARSOMETABS20;           ! END LOOP FOR EACH BLOCK IN THE SIGNAL !
 
 
 
 
CLEARSOMETABS50)
  
   CK=CK+16;
   CNOFREQ=CNOFREQ+1;   
   GOTO CLEARSOMETABS10;                 ! END LOOP FOR EACH SIGNAL FCH.. !






! ALL BLOCK REFERENCES OF ALL TABLE-OWNING BLOCKS THAT PARTICIPATE IN THE !
! FUNCTION CHANGE ARE STORED IN THE ARRAY CBLOCK. THE NUMBER OF BLOCKS    !
! THAT ARE STORED IN CBLOCK WILL BE GIVEN BY CNOFBLOCKS.                  !


CLEARSOMETABS60)

   CNOFBLOCKS = CBLOCKCOUNT;
   CK=0;
   
!BEGIN SQL BEGIN 0!
!******************************************************************************!

!EXEC SQL BEGIN PROTECTED REGION!

!------------------------------------------------------------------------------!

%%INCLUDE (beginStat)


!******************************************************************************!
!END SQL!










CLEARSOMETABS70)
          
   IF CK=CNOFBLOCKS THEN                 ! BEGIN LOOP FOR EACH BLOCK !
      GOTO CLEARSOMETABS110;
   FI;
                

   CRETURNFROMTRHSTATRANSR=SYMCLEARSOMETABS80;

   
   SEND TRHSTATRANS WITH
      PROTECTEDP,            ! OWN POINTER !
      COWNREF,
      ZDONOTLOG,
      +;
   EXIT;

CLEARSOMETABS80)

   CMORETABSTODELETE = TRUE;
   
!BEGIN SQL OPEN_CURSOR 0!
!******************************************************************************!

!EXEC SQL OPEN FINDNEXTTABLE!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(4)
%%SET keyExprs("CBLOCK(CK)")
%%SET keyPtrs("")
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(4)
%%INCLUDE (locOpenStat)


!******************************************************************************!
!END SQL!







CLEARSOMETABS90)                          ! BEGIN LOOP FOR EACH TABLE !

   IF CMORETABSTODELETE = FALSE THEN
      GOTO CLEARSOMETABS100;
   FI;

   
!BEGIN SQL FETCH 0!
!******************************************************************************!

!EXEC SQL FETCH FINDNEXTTABLE INTO `%PROTECTEDP:NEXTTOBEDELETED!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(4)
%%SET keyPrefix(1)
%%SET keyOp(0)
%%SET curNo(4)
%%SET cols(0)
%%SET vars("NEXTTOBEDELETED")
%%SET ptrs("PROTECTEDP")
%%SET nulls("")
%%SET nullPtrs("")
%%SET preds(0)
%%INCLUDE (locFetchStat)


!******************************************************************************!
!END SQL!

   !$EXEC SQL CONTINUE$!
   
   CASE SQLCODE.VALUE IS
      WHEN ZTABLEFOUND DO
         
!BEGIN SQL DELETE 1!
!******************************************************************************!

!EXEC SQL DELETE FROM TABLES
            WHERE TROWNO=`%PROTECTEDP:NEXTTOBEDELETED!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET keyNo(0)
%%SET keyExprs("NEXTTOBEDELETED")
%%SET keyPtrs("PROTECTEDP")
%%SET keyPrefix(1)
%%SET sigAssVars0()
%%SET sigAssPtrs0()
%%SET sigAssExprs0()
%%INCLUDE (deleteStat)


!******************************************************************************!
!END SQL!

     
      WHEN ZSEARCHFAIL DO
         CMORETABSTODELETE = FALSE;
         
      OTHERWISE DO;
   ESAC;
  
   GOTO CLEARSOMETABS90;                  ! END LOOP FOR EACH TABLE !





CLEARSOMETABS100)
   
   
!BEGIN SQL COMMIT 0!
!******************************************************************************!

!EXEC SQL COMMIT TRANSACTION!

!------------------------------------------------------------------------------!

%%INCLUDE (commitStat)


!******************************************************************************!
!END SQL!

   
!BEGIN SQL CLOSE_CURSOR 0!
!******************************************************************************!

!EXEC SQL CLOSE FINDNEXTTABLE!

!------------------------------------------------------------------------------!

%%SET tabNo(1)
%%SET tabName(TABLES)
%%SET curNo(4)
%%INCLUDE (locCloseStat)


!******************************************************************************!
!END SQL!

            

   CK=CK+1;
   GOTO CLEARSOMETABS70;                 ! END LOOP FOR EACH BLOCK !
 
 
 
 
 
 
 
 
   
CLEARSOMETABS110)                       
   
!BEGIN SQL END 0!
!******************************************************************************!

!EXEC SQL END PROTECTED REGION!

!------------------------------------------------------------------------------!

%%INCLUDE (endStat)


!******************************************************************************!
!END SQL!

          
BRANCH ON CRETURNFROMCLEARSOMETABS
   TO WHICHRESTCASE10 IF SYMWHICHRESTCASE10
   ELSE TO WHICHRESTCASE10;



















!*****************************************************************************!
!*                                                                           *! 
!*             E V E N T R E Q                                               *!
!*                                                                           *!
!*****************************************************************************!





! THIS ROUTINE SENDS THE SIGNAL EVENTMSGREQ IN ORDER TO TELL KEED !
! THAT THIS BLOCK WANTS TO SUBSCRIBE ON THE SIGNAL EVENTMESSAGEC  !
! IN THE SPECIFIC CASE THAT THE RECENT SYSTEM RESTART FLAG HAS    !
! CHANGED STATES. THE OBJECTIVE IS TO FIND OUT WHETHER OR NOT A   !
! SYSTEM RESTART IS CAUSED BY A FUNCTION CHANGE.                  !

! INDATA:        NONE                                             !

! OUTDATA:       COWNREF                                          !
!                CFC=FALSE          VALUE MAY BE CHANGED LATER BY !
!                                   SIGNAL EVENTMESSAGEC.         !

          
BEGIN EVENTREQ;

   LOADREF TOWNREF;
   COWNREF=TOWNREF;   

   CFC=FALSE;


EVENTREQ10)
         
   SEND EVENTMSGREQ WITH
      +,                       ! OWN POINTER !
      COWNREF,
      ZINFOONLEVELC,
      ZONEEVENT,
      ZSYSRESTFLAGCHANGED,
   WAIT FOR EVENTMSGREQACK IN EVENTREQ20;
          
EVENTREQ20)
   RETRIEVE EVENTMSGREQACK WITH 
      +,                       ! OWN POINTER !
      TRETURNCODE;
          
             
   CASE TRETURNCODE IS
      WHEN ZREQUESTACKN DO;
      WHEN ZCONGESTION DO
!         EXEC SQL DELAY 100 MS!
         GOTO EVENTREQ10;          ! CONGESTION IN KEED. TRY AGAIN !
      OTHERWISE DO;  
   ESAC;
          
END EVENTREQ;

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 












!*****************************************************************************!
!*                                                                           *! 
!*             T R I G T O W I N I T I A T I O N S                           *!
!*                                                                           *!
!*****************************************************************************!



TRIGTOWINITIATION)

   
!BEGIN SQL BEGIN 0!
!******************************************************************************!

!EXEC SQL BEGIN PROTECTED REGION!

!------------------------------------------------------------------------------!

%%INCLUDE (beginStat)


!******************************************************************************!
!END SQL!


   PROTECTEDP:BLKNUM = 0;
   PROTECTEDP:COUNTER = 0;
   

TRIGTOWINITIATIONS10)

   IF CONLYSOMEBLOCKS = TRUE THEN
   
      IF PROTECTEDP:COUNTER = CNOFBLOCKS THEN
         GOTO TRIGTOWINITIATIONS30;
      FI;
      
      SEND TOWRESPART REFERENCE CBLOCK(PROTECTEDP:COUNTER) WITH
         COWNREF,
         PROTECTEDP,
         CLOCALRESTARTPHASE;
         
      PROTECTEDP:COUNTER = PROTECTEDP:COUNTER+1;
      EXIT;
                     
   ELSE
      
      SEND NOFORFUCODE WITH
         PROTECTEDP,
         ZTOWFUCODE,
         PROTECTEDP:BLKNUM,
      WAIT FOR NOFORFUCODEACK IN TRIGTOWINITIATIONS20;
         
   FI;
   
TRIGTOWINITIATIONS20)

   RETRIEVE NOFORFUCODEACK WITH
      PROTECTEDP,
      PROTECTEDP:BLKNUM,
      TANSWER;
      
   CASE TANSWER IS
   
      WHEN ZOK DO
      
         TBLKNUM = PROTECTEDP:BLKNUM;
         TRANSFORM BLOCKNUMBER IN TEMP TBLKNUM
            TO BLOCKREF IN TEMP TBLKREF;

         SEND TOWRESPART REFERENCE TBLKREF WITH
            COWNREF,
            PROTECTEDP,
            CLOCALRESTARTPHASE;
            
         EXIT;
         
      OTHERWISE DO

         GOTO TRIGTOWINITIATIONS30;
            
   ESAC;



TRIGTOWINITIATIONS30)


   BRANCH ON CRETURNFROMTRIGTOWINITIATION
      TO STTOR10 IF SYMSTTOR10
      ELSE TO STTOR10;







!*****************************************************************************!
!*                                                                           *! 
!*             W H I C H R E S T C A S E                                     *!
!*                                                                           *!
!*****************************************************************************!






! THIS ROUTINE DIFFERS BETWEEN THE TWO ALTERNATIVE RESTART CASES  !
! THAT MAY OCCUR. IF A SYSTEM START OR ANY KIND OF LARGE RESTART  !
! OCCURS, THEN THE ENTIRE DATA DICTIONARY WILL BE (RE-)INITIATED  !
! AND THIS HAS TO BE PREPARED BY CLEARING ALL DATA DICTIONARY     !
! TABLES. A SMALL RESTART IMPLIES NO ACTION FROM DATA DICTIONARY  !
! EXCEPT WHEN THE RESTART IS CAUSED BY A FUNCTION CHANGE. IN THIS !
! CASE, ONLY THE BLOCKS THAT PARTICIPATE IN THE FUNCTION CHANGE   !
! WILL BE REINITIATED IN DATA DICTIONARY.                         !

! INDATA:        CRESTCASE        RESTART CASE                    !
!                CFC              HAS AN FC OCCURRED?             !

! OUTDATA:       CSMALLREST       BOOLEAN                         !
!                CONLYSOMEBLOCKS  BOOLEAN                         !

! ACTIONS:       CALL SUBROUTINE CLEARSOMETABS, CLEARALLTABS OR   !
!                DO NOTHING                                       !

WHICHRESTCASE)

   CONLYSOMEBLOCKS = FALSE;
   CSMALLREST=FALSE;
   
   CASE CRESTCASE IS

      WHEN ZSMALLRESTART DO
         CSMALLREST=TRUE;
         IF  CFC=TRUE THEN
            CONLYSOMEBLOCKS = TRUE;
            CRETURNFROMCLEARSOMETABS=SYMWHICHRESTCASE10;          
            GOTO CLEARSOMETABS;       
         FI;

      WHEN ZLARGERELOAD, ZLARGERESTART, ZSYSTEMSTART DO
         CRETURNFROMCLEARALLTABS = SYMWHICHRESTCASE10;
         CNEXTTROWNO = 0;
         CNEXTFROWNO = 0;  
         GOTO CLEARALLTABS;
         
      OTHERWISE DO;   
   ESAC;
   


WHICHRESTCASE10) 
  
   BRANCH ON CRETURNFROMWHICHRESTCASE
      TO STTOR10 IF SYMSTTOR10
      ELSE TO STTOR10;


! Additional SQL statments are stated to make sure that all the grammar 
  rules are used at least one time !


!BEGIN SQL CONTINUE 0!
!******************************************************************************!

!EXEC SQL CONTINUE AT LEVEL B DELAY 5 MS!

!------------------------------------------------------------------------------!

%%SET level("B")
%%SET exprs("5")
%%SET timeUnit("MS")
%%INCLUDE (continueStat)


!******************************************************************************!
!END SQL!



!BEGIN SQL CONTINUE 0!
!******************************************************************************!

!EXEC SQL CONTINUE B!

!------------------------------------------------------------------------------!

%%SET level("B")
%%SET exprs("")
%%SET timeUnit("")
%%INCLUDE (continueStat)


!******************************************************************************!
!END SQL!



!BEGIN SQL GET_DB_NUMBER 0!
!******************************************************************************!

!EXEC SQL GET DBNUMBER INTO `%a!

!------------------------------------------------------------------------------!

%%SET vars("A")
%%SET ptrs("")
%%INCLUDE (getDbnumberStat)


!******************************************************************************!
!END SQL!



!BEGIN SQL UPDATE 0!
!******************************************************************************!

!EXEC SQL UPDATE test1 AS tt SET col3=`%a`%b, col6=`%b WHERE col2 = "bb" AND col1 = "aa"!

!------------------------------------------------------------------------------!

%%SET tabNo(10)
%%SET tabName(TEST1)
%%SET keyNo(2)
%%SET keyExprs("SQLM_1", "SQLM_2")
%%SET keyPtrs("PROTECTEDP", "PROTECTEDP")
%%SET keyPrefix(2)
%%SET sigCount(1)
%%SET sigAssVars0("SQLM_2", "SQLM_1")
%%SET sigAssVars1()
%%SET sigAssPtrs0("PROTECTEDP", "PROTECTEDP")
%%SET sigAssPtrs1()
%%SET sigAssExprs0("""bb""", """aa""")
%%SET sigAssExprs1()
%%SET sigCols0(4)
%%SET sigCols1(7)
%%SET sigColOps0("=")
%%SET sigColOps1("=")
%%SET sigExprs0("A")
%%SET sigExprs1("B")
%%SET sigPtrs0("")
%%SET sigPtrs1("")
%%SET sigNulls0("B")
%%SET sigNulls1("")
%%SET sigNullPtrs0("")
%%SET sigNullPtrs1("")
%%INCLUDE (updateStat)


!******************************************************************************!
!END SQL!



!BEGIN SQL UPDATE 0!
!******************************************************************************!

!EXEC SQL UPDATE test1 AS tt SET col3=`%a:b`%c:d, col6=`%b WHERE CURRENT OF WORK!

!------------------------------------------------------------------------------!

%%SET tabNo(10)
%%SET tabName(TEST1)
%%SET cols(4, 7)
%%SET exprs("B", "B")
%%SET ptrs("A", "")
%%SET nulls("D", "")
%%SET nullsPtrs("C", "")
%%INCLUDE (workUpdateStat)


!******************************************************************************!
!END SQL!



!BEGIN SQL UPDATE_VOLATILE 1!
!******************************************************************************!

!EXEC SQL UPDATE test3 AT (`%xx) tt VOLATILE col4=`%a 
         WHERE test3.col9 = 4!

!------------------------------------------------------------------------------!

%%SET tabNo(257)
%%SET tabName(TEST3)
%%SET blockRef("XX")
%%SET keyExprs("4")
%%SET sigCount(0)
%%SET sigAssVars0()
%%SET sigAssPtrs0()
%%SET sigAssExprs0()
%%SET sigCols0(5)
%%SET sigColOps0("=")
%%SET sigExprs0("A")
%%SET sigPtrs0("")
%%SET sigNulls0("")
%%SET sigNullPtrs0("")
%%INCLUDE (remUpdateVolatileStat)


!******************************************************************************!
!END SQL!



!BEGIN SQL SELECT 0!
!******************************************************************************!

!EXEC SQL SELECT col3 INTO `%a`%b FROM test1 WHERE CURRENT OF WORK!

!------------------------------------------------------------------------------!

%%SET tabNo(10)
%%SET tabName(TEST1)
%%SET keyNo(1)
%%SET keyExprs("WORK")
%%SET keyPtrs("")
%%SET keyPrefix(0)
%%SET cols(4)
%%SET vars("A")
%%SET ptrs("")
%%SET nulls("B")
%%SET nullPtrs("")
%%INCLUDE (locSelectStat)


!******************************************************************************!
!END SQL!
  


!BEGIN SQL SELECT 0!
!******************************************************************************!

!EXEC SQL SELECT col3 INTO `%a`%b FROM test1 WHERE CURRENT OF ORIGINAL!

!------------------------------------------------------------------------------!

%%SET tabNo(10)
%%SET tabName(TEST1)
%%SET keyNo(1)
%%SET keyExprs("ORIGINAL")
%%SET keyPtrs("")
%%SET keyPrefix(0)
%%SET cols(4)
%%SET vars("A")
%%SET ptrs("")
%%SET nulls("B")
%%SET nullPtrs("")
%%INCLUDE (locSelectStat)


!******************************************************************************!
!END SQL!
  


!BEGIN SQL START 0!
!******************************************************************************!

!EXEC SQL START WORK "abc"!

!------------------------------------------------------------------------------!

%%SET transId("""abc""")
%%INCLUDE (startStat)


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



!BEGIN SQL ROLLBACK 0!
!******************************************************************************!

!EXEC SQL ROLLBACK TRANSACTION!

!------------------------------------------------------------------------------!

%%INCLUDE (rollbackStat)


!******************************************************************************!
!END SQL!




! Comment test !
! EXEC SQL START WORK "abc""def`%ghi``jkl`%`%mno````pqr" !

   

! String test !

!BEGIN SQL START 0!
!******************************************************************************!

!EXEC SQL START WORK "abc""def`%ghi``jkl`%`%mno````pqr"!

!------------------------------------------------------------------------------!

%%SET transId("""abc""def`%ghi``jkl`%`%mno````pqr""")
%%INCLUDE (startStat)


!******************************************************************************!
!END SQL!

   

      


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

%%INCLUDE (towData())

%%INCLUDE (tuData())

!END SQL!



END DOCUMENT;
