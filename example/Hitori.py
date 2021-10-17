from random import randint
from upemtk import *
import os



# FONCTIONS DE LA TACHE 1

def lire_grille(nom_fichier):
    '''Fonction qui permet de lire une grille à partir d'un fichier externe'''
    lst=[]
    f=open(nom_fichier, "r")
    contenu=f.readlines()
    for elem in contenu:
        c=elem.split()
        lst.append(c)
    f.close()
    for i in range(len(lst)):
        for j in range(len(lst[i])):
            lst[i][j]=int(lst[i][j])
    return lst


def affiche_grille(ldl):
    '''Fonction permettant d'afficher la grille dans la console'''
    for i in range(len(ldl)):
        lst=ldl[i]*1
        for j in range(len(lst)):
            lst[j]=str(lst[j])
        s=" "
        print(s.join(lst))
        

def ecrire_grille(grille,nom_fichier):
    '''Fonction permettant d'ecrire une grille sur un fichier externe'''
    f=open(nom_fichier, "w")
    x=0
    for ligne in grille:
        if x>0:
            f.write("/n")
        for i in range(len(ligne)-1):
            f.write(str(ligne[i] + ' '))
        x+=1
    f.close()
            

# FONCTIONS DE LA TACHE 2

def sans_conflit(grille, noircies):
    '''Fonction vérifiant le nombre d'occurence sur chaque ligne et colonne d'une valeur, qui renvoie False si il y a des doublons sur une ligne et/ou colonne, et True sinon'''
    colonne=[]
    ligne=[]
    for i in range(len(grille)):
        for j in range(len(grille[i])):
            ligne.append(grille[i][j])
            if (i, j) in noircies:
                ligne.remove(grille[i][j])
            if ligne.count(grille[i][j])>1:
                return False
        ligne=[]
    for a in range(len(grille)):
        for b in range(len(grille[a])):
            colonne.append(grille[b][a])
            if (b, a) in noircies:
                colonne.remove(grille[b][a])
        for k in range(len(colonne)):
            if colonne.count(colonne[k])>1:

                return False
        colonne=[]
    return True
    
    
def Sans_voisines_noircies(grille, noircies):
    '''Fonction qui renvoie False si deux cases noires sont collées, True sinon'''
    for ligne in range(len(grille)):
        for colonne in range(len(grille[ligne])):

            if (ligne, colonne) not in noircies:
                continue

            if (ligne, colonne) in noircies:
                
                if ligne>0 and (ligne-1, colonne) in noircies:
                    return False
                if ligne<len(grille) and (ligne+1, colonne) in noircies:
                    return False

                if colonne>0 and (ligne, colonne-1) in noircies:
                    return False
                if colonne<len(grille[ligne]) and (ligne, colonne+1) in noircies:
                    return False
    return True
    


def limite_grille(grille, ligne, colonne):
    '''renvoit True si la case est dans le plateau, False sinon'''
    return ((0<=ligne<len(grille)) and 0<=colonne<len(grille[ligne]))    


def voisins(ligne, colonne):
    return [(ligne+1, colonne), 
            (ligne,colonne+1), 
            (ligne-1, colonne), 
            (ligne, colonne-1)]


def colorier(grille, ligne, colonne, c_nouv):
    '''fonction récursive permettant de propager un nombre'''
    c_prec=grille[ligne][colonne]
    if c_prec==c_nouv:
        return
    grille[ligne][colonne]=c_nouv
    for vi, vj in voisins(ligne, colonne):
        if (limite_grille(grille, vi, vj) and grille[vi][vj]==c_prec):
            colorier(grille, vi, vj, c_nouv)
            
def connexe(plateau, noircies):
    '''créer un plateau et le remplit en fonction de la noirceur des cases; la fonction 'colorie' récursivement les zones non noircies, si les zones blanches forment une zone, elle renvoie True, False sinon.'''
    plateau2=[]
    for ligne in range(len(plateau)):
        plateau2.append([])
        for colonne in range(len(plateau[ligne])):
            if (ligne, colonne) in noircies:
                plateau2[ligne].append(0)
            else:
                plateau2[ligne].append(1)
    c_nouv=2
    rand_colonne=randint(0, len(plateau2[0])-1)
    rand_ligne=randint(0, len(plateau2)-1)
    while plateau2[rand_ligne][rand_colonne]!=1:
        rand_colonne=randint(0, len(plateau2[0])-1)
    colorier(plateau2, rand_ligne, rand_colonne, c_nouv)
    for ligne1 in range(len(plateau2)):
        for colonne1 in range(len(plateau2[ligne1])):
            if plateau2[ligne1][colonne1]==1:
                return False
    return True
    

#FONCTIONS DE LA TACHE 3

def menu():
    rectangle(20,20,580,100, couleur="red",remplissage="red" ,epaisseur=3)
    texte(125,45, "Projet d'AP2 : HITORI", couleur="black")
    texte(100, 250,"Bienvenue sur notre jeu !")
    rectangle(20, 400, 580, 500, couleur="green", remplissage="green", epaisseur=3)
    texte(38, 430, "Cliquez pour selectionner une grille ! :D", taille=23, couleur="white")
        
        
def menu_grille():
    rectangle(0,0,600,600, remplissage="snow")
    texte(175,15, "Choix de la grille")
    rectangle(80,100,520,150, remplissage="green")
    texte(230,105,"Niveau 1")
    rectangle(80, 200, 520, 250, remplissage="yellow")
    texte(230,205,"Niveau 2")
    rectangle(80, 300, 520, 350, remplissage="orange")
    texte(230, 305, "Niveau 3")
    rectangle(80, 400, 520, 450, remplissage="tomato")
    texte(230, 405, "Niveau 4")
    rectangle(80, 500, 520, 550, remplissage="red")
    texte(230, 505, "Niveau 5")
    
    
def menu_mode():
    rectangle(20,20,580,100, remplissage="blue")
    texte(115, 40, "Choix du mode de jeu :", couleur="white", taille=27)
    rectangle(100,175,500,230, remplissage="snow")
    texte(200,185,"Mode Manuel")
    rectangle(100,275,500,330, remplissage="snow")
    texte(200,285,"Solveur naïf")
    rectangle(100,375,500,430, remplissage="snow")
    texte(180,385,"Solveur avancé")
    

def menu_pause():
    i=0
    rectangle(100,145,500,200, remplissage="snow")
    texte(113,155 ,"Charger une nouvelle grille")
    rectangle(100,245,500,300, remplissage="snow")
    texte(190, 255, "Recommencer")
    rectangle(100,345,500,400, remplissage="snow")
    texte(240, 360, "Quitter")
    texte(225,15,"PAUSE",couleur="red", taille=30)
        
    
        
def dico_couleurs():
    '''créé un dictionnaire qui à chaque nombre donne comme valeurs une couleur'''
    dico={}
    couleurs=["red", "yellow", "purple", "pink", "green", "grey", "brown", "blue", "orange", "magenta"]
    for i in range(len(couleurs)):
        dico[i]=couleurs[i]
    return dico
    
def come_back(grille, grille2, noircies, ligne, colonne):
    ax, ay, bx, by=case_vers_pixel(ligne, colonne)
    if grille2[ligne][colonne]==0:
        rectangle(ay, ax, by, bx, tag='jeu')
        texte(ligne*taille_case+taille_case/3+.5, colonne* taille_case+taille_case/3+.5, grille[ligne][colonne])

def creer_grille(grille):
    '''permet de créer la grille graphiquement'''
    taille_case=600/len(grille)
    dico={}
    couleurs=["red", "yellow", "purple", "pink", "green", "grey", "brown", "blue", "orange", "magenta"]
    for k in range(len(couleurs)):
        dico[k]=couleurs[k]
    for i in range(len(grille)):
        for j in range(len(grille[i])):
            rectangle(j*taille_case, i*taille_case,(j+1)*taille_case, (i+1)*taille_case,remplissage=dico[grille[i][j]],tag='jeu')
            
def pixel_vers_case(x, y):
    '''fonction qui convertit des coordonnées en une case de la grille'''
    return (y//taille_case, x//taille_case) 
    
def placer_grille(grille):
    '''Fonction qui place les nombres de la grille dans la bonne case'''
    taille_case=600/len(grille)
    for i in range(len(grille)):
        for j in range(len(grille[i])):
            texte(i*taille_case+taille_case/3+.5, j* taille_case+taille_case/3+.5, grille[j][i])


        
def case_noircies(grille, grille2, noircies, ligne, colonne, dico):
    
    ligne, colonne=int(ligne), int(colonne)
    if grille2[ligne][colonne]==0:
        grille2[ligne][colonne]=1
        noircies.add((ligne, colonne))
    elif grille2[ligne][colonne]==1:
        grille2[ligne][colonne]=0
        noircies.discard((ligne, colonne))
        i, j=ligne, colonne
        ax, ay, bx, by=case_vers_pixel(ligne, colonne)
        rectangle(ay, ax, by, bx, remplissage=dico[grille[i][j]],tag='jeu')
        placer_grille(grille)

def case_vers_pixel(x, y):
    '''Fonction permettant de convertir une case en ses coordonnéees'''
    return x*taille_case, y*taille_case, (x+1)*taille_case, (y+1)*taille_case

def creer_grille2(grille):
    '''Fonction qui crée une deuxieme liste dans laquelle 0 correspond à case une non-noircie et 1 correspond à une case noircie'''
    grille2=[]
    for ligne in range(len(grille)):
        grille2.append([])
        for colonne in range(len(grille[ligne])):
            grille2[ligne].append(0)
    return grille2

def noirceur(grille2, ligne, colonne):
    '''Fonction qui noircie les cases selectionnées'''
    ax, ay, bx, by=case_vers_pixel(ligne, colonne)
    if grille2[ligne][colonne]==1:
        rectangle(ay, ax, by, bx, remplissage='black', tag='jeu')

def choix_grille(x, y):
    '''Fonction permettant de choisir sa grille lors du menu'''
    if 80<x<520 and 100<y<150:
        grille=lire_grille('niveau1.txt')
        taille_case=600/len(grille)
        grille2=creer_grille2(grille)
    elif 80<x<520 and 200<y<250:
        grille=lire_grille('niveau2.txt')
        taille_case=600/len(grille)
        grille2=creer_grille2(grille)
    elif 80<x<520 and 300<y<350:
        grille=lire_grille('niveau3.txt')
        taille_case=600/len(grille)
        grille2=creer_grille2(grille)
    elif 80<x<520 and 400<y<450:
        grille=lire_grille('niveau4.txt')
        taille_case=600/len(grille)
        grille2=creer_grille2(grille)
    elif 80<x<520 and 500<y<550:
        grille=lire_grille('niveau5.txt')
        taille_case=600/len(grille)
        grille2=creer_grille2(grille)
    return grille, taille_case, grille2
        
def gagne():
    '''Message qui s'affiche lorsque l'utilisateur gagne'''
    i=0
    rectangle(50,15,550,105,remplissage="red")
    texte(220,200,"Bravo !", taille=30)
    texte(80, 300, "Vous avez résolu la grille", taille = 30)
    while i<=15:
        if i%2==0:
            texte(120,25,"VICTOIRE !",couleur="black", taille=50)
        else:
            texte(120,25,"VICTOIRE !",couleur="white", taille=50)
        i+=1
        attente(0.5)
        
# FONCTIONS DE LA TACHE 4

def solveur_naif(grille, noircies, i, j):
    '''Fonction récursive permettant de résoudre une grille donnée mais qui prend du temps car ce n'est pas une méthode optimisée'''
    if not (Sans_voisines_noircies(grille,noircies) and connexe(grille, noircies)):
        return None
    elif sans_conflit(grille, noircies) and Sans_voisines_noircies(grille, noircies) and connexe(grille, noircies):
        return noircies
    else:
        if i < len(grille):
            grille_copie = grille*1
            for elem in noircies:
                (a, b) = elem
                grille_copie[a][b] = None
            colonne_copie = [[colonne[x] for colonne in grille_copie] for x in range(len(grille_copie[0]))]
            if grille_copie.count(grille[i][j]) == 1 and colonne.count(grille[i][j]) == 1 and grille_copie[i][j] != None:
                if j == len(grille[0])-1:
                    return solveur_naif(grille, noircies, i + 1, 0)
                else:
                    return solveur_naif(grille, noircies, i, j+1)
            else:
                noircies.add((i, j))
                if j == len(grille[0]) - 1:
                    sol = solveur_naif(grille, noircies, i + 1, 0)
                else:
                    sol = solveur_naif(grille, noircies, i, j + 1)

                if sol is not None:
                    return sol
                else:
                    noircies.discard((i, j))
                    if j == len(grille[0])-1:
                        sol = solveur_naif(grille, noircies, i+1, 0)
                    else:
                        sol = solveur_naif(grille, noircies, i, j+1)
                    if sol is not None:
                        return sol
                    else:
                        return None
#TACHES OPTIONNELS : (Essai)
def solveur_conflit(grille, noircies, i ,j):
    if Sans_voicines_noircies(grille, noircies)==False or connexe(grille, noircies)==False:
        return None
    elif sans_conflit(grille, noircies) and Sans_voisines_noircies(grille, noircies) and connexe(grille, noircies):
        return noircies
    else:
        liste_ligne=[]
        liste_colonne=[]
        #if i < len(grille):
        for i in range(len(grille)):
            liste_ligne.append([])
            liste_colonne.append([])
            grille_copie = grille*1
            print(grille_copie)
            for elem in noircies:
                (a, b) = elem
                grille_copie[a][b] = None
            colonne_copie = [[colonne[x] for colonne in grille_copie] for x in range(len(grille_copie[0]))]
            print(colonne_copie)
       
            for y in range(len(grille_copie[i])):
                print(grille_copie[i].count(grille_copie[i][y]))
                if grille_copie[i].count(grille_copie[i][y])>1 and grille_copie[i][y] != None:
                    liste_ligne[i].append((i, y))
                if colonne_copie[i].count(colonne_copie[i][y])>1 and colonne_copie[i][y]!= None:
                    liste_colonne[i].append((i, y))
        if len(liste_ligne)!=0:
            i=liste_ligne[0][0][1]
            j=liste_ligne[0][0][1]
        elif len(liste_ligne)==0 and len(liste_colonne)!=0:
            i=liste_colonne[0][0][0]
            j=liste_colonne[0][0][1]
        
        if (i, j) in liste_ligne and (i, j) in liste_colonne:
            liste_ligne[i].remove((i, j))
            liste_colonne[i].remove((i, j))
            for elem in liste_ligne:
                noircies.add([elem])
            for elem2 in liste_colonne:
                noircies.add([elem2])
            if len(liste_ligne)!=0:
                sol=solveur_conflit(grille, noircies, liste_ligne[0][0], liste_ligne[0][1])
            elif len(liste_ligne)==0 and len(liste_colonne)!=0:
                sol=solveur_conflit(grille, noircies, liste_colonne[0][0], liste_colonne[0][1])
            
        elif (i, j) in liste_ligne and (i, j) not in liste_colonne:
            liste_ligne[i].remove((i, j))
            for elem in liste_ligne:
                noircies.add([elem])
            if len(liste_ligne)!=0:
                sol=solveur_conflit(grille, noircies, liste_ligne[0][0], liste_ligne[0][1])
            elif len(liste_ligne)==0 and len(liste_colonne)!=0:
                sol=solveur_conflit(grille, noircies, liste_colonne[0][0], liste_colonne[0][1])
            
        elif (i, j) in liste_colonne and (i, j) not in liste_ligne:
            liste_colonne[i].remove((i, j))
            for elem in liste_colonne:
                noircies.add([elem])
            if len(liste_ligne)!=0:
                sol=solveur_conflit(grille, noircies, liste_ligne[0][0], liste_ligne[0][1])
            elif len(liste_ligne)==0 and len(liste_colonne)!=0:
                sol=solveur_conflit(grille, noircies, liste_colonne[0][0], liste_colonne[0][1])
            
        if sol is not None:
            return sol
        else:
            for elem in noircies:
                noircies.remove(elem)
            if len(liste_ligne)!=0:
                sol=solveur_conflit(grille, noircies, liste_ligne[0][0], liste_ligne[0][1])
            elif len(liste_ligne)==0 and len(liste_colonne)!=0:
                sol=solveur_conflit(grille, noircies, liste_colonne[0][0], liste_colonne[0][1])
            
            if sol is not None:
                return sol
            else:
                return None

# PROGRAMME PRINCIPAL :
couleurs=dico_couleurs()
noircies=set()
cree_fenetre(600,600)
menu()
attend_clic_gauche()
efface_tout()
menu_grille()
x,y=attend_clic_gauche()
#grille=[[2,2,1,5,3], [2,3,1,4,5], [1,1,1,3,5], [1,3,5,4,2], [5,4,3,2,1]] #à tester pour le solveur
#taille_case=600/len(grille)#a tester pour le solveur
#grille2=creer_grille2(grille)
while not ((80<x<520) and (100<y<150) or (200<y<250) or (300<y<350) or (400<y<450) or (500<y<550)):
    x, y = attend_clic_gauche()
grille, taille_case, grille2=choix_grille(x, y)
efface_tout()
menu_mode()
x, y = attend_clic_gauche()
while not ((100<x<500) and (175<y<230) or (275<y<330) or (375<y<430)):
    x, y = attend_clic_gauche()
if 100<x<500 and 175<y<230:
    efface_tout()
    creer_grille(grille)
    placer_grille(grille)
    
    while not (connexe(grille, noircies) and Sans_voisines_noircies(grille, noircies) and sans_conflit(grille, noircies)):
        
        ev=attend_ev()
        
        if "p"==touche(ev):
            efface_tout()
            menu_pause()
            x, y = attend_clic_gauche()
            if 100<x<500 and 145<y<200:
                efface_tout()
                menu_grille()
                x, y = attend_clic_gauche()
                while not ((80<x<520) and (100<y<150) or (200<y<250) or (300<y<350) or (400<y<450) or (500<y<550)):
                    x, y = attend_clic_gauche()
                grille, taille_case, grille2=choix_grille(x,y)
                noircies.clear()
                
                efface_tout()
                creer_grille(grille)
                placer_grille(grille)
                grille2=creer_grille2(grille)
            elif 100<x<500 and 245<y<300:
                noircies.clear()
                creer_grille(grille)
                placer_grille(grille)
            elif 100<x<500 and 345<y<400:
                ferme_fenetre()
        elif type_ev(ev)=="ClicGauche":
            x, y = attend_clic_gauche()
            ligne, colonne=pixel_vers_case(x, y)
            ligne, colonne=int(ligne), int(colonne)
            case_noircies(grille, grille2, noircies, ligne, colonne, couleurs)
            noirceur(grille2, ligne, colonne)
    efface_tout()
    gagne()
if 100<x<500 and 275<y<330:
    efface_tout()
    creer_grille(grille)
    placer_grille(grille)
    a=solveur_naif(grille, noircies, 0, 0)
    lst=list(a)
    for elem in lst:
        ax, ay, bx, by = case_vers_pixel(elem[1], elem[0])
        rectangle(ax, ay, bx, by, remplissage="black")
if 100<x<500 and 375<y<430:
    pass
    
attend_fermeture()


