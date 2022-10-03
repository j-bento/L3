########################################
#~ définitions
########################################

# Executables à générer
BIN=bin/grey bin/erosion bin/dilatation bin/fermeture bin/ouverture bin/difference
# bin/couleur 

# liste des fichiers sources 
SRCS0=test_grey.cpp
SRCS1=erosion.cpp
SRCS2=dilatation.cpp
SRCS3=fermeture.cpp
SRCS4=ouverture.cpp
SRCS5=difference.cpp
default: $(BIN)
all : default
grey : bin/grey
eros : bin/erosion
dilat : bin/dilat
ferm : bin/fermeture
ouv : bin/ouverture
diff : bin/difference
########################################
#~ regles pour l'executable
########################################

obj/%.o: %.cpp
	gcc -Wall -Iinclude -c $< -o $@

bin/grey: $(SRCS0:%.cpp=obj/%.o)
	gcc -o $@ $+

bin/erosion: $(SRCS1:%.cpp=obj/%.o)
	gcc -o $@ $+

bin/dilatation: $(SRCS2:%.cpp=obj/%.o)
	gcc -o $@ $+

bin/fermeture: $(SRCS3:%.cpp=obj/%.o)
	gcc -o $@ $+

bin/ouverture: $(SRCS4:%.cpp=obj/%.o)
	gcc -o $@ $+

bin/difference: $(SRCS5:%.cpp=obj/%.o)
	gcc -o $@ $+

clean:
	rm -f $(BIN) obj/*.o *~ *.dat
