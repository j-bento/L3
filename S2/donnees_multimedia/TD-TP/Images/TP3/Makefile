########################################
#~ définitions
########################################

# Executables à générer
BIN=bin/profil bin/histo_grey bin/conversion_gris bin/inverse\
	bin/filtre_flou1 bin/filtre_flou2 bin/flou_couleur

# liste des fichiers sources 
SRCS1=histo_grey.cpp
SRCS2=conversion_gris.cpp
SRCS3=inverse.cpp
SRCS4=profil.cpp
SRCS5=filtre_flou1.cpp
SRCS6=filtre_flou2.cpp
SRCS7=flou_couleur.cpp

default: $(BIN)

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.cpp
	gcc -Wall -Iinclude -c $< -o $@

bin/histo_grey: $(SRCS1:%.cpp=obj/%.o)
	gcc -o $@ $+

bin/conversion_gris: $(SRCS2:%.cpp=obj/%.o)
	gcc -o $@ $+

bin/inverse: $(SRCS3:%.cpp=obj/%.o)
	gcc -o $@ $+

bin/profil: $(SRCS4:%.cpp=obj/%.o)
	gcc -o $@ $+

bin/filtre_flou1: $(SRCS5:%.cpp=obj/%.o)
	gcc -o $@ $+

bin/filtre_flou2: $(SRCS6:%.cpp=obj/%.o)
	gcc -o $@ $+

bin/flou_couleur: $(SRCS7:%.cpp=obj/%.o)
	gcc -o $@ $+

clean:
	rm -f $(BIN) obj/*.o *~ *.dat
