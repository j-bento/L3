########################################
#~ définitions
########################################

# Executables à générer
BIN=bin/norme_gradient bin/test_grey bin/seuil_hysteresis

# liste des fichiers sources 
SRCS1=norme_gradient.cpp
SRCS2=test_grey.cpp
SRCS3=seuil_hysteresis.cpp
#librairies
LIB=-lm
default : $(BIN)
grad : bin/norme_gradient #pour pouvoir construire juste le gradient avec "make grad"
grey : bin/test_grey
hyst : bin/seuil_hysteresis
########################################
#~ regles pour l'executable
########################################

obj/%.o: %.cpp
	gcc -Wall -Iinclude -c $< -o $@

bin/norme_gradient: $(SRCS1:%.cpp=obj/%.o)
	gcc -o $@ $+ $(LIB)

bin/test_grey: $(SRCS2:%.cpp=obj/%.o)
	gcc -o $@ $+

bin/seuil_hysteresis: $(SRCS3:%.cpp=obj/%.o)
	gcc -o $@ $+

clean:
	rm -f $(BIN) obj/*.o *~ *.dat
