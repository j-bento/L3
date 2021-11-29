# !/bin/bash 
alias c='clear'
alias rm='rm -i'
alias hier='find ~ -mtime -1'
alias lst='ls ~/Téléchargements'
alias cdl='cd ~/Documents/L3'
alias b='. ~/.bashrc'
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

