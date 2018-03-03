# Annuaire partagé

## Sujet

Nous souhaitons mettre en place un service d'annuaire partagé. Un utilisateur peut créer un annuaire partagé accessible en lecture à toute personne qui souhaite le consulter. Seul l'utilisateur qui a créé l'annuaire peut modifier son contenu.
Le serveur de l'application stockera dans un ou plusieurs fichiers texte ou binaire les données de ces annuaires partagés. Il aura donc à gérer plusieurs annuaires.
Pour chaque contact dans l'annuaire, on stockera : le nom, le prénom, la société, le numéro de téléphone portable, le numéro de téléphone professionnel, l'adresse postale, l'adresse mail, la date de naissance, des remarques concernant le contact. Les champs nom, prénom et adresse mail sont obligatoires.
L'application permettra de créer un nouvel annuaire, de le modifier (ajout, suppression et modification d'un contact) et de le supprimer. Seul l'utilisateur qui a créé l'annuaire pourra le supprimer et y amener des modifications.
Elle permettra en outre à tout utilisateur de consulter n'importe quel annuaire partagé et de rechercher un contact en particulier.
Le client présentera un menu texte permettant de choisir l'action à réaliser.

## Fonctionnalités offerte par l'annuaire partagé

- Rechercher un annuaire dans le serveur.
- Rechercher un contact dans un annuaire existant.

L'utilisation d'un compte est nécessaire seulement pour la création, modification et suppression d'annuaire et/ou contact.
Les fonctionnalités de recherches peuvent s'effectuer en mode **hors connexion** (qui se traduit par une connexion anonyme au serveur)

- Crée un compte utilisateur.
- Modifier le mot de passe du compte utilisateur.
- Supprimer le compte utilisateur.
- Se connecter à un compte utilisateur.
- Se déconnecter d'un compte utilisateur.


- Créer un annuaire partagé.
- Modifier le nom de l'annuaire partagé.
- Supprimer un annuaire partagé (tout les contacts de l'annuaire sont supprimé).


- Ajouter un contact dans un annuaire.
- Modifier un contact dans un annuaire.
- Supprimer un contact dans un annuaire.

## Protocole d'échange de donnée (SDAP)

**Simply directory access protocol** *(SDAP)* est le protocole utilisé par le client et le serveur.

La RFC SDAP est disponible en PDF ou TXT.
Deux exemples d'échange de données sont mentionnées à la fin de la RFC.

#

OLIVIER Thomas - STRMSEK Nicolas - ROBERT DE SAINT VINCENT Guillaume

Université Paul Sabatier
1A - STRI - UPSSITECH
Janvier 2018
