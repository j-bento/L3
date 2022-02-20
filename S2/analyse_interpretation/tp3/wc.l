%{/* wc.l */

/* ZONE DE DEFINITION (OPTIONNELLE) */
int wc,ret_ligne,espace;
/* ZONE DES REGLES apres le double pourcent (OBLIGATOIRE) */
%}
%option noyywrap
%%
"\n" {ret_ligne++;}
" " {espace++;}
. {wc++;}
%%
/* ZONE DES FONCTIONS C */
int main(){
    wc=0;
    ret_ligne=0;
    espace=0;
    while (yylex()!=0){}
    wc=( wc + ret_ligne + espace);
    espace+=ret_ligne;
    printf("wc: %d %d %d\n",ret_ligne,espace,wc);
    return 0;
}   
// exécution : ./wc < "fichier_entree"