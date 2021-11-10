package agl.tp1;

import java.util.HashMap;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;

@JsonIgnoreProperties(ignoreUnknown = true)
public class Groupe {
  public int id;
  public static int idPartage;
  public String nom;
  public HashMap<Integer, Sujet> voeux;
  public boolean voeuFini;

  public Groupe() {}

  public Groupe(int id, int idPartage, String nom, HashMap<Integer, Sujet> voeux, boolean voeuFini) {
    this.id = id;
    Groupe.idPartage = idPartage;
    this.nom = nom;
    this.voeux = voeux;
    this.voeuFini = voeuFini;
  }

  public Groupe(String nom) {
    this.id = idPartage;
    idPartage = idPartage + 1;
    this.nom = nom;
    this.voeux = new HashMap<Integer, Sujet>();
    this.voeuFini = false;
  }

  public boolean getVoeuFini() {
	  return this.voeuFini;
  }
  
  public void setNom(String nom) {
    this.nom = nom;
  }
  public String getNom() {
    return this.nom;
  }
  public int getId() {
    return this.id;
  }
  public void setVoeuFini(boolean voeuFini) {
    this.voeuFini = voeuFini;
  }
  
  public void setVoeux(HashMap<Integer, Sujet> hash) {
    this.voeux = hash;
  }

  private boolean isSujetInVoeu(Sujet suj) {
    boolean inIt = false;
    for(Integer key : this.voeux.keySet()) {
      if(this.voeux.get(key) == suj) {
        inIt = true;
      }
    }
    return inIt;
  }

  public boolean addVoeu(int ordre, Sujet suj) throws cantAddVoeu{
    if(ordre > 0 && ordre < 6) {
      if(!this.isSujetInVoeu(suj)) {
        if(!this.voeux.keySet().contains(ordre)) {
          this.voeux.put(ordre, suj);
        } else {
        	throw new cantAddVoeu("L'ordre a déjà été rempli");
        }
      } else {
    	  throw new cantAddVoeu("Le sujet a déjà été choisi");
      }
    } else {
    	throw new cantAddVoeu("L'ordre du voeu doit être entre 1 et 5");
    }
    boolean complet = true;
    for(int i=1; i<6; i++) {
      if(this.voeux.get(i) == null) {
        complet = false;
      }
    }
    if(complet) {
      this.voeuFini = true;
    }
    return true;
  }

  public boolean isVoeuReady() {
    return this.voeuFini;
  }

  public String toString() {
    String str = this.nom + " (id:" + this.id + ")\n"; 
    for(Integer key : this.voeux.keySet()) {
      str += "--" + key + ": " + this.voeux.get(key).toString() + "\n";
    }
    return str;
  }

}

/*
 private HashMap<String, NoticeBiblio> catalogue;

  public Catalogue() {
    catalogue = new HashMap<String, NoticeBiblio>();**/
