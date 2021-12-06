package courriel;

import static org.junit.jupiter.api.Assertions.assertEquals;
import org.junit.jupiter.params.ParameterizedTest;

import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.fail;

import java.util.stream.Stream;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;

public class CourrielTest {
	
	Courriel courrier;
	
	@BeforeEach
	public void setUp() {
		courrier=new Courriel();
	}
	    public static Stream<Arguments> mauvaisesAdresses() {
	        return Stream.of(
	            Arguments.of("blablabla", "Pas d'arobase"),
	            Arguments.of("@gmail.com", "Rien avant l'arobase"),
	            Arguments.of("adresse@gmail.", "Pas de nom de domaine")
	        );
	    }
		
	    @ParameterizedTest(name="pour {0} : {1}")
	    @MethodSource("mauvaisesAdresses")
	    public void testAdresses(String adress,String probleme) {
	        courrier.setAdresse(adress);
	        EnvoiInvalide thrown = assertThrows(EnvoiInvalide.class, () -> {courrier.envoyer();});
	        assertEquals("Adresse du destinataire incorrecte",thrown.getMessage());
	    }
	
	@Test	
	public void envoiSansAdresse() {
		 EnvoiInvalide thrown = assertThrows(EnvoiInvalide.class, () -> {courrier.envoyer();});
		 assertEquals("Pas de destinataire",thrown.getMessage());
	    
	}
	@Test	
	@Disabled("On vérifie déjà ce test avec le test paramétré")
	public void adresseMalFormeeTest() {
		courrier.setAdresse("blablabla");
        EnvoiInvalide thrown = assertThrows(EnvoiInvalide.class, () -> {courrier.envoyer();}); 
        assertEquals("Adresse du destinataire incorrecte",thrown.getMessage());
	}
	@Test	
	@Disabled("On vérifie déjà ce test avec le test paramétré")
	public void adresseMalFormeeTest2() {
		courrier.setAdresse("@gmail.com");
        EnvoiInvalide thrown = assertThrows(EnvoiInvalide.class, () -> {courrier.envoyer();}); 
        assertEquals("Adresse du destinataire incorrecte",thrown.getMessage());
	}
	@Test
	@Disabled("On vérifie déjà ce test avec le test paramétré")
	public void adresseMalFormeeTest3() {
		courrier.setAdresse("adresse@gmail.");
        EnvoiInvalide thrown = assertThrows(EnvoiInvalide.class, () -> {courrier.envoyer();}); 
        assertEquals("Adresse du destinataire incorrecte",thrown.getMessage());
	}
	
	@Test
	public void envoiSansTitre() {
	    courrier.setAdresse("adresse@messagerie.dom");
	    EnvoiInvalide thrown = assertThrows(EnvoiInvalide.class, () -> {courrier.envoyer();});
	    assertEquals("Pas de titre",thrown.getMessage());
	}
	
	@Test
    public void pieceJointeAbsente()
    {
        courrier.setAdresse("adresse@messagerie.dom");
        courrier.setTitre("titre");
        courrier.setCorps("Message contenant une fichier joint");
        EnvoiInvalide thrown = assertThrows(EnvoiInvalide.class, () -> {courrier.envoyer();});
        assertEquals("Pas de piece jointe",thrown.getMessage());
    }
	
	@Test
    public void pieceJointeAbsente2()
    {
        courrier.setAdresse("adresse@messagerie.dom");
        courrier.setTitre("titre");
        courrier.setCorps("Message contenant une pièce jointe");
        EnvoiInvalide thrown = assertThrows(EnvoiInvalide.class, () -> {courrier.envoyer();});
        assertEquals("Pas de piece jointe",thrown.getMessage());
    }
	
	@Test
    public void pieceJointeAbsente3()
    {
        courrier.setAdresse("adresse@messagerie.dom");
        courrier.setTitre("titre");
        courrier.setCorps("Message contenant une PJ");
        EnvoiInvalide thrown = assertThrows(EnvoiInvalide.class, () -> {courrier.envoyer();});
        assertEquals("Pas de piece jointe",thrown.getMessage());
    }
	@Test
    public void adresseCorrecte() { //envoie un courriel correctement formé
        courrier.setAdresse("adresse@messagerie.dom");
        courrier.setTitre("titre");
        courrier.setCorps("Message contenant une PJ");
        courrier.addJoint("/succes.txt");
        try {
        	courrier.envoyer();
        } catch (Exception e) {
        	fail(e);
        }
    }

}
