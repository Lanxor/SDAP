# Annuaire partagé

## Client CLI

Le client CLI va permetre de se connecter à un serveur et pouvoir envoyer des commandes formater selon la **RFC SDAP**.
Pour utiliser ce client il faut au préalable connaître la syntaxe des PDU échangé par le serveur et le client.

Compiler le client :
```bash
$ make
```

Lancer le client :
```bash
$ ./play.client
```

Effacer les fichiers objets :
```bash
$ make clean
```

Effacer les fichier objets et l'exécutable :
```bash
$ mrproper
```
