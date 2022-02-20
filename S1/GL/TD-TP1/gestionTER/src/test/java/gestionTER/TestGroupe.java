package gestionTER;

import static org.junit.jupiter.api.Assertions.*;

import java.util.HashMap;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import gestionTER.CantAddVoeu;
import gestionTER.Groupe;
import gestionTER.Sujet;

class TestGroupe {
	
	public Groupe g;
	
	@BeforeEach
	public void init() {
		g = new Groupe("groupe");
	}
	
	@Test
	void testGroupeIdDeuxGroupes() {
		int id = g.getId() + 1;
		Groupe gg = new Groupe("groupe");
		assertEquals(id, gg.getId());
	}

	@Test
	void testGroupeStringl() {
		assertEquals("groupe", g.getNom());
	}
	
	@Test
	void testGroupeVoeuFiniNon() {
		assertFalse(g.isVoeuReady());
	}
	
	@Test
	void testGroupeVoeuFiniOui() {
		g.setVoeuFini(true);
		assertTrue(g.isVoeuReady());
	}
	
	@Test
	void testGroupeChangementNom() {
		g.setNom("coucou");
		assertEquals("coucou", g.getNom());
	}
	
	@Test
	void testGroupeVide() {
		Groupe gg = new Groupe();
		assertEquals(null, gg.getNom());
	}
	
	@Test
	void testGroupeToString() {
		int id = g.getId();
		String nom = g.getNom();
		assertEquals(nom+" (id:"+id+")\n", g.toString());
	}
	
	@Test
	void testGroupeToStringUnVoeu() {
		Sujet s = new Sujet("suj");
		try {
			g.addVoeu(1, s);
		} catch (CantAddVoeu e) {
			e.printStackTrace();
		}
		int id = g.getId();
		String nom = g.getNom();
		assertEquals(nom+" (id:"+id+")\n--1: "+s.toString()+"\n", g.toString());
	}
	
	@Test
	void testGroupeAjouterVoeuOrdreBas() {
		CantAddVoeu thrown = assertThrows(CantAddVoeu.class, () -> {g.addVoeu(0, null);});
        assertEquals("L'ordre du voeu doit être entre 1 et 5", thrown.getMessage());
	}
	
	@Test
	void testGroupeAjouterVoeuOrdreHaut() {
		CantAddVoeu thrown = assertThrows(CantAddVoeu.class, () -> {g.addVoeu(6, null);});
        assertEquals("L'ordre du voeu doit être entre 1 et 5", thrown.getMessage());
	}
	
	@Test
	void testGroupeAjouterVoeuCorrect() {
		try {
			assertTrue(g.addVoeu(1, null));
		} catch (CantAddVoeu e) {
			assertTrue(false);
			e.printStackTrace();
		}
	}
	
	@Test
	void testGroupeAjouterVoeuSujetDejaChoisi() {
		Sujet s = new Sujet("suj1");
		try {
			assertTrue(g.addVoeu(1, s));
		} catch (CantAddVoeu e) {
			assertTrue(false);
			e.printStackTrace();
		}
		CantAddVoeu thrown = assertThrows(CantAddVoeu.class, () -> {g.addVoeu(2, s);});
        assertEquals("Le sujet a déjà été choisi", thrown.getMessage());
	}
	
	@Test
	void testGroupeAjouterVoeuOrdreDejaRempli() {
		Sujet s = new Sujet("suj1");
		Sujet s2 = new Sujet("suj2");
		try {
			assertTrue(g.addVoeu(1, s));
		} catch (CantAddVoeu e) {
			assertTrue(false);
			e.printStackTrace();
		}
		CantAddVoeu thrown = assertThrows(CantAddVoeu.class, () -> {g.addVoeu(1	, s2);});
        assertEquals("L'ordre a déjà été rempli", thrown.getMessage());
	}
	
	@Test
	void testGroupeSetVoeu() {
		HashMap<Integer, Sujet> v = new HashMap<Integer, Sujet>();
		Sujet s = new Sujet("suj1");
		v.put(1, s);
		g.setVoeux(v);
		CantAddVoeu thrown = assertThrows(CantAddVoeu.class, () -> {g.addVoeu(2, s);});
        assertEquals("Le sujet a déjà été choisi", thrown.getMessage());
	}
	
	@Test
	void testGroupeConstructorAllInfo() {
		Groupe gg = new Groupe(444, 444, "gg", new HashMap<Integer, Sujet>(), false);
		assertFalse(gg.isVoeuReady());
		assertEquals("gg", gg.getNom());
		
	}
	
	@Test
	void testGroupeAddFiveVoeuxAndReady() {
		Sujet s1 = new Sujet("suj");
		Sujet s2 = new Sujet("suj");
		Sujet s3 = new Sujet("suj");
		Sujet s4 = new Sujet("suj");
		Sujet s5 = new Sujet("suj");
		try {
			g.addVoeu(1, s1);
			g.addVoeu(2, s2);
			g.addVoeu(3, s3);
			g.addVoeu(4, s4);
			g.addVoeu(5, s5);
			assertTrue(g.getVoeuFini());
		} catch (CantAddVoeu e) {
			assertFalse(true);
			e.printStackTrace();
		}
	}
	
	@Test
	void testGroupeAddOneVoeuAndNotReady() {
		Sujet s = new Sujet("suj");
		try {
			g.addVoeu(1, s);
		} catch (CantAddVoeu e) {
			assertTrue(false);
			e.printStackTrace();
		}
		assertFalse(g.getVoeuFini());
	}
}
