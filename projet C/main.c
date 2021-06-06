#include<stdio.h>
#include<stdlib.h>
main()
{
   MenuPrincipal();
}


//********************************************Les structures****************************************************************************

typedef struct
{
    int IdVoiture;
    char marque[20];
    char NomVoiture[30];
    char couleur[10];
    int NbPlaces;
    int PrixJour;
    int EnLocation;// 0:voiture disponible 1:voiture indisponible
}voiture;

typedef struct
{
    int day;
    int month;
    int year;
}date;

typedef struct
{
    int NumContrat;
    int IdVoiture;
    int IdClient;
    date debut;
    date fin;
    int cout;
}Contrat;

typedef struct
{
    int IdClient;
    char nom[20];
    char prenom[20];
    int cin;
    char adresse[15];
    int telephone;
}Client;

voiture car;
Client client;
Contrat contrat;

//****************************************La gestion des voitures********************************************************************************

void gestiondevoitures()
{
    int choix;

    printf("\n\xb3 Gestion des Voitues   \xb3");
    printf("\n\n");
    printf("\n\xba                                                          \xba");
    printf("\n\xba    Liste de voitures...............................1     \xba");
    printf("\n\xba    Ajouter voiture.................................2     \xba");
    printf("\n\xba    Modifier voiture................................3     \xba");
    printf("\n \xba    Supprimer voiture...............................4     \xba");
    printf("\n\xba    Retour..........................................5     \xba");
    printf("\n\xba\xba");
    printf("\n\nVotre choix  :  ");
    scanf("%d",&choix);


    switch(choix)
    {
        case 1 : listedevoitures();
        break;
        case 2 : ajoutdevoiture();
        break;
        case 3 : modifiervoiture();
        break;
        case 4 : supprimervoiture();
        break;
        case 5 : MenuPrincipal();
        break;
    }

}

//************************************************************************************************************************

int search(int IdV) //cette fonction permet l'access au ficher des voitures et de retourner 1 si un Identifient de voiture passé en paramètres existe et -1 sinon
{                   //en faisant le fscanf() ligne par ligne. Et la meme chose pour les deux autres fonctions; cher()pour les clients et lookfor() pour les contrats
    FILE *f;
    f=fopen("car.txt","r");
        do
        {
            fscanf(f,"%d ,%s ,%s ,%s ,%d ,%d ,%d\n",&car.IdVoiture,&car.marque,&car.NomVoiture,&car.couleur,&car.NbPlaces,&car.PrixJour,&car.EnLocation);
            fflush(stdin);
            if(car.IdVoiture == IdV) //pour chaque ligne on verifie cette condition.
                {
                    fclose(f);
                    return 1;
                }
        }while(!feof(f));
        fclose(f);
    return -1 ;
}

//*************************************************************************************************************************


void ajoutdevoiture() // on saisie un id de voiture et on verifie son existence , s'il n'existe pas on insère cet id dans la structure et on demande la saisie des autres attributs,sinon on redemande la saisie de l'identifient.
{
    FILE *f ;
    int id ;
    f=fopen("car.txt","a");// on ouvre le fichier en mode "append", ce qui permet d'ajouter une autre voiture sans avoir ecraser le contenu existant dans ce fichier.
    printf("saisir l'id de la nouvelle voiture \t");
    scanf("%d",&id);
    while(search(id)==1) //verification de l'existence de l'id saisi.
    {
        printf("cet id de voiture existe deje \n");
        printf("saisir l'id de la nouvelle voiture \t"); // cette procedure est affichée si et seulement si l'id saisi existe dans le ficher car.txt.
        scanf("%d",&id);
    }
    car.IdVoiture=id; // l'ajout de l'id à la structure.
    printf("saisir la marque de la nouvelle voiture \t");
    scanf("%s",car.marque);
    fflush(stdin);
    printf("saisir le nom de la nouvelle voiture \t");
    scanf("%s",car.NomVoiture);
    fflush(stdin);
    printf("saisir la couleur de la nouvelle voiture \t");
    scanf("%s",car.couleur);
    fflush(stdin);
    printf("saisir le nombre de places de la nouvelle voiture \t");
    scanf("%d",&car.NbPlaces);
    fflush(stdin);
    printf("saisir le prix du jour de la nouvelle voiture \t");
    scanf("%d",&car.PrixJour);
    fflush(stdin);
    printf("saisir l'enloc de la nouvelle voiture \t");
    scanf("%d",car.EnLocation);
    fflush(stdin);
    // on fait ensuite le fprintf() pour ecrire tous ces informations enregistrées sur la nouvelle voiture dans notres fichier car.txt.
    fprintf(f, "%d ,%s ,%s ,%s ,%d ,%d ,%d \n",car.IdVoiture,car.marque,car.NomVoiture,car.couleur,car.NbPlaces,car.PrixJour,car.EnLocation );

    fclose(f); // et on ferme le fichier .
    gestiondevoitures();
}
// on fait le meme principe pour la fonction ajouterclient().

//*************************************************************************************************************************

void listedevoitures() // on lit dans le fichier ligne par ligne et on l'affiche.
{
    FILE *f;
    f=fopen("car.txt","r");//ouverture en mode "read" , lecture seulement.
    printf("voila la liste des voitures \n");
    do
    {
        // on fait le fscanf() dans la boucle do..while() pour lire ligne par ligne.
        fscanf(f,"%d ,%s ,%s ,%s ,%d ,%d ,%d \n",&car.IdVoiture,&car.marque,&car.NomVoiture,&car.couleur,&car.NbPlaces,&car.PrixJour,&car.EnLocation);
        fflush(stdin);
        printf("l'id de voiture : %d\t\n",car.IdVoiture);
        printf("Marque : %s\t\n",car.marque);
        printf("nom: %s\t\n",car.NomVoiture);
        printf("Couleur: %s\t\n",car.couleur);          //on affiche les informations des nos voitures.
        printf("Nombre de places : %d\t\n",car.NbPlaces);
        printf("Prix du jour : %d\t\n",car.PrixJour);
        printf("Enlocation : %d\t\n",car.EnLocation);
    }while(!feof(f));
fclose(f);
gestiondevoitures(); //on retourne au menu precedent.et on fait la meme chose pour la fonction listedeclients().

}

//*************************************************************************************************************************

void modifiervoiture() // cette fonction fait le choix entre modification generale de la voiture
{                      //et modifier le champs "enlocation" seulement pour faciliter la tache
    int choix;         //lors de la location et le retour des voitures.

    printf("\n                               \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
    printf("\n                               \xb3 modifier voiture  \xb3");
    printf("\n                               \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");

    printf("\n\n");

    printf("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
    printf("\n               \xba                                                     \xba");
    printf("\n               \xba    Modification generale........................1   \xba");
    printf("\n               \xba    Modifier Enlocation..........................2   \xba");
    printf("\n               \xba    Quitter......................................4   \xba");
    printf("\n               \xba                                                     \xba");
    printf("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
    printf("\n\n                                Votre choix  :  ");

    scanf("%d",&choix);



    switch(choix)
    {
        case 1 : modifiervoiture_generale();
        break;
        case 2 : modifier_enloc();
        break;
        case 3 : gestiondevoitures();
        break;
    }
}

//*************************************************************************************************************************


void modifier_enloc() //on saisie l'id de la voiture a modifier et on verifie son existence, si oui on demande d'assurer la modification et
{                     //chaque fois qu'on lit une ligne dans le fichier contenant les voitures(ouvert en mode "read") on l'ecrit dans un fichier
                      //temporaire ouvert em mode "append",et si l'id d'une ligne est le meme que l'id saisie on demande la nouvelle valeur du champs
                      //enlocation et puis on l'ecrit dans le nouveau fichier. et apres on ecrase le premier ficher et on renomme
                      //le fichier temporaire par le meme nom que le fichier supprimé.
    FILE *f,*fl;
    int id ;
    int rep;
    printf("saisir l'id de la voiture a modifier \t");
    scanf("%d",&id);
    fflush(stdin);
    if(search(id)==1) // l'id  saisi existe dans le fichier
        {
            printf("voulez vous vraiment modifier cette voiture 0(non)/1(oui) \t"); //on confirme la modification
            scanf("%d",&rep);
            fflush(stdin);
            if(rep==1)// la reponse de la confirmation est oui
                {
                    f=fopen("car.txt","r"); //on ouvre le fichier contenant les voitures en mode "read"
                    fl=fopen("voiture.txt","a"); //le fichier temporaire crée en mode "append" pour effectuer les modification.
                            do
                            {
                                // on fait la lecture ligne par ligne tout au long du fichier
                                fscanf(f,"%d ,%s ,%s ,%s ,%d ,%d ,%d\n",&car.IdVoiture,&car.marque,&car.NomVoiture,&car.couleur,&car.NbPlaces,&car.PrixJour,&car.EnLocation);
                                if(id==car.IdVoiture) // si on est arriveé a la ligne dont l'id de voiture est le meme que l'id saisi
                                {
                                    car.IdVoiture=id;
                                    printf("la nouvelle enlocation :\t"); // on demande la nouvelle valeur du champ
                                    scanf("%d",&car.EnLocation);
                                }
                                //on copie les lignes du premier fichier sans le deuxieme ainsi que les modifications effectuées.
                                fprintf(fl,"%d ,%s ,%s ,%s ,%d ,%d ,%d\n",car.IdVoiture,car.marque,car.NomVoiture,car.couleur,car.NbPlaces,car.PrixJour,car.EnLocation );

                            }while(!feof(f));
                            fclose(f); // on ferme les deux fichiers
                            fclose(fl);
                            remove("car.txt"); // suppression du premier
                            rename("voiture.txt","car.txt"); //renommage du deuxieme
                            printf("\n voiture modifiée avec succes\n"); // et voila .
                }
            else
                printf("la modification est annulée"); // la reponse de la confirmation est non

        }
    else
        printf("\n cet id de voiture n'existe pas \n"); // l'id saisi n'existe pas dans le fichier

}

//*************************************************************************************************************************

void modifiervoiture_generale()  //on saisie l'id de la voiture a modifier et on verifie son existence, si oui on demande d'assurer la modification et
                                //chaque fois qu'on lit une ligne dans le fichier contenant les voitures(ouvert en mode "read") on l'ecrit dans un fichier
                                  //temporaire ouvert em mode "append",et si l'id d'une ligne est le meme que l'id saisie on demande les nouvelles valeurs des champs
                                  //et puis on les ecrit dans le nouveau fichier. et apres on ecrase le premier ficher et on renomme
                                  //le fichier temporaire par le meme nom que le fichier supprimé.
                                  //on suit les memes etapes que la fonction modifier_enloc();
                                  //les memes aussi pour les fonctions modifierclient() et modifiercontrat().
{
    FILE *f,*fl;
    int id ;
    int rep;
    printf("saisir l'id de la voiture a modifier \t");
    scanf("%d",&id);
    fflush(stdin);
    if(search(id)==1)
        {
            printf("voulez vous vraiment modifier cette voiture 0(non)/1(oui) \t");
            scanf("%d",&rep);
            fflush(stdin);
            if(rep==1)
                {
                    f=fopen("car.txt","r");
                    fl=fopen("voiture.txt","a");
                            do
                            {
                                fscanf(f,"%d ,%s ,%s ,%s ,%d ,%d ,%d\n",&car.IdVoiture,&car.marque,&car.NomVoiture,&car.couleur,&car.NbPlaces,&car.PrixJour,&car.EnLocation);
                                if(id==car.IdVoiture)
                                {
                                    car.IdVoiture=id;
                                    printf("saisir la nouvelle marque :\t");    //si on est arrivé à une ligne dont l'id de voiture
                                    scanf("%s",&car.marque);                    //est le meme que l'id saisi on demande de saisir les nouvelle valeurs
                                    printf("saisir le nouveau nom : \t");       //des champs
                                    scanf("%s",&car.NomVoiture);
                                    printf("saisir la nouvelle couleur :\t");
                                    scanf("%s",&car.couleur);
                                    printf("saisir le nouveau nombre de places :\t");
                                    scanf("%d",&car.NbPlaces);
                                    printf("saisir le nouveau prix du jour :\t");
                                    scanf("%d",&car.PrixJour);
                                    printf("enlocation :\t");
                                    scanf("%d",&car.EnLocation);
                                }
                                fprintf(fl,"%d ,%s ,%s ,%s ,%d ,%d ,%d\n",car.IdVoiture,car.marque,car.NomVoiture,car.couleur,car.NbPlaces,car.PrixJour,car.EnLocation );

                            }while(!feof(f));
                            fclose(f);
                            fclose(fl);
                            remove("car.txt");
                            rename("voiture.txt","car.txt");
                            printf("\n voiture modifiée avec succes\n");
                }
            else
                printf("la modification est annulée");

        }
    else
        printf("\n cet id de voiture n'existe pas \n");
    gestiondevoitures();
}

//**********************************************************************************************************************

void supprimervoiture() //on saisie l'id de la voiture a supprimer et on verifie son existence, si oui on demande d'assurer la suppression et
                       //on copie toutes lignes du fichier contenant les voitures et ouvert en mode "read" dans un autre fichier temporaire
                        //crée SAUF la ligne qu'on veut supprimer ... et puis on supprime le premier fichier et on renomme
                        //le fichier temporaire par le meme nom que le fichier supprimé.
                        //les memes etapes aussi pour les fonctions supprimerclient() et supprimercontrat().
{
    FILE *f , *fl;
    int rep ;
    int id;
    printf("saisir l'id de la voiture a supprimer \n");
    scanf("%d",&id);
    fflush(stdin);
    if(search(id)==1)
        {
            printf("voulez vous vraiment supprimer cette voiture ? \n");
            scanf("%d",&rep);
            fflush(stdin);
            if(rep ==1)
                {
                    f=fopen("car.txt","r"); // le premier fichier en "read"
                    fl=fopen("fic.txt","a"); // le deuxieme en "append"
                    if(fl==NULL)
                    printf("cannot open the file\n");
                    else
                    {
                        do
                        {
                            fscanf(f,"%d ,%s ,%s ,%s ,%d ,%d ,%d \n",&car.IdVoiture,&car.marque,&car.NomVoiture,&car.couleur,&car.NbPlaces,&car.PrixJour,&car.EnLocation);
                            if(id != car.IdVoiture)// si l'id de voiture saisi est different de l'id dans la ligne
                            {                   //on copie la ligne dans le deuxieme fichier.
                                fprintf(fl, "%d ,%s ,%s ,%s ,%d ,%d ,%d \n",car.IdVoiture,car.marque,car.NomVoiture,car.couleur,car.NbPlaces,car.PrixJour,car.EnLocation );
                            }
                        }while(!feof(f));
                        fclose(f);
                        fclose(fl);
                        remove("car.txt");
                        rename("fic.txt","car.txt");
                        printf("\n voiture supprimée avec succes\n");

                    }
                }
            else
                printf("\n suppression annulée \n");
        }
    else
    {    printf("cet id n'existe pas \n");
        gestiondevoitures();
    }
}

//**********************************************************************************************************************

void retournervoiture()// on saisie l'id de la voiture qu'on veut retourner et on verifie son existence, on saisit le numero du contrat crée
                        // et on verifie son existence, puis on supprime ce contrat et on change la valeur le l"enlocation
                        //pour indiquer que la voiture est maintenant disponible
{
    FILE *f,*fl;
    int id,num;
    printf("saisir l'id de la voiture retournée \n");
    scanf("%d",&id);
    f=fopen("car.txt","a");
    fl=fopen("contrat.txt","a");
    fscanf(f,"%d ,%s ,%s ,%s ,%d ,%d ,%d\n",&car.IdVoiture,&car.marque,&car.NomVoiture,&car.couleur,&car.NbPlaces,&car.PrixJour,&car.EnLocation);
    if(search(id) != 1) // l'id de voiture saisi n'existe pas
    {
        printf("veuillez saisir l'id de la voiture retournée\n");//on remande la saisie de lid voiture
        scanf("%d",&id);
    }
    printf("veuillez saisir le numero de votre contrat \n");
    scanf("%d",&num);
    fscanf(fl, "%d ,%d ,%d ,%d /%d /%d ,%d /%d /%d ,%d\n",&contrat.NumContrat,&contrat.IdVoiture,&contrat.IdClient,&contrat.debut.day,&contrat.debut.month,&contrat.debut.year,&contrat.fin.day,&contrat.fin.month,&contrat.fin.year,&contrat.cout );
    if(lookfor(num) != 1) //le numero de contrat n'existe pas
    {
        printf("veuillez saisir le numero de votre contrat \n");//on remande la saisie du numero de contrat
        scanf("%d",&num);

    }
    supprimercontrat();// on fait appel a cette fonction qui supprime le contrat dont le meme numero saisi
    printf("votre contrat est supprimé \n");
    printf("changer la valeur de l'enlocation a 0\n");
    modifier_enloc();
    printf("merci d'avoir choisir notre agence\n");
    location();
}

//**********************************************************************************************************************

int cost(int idv,int nbj)// cette fonction calcule le prix total de location d'une voiture, apres avoir verifier que son id passé en arguments existe
                        // dans le fichier en fonction du prix du jour de chaque voiture
{
    FILE *fv;
    int cost=0,price=0;
    fv=fopen("car.txt","r");
    do
    {
        fscanf(fv,"%d ,%s ,%s ,%s ,%d ,%d ,%d \n",&car.IdVoiture,&car.marque,&car.NomVoiture,&car.couleur,&car.NbPlaces,&car.PrixJour,&car.EnLocation);
        if (idv==car.IdVoiture)
        {
            price=car.PrixJour;
            cost=price*nbj;
        }

    }while(!feof(fv));
    fclose(fv);
    return cost;
}

//***********************************************************************************************************************

void louervoiture()//on saisie l'id du client qui veut louer la voiture,si cet id n'exixte pas dans le fichier myclients.txt on lui
                    // assure qu'il doit s'enregister parmi les clients de l'agence, on affiche ensuite la liste des voitures disponibles
                    //on demande la saisie de lid de voiture à louer et le nombre de jours qu'il desire cette voiture et on calcul le cout
                    //on demande au client de remplir le contrat et de changer la valeur du champs enlocation pour indiquer
                    // que la voiture n'est pas disponible
{
    FILE *fv,*fc,*ft;
    int idc,idv,nbj ,c;
    printf("saisir votre id\n");
    scanf("%d",&idc);
    fc=fopen("myclients.txt","r");
    fscanf(fc,"%d ,%s ,%s ,%d ,%s ,%d \n",&client.IdClient,&client.nom,&client.prenom,&client.cin,&client.adresse,&client.telephone);
    if(cher(idc) != 1)
    {
        printf("veuillez enregister vos informations au premier\n");
        printf("ajouter client\n");
        ajoutdeclient();
        printf("maintenant vous pouver louer une voiture\n");
    }

    fv=fopen("car.txt","r");
    while(!feof(fv))
    {
        fscanf(fv,"%d ,%s ,%s ,%s ,%d ,%d ,%d ",&car.IdVoiture,&car.marque,&car.NomVoiture,&car.couleur,&car.NbPlaces,&car.PrixJour,&car.EnLocation);
        if (car.EnLocation==0)
        {
            printf("l'id de voiture : %d\t\n",car.IdVoiture);
            printf("Marque : %s\t\n",car.marque);
            printf("nom: %s\t\n",car.NomVoiture);
            printf("Couleur: %s\t\n",car.couleur);
            printf("Nombre de places : %d\t\n",car.NbPlaces);
            printf("Prix du jour : %d\t\n",car.PrixJour);
            printf("Enlocation : %d\t\n",car.EnLocation);
        }
    }
    printf("veuillez saisir l'id de la voiture a louer\n");
    scanf("%d",&idv);
    printf("combien de jours voulez vous louer la voiture\n");
    scanf("%d",&nbj);
    c=cost(idv,nbj);
    printf("vous devez payer alors %d MAD\n",c );
    printf("veuillez rempliir le contrat suivant :\n");
    creercontrat();
    printf("changer la valeur de l'enlocation en 1\n");
    modifier_enloc(); // changer la valeur de champs à 1
    printf("merci d'avoir choisir notre agence\n");
    fclose(fv);
    fclose(fc);
    location();
}

//***********************************************La gestion des clients*****************************************************************

int gestiondeclients()
{
    int choix;

    printf("\n                               \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
    printf("\n                               \xb3 Gestion de clients    \xb3");
    printf("\n                               \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");

    printf("\n\n");

    printf("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
    printf("\n               \xba                                                          \xba");
    printf("\n               \xba    Liste de clients...............................1      \xba");
    printf("\n               \xba    Ajouter client.................................2      \xba");
    printf("\n               \xba    Modifier client................................3      \xba");
    printf("\n               \xba    Supprimer client...............................4      \xba");
    printf("\n               \xba    Retour.........................................5      \xba");
    printf("\n               \xba                                                          \xba");
    printf("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
    printf("\n\n                                Votre choix  :  ");

    scanf("%d",&choix);

    switch(choix)
    {
        case 1 : listedeclients();
        break;
        case 2 : ajoutdeclient();
        break;
        case 3 : modifierclient();
        break;
        case 4 : supprimerclient();
        break;
        case 5 : break;
    }
}

//***********************************************************************************************************************

int cher(int id)
{
	FILE *f;
	f=fopen("myclients.txt","r");
	if(f==NULL)
		printf("cannot open the file \n");
	else
	{
		do
		{
			fscanf(f,"%d ,%s ,%s ,%d ,%s ,%d \n",&client.IdClient,&client.nom,&client.prenom,&client.cin,&client.adresse,&client.telephone);
			fflush(stdin);
			if(client.IdClient==id)
			{
				fclose(f);
				return 1;
			}
		} while (!feof(f));
		fclose(f);
	}
	return -1;
}

//***********************************************************************************************************************


void ajoutdeclient()
{
    FILE *f;
    int num;
    f=fopen("myclients.txt","a");
    printf("saisir l'id du nouveau client \n");
    scanf("%d",&num);
    client.IdClient=num;
    printf("saisir le nom du nouveau client \n");
    scanf("%s",&client.nom);
    fflush(stdin);
    printf("saisir le prenom du nouveau client\n");
    scanf("%s",&client.prenom);
    fflush(stdin);
    printf("saisir le cin du nouveau client \n");
    scanf("%d",&client.cin);
    fflush(stdin);
    printf("saisir l'adresse du nouveau client \n");
    scanf("%s",&client.adresse);
    fflush(stdin);
    printf("saisir le telephone du nouveau client \n");
    scanf("%d",&client.telephone);
    fflush(stdin);
    fprintf(f,"%d ,%s ,%s ,%d ,%s ,%d \n",client.IdClient,client.nom,client.prenom,client.cin,client.adresse,client.telephone);
    fclose(f);
}

//***********************************************************************************************************************


void listedeclients()
{
    FILE *f;
    f=fopen("myclients.txt","r");
    printf("voila la liste des clients \n");
    do
    {
        fscanf(f,"%d ,%s ,%s ,%d ,%s ,%d \n",&client.IdClient,&client.nom,&client.prenom,&client.cin,&client.adresse,&client.telephone);
        fflush(stdin);
        printf("l'id de client : %d\t\n",client.IdClient);
        printf("Nom : %s\t\n",client.nom);
        printf("Prenom : %s\t\n",client.prenom);
        printf("Cin: %d\t\n",client.cin);
        printf("Adresse : %s\t\n",client.adresse);
        printf("Telephone : %d\t\n",client.telephone);
    }while(!feof(f));
fclose(f);
gestiondeclients();
}

//***********************************************************************************************************************


void modifierclient()
{
    FILE *f,*fl;
    int id ;
    int rep;
    printf("saisir l'id du client a modifier \t");
    scanf("%d",&id);
    if(cher(id)==1)
        {
            printf("voulez vous vraiment modifier cette voiture 0(non)/1(oui) \t");
            scanf("%d",&rep);
            fflush(stdin);
            if(rep==1)
                {
                    f=fopen("myclients.txt","r");
                    fl=fopen("tempo.txt","a");
                    if(fl==NULL)
                        printf("cannot oppen the file\n");
                    else
                        {
                            do
                            {
                                fscanf(f,"%d ,%s ,%s ,%d ,%s ,%d \n",&client.IdClient,&client.nom,&client.prenom,&client.cin,&client.adresse,&client.telephone);
                                if(id==client.IdClient)
                                    {
                                        client.IdClient=id;
                                        printf("saisir le nouveau nom \n");
                                        scanf("%s",&client.nom);
                                        fflush(stdin);
                                        printf("saisir le nouveau prenom \n");
                                        scanf("%s",&client.prenom);
                                        fflush(stdin);
                                        printf("saisir le nouveau cin \n");
                                        scanf("%d",&client.cin);
                                        fflush(stdin);
                                        printf("saisir la nouvelle adresse  \n");
                                        scanf("%s",&client.adresse);
                                        fflush(stdin);
                                        printf("saisir le nouveau telephone \n");
                                        scanf("%s",&client.telephone);
                                        fflush(stdin);
                                    }
                                        fprintf(fl,"%d ,%s ,%s ,%d ,%s ,%d \n",client.IdClient,client.nom,client.prenom,client.cin,client.adresse,client.telephone);
                            }while(!feof(f));
                            fclose(f);
                            fclose(fl);
                            remove("cyclients.txt");
                            rename("tempo.txt","myclients.txt");
                            printf("\n client modifié avec succes\n");
                        }
                }
            else
                printf("la modification est annulée");

        }
    else
        printf("\n cet id de client n'existe pas \n");
    gestiondeclients();
}


//***********************************************************************************************************************


void supprimerclient()
{
    FILE *f , *fl;
    int id,rep;
    printf("saisir l'id du client a supprimer\n");
    scanf("%d",&id);
    fflush(stdin);
    if(cher(id)==1)
        {
            printf("voulez vous vraiment supprimer ce client 0/1 ? \n");
            scanf("%d",&rep);
            fflush(stdin);
            if(rep==1)
                {
                    f=fopen("myclients.txt","r");
                    fl=fopen("clienttemp.txt","a");

                        do
                        {
                            fscanf(f,"%d ,%s ,%s ,%d ,%s ,%d \n",&client.IdClient,&client.nom,&client.prenom,&client.cin,&client.adresse,&client.telephone);
                            if(id != client.IdClient)
                                {
                                    fprintf(fl,"%d ,%s ,%s ,%d ,%s ,%d \n",client.IdClient,client.nom,client.prenom,client.cin,client.adresse,client.telephone);
                                }
                        }while(!feof(f));
                        fclose(f);
                        fclose(fl);
                        remove("myclients.txt");
                        rename("clienttemp.txt","myclients.txt");
                        printf("\n client supprimé avec succes\n");
                }
            else
                printf("\n suppression annulée \n");
        }
    else
        printf("cet id de client n'existe pas \n");
    gestiondeclients();
}

//**************************************Les contrats*********************************************************************************

void location()
{
    int choix;

    printf("\n                               \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
    printf("\n                               \xb3 location d'une voiture  \xb3");
    printf("\n                               \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");

    printf("\n\n");

    printf("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
    printf("\n               \xba                                                          \xba");
    printf("\n               \xba    Visualiser contrat...............................1    \xba");
    printf("\n               \xba    Louer voiture....................................2    \xba");
    printf("\n               \xba    Retourner voiture................................3    \xba");
    printf("\n               \xba    Modifier contrat.................................4    \xba");
    printf("\n               \xba    Supprimer contrat................................5    \xba");
    printf("\n               \xba    Retour...........................................6    \xba");
    printf("\n               \xba                                                          \xba");
    printf("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
    printf("\n\n                                Votre choix  :  ");

    scanf("%d",&choix);

    switch(choix)
    {
        case 1 : voircontrat();
        break;
        case 2 : louervoiture();
        break;
        case 3 : retournervoiture();
        break;
        case 4 : modifiercontrat();
        break;
        case 5 :supprimercontrat();
        break;
        case 6 : MenuPrincipal();
        break;
    }
}

//***********************************************************************************************************************

int lookfor(int num)
{
	FILE *f;
	f=fopen("contrat.txt","r");
	if(f==NULL)
		printf("cannot open the file \n");
	else
	{
		do
		{
			fscanf(f, "%d ,%d ,%d ,%d /%d /%d ,%d /%d /%d ,%d\n",&contrat.NumContrat,&contrat.IdVoiture,&contrat.IdClient,&contrat.debut.day,&contrat.debut.month,&contrat.debut.year,&contrat.fin.day,&contrat.fin.month,&contrat.fin.year,&contrat.cout );
			if(contrat.NumContrat==num)
			{
				fclose(f);
				return 1;
			}
		} while (!feof(f));
		fclose(f);
	}
	return -1;
}

//***********************************************************************************************************************

void voircontrat() //on saisie le numero du contrat dont nous voulons les informations,  et on verifie son existence par la fonction lookfor() s'il existe on affiche les informations,sinon on redemande la saisie du numero de contrat
{
	FILE *f;
	int num;
	f=fopen("contrat.txt","r"); //ouverture en mode "read"
	printf("saisir le numero du contrat que vous voulez Visualiser\n"); //saisie et lecture du numero de contrat
	scanf("%d",&num);
	fscanf(f, "%d ,%d ,%d ,%d /%d /%d ,%d /%d /%d ,%d\n",&contrat.NumContrat,&contrat.IdVoiture,&contrat.IdClient,&contrat.debut.day,&contrat.debut.month,&contrat.debut.year,&contrat.fin.day,&contrat.fin.month,&contrat.fin.year,&contrat.cout );
	if (lookfor(num)==1)// si le numero de contrat saisi existe dans le fichier
	{
		printf("voila les informations concernées votre contrat\n");  //on affiche ses informations sur l'ecran
		printf("l'id de voiture : %d \n", contrat.IdVoiture );
		printf("l'id ce client : %d \n", contrat.IdClient );
		printf("la date de debut : %d / %d / %d \n",contrat.fin.day,contrat.fin.month,contrat.fin.year);
		printf("la date de fin : %d /%d /%d \n",contrat.fin.day,contrat.fin.month,contrat.fin.year );
		printf("le cout : %d\n",contrat.cout);
	}else  // sinon un message sera afficher que ce numero n'existe pas
	{
		printf("ce numero de contrat n'existe pas \n");
	}
    fclose(f);
    location();// retour au menu precedent.
}

//***********************************************************************************************************************

void modifiercontrat()
{
    FILE *f,*fl;
    int id ;
    int rep;
    printf("saisir l'id du contrat a modifier \n");
    scanf("%d",&id);
    fflush(stdin);
    if(lookfor(id)==1)
        {
            printf("voulez vous vraiment modifier ce contrat 0/1\n");
            scanf("%d",&rep);
            fflush(stdin);
            if(rep==1)
                {
                    f=fopen("contrat.txt","r");
                    fl=fopen("file.txt","a");
                    if(fl==NULL)
                        printf("cannot oppen the file\n");
                    else
                        {
                            do
                            {
                                fscanf(f, "%d ,%d ,%d ,%d /%d /%d ,%d /%d /%d ,%d\n",&contrat.NumContrat,&contrat.IdVoiture,&contrat.IdClient,&contrat.debut.day,&contrat.debut.month,&contrat.debut.year,&contrat.fin.day,&contrat.fin.month,&contrat.fin.year,&contrat.cout );
                                if(id==contrat.NumContrat)
                                    {
                                        contrat.NumContrat=id;
                                  		printf("saisir le nouveau id de voiture \n");
                                  		scanf("%d",&contrat.IdVoiture);
                                  		printf("saisir le nouveau id de client qui loue la voiture \n");
										scanf("%d",&contrat.IdClient);
										printf("saisir la date du debut\n");
                                        printf("jour :\t");
                                        scanf("%d",&contrat.debut.day);
                                        printf("mois :\t");
                                        scanf("%d",&contrat.debut.month);
                                        printf("annee :\t");
                                        scanf("%d",&contrat.debut.year);
                                        printf("\nsaisir la date de la fin\n");
                                        printf("jour :\t");
                                        scanf("%d",&contrat.fin.day);
                                        printf("mois :\t");
                                        scanf("%d",&contrat.fin.month);
                                        printf("annee :\t");
                                        scanf("%d",&contrat.fin.year);
										printf("saisir le nouveau cout \n");
										scanf("%d",&contrat.cout);
                                    }
                                        fprintf(fl, "%d ,%d ,%d ,%d /%d /%d ,%d /%d /%d ,%d\n",contrat.NumContrat,contrat.IdVoiture,contrat.IdClient,contrat.debut.day,contrat.debut.month,contrat.debut.year,contrat.fin.day,contrat.fin.month,contrat.fin.year,contrat.cout );

                            }while(!feof(f));
                            fclose(f);
                            fclose(fl);
                            remove("contrat.txt");
                            rename("file.txt","contrat.txt");
                            printf("\n contrat modifié avec succes\n");

                        }
                }
            else
                printf("la modification est annulée");

        }
    else
        printf("\n ce numero de contrat n'existe pas \n");
    location();
}

//***********************************************************************************************************************

void supprimercontrat()
{
    FILE *f , *fl;
    int rep; ;
    int id;
    printf("saisir le numero du contrat a supprimer \n");
    scanf("%d",&id);
    fflush(stdin);
    if(lookfor(id)==1)
        {
            printf("voulez vous vraiment supprimer ce contrat ? o/n \n");
            scanf("%d",&rep);
            fflush(stdin);
            if(rep==1)
                {
                    f=fopen("contrat.txt","r");
                    fl=fopen("fich.txt","a");
                    if(fl==NULL)
                    printf("cannot open the file\n");
                    else
                    {
                        do
                        {
                            fscanf(f, "%d ,%d ,%d ,%d /%d /%d ,%d /%d /%d ,%d\n",&contrat.NumContrat,&contrat.IdVoiture,&contrat.IdClient,&contrat.debut.day,&contrat.debut.month,&contrat.debut.year,&contrat.fin.day,&contrat.fin.month,&contrat.fin.year,&contrat.cout );
                            if(id != contrat.NumContrat)
                                {
                                    fprintf(fl, "%d ,%d ,%d ,%d /%d /%d ,%d /%d /%d ,%d\n",contrat.NumContrat,contrat.IdVoiture,contrat.IdClient,contrat.debut.day,contrat.debut.month,contrat.debut.year,contrat.fin.day,contrat.fin.month,contrat.fin.year,contrat.cout );
                                }
                        }while(!feof(f));
                        fclose(f);
                        fclose(fl);
                        remove("contrat.txt");
                        rename("fich.txt","contrat.txt");
                        printf("\n contrat supprimé avec succes\n");

                    }
                }
            else
                printf("\n suppression annulée \n");
        }
    else
        printf("ce num de contrat n'existe pas \n");
    location();
}

//***********************************************************************************************************************

void creercontrat() // on demande de saisir toutes les informations de nouveau contrat et on les ecrit dans le fichier contrat.txt en utilisant la fonction fprintf().
{
	FILE *f;
	f=fopen("contrat.txt","a");
	printf("saisir le numero du contrat \t" );
	scanf("%d",&contrat.NumContrat);
	printf("saisir l'id de voiture a louer \t");
	scanf("%d",&contrat.IdVoiture);
	printf("saisir l'id de client qui loue la voiture \t");
	scanf("%d",&contrat.IdClient);
	printf("saisir la date du debut\n");
    printf("jour :\t");
    scanf("%d",&contrat.debut.day);
    printf("mois :\t");
    scanf("%d",&contrat.debut.month);
    printf("annee :\t");
    scanf("%d",&contrat.debut.year);
    printf("saisir la date de la fin\n");
    printf("jour :\t");
    scanf("%d",&contrat.fin.day);
    printf("mois :\t");
    scanf("%d",&contrat.fin.month);
    printf("annee :\t");
    scanf("%d",&contrat.fin.year);
	printf("saisir le cout \t");
	scanf("%d",&contrat.cout);
	fprintf(f,"%d ,%d ,%d ,%d /%d /%d ,%d /%d /%d ,%d\n",contrat.NumContrat,contrat.IdVoiture,contrat.IdClient,contrat.debut.day,contrat.debut.month,contrat.debut.year,contrat.fin.day,contrat.fin.month,contrat.fin.year,contrat.cout );
}

//***********************************************************************************************************************
void MenuPrincipal()
{
    int choix;

	printf("\n                               \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
	printf("\n                               \xb3 Menu Principal  \xb3");
	printf("\n                               \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
    printf("\n\n");
    printf("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
    printf("\n               \xba                                              \xba");
    printf("\n               \xba    Location..............................1   \xba");
    printf("\n               \xba    Gestion voitures......................2   \xba");
    printf("\n               \xba    Gestion clients.......................3   \xba");
    printf("\n               \xba    Quitter...............................4   \xba");
    printf("\n               \xba                                              \xba");
    printf("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
    printf("\n\n                                Votre choix  :  ");

    scanf("%d",&choix);

    switch(choix)
    {
        case 1 : location();
        break;
        case 2 : gestiondevoitures();
        break;
        case 3 : gestiondeclients();
        break;
        case 4 : MenuPrincipal();
        break;
    }
}

