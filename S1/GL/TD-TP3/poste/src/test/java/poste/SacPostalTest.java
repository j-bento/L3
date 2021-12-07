package poste;

import org.junit.jupiter.api.BeforeEach;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;

import java.util.ArrayList;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Test;
public class SacPostalTest {
	Colis colis1;
	Colis colis2;
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
		//colis qui prend beaucoup de place
		colis2 = new Colis("Le pere Noel", 
				"famille Kaya, igloo 10, terres ouest",
				"7877", 1024, 1f, Recommandation.deux, "train electrique", 200);
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
	@Test
	public void toStringSacPostalTest() {
		assertEquals(("Sac \ncapacite: "+sac1.getCapacite()+
				"\nvolume: "+sac1.getVolume()+"\n"+sac1.getContenu()+"\n"),sac1.toString());
	}
	@Test
	public void capaciteDepasseeTest() {
		SacPostal sac3=new SacPostal();
		assertFalse(sac3.ajoute(colis2));
	}
	
	@Test
	public void extraireV2Test() {	
		SacPostal sac3=new SacPostal();
		sac3.ajoute(lettre1);
		sac3.ajoute(lettre2);
		sac3.ajoute(colis1);
		//colis1 et lettre1 ont le même code
		sac3.extraireV2("7877");
		assertEquals(1,sac3.getContenu().size());
	}
	
	@AfterEach
	public void volumeTest2() {		
		sac2 = sac1.extraireV1("7877");
		assert (sac2.getVolume()-0.02517999955569394f<toleranceVolume);
	}
	
	
}