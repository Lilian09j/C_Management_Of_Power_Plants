// JAOUANNE Lilian et GARCON Bastian 20/10/2022
// Projet de GIF 1301

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Declaration des types
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////// Liste des villes ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	typedef struct ville
    {
		int codePostal;
		char nomVille[50];
		struct ville * villeSuivante;
	} Tville;

	typedef Tville * PTville;
	
/////////////////////////////////// Liste des lignes electriques //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	typedef struct lignesElectrique
    {
		int puissance;
		PTville villeDesservie;	
		struct lignesElectrique * ligneSuivante ;
	} TlignesElectrique;
	
	typedef TlignesElectrique * PTligneElectrique;
	
//////////////////////////////////////// Liste des centrales //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	typedef struct centrale
    {
		int codeCentrale; 
		PTligneElectrique villeDependante; // Pointeur sur la liste des lignes
		// Pointeur sur le bidon des lignes electriques de la centrale.
		// pfinLigne NE DESSER PAS DE VILLES !!!
		PTligneElectrique pfinLigne;
		struct centrale * ptsuivant;
		struct centrale * ptprecedent;
	}Tcentrale;
	
	typedef Tcentrale * PTcentrale;

//////////////////////// Structure contenant tout les bidons des listes poublelles ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ben
{
	PTville pdebutV;
	PTville pfinV;
	PTcentrale pdebutC;
	PTcentrale pfinC;
	PTligneElectrique pdebutL;
	PTligneElectrique pfinL;
}Tben;

typedef Tben *PTben;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                           Fonctions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Met le curseur a la position lig col ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gotoligcol(int lig , int col)
{
	COORD mycoord;
		
	mycoord.X = col;
	mycoord.Y = lig;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ) , mycoord);
}

// Supprimer tout ce qu'il y a a l ecran //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClearConsole(HANDLE hConsole){
	system("cls");//clean la console
	SetConsoleTextAttribute(hConsole, 16 * 2 + 15);//vert fonce sur noir
	gotoligcol(0,3);
	printf("---- Gestion du reseau electrique ----\n\n");
	SetConsoleTextAttribute(hConsole, 16 * 0 + 15);//blanc sur noir
}

// Cree un cadre à la position (x,y) de hauteur "haut" et de largeur "larg" ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void cadre(int x, int y, int haut, int larg){
	int i, j;
	char c, cvertical, chorizontal, cangleGH, cangleGB, cangleDH, cangleDB;
	cvertical = 186;
   	chorizontal = 205;
   	cangleGH = 201;
   	cangleGB = 200;
   	cangleDH = 187;
   	cangleDB = 188;
	   	
	//ligne haut
    gotoligcol(x,y);
	printf("%c",cangleGH);
	i = larg; 
	while(i > 0){	
		printf("%c",chorizontal);
		i = i - 1;
	};
	printf("%c" , cangleDH);
	// ligne intermediaires
	j = haut;
	
	while(j > 0){
		gotoligcol(x + j, y);	
		printf("%c" , cvertical);
		i = larg; 
		while(i > 0)	{	
			printf("%c",' ');
			i = i - 1;
		};
		j = j - 1;
		printf("%c" , cvertical);
	}
	//ligne bas
    gotoligcol(x + haut , y);
	printf("%c" , cangleGB);
	i = larg; 
	while(i > 0)	{	
		printf("%c" , chorizontal);
		i = i - 1;
	};
	printf("%c" , cangleDB);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Affiche(HANDLE hConsole , char c , int fond , int couleur)
{
	int i;
		
	i = 16 * fond + couleur;
	SetConsoleTextAttribute(hConsole , i);
	printf("%c " , c);
}

// Afficher les MENUS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AfficheMenu(HANDLE hConsole)
{	
	SetConsoleTextAttribute(hConsole, 16 * 7 + 0);//noir sur gris clair
	gotoligcol(5,5);printf("*********************************");
	gotoligcol(6,5);printf("*             MENU              *");
	gotoligcol(7,5);printf("*********************************");		
	SetConsoleTextAttribute(hConsole, 16 * 0 + 15);			
	gotoligcol(10,9);printf("1 - Gestion des centrales ");	
	gotoligcol(11,9);printf("2 - Gestion des villes ");
	gotoligcol(12,9);printf("3 - Gestion des lignes electriques ");
	gotoligcol(13,9);printf("4 - Gestion du reseau ");
	gotoligcol(15,9);printf("ESC - Quitter");
}
void AfficheMenuCentrales(HANDLE hConsole)
{	
	SetConsoleTextAttribute(hConsole, 16 * 7 + 0);//noir sur gris clair
	gotoligcol(6,5);printf("---   Gestion Des Centrales   ---");	
	SetConsoleTextAttribute(hConsole, 16 * 0 + 15);			
	gotoligcol(10,9);printf("1 - Ajouter des centrales ");	
	gotoligcol(11,9);printf("2 - Supprimer des centrales ");
	gotoligcol(12,9);printf("3 - Afficher les centrales ");
	gotoligcol(14,9);printf("ESC - Retour");
}
void AfficheMenuVilles(HANDLE hConsole)
{	
	SetConsoleTextAttribute(hConsole, 16 * 7 + 0);//noir sur gris clair
	gotoligcol(6,5);printf("---    Gestion Des Villes    ---");
	SetConsoleTextAttribute(hConsole, 16 * 0 + 15);			
	gotoligcol(10,9);printf("1 - Ajouter des villes ");	
	gotoligcol(11,9);printf("2 - Supprimer des villes ");
	gotoligcol(12,9);printf("3 - Afficher les villes ");
	gotoligcol(14,9);printf("ESC - Retour");
}
void AfficheMenuLignes(HANDLE hConsole)
{	
	SetConsoleTextAttribute(hConsole, 16 * 7 + 0);//noir sur gris clair
	gotoligcol(6,5);printf("--- Gestion Des Lignes Electriques ---");	
	SetConsoleTextAttribute(hConsole, 16 * 0 + 15);			
	gotoligcol(10,9);printf("1 - Ajouter lignes electriques ");	
	gotoligcol(11,9);printf("2 - Supprimer lignes electriques ");
	gotoligcol(12,9);printf("3 - Afficher lignes des villes");
	gotoligcol(13,9);printf("4 - Afficher lignes des centrales");
	gotoligcol(15,9);printf("ESC - Retour");
}
void AfficheMenuReseau(HANDLE hConsole)
{	
	SetConsoleTextAttribute(hConsole, 16 * 7 + 0);//noir sur gris clair
	gotoligcol(6,5);printf("---     Gestion Du Reseau     ---");
	SetConsoleTextAttribute(hConsole, 16 * 0 + 15);			
	gotoligcol(10,9);printf("1 - Charger un reseau ");	
	gotoligcol(11,9);printf("2 - Supprimer le reseau ");
	gotoligcol(12,9);printf("3 - Enregistrer le reseau ");
	gotoligcol(14,9);printf("ESC - Retour");
}

// Affiche le code de toutes les centrales ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AfficherCentrales(PTcentrale pDebut , PTcentrale pFin)
{
	if(pDebut->codeCentrale > 0)
	{
		PTcentrale pY;
		pY = pDebut;
	
		while(pY->ptsuivant != pFin)
		{
			pY = pY->ptsuivant;
		
			printf("\tCode centrale : %d\n" , pY->codeCentrale);		
		}
	}
	else
	{
		printf("Il n'y a pas de centrales !\n");
	}
}

// Affiche le code postale et le nom de toutes les villes /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AfficherVilles(PTville pDebut , PTville pFin, int ligne)	//On donne a quelle ligne afficher les villes
{	
	int i = 0;
	if(pDebut->codePostal > 0)
	{
		PTville pY;
		pY = pDebut;
		
		while(pY->villeSuivante != pFin)
		{
			pY = pY->villeSuivante;
			gotoligcol(ligne+i,0);printf("\t%s" , pY->nomVille);
			gotoligcol(ligne+i,25);printf("%d\n" , pY->codePostal);
			i++;	
		}
	}
	else
	{
		printf("Il n'y a pas de villes !\n");
	}
}

// Verifie que la centrale avec le codeCentrale = num existe //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ExistanceCentrale(PTcentrale pDebut , PTcentrale pFin , int num)
{
	PTcentrale pX;
 	pX = pDebut->ptsuivant;
    
    // pour etre sur que la boucle while s arrete
	pFin->codeCentrale = num;
	while(pX->codeCentrale != num)
	{
		pX = pX->ptsuivant;
	}
	if(pX != pFin)
		return 1;	//true : le codeCentrale existe
	else
		return 0;	//false : le codeCentrale n existe pas
}

// Verifie que la ville avec le codePostale = cp existe ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ExistanceVille(PTville pDebut , PTville pFin , int cp)
{
	PTville pX;
 	pX = pDebut->villeSuivante;

    // pour etre sur que la boucle while s arrete
	pFin->codePostal = cp;
	while(pX->codePostal != cp)
	{
		pX = pX->villeSuivante;
	}
	if(pX != pFin)
		return 1;	//true : le codePostal existe
	else
		return 0;	//false : le codePostal n existe pas
}

// Renvoie un PTcentrale avec le codeCentrale = num ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PTcentrale NumCentrale(PTcentrale pDebut , PTcentrale pFin , int num)
{
	PTcentrale pX;
	pX = pDebut->ptsuivant;

	// pour etre sur que la boucle while s arrete
	pFin->codeCentrale = num;
	while(pX->codeCentrale != num)
	{
		pX = pX->ptsuivant;
	}
	if(pX != pFin)
		return(pX);
	else
		return(NULL);
}

// Renvoie un PTville avec le codePostal = num ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PTville NumVille(PTville pDebut , PTville pFin , int num)
{
	PTville pX;
	pX = pDebut->villeSuivante;

	// pour etre sur que la boucle while s arrete
	pFin->codePostal = num;
	while(pX->codePostal != num)
	{
		pX = pX->villeSuivante;
	}
	if(pX != pFin)
		return(pX);
	else
		return(NULL);
}

// Renvoie un PTville qui precede pX dans la liste pDebut /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PTville PtPreVille(PTville pDebut , PTville pX)
{
	PTville pPre;
	pPre = pDebut;

	while(pPre->villeSuivante != pX)
	{ pPre = pPre->villeSuivante; }

	return(pPre);
}

// Renvoie un NOUVEAU PTville juste avant pFin ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PTville InsertionVille(PTville pDebut , PTville pFin , PTben BEN)
{
	PTville pV;
	PTville pPrePV;

	if (BEN->pdebutV->codePostal == 0){ // si il n y a rien dans la poubelle -> malloc
	pV = (PTville)malloc(sizeof(Tville));
	}
	else{ // sinon on recycle le maillon
		pV = BEN->pdebutV->villeSuivante;
		BEN->pdebutV->villeSuivante = pV->villeSuivante;
		BEN->pdebutV->codePostal = BEN->pdebutV->codePostal - 1;
	}
	pPrePV = PtPreVille(pDebut , pFin);

	pV->villeSuivante = pFin;
	pPrePV->villeSuivante = pV;

	pDebut->codePostal = pDebut->codePostal + 1;
	return(pV);
}

// Renvoie un NOUVEAU PTcentrale juste avant pFin /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PTcentrale InsertionCentrale(PTcentrale pDebut , PTcentrale pFin , PTben BEN)
{
	PTcentrale pC;
	PTligneElectrique pfinL; // pointeur sur le bidon des lignes electriques de la centrale
	if(BEN->pdebutC->codeCentrale == 0){
		pfinL = (PTligneElectrique)malloc(sizeof(TlignesElectrique));
		pC = (PTcentrale)malloc(sizeof(Tcentrale));
		pfinL->ligneSuivante = NULL;
		pfinL->villeDesservie = NULL;
		pC->pfinLigne = pfinL;
	}
	else{
		pC = BEN->pdebutC->ptsuivant;
		BEN->pdebutC->ptsuivant = pC->ptsuivant;
		pC->ptsuivant->ptprecedent = BEN->pdebutC;
		BEN->pdebutC->codeCentrale = BEN->pdebutC->codeCentrale - 1;
	}

	pC->ptsuivant = pFin;
	pC->ptprecedent = pFin->ptprecedent;
	pFin->ptprecedent->ptsuivant = pC;
	pFin->ptprecedent = pC;

	//il n y a pas encore de lignes donc "pC->villeDependante" est equivalent a "pC->pfinLigne"
	pC->villeDependante = pC->pfinLigne;
	
	pDebut->codeCentrale = pDebut->codeCentrale + 1;
	return(pC);
}

// Renvoie un PTligneElectrique qui precede pLx dans une liste de ligne. /!\ Si pLx est la premiere ligne, renvoie pLx /!\ ////////////////////////////////////////////////////////////////////////////
PTligneElectrique PtPreLigne(PTligneElectrique pDebut , PTligneElectrique pLx)
{
	PTligneElectrique pPrePLx;
	pPrePLx = pDebut;
	while(pPrePLx->ligneSuivante != pLx && pPrePLx->ligneSuivante != NULL){
		pPrePLx = pPrePLx->ligneSuivante;
	}

	return(pPrePLx);
}

// Renvoie un NOUVEAU PTligneElectrique avant pfinLigne (dans pC) /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PTligneElectrique InsertionLigneElec(PTcentrale pC , PTben BEN)
{
	PTligneElectrique pL;

	if (BEN->pdebutL->puissance == 0){ // si il n y a rien dans la poubelle -> malloc
	pL = (PTligneElectrique)malloc(sizeof(TlignesElectrique));
	}
	else{ // sinon on recycle le maillon
		pL = BEN->pdebutL->ligneSuivante;
		BEN->pdebutL->ligneSuivante = pL->ligneSuivante;
		BEN->pdebutL->puissance = BEN->pdebutL->puissance - 1;
	}

	if (pC->villeDependante != pC->pfinLigne) { // on regarde si il y a des lignes electriques
		//renvoie un pointeur sur la ligne electrique se trouvant avant pfinLigne
		PTligneElectrique pPrePL = PtPreLigne(pC->villeDependante , pC->pfinLigne);
		pPrePL->ligneSuivante = pL;
	}
	else{
		pC->villeDependante = pL;
	}
	pL->ligneSuivante = pC->pfinLigne;
	pL->villeDesservie = NULL;

	return(pL);
}

// Ajouter "n" centrales //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RemplirCentrales(PTcentrale pDebut , PTcentrale pFin , int n , PTben BEN)
{
	int i = 0, existance = 0, code = 0;
	PTcentrale pX;
 
	while(i < n)
	{
		printf("Code centrale : ");
		scanf("%d" , &code);
		existance = ExistanceCentrale(pDebut , pFin , code);
		
		while(existance == 1)
		{
			/* si le numero de la centrale a deja ete ajoute au reseau, on redemande un
			numero => eviter les doublons de num centrales */
			printf("La centrale %d fait deja partie du reseau\nCode centrale : ", code);
			scanf("%d" , &code);
			existance = ExistanceCentrale(pDebut , pFin , code);
		}
		
		pX = InsertionCentrale(pDebut , pFin , BEN);
		pX->codeCentrale = code;
		i++;
	}	
}

// Ajouter "n" villes /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RemplirVilles(PTville pDebut , PTville pFin, int n , PTben BEN)
{
	int i = 0, cp = 0;
	int existance = 0;	//1 si l element existe et 0 si l element n existe pas
	PTville px;

	while(i < n)
	{
		printf("\nCode postal : ");
		scanf("%d" , &cp);
		existance = ExistanceVille(pDebut , pFin , cp);
		
		while(existance == 1)
		{
			/* si le code postal de la ville a deja ete ajoute au reseau, on redemande le code
			postal => eviter les doublons */
			printf("Une ville de code postal %d fait deja partie du reseau\nCode postal : ", cp);
			scanf("%d" , &cp);
			existance = ExistanceVille(pDebut , pFin , cp);
		}
		
		px = InsertionVille(pDebut , pFin , BEN);
		printf("Nom ville : ");
		scanf("%s", px->nomVille);
		px->codePostal = cp;
		i++;
	}
}

// Met la ligne pL du reseau dans la poubelle /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SupLigne(PTcentrale pC , PTligneElectrique pL , PTben BEN)
{
	PTligneElectrique ptPrePL;
	// On commence par delier la ligne electrique pL de la liste
	if (pL != pC->villeDependante){ // on regarde si pL n est pas la premiere ligne electrique
		ptPrePL = PtPreLigne(pC->villeDependante , pL);
		ptPrePL->ligneSuivante = pL->ligneSuivante;
	}
	else // sinon ca veut dire que pL est la première ligne electrique
		pC->villeDependante = pL->ligneSuivante;
	
	// Ici on insert la ligne electrique pL au debut de la liste poubelle
	pL->ligneSuivante = BEN->pdebutL->ligneSuivante;
	BEN->pdebutL->ligneSuivante = pL;
	pL->villeDesservie = NULL;
	BEN->pdebutL->puissance = BEN->pdebutL->puissance + 1;
}

// Met la centrale avec le codeCentrale = num dans la liste poubelle + ses lignes /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SupCentrales(PTcentrale pDebutC , PTcentrale pFinC , int num , PTben BEN)
{
	PTligneElectrique pLx , pLy;
	PTcentrale pC;
 	pC = NumCentrale(pDebutC , pFinC , num);
	pLx = pC->villeDependante;
	
	// On commence par enlever la centrale pC de la liste
 	pC->ptprecedent->ptsuivant = pC->ptsuivant;
	pC->ptsuivant->ptprecedent = pC->ptprecedent;
	pDebutC->codeCentrale = pDebutC->codeCentrale - 1;

	// on met dans la liste poubelle les lignes de la centrales pC
	while(pLx != pC->pfinLigne){
		pLy = pLx->ligneSuivante;
		SupLigne(pC , pLx , BEN);
		pLx = pLy;
	}
	// Insertion de la centrale pC dans la liste poubelle
	pC->ptsuivant = BEN->pdebutC->ptsuivant;
	BEN->pdebutC->ptsuivant = pC;
	pC->ptprecedent = BEN->pdebutC;
	pC->ptsuivant->ptprecedent = pC;
	BEN->pdebutC->codeCentrale = BEN->pdebutC->codeCentrale + 1;
}

// Met la ville avec le codePostale = cp dans la liste poubelle + les lignes pointants sur la ville ///////////////////////////////////////////////////////////////////////////////////////////////////
void SupVilles(PTville pDebutV , PTville pFinV , PTcentrale pDebutC , PTcentrale pFinC , int cp , PTben BEN)
{
	PTville pV , ptPrePV;
	PTcentrale pC;
	PTligneElectrique pLx , pLy;
	pV = NumVille(pDebutV , pFinV , cp);

	// Ici on enleve la ville pV de la liste
	ptPrePV = PtPreVille(pDebutV , pV);
	ptPrePV->villeSuivante = pV->villeSuivante;
	pDebutV->codePostal = pDebutV->codePostal - 1;

	// On met dans la poubelle les lignes pointants sur la ville pV
	pC = pDebutC->ptsuivant;
	while(pC != pFinC){
		pLx = pC->villeDependante;
		while(pLx != pC->pfinLigne){
			pLy = pLx->ligneSuivante;
			if(pLx->villeDesservie == pV){
				SupLigne(pC , pLx , BEN);
			}
			pLx = pLy;
		}
		pC = pC->ptsuivant;
	}

	// On insert la ville pV dans la poubelle
	pV->villeSuivante = BEN->pdebutV->villeSuivante;
	BEN->pdebutV->villeSuivante = pV;
	BEN->pdebutV->codePostal = BEN->pdebutV->codePostal + 1;
}

// Met TOUT le reseau dans les listes poubelles ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SupprimerReseau(PTcentrale pdebutC , PTcentrale pfinC , PTville pdebutV , PTville pfinV , PTben BEN)
{
	int numC, cp;
	PTcentrale pC;
	PTville pV;
	
	while(pdebutC->codeCentrale > 0){
		pC = pdebutC->ptsuivant;
		pC->codeCentrale = numC;
		SupCentrales(pdebutC , pfinC , numC , BEN);
	}
	while(pdebutV->codePostal > 0){
		pV = pdebutV->villeSuivante;
		pV->codePostal = cp;
		SupVilles(pdebutV , pfinV , pdebutC , pfinC , cp , BEN);
	}
}

// Fonction qui demande une validation a l utilisateur, retourne 1 si validee et 0 si rejetee /////////////////////////////////////////////////////////////////////////////////////////////////////////
int Validation()
{
	char a = ' ';
	while(a != 'O' && a != 'o' && a != 'N' && a != 'n'){
		a = getch();
		if(a == 'O' || a == 'o')
			return 1;
		else if(a == 'N' || a == 'n')			
			return 0;
	}
}

// Lit un caractère entré au clavier et retourne son code ASCII ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int lireCaract()
{
    char c = 10;
    int fnt = 0;	
    c = getch();
    fnt = c;
    if (c == -32) { c=getch();fnt = 400+c; }
    if (c == 0)  { c=getch();fnt = 500+c; }
    	return (fnt);
}

// Renvoie la centrale selectionnee dans le cadre /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SelectCentrale(PTcentrale pDebut , PTcentrale pFin)
{
   	PTcentrale pC;
	int lig = 16;
	int col = 12;
	int i;
    
	pC = pDebut->ptsuivant;
    i = 0;
    
    gotoligcol(lig-7,0);printf("Commandes :\tPrecedent : <");
	gotoligcol(lig-6,16);printf("Suivant : >");
	gotoligcol(lig-5,16);printf("Selectionner : Entrer");
	gotoligcol(lig-4,16);printf("Quitter : echap");
	
    while (i != 13){ // entrer
   		printf("\33[2K\r");	// efface l entierete de la ligne sur laquelle est place le curseur et effectue un retour chariot
   		cadre(lig-2,col-2,5,30);	// On pose un cardre le hauteur 5, largeur 30 à la colonne col-2 et ligne lig-2
   		gotoligcol(lig , col);
    	printf("Centrale : %d",pC->codeCentrale);

    	i = lireCaract();
    	if (i == 13) { // entree -> selectionner code centrale
			return (pC->codeCentrale);
		}
    	else if (i == 475 && pC->ptprecedent != pDebut) // fleche gauche
			pC = pC->ptprecedent;
    	else if (i == 477 && pC->ptsuivant != pFin) // fleche droite
			pC = pC->ptsuivant;
    	else if (i == 27) // touche ESC sortir du programme
			return (-1);
  	}
}

// Renvoie la ville selectionnee dans le cadre ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SelectVille(PTville pDebut, PTville pFin)
{
   	PTville pX , pPrePX;
	int lig = 16;
	int col = 12;
    int i; 
    
	pX = pDebut->villeSuivante;
    i = 0;
    
    gotoligcol(lig-7,0);printf("Tapper :\tPrecedent : <");
	gotoligcol(lig-6,16);printf("Suivant : >");
	gotoligcol(lig-5,16);printf("Selectionner : Entrer");
	gotoligcol(lig-4,16);printf("Quitter : echap");
	
    while (i != 13){ // entrer
   		// efface 2 lignes et remonte sur la 1ere
		printf("\33[2K\r\n");
   		printf("\33[2K\r");
		printf("\r\33[A");// le curseur effectue un retour chariot et remonte d'une ligne
		cadre(lig-2,col-2,5,30);// On pose un cardre le hauteur 5, largeur 30 à la colonne col-2 et ligne lig-2
   		gotoligcol(lig , col);
    	printf("Ville : %s\n",pX->nomVille);
    	gotoligcol(lig+1 , col);
    	printf("Code postal : %d",pX->codePostal);

    	i = lireCaract();	
    	if      (i == 13){ // entree -> selectionner code centrale
			return pX->codePostal;
		}
    	else if (i == 475){ // fleche gauche
			pPrePX = PtPreVille(pDebut , pX);
    		if(pPrePX != pDebut){
	    		pX = pPrePX;
			}
		}
    	else if (i == 477 && pX->villeSuivante != pFin) // fleche droite
			pX = pX->villeSuivante;
    	else if (i == 27) // touche ESC sortir du programme
			return -1;
  	}
}

// Met les pointeur/variable de la ligne electrique au bon endroit/valeur /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreationLigne(PTcentrale pDebutC, PTcentrale pFinC, PTville pDebutV, PTville pFinV, int numC, int cp, int pow , PTben BEN)
{
	PTligneElectrique pLignes;
	PTcentrale pCentrales;
	PTville pVilles;
	
	//retourne le pointeur sur une structure centrale a partir de son code
	pCentrales = NumCentrale(pDebutC, pFinC, numC);

	pLignes = InsertionLigneElec(pCentrales , BEN);

	pLignes->puissance = pow;
	pLignes->villeDesservie = NumVille(pDebutV , pFinV , cp);
}

// Affiche les lignes electriques d une centrale //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AfficherLignesCentrale(PTcentrale pdebutCentrale, PTcentrale pfinCentrale){
	int i = 0, numCentrale, lig = 15, col = 12, acc = 0, compt = 0, pow = 0;
	PTcentrale pC;
   	PTligneElectrique pParcLigne;
	
	/* L'info du nombre de centrales dans le reseau a ete stockee dans
	pdebutCentrale->codeCentrale => verif que la liste n est pas vide */
	if(pdebutCentrale->codeCentrale != 0){
		printf("\n\n\tSelectionner une centrale :");
		pC = pdebutCentrale->ptsuivant;
	
    	gotoligcol(lig-6,0);printf("Commandes :\tPrecedent : <");
		gotoligcol(lig-5,16);printf("Suivant : >");
		gotoligcol(lig-4,16);printf("Quitter : echap");
 		cadre(13,10,5,30);	// On pose un cardre de hauteur 5, largeur 30 à la 10eme colonne et 13eme ligne
		
		while (i != 27){ // touche ESC sortir du programme echap
	    	printf("\33[2K\r");	// efface l entierete de la ligne sur laquelle est place le curseur et effectue un retour chariot
   			cadre(lig-2,col-2,5,30);	// On pose un cardre le hauteur 5, largeur 30 à la colonne col-2 et ligne lig-2
   			gotoligcol(lig , col);
	    	printf("Centrale : %d", pC->codeCentrale);
	    	gotoligcol(19,0);
			printf("\n\n\tVilles raccordees a la centrale %d : \n", pC->codeCentrale);
			pParcLigne = pC->villeDependante;
			
			//Suppression affichage des lignes actuellement affichees
			for(compt=0; compt <= acc; compt++){
				printf("\33[2K\r\n");	// efface l entierete de la ligne sur laquelle est place le curseur et effectue un retour chariot et un retour a la ligne
			}
			for(compt=0; compt <= acc; compt++){
				printf("\r\33[A");	// le curseur effectue un retour chariot et remonte d'une ligne
			}
			acc = 0;//remise a 0 du nombres de lignes sur lesquelles effacer les donnees
			pow = 0;//remise a 0 de la puissance totale fournie a la ville
				
			while(pParcLigne != pC->pfinLigne){
				printf("\n\t%d kW   ->     %s   %d",pParcLigne->puissance, pParcLigne->villeDesservie->nomVille, pParcLigne->villeDesservie->codePostal);
				pow+=pParcLigne->puissance;
				pParcLigne = pParcLigne->ligneSuivante;
				acc++;
			}
			
			if(acc == 0)
				printf("\n\tAucune"); acc++;//si aucune ligne ne part de la centrale
	    	if(acc != 1){//si au moins une ligne elec reliee a la ville n a ete trouvee
				printf("\n\n\tPuissance totale distribuee : %d kW", pow); acc+=2;}
	    	i = lireCaract();
	    	if (i == 475 && pC->ptprecedent != pdebutCentrale){ // fleche gauche
				pC = pC->ptprecedent;
			}
	    	else if (i == 477 && pC->ptsuivant != pfinCentrale){ // fleche droite
				pC = pC->ptsuivant;
				gotoligcol(lig,col);
			}
	  	}
	}
	else
		printf("\nLe reseau ne contient aucune centrale");
}

// Affiche les lignes electriques d une ville /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AfficherLignesVille(PTcentrale pdebutCentrale, PTcentrale pfinCentrale, PTville pdebutVille, PTville pfinVille){
	int i = 0, numCentrale, lig = 15, col = 12, acc = 0, compt = 0, pow = 0;
	PTcentrale pC;
	PTville pV, pVpre;
   	PTligneElectrique pParcLigne;
	
	/* L'info du nombre de villes dans le reseau a ete stockee dans
	pdebutVille->codePostal => verif que la liste n est pas vide */
	if(pdebutVille->codePostal != 0){
		printf("\n\n\tSelectionner une ville :");
		pV = pdebutVille->villeSuivante;
		
    	gotoligcol(lig-6,0);printf("Commandes :\tPrecedent : <");
		gotoligcol(lig-5,16);printf("Suivant : >");
		gotoligcol(lig-4,16);printf("Quitter : echap");
 		cadre(13,10,5,30);	// On pose un cardre de hauteur 5, largeur 30 à la 10eme colonne et 13eme ligne
		
		while (i != 27){ // touche ESC sortir du programme echap
	    	gotoligcol(lig , col);
	    	printf("\33[2K\r");	// efface l entierete de la ligne sur laquelle est place le curseur et effectue un retour chariot
   			cadre(lig-2,col-2,5,30);	// On pose un cardre le hauteur 5, largeur 30 à la colonne col-2 et ligne lig-2
   			gotoligcol(lig , col);
	    	printf("Ville : %s", pV->nomVille);
	    	gotoligcol(19,0);
			printf("\n\n\tCentrales raccordees a %s :           \n", pV->nomVille);
			
			//Suppression de l affichage des lignes actuellement affichees
			for(compt=0; compt <= acc; compt++){
				printf("\33[2K\r\n");	// efface l entierete de la ligne sur laquelle est place le curseur et effectue un retour chariot et un retour a la ligne
			}
			for(compt=0; compt <= acc; compt++){
				printf("\r\33[A");	// le curseur effectue un retour chariot et remonte d'une ligne
			}
			acc = 0;//remise a 0 du nombres de lignes sur lesquelles effacer les donnees
			pow = 0;//remise a 0 de la puissance totale fournie a la ville
			
			pC = pdebutCentrale->ptsuivant;
			while(pC->ptsuivant != pfinCentrale){
				pParcLigne = pC->villeDependante;
				while(pParcLigne != pC->pfinLigne){
					if(pParcLigne->villeDesservie->codePostal == pV->codePostal){
						printf("\n\t%d kW   <-     %d",pParcLigne->puissance, pC->codeCentrale);
						acc++;
						pow+=pParcLigne->puissance;
					}
					pParcLigne = pParcLigne->ligneSuivante;
				}
				pC = pC->ptsuivant;
			}
			if(acc == 0)//si aucune ligne elec reliee a la ville n a ete trouvee
				printf("\n\tAucune"); acc++;
			if(acc != 1){//si au moins une ligne elec reliee a la ville n a ete trouvee
				printf("\n\n\tPuissance totale attribuee : %d kW", pow); acc+=2;}
	    	i = lireCaract();
	    	pVpre = PtPreVille(pdebutVille , pV);//pVpre pointe sur le Tville qui precede le Tville pointe par pV
	    	if (i == 475 && pVpre != pdebutVille){ // fleche gauche
				pV = pVpre;
			}
	    	else if (i == 477 && pV->villeSuivante != pfinVille){ // fleche droite
				pV = pV->villeSuivante;
				gotoligcol(lig,col);
			}
	  	}
	}
	else
		printf("\nLe reseau ne contient aucune ville");
}

// Charger un reseau a partir d un fichier texte nomme "nomFichier[100]" //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Charger(PTcentrale pdebutC , PTcentrale pfinC , PTville pdebutV , PTville pfinV , char nomFichier[100] , PTben BEN)
{
	char c , str_temp[50];
	int i = 0 , puissance = 0 , cp = 0;
	PTville pV;
	PTcentrale pC;
	PTligneElectrique pL;
  
	FILE *fIn = NULL;	// file input
	fIn = fopen(nomFichier , "rt"); // read texte

	if(fIn != NULL){
		fscanf(fIn, "%c", &c);
		//le fichier texte se termine par un "."
		while (c != '.'){
			// "$" indique qu on a fini d entrer les villes meme si il n y en a pas
			while (c != '$'){
				pV = InsertionVille(pdebutV , pfinV , BEN);
				i = 0;
				while (c != 9){	// 9 correspond au caractere ASCII de la tabulation \t
				  	str_temp[i] = c;
					fscanf(fIn, "%c", &c);
					i++;
				}
				str_temp[i] = '\0';	// on met '\0' pour dire que c est la fin de la chaine
				/*la fonction atoi() fait partie de la bibliothèque <stdlib.h> et permet
				de convertir une chaine de caractères en un entier*/
				pV->codePostal = atoi(str_temp);
				
				fscanf(fIn, "%c", &c);
				i = 0;
				while (c != 10){ // 10 correspond au caractere ASCII du retour a la ligne \n
				  	pV->nomVille[i] = c;
					fscanf(fIn, "%c", &c);
					i++;
				}
				pV->nomVille[i]='\0'; // on met '\0' pour dire que c est la fin de la chaine
				fscanf(fIn, "%c", &c);
			}
			fscanf(fIn, "%c", &c);
			fscanf(fIn, "%c", &c); // pour passer au caractere en dessous du "$"
			// "." indique la fin du fichier
			while(c != '.'){
				pC = InsertionCentrale(pdebutC , pfinC , BEN);
				i = 0;
				while (c != 10){ // 10 correspond au caractere ASCII du retour a la ligne \n
				  	str_temp[i] = c;
					fscanf(fIn, "%c", &c);
					i++;
				}
				str_temp[i] = '\0';
				pC->codeCentrale = atoi(str_temp);

				fscanf(fIn, "%c", &c);
				// "#" indique que l on passe a la declaration de la centrale suivant (avec ses lignes)
				while (c != '#'){
					i = 0;
					while (c != ' '){ // tant que c different d un espace
				  		str_temp[i] = c;
						fscanf(fIn, "%c", &c);
						i++;
					}
					str_temp[i] = '\0';
					cp = atoi(str_temp);

					i = 0;
					while (c != 10){ // 10 correspond au caractere ASCII du retour a la ligne \n
				  		str_temp[i] = c;
						fscanf(fIn, "%c", &c);
						i++;
					}
					str_temp[i] = '\0';
					puissance = atoi(str_temp);
					CreationLigne(pdebutC , pfinC , pdebutV , pfinV, pC->codeCentrale , cp , puissance , BEN);

					fscanf(fIn, "%c", &c);
				}
				fscanf(fIn, "%c", &c);
				fscanf(fIn, "%c", &c); // pour passer au caractere en dessous du "#"
			}
		}
	}
	else
		printf("%s n'existe pas" , nomFichier);

	fclose(fIn);	// fermeture du fichier d entree
}

// Enregistrer un fichier sous le nom de "nomFichier" /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Enregistrer(PTcentrale pdebutC , PTcentrale pfinC , PTville pdebutV , PTville pfinV , char nomFichier[100])
{
	int i = 0;
	PTville pV = pdebutV->villeSuivante;
	PTcentrale pC = pdebutC->ptsuivant;
	PTligneElectrique pL;
	FILE *fOut = NULL;	// file Output

	fOut = fopen(nomFichier , "rt"); // on ouvre en mode lecture pour voir si le fichier existe deja
	if(fOut == NULL){
		fclose(fOut);
		fOut = fopen(nomFichier , "wt");
		// On commence par enregistrer les villes
		while(pV != pfinV){
			fprintf(fOut , "%d\t%s\n" , pV->codePostal , pV->nomVille);
			pV = pV->villeSuivante;
		}
		fprintf(fOut , "$\n");
		// Puis on enregistre les centrales ...
		while(pC != pfinC){
			fprintf(fOut , "%d\n" , pC->codeCentrale);
			pL = pC->villeDependante;
			// avec leurs lignes électrique
			while(pL != pC->pfinLigne){
				fprintf(fOut , "%d %d\n" , pL->villeDesservie->codePostal , pL->puissance);
				pL = pL->ligneSuivante;
			}
			fprintf(fOut , "#\n");
			pC = pC->ptsuivant;
		}
		fprintf(fOut , ".");
		printf("\nLe fichier a bien ete enregistre sous le nom : %s" , nomFichier);
	}
	else{
		printf("\n%s existe deja." , nomFichier);
	}
	fclose(fOut);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                             Main                               
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{
	int i = 32, nbrVilles = 0, nbrCentrales = 0, numCentrale = 0, existance = 32, cp = 0, puissance = 0;
	char c = 32, k=32, nomFichier[100];

	//Creation des poiteurs qui serviront a PARCOURIR les differentes listes
	PTligneElectrique pParcLigne = NULL;
	PTville pParcVille = NULL;
	PTcentrale pParcCentrale = NULL;
	
	//Creation des bidons
    PTville pdebutVille;
	PTville pfinVille;
	PTcentrale pdebutCentrale;
	PTcentrale pfinCentrale;

	//Creation de la poubelle
	PTben BEN;

	// Initalistaion des bidons
	pdebutVille = (PTville)malloc(sizeof(Tville));
	pfinVille = (PTville)malloc(sizeof(Tville));
	pdebutCentrale = (PTcentrale)malloc(sizeof(Tcentrale));
	pfinCentrale = (PTcentrale)malloc(sizeof(Tcentrale));

	pdebutVille->villeSuivante = pfinVille;
	pfinVille->villeSuivante = NULL;
	pdebutVille->codePostal = 0;

	pdebutCentrale->ptsuivant = pfinCentrale;
	pdebutCentrale->ptprecedent = NULL;
	pfinCentrale->ptsuivant = NULL;
	pfinCentrale->ptprecedent = pdebutCentrale;
	pdebutCentrale->villeDependante = NULL;
	pfinCentrale->villeDependante = NULL;
	pdebutCentrale->codeCentrale = 0;

	// Initialisation des poubelles
	BEN = (PTben)malloc(sizeof(Tben));

	BEN->pdebutV = (PTville)malloc(sizeof(Tville));
	BEN->pfinV = (PTville)malloc(sizeof(Tville));
	BEN->pdebutC = (PTcentrale)malloc(sizeof(Tcentrale));
	BEN->pfinC = (PTcentrale)malloc(sizeof(Tcentrale));
	BEN->pdebutL = (PTligneElectrique)malloc(sizeof(TlignesElectrique));
	BEN->pfinL = (PTligneElectrique)malloc(sizeof(TlignesElectrique));

	BEN->pdebutV->villeSuivante = BEN->pfinV;
	BEN->pfinV->villeSuivante = NULL;
	BEN->pdebutV->codePostal = 0;

	BEN->pdebutC->ptsuivant = BEN->pfinC;
	BEN->pdebutC->ptprecedent = NULL;
	BEN->pfinC->ptsuivant = NULL;
	BEN->pfinC->ptprecedent = BEN->pdebutC;
	BEN->pdebutC->villeDependante = NULL;
	BEN->pfinC->villeDependante = NULL;
	BEN->pdebutC->codeCentrale = 0;
	
	BEN->pdebutL->ligneSuivante = BEN->pfinL;
	BEN->pfinL->ligneSuivante = NULL;
	BEN->pdebutL->puissance = 0;
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	while(i != 0)
	{
		ClearConsole(hConsole);
	  	AfficheMenu(hConsole);
	  	
	  	while(c!='1' && c!='2' && c!='3' && c!='4' && c!=27){//ne rien faire tant que la touche tappee n est pas definie
			c = getch();
		}
	  	if(c == '1')//Menu gestion des centrales //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			ClearConsole(hConsole);
			AfficheMenuCentrales(hConsole);
			
			k = getch();
			if(k == '1')//Ajouter des centrales ///////////////////////////////////////////////////
			{
				SetConsoleTextAttribute(hConsole, 16 * 0 + 10);//vert sur noir
		  		printf("\n\n\tAjout de centrales\n");
		  		SetConsoleTextAttribute(hConsole, 16 * 0 + 15);//blanc sur noir
		  		printf("\nNombre de centrales a ajouter : ");
				scanf("%d" , &nbrCentrales);
				printf("\n");
		  		RemplirCentrales(pdebutCentrale , pfinCentrale , nbrCentrales , BEN);
			}	
			if(k == '2')//Supprimer des centrales /////////////////////////////////////////////////
			{
				ClearConsole(hConsole);
				SetConsoleTextAttribute(hConsole, 16 * 0 + 10);//vert sur noir
		  		printf("\n\n\tSuppression de centrales\n");
		  		SetConsoleTextAttribute(hConsole, 16 * 0 + 15);//blanc sur noir
		  		if(pdebutCentrale->codeCentrale!=0){
		  			printf("\n\nSelectionner une centrale :");
					// On pose un cardre le hauteur 10, largeur 10 à la 5eme colonne et 30eme ligne
			  		cadre(14,10,5,30);
			  		numCentrale = SelectCentrale(pdebutCentrale , pfinCentrale);
			  		gotoligcol(20,0);
			  		if(numCentrale!=-1){	// l utilisateur a bien selectionne une centrale
			  			printf("\nEtes-vous sur de vouloir supprimer la centrale %d\n\tTappez :\tO : Oui \t N : Non", numCentrale);
						if(Validation()==1){
							SupCentrales(pdebutCentrale , pfinCentrale , numCentrale , BEN);
							printf("\n\nLa centrale %d a etee retiree du reseau", numCentrale);
						}
						else
							printf("\n\nSuppression annulee");
					}
			  		else
			  			printf("\n\nSuppression annulee");
				}
				else
					printf("\n\nLe reseau ne contient aucune centrale");
			}
			if(k == '3')//Afficher les centrales //////////////////////////////////////////////////
			{
				ClearConsole(hConsole);
				SetConsoleTextAttribute(hConsole, 16 * 0 + 10);//vert sur noir
		  		printf("\n\n\tAffichage de la liste des centrales\n\n\n");
		  		SetConsoleTextAttribute(hConsole, 16 * 0 + 15);//blanc sur noir	
		  		AfficherCentrales(pdebutCentrale , pfinCentrale);
			}
			if(k == 27){} // echap pour quitter le sous-menu et revenir au menu principal /////////
			//ne rien faire tant que la touche tappee n est pas definie
			while(k!='1' && k!='2' && k!='3' && k!=27){
				k = getch();
			}
		}
		if(c == '2')//Menu gestion des villes /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			ClearConsole(hConsole);
			AfficheMenuVilles(hConsole);
			
			k = getch();
			if(k == '1')//Ajouter des villes //////////////////////////////////////////////////////
			{
				SetConsoleTextAttribute(hConsole, 16 * 0 + 10);//vert sur noir
		  		printf("\n\n\tAjout de villes\n");
		  		SetConsoleTextAttribute(hConsole, 16 * 0 + 15);//blanc sur noir
				printf("\nNombre de villes a ajouter : ");
				scanf("%d", &nbrVilles);
		  		RemplirVilles(pdebutVille , pfinVille , nbrVilles , BEN);
			}	
			if(k == '2')//Supprimer des villes ////////////////////////////////////////////////////
			{
				ClearConsole(hConsole);
				SetConsoleTextAttribute(hConsole, 16 * 0 + 10);//vert sur noir
		  		printf("\n\n\tSuppression de villes\n");
		  		SetConsoleTextAttribute(hConsole, 16 * 0 + 15);//blanc sur noir
		  		if(pdebutVille->codePostal!=0){
		  			printf("\n\nSelectionner une ville :");
					// On pose un cardre le hauteur 5, largeur 30 à la 10eme colonne et 14eme ligne
			  		cadre(14,10,5,30);
			  		cp = SelectVille(pdebutVille , pfinVille);
			  		gotoligcol(20,0);
			  		if(cp!=-1){	// l utilisateur a bien selectionne une ville
				  		printf("\nEtes-vous sur de vouloir supprimer la ville de code postal %d\n\tTappez :\tO : Oui \t N : Non", cp);
						if(Validation()==1){
							SupVilles(pdebutVille , pfinVille , pdebutCentrale , pfinCentrale , cp , BEN);
							printf("\n\nLa ville de code postal %d a etee retiree du reseau", cp);
						}
						else
							printf("\n\nSuppression annulee");
					}
					else
						printf("\n\nSuppression annulee");
				}
				else
					printf("\n\nLe reseau ne contient aucune ville");
			}
			if(k == '3')//Afficher les villes /////////////////////////////////////////////////////
			{
				ClearConsole(hConsole);
				SetConsoleTextAttribute(hConsole, 16 * 0 + 10);//vert sur noir
		  		printf("\n\n\tAffichage de la liste des villes\n\n");
		  		SetConsoleTextAttribute(hConsole, 16 * 0 + 15);//blanc sur noir	
				AfficherVilles(pdebutVille , pfinVille, 7);//On affiche la liste a la ligne 7
			}
			if(k == 27){} // echap pour quitter le sous-menu et revenir au menu principal /////////
			//ne rien faire tant que la touche tappee n est pas definie
			while(k!='1' && k!='2' && k!='3' && k!=27){
				k = getch();
			}
		}
		if(c == '3')//Menu gestion des lignes electriques /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			ClearConsole(hConsole);
			AfficheMenuLignes(hConsole);
			
			k = getch();
			if(k == '1')//Ajouter des lignes //////////////////////////////////////////////////////
			{
				ClearConsole(hConsole);
				SetConsoleTextAttribute(hConsole, 16 * 0 + 10);//vert sur noir
				printf("\n\n\tAjout de lignes electriques\n");
				SetConsoleTextAttribute(hConsole, 16 * 0 + 15);//blanc sur noir
	
				/* L'info du nombre de centrales dans le reseau a ete stockee dans
				pdebutCentrale->codeCentrale => verif que la liste n est pas vide */
				if(pdebutCentrale->codeCentrale != 0 && pdebutVille->codePostal !=0 )
				{
					printf("\n\nSelectionner une centrale :");
					// On pose un cardre le hauteur 5, largeur 30 à la 10eme colonne et 14eme ligne
			  		cadre(14,10,5,30);
			  		numCentrale = SelectCentrale(pdebutCentrale , pfinCentrale);
			  		gotoligcol(20,0);
			  		if(numCentrale!=-1){	// l utilisateur a bien selectionne une centrale
			  			ClearConsole(hConsole);
						SetConsoleTextAttribute(hConsole, 16 * 0 + 10);//vert sur noir
						printf("\n\n\tAjout de lignes electriques\n");
						SetConsoleTextAttribute(hConsole, 16 * 0 + 15);//blanc sur noir
	
			  			printf("\n\nSelectionner la ville a desservir avec la centrale %d :", numCentrale);
						// On pose un cardre le hauteur 5, largeur 30 à la 10eme colonne et 14eme ligne
			  			cadre(14,10,5,30);
				  		cp = SelectVille(pdebutVille , pfinVille);
				  		gotoligcol(20,0);
				  		if(cp!=-1){	// l utilisateur a bien selectionne une ville
				  			printf("\n\nPuissance (en kW) a alouer a la ville : ");
				  			scanf("%d",&puissance);
				  			CreationLigne(pdebutCentrale, pfinCentrale, pdebutVille, pfinVille, numCentrale, cp, puissance, BEN);
				  			printf("\n\nLa ligne electrique a bien ete cree");
					  	}
				  		else
				  			printf("\n\nCreation de ligne electrique annulee");
					}
			  		else
			  			printf("\n\nCreation de ligne electrique annulee");
			  	}
			  	else
			  		printf("\n\nIl n y a aucune centrale ou aucue ville dans le reseau");
			}
			if(k == '2')//Supprimer des lignes ////////////////////////////////////////////////////
			{
				printf("\n\n Fonction encore inexistante !\n");
			}
			if(k == '3')//Afficher les lignes par rapport aux villes //////////////////////////////
			{
			ClearConsole(hConsole);
			SetConsoleTextAttribute(hConsole, 16 * 0 + 10);//vert sur noir
			printf("\n\n\tAffichage des lignes electriques raccordees a une ville\n");
	  		SetConsoleTextAttribute(hConsole, 16 * 0 + 15);//blanc sur noir	
	  		AfficherLignesVille(pdebutCentrale, pfinCentrale, pdebutVille, pfinVille);
			}
			if(k == '4')//Afficher les lignes par rapport aux centrales ///////////////////////////
			{
				ClearConsole(hConsole);
				SetConsoleTextAttribute(hConsole, 16 * 0 + 10);//vert sur noir
				printf("\n\n\tAffichage des lignes electriques raccordees a une centrale\n");
		  		SetConsoleTextAttribute(hConsole, 16 * 0 + 15);//blanc sur noir	
		  		AfficherLignesCentrale(pdebutCentrale, pfinCentrale);
			}
			if(k == 27){} // echap pour quitter le sous-menu et revenir au menu principal /////////
			//ne rien faire tant que la touche tappee n est pas definie
			while(k!='1' && k!='2' && k!='3' && k!=27){
				k = getch();
			}
		}
		if(c == '4')//Menu gestion du reseau //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			ClearConsole(hConsole);
			AfficheMenuReseau(hConsole);
			
			k = getch();
			if(k == '1')//Charger un reseau ///////////////////////////////////////////////////////
			{
				SetConsoleTextAttribute(hConsole, 16 * 0 + 10);//vert sur noir
		  		printf("\n\n\tCharger un reseau\n");
		  		SetConsoleTextAttribute(hConsole, 16 * 0 + 15);//blanc sur noir
		  		SupprimerReseau(pdebutCentrale, pfinCentrale, pdebutVille, pfinVille, BEN);	//le reseau existant est ecrase
		  		printf("\nNom du fichier a charger : ");
		  		scanf("%s",nomFichier);
		  		Charger(pdebutCentrale, pfinCentrale, pdebutVille, pfinVille, nomFichier, BEN);
			}	
			if(k == '2')//Supprimer le reseau actuel //////////////////////////////////////////////
			{
				SetConsoleTextAttribute(hConsole, 16 * 0 + 10);//vert sur noir
		  		printf("\n\n\tSupprimer le reseau\n");
		  		SetConsoleTextAttribute(hConsole, 16 * 0 + 15);//blanc sur noir
		  		printf("\nEtes vous sur de vouloir supprimer le reseau\n\tTappez :\tO : Oui \t N : Non");
		  		if(Validation()==1){
					SupprimerReseau(pdebutCentrale, pfinCentrale, pdebutVille, pfinVille, BEN);
					printf("\n\nReseau supprime");
				}
				else
					printf("\n\nReseau non supprime");
			}
			if(k == '3')//Enregistrer le reseau actuel dans un fichier texte //////////////////////
			{
				SetConsoleTextAttribute(hConsole, 16 * 0 + 10);//vert sur noir
		  		printf("\n\n\tEnregistrer le reseau\n");
		  		SetConsoleTextAttribute(hConsole, 16 * 0 + 15);//blanc sur noir
				printf("\nDonnez un nom au fichier : ");
		  		scanf("%s" , nomFichier);
		  		Enregistrer(pdebutCentrale, pfinCentrale, pdebutVille, pfinVille, nomFichier);
			}
			if(k == 27){} // echap pour quitter le sous-menu et revenir au menu principal /////////
			//ne rien faire tant que la touche tappee n est pas definie
			while(k!='1' && k!='2' && k!='3' && k!=27){
				k = getch();
			}
		}
		if(c == 27) // echap pour quitter /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			break;

		SetConsoleTextAttribute(hConsole, 16 * 8 + 15);//gris sur noir
		printf("\n\n\n\tAppuyer sur une touche pour continuer");
		SetConsoleTextAttribute(hConsole, 16 * 0 + 15);//blanc sur noir
		c = getch();
	}
}
