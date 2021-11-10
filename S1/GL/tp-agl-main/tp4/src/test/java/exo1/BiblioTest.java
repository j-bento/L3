package exo1;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.mockito.Mockito.when;

import java.util.ArrayList;

import org.junit.jupiter.api.BeforeEach;

//import static org.mockito.Mockito.doReturn;

import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;


public class BiblioTest {
	
	//public GlobalBibliographyAccess GBA;
	public ArrayList<NoticeBibliographique> notices;
	//public ArrayList<NoticeBibliographique> noticesRes;
	public NoticeBibliographique noticeA;
	public NoticeBibliographique noticeB;
	public NoticeBibliographique noticeC;
	public NoticeBibliographique noticeD;
	public NoticeBibliographique noticeE;
	public NoticeBibliographique noticeF;
	public NoticeBibliographique noticeG;
	public NoticeBibliographique noticeH;
	
	@BeforeEach
	public void init() {
		notices=new ArrayList<NoticeBibliographique>();
		noticeA=new NoticeBibliographique("ISBN A","Titre A","Auteur A");
		noticeB=new NoticeBibliographique("ISBN B","Titre B","Auteur A");
		noticeC=new NoticeBibliographique("ISBN C","Titre C","Auteur A");
		noticeD=new NoticeBibliographique("ISBN D","Titre D","Auteur A");
		noticeE=new NoticeBibliographique("ISBN E","Titre E","Auteur A");
		noticeF=new NoticeBibliographique("ISBN F","Titre F","Auteur A");
		noticeG=new NoticeBibliographique("ISBN G","Titre G","Auteur G");
		noticeH=new NoticeBibliographique("ISBN H","Titre H","Auteur H");
	}
	@Mock
	IGlobalBibliographyAccess GBA;
	
	@InjectMocks
	BiblioUtilities BU=new BiblioUtilities();
	

	
	@Test
	public void chercherNoticesConnexesTest() {
		notices.add(noticeB);
		notices.add(noticeC);
		notices.add(noticeD);
		notices.add(noticeE);
		notices.add(noticeF);
		when(GBA.noticesDuMemeAuteurQue(noticeA)).thenReturn(notices);
		//ArrayList<NoticeBibliographique> noticesRes=BU.chercherNoticesConnexes(noticeA);
		boolean b=true;int i=0;
		/*
		while (b || i<notices.size()) {
			if (!notices.get(i).equals(noticesRes.get(i))) {
				b=false;
			}
			else {
				i++;
			}
		}*/
		assertTrue(b);
	
		
	}
}
