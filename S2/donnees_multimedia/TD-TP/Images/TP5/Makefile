########################################
#~ définitions
########################################

# Executables à générer
BIN = bin/RGBtoY bin/RGBtoYCbCr bin/difference bin/YCbCrtoRGB\
	  bin/YCbCrtoRBG bin/modifY

# liste des fichiers sources 
SRCS0=difference.cpp
SRCS1=RGBtoY.cpp
SRCS2=RGBtoYCbCr.cpp
SRCS3=YCbCrtoRGB.cpp
SRCS4=YCbCrtoRBG.cpp
SRCS5=modifY.cpp

# complémentaire: warnings et dir guard
CFLAGS=-Wall -Iinclude
DIR_GUARD=@mkdir -p $(@D)
#librairies
LIB=-lm
default : $(BIN)

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.cpp
	$(DIR_GUARD)
	gcc $(CFLAGS) -c $< -o $@

bin/difference: $(SRCS0:%.cpp=obj/%.o)
	$(DIR_GUARD)
	gcc -o $@ $+

bin/RGBtoY: $(SRCS1:%.cpp=obj/%.o)
	$(DIR_GUARD)
	gcc -o $@ $+

bin/RGBtoYCbCr: $(SRCS2:%.cpp=obj/%.o)
	$(DIR_GUARD)
	gcc -o $@ $+

bin/YCbCrtoRGB: $(SRCS3:%.cpp=obj/%.o)
	$(DIR_GUARD)
	gcc -o $@ $+

bin/YCbCrtoRBG: $(SRCS4:%.cpp=obj/%.o)
	$(DIR_GUARD)
	gcc -o $@ $+

bin/modifY: $(SRCS5:%.cpp=obj/%.o)
	$(DIR_GUARD)
	gcc -o $@ $+

clean:
	rm -f $(BIN) obj/*.o *~ *.dat
