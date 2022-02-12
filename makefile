#Makfile conçus le 29/6/2020 par bengloo
#a pour bute de simplifier la gestion des library et la compilation."
# all: mkpile par defaut
# Debug: active les printf spécifique au mod debug
# clean: retire les.o du dossier

#////////recette par defaut//////////
c=gcc #type de compilation
op=-Wall -Wextra #opertion et retoure de la compilation
EXEC=main #nom de l'executable final
MAINSOURCE=main.o#fichier source de l'executable
LIBFIC=math.o #nom des library en .o
HEADERFIC=math.h#nom des header
#création de l'executable commenter le rm pour les compilation lourde 
all : $(MAINSOURCE) $(LIBFIC)
	$(c) $(MAINSOURCE) $(LIBFIC) -o $(EXEC)
	rm -rf *.o 
#activer mode debug défini dans ma lib utile
debug:DEBUG=-D'__DEBUG__'
debug:all

#inclusion des headers
$(MAINSOURCE): $(HEADERFIC)

#compilation des library
%.o: %.c
	$(c) -c $< -o $@ $(op) $(DEBUG)

# suppression des fichiers temporaires
clean:
	rm -rf *.o
 
# suppression de tous les fichiers, sauf les sources,
# en vue d'une reconstruction complète
mrproper: clean
	rm -rf $(EXEC)


