# $@ says to put the output of the compilation in the file named on the left side of the :
# $< is the first item in the dependencies list
LIBS=-lfl
WC=wc
BLANCS=delblancs
MDC=mdconverter
default:
	


$(BLANCS): lex.yy.c
	gcc -o $@ $< $(LIBS)

$(MDC): lex.yy.c
	gcc -o $@ $< $(LIBS)

$(WC): lex.yy.c
	gcc -o $@ $< $(LIBS)

lex.yy.c: $(WC).l
	flex $<
	
lex.yy.c: $(BLANCS).l
	flex $<

lex.yy.c: $(MDC).l
	flex $<

clean: 
	rm lex.yy.c wc mdconverter delblancs lex.yy.c *.o 