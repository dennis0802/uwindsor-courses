import java_cup.runtime.*;
%%

%implements java_cup.runtime.Scanner
%type Symbol
%function next_token
%class A4Scanner
%state COMMENT

%%
<YYINITIAL>"MAIN" { return new Symbol(A4Symbol.MAIN); }
<YYINITIAL>"BEGIN" { return new Symbol(A4Symbol.BEGIN); }
<YYINITIAL>"END" { return new Symbol(A4Symbol.END); }
<YYINITIAL>"INT"|"REAL"|"STRING" { 
    if(yytext().equals("INT")){
        return new Symbol(A4Symbol.TYPE, "int"); 
    }
    else if(yytext().equals("STRING")){
        return new Symbol(A4Symbol.TYPE, "String"); 
    }
    return new Symbol(A4Symbol.TYPE, "double"); 
}
<YYINITIAL>"RETURN" { return new Symbol(A4Symbol.RETURN); }
<YYINITIAL>"IF" { return new Symbol(A4Symbol.IF); }
<YYINITIAL>"ELSE" { return new Symbol(A4Symbol.ELSE); }
<YYINITIAL>"READ" { return new Symbol(A4Symbol.READ); }
<YYINITIAL>"WRITE" { return new Symbol(A4Symbol.WRITE); }
<YYINITIAL>"TRUE"|"FALSE" {
    if(yytext().equals("TRUE")){
        return new Symbol(A4Symbol.BOOLVAL, "true");
    }
    return new Symbol(A4Symbol.BOOLVAL, "false");
}

<YYINITIAL>[a-zA-Z][a-zA-Z0-9]* { return new Symbol(A4Symbol.ID, yytext());}
<YYINITIAL>[0-9]+(\.[0-9]+)? { return new Symbol(A4Symbol.NUMBER, yytext());}
<YYINITIAL>\"[^\"]*\" { return new Symbol(A4Symbol.QSTRING, yytext());}
<YYINITIAL>"/**" {yybegin(COMMENT);}

<YYINITIAL>"+"|"-"|"*"|"/" { return new Symbol(A4Symbol.ARITH, yytext()); }
<YYINITIAL>";" { return new Symbol(A4Symbol.SEMICOLON); }
<YYINITIAL>"," { return new Symbol(A4Symbol.COMMA); }
<YYINITIAL>"(" { return new Symbol(A4Symbol.LPAREN); }
<YYINITIAL>")" { return new Symbol(A4Symbol.RPAREN); }
<YYINITIAL>":=" { return new Symbol(A4Symbol.ASSIGN);}
<YYINITIAL>"=="|">="|"<="|"<"|">"|"!=" {return new Symbol(A4Symbol.BOOL, yytext());}

<COMMENT>"**/" {yybegin(YYINITIAL);}
<COMMENT>. {}

\r|\n|\t|" " {}
. {return new Symbol(A4Symbol.error);}