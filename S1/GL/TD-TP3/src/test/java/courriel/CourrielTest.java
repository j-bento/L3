package courriel;

import java.util.ArrayList;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
public class CourrielTest {
	
	Courriel courriel1;
	Courriel courriel2;
	Courriel courriel3;
	ArrayList<String> PJ=new ArrayList<String>();
	
	@BeforeEach
	public void SetUp() {
		PJ.add("furries.jpg");
		PJ.add("somePicture.jpg");
		courriel1=new Courriel("michel.lebon@yahh.fr",
				"TP GL",
				"Voici un exemple d'objet courrier.",
				PJ);
		courriel2=new Courriel("michel.lebon@yahh.fr",
				"TP GL",
				"Voici un exemple d'objet courrier avec pièce jointe.",
				PJ);
		courriel3=new Courriel("micheau.lebonyahh.fr",
				"",
				"Voici un exemple d'objet courrier avec une mauvaise adresse, pas de titre, sans PJ.",
				new ArrayList<String>());
	}
	@Test	
	public void adresseElectroniqueBienFormee() {
		assert(courriel1.adresseMailValide());
	}
	@Test	
	public void adresseElectroniqueBienFormee2() {
		assert(courriel3.adresseMailValide());
		}
	@Test
	public void titreNonNul() {
	assert(courriel1.titreValide());
	}
	@Test
	public void titreNonNul2() {
	assert(courriel3.titreValide());
	}
	@Test
	public void PieceJointeTest1() {
		assert(courriel1.checkPieceJointe());
	}
	@Test
	public void PieceJointeTest2() {
		assert(courriel3.checkPieceJointe());
	}
}