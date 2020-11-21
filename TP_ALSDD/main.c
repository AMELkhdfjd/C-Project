#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct enr1
{
    char nom[30];
    char affiliation[50];
    char pays[15];
}enr1;

typedef struct date
{
    int jour;
    char mois[15];
    int annee;
    int heure;
    int minute;
}date;

typedef struct maillon1
{
    date datepres;
    char titlepres[255];
    enr1 autrpres;
    struct maillon1 *next2;
}maillon1;

typedef struct listesalle
{
    char idsalle[20];
    maillon1 *listpres;
    struct listesalle *next1;
}listesalle;
//procedure allouer un maillon de la petite liste

void allouer2(maillon1 **nouveau)
{
    *nouveau = (maillon1*)malloc(sizeof(maillon1));
}

//procedure allouer un maillon de la grande liste

void allouer1(listesalle **nouveau)
{
    *nouveau = (listesalle *)malloc(sizeof(listesalle));
}

//procedure liberer.
void liberer(maillon1 ** ancien)
{
    free(* ancien);
    *ancien=NULL;
}

//fonction qui retourne le nombre d'occurence d'une salle dans la liste des presentations

int NBSALLE(listesalle *l,char salle[20])
{
    int cpt = 0;
    listesalle *p;
    p = l;
    while(p != NULL)
    {
        if(strcmp(p->idsalle,salle) == 0)
        {
            cpt++;
        }
        p=p->next1;
    }
    return cpt;
}

//fonction qui retourne la tête de la petite liste qui contient les presentation de la salle qu'on veut suprimer

maillon1 *SUPRIMEDOUBL(listesalle *a,char salle[20],listesalle *precedant)
{
    listesalle *b,*q;
    int trouve = 0;
    maillon1 *h;
    b = a;
    int v = 1;

    while((b != NULL) && (trouve == 0))
    {
        if(strcmp(b->idsalle,salle) == 0)
        {
             if(v == 1)
             {
                 precedant->next1 = b->next1;
                 h = b->listpres;
                 trouve = 1;
             }
             else
             {
               q->next1 = b->next1;
               trouve = 1;
               h = b->listpres;
             }
        }

        else
        {
        q = b;
        b = b->next1;
        v++;
        }
    }
     return h;
}


//la fonction qui cree la liste des presentations à partir d'un fichier

listesalle *LISTEFICHIER()
{
  int i=1,j=1;
  char *prem_mot;
  char ligne[255];
  int jour,annee,heure,minute;
  char titrepres[255];
  char moi[15];
  char *nomSalle;
  char *rest;
  listesalle *w;
  maillon1 *k,*c,*s;
  char *nomAut,*affiliation,*pays;
  listesalle *l1,*p1,*q1;
  maillon1 *l2,*p2,*q2;
  FILE *fic = fopen("ConfProgram.txt","r");
  while( ! feof(fic))
  {
      fgets(ligne,255,fic);
      prem_mot = strtok(ligne," ");
      if(strcmp(prem_mot,"Date:") == 0)
      {
          rest = strtok(NULL,"\n");
          sscanf(rest,"%d %s %d",&jour,moi,&annee);
      }
      else
      {
          if(strcmp(prem_mot,"Salle:") == 0)
          {
              if(j == 2)
              {
                  l2->next2 = NULL;
              }
              else
              {
                  if(j > 2)
                  {
                      p2->next2 = NULL;
                  }
              }
              j = 1;
              nomSalle = strtok(NULL,"\n");

              if(i == 1)
              {
                  allouer1(&l1);
                  q1 = l1;
                 strcpy(l1->idsalle,nomSalle);


                  i++;
              }
              else
              {
                  allouer1(&p1);
                  q1->next1 = p1;
                  q1 = p1;
                  strcpy(p1->idsalle,nomSalle);

                  i++;
              }
          }
          else
          {
              if(strlen(prem_mot) == 5)
              {
                  prem_mot[1] = ' ';
              }
              else
              {
                  prem_mot[2] = ' ';
              }

              sscanf(prem_mot,"%d %d",&heure,&minute);
              fgets(titrepres,255,fic);
              fgets(ligne,255,fic);
              nomAut = strtok(ligne,"(");
              affiliation = strtok(NULL,",");
              pays = strtok(NULL,")");
              if(j == 1)
              {
                  allouer2(&l2);
                  l2->datepres.jour = jour;
                  l2->datepres.annee = annee;
                  strcpy(l2->datepres.mois,moi);
                  l2->datepres.heure = heure;
                  l2->datepres.minute = minute;
                  strcpy(l2->titlepres,titrepres);
                  strcpy(l2->autrpres.nom,nomAut);
                  strcpy(l2->autrpres.affiliation,affiliation);
                  strcpy(l2->autrpres.pays,pays);
                  if(i == 2)
                  {
                      l1->listpres = l2;
                  }
                  else
                  {
                      p1->listpres = l2;
                  }
                  q2 = l2;
                  j++;
              }
              else
              {
                  allouer2(&p2);
                  p2->datepres.jour = jour;
                  p2->datepres.annee = annee;
                  strcpy(p2->datepres.mois,moi);
                  p2->datepres.heure = heure;
                  p2->datepres.minute = minute;
                  strcpy(p2->titlepres,titrepres);
                  strcpy(p2->autrpres.nom,nomAut);
                  strcpy(p2->autrpres.affiliation,affiliation);
                  strcpy(p2->autrpres.pays,pays);
                  q2->next2 = p2;
                  q2 = p2;
                  j++;

              }
          }
      }
  }
  fclose(fic);
  p1->next1 = NULL;
  if(j == 2)
    {
        l2->next2 = NULL;
    }
  else
    {
        if(j > 2)
            {
                p2->next2 = NULL;
            }
    }

//la partie de la supression des doublons (on a des salles qui se repète plus de 1 fois)


w = l1;
while(w != NULL)
{

    while((NBSALLE(w,w->idsalle)) >= 2)
    {
         k = w->listpres;
        while(k != NULL)
        {
            c = k;
            k = k->next2;
        }
        s = SUPRIMEDOUBL(w->next1,w->idsalle,w);
        c->next2 = s;
    }
    w = w->next1;
}
    return l1;
}



//la procedure qui affiche la petite liste

void AFFICHEPRES(maillon1 *g)
{
    maillon1 *p;
    p=g;
    while(p != NULL)
    {
        printf("date: %d",p->datepres.jour);
        printf("  %s",p->datepres.mois);
        printf("  %d\n",p->datepres.annee);
        printf("%d:",p->datepres.heure);
        printf("%d\n",p->datepres.minute);
        printf("le titre est: %s\n",p->titlepres);
        printf("%s",p->autrpres.nom);
        printf("(%s",p->autrpres.affiliation);
        printf(",%s)\n",p->autrpres.pays);
        p=p->next2;
    }
}

//procedure affichage du programme

void AFFICHAGE(listesalle *h)
{
    listesalle *l;
    l=h;
    int i=1;
    while(l != NULL)
    {
        printf("salle n %d: ",i);
        i++;
        printf("%s\n",l->idsalle);
        printf("la liste des presentations de cette salle est :\n");
        AFFICHEPRES(l->listpres);
        l=l->next1;

    }
}


//PARCOURT DE LISTE
// PARTIE "A"

//afficher tout le programme d'une salle donnee


void AFFICHESALLE(listesalle *l)
{
    char salle[20];
    printf("donnez la salle que vous souhaitez afficher sa liste de presentation SVP !");
    scanf("%s",salle);
    listesalle *p;
    p=l;
    printf("%s\n",salle);
    printf("la liste des presentations de cette salle est : \n");
       while(p != NULL)
       {
           if(strcmp(p->idsalle,salle) == 0)
           {
              AFFICHEPRES(p->listpres);
           }
           p=p->next1;
       }
}

//afficher la programme d'une salle donnee pour une date donnee
void AFFICHESALLEDATE(listesalle *l)
{
    char salle[20];
    int jour,annee;
    char moi[15];
    printf("donnez la salle que vous souhaitez afficher sa liste de presentation SVP !");
    scanf("%s",salle);
    printf("donner le jour/moi/annee que vous voulez affichez la liste des presentations ");
    scanf("%d",&jour);
    scanf("%s",moi);
    scanf("%d",&annee);
    printf("%s\n",salle);
    printf("la liste des presentations de cette salle est : \n");
    listesalle *p;
    maillon1 *k;
    p=l;
    while(p != NULL)
    {
        if((strcmpi(p->idsalle,salle) == 0))
        {
        k=p->listpres;
        while(k != NULL)
        {
        if((jour == k->datepres.jour) && (annee == k->datepres.annee) && (strcmpi(moi,k->datepres.mois)) == 0)
        {
            printf(" %d:%d\n",k->datepres.heure,k->datepres.minute);
            printf(" le titre de cette representation est : %s\n",k->titlepres);
            printf("les informations de l'auteur sont :\n");
            printf("le nom de l'auteur : %s\n",k->autrpres.nom);
            printf("son affiliation est : %s\n",k->autrpres.affiliation);
            printf("son pays est : %s\n",k->autrpres.pays);
        }
        k=k->next2;
        }
        }
        p=p->next1;
    }
}


//PARTIE "B"

//procedure qui affiche le programme d'une date donnée.

void AFFICHEDATE(listesalle *l,int jour,char moi[15],int annee)
{
    //remove("ConfProgram.txt");
    //FILE *fich = fopen("listeficher","a+");


    listesalle *p;
    maillon1 *k;
    p=l;
    char salle[20];
    strcpy(salle,"SESE");
    printf("Date: %d %s %d\n",jour,moi,annee);

    while(p != NULL)
    {
         k=p->listpres;
         while(k != NULL)
         {
             if((jour == k->datepres.jour) && (annee == k->datepres.annee) && (strcmpi(moi,k->datepres.mois)) == 0)
             {
                 if(strcmp(salle,p->idsalle) != 0)
                 {
                       printf("Salle : %s\n",p->idsalle);
                       strcpy(salle,p->idsalle);
                 }
                 printf("%d:%d\n",k->datepres.heure,k->datepres.minute);
                 printf("Titre : %s\n",k->titlepres);
                 printf("le nom de l'auteur est : %s\n",k->autrpres.nom);
                 printf("son affiliation est : %s\n",k->autrpres.affiliation);
                 printf("son pays est : %s\n",k->autrpres.pays);
                 k->datepres.annee = k->datepres.annee - 1;
             }
             k=k->next2;
         }
         p=p->next1;
    }
}

//la procedure qui affiche toutes  les presentations (regroupées par date des presentations)

void AFFICHEDATETOUT(listesalle *l)
{
    listesalle *p;
    maillon1 *k;
    p=l;
    k=p->listpres;
    int annee;
    annee = k->datepres.annee;
    while(p != NULL)
    {
        k=p->listpres;
        while(k != NULL)
        {
            if(annee == k->datepres.annee)
            {
                AFFICHEDATE(p,k->datepres.jour,k->datepres.mois,k->datepres.annee);
            }
            k=k->next2;
        }
        p=p->next1;
    }
    p=l;
    while(p != NULL)
    {
        k=p->listpres;
        while(k != NULL)
        {
        if(k->datepres.annee != 2019)
        {
            k->datepres.annee = k->datepres.annee + 1;//pour rendre toutes les années comme elles étaient avant.
        }
        k=k->next2;
        }
        p=p->next1;
    }
}

//PARTIE "C"

//procedure qui affiche les informations d'une presentation en fonction du titre de la presentation

void AFFICHETITRE(listesalle *l)
{
    char titre[255];
    printf("donner le titre de la presentation que vous voulez afficher la liste des presentations\n");
    fgets(titre,255,stdin);
    listesalle *p;
    maillon1 *k;
    p=l;
    while(p != NULL)
    {
        k=p->listpres;
        while(k != NULL)
        {
            if(strcmpi(titre,k->titlepres) == 0)
            {
                printf("Salle : %s\n",p->idsalle);
                printf("Date : %d %s %d\n",k->datepres.jour,k->datepres.mois,k->datepres.annee);
                printf("%d:%d\n",k->datepres.heure,k->datepres.minute);
                printf("le nom de l'auteur est : %s\n",k->autrpres.nom);
                printf("son affiliation est : %s\n",k->autrpres.affiliation);
                printf("son pays est : %s\n",k->autrpres.pays);

            }
            k=k->next2;
        }
        p=p->next1;
    }
}

//procedure qui affiche toutes les informations d'une presentation en fonction du nom du presentateur

void AFFICHEAUTNOM(listesalle *l)
{
    char nom[255];
    printf("donner le nom de l'auteur que vous voulez afficher la liste des presentations\n");
    fgets(nom,255,stdin);
    nom[strlen(nom)-1] = '\0';  //pour enlever le \n que la fonction fgets ajoute à la fin.
    listesalle *p;
    maillon1 *k;
    p=l;
    while(p != NULL)
    {
        k=p->listpres;
        while(k != NULL)
        {
            if(strcmpi(nom,k->autrpres.nom) == 0)
            {
                printf("Salle : %s\n",p->idsalle);
                printf("Date : %d %s %d\n",k->datepres.jour,k->datepres.mois,k->datepres.annee);
                printf("%d:%d\n",k->datepres.heure,k->datepres.minute);
                printf("%s",k->titlepres);
                printf("Son affiliation est : %s\n",k->autrpres.affiliation);
                printf("Son pays est : %s\n",k->autrpres.pays);
            }
            k=k->next2;
        }
        p=p->next1;
    }
}

//INSERTION D'ELEMENT


//les procedures concernées par la modification du fichier des presentation au cas d'ajout ou de supression.

//la procedure qui ajoute au fichier toutes les modifications apportées par l'utilisateur comme l'ajout et la supression des presentations

void CORRIGEFICHIER(listesalle *l)
{
    listesalle *p;
    maillon1 *k;
    int jour;
    char moi[15];
    p=l;
    k=p->listpres;
    int annee;
    annee = k->datepres.annee;
    remove("ConfProgram.txt");
    FILE *fich = fopen("ConfProgram.txt","a+");
    while(p != NULL)
    {
        k=p->listpres;
        while(k != NULL)
        {
            if(annee == k->datepres.annee)
            {
                   jour = k->datepres.jour;
                   annee = k->datepres.annee;
                   strcpy(moi,k->datepres.mois);
                   listesalle *r;
                   maillon1 *h;
                   r=l;
                   char salle[20];
                   strcpy(salle,"SESE");
                   fprintf(fich,"Date: %d %s %d\n",jour,moi,annee);
                   while(r != NULL)
                    {
                    h=r->listpres;
                    while(h != NULL)
                    {
                    if((jour == h->datepres.jour) && (annee == h->datepres.annee) && (strcmpi(moi,h->datepres.mois)) == 0)
                      {
                    if(strcmpi(salle,r->idsalle) != 0)
                    {
                       fprintf(fich,"Salle: %s\n",r->idsalle);
                       strcpy(salle,r->idsalle);
                    }
                    fprintf(fich,"%d",h->datepres.heure);
                 if(h->datepres.minute == 0)
                 {
                  fprintf(fich,":00\n");
                 }
                 else
                 {
                     fprintf(fich,":%d\n",h->datepres.minute);
                 }
                 fprintf(fich,"%s",h->titlepres);
                 fprintf(fich,"%s (%s, %s)\n",h->autrpres.nom,h->autrpres.affiliation,h->autrpres.pays);
                 h->datepres.annee = h->datepres.annee - 1;
                      }
                  h=h->next2;
                   }
                  r=r->next1;
                    }

            }
            k=k->next2;
        }
        p=p->next1;
    }
    p=l;
    while(p != NULL)
    {
        k=p->listpres;
        while(k != NULL)
        {
        if(k->datepres.annee != 2019)
        {
            k->datepres.annee = k->datepres.annee + 1;//pour rendre toutes les années comme elles étaient avant.
        }
        k=k->next2;
        }
        p=p->next1;
    }
    fclose(fich);
}


//PARTIE "B"
//procedure qui ajoute une nouvelle salle

void AJOUTERSALLE(listesalle *l)
{
    listesalle *s,*b,*l1,*z;
    int i=1,k=1;
    int ajouter=1;
    char titre[255];
    maillon1 *l2,*p2,*q2;
    b=l;
    z = l;
    while(b != NULL)
    {
        s=b;
        b=b->next1;
    }
    allouer1(&l1);
    s->next1=l1;
    l1->next1=NULL;
    printf("donner la salle %d  ",i);
        i++;
        scanf(" %s",l1->idsalle);
        while(ajouter == 1)
        {
            if(k ==1)
            {
                allouer2(&l2);
                printf("donner la date  ");
                scanf(" %d",&l2->datepres.jour);
                scanf(" %s",l2->datepres.mois);
                scanf(" %d",&l2->datepres.annee);
                scanf(" %d",&l2->datepres.heure);
                scanf(" %d",&l2->datepres.minute);
                printf("donner le titre  ");
                fgets(titre,255,stdin);
                strcpy(l2->titlepres,titre);
                printf("donner les informations de l'auteur  ");
                scanf(" %s",l2->autrpres.nom);
                scanf(" %s",l2->autrpres.affiliation);
                scanf(" %s",l2->autrpres.pays);
                q2=l2;
                k++;
            }
            else
            {
                allouer2(&p2);
                q2->next2=p2;
                printf("donner la date  ");
                scanf(" %d",&p2->datepres.jour);
                scanf(" %s",p2->datepres.mois);
                scanf(" %d",&p2->datepres.annee);
                scanf(" %d",&p2->datepres.heure);
                scanf(" %d",&p2->datepres.minute);
                printf("donner le titre  ");
                fgets(titre,255,stdin);
                titre[strlen(titre)-1] = '\0';
                strcpy(p2->titlepres,titre);
                printf("donner les informations de l'auteur  ");
                scanf(" %s",p2->autrpres.nom);
                scanf(" %s",p2->autrpres.affiliation);
                scanf(" %s",p2->autrpres.pays);
                q2=p2;
                k++;
            }
            printf("on ajoute encore dans la petite liste 0 pour sortir 1 pour oui");
            scanf("%d",&ajouter);
        }
        l1->listpres=l2;
        if(k == 2)
        {
         l2->next2=NULL;
        }
        else
        {
            p2->next2=NULL;
        }
    CORRIGEFICHIER(z);

}

//la fonction qui verifie si on peut inserer une nouvelle presentation ou non elle retourn 1(oui) et 0(non)
//pour verifier si l'utilisateur peut inserer une nouvelle presentation ou non.
int SIAJOUTER(listesalle *l,char salle[10],int jour,char moi[15],int annee,int heure,int minute)
{
    int trouve=1;
    listesalle *p;
    maillon1 *k;
    p=l;
    while((trouve == 1) && (p != NULL))
    {
        if(strcmpi(p->idsalle,salle) == 0)
        {
            k=p->listpres;
            while((k != NULL) && (trouve == 1))
            {
                if((k->datepres.jour == jour) && (k->datepres.annee == annee) && (heure == k->datepres.heure) && (minute == k->datepres.minute) && (strcmpi(moi,k->datepres.mois) == 0))
                {
                    trouve = 0;
                }
                k=k->next2;

            }

        }
        p=p->next1;
    }
    return trouve;
}


//la fonction qui compare deux temps elle retourne (-1) si temps1 < temps2 et (0) si temps1 = temps2 et (1) si temps1>temps2
//pour comparer deux temps et voir le bon emplacement pour inserer une presentation pour garder l'ordre chronologique.
int COMPTIME(int heure1,int minute1,int heure2,int minute2)
{
    if(heure1 < heure2)
    {
        return -1;
    }
    else
    {
        if(heure1 > heure2)
        {
            return 1;
        }
        else
        {
            if(minute1 < minute2)
            {
                return -1;
            }
            else
            {
                if(minute1 > minute2)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        }
    }
}
//PARTIE "A"
//la procedure qui ajoute une presentation

void AJOUTERPRES(listesalle *l)
{
    listesalle *p,*f;
    maillon1 *a,*b,*c,*k,*q;
    char salle[15];
    char moi[15];
    int jour,annee,heure,minute;
    p=l;
    f = l;
    printf("donner la salle ");
    scanf(" %s",&salle);
    printf("donner la date (jour/moi/annee)");
     scanf("%d",&jour);
     scanf(" %s",&moi);
     scanf("%d",&annee);
    printf("donner l'heure et minute");
    scanf("%d",&heure);
    scanf("%d",&minute);
    int add = 0;
     if(SIAJOUTER(p,salle,jour,moi,annee,heure,minute) == 1)                 //alors on peut ajouter une nouvelle presentation
     {
         while((p != NULL) && (add == 0))
         {


             if(strcmpi(salle,p->idsalle) == 0)
             {
                 k=p->listpres;
                 q=k->next2;

                 if((jour == k->datepres.jour) && (annee == k->datepres.annee) && (strcmpi(moi,k->datepres.mois) == 0) && (COMPTIME(k->datepres.heure,k->datepres.minute,heure,minute) == 1))
                 {

                        allouer2(&a);
                        a->next2=k;
                        p->listpres=a;
                        a->datepres.jour = jour;
                        a->datepres.annee = annee;
                        strcpy(a->datepres.mois,moi);
                        a->datepres.heure = heure;
                        a->datepres.minute = minute;
                        printf("donner le titre de votre presentation SVP !!");
                        scanf(" %s",&a->titlepres);
                        printf("donner les informations de l'auteur (nom/affiliation/pays)");
                        scanf(" %s",&a->autrpres.nom);
                        scanf(" %s",&a->autrpres.affiliation);
                        scanf(" %s",&a->autrpres.pays);
                        add = 1;
                 }
                 else
                 {
                     while((k != NULL) && (add == 0))
                     {
                         if(q != NULL)
                         {
                             if((jour == k->datepres.jour) && (annee == k->datepres.annee) && (strcmpi(moi,k->datepres.mois) == 0) && (jour == q->datepres.jour) && (annee == q->datepres.annee) && (strcmpi(moi,q->datepres.mois) == 0) && (k->datepres.heure <= heure) && (COMPTIME(q->datepres.heure,q->datepres.minute,heure,minute) == 1))
                             {


                                    allouer2(&b);
                                    k->next2 = b;
                                    b->next2 = q;
                                    b->datepres.jour = jour;
                                    b->datepres.annee = annee;
                                    strcpy(b->datepres.mois,moi);
                                    b->datepres.heure = heure;
                                    b->datepres.minute = minute;
                                    printf("donner le titre de votre presentation SVP !!");
                                    scanf("%s",b->titlepres);
                                    printf("donner les informations de l'auteur (nom/affiliation/pays)");
                                    scanf(" %s",b->autrpres.nom);
                                    scanf(" %s",b->autrpres.affiliation);
                                    scanf(" %s",b->autrpres.pays);
                                    add = 1;
                             }
                             else
                             {
                             if((jour == k->datepres.jour) && (annee == k->datepres.annee) && (strcmpi(moi,k->datepres.mois) == 0) && ((jour != q->datepres.jour) || (annee != q->datepres.annee) || (strcmpi(moi,q->datepres.mois) != 0)) && (heure >=k->datepres.heure))
                             {
                                    allouer2(&b);
                                    k->next2 = b;
                                    b->next2 = q;
                                    b->datepres.jour = jour;
                                    b->datepres.annee = annee;
                                    strcpy(b->datepres.mois,moi);
                                    b->datepres.heure = heure;
                                    b->datepres.minute = minute;
                                    printf("donner le titre de votre presentation SVP !!");
                                    scanf(" %s",&b->titlepres);
                                    printf("donner les informations de l'auteur (nom/affiliation/pays)");
                                    scanf(" %s",&b->autrpres.nom);
                                    scanf(" %s",&b->autrpres.affiliation);
                                    scanf(" %s",&b->autrpres.pays);
                                    add = 1;
                             }
                             }
                         }
                         else
                         {
                         if((jour == k->datepres.jour) && (annee == k->datepres.annee) && (strcmpi(moi,k->datepres.mois) == 0) && (heure >= k->datepres.heure) && (q == NULL))
                         {
                             allouer2(&c);
                             k->next2=c;
                             c->next2=NULL;
                             c->datepres.jour = jour;
                             c->datepres.annee = annee;
                             strcpy(c->datepres.mois,moi);
                             c->datepres.heure = heure;
                             c->datepres.minute = minute;
                             printf("donner le titre de votre presentation SVP !!");
                             scanf(" %s",&c->titlepres);
                             printf("donner les informations de l'auteur (nom/affiliation/pays)");
                             scanf(" %s",&c->autrpres.nom);
                             scanf(" %s",&c->autrpres.affiliation);
                             scanf(" %s",&c->autrpres.pays);
                             add = 1;

                         }
                         }
                         k=q;
                         if(q != NULL)
                         {
                             q=q->next2;
                         }
                     }
                 }
             }
             p=p->next1;
         }
     }
     else
     {
         printf("vous ne pouvez pas ajouter une nouvelle presentation\n ");
     }
//la partie qui modifie le contenu du fichier et ajouter la presentation à la liste des presentations.
  CORRIGEFICHIER(f);

}


//SUPRESSION D'ELEMENT
//PARTIE "A"

//procedure qui suprime une presentation.

void SUPRIMEPRES(listesalle *l)
{
    char titre[255];
    printf("donner le titre de la presentation que vous voulez suprimer\n");
    fgets(titre,255,stdin);
    listesalle *p,*u;
    maillon1 *k,*n,*q;
    int m=1;
    p=l;
    u = l;
    int jour,annee,heure;
    char moi[15];
    while(p != NULL)
    {
        k=p->listpres;
        while(k != NULL)
        {
            if(strcmpi(titre,k->titlepres) == 0)
            {
                jour = k->datepres.jour;
                annee = k->datepres.annee;
                strcpy(moi,k->datepres.mois);
                heure = k->datepres.heure;

                if(m == 1) //si le maillon suprimé c'est la tête.
                {
                    p->listpres = k->next2;
                    n=k->next2;
                    liberer(k);
                }
                else //si c'est pas la tête.
                {
                        q->next2=k->next2;
                        n=k->next2;
                        liberer(k);}
                        if(heure < 14) //on fait le décalage just le matin puisque la presentation qu'on veut suprimer et au matin.
                        {
                         while((n != NULL) && (jour == n->datepres.jour) && (annee == n->datepres.annee) && (strcmpi(moi,k->datepres.mois) == 0) && (n->datepres.heure < 14))
                      {
                       if(n->datepres.minute == 30)
                       {
                           n->datepres.minute = n->datepres.minute - 30;
                       }
                       else
                       {
                            n->datepres.minute = n->datepres.minute + 30;
                            n->datepres.heure = n->datepres.heure - 1;
                       }
                       m++;
                       n=n->next2;
                      }
                    }
                    else  //ce bloq est pour le dècalage si l'heure de la presenation suprimée est l'après midi.
                    {
                         while((n != NULL) && (jour == n->datepres.jour) && (annee == n->datepres.annee) && (strcmpi(moi,k->datepres.mois) == 0))
                      {
                       if(n->datepres.minute == 30)
                       {
                           n->datepres.minute = n->datepres.minute - 30;
                       }
                       else
                       {
                            n->datepres.minute = n->datepres.minute + 30;
                            n->datepres.heure = n->datepres.heure - 1;
                       }
                       m++;
                       n=n->next2;
                      }

                    }
            }
            q=k;
            k=k->next2;
            m++;
                }
          p=p->next1;
    }
    CORRIGEFICHIER(u);
}

//PARTIE "B"
//procedure qui suprime toutes les presentations d'un auteur

void SUPRIMEAUT(listesalle *l)
{
    char nom[30];
    printf("donner le nom de l'auteur que vous voulez suprimer");
    scanf("%s",nom);
    listesalle *p,*d;
    maillon1 *k,*n,*q;
    int jour,annee,heure;
    char moi[15];
    p=l;
    d = l;
    while(p != NULL)
    {
        k=p->listpres;
        //cette partie fonctionne si le maillon qu'on veut suprimer est la tête.
        while(strcmpi(k->autrpres.nom,nom) == 0)
        {
                jour = k->datepres.jour;
                annee = k->datepres.annee;
                strcpy(moi,k->datepres.mois);
                heure = k->datepres.heure;
                n=k->next2;
                liberer(k);
                k=n;
                p->listpres=k;
                if(heure < 14)   //on fait le décalage just le matin puisque la presentation qu'on veut suprimer et au matin.
                        {
                         while((n != NULL) && (jour == n->datepres.jour) && (annee == n->datepres.annee) && (strcmpi(moi,k->datepres.mois) == 0) && (n->datepres.heure < 14))
                      {
                       if(n->datepres.minute == 30)
                       {
                           n->datepres.minute = n->datepres.minute - 30;
                       }
                       else
                       {
                            n->datepres.minute = n->datepres.minute + 30;
                            n->datepres.heure = n->datepres.heure - 1;
                       }
                       n=n->next2;
                      }
                    }
                    else     //ce bloq est pour le dècalage si l'heure de la presenation suprimée est l'après midi.
                    {
                         while((n != NULL) && (jour == n->datepres.jour) && (annee == n->datepres.annee) && (strcmp(moi,k->datepres.mois) == 0))
                      {
                       if(n->datepres.minute == 30)
                       {
                           n->datepres.minute = n->datepres.minute - 30;
                       }
                       else
                       {
                            n->datepres.minute = n->datepres.minute + 30;
                            n->datepres.heure = n->datepres.heure - 1;
                       }
                       n=n->next2;
                      }
                    }


        }
        //si ce n'est pas la tête.
        while(k != NULL)
        {
            if(strcmpi(k->autrpres.nom,nom) == 0)
            {
                jour = k->datepres.jour;
                annee = k->datepres.annee;
                strcpy(moi,k->datepres.mois);
                heure = k->datepres.heure;
                q->next2=k->next2;
                n=k->next2;
                liberer(k);
                k=q;
                if(heure < 14) //le metin.
                        {
                         while((n != NULL) && (jour == n->datepres.jour) && (annee == n->datepres.annee) && (strcmpi(moi,k->datepres.mois) == 0) && (n->datepres.heure < 14))
                      {
                       if(n->datepres.minute == 30)
                       {
                           n->datepres.minute = n->datepres.minute - 30;
                       }
                       else
                       {
                            n->datepres.minute = n->datepres.minute + 30;
                            n->datepres.heure = n->datepres.heure - 1;
                       }
                       n=n->next2;
                      }
                    }
                    else // l'aprés midi.
                    {
                         while((n != NULL) && (jour == n->datepres.jour) && (annee == n->datepres.annee) && (strcmpi(moi,k->datepres.mois) == 0))
                      {
                       if(n->datepres.minute == 30)
                       {
                           n->datepres.minute = n->datepres.minute - 30;
                       }
                       else
                       {
                            n->datepres.minute = n->datepres.minute + 30;
                            n->datepres.heure = n->datepres.heure - 1;
                       }
                       n=n->next2;
                      }
                    }


            }
            q=k;
            k=k->next2;
        }
        p=p->next1;
    }
    CORRIGEFICHIER(d);
}

int main()
{
    int t = 1;
    int choix;
    listesalle *m;
    m = LISTEFICHIER();
    while(t == 1)
    {
    listesalle *m;
    m = LISTEFICHIER();
    int annee,jour;
    char moi[15];
    printf("le menu : \n");
    printf(" VOICI LES FONCTIONS ET LES PROCEDURES QUE VOUS POUVEZ UTILISER AVEC CETTE APPLICATION : \n");
    printf("1\\Afficher tout le programme d'une salle donnee.\n");
    printf("2\\Afficher la programme d'une salle donnee pour une date donnee.\n");
    printf("3\\Afficher toutes  les presentations de la conference (regroupees par date des presentations).\n");
    printf("4\\Afficher le programme d'une date donnee (regroupe par salle).\n");
    printf("5\\Affiche les informations d'une presentation en fonction du titre de la presentation.\n");
    printf("6\\Affiche tous les informations d'une presentation en fonction du nom du presentateur.\n");
    printf("7\\Ajouter une presentation.\n");
    printf("8\\Ajouter une nouvelle salle.\n");
    printf("9\\Suprimer une presentation.\n");
    printf("10\\Suprimer toutes les presentations d'un auteur.\n");
    printf("entrer votre choix \n");
    scanf("%d",&choix);
    switch (choix)
    {
    case 1 :
        AFFICHESALLE(m);
        break;
    case 2 :
        AFFICHESALLEDATE(m);
        break;
    case 3 :
        AFFICHEDATETOUT(m);
        break;
    case 4 :
        printf("donner la date que vous voulez afficher la presentation (jour/moi/annee)");
        scanf("%d",&jour);
        scanf("%s",moi);
        scanf("%d",&annee);
        AFFICHEDATE(m,jour,moi,annee);
        break;
    case 5 :
        AFFICHETITRE(m);
        break;
    case 6 :
        printf("veillez ajouter un espace a la fin du nom\n");
        AFFICHEAUTNOM(m);
        break;
    case 7 :
        AJOUTERPRES(m);
        break;
    case 8 :
        AJOUTERSALLE(m);
        break;
    case 9 :
        SUPRIMEPRES(m);
        break;
    case 10 :
        SUPRIMEAUT(m);
        break;
    default:
        printf("repeter votre choix");
        break;
    }
    printf("on ajoute\n");
    scanf("%d",&t);
    }


    system("pause");
}
