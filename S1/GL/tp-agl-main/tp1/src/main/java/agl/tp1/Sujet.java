package agl.tp1;

public class Sujet {
  public static int index;
  public String titre;
  public int id;

  public Sujet() {}

  public Sujet(String titre) {
    this.titre = titre;
    this.id = index;
    index++;
  }

  public String getTitre() {
    return this.titre;
  }

  public void setTitre(String titre) {
    this.titre = titre;
  }
  
  public int getId() {
    return this.id;
  }
  
  public String toString() {
    return this.titre + " (id:" + this.id + ")";
  }
}