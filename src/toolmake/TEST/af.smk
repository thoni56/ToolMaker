----------------------------------------------------------------------------
-- af.smk			Date: 1997-01-20/toolmake
--
-- af - ScannerMaker description file
--
----------------------------------------------------------------------------
-- Created:   1993-04-27/reibert@roo
-- Generated: 1997-01-20 18:40:40/toolmake v2,r1,c6
----------------------------------------------------------------------------

%%EXPORT

extern afScContext lexContext;

%%DECLARATIONS

afScContext lexContext;

%%CONTEXT
    char *fileName;
    int fd;

%%READER
    return read(smThis->fd, (char *)smBuffer, smLength);

%%DEFINITIONS

    White = [ \t\n];
    NotWhite = [^ \t\n];

%%VOCABULARY main

%%SCANNER main %%RULES

    ITEM = NotWhite+
	%%
		/* Semantic action */
	%%;

    Unknown = _Unknown;
    EndOfText = _EndOfText;

%%SKIP

     Blank = White+;

