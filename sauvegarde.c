#include "sauvegarde.h"

int sauvegarde(Animal *animals, int taille) {
     if (animals == NULL || taille <= 0) {
          printf("[ERREUR] Paramètres invalides : animals est NULL ou size <= 0\n");
          return 1;
     }

     FILE *fichier = fopen("animaux/animal.txt", "w");
     if (fichier == NULL) {
          printf("[ERREUR] Impossible d'ouvrir le fichier animal.txt\n");
          return 1;
     }

     printf("[LOGS] Sauvegarde en cours... (ne pas éteindre le programme)\n");
     for (int i = 1; i < taille; i++) {
          if (animals[i].keyid < 0) {
               continue;
          }

          if (animals[i].nom == NULL || animals[i].phrase == NULL) {
               printf("[ERREUR] Données invalides pour l'animal à l'index %d\n", i);
               fclose(fichier);
               return 1;
          }

          if (fprintf(fichier, "%d %s %d %d %f %s\n\n",
                      animals[i].keyid,
                      animals[i].nom,
                      animals[i].espece,
                      animals[i].b_year,
                      animals[i].weight,
                      animals[i].phrase) < 0) {
               printf("[ERROR] Erreur lors de l'écriture dans le fichier\n");
               fclose(fichier);
               return 1;
                      }
     }

     if (fclose(fichier) != 0) {
          printf("[ERREUR] Erreur lors de la fermeture du fichier animal.txt\n");
          return 1;
     }

     printf("[LOGS] Sauvegarde terminée !\n");
     return 0;
}


int restauration(Animal *animals, int taille) {
    if (animals == NULL || taille <= 0) {
        printf("[ERREUR] Paramètres invalides\n");
        return 1;
    }

    FILE *fichier = fopen("animaux/animal.txt", "r");
    if (fichier == NULL) {
        printf("[ERREUR] Fichier introuvable\n");
        return 1;
    }

    printf("[LOGS] Restauration en cours...\n");
    for (int i = 0; i < taille; i++) {
        animals[i].keyid = -(i); // Initialiser les cages comme vides
        animals[i].nom[0] = '\0';
        animals[i].espece = 0;
        animals[i].b_year = 0;
        animals[i].weight = 0.0f;
        animals[i].phrase[0] = '\0';
    }

    int keyid;
    char ligne[512]; // Taille suffisante pour une ligne

    while (fgets(ligne, sizeof(ligne), fichier)) {
        Animal temp;
        int result = sscanf(ligne, "%d %s %d %d %f %[^\n]",
                            &keyid,
                            temp.nom,
                            &temp.espece,
                            &temp.b_year,
                            &temp.weight,
                            temp.phrase);

        if (result == 6) {
            if (keyid >= 0 && keyid < taille) {
                temp.keyid = keyid;
                animals[keyid] = temp; // Copie les données
            } else {
                printf("[ATTENTION] keyid %d hors limites, ignorée\n", keyid);
            }
        } else {
            // rien ! printf("[ATTENTION] Ligne malformée: %s", ligne);
        }
    }

    fclose(fichier);
    printf("[LOGS] Restauration terminée !\n");
    return 0;
}
