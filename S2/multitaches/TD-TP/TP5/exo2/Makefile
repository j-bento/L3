########################################
#~ définitions
########################################

BIN=bin/rdv	bin/suppr bin/semInit

# liste des fichiers sources
SRCS0=semInit.c
SRCS1=supprimeSem.c
SRCS2=rdv.c

default: $(BIN)

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.c
	gcc -Wall -Iinclude -c $< -o $@

bin/semInit: $(SRCS0:%.c=obj/%.o)
	gcc -o $@ $+

bin/suppr: $(SRCS1:%.c=obj/%.o)
	gcc -o $@ $+

bin/rdv: $(SRCS2:%.c=obj/%.o)
	gcc -o $@ $+


clean:
	rm -f $(BIN) obj/*.o *~