package agl.tp4_mocks;

import java.util.ArrayList;

public interface InterfaceGlobalBibliographyAccess {

	NoticeBibliographique getNoticeFromIsbn(String isbn) throws IncorrectIsbnException;

	ArrayList<NoticeBibliographique> noticesDuMemeAuteurQue(NoticeBibliographique ref);

	ArrayList<NoticeBibliographique> autresEditions(NoticeBibliographique ref);

}