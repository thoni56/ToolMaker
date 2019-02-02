%%OPTIONS
	LIBRARY '../../..';
%%CONTEXT

  int fd;

%%READER

  return read(smThis->fd, smBuffer, smLength);

%%MAP

	[A-Z]		= [a-z];

%%DEFINITIONS

	letter		= [a-z] ;
	string_element	= [']['] ! [ -&(-~\t] ;
	digit		= [0-9] ;
	digit_sequence	= digit+ ;
	exponent	= [e][+\-]?digit_sequence ;

%%VOCABULARY pascal

	EOT		= 0;
	unknown		= 1;
	'of'		= 2;
	'or'		= 3;
	'in'		= 4;
	'if'		= 5;
	'do'		= 6;
	'to'		= 7;
	'var'		= 8;
	'end'		= 9;
	'set'		= 10;
	'nil'		= 11;
	'not'		= 12;
	'div'		= 13;
	'mod'		= 14;
	'and'		= 15;
	'for'		= 16;
	'type'		= 17;
	'case'		= 18;
	'file'		= 19;
	'goto'		= 20;
	'then'		= 21;
	'else'		= 22;
	'with'		= 23;
	'label'		= 24;
	'const'		= 25;
	'array'		= 26;
	'begin'		= 27;
	'until'		= 28;
	'while'		= 29;
	'packed'	= 30;
	'record'	= 31;
	'repeat'	= 32;
	'downto'	= 33;
	'program'	= 34;
	'function'	= 35;
	'procedure'	= 36;
	Identifier	= 38;
	Character	= 39;
	String		= 40;
	Unsigned_Integer= 41;
	Unsigned_Real	= 42;
	'+'		= 44;
	'-'		= 45;
	';'		= 46;
	','		= 47;
	'='		= 48;
	'('		= 49;
	')'		= 50;
	':'		= 51;
	'.'		= 52;
	'*'		= 53;
	'<'		= 54;
	'>'		= 55;
	'..'		= 56;
	'<>'		= 57;
	'<='		= 58;
	'>='		= 59;
	':='		= 60;
	'^'		= 62;
	'['		= 63;
	']'		= 64;

    %%SCANNER main %%RULES

	Identifier	= letter ( letter ! digit ! '_')* ;
	Character	= ['] string_element ['] ;
	String		= ['] string_element string_element+ ['] ! [']['] ;
	Unsigned_Integer= digit_sequence ;
	Unsigned_Real	= digit_sequence '.' digit_sequence exponent?
			! digit_sequence exponent ;

	'^'		= '^' ! '@' ;
	'['		= '[' ! '(.' ;
	']'		= ']' ! '.)' ;

	EOT 		= _EndOfText;
	unknown		= _Unknown;

    %%SKIP

	blanks		= [\001- ~-]+ ;
	comment 	= ('(*'[^\000]*'*)' ! '{'[^\000]*'}').;

%%END

