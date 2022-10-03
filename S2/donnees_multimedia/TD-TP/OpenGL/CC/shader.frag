// --------------------------------------------------------------------------
// gMini,
// a minimal Glut/OpenGL app to extend
//
// Copyright(C) 2007-2009
// Tamy Boubekeur
//
// All rights reserved.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License (http://www.gnu.org/licenses/gpl.txt)
// for more details.
//
// --------------------------------------------------------------------------

uniform float ambientRef;
uniform float diffuseRef;
uniform float specularRef;
uniform float shininess;
uniform int levels;

varying vec4 p;
varying vec3 n;


void main (void) {
    vec3 P = vec3 (gl_ModelViewMatrix * p);
    vec3 N = normalize (gl_NormalMatrix * n);
    vec3 V = normalize (-P);

    vec4 Isa = gl_LightModel.ambient;
    vec4 Ka = gl_FrontMaterial.ambient;
    vec4 Ia = Isa*Ka;

    vec4 I = ambientRef * Ia ;

    for (int i = 0; i < 1; i++) {

        vec4 Isd = gl_LightSource[i].diffuse;
        vec4 Kd = gl_FrontMaterial.diffuse;

        vec3 L = normalize (gl_LightSource[i].position.xyz - P);
        //Exercice 3
        //mettre à jour L pour avoir une lumière placée à la position de la caméra
        //L = ...

        float dotLN = max(dot (L, N), 0.);

        //TOON shading a completer

        //Caluler la valeur de la variable diffuse pour le cel shading en utilisant la variable levels
        float diffuse = 0.0;
        
        float step = 1./float(levels);
        while (diffuse < dotLN){
            diffuse += step;
        }
        diffuse -= step; //on fera toujours une étape de trop, on l'enlève après la boucle

        vec4 Id = Isd*Kd*diffuse; // on remplace la valeur de dotLN par celle de son arrondi

        vec4 Iss = gl_LightSource[i].specular;
        vec4 Ks = gl_FrontMaterial.specular;

        vec3 R = reflect (-L, N);
        //ou
        // R = 2.*dotLN*N -L;

        float dotRV = max(dot(R, V), 0.0);
        vec4 Is = Iss*Ks*max (0.0, pow (dotRV, shininess));

        //Caluler l'intensité en utilisant 'diffuse' pour moduler la couleur : indication utiliser Kd
        
        I += diffuseRef * Id + specularRef * Is;

        //Ajouter un bord noir en utilisant un seuil sur le produit scalaire entre N et V
        float seuil = 0.3;
        float dotNV = max(dot(N, V), 0.);
        if (dotNV < seuil){ /*affichage d'un bord noir*/}

    }

    gl_FragColor =vec4 (I.xyz, 1.);
}

