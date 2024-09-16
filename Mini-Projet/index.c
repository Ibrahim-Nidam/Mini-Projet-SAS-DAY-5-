    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>


    void menuPricipal(int *choix){

            printf("======Menu Principal======\n");
            printf("1 - Ajouter un livre au stock.\n");
            printf("2 - Afficher tous les livres Disponibles.\n");
            printf("3 - Mettre a Jour la quantité d'un livre.\n");
            printf("4 - Supprimer un livre du stock.\n");
            printf("5 - Afficher le Nombre total de livres en stock.\n");
            printf("6 - Quitter l'application\n");
            do {

                printf("Quel est votre choix : ");
                scanf(" %d",choix);
                printf("\n");
                if(*choix < 1 || *choix > 6){
                    printf("Entrez un nombre entre 1 - 6.\n");
                }
            }while(*choix < 1 || *choix > 6);
    }


    void ajouteLivre(char TitreLivre[][100], char auteurLivre[][100], float prixLivre[], int quantiteLivre[], int *livreConteur,int *totalLivreStocker){

        int quitterOption;
        do {

            getchar();

            printf("Entrez le nom du livre : ");
            fgets(TitreLivre[*livreConteur], 100,stdin);
            printf("Entrez l'auteur du livre : ");
            fgets(auteurLivre[*livreConteur], 100,stdin);
            do{
                printf("Entrez le prix du livre : ");
                scanf(" %f",&prixLivre[*livreConteur]);
                printf("Entrez la Quantité : ");
                scanf(" %d",&quantiteLivre[*livreConteur]);
                if(prixLivre[*livreConteur] <= 0 || quantiteLivre[*livreConteur] <= 0){
                    printf("Entrez un nombre positif.\n");
                }
            }while(prixLivre[*livreConteur] <= 0 || quantiteLivre[*livreConteur] <= 0);

            *totalLivreStocker +=  quantiteLivre[*livreConteur];
            (*livreConteur)++;

            printf("\n");
            printf("Entrer 1 si vous voulez ajouter un autre livre et 0 si vous voulez retourner au menu principale : ");
            scanf(" %d",&quitterOption);
            printf("\n");

        }while(quitterOption != 0);

    }

    void affichezTousLivreDispo(char TitreLivre[][100], char auteurLivre[][100], float prixLivre[], int quantiteLivre[], int livreConteur){

        if(livreConteur > 0){

            for(int i = 0; i <  livreConteur; i++){
                printf("*********************\n");
                printf("Livre %d : %s\n",i+1,TitreLivre[i]);
                printf("Par : %s\n",auteurLivre[i]);
                printf("Prix : %.2f$  ---  Quantité en : %d\n\n",prixLivre[i],quantiteLivre[i]);
                printf("*********************\n");
            }

        }else{
            printf("Aucun livre n'est disponible.\n\n");
        }

    }

    void toLowerCase(char str[]){
        for (int i = 0; str[i]; i++){
            str[i] = tolower(str[i]);
        }
    }

    int trouverTitre(char TitreLivre[][100], int livreConteur,char titreLivreAChercher[100]){
        char lowerCaseTitle[100];
        int trouve = 0;
        toLowerCase(titreLivreAChercher);

        int len = strlen(titreLivreAChercher);

        if (titreLivreAChercher[len - 1] == '\n') {
            titreLivreAChercher[len - 1] = '\0';  // Replace newline with null terminator
        }

        for (int i = 0; i < livreConteur; i++){

            strcpy(lowerCaseTitle, TitreLivre[i]);  // Make a copy of the title
            toLowerCase(lowerCaseTitle);

            if(strstr(lowerCaseTitle, titreLivreAChercher) != NULL){

                printf("Livre trouvé : %s\n",TitreLivre[i]);
                trouve = 1;
                return i;
            }

        }
            if(!trouve){
                printf("Livre non trouvé.\n\n");
                return -1;
            }

    }

    void miseAJourQuantite(char TitreLivre[][100], char auteurLivre[][100], int quantiteLivre[], int livreConteur,int *totalLivreStocker){
        char titreLivreAChercher[100];
        int nouvelleQuantite = 0;

        if(livreConteur > 0){
                getchar();

            printf("Entrez le Titre du Livre que voulez changer la Quantité : ");
            fgets(titreLivreAChercher, 100, stdin);

            int index = trouverTitre(TitreLivre, livreConteur,titreLivreAChercher);

            if(index != -1){

                printf("Quantité : %d\n",quantiteLivre[index]);
                printf("Entrez  la nouvelle Quantité : ");
                scanf(" %d",&nouvelleQuantite);

                *totalLivreStocker -=  quantiteLivre[index];
                quantiteLivre[index] = nouvelleQuantite;
                *totalLivreStocker +=   quantiteLivre[index];

                printf("La nouvelle  Quantité du livre A jour est : %d\n",quantiteLivre[index]);
            }
        
        }else {
            printf("La bibliotheque ne posséde aucun livre pour le moment.\n\n");
        }
    }

    void  supprimerLivre(char TitreLivre[][100], char auteurLivre[][100],int *livreConteur,int quantiteLivre[],float prixLivre[],int *totalLivreStocker){
        char titreLivreAChercher[100];

            getchar();

        printf("Entrez le titre de livre a supprimé : ");
        fgets(titreLivreAChercher, 100, stdin);

        int index = trouverTitre(TitreLivre, *livreConteur, titreLivreAChercher);

        if (index != -1) {
        *totalLivreStocker -= quantiteLivre[index];

        // Shift the arrays to remove the book at the found index
        for (int i = index; i < *livreConteur - 1; i++) {

            strcpy(TitreLivre[i], TitreLivre[i + 1]);
            strcpy(auteurLivre[i], auteurLivre[i + 1]);
            quantiteLivre[i] = quantiteLivre[i + 1];
            prixLivre[i] = prixLivre[i + 1];
        }

        (*livreConteur)--;  // Decrease the book count
        printf("Le livre a été supprimé avec succès.\n\n");
    }



    }

    int main(){

        char TitreLivre[100][100];
        char auteurLivre[100][100];
        int quantiteLivre[100];
        float prixLivre[100];

        int livreConteur = 0;
        int totalLivreStocker = 0;
        int choix;
        
        do{

            menuPricipal(&choix);

            switch(choix){
                case 1 :
                    system("cls");
                    ajouteLivre(TitreLivre, auteurLivre, prixLivre, quantiteLivre, &livreConteur, &totalLivreStocker);
                break;
                case 2 :
                    system("cls");
                    affichezTousLivreDispo(TitreLivre, auteurLivre, prixLivre, quantiteLivre, livreConteur);
                break;
                case 3 :
                    system("cls");
                    miseAJourQuantite(TitreLivre, auteurLivre, quantiteLivre, livreConteur,&totalLivreStocker);
                break;
                case 4 :
                    system("cls");
                    supprimerLivre(TitreLivre, auteurLivre, &livreConteur, quantiteLivre, prixLivre, &totalLivreStocker);
                break;
                case 5 :
                    system("cls");
                    printf("La Quantité total des livres en stock est %d\n\n",totalLivreStocker);
                break;
            }

        }while(choix != 6);
        return 0;
    }