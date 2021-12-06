package courriel;

import java.util.ArrayList;

public class Courriel {
    private String adresse;
    private String titre;
    private String corps;
    private ArrayList<String> joint;

    public Courriel() {
        adresse = "";
        titre = "";
        corps = "";
        joint = new ArrayList<String>();
    }

    public Courriel(String adr, String titr, String corp) {
        adresse = adr;
        titre = titr;
        corps = corp;
        joint = new ArrayList<String>();
    }
    
    public Courriel(String adr, String titr, String corp, ArrayList<String> join) {
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
        return !(adresse.isEmpty());
    }

    private boolean adresseBienFormee() {
        return adresse.matches("(.+)@(.+)\\.(.+)");
    }

    private boolean titrePresent() {
        return !(titre.isEmpty());
    }

    private boolean motCleJoin() {
        return corps.matches("(.*)(joint|jointe|PJ)(.*)");
    }

    private boolean pieceJointePresente() {
        return !(joint.isEmpty());
    }
}
