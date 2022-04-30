# DeapLearning
Projet autodidacte etudiant sur le machine-learning et le deap-learning

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