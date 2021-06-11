#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <MYSQL/mysql.h>

int ajouterCompte(int nc, float montant);
int ajouterSolde(int nc, float montant);
int getSolde(int ncc);
    MYSQL mysql;
    int resultat;
    char requette[512];
int main(void)
{
    int choix;


    mysql_init(&mysql);
    mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");

    if(mysql_real_connect(&mysql,"localhost","root","","bank",0,NULL,0))
    {
        do{
            printf("donnez votre choix \n");
            printf("1--ajouter un compte \n");
            printf("2--get montant \n");
            printf("3--ajouter montant \n");
            printf("4--supprimer compte \n");
            printf("autre exit \n");
            scanf("%d",&choix);
            switch(choix)
            {
                case 1:printf("donnez le numero du nouveau compte");int numco;scanf("%d",&numco);
                printf("donnez le le montant a ajouter");float monto;scanf("%f",&monto);
                ajouterCompte(numco, monto);mysql_close(&mysql);break;
                case 2:printf("donnez le numero de votre compte");int numcmpt;scanf("%d",&numcmpt);getSolde(numcmpt);mysql_close(&mysql);break;
                case 3:printf("donnez le numero de votre compte");int numc;scanf("%d",&numc);
                printf("donnez le le montant a ajouter");float mont;scanf("%f",&mont);
                ajouterSolde(numc, mont);mysql_close(&mysql);break;
                case 4:mysql_close(&mysql);break;
                default:choix=10;break;
            }
        }while(choix != 10);

    }
    else
    {
        printf("Une erreur s'est produite lors de la connexion à la BDD!");
    }

    return 0;
}
int ajouterSolde(int nc, float montant)
{

snprintf(requette,512,"SELECT * FROM compte WHERE nc = %d",&nc);
 mysql_query(&mysql,requette);
        //Déclaration des objets
        MYSQL_RES *result = NULL;
        MYSQL_ROW row;
        int i = 1;

        //On met le jeu de résultat dans le pointeur result
        result = mysql_use_result(&mysql);
         unsigned int num_champs = mysql_num_fields(result);
        //Tant qu'il y a encore un résultat ...
        while ((row = mysql_fetch_row(result)))
        {
          unsigned long *lengths;

            //On stocke ces tailles dans le pointeur
            lengths = mysql_fetch_lengths(result);

    float sld=montant+(float)atof(row[1]);
    snprintf(requette,512,"UPDATE compte SET solde = %f",&sld);

        }
    if(mysql_query(&mysql,requette ))
        {
            resultat = -1;
        }
        else
        {
            resultat = 1;
        }

        mysql_free_result(result);
}
int ajouterCompte(int nc, float montant)
{

snprintf(requette,512,"INSERT INTO compte VALUE (%d,%f)",nc,montant);
printf(requette);
 mysql_query(&mysql,requette);
        //Déclaration des objets
        MYSQL_RES *result = NULL;
        MYSQL_ROW row;
        int i = 1;

        //On met le jeu de résultat dans le pointeur result
        result = mysql_use_result(&mysql);
         unsigned int num_champs = mysql_num_fields(result);
        //Tant qu'il y a encore un résultat ...
        while ((row = mysql_fetch_row(result)))
        {
          unsigned long *lengths;

            //On stocke ces tailles dans le pointeur
            lengths = mysql_fetch_lengths(result);

    float sld=montant+(float)atof(row[1]);
    snprintf(requette,512,"UPDATE compte SET solde = %f",sld);

        }
    if(mysql_query(&mysql,requette ))
        {
            resultat = -1;
        }
        else
        {
            resultat = 1;
        }

        mysql_free_result(result);
}
int getSolde(int nc)
{

snprintf(requette,512,"SELECT * FROM compte WHERE nc = %d",nc);
 mysql_query(&mysql,requette);
        //Déclaration des objets
        MYSQL_RES *result = NULL;
        MYSQL_ROW row;
        int i = 1;

        //On met le jeu de résultat dans le pointeur result
        result = mysql_use_result(&mysql);
         unsigned int num_champs = mysql_num_fields(result);
        //Tant qu'il y a encore un résultat ...
        while ((row = mysql_fetch_row(result)))
        {
          unsigned long *lengths;

            //On stocke ces tailles dans le pointeur
            lengths = mysql_fetch_lengths(result);

            //On fait une boucle pour avoir la valeur de chaque champs
            for(i = 0; i < num_champs; i++)
            {

                  printf("[%.*s] ", (int) lengths[i], row[i] ? row[i] : "NULL");

            }
            printf("\n");
        }


        //Libération du jeu de résultat
        mysql_free_result(result);

        //Fermeture de MySQL
}

