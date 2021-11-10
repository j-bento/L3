package agl.tp1;

import java.lang.management.OperatingSystemMXBean;
import java.util.ArrayList;

public class App 
{
    public static void main( String[] args )
    {
    	/*
    	GestionTER app = new GestionTER();
        
        //ajouter groupes + sujets
        app.addGroupe("groupe A");
        app.addGroupe("groupe B");
        app.addGroupe("groupe C");
        app.addGroupe("groupe D");
        app.addGroupe("groupe E");
        app.addGroupe("groupe F");

        app.addSujet("sujet A");
        app.addSujet("sujet B");
        app.addSujet("sujet C");
        app.addSujet("sujet D");
        app.addSujet("sujet E");
        app.addSujet("sujet F");

        ArrayList<Sujet> sujets = app.getSujets();

        //affecter aléatoirement des voeux aux groupes
        Groupe g;
        int nbSujets = sujets.size();
        for(int i=0; i<app.getNbGroupe(); i++) {
          g = app.getGroupe(i);
          int ordre = 1;
          for(int j=0; j<7; j++) {
            int index = (int)(Math.random() * nbSujets);
            Sujet s = sujets.get(index);
            if(g.addVoeu(ordre, s)) {
              ordre++;
            }
          }
        }
        System.out.println(app.toString());

        //serialiser données groupe et voeu
        app.serializeGroupe();
        app.serializeSujet();
        System.out.println("\n-----------------\nSerialisation:\n");

        //reinitialiser l'app
        app = new GestionTER();
        System.out.println("\n-------------------\nReinitialisation:\n" + app.toString() + "\n");

        //app.importSujet(sujetSer);
        app.importGroupe();
        app.importSujet();

        System.out.println(app.toString());
        */
    }
}
