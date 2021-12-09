# !/bin/bash 
alias c='clear'
alias rm='rm -i'
alias hier='find ~ -mtime -1'
alias lst='ls ~/Téléchargements'
alias cdl='cd ~/Documents/L3'
alias b='. ~/.bashrc'
alias algo='cd ~/Documents/L3/S1/Algo4'
alias gl='cd ~/Documents/L3/S1/GL'
alias cf='cd ~/Documents/L3/S1/Sage'
alias s1='cd ~/Documents/L3/S1'
date
function mvtel()
{
	mv ~/Téléchargements/$1 .
}
function lst()
{
	ls ~/Téléchargements
}
function revmvtel()
{
	mv ./$1 ~/Téléchargements/
}

#copie le nom d'un fichier/dossier dans les téléchargements
function ct()
{
	xsel -b -c
	ls ~/Téléchargements | grep $1 | xsel -b -a 
}
