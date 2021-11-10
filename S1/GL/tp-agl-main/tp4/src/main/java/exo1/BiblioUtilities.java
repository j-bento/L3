package exo1;

import java.time.Clock;
import java.time.LocalDate;
import java.time.ZoneId;
import java.util.ArrayList;

public class BiblioUtilities {
	
	public ArrayList<NoticeBibliographique> chercherNoticesConnexes(NoticeBibliographique ref) {
		GlobalBibliographyAccess GBA=new GlobalBibliographyAccess();
		return GBA.noticesDuMemeAuteurQue(ref);
	}
	/*
	public void ajoutNotice(String isbn) throws AjoutImpossibleException {
		
		GlobalBibliographyAccess GBA=new GlobalBibliographyAccess();
		if GBA.getNoticeFromIsbn(isbn){
			
		}
	}*/
	
	public void prévoirInventaire() {
		
	}
	LocalDate uneDate = LocalDate.of(2022, 12, 01);
	Clock fixedClock = Clock.fixed(uneDate.atStartOfDay(ZoneId.systemDefault()).toInstant(), ZoneId.systemDefault());
	//doReturn(fixedClock.instant()).when(mockedClock).instant();
	//doReturn(fixedClock.getZone()).when(mockedClock).getZone();
}
