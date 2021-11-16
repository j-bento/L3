package exo1;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.mockito.Mockito.when;

import java.util.ArrayList;

import org.junit.jupiter.api.BeforeEach;

//import static org.mockito.Mockito.doReturn;

import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

import static org.mockito.Mockito.*;

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
	
	@SuppressWarnings("deprecation")
	@BeforeEach
	public void init() {
		MockitoAnnotations.openMocks(this);
		
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
	GlobalBibliographyAccess GBA;
	
	@InjectMocks
	BiblioUtilities BU=new BiblioUtilities();
	
	//@InjectMocks
	//GlobalBibliographyAccess GBA=new GlobalBibliographyAccess();
	
	@Test
	public void chercherNoticesConnexesTest() {
		notices.add(noticeB);
		notices.add(noticeC);
		notices.add(noticeD);
		notices.add(noticeE);
		notices.add(noticeF);
		//when(GBA.yolo(12)).thenReturn(3);
		//int test=GBA.yolo(12);
		when(GBA.noticesDuMemeAuteurQue(noticeA)).thenReturn(notices);
		
		ArrayList<NoticeBibliographique> noticesRes=GBA.noticesDuMemeAuteurQue(noticeA);
		//noticesRes.add(noticeA)
		boolean b=true;int i=0;
		
		while (b && i<noticesRes.size()) {//on s'assure ici que toutes les notices ont le même auteur et des titres différents
			if (noticeA.getAuteur()==noticesRes.get(i).getAuteur()) {//cas où l'auteur est le même
				for (int j=0; j<noticesRes.size();j++) {
					if (i!=j) {
						if (noticesRes.get(i).getTitre()==noticesRes.get(j).getTitre()){
							b=false;//cas où l'auteur est le même mais le titre est similaire à une autre notice
						}
					}
				}
			i++;
			}
			else {
				b=false;
			}	
		}
		assertTrue(b);	//let's go
	}
	
	@Test
	public void ajoutNoticeTest() {
		//TODO test ajout notice
	}
}
