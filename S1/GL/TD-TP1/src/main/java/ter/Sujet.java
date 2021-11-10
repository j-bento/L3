package ter;
public class Sujet{
	  
	  private int id;
	  private String titre;
	  private Groupe grp;

	  //Accesseurs

	  public int getId(){
	    return this.id;
	  }
	   
	  public String getTitre(){
	    return this.titre;
	  }

	  public void setId(int id){
	    this.id=id;
	  }

	  public void setTitre(String titre){
	    this.titre=titre;
	  }

	  public Groupe getGrp(){
	    return this.grp;
	  }

	  public void setGrp(Groupe grp){
	    this.grp = grp;
	  }

	  //Constructeur

	  public Sujet(int id, String titre){
	    this.id=id;
	    this.titre=titre;
	  }
	}