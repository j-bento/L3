package agl.tp2_Poste;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.jupiter.api.Test;

public class TestString
{
    Lettre lettre1 = new Lettre("Le pere Noel",
				"famille Kirik, igloo 5, banquise nord",
				"7877", 25, 0.00018f, Recommandation.un, false);
	Lettre lettre2 = new Lettre("Le pere Noel",
				"famille Kouk, igloo 2, banquise nord",
				"5854", 18, 0.00018f, Recommandation.deux, true);
	Colis colis1 = new Colis("Le pere Noel", 
				"famille Kaya, igloo 10, terres ouest",
				"7877", 1024, 0.02f, Recommandation.deux, "train electrique", 200);   
    
    @Test
    public void toStringColis1()
    {
        assertTrue(colis1.toString().equals("Colis 7877/famille Kaya, igloo 10, terres ouest/2/0.02/200.0"));
    }

    @Test
    public void toStringLettre1()
    {
        assertTrue(lettre1.toString().equals("Lettre 7877/famille Kirik, igloo 5, banquise nord/1/ordinaire"));
    }

    @Test
    public void toStringLettre2()
    {
        assertTrue(lettre2.toString().equals("Lettre 5854/famille Kouk, igloo 2, banquise nord/2/urgence"));
    }
    
    @Test
    public void urgence() {
    	Lettre L = new Lettre();
    	assertFalse(L.getUrgence());
    }
}
