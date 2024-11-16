# README

## ERTMS

Composition des messages et paquets pour les transmissions sol-air. Contenu:
- **EBT_message**: Contient la structure principale des *EuroBalise Telegram*.
- **EBT_packet**: Contient les briques d'information à l'intérieur des *EuroBalise Telegram*.
- **GSMR_message**: Contient les structures de messages GSM-R.
- **GSMR_packet**: Contient les briques d'information qui composent les messages GSM-R.
- **ERTMS**: Contient les fonctions d'initialisation et sérialisation/désérialisation des données pour leur transmission.
- **NRBC**: Contient les structures de messages d'échange entre RBCs (Handover).
- **API Unirail**: Contient les principales fonctinos d'envoi des messages GSM-R, avec abstraction du type de communication utilisé.
- Suite pour tests unitaires, avec un CMakeLists et code pour générer l'executable check_ertms.
