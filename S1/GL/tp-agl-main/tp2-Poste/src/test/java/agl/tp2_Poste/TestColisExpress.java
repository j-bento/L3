package agl.tp2_Poste;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.time.LocalDate;

import org.junit.jupiter.api.Test;

public class TestColisExpress {
    private static float tolerancePrix=0.001f;
    
    @Test
    public void affranchissement() {
        try {
            ColisExpress colisExpress1 = new ColisExpress("Le pere Noel", "famille Kaya, igloo 10, terres ouest", "7877", 25, 0.02f, Recommandation.deux, "train electrique", 200, true);
            assertTrue(Math.abs(colisExpress1.tarifAffranchissement()-33.0f)<tolerancePrix);
        } catch(Exception e) {
            assertTrue(false);
        }
    }

    @Test 
    public void string() {
        try {
            ColisExpress colisExpress1 = new ColisExpress("Le pere Noel", "famille Kaya, igloo 10, terres ouest", "7877", 25, 0.02f, Recommandation.deux, "train electrique", 200, true);
            assertTrue(colisExpress1.toString().equals("Colis express 7877/famille Kaya, igloo 10, terres ouest/2/0.02/200.0/25.0/0"));
        } catch(Exception e) {
            assertTrue(false);
        }
    }

    @Test
    public void remboursement() {
        try {
            ColisExpress colisExpress1 = new ColisExpress("Le pere Noel", "famille Kaya, igloo 10, terres ouest", "7877", 25, 0.02f, Recommandation.deux, "train electrique", 200, true);
            assertTrue(Math.abs(colisExpress1.tarifRemboursement()-100.0f)<tolerancePrix);
        } catch(Exception e) {
            assertTrue(false);
        }
    }

    @Test
    public void invalide() {
        try {
            ColisExpress colisExpress1 = new ColisExpress("Le pere Noel", "famille Kaya, igloo 10, terres ouest", "7877", 1024, 0.02f, Recommandation.deux, "train electrique", 200, true);
            assertTrue(false);
            colisExpress1.affiche();
        } catch(Exception e) {
            assertTrue(e.getMessage().equals("poids incohérent, votre colis ne pourra pas être acheminé."));
        }
    }
    
    
    @Test
    public void date() {
    	try {
			ColisExpress colisExpress1 = new ColisExpress("Le pere Noel", "famille Kaya, igloo 10, terres ouest", "7877", 25, 0.02f, Recommandation.deux, "train electrique", 200, true);
			assertEquals(LocalDate.now(),colisExpress1.getDateEnvoi());
    	} catch (ColisExpressInvalide e) {
			e.printStackTrace();
			assertTrue(false);
		}
    }
}
