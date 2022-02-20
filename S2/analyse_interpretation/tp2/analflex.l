%{/* analflex.l */

/* ZONE DE DEFINITION (OPTIONNELLE) */
union{
    long int LITENT;
    char* ID;
    double LITFLOAT;
} yylval;
/* ZONE DES REGLES apres le double pourcent (OBLIGATOIRE) */
%}
%option noyywrap
%%
if|else|th(row|en) {    yylval.ID=malloc(strlen(yytext)+1);
                        strcopy(yylval.ID,yytext);
                        return 300; /* ret un jeton pour Lkey */ }

^[1-9][0-9]*                                    {return 301;/* ret un jeton pour Lc10*/ }
^0[0-7]*                                        {return 302;/* ret un jeton pour Lc8 */ }
^(0x)[0-9A-Fa-f]+                               {return 303;/* ret un jeton pour Lc16 */ }
^[A-Za-z_][A-Za-z0-9_]*                         {return 304;/* ret un jeton pour Lid */ }
([0-9]+\.[0-9]*|\.[0-9]+)([EeDd][+-]?[0-9]+)?   {return 305;/* ret un jeton pour Lf */ }

[ \t\n]+ {/*blanc, ne rien faire*/}
"//".*\n {/* commentaire monoligne en C */}
"/*"([^*]"*"+[^*])*"*"+"/" {/* commentaire multiligne en C */}
. {return yytext[0]; /* ret valeur ascii pour tout le reste */ }
%%
/* ZONE DES FONCTIONS C */
main(){
    int j;
    char *invite="Saisissez un(des) mot(s): ";
    printf(invite);
    while ((j=yylex())!=0) {
        switch (j){
            case 300:
                printf(yylval.ID);
                break;
            case 301:
                printf();
                break;
            case 302:
                printf();
                break;
            case 303:
                printf();
                break;
            case 304:
                printf();
                break;
            case 305:
                printf();
                break;
        }
    
        printf("\nJeton : %i; de lexeme,%s\n%s",j,yytext,invite);
    }
    // return 0;
}   