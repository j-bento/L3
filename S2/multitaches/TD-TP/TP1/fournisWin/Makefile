########################################
#~ définitions
########################################

# Executables à générer
BIN=bin/client  bin/serveur
# Objets à générer
OBJ=obj/client obj/serveur

# version windows
# BINW=bin\client.exe  bin\serveur.exe
# OBJW=obj\client.o obj\serveur.o

# liste des fichiers sources 
SRCS0=client.c
SRCS1=serveur.c
LIBS=-lwsock32
default: $(BIN)

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.c
	gcc -Wall -Iinclude -c $< -o $@ 
#$(LIBS)

bin/client: $(SRCS0:%.c=obj/%.o)
	gcc -o $@ $+ $(LIBS)

bin/serveur: $(SRCS1:%.c=obj/%.o)
	gcc -o $@ $+ $(LIBS)

#version unix:
#clean:
# 	rm -f $(BIN) obj/*.o *~

#version windows:
clean:
	del /f "obj\*.o" "bin\*.exe" 
#	del /f $(BINW) $(OBJW)
