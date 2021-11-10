package agl.tp2_courriel;

import java.util.ArrayList;

public class Courrier {
    private String adresse;
    private String titre;
    private String corps;
    private ArrayList<String> joint;

    public Courrier() {
        adresse = "";
        titre = "";
        corps = "";
        joint = new ArrayList<String>();
    }

    public Courrier(String adr, String titr, String corp) {
        adresse = adr;
        titre = titr;
        corps = corp;
        joint = new ArrayList<String>();
    }
    
    public Courrier(String adr, String titr, String corp, ArrayList<String> join) {
        adresse = adr;
        titre = titr;
        corps = corp;
        joint = join;
    }

    public String getAdresse() {
        return this.adresse;
    }

    public void setAdresse(String adresse) {
        this.adresse = adresse;
    }

    public String getTitre() {
        return this.titre;
    }

    public void setTitre(String titre) {
        this.titre = titre;
    }

    public String getCorps() {
        return this.corps;
    }

    public void setCorps(String corps) {
        this.corps = corps;
    }

    public ArrayList<String> getJoint() {
        return this.joint;
    }

    public void setJoint(ArrayList<String> joint) {
        this.joint = joint;
    }

    public void addJoint(String join) {
        this.joint.add(join);
    }

    public void envoyer() throws EnvoiInvalide {
        //verifier présence adresse
        if(!adressePresente()) {
            throw new EnvoiInvalide("Pas de destinataire");
        }
        //verifier adresse bien formée
        if(!adresseBienFormee()) {
            throw new EnvoiInvalide("Adresse du destinataire incorrecte");
        }
        //verifier présence titre
        if(!titrePresent()) {
            throw new EnvoiInvalide("Pas de titre");
        }
        //verifier si message contient "joint", si oui si présence d'au moins une pièce jointe
        if(motCleJoin() && !pieceJointePresente()) {
            throw new EnvoiInvalide("Pas de piece jointe");
        }
    }

    private boolean adressePresente() {
        return !(adresse.length()==0);
    }

    private boolean adresseBienFormee() {
        return adresse.matches("(.+)@(.+)\\.(.+)");
    }

    private boolean titrePresent() {
        return !(titre.length()==0);
    }

    private boolean motCleJoin() {
        return corps.matches("(.*)(joint|jointe|PJ)(.*)");
    }

    private boolean pieceJointePresente() {
        return !(joint.size() == 0);
    }
}
