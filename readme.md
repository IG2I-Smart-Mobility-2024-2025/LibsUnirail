# README

Librairies partagées. Contient:
- Lib CAN, avec identifiants et champs de chaque trame.
- Lib xBee, pour les communications GSM-R
- Librairie DSPICfj, avec des peripheriques de communication pour DSPIC.
- ERTMS, avec:
	- les messages et paquets GSM-R.
	- les Eurobalise Telegram et les paquets qui les intègrent.
	- les messages NRBC pour les communications "handover" entre RBCs
	- les routines pour initialisation, serialisation et deserialisation des messages
	- une API pour l'envoi des messages, avec detection automatique de standard de cpmmunication
	- une suite de tests unitaires

Cette librairie est utilisé dans les projets:
 - EVC
 - RBC
 - SD60_Balise
 - SD60_Regul
 - SD60_LCD
 - SD60_GSMR
 ### Compilation des tests unitaires
- Le paquet LibCheck  (*sudo apt-get install check*) est  nécessaire à la compilation
- Un fichier CMakeLists.txt dans le dossier ERTMS produit un script MakeFile pour la compilation des tests, l'executable lance les tests.

