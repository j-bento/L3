package exo1;

import java.util.ArrayList;

public interface IGlobalBibliographyAccess {
	public NoticeBibliographique getNoticeFromIsbn(String isbn) throws IncorrectIsbnException;
	public ArrayList<NoticeBibliographique>noticesDuMemeAuteurQue(NoticeBibliographique ref);
	public ArrayList<NoticeBibliographique> autresEditions(NoticeBibliographique ref);
}