########################################
#~ définitions
########################################

BIN=bin/traitement bin/init
DIRG=@mkdir -p $(@D)

# liste des fichiers sources
SRCS0=traitement.c
SRCS1=init.c

default: $(BIN)

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.c
	$(DIRG)
	gcc -Wall -Iinclude -c $< -o $@

bin/traitement: $(SRCS0:%.c=obj/%.o)
	$(DIRG)
	gcc -o $@ $+

bin/init: $(SRCS1:%.c=obj/%.o)
	$(DIRG)
	gcc -o $@ $+

clean:
	rm -f $(BIN) obj/*.o *~