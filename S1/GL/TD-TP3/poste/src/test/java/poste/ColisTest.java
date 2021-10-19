package poste;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeEach;

public class ColisTest {
	Colis colis1;
	private static float tolerancePrix=0.001f;
	@BeforeEach
	public void setUp() {
		colis1 = new Colis("Le pere Noel", 
				"famille Kaya, igloo 10, terres ouest",
				"7877", 1024, 0.02f, Recommandation.deux, "train electrique", 200);
	}
	@Test
	public void testToStringColis() {
		assertEquals(colis1.toString(),("Colis 7877/famille Kaya, igloo 10, terres ouest/2/0.02/200.0"));
	}
	@Test
	public void testAffranchissement() {
		assert (Math.abs(colis1.tarifAffranchissement()-3.5f)<tolerancePrix);
	}
	@Test
	public void tarifRemboursementTest() {
		assert (Math.abs(colis1.tarifRemboursement()-100.0f)<tolerancePrix);
	}
}
