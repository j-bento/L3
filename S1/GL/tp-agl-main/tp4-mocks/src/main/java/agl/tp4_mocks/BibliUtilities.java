package agl.tp4_mocks;

import java.time.Clock;
import java.time.LocalDate;
import java.time.Period;
import java.time.temporal.ChronoUnit;
import java.util.ArrayList;

public class BibliUtilities {
	
	public Clock horloge;
	public InterfaceGlobalBibliographyAccess glob;
	
	public BibliUtilities() {}
	
	public ArrayList<NoticeBibliographique> chercherNoticesConnexes(NoticeBibliographique ref) {
		ArrayList<NoticeBibliographique> connexe = new ArrayList<NoticeBibliographique>();
		//récupérer les notice du même auteur
		ArrayList<NoticeBibliographique> titres = glob.noticesDuMemeAuteurQue(ref);
		//en ajouter à la liste si pas même titre
		for (int i = 0; i < titres.size() && connexe.size() < 5; i++) {
			if (!titres.get(i).getTitre().equals(ref.getTitre())) {
				connexe.add(titres.get(i));
			}
		}
		//une fois qu'on en a 5 ou qu'on a tout parcouru on renvoie		
		return connexe;
	}
	
	public NoticeStatus ajoutNotice(String isbn) throws AjoutImpossibleException {
		NoticeBibliographique n;
		//si la notice n'existe pas, on ne peut l'ajouter
		try {
			n = glob.getNoticeFromIsbn(isbn);
		} catch (IncorrectIsbnException e) {
			throw new AjoutImpossibleException();
		}
		//récupérer la bibliothèque
		Bibliothèque b = Bibliothèque.getInstance();
		//ajouter à la bibliothèque et renvoyer le statut
		return b.addNotice(n);
	}
	
	public void prévoirInventaire() {
		//récupérer date du jour
		LocalDate jour = LocalDate.now(horloge);
		//récupérer la date du dernier inventaire
		Bibliothèque b = Bibliothèque.getInstance();
		LocalDate dernierInv = b.getLastInventaire();
		//faire la différence
	    long diff = ChronoUnit.MONTHS.between(dernierInv, jour);
	    if(diff >= 12) {
	    	b.inventaire();
	    }
	}
}
