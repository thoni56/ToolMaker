letter		[A-Za-z]
string_element	['][']|[ -&(-~\t]
digit		[0-9]
digit_sequence	{digit}+
exponent	[Ee][+\-]?{digit_sequence}

%%

{letter}({letter}|{digit}|"_")*				{return 1;}
[']{string_element}[']					{return 1;}
[']{string_element}{string_element}+[']|['][']		{return 1;}
{digit_sequence}					{return 1;}
{digit_sequence}"."{digit_sequence}{exponent}?|{digit_sequence}{exponent}	{return 1;}
"+"							{return 1;}
"-"							{return 1;}
";"							{return 1;}
","							{return 1;}
"="							{return 1;}
"("							{return 1;}
")"							{return 1;}
":"							{return 1;}
"."							{return 1;}
"*"							{return 1;}
"<"							{return 1;}
">"							{return 1;}
".."							{return 1;}
"<>"							{return 1;}
"<="							{return 1;}
">="							{return 1;}
":="							{return 1;}
"^"|"@"							{return 1;}
"["|"(."							{return 1;}
"]"|".)"							{return 1;}
[Oo][Ff]							{return 1;}
[Oo][Rr]							{return 1;}
[Ii][Nn]							{return 1;}
[Ii][Ff]							{return 1;}
[Dd][Oo]							{return 1;}
[Tt][Oo]							{return 1;}
[Vv][Aa][Rr]							{return 1;}
[Ee][Nn][Dd]							{return 1;}
[Ss][Ee][Tt]							{return 1;}
[Nn][Ii][Ll]							{return 1;}
[Nn][Oo][Tt]							{return 1;}
[Dd][Ii][Vv]							{return 1;}
[Mm][Oo][Dd]							{return 1;}
[Aa][Nn][Dd]							{return 1;}
[Ff][Oo][Rr]							{return 1;}
[Tt][Yy][Pp][Ee]						{return 1;}
[Cc][Aa][Ss][Ee]						{return 1;}
[Ff][Ii][Ll][Ee]						{return 1;}
[Gg][Oo][Tt][Oo]						{return 1;}
[Tt][Hh][Ee][Nn]						{return 1;}
[Ee][Ll][Ss][Ee]						{return 1;}
[Ww][Ii][Tt][Hh]						{return 1;}
[Ll][Aa][Bb][Ee][Ll]						{return 1;}
[Cc][Oo][Nn][Ss][Tt]						{return 1;}
[Aa][Rr][Rr][Aa][Yy]						{return 1;}
[Bb][Ee][Gg][Ii][Nn]						{return 1;}
[Uu][Nn][Tt][Ii][Ll]						{return 1;}
[Ww][Hh][Ii][Ll][Ee]						{return 1;}
[Pp][Aa][Cc][Kk][Ee][Dd]					{return 1;}
[Rr][Ee][Cc][Oo][Rr][Dd]					{return 1;}
[Rr][Ee][Pp][Ee][Aa][Tt]					{return 1;}
[Dd][Oo][Ww][Nn][Tt][Oo]					{return 1;}
[Pp][Rr][Oo][Gg][Rr][Aa][Mm]					{return 1;}
[Ff][Uu][Nn][Cc][Tt][Ii][Oo][Nn]				{return 1;}
[Pp][Rr][Oo][Cc][Ee][Dd][Uu][Rr][Ee]				{return 1;}
[\001- ~-\177]+							;
("(*"|"{")(")"|"*"*([\001-(+-|~]))*("*"+")"|"*"*"}")		;
%%
