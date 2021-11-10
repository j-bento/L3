package agl.tp1;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

//import com.fasterxml.jackson.core.JsonGenerationException;
//import com.fasterxml.jackson.core.JsonParseException;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;

public class GestionTER {
	public ArrayList<Groupe> groupes;
	public ArrayList<Sujet> sujets;
	
	public GestionTER() {
	  this.groupes = new ArrayList<Groupe>();
	  this.sujets = new ArrayList<Sujet>();
	}
	
	public void addGroupe(String nom) {
	  this.groupes.add(new Groupe(nom));
	}
	public void addSujet(String titre) {
	  this.sujets.add(new Sujet(titre));
	}
	public ArrayList<Sujet> getSujets() {
	  return this.sujets;
	}
	public int getNbGroupe() {
	  return this.groupes.size();
	}
	public Groupe getGroupe(int id) {
	  if(id >= 0 && id < this.getNbGroupe()) {
	    return this.groupes.get(id);
	  }
	  return new Groupe("n'existe pas");
	}
	
	public String toString() {
	  String str = "Liste des groupes:\n----------------\n";
	  for(int i=0; i<this.groupes.size(); i++) {
	    str += this.groupes.get(i).toString() + "\n";
	  }
	  str += "\n\nListe des sujets:\n------------------\n";
	  for(int i=0; i<this.sujets.size(); i++) {
	    str += this.sujets.get(i).toString() + "\n";
	  }
	  return str;
	}
	
	public void serializeGroupe() {
	  ObjectMapper test = new ObjectMapper();
	  try {
	    test.writeValue(new File("target/groupes.json"), this.groupes);
	  } catch (JsonProcessingException e) {
	    // TODO Auto-generated catch block
	    e.printStackTrace();
	  } catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	}
	
	public void serializeSujet() {
	  ObjectMapper test = new ObjectMapper();
	  try {
	    test.writeValue(new File("target/sujets.json"), this.sujets);
	  } catch (JsonProcessingException e) {
	    // TODO Auto-generated catch block
	    e.printStackTrace();
	  } catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	  }
	}
	
	public void importGroupe() {
	  ObjectMapper test = new ObjectMapper();
	  try {
	    Groupe[] groupes = test.readValue(new File("target/groupes.json"), Groupe[].class);
	    this.groupes = new ArrayList<Groupe>();
	    for(int i=0; i<groupes.length; i++) {
	      this.groupes.add(groupes[i]);
	    }
	  } catch (JsonMappingException e) {
	    // TODO Auto-generated catch block
	    e.printStackTrace();
	  } catch (JsonProcessingException e) {
	    // TODO Auto-generated catch block
	    e.printStackTrace();
	  } catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	}
	
	public void importSujet() {
	  ObjectMapper test = new ObjectMapper();
	  try {
	    Sujet[] sujets = test.readValue(new File("target/sujets.json"), Sujet[].class);
	    this.sujets = new ArrayList<Sujet>();
	    for(int i=0; i<sujets.length; i++) {
	      this.sujets.add(sujets[i]);
	    }
	  } catch (JsonMappingException e) {
	    // TODO Auto-generated catch block
	    e.printStackTrace();
	  } catch (JsonProcessingException e) {
	    // TODO Auto-generated catch block
	    e.printStackTrace();
	  } catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	}
}