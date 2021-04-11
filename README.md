# Quarto

    Polytech 3A Informatique année 2018/2019
    Tuteur : Mohammed HADDAD
    
    ![image](https://user-images.githubusercontent.com/31795527/114316180-c1e23780-9b02-11eb-9cba-306552b82270.png)


## Equipe

- ARMANET Nathan
- NAAJI Dorian

## Contexte

projet Algo et cpx S6

## Compilation

Pour compiler le projet, nous utilisons un *MakeFile* permettant d'éxécuter les commandes suivantes :
- **make** ou **make all**
    - compile l'éxécutable du projet (bin/quarto) avec toutes les dépendances (obj/*.o)
- **make clean**
    - supprime les fichiers .o du sous-dossier obj/
- **make veryclean**
    - supprime l'éxécutable dans le sous-dossier bin/
    - supprime les fichiers .o du sous-dossier obj/
