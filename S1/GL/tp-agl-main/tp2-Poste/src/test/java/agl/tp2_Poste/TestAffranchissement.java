package agl.tp2_Poste;

import static org.junit.Assert.assertTrue;
import org.junit.jupiter.api.Test;

public class TestAffranchissement
{
    private static float tolerancePrix=0.001f;
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
    public void lettre1()
    {
        assertTrue(Math.abs(lettre1.tarifAffranchissement()-1.0f)<tolerancePrix);
    }

    @Test
    public void lettre2()
    {
        assertTrue(Math.abs(lettre2.tarifAffranchissement()-2.3f)<tolerancePrix);
    }

    @Test
    public void colis1()
    {
        assertTrue(Math.abs(colis1.tarifAffranchissement()-3.5f)<tolerancePrix);
    }
}