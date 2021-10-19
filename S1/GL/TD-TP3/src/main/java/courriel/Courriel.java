package courriel;
import java.util.ArrayList;
public class Courriel {
	private String mailDestinataire;
	private String titreMessage;
	private String corps;
	private ArrayList<String> pieceJointe;
	
	public Courriel() {
		mailDestinataire="";
		titreMessage="";
		corps="";
		pieceJointe=new ArrayList<String>();
	}
	public Courriel(String m,String t,String c,ArrayList<String> p) {
		mailDestinataire=m;
		titreMessage=t;
		corps=c;
		pieceJointe=p;
	}
	
	public String getTitre() {
		return this.titreMessage;
	}
	
	public String getMail() {
		return this.mailDestinataire;
	}
	
	public boolean titreValide() {
		return titreMessage!="";
	}
	public boolean adresseMailValide() {//magnifique
		return mailDestinataire.matches("^[[A-Z][a-z]]+[[A-Z][a-z][0-9].-]+@[a-z]+\\.[a-z]{2,6}$");
	}
	public String envoyer()
	{
		if (adresseMailValide() && checkPieceJointe()) {
			return "ok";
		}
		else {
			return "pas ok";
		}
	}
	public boolean checkPieceJointe() {

		if (corps.contains("PJ") ||
			corps.contains("joint")) {
			return !(pieceJointe.isEmpty());
		}
		else {
			return true;
		}
	}
}