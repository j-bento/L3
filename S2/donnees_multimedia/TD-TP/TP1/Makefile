########################################
#~ définitions
########################################

# Executables à générer
BIN=bin/histo_grey bin/histo_couleur bin/couleur bin/grey bin/profil

# liste des fichiers sources 
SRCS0=histo_grey.cpp
SRCS1=histo_couleur.cpp
SRCS2=test_couleur.cpp
SRCS3=test_grey.cpp
SRCS4=profil.cpp

default: $(BIN)

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.cpp
	gcc -Wall -Iinclude -c $< -o $@

bin/histo_grey: $(SRCS0:%.cpp=obj/%.o)
	gcc -o $@ $+

bin/histo_couleur: $(SRCS1:%.cpp=obj/%.o)
	gcc -o $@ $+

bin/couleur: $(SRCS2:%.cpp=obj/%.o)
	gcc -o $@ $+

bin/grey: $(SRCS3:%.cpp=obj/%.o)
	gcc -o $@ $+

bin/profil: $(SRCS4:%.cpp=obj/%.o)
	gcc -o $@ $+

clean:
	rm -f $(BIN) obj/*.o *~ *.dat *.pgm *.ppm
