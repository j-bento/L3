# !/bin/bash 
alias c='clear'
alias m='make'
alias rm='rm -i'
alias hier='find ~ -mtime -1'
alias lst='ls ~/Téléchargements'
alias cdl='cd ~/FAC/L3'
alias cdm='cd ~/FAC/M1'
alias b='. ~/.bashrc'
alias s1='cd ~/FAC/L3/S1'
alias s2='cd ~/FAC/L3/S2'
alias func='cat ~/FAC/L3/shell1.sh | grep -v alias | grep function' # affiche les fonctions
alias code='~/Téléchargements/code_1.65.2-1646927742_amd64/usr/share/code/bin/code'
alias antlr4='java -jar /home/e20190004783/antlr/antlr-4.11.1-complete.jar'
alias grun='java org.antlr.v4.gui.TestRig'
alias codium='codium -n .'
export CLASSPATH=".:/home/e20190004783/antlr/antlr-4.11.1-complete.jar:$CLASSPATH"

date
function mvtel()
{
	if [ -z ${1+x} ]
	then echo "Usage: mvtel <nom_fichier>" # $1 non défini
	else 
		for i in $@
		do
			mv ~/Téléchargements/$i .
		done
	fi
}
function lst()
{
	ls ~/Téléchargements
}
function revmvtel()
{
	mv $@ ~/Téléchargements/
}
# historique des x dernières commandes
# utilisation: 
# hist -> toutes les commandes
# hist 10 -> 10 dernières commandes
# hist 10 30 -> entre les 10 et 30 dernières commandes
function hist()
{
	if [ -z ${1+x} ]
	then cat ~/.bash_history # $1 non défini
	else if [ -z ${2+x} ] # $1 défini
		then head -$1 ~/.bash_history # $2 non défini
   		else head -$2 ~/.bash_history | tail -$(expr $2 - $1) # $2 défini
		fi
	fi
}


#copie le nom d'un fichier/dossier dans les téléchargements
function ct()
{
	xsel -b -c # efface le contenu du clipboard (s'il en possède un)
	ls ~/Téléchargements | grep $1 | xsel -b -a 
}

#copie le nom d'un fichier/dossier passé par un pipe
function cpy()
{
	xsel -b -c # efface le contenu du clipboard (s'il en possède un)
	xsel -b -a 
}
