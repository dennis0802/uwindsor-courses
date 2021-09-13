import java_cup.runtime.*;


class A4Scanner implements java_cup.runtime.Scanner {
	private final int YY_BUFFER_SIZE = 512;
	private final int YY_F = -1;
	private final int YY_NO_STATE = -1;
	private final int YY_NOT_ACCEPT = 0;
	private final int YY_START = 1;
	private final int YY_END = 2;
	private final int YY_NO_ANCHOR = 4;
	private final int YY_BOL = 128;
	private final int YY_EOF = 129;
	private java.io.BufferedReader yy_reader;
	private int yy_buffer_index;
	private int yy_buffer_read;
	private int yy_buffer_start;
	private int yy_buffer_end;
	private char yy_buffer[];
	private boolean yy_at_bol;
	private int yy_lexical_state;

	A4Scanner (java.io.Reader reader) {
		this ();
		if (null == reader) {
			throw (new Error("Error: Bad input stream initializer."));
		}
		yy_reader = new java.io.BufferedReader(reader);
	}

	A4Scanner (java.io.InputStream instream) {
		this ();
		if (null == instream) {
			throw (new Error("Error: Bad input stream initializer."));
		}
		yy_reader = new java.io.BufferedReader(new java.io.InputStreamReader(instream));
	}

	private A4Scanner () {
		yy_buffer = new char[YY_BUFFER_SIZE];
		yy_buffer_read = 0;
		yy_buffer_index = 0;
		yy_buffer_start = 0;
		yy_buffer_end = 0;
		yy_at_bol = true;
		yy_lexical_state = YYINITIAL;
	}

	private boolean yy_eof_done = false;
	private final int YYINITIAL = 0;
	private final int COMMENT = 1;
	private final int yy_state_dtrans[] = {
		0,
		40
	};
	private void yybegin (int state) {
		yy_lexical_state = state;
	}
	private int yy_advance ()
		throws java.io.IOException {
		int next_read;
		int i;
		int j;

		if (yy_buffer_index < yy_buffer_read) {
			return yy_buffer[yy_buffer_index++];
		}

		if (0 != yy_buffer_start) {
			i = yy_buffer_start;
			j = 0;
			while (i < yy_buffer_read) {
				yy_buffer[j] = yy_buffer[i];
				++i;
				++j;
			}
			yy_buffer_end = yy_buffer_end - yy_buffer_start;
			yy_buffer_start = 0;
			yy_buffer_read = j;
			yy_buffer_index = j;
			next_read = yy_reader.read(yy_buffer,
					yy_buffer_read,
					yy_buffer.length - yy_buffer_read);
			if (-1 == next_read) {
				return YY_EOF;
			}
			yy_buffer_read = yy_buffer_read + next_read;
		}

		while (yy_buffer_index >= yy_buffer_read) {
			if (yy_buffer_index >= yy_buffer.length) {
				yy_buffer = yy_double(yy_buffer);
			}
			next_read = yy_reader.read(yy_buffer,
					yy_buffer_read,
					yy_buffer.length - yy_buffer_read);
			if (-1 == next_read) {
				return YY_EOF;
			}
			yy_buffer_read = yy_buffer_read + next_read;
		}
		return yy_buffer[yy_buffer_index++];
	}
	private void yy_move_end () {
		if (yy_buffer_end > yy_buffer_start &&
		    '\n' == yy_buffer[yy_buffer_end-1])
			yy_buffer_end--;
		if (yy_buffer_end > yy_buffer_start &&
		    '\r' == yy_buffer[yy_buffer_end-1])
			yy_buffer_end--;
	}
	private boolean yy_last_was_cr=false;
	private void yy_mark_start () {
		yy_buffer_start = yy_buffer_index;
	}
	private void yy_mark_end () {
		yy_buffer_end = yy_buffer_index;
	}
	private void yy_to_mark () {
		yy_buffer_index = yy_buffer_end;
		yy_at_bol = (yy_buffer_end > yy_buffer_start) &&
		            ('\r' == yy_buffer[yy_buffer_end-1] ||
		             '\n' == yy_buffer[yy_buffer_end-1] ||
		             2028/*LS*/ == yy_buffer[yy_buffer_end-1] ||
		             2029/*PS*/ == yy_buffer[yy_buffer_end-1]);
	}
	private java.lang.String yytext () {
		return (new java.lang.String(yy_buffer,
			yy_buffer_start,
			yy_buffer_end - yy_buffer_start));
	}
	private int yylength () {
		return yy_buffer_end - yy_buffer_start;
	}
	private char[] yy_double (char buf[]) {
		int i;
		char newbuf[];
		newbuf = new char[2*buf.length];
		for (i = 0; i < buf.length; ++i) {
			newbuf[i] = buf[i];
		}
		return newbuf;
	}
	private final int YY_E_INTERNAL = 0;
	private final int YY_E_MATCH = 1;
	private java.lang.String yy_error_string[] = {
		"Error: Internal error.\n",
		"Error: Unmatched input.\n"
	};
	private void yy_error (int code,boolean fatal) {
		java.lang.System.out.print(yy_error_string[code]);
		java.lang.System.out.flush();
		if (fatal) {
			throw new Error("Fatal Error.\n");
		}
	}
	private int[][] unpackFromString(int size1, int size2, String st) {
		int colonIndex = -1;
		String lengthString;
		int sequenceLength = 0;
		int sequenceInteger = 0;

		int commaIndex;
		String workString;

		int res[][] = new int[size1][size2];
		for (int i= 0; i < size1; i++) {
			for (int j= 0; j < size2; j++) {
				if (sequenceLength != 0) {
					res[i][j] = sequenceInteger;
					sequenceLength--;
					continue;
				}
				commaIndex = st.indexOf(',');
				workString = (commaIndex==-1) ? st :
					st.substring(0, commaIndex);
				st = st.substring(commaIndex+1);
				colonIndex = workString.indexOf(':');
				if (colonIndex == -1) {
					res[i][j]=Integer.parseInt(workString);
					continue;
				}
				lengthString =
					workString.substring(colonIndex+1);
				sequenceLength=Integer.parseInt(lengthString);
				workString=workString.substring(0,colonIndex);
				sequenceInteger=Integer.parseInt(workString);
				res[i][j] = sequenceInteger;
				sequenceLength--;
			}
		}
		return res;
	}
	private int yy_acpt[] = {
		/* 0 */ YY_NOT_ACCEPT,
		/* 1 */ YY_NO_ANCHOR,
		/* 2 */ YY_NO_ANCHOR,
		/* 3 */ YY_NO_ANCHOR,
		/* 4 */ YY_NO_ANCHOR,
		/* 5 */ YY_NO_ANCHOR,
		/* 6 */ YY_NO_ANCHOR,
		/* 7 */ YY_NO_ANCHOR,
		/* 8 */ YY_NO_ANCHOR,
		/* 9 */ YY_NO_ANCHOR,
		/* 10 */ YY_NO_ANCHOR,
		/* 11 */ YY_NO_ANCHOR,
		/* 12 */ YY_NO_ANCHOR,
		/* 13 */ YY_NO_ANCHOR,
		/* 14 */ YY_NO_ANCHOR,
		/* 15 */ YY_NO_ANCHOR,
		/* 16 */ YY_NO_ANCHOR,
		/* 17 */ YY_NO_ANCHOR,
		/* 18 */ YY_NO_ANCHOR,
		/* 19 */ YY_NO_ANCHOR,
		/* 20 */ YY_NO_ANCHOR,
		/* 21 */ YY_NO_ANCHOR,
		/* 22 */ YY_NO_ANCHOR,
		/* 23 */ YY_NO_ANCHOR,
		/* 24 */ YY_NO_ANCHOR,
		/* 25 */ YY_NO_ANCHOR,
		/* 26 */ YY_NO_ANCHOR,
		/* 27 */ YY_NOT_ACCEPT,
		/* 28 */ YY_NO_ANCHOR,
		/* 29 */ YY_NO_ANCHOR,
		/* 30 */ YY_NO_ANCHOR,
		/* 31 */ YY_NO_ANCHOR,
		/* 32 */ YY_NO_ANCHOR,
		/* 33 */ YY_NO_ANCHOR,
		/* 34 */ YY_NOT_ACCEPT,
		/* 35 */ YY_NO_ANCHOR,
		/* 36 */ YY_NO_ANCHOR,
		/* 37 */ YY_NOT_ACCEPT,
		/* 38 */ YY_NO_ANCHOR,
		/* 39 */ YY_NO_ANCHOR,
		/* 40 */ YY_NOT_ACCEPT,
		/* 41 */ YY_NO_ANCHOR,
		/* 42 */ YY_NOT_ACCEPT,
		/* 43 */ YY_NO_ANCHOR,
		/* 44 */ YY_NO_ANCHOR,
		/* 45 */ YY_NO_ANCHOR,
		/* 46 */ YY_NO_ANCHOR,
		/* 47 */ YY_NO_ANCHOR,
		/* 48 */ YY_NO_ANCHOR,
		/* 49 */ YY_NO_ANCHOR,
		/* 50 */ YY_NO_ANCHOR,
		/* 51 */ YY_NO_ANCHOR,
		/* 52 */ YY_NO_ANCHOR,
		/* 53 */ YY_NO_ANCHOR,
		/* 54 */ YY_NO_ANCHOR,
		/* 55 */ YY_NO_ANCHOR,
		/* 56 */ YY_NO_ANCHOR,
		/* 57 */ YY_NO_ANCHOR,
		/* 58 */ YY_NO_ANCHOR,
		/* 59 */ YY_NO_ANCHOR,
		/* 60 */ YY_NO_ANCHOR,
		/* 61 */ YY_NO_ANCHOR,
		/* 62 */ YY_NO_ANCHOR,
		/* 63 */ YY_NO_ANCHOR,
		/* 64 */ YY_NO_ANCHOR,
		/* 65 */ YY_NO_ANCHOR,
		/* 66 */ YY_NO_ANCHOR,
		/* 67 */ YY_NO_ANCHOR,
		/* 68 */ YY_NO_ANCHOR,
		/* 69 */ YY_NO_ANCHOR,
		/* 70 */ YY_NO_ANCHOR,
		/* 71 */ YY_NO_ANCHOR,
		/* 72 */ YY_NO_ANCHOR
	};
	private int yy_cmap[] = unpackFromString(1,130,
"32:9,33,20,32:2,20,32:18,33,31,19,32:5,26,27,22,23,25,23,18,21,17:10,28,24," +
"30,29,30,32:2,2,5,16,8,6,14,7,16,3,16:2,11,1,4,16:3,10,12,9,13,16,15,16:3,3" +
"2:6,16:26,32:5,0:2")[0];

	private int yy_rmap[] = unpackFromString(1,73,
"0,1,2,3,1:2,4,1:4,5,6,1:2,6:2,1,6:7,1:2,7,8,7,9,1:2,10,9,11,12,13,14,5,15,1" +
"6,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,6,40" +
",41,42,43,44,45,46")[0];

	private int yy_nxt[][] = unpackFromString(47,34,
"1,2,65,28,65,67,50,65:2,68,69,65,70,65,71,72,65,3,4,30,5,6,31:2,7,8,9,10,36" +
",39,11,39,4,5,-1:35,65,51,65:15,-1:33,3,27,-1:37,37,-1:40,32,-1:5,65:17,-1:" +
"33,29,-1:17,65:3,35,65:9,12,65:3,-1:17,34:18,13,34:14,-1:22,42,-1:12,65:8,1" +
"5,65:8,-1:45,14,-1:26,17,-1:12,65:7,16,65:9,-1:16,1,25:19,5,25,33,25:11,-1," +
"65:3,18,65:13,-1:37,26,-1:13,65:5,19,65:11,-1:17,65:5,20,65:11,-1:17,65:7,2" +
"1,65:2,15,65:6,-1:17,65:3,22,65:13,-1:17,65:5,23,65:11,-1:17,65:3,24,65:13," +
"-1:17,65:6,15,65:10,-1:17,65:3,38,65:6,53,65:6,-1:17,65:2,41,65:14,-1:17,65" +
":6,59,65:10,-1:17,65:11,43,65:5,-1:17,65:12,44,65:4,-1:17,65,45,65:6,60,65:" +
"8,-1:17,65:9,66,65:7,-1:17,65:10,61,65:6,-1:17,65:2,62,65:14,-1:17,65:2,46," +
"65:14,-1:17,65:12,63,65:4,-1:17,65:11,44,65:5,-1:17,65:8,47,65:8,-1:17,65:9" +
",48,65:7,-1:17,65:3,49,65:13,-1:17,65:2,64,65:14,-1:17,65:5,52,65:11,-1:17," +
"65:9,54,65:7,-1:17,65:5,55,65:11,-1:17,65:8,56,65:8,-1:17,65,57,65:15,-1:17" +
",65:9,58,65:7,-1:16");

	public Symbol next_token ()
		throws java.io.IOException {
		int yy_lookahead;
		int yy_anchor = YY_NO_ANCHOR;
		int yy_state = yy_state_dtrans[yy_lexical_state];
		int yy_next_state = YY_NO_STATE;
		int yy_last_accept_state = YY_NO_STATE;
		boolean yy_initial = true;
		int yy_this_accept;

		yy_mark_start();
		yy_this_accept = yy_acpt[yy_state];
		if (YY_NOT_ACCEPT != yy_this_accept) {
			yy_last_accept_state = yy_state;
			yy_mark_end();
		}
		while (true) {
			if (yy_initial && yy_at_bol) yy_lookahead = YY_BOL;
			else yy_lookahead = yy_advance();
			yy_next_state = YY_F;
			yy_next_state = yy_nxt[yy_rmap[yy_state]][yy_cmap[yy_lookahead]];
			if (YY_EOF == yy_lookahead && true == yy_initial) {
				return null;
			}
			if (YY_F != yy_next_state) {
				yy_state = yy_next_state;
				yy_initial = false;
				yy_this_accept = yy_acpt[yy_state];
				if (YY_NOT_ACCEPT != yy_this_accept) {
					yy_last_accept_state = yy_state;
					yy_mark_end();
				}
			}
			else {
				if (YY_NO_STATE == yy_last_accept_state) {
					throw (new Error("Lexical Error: Unmatched Input."));
				}
				else {
					yy_anchor = yy_acpt[yy_last_accept_state];
					if (0 != (YY_END & yy_anchor)) {
						yy_move_end();
					}
					yy_to_mark();
					switch (yy_last_accept_state) {
					case 1:
						
					case -2:
						break;
					case 2:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -3:
						break;
					case 3:
						{ return new Symbol(A4Symbol.NUMBER, yytext());}
					case -4:
						break;
					case 4:
						{return new Symbol(A4Symbol.error);}
					case -5:
						break;
					case 5:
						{}
					case -6:
						break;
					case 6:
						{ return new Symbol(A4Symbol.ARITH, yytext()); }
					case -7:
						break;
					case 7:
						{ return new Symbol(A4Symbol.SEMICOLON); }
					case -8:
						break;
					case 8:
						{ return new Symbol(A4Symbol.COMMA); }
					case -9:
						break;
					case 9:
						{ return new Symbol(A4Symbol.LPAREN); }
					case -10:
						break;
					case 10:
						{ return new Symbol(A4Symbol.RPAREN); }
					case -11:
						break;
					case 11:
						{return new Symbol(A4Symbol.BOOL, yytext());}
					case -12:
						break;
					case 12:
						{ return new Symbol(A4Symbol.IF); }
					case -13:
						break;
					case 13:
						{ return new Symbol(A4Symbol.QSTRING, yytext());}
					case -14:
						break;
					case 14:
						{ return new Symbol(A4Symbol.ASSIGN);}
					case -15:
						break;
					case 15:
						{ 
    if(yytext().equals("INT")){
        return new Symbol(A4Symbol.TYPE, "int"); 
    }
    else if(yytext().equals("STRING")){
        return new Symbol(A4Symbol.TYPE, "String"); 
    }
    return new Symbol(A4Symbol.TYPE, "double"); 
}
					case -16:
						break;
					case 16:
						{ return new Symbol(A4Symbol.END); }
					case -17:
						break;
					case 17:
						{yybegin(COMMENT);}
					case -18:
						break;
					case 18:
						{ return new Symbol(A4Symbol.MAIN); }
					case -19:
						break;
					case 19:
						{ return new Symbol(A4Symbol.ELSE); }
					case -20:
						break;
					case 20:
						{
    if(yytext().equals("TRUE")){
        return new Symbol(A4Symbol.BOOLVAL, "true");
    }
    return new Symbol(A4Symbol.BOOLVAL, "false");
}
					case -21:
						break;
					case 21:
						{ return new Symbol(A4Symbol.READ); }
					case -22:
						break;
					case 22:
						{ return new Symbol(A4Symbol.BEGIN); }
					case -23:
						break;
					case 23:
						{ return new Symbol(A4Symbol.WRITE); }
					case -24:
						break;
					case 24:
						{ return new Symbol(A4Symbol.RETURN); }
					case -25:
						break;
					case 25:
						{}
					case -26:
						break;
					case 26:
						{yybegin(YYINITIAL);}
					case -27:
						break;
					case 28:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -28:
						break;
					case 29:
						{ return new Symbol(A4Symbol.NUMBER, yytext());}
					case -29:
						break;
					case 30:
						{return new Symbol(A4Symbol.error);}
					case -30:
						break;
					case 31:
						{ return new Symbol(A4Symbol.ARITH, yytext()); }
					case -31:
						break;
					case 32:
						{return new Symbol(A4Symbol.BOOL, yytext());}
					case -32:
						break;
					case 33:
						{}
					case -33:
						break;
					case 35:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -34:
						break;
					case 36:
						{return new Symbol(A4Symbol.error);}
					case -35:
						break;
					case 38:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -36:
						break;
					case 39:
						{return new Symbol(A4Symbol.error);}
					case -37:
						break;
					case 41:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -38:
						break;
					case 43:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -39:
						break;
					case 44:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -40:
						break;
					case 45:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -41:
						break;
					case 46:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -42:
						break;
					case 47:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -43:
						break;
					case 48:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -44:
						break;
					case 49:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -45:
						break;
					case 50:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -46:
						break;
					case 51:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -47:
						break;
					case 52:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -48:
						break;
					case 53:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -49:
						break;
					case 54:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -50:
						break;
					case 55:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -51:
						break;
					case 56:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -52:
						break;
					case 57:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -53:
						break;
					case 58:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -54:
						break;
					case 59:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -55:
						break;
					case 60:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -56:
						break;
					case 61:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -57:
						break;
					case 62:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -58:
						break;
					case 63:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -59:
						break;
					case 64:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -60:
						break;
					case 65:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -61:
						break;
					case 66:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -62:
						break;
					case 67:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -63:
						break;
					case 68:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -64:
						break;
					case 69:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -65:
						break;
					case 70:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -66:
						break;
					case 71:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -67:
						break;
					case 72:
						{ return new Symbol(A4Symbol.ID, yytext());}
					case -68:
						break;
					default:
						yy_error(YY_E_INTERNAL,false);
					case -1:
					}
					yy_initial = true;
					yy_state = yy_state_dtrans[yy_lexical_state];
					yy_next_state = YY_NO_STATE;
					yy_last_accept_state = YY_NO_STATE;
					yy_mark_start();
					yy_this_accept = yy_acpt[yy_state];
					if (YY_NOT_ACCEPT != yy_this_accept) {
						yy_last_accept_state = yy_state;
						yy_mark_end();
					}
				}
			}
		}
	}
}
