package ter;

import java.util.ArrayList;

public class Groupe{
	  private int id;
	  private String nom;
	  private Sujet sujet;
	  private ArrayList<Sujet> voeux;
	  
	  //Accesseurs

	  public int getId(){
	    return this.id;
	  }
	  public String getNom(){
	    return this.nom;
	  } 

	  public void addEtu() {
		  
	  }

	  public void addVoeu (String voeu){
	    if (voeux.size()>=5)
	    {
	      System.out.println("Max de voeux atteint");
	    }
	    else{
	      voeux.add();
	    }
	  }

	  public Groupe(int id,String nom,Sujet sujet){
	    this.id=id;
	    this.nom=nom;
	    this.sujet=sujet;
	  }
	}