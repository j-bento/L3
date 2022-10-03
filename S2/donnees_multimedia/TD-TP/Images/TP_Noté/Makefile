########################################
#~ définitions
########################################

# Executables à générer
BIN=bin/exam bin/histo_grey bin/ddp bin/repartition bin/egalisation

# liste des fichiers sources 
SRCS1=exam.cpp
SRCS2=histo_grey.cpp
SRCS3=ddp.cpp
SRCS4=repartition.cpp
SRCS5=egalisation.cpp
default: $(BIN)

# complémentaire: warnings et dir guard
CFLAGS=-Wall -Iinclude
DIR_GUARD=@mkdir -p $(@D)
#librairies
LIB=-lm

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.c
	$(DIR_GUARD)
	gcc -Wall -Iinclude -c $< -o $@

bin/exam: $(SRCS1:%.c=obj/%.o)
	$(DIR_GUARD)
	gcc -o $@ $+

bin/histo_grey : $(SRCS2:%.c=obj/%.o)
	$(DIR_GUARD)
	gcc -o $@ $+

bin/ddp : $(SRCS3:%.c=obj/%.o)
	$(DIR_GUARD)
	gcc -o $@ $+

bin/repartition : $(SRCS4:%.c=obj/%.o)
	$(DIR_GUARD)
	gcc -o $@ $+

bin/egalisation : $(SRCS5:%.c=obj/%.o)
	$(DIR_GUARD)
	gcc -o $@ $+ $(LIB)

clean:
	rm -f $(BIN) obj/*.o *~ *.dat
