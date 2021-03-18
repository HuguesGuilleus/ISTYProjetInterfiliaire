# Protocole de réseau

L'idée est d'avoir un client (un petit truc en ligne de commande ou bien un truc avec de la vision avec OpenCV) qui envoie des ordres au serveurs, le serveur les exécutera et renvera un ackittement.

## Format


```txt
exe:commande nb1 nb2 
ack:commande
```

Les nombres nb1 et nb2 doivent toujours êtres présents mais peuvent ne pas servir pour certaine commande. Ils sont encodé de décimal.

*On fini par un retour à léa lignre, retour chario, caractère nul?*

## Liste des ordres

- reset: Remet le robots à la position initiale
- stop: Arrête le déplacement
- move: se déplace au coordonée x y
- axe: axe se déplace de nb2 degré // pas sur qu'on l'utilise
	nb2 est en radian, degrée???

