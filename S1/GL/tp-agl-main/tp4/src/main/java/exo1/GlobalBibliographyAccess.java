package exo1;

import java.util.ArrayList; 

public class GlobalBibliographyAccess implements IGlobalBibliographyAccess {
	
	
	@Override
	public NoticeBibliographique getNoticeFromIsbn(String isbn) throws IncorrectIsbnException {
		throw new UnsupportedOperationException();
	}

	@Override
	public ArrayList<NoticeBibliographique>noticesDuMemeAuteurQue(NoticeBibliographique ref){
		throw new UnsupportedOperationException();
	}
	
	@Override
	public ArrayList<NoticeBibliographique> autresEditions(NoticeBibliographique ref){
		throw new UnsupportedOperationException();
	}
	
}
