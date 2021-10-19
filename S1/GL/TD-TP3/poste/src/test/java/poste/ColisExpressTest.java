package poste;
import org.junit.jupiter.api.BeforeEach;
//import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
public class ColisExpressTest {
	
	ColisExpress colisExpress1 ;
	//ColisExpress colisExpress2 ;
	//ColisExpress colisExpress3 ;
	@BeforeEach
	public void setUp() throws ColisExpressInvalide {
	colisExpress1=new ColisExpress("Le pere Noel", 
			"famille Kaya, igloo 10, terres ouest",
			"7877", 25, 0.02f, Recommandation.deux, "train electrique", 200,true);
	}
	@Test
	public void poidsTest(){//doit renvoyer vrai
		/*Throwable exception=*/assertThrows(ColisExpressInvalide.class, 
					()->{ 
						new ColisExpress("Le pere Noel","famille Bidule, igloo 10, terres ouest","7877", 200, 0.02f, Recommandation.deux, "velo electrique", 200, false);
					}); 
		//assertEquals(exception.getClass(),ColisExpressInvalide.class);
	}
	@Test
	public void poidsTest2(){//doit renvoyer faux
		/*Throwable exception=*/assertThrows(ColisExpressInvalide.class, 
					()->{ 
						new ColisExpress("Le pere Noel","famille Bidule, igloo 10, terres ouest","7877", 29, 0.02f, Recommandation.deux, "velo electrique", 200, false);
					});      
		//assertEquals(exception.getClass(),ColisExpressInvalide.class);
	}
	@Test
	public void testToStringColisExpress() {
		assertEquals(("Colis express 7877/famille Kaya, igloo 10, terres ouest/2/0.02/200.0/25.0/0"),colisExpress1.toString());
	}
	//TODO finir tarifAffranchissementTest
	/*@Test
	public void tarifAffranchissementTest() {
		assert
	}*/
	
}
