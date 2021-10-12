package poste;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Test;
public class SacPostalTest {
	Colis colis1;
	Lettre lettre1;
	Lettre lettre2;
	SacPostal sac1;
	SacPostal sac2;
	private static float tolerancePrix=0.001f;
	private static float toleranceVolume=0.0000001f;
	@BeforeEach
	public void setUp() {
		lettre1 = new Lettre("Le pere Noel",
				"famille Kirik, igloo 5, banquise nord",
				"7877", 25, 0.00018f, Recommandation.un, false);
		lettre2 = new Lettre("Le pere Noel",
				"famille Kouk, igloo 2, banquise nord",
				"5854", 18, 0.00018f, Recommandation.deux, true);
		colis1 = new Colis("Le pere Noel", 
				"famille Kaya, igloo 10, terres ouest",
				"7877", 1024, 0.02f, Recommandation.deux, "train electrique", 200);
		sac1=new SacPostal();
		sac1.ajoute(lettre1);
		sac1.ajoute(lettre2);
		sac1.ajoute(colis1);
		
		
	}
	@Test
	public void valeurRemboursementTest() {
		assert (Math.abs(sac1.valeurRemboursement()-116.5f)<tolerancePrix);
	}
	@Test
	public void volumeTest() {
		assert (Math.abs(sac1.getVolume()-0.025359999558422715f)<toleranceVolume);
	}
	@AfterEach
	public void volumeTest2() {
		sac2 = sac1.extraireV1("7877");
		assert (sac2.getVolume()-0.02517999955569394f<toleranceVolume);
	}
}