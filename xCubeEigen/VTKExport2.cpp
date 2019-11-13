#include "VTKExport2.h"

VTKExport2::VTKExport2(HBRBFEval *hb, int resolution)
{
    this->hb = hb;
    this->resolution = resolution;
    computeBB(hb->getMesh());
    this->mesh = hb->getMesh();
    this->rbf = hb->getRBF();
    pointKdtree = new KDTree<double,3>(hb->getMesh()->numPoints,hb->getMesh()->points,1,hb->getRBF()->radius*0.6);
}


void VTKExport2::computeNeighbours(double *points,
                                   int numPoints, KDTree<double,3> *kdTree,
                                   std::vector< std::vector<unsigned int> >& neighborPoints,
                                   bool greaterThan )

 {

     //greaterThan = true;
     if(greaterThan)//look for inballGreatherThanIndex
     {
         //copy points to use in kdtree

         int numEntries = 0;
         //temporary vector
         //an vector with indexes of the points.
         std::vector<unsigned int> neighbors;

         //an vector of neighbors of all points

         //for each point compute its neighbours
         for(int i = 0; i < numPoints; i++)
         {
             kdTree->inBallWithIndexGreaterThan(points, rbf->radius*0.9 , i, neighbors);
             std::sort(neighbors.begin(), neighbors.end());

             //allocate space
             neighborPoints[i].reserve(neighbors.size());
             //clean
             neighborPoints[i].clear();

             //copy
             neighborPoints[i].insert(neighborPoints[i].end(),
                                      neighbors.begin(), neighbors.end());


             //the number of matrix entries is updated
             numEntries+= neighbors.size();

             //clear to use with another point
             neighbors.clear();

         }
     }
     else
     {

         //copy points to use in kdtree

         int numEntries = 0;
         //temporary vector
         //an vector with indexes of the points.
         std::vector<unsigned int> neighbors;

         //an vector of neighbors of all points

         //for each point compute its neighbours
         for(int i = 0; i < numPoints; i++)
         {
             kdTree->inBall(points, rbf->radius*0.6   , neighbors);
             //std::sort(neighbors.begin(), neighbors.end());

             //allocate space
             neighborPoints[i].reserve(neighbors.size());
             //clean
             neighborPoints[i].clear();

             //copy
             neighborPoints[i].insert(neighborPoints[i].end(),
                                      neighbors.begin(), neighbors.end());


             //the number of matrix entries is updated
             numEntries+= neighbors.size();

             //clear to use with another point
             neighbors.clear();
         }
     }
 }


void VTKExport2::toVTK(const char *fileName)
{


    std::cerr << "Loading coefficients ..." << std::endl;

    computeBB(hb->getMesh());
    std::cerr << "Exporting to VTK ... please wait." << std::endl;
    std::ofstream ofnamefile(fileName,std::ios::out);


    ofnamefile << "# vtk DataFile Version 3.0\nNon-Uniform rect grid \nASCII\n";
    ofnamefile << "DATASET RECTILINEAR_GRID" << std::endl;
    ofnamefile << "DIMENSIONS " << resolution << " " << resolution << " " << resolution  <<std::endl;
    ofnamefile << "X_COORDINATES " << resolution <<  " float\n";
    for(unsigned int i = 0; i < resolution ; i++)
        ofnamefile << bbp1[0] +  (double)i/(double)resolution*(bbp2[0]-bbp1[0]) << " ";
    ofnamefile << "\nY_COORDINATES " <<resolution <<  " float\n";
    for(unsigned int i = 0; i < resolution ; i++)
        ofnamefile << bbp1[1] +  (double)i/(double)resolution*(bbp2[1]-bbp1[1]) << " ";
    ofnamefile << "\nZ_COORDINATES " << resolution <<  " float\n";
for(unsigned int i = 0; i < resolution ; i++)
    ofnamefile << bbp1[2] +  (double)i/(double)resolution*(bbp2[2]-bbp1[2]) << " ";
    ofnamefile << "\nPOINT_DATA " << resolution*resolution*resolution<< std::endl;
ofnamefile << "SCALARS Escalares float 1\nLOOKUP_TABLE default\n" << std::endl;

double spacingX = (fabs(bbp1[0]) + fabs(bbp2[0])) / resolution;
double spacingY = (fabs(bbp1[1]) + fabs(bbp2[1])) / resolution;
double spacingZ = (fabs(bbp1[2]) + fabs(bbp2[2])) / resolution;

cout << "spacingZ: " << spacingX << endl;
cout << "spacingY: " << spacingY << endl;
cout << "spacingZ: " << spacingZ << endl;

//exit(0);
double p[3];
p[0] = bbp1[0];
p[1] = bbp1[1];
p[2] = bbp1[2];
for(unsigned int i = 0; i < resolution ; i++)//Z
{
    p[1] = bbp1[1];
            for(unsigned int j = 0; j < resolution ; j++)//Y
            {
                p[0] = bbp1[0];
                    for(unsigned int k = 0; k < resolution ; k++)//X
                    {


                        //p[0] = bbp1[0] +  spacingX * k;//(double)k/(double)resolution*(bbp2[0]-bbp1[0]);
                        //p[1] = bbp1[1] +  spacingY * j;//(double)j/(double)resolution*(bbp2[1]-bbp1[1]);
                        //p[2] = bbp1[2] +  spacingZ * i;//(double)i/(double)resolution*(bbp2[2]-bbp1[2]);
                        //double r = hb->evalPoint()

                        bool ok= true;
                        double pn = VecMath::calcNorm(p);

                        for(int v =0; v < mesh->numPoints && ok; v++)
                        {

                            double *p2 = &mesh->points[v*3];
                            if(p[2]>=p2[2] && p[2]< p2[2]+spacingZ)
                            {
                                if(pn <= VecMath::calcNorm(p2)+rbf->radius/4)
                                    ok = true;
                                else
                                    ok = false;
                            }
                        }

                        if(ok)
                        {
                            ofnamefile << hb->evalPoint(p) << "  ";
                            ofnamefile.flush();
                        }
                        else
                        {
                            //cerr << " false " << endl;
                            ofnamefile << 0.001 << "  ";
                            ofnamefile.flush();
                        }

                    //	std::cerr << i*resolution*resolution + j*30 + k << "  ";
                        p[0]+=spacingX;
                    }
                    p[1]+=spacingY;
            }
            p[2]+=spacingZ;
}
    ofnamefile.close();
    std::cerr << "Exported to VTK file.\n " << std::endl;

}

void VTKExport2::computeBB(MeshData *m)
{
    double bboxoffset = 1.2;
        double min[] = {HUGE_VAL,HUGE_VAL,HUGE_VAL} ,max[] = {-HUGE_VAL,-HUGE_VAL,-HUGE_VAL} ;
        for(int i =0; i < m->numPoints; i++)
        {
                if(m->points[i*3  ] < min[0]) min[0] = m->points[i*3  ];
                if(m->points[i*3+1] < min[1]) min[1] = m->points[i*3+1];
                if(m->points[i*3+2] < min[2]) min[2] = m->points[i*3+2];


                if(m->points[i*3  ] > max[0]) max[0] = m->points[i*3  ];
                if(m->points[i*3+1] > max[1]) max[1] = m->points[i*3+1];
                if(m->points[i*3+2] > max[2]) max[2] = m->points[i*3+2];


        }


        bbp1[0] = min[0];//0.5*(min[0]+max[0])-bboxoffset*(0.5*(max[0]-min[0]));
        bbp1[1] = min[1];//0.5*(min[1]+max[1])-bboxoffset*(0.5*(max[1]-min[1]));
        bbp1[2]  =min[2];// 0.5*(min[2]+max[2])-bboxoffset*(0.5*(max[2]-min[2]));

        bbp2[0] = max[0];//0.5*(min[0]+max[0])+bboxoffset*(0.5*(max[0]-min[0]));
        bbp2[1] = max[1];//0.5*(min[1]+max[1])+bboxoffset*(0.5*(max[1]-min[1]));
        bbp2[2] = max[2];//0.5*(min[2]+max[2])+bboxoffset*(0.5*(max[2]-min[2]));
}
