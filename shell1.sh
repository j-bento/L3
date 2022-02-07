# !/bin/bash 
alias c='clear'
alias rm='rm -i'
alias hier='find ~ -mtime -1'
alias lst='ls ~/Téléchargements'
alias cdl='cd ~/FAC/L3'
alias b='. ~/.bashrc'
alias algo='cd ~/FAC/L3/S1/Algo4'
alias gl='cd ~/FAC/L3/S1/GL'
alias cf='cd ~/FAC/L3/S1/Sage'
alias s1='cd ~/FAC/L3/S1'
alias s2='cd ~/FAC/L3/S1'
date
function mvtel()
{
	if [ -z ${1+x} ]
	then echo "Usage: mvtel <nom_fichier>" # $1 non défini
	else mv ~/Téléchargements/$1 .
	fi
}
function lst()
{
	ls ~/Téléchargements
}
function revmvtel()
{
	mv ./$1 ~/Téléchargements/
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
	xsel -b -c
	ls ~/Téléchargements | grep $1 | xsel -b -a 
}
