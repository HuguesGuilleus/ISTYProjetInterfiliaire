# -*- coding: utf-8 -*-
import cv2
import numpy as np
import time
import sys

WINDOW_NAME = 'BallTracker' 

def track(image,color):

    '''
       La fonction retourne les coordonnées (x,y) si la caméra trouve la couleur
       Si la caméra ne trouve pas, la fonction renvoie (-1, -1)         
       Si on appuie sur Echap on sort du programme
    '''

    if color=="red":
        a,b,c=170,67,54
        d,e,f=179,255,255
    elif color == "green":
        a,b,c=45,0,0
        d,e,f=140,255,107
    elif color =="blue":
        a,b,c=95,81,100
        d,e,f=125,255,255

    
    # On brouille l'image pour attenuer les variations possibles
    blur = cv2.GaussianBlur(image, (5,5),0)

    # Convertis le format RGB (Red Green Blue) en TSV (Teinte Saturation Valeur)
    hsv = cv2.cvtColor(blur, cv2.COLOR_BGR2HSV)

    # Définir le seuil de HSV pour détecter la couleur verte                      Threshold the HSV image for only green colors
    lower = np.array([a,b,c])
    upper = np.array([d,e,f])

    # Application du masque permettant de distinguer l'objet du décor 
    mask = cv2.inRange(hsv, lower, upper)

    # On brouille le masque pour distinguer plus facilement les patternes --- Application du masque permettant grâce à l'extérieur de l'objet de le distinguer plus clairement
    bmask = cv2.GaussianBlur(mask, (5,5),0)
    cv2.imshow("bmask",bmask)
    # On trouve le centre de l'objet
    moments = cv2.moments(bmask)
    m00 = moments['m00']
    centroid_x, centroid_y = None, None
    if m00 != 0:

        centroid_x = int(moments['m10']/m00)
        centroid_y = int(moments['m01']/m00)

    # Si on ne trouve pas de centre, on renvoie (-1, -1)
    ctr = (-1,-1)

    # Pointe l'objet si on a des coordonnées non nulles sur x et y
    if centroid_x != None and centroid_y != None:
        #Ctr : coordonnée centre objet
        ctr = (centroid_x,centroid_y)


        # Créer un pointeur noir
        cv2.circle(image, ctr, 4, (0,0,0))

    # Affiche le flux vidéo de la caméra
    cv2.imshow(WINDOW_NAME, image)

    # Si on appuie sur echap, on arrête de pointer
    if cv2.waitKey(1) & 0xFF == 27:
        ctr = None

        

    
    return ctr

# On teste avec le flux de la caméra

# On teste avec le flux de la caméra
capture = cv2.VideoCapture(0)    
while True:

    okay, image = capture.read()    #Détecte si le flux de caméra existe

    if okay:
        
        ctr = track(image,sys.argv[1])         #Si un flux de caméra existe, on utilise track (on trouve le centre de l'objet)
        x = ctr[0]
        y = ctr[1]
        print(int(x/7) , int(y/7))
        if not track(image,sys.argv[1]):
            break

        if cv2.waitKey(1) & 0xFF == 27:
            break

    else:

        print('Capture failed')
        break
