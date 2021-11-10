package agl.tp2_Poste;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;
import static org.junit.Assert.assertTrue;

public class TestSacPostaux {
    private static float tolerancePrix=0.001f;
	private static float toleranceVolume=0.0000001f;
    Lettre lettre1 = new Lettre("Le pere Noel", "famille Kirik, igloo 5, banquise nord",
    "7877", 25, 0.00018f, Recommandation.un, false);
    Lettre lettre2 = new Lettre("Le pere Noel",
    "famille Kouk, igloo 2, banquise nord",
    "5854", 18, 0.00018f, Recommandation.deux, true);
    Colis colis1 = new Colis("Le pere Noel", 
    "famille Kaya, igloo 10, terres ouest",
    "7877", 1024, 0.02f, Recommandation.deux, "train electrique", 200);
    SacPostal sac1 = new SacPostal();
    /*
		sac1.ajoute(lettre1);
		sac1.ajoute(lettre2);
		sac1.ajoute(colis1);
    */
    @Test
    public void remboursement() {
        sac1.ajoute(lettre1);
		sac1.ajoute(lettre2);
		sac1.ajoute(colis1);
        assertTrue(Math.abs(sac1.valeurRemboursement()-116.5f)<tolerancePrix);
    }

    @Test
    public void getVolume() {
        sac1.ajoute(lettre1);
		sac1.ajoute(lettre2);
		sac1.ajoute(colis1);
        assertTrue(Math.abs(sac1.getVolume()-0.025359999558422715f)<toleranceVolume);
    }

    @Test
    public void getVolume2() {
        sac1.ajoute(lettre1);
		sac1.ajoute(lettre2);
		sac1.ajoute(colis1);
        SacPostal sac2 = sac1.extraireV1("7877");
        assertTrue(sac2.getVolume()-0.02517999955569394f<toleranceVolume);
    }
    
    @Test
    public void getCapacite() {
    	assertEquals(sac1.getCapacite(),0.5);
    }
}