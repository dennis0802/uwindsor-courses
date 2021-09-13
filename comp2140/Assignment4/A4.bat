del *.class A4.java A4.output A4Parser.java A4Symbol.java A4.lex.java A4.output
java JLex.Main A4.lex
java java_cup.Main -parser A4Parser -symbols A4Symbol A4.cup
javac A4.lex.java A4Parser.java A4Symbol.java A4User.java
java A4User
javac A4.java
java A4
more A4.output