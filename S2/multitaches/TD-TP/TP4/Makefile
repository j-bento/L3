BIN=bin/exo1 bin/client bin/serveur bin/rdv bin/traitementImage bin/tests

LIB=-lpthread
CALC=./calcul/calculC.o
CALCPP=./calcul/calculCC.o
SRCS0=exo1.c
SRCS1=client.c
SRCS2=serveur.c
SRCS3=rdv.c
SRCS4=traitementImage.c
SRCS5=tests.c

default: $(BIN)
DIR_GUARD=@mkdir -p $(@D)

obj/%.o: %.c
	$(DIR_GUARD)
	gcc -Wall -Iinclude -c $< -o $@

bin/exo1 : $(SRCS0:%.c=obj/%.o)
	$(DIR_GUARD)
	gcc $(CALC) -o $@ $+ $(LIB)

bin/client : $(SRCS1:%.c=obj/%.o)
	$(DIR_GUARD)
	gcc -o $@ $+
	
bin/serveur : $(SRCS2:%.c=obj/%.o)
	$(DIR_GUARD)
	gcc -o $@ $+ $(LIB)

bin/rdv : $(SRCS3:%.c=obj/%.o)
	$(DIR_GUARD)
	gcc $(CALC) -o $@ $+ $(LIB)

bin/traitementImage : $(SRCS4:%.c=obj/%.o)
	$(DIR_GUARD)
	gcc $(CALC) -o $@ $+ $(LIB)

bin/tests : $(SRCS5:%.c=obj/%.o)
	$(DIR_GUARD)
	gcc $(CALC) -o $@ $+ $(LIB)

clean :
	rm -f *.o *~ $(BIN)