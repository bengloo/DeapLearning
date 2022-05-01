# DeapLearning
Projet autodidacte etudiant sur le machine-learning et le deap-learning
fais sous linux 

V3: regression lineaire modéle un couche lineaire

V4: regression polynomiale mulicouche multineurones

# diferent parametres sont réglable et son défint dans le fichier setting.h
(nombre de neurone,couche,data,paramétre,iteration;fonction d'activation,type de donné,bornes)

# compilation en mode debug
-définir debug dans setting
-instalé les paquet cmake et valgrind si besoin
-dans le ficher build:
    vidé le dossier build si besoin
    cmake -DTYPE=Debug ..
    make
    valgrind ./Deeplearning

# compilation normal
-commenté le deffine debug dans setting
-instalé le paquet cmake
-dans le ficher build:
    vidé le dossier build si besoin
    cmake
    make
    ./Deeplearning

# fichier de log et encodage ANSI
si vous redirigé le procesus vert un fichier :.\Deaplearning>res.ansi
Vous n'aurais pas l'interpretation de l'encodage ansi faite naturelement par le terminal
Personellement j'utilise le mode Priview de l'extension ANSI colore de Visual studio Code