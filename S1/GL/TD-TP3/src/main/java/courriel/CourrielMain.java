package courriel;

import java.util.ArrayList;

public class CourrielMain {
	public static void main(String[] arguments)
	{
		ArrayList<String> PJ=new ArrayList<String>();
		PJ.add("furries.jpg");
		PJ.add("somePicture.jpg");
		Courriel courriel1=new Courriel("michel.lebon@yahh.fr",
				"TP GL",
				"Voici un exemple d'objet courrier.",
				PJ);
		Courriel courriel2=new Courriel("michel.lebon@yahh.fr",
				"TP GL",
				"Voici un exemple d'objet courrier avec pièce jointe.",
				PJ);
		Courriel courriel3=new Courriel("micheau.lebonyahh.fr",
				"",
				"Voici un exemple d'objet courrier avec une mauvaise adresse, pas de titre, sans PJ.",
				new ArrayList<String>());
		System.out.println(courriel1.adresseMailValide());
		System.out.println(courriel1.checkPieceJointe());
		System.out.println(courriel1.envoyer());
		//System.out.println(new ArrayList<String>().isEmpty());
		System.out.println(courriel2.adresseMailValide());
		System.out.println(courriel2.checkPieceJointe());
		System.out.println(courriel2.envoyer());
		
		System.out.println(courriel3.adresseMailValide());
		System.out.println(courriel3.checkPieceJointe());
		System.out.println(courriel3.envoyer());
	}
}
