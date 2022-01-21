package agl.tp4_mocks;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.mockito.Mockito.doReturn;
import static org.mockito.Mockito.when;

import java.time.Clock;
import java.time.LocalDate;
import java.time.ZoneId;
import java.util.ArrayList;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

@ExtendWith(MockitoExtension.class)
class TestBibliUtilities {
	
	private NoticeBibliographique n1;
	private NoticeBibliographique n2;
	private NoticeBibliographique n3;
	private NoticeBibliographique n4;
	private NoticeBibliographique n5;
	private NoticeBibliographique n6;
	private NoticeBibliographique n7;
	private NoticeBibliographique n8;
	private ArrayList<NoticeBibliographique> listeNotices;
	private ArrayList<NoticeBibliographique> retour;
	private Bibliothèque b;
	
	@Mock
	Clock mockedClock;
	
	@Mock
	InterfaceGlobalBibliographyAccess glob;
	
	@InjectMocks
	BibliUtilities bib = new BibliUtilities();
	
	@BeforeEach
	void setup() {
		n1 = new NoticeBibliographique("1", "Marche ou crève", "Stephen King");
		n2 = new NoticeBibliographique("2", "Carrie", "Stephen King");
		n3 = new NoticeBibliographique("3", "Charlie", "Stephen King");
		n4 = new NoticeBibliographique("4", "Christine", "Stephen King");
		n5 = new NoticeBibliographique("5", "Jessie", "Stephen King");
		n6 = new NoticeBibliographique("6", "Mercure", "Amélie Nothomb");
		n7 = new NoticeBibliographique("7", "Frappe-toi le coeur", "Amélie Nothomb");
		n8 = new NoticeBibliographique("8", "Survivant", "Chuck Palahniuk");
		listeNotices = new ArrayList<NoticeBibliographique>();
		retour = new ArrayList<NoticeBibliographique>();
		b = Bibliothèque.getInstance();
		b.addNotice(n1);
		b.addNotice(n3);
	}
	
	@Test
	public void testConnexe5Titres() {
		listeNotices.add(n1);
		listeNotices.add(n2);
		listeNotices.add(n3);
		listeNotices.add(n4);
		listeNotices.add(n5);
		retour.add(n2);
		retour.add(n3);
		retour.add(n4);
		retour.add(n5);
		when(glob.noticesDuMemeAuteurQue(n1)).thenReturn(listeNotices);
		assertEquals(retour.size(),bib.chercherNoticesConnexes(n1).size());
	}
	
	@Test
	public void testConnexe2Titres() {
		listeNotices.add(n6);
		listeNotices.add(n7);
		retour.add(n7);
		when(glob.noticesDuMemeAuteurQue(n6)).thenReturn(listeNotices);
		assertEquals(retour.size(),bib.chercherNoticesConnexes(n6).size());
	}
	
	@Test
	public void testConnexe0Titres() {
		when(glob.noticesDuMemeAuteurQue(n8)).thenReturn(listeNotices);
		assertEquals(retour.size(),bib.chercherNoticesConnexes(n8).size());
	}
	
	@Test
	public void testAjoutNoticeInexistante() throws IncorrectIsbnException {
		listeNotices.add(n8);
		when(glob.getNoticeFromIsbn("Minority Report")).thenThrow(IncorrectIsbnException.class);
		assertThrows(AjoutImpossibleException.class, () -> {bib.ajoutNotice("Minority Report");});
	}
	
	@Test
	public void testAjoutNoticeCorrecteNew() throws IncorrectIsbnException, AjoutImpossibleException {
		when(glob.getNoticeFromIsbn("2")).thenReturn(n2);
		assertEquals(NoticeStatus.newlyAdded,bib.ajoutNotice("2"));
	}
	
	@Test
	public void testAjoutNoticeCorrecteNoChange() throws IncorrectIsbnException, AjoutImpossibleException {
		when(glob.getNoticeFromIsbn("1")).thenReturn(n1);
		assertEquals(NoticeStatus.nochange,bib.ajoutNotice("1"));
	}
	
	@Test
	public void testAjoutNoticeCorrecteUpdated() throws AjoutImpossibleException, IncorrectIsbnException {
		n3 = new NoticeBibliographique("3", "La Peau sur les os", "Stephen King");
		when(glob.getNoticeFromIsbn("3")).thenReturn(n3);
		assertEquals(NoticeStatus.updated,bib.ajoutNotice("3"));
	}
	
	@Test
	public void testPrévoirInventairePasBesoinPuisBesoin() {
		LocalDate uneDate = LocalDate.of(2021, 05, 01);
		Clock fixedClock = Clock.fixed(uneDate.atStartOfDay(ZoneId.systemDefault()).toInstant(), ZoneId.systemDefault());
		doReturn(fixedClock.instant()).when(mockedClock).instant();
		doReturn(fixedClock.getZone()).when(mockedClock).getZone();
		LocalDate dernierInv = b.getLastInventaire();
		bib.prévoirInventaire();
		LocalDate nouveauInv = b.getLastInventaire();
		assertTrue(dernierInv.equals(nouveauInv));
		//les deux tests sont dans un seul test parce qu'on manipule une même instance de bibliothèque
		LocalDate autreDate = LocalDate.of(2022, 12, 01);
		fixedClock = Clock.fixed(autreDate.atStartOfDay(ZoneId.systemDefault()).toInstant(), ZoneId.systemDefault());
		doReturn(fixedClock.instant()).when(mockedClock).instant();
		doReturn(fixedClock.getZone()).when(mockedClock).getZone();
		dernierInv = b.getLastInventaire();
		bib.prévoirInventaire();
		nouveauInv = b.getLastInventaire();
		assertFalse(dernierInv.equals(nouveauInv));
	}
}
