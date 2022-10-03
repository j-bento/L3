########################################
#~ définitions
########################################

# Executables à générer
BIN=bin/seuil_2_parties bin/seuil_3_parties bin/seuil_4_parties\
 	bin/histo_couleur bin/test_couleur bin/histo_grey bin/profil

# liste des fichiers sources 
SRCS0=seuil_2_parties.cpp
SRCS1=seuil_3_parties.cpp
SRCS2=seuil_4_parties.cpp
SRCS3=test_couleur.cpp
SRCS4=histo_grey.cpp
SRCS5=histo_couleur.cpp
SRCS6=profil.cpp

default: $(BIN)

DIR_GUARD=@mkdir -p $(@D)
########################################
#~ regles pour l'executable
########################################

obj/%.o: %.cpp
	${DIR_GUARD}
	gcc -Wall -Iinclude -c $< -o $@

bin/seuil_2_parties: $(SRCS0:%.cpp=obj/%.o)
	${DIR_GUARD}
	gcc -o $@ $+

bin/seuil_3_parties: $(SRCS1:%.cpp=obj/%.o)
	${DIR_GUARD}
	gcc -o $@ $+

bin/seuil_4_parties: $(SRCS2:%.cpp=obj/%.o)
	${DIR_GUARD}
	gcc -o $@ $+

bin/test_couleur: $(SRCS3:%.cpp=obj/%.o)
	${DIR_GUARD}
	gcc -o $@ $+

bin/histo_grey: $(SRCS4:%.cpp=obj/%.o)
	${DIR_GUARD}
	gcc -o $@ $+

bin/histo_couleur: $(SRCS5:%.cpp=obj/%.o)
	${DIR_GUARD}
	gcc -o $@ $+

bin/profil: $(SRCS6:%.cpp=obj/%.o)
	${DIR_GUARD}
	gcc -o $@ $+

clean:
	rm -f $(BIN) obj/*.o *~ *.dat
