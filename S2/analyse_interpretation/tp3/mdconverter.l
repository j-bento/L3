%{/* md_converter.l */

/* ZONE DE DEFINITION (OPTIONNELLE) */
int c;
/* ZONE DES REGLES apres le double pourcent (OBLIGATOIRE) */
%}
%option noyywrap
%%
[\-\*](.|\n)* {if ((c=input())!=EOF && c!=0)
        {
            unput(c);
            printf("ok");
            putchar('<'); putchar('u'); putchar('l'); putchar('>');
            putchar('<'); putchar('l'); putchar('i'); putchar('>');

            // puts("<ul><li>");
            // putchar(c);
            
        }
    }
%%
/* ZONE DES FONCTIONS C */
int main(){
    while (yylex()!=0){}
    return 0;
}   
//exécution : ./delblancs < "fichier_entree" > "fichier_sortie"