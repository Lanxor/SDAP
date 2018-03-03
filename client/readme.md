# Annuaire partagé

## Client

Ce client propose à l'utilisateur une interface de communication avec le serveur. Nulle besoin de connaitre la **RFC SDAP** pour pouvoir l'utiliser.
L'utilisateur est guidé sur les actions possibles et les résultats de ces actions. Des messages d'erreurs apparaissent pour indiquer à l'utilisateur les réponses du serveur sur l'action demandé.

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
