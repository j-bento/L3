package poste;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeEach;

public class ColisTest {
	Colis colis1;
	Colis colis2;
	Colis colis3;
	private static float tolerancePrix=0.001f;
	@BeforeEach
	public void setUp() {
		colis1 = new Colis("Le pere Noel", 
				"famille Kaya, igloo 10, terres ouest",
				"7877", 1024, 0.02f, Recommandation.deux, "train electrique", 200);
		colis2 = new Colis("Le pere nono", 
				"famille Kaya, igloo 10, terres est",
				"7877", 1024, 0.4f, Recommandation.un, "train electrique", 100);
		colis3 = new Colis("Le pere nono", 
				"famille Kaya, igloo 10, terres est",
				"7877", 1024, 0.02f, Recommandation.zero, "train electrique", 100);
	}
	
	@Test
	public void testColisConstructeurDef() {
		Colis colisDefaut=new Colis();
		assertEquals("inconnue",colisDefaut.getOrigine());
		assertEquals("inconnue",colisDefaut.getDestination());
		assertEquals("0000",colisDefaut.getCodePostal());
		assertEquals(0,colisDefaut.getPoids());
		assertEquals(0,colisDefaut.getVolume());
		assertEquals(Recommandation.zero,colisDefaut.getTauxRecommandation());
		assertEquals("vide",colisDefaut.getDeclareContenu());
		assertEquals(0,colisDefaut.getValeurDeclaree());
				
	}
	@Test
	public void testToStringColis() {
		assertEquals("Colis 7877/famille Kaya, igloo 10, terres ouest/2/0.02/200.0",colis1.toString());
	}
	@Test
	public void testAffranchissement() {
		assert (Math.abs(colis1.tarifAffranchissement()-3.5f)<tolerancePrix);
		assert (Math.abs(colis2.tarifAffranchissement()-5.5f)<tolerancePrix);
	}
	
	@Test
	public void testTarifRemboursement() {
		assert (Math.abs(colis1.tarifRemboursement()-100.0f)<tolerancePrix);
		assert (Math.abs(colis2.tarifRemboursement()-10.0f)<tolerancePrix);
		assert (colis3.tarifRemboursement()<tolerancePrix);
	}
}
