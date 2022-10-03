########################################
#~ définitions
########################################

BIN=bin/Pi  bin/Pctrl bin/suppr

# liste des fichiers sources
SRCS0=Pi.cc
SRCS1=Pctrl.cc
SRCS3=supprimeFile.cc

default: $(BIN)
DIR_GUARD=@mkdir -p $(@D)
########################################
#~ regles pour l'executable
########################################

obj/%.o: %.cc
	$(DIR_GUARD)
	g++ -Wall -Iinclude -c $< -o $@

bin/Pi: $(SRCS0:%.c=obj/%.o)
	$(DIR_GUARD)
	g++ -o $@ $+

bin/Pctrl: $(SRCS1:%.c=obj/%.o)
	$(DIR_GUARD)
	g++ -o $@ $+

bin/suppr: $(SRCS3:%.c=obj/%.o)
	$(DIR_GUARD)
	g++ -o $@ $+


clean:
	rm -f $(BIN) obj/*.o *~
