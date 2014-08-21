InterRCCar
==========

Basé sur les travaux de Jon Bennett

http://www.jbprojects.net/articles/programmable-rc/

21/08

Mise en place mon environnement de travail au sous sol après avoir vérifié que la voiture radiocommandée fonctionnait correctement.

Installation de quelques programmes indispensables, tel que Github windows et l'IDE arduino.

Du côté matériel, ouverture de la télécommande et repérage des composants, boutons et du circuit imprimé.

Rallonge des deux fils d'alimentation (rouge et noir) et soudure d'un 1er fil jaune qui devrait (à valider plus tartd) commander une direction (gauche / droite) ou un mouvement (avant / arrière).

La méthode de répérage est la suivante : chaque bouton poussoir dispose de 4 points de soudure sur le circuit imprimé. Ils sont connecté par pairs : deux sont à la masse et deux sont au +VCC (3,3 V) quand le bouton n'est pas actionné. Le fil jaune est soudé au +VCC (il passe à 0 V quand il est actionné).








