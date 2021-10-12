package poste;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeEach;

public class LettreTest {
	// création des objets sous test
	Lettre lettre1;
	Lettre lettre2;
	private static float tolerancePrix=0.001f;
	@BeforeEach
	public void setUp() {
	lettre1 = new Lettre("Le pere Noel",
			"famille Kirik, igloo 5, banquise nord",
			"7877", 25, 0.00018f, Recommandation.un, false);
	lettre2 = new Lettre("Le pere Noel",
			"famille Kouk, igloo 2, banquise nord",
			"5854", 18, 0.00018f, Recommandation.deux, true);
	}
	@Test
	public void testToStringLettre() {
	assertEquals(lettre1.toString(),"Lettre 7877/famille Kirik, igloo 5, banquise nord/1/ordinaire");
	assertEquals(lettre2.toString(),"Lettre 5854/famille Kouk, igloo 2, banquise nord/2/urgence");
	}
	@Test
	public void testAffranchissement() {
		assert (Math.abs(lettre1.tarifRemboursement()-1.5f)<tolerancePrix);
		assert (Math.abs(lettre2.tarifAffranchissement()-2.3f)<tolerancePrix);
	}
	@Test
	public void tarifRemboursementTest() {
		assert (Math.abs(lettre1.tarifRemboursement()-1.5f)<tolerancePrix);
		assert (Math.abs(lettre2.tarifRemboursement()-15.0f)<tolerancePrix);
	}
}
