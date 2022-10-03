#include "Mesh.h"
#include <iostream>
#include <fstream>

Vec3 Mesh::scalarToRGB( float scalar_value ) const //Scalar_value ∈ [0, 1]
{
    Vec3 rgb;
    float H = scalar_value*360., S = 1., V = 0.85,
            P, Q, T,
            fract;

    (H == 360.)?(H = 0.):(H /= 60.);
    fract = H - floor(H);

    P = V*(1. - S);
    Q = V*(1. - S*fract);
    T = V*(1. - S*(1. - fract));

    if      (0. <= H && H < 1.)
        rgb = Vec3( V,  T,  P);
    else if (1. <= H && H < 2.)
        rgb = Vec3( Q,  V,  P);
    else if (2. <= H && H < 3.)
        rgb = Vec3( P,  V,  T);
    else if (3. <= H && H < 4.)
        rgb = Vec3( P,  Q,  V);
    else if (4. <= H && H < 5.)
        rgb = Vec3( T,  P,  V);
    else if (5. <= H && H < 6.)
        rgb = Vec3( V,  P,  Q);
    else
        rgb = Vec3( 0.,  0.,  0.);

    return rgb;
}

Vec3 Mesh::projectPointSegment(Vec3 a, Vec3 b, Vec3 c) {
    double r = Vec3::dot(b - a, b - a);
    if (fabs(r) < 1e-12) return a;
    r = Vec3::dot(c - a, b - a) / r;
    if (r < 0) return a;
    if (r > 1) return b;
    return a + (b - a) * r;
}

void Mesh::computeSkinningWeights( Skeleton & skeleton ) {
    //---------------------------------------------------//
    //---------------------------------------------------//
    // code to change :
    // Indications:
    // you should compute weights for each vertex w.r.t. the skeleton bones
    // so each vertex will have B weights (B = number of bones)
    //Don't forget to normalize weights
    // these weights shoud be stored in vertex.weights:
    
    // w : (weights?), r : rotation, t : translation
    for( size_t i = 0 ; i < vertices.size() ; ++i ) {
        MeshVertex & vertex = vertices[ i ];
        vertex.weights.clear(); // on assure que les points sont bien reset avant d'opérer
        vertex.weights = 0.;
        // vertex.weights.resize(skeleton.bones.size());
        for (size_t j = 0; j < skeleton.bones.size(); j++){
            //on récupère les articulations aux 2 extrémités de l'os
            Vec3 a = skeleton.articulations[skeleton.bones[j].joints[0]].position;
            Vec3 art2 = skeleton.articulations[skeleton.bones[j].joints[1]].position;
            Vec3 c = projectPointSegment(a, b, vertex.position);
            double dist = (vertex.position - c).length();
            double w = pow(1/dist, n);
            vertex.weights.push_back(w);
            weights += w;
            // a: articulation 1, b: articulation 2, c : position du vertex 
            // calcul ab et ac et ac' 
            Vec3 AB = art2 - a;
            Vec3 AC = vertex.position - a;
            Vec3 ACprimeNormalized = Vec3::cross(AB,AC);
            // ACprimeNormalized.dot(AB, AC);
            ACprimeNormalized /= AC.length();
            Vec3 proj = a + std::min<double>(1.,std::max<double>(0.,Vec3::dot(AC,AB) / Vec3::dot(AB,AB))) * AB;
            Vec3 Cprime;
            for (int k = 0; k < 2; k++) 
            {Cprime[k] = a[k] + ACprimeNormalized[k];}

            // calcul du vecteur poids CCprime
            // p - proj pour obtenir la distance
            Vec3 CCprime = vertex.position - Cprime;
            // double alpha_ij = 1. / CCprime.squareLength();
            double alpha_ij = 1. / (proj - vertex.position).squareLength();
            alpha_ij*=alpha_ij;
            alpha_ij*=alpha_ij;
            // vertex.weights[j] = proj.length();
            vertex.weights[j] = alpha_ij;
        }
    }

    //---------------------------------------------------//
    //---------------------------------------------------//
    //---------------------------------------------------//
}

void Mesh::draw( int displayed_bone ) const {

    glEnable(GL_LIGHTING);
    glBegin (GL_TRIANGLES);
    for (unsigned int i = 0; i < triangles.size (); i++)
        for (unsigned int j = 0; j < 3; j++) {
            const MeshVertex & v = vertices[triangles[i].v[j]];
            if( displayed_bone >= 0 && v.weights.size() > 0 ){
                // code to change :
                Vec3 color = scalarToRGB(v.weights[displayed_bone]);
                glColor3f(color[0],color[1],color[2]);
                // Indications:
                //Call the function scalarToRGB so that you get the same coloring as slide 51
                //Update the color from the Vec3 resulting color

            }
            glNormal3f (v.normal[0], v.normal[1], v.normal[2]);
            glVertex3f (v.position[0], v.position[1], v.position[2]);
        }
    glEnd ();
}

void Mesh::drawTransformedMesh( SkeletonTransformation & transfo ) const {
    std::vector< Vec3 > new_positions( vertices.size() );

    //---------------------------------------------------//
    //---------------------------------------------------//
    // code to change :
    for( unsigned int i = 0 ; i < vertices.size() ; ++i ) {
        Vec3 p = vertices[i].position;

        // Indications:
        // you should use the skinning weights to blend the transformations of the vertex position by the bones.
        // to update the position use the weight and the bone transformation
        // for each bone p'=R*p+t
        new_positions[ i ] = p;

    }
    //---------------------------------------------------//
    //---------------------------------------------------//
    //---------------------------------------------------//

    glEnable(GL_LIGHTING);
    glBegin (GL_TRIANGLES);
    for (unsigned int i = 0; i < triangles.size (); i++)
        for (unsigned int j = 0; j < 3; j++) {
            const MeshVertex & v = vertices[triangles[i].v[j]];
            Vec3 p = new_positions[ triangles[i].v[j] ];
            glNormal3f (v.normal[0], v.normal[1], v.normal[2]);
            glVertex3f (p[0], p[1], p[2]);
        }
    glEnd ();
}

void Mesh::loadOFF (const std::string & filename) {
    std::ifstream in (filename.c_str ());
    if (!in)
        exit (EXIT_FAILURE);
    std::string offString;
    unsigned int sizeV, sizeT, tmp;
    in >> offString >> sizeV >> sizeT >> tmp;
    vertices.resize (sizeV);
    triangles.resize (sizeT);
    for (unsigned int i = 0; i < sizeV; i++)
        in >> vertices[i].position;
    int s;
    for (unsigned int i = 0; i < sizeT; i++) {
        in >> s;
        for (unsigned int j = 0; j < 3; j++)
            in >> triangles[i].v[j];
    }
    in.close ();
    recomputeNormals ();
}

void Mesh::recomputeNormals () {
    for (unsigned int i = 0; i < vertices.size (); i++)
        vertices[i].normal = Vec3 (0.0, 0.0, 0.0);
    for (unsigned int i = 0; i < triangles.size (); i++) {
        Vec3 e01 = vertices[triangles[i].v[1]].position -  vertices[triangles[i].v[0]].position;
        Vec3 e02 = vertices[triangles[i].v[2]].position -  vertices[triangles[i].v[0]].position;
        Vec3 n = Vec3::cross (e01, e02);
        n.normalize ();
        for (unsigned int j = 0; j < 3; j++)
            vertices[triangles[i].v[j]].normal += n;
    }
    for (unsigned int i = 0; i < vertices.size (); i++)
        vertices[i].normal.normalize ();
}
