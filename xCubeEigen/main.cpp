#include "MeshData.h"
#include <iostream>
#include <cstdlib>
#include "XCube.h"
#include "InverseMultiquadrics.h"
#include "Multiquadrics.h"
#include "GeneralInverseMultiquadrics.h"
#include "RBF.h"
#include "Gaussian.h"
#include "HBRBF.h"
#include "HBRBFEval.h"
#include "VTKExport.h"
#include "polyg/SurfacePolygonizer.h"
#include <QTimer>
#include <QTime>



#include <ctime>
#include <fstream>
#define XCUBE 0
#define INV_MULT 1
#define GAUSSIAN 2
#define MULTIQUADRIC 3
#define GEN_INV_MULT 4
using namespace std;
#include <stdio.h>
#include <sstream>
int main(int argc, char *argv[])
{




    int RBF_USED = XCUBE;
    //ofstream time("tempo");
    // cout << endl << endl << "*********************************************" << endl;
    RBF *rbf;
    bool usePoly;
    switch(RBF_USED)
    {
    case XCUBE:
    {
        rbf =new XCube();
        cout << "xcube" << endl;
        usePoly = true;
        break;
    }
    case INV_MULT:
    {
        cout << "Using Inverse Multiquadrics" << endl;
        rbf = new InverseMultiquadrics();
        usePoly = true;
        break;
    }
    case GAUSSIAN:
    {
        cout << "Using Inverse Multiquadrics" << endl;
        rbf = new Gaussian();
        usePoly = false;
        break;
    }
    case MULTIQUADRIC:
    {
        cout << "Using Inverse Multiquadrics" << endl;
        rbf = new Multiquadrics();
        usePoly = false;
        break;
    }
    case GEN_INV_MULT:
    {
        cout << "Using Inverse Multiquadrics" << endl;
        rbf = new GeneralInverseMultiquadrics();
        usePoly = false;
        break;
    }
    default:
    {
        cout << "Invalid RBF Kernel"    << endl;
        exit(0);
    }
    }

    //string names[] = {"cube_050.1","cube_050.2","cube_050.3","cube_050.4","cube_050.5", "cube_050.6","cube_050.7"};
    string names[] = {


        "rbf_cabra_ID2_Ciclo5",
        "rbf_cabra_ID2_Ciclo10",
        "rbf_cabra_ID7_Ciclo6_1",
        "rbf_cabra_ID7_Ciclo6_2",
        "rbf_cabra_ID7_Ciclo7_1",
        "rbf_cabra_ID7_Ciclo7_2",
        "rbf_cabra_ID7_Ciclo8_1",
        "rbf_cabra_ID7_Ciclo8_2",
        "rbf_cabra_ID7_Ciclo9_1",
        "rbf_cabra_ID7_Ciclo9_2",
        "rbf_cacto_ID2_Ciclo3",
        "rbf_cacto_ID7_Ciclo2_1",
        "rbf_cacto_ID7_Ciclo2_2",
        "rbf_coelho_ID2_Ciclo2",
        "rbf_coelho_ID2_Ciclo7",
        "rbf_coelho_ID4_Ciclo3_1",
        "rbf_coelho_ID4_Ciclo3_2",
        "rbf_coelho_ID7_Ciclo5_1",
        "rbf_coelho_ID7_Ciclo5_2",
        "rbf_coelho_ID7_Ciclo6_1",
        "rbf_coelho_ID7_Ciclo6_2",
        "rbf_dino_ID2_Ciclo3",
        "rbf_dino_ID2_Ciclo8",
        "rbf_dino_ID3_Ciclo1_1",
        "rbf_dino_ID3_Ciclo1_2",
        "rbf_dino_ID7_Ciclo6_1",
        "rbf_dino_ID7_Ciclo6_2",
        "rbf_dino_ID7_Ciclo7_1",
        "rbf_dino_ID7_Ciclo7_2",
        "rbf_elefante_ID2_Ciclo5",
        "rbf_elefante_ID2_Ciclo10",
        "rbf_elefante_ID3_Ciclo6_1",
        "rbf_elefante_ID3_Ciclo6_2",
        "rbf_elefante_ID4_Ciclo1_1",
        "rbf_elefante_ID4_Ciclo1_2",
        "rbf_elefante_ID7_Ciclo8_1",
        "rbf_elefante_ID7_Ciclo8_2",
        "rbf_elefante_ID7_Ciclo9_1",
        "rbf_elefante_ID7_Ciclo9_2",
        "rbf_gato_ID2_Ciclo4",
        "rbf_gato_ID2_Ciclo7",
        "rbf_gato_ID2_Ciclo11",
        "rbf_gato_ID3_Ciclo3_1",
        "rbf_gato_ID3_Ciclo3_2",
        "rbf_gato_ID7_Ciclo8_1",
        "rbf_gato_ID7_Ciclo8_2",
        "rbf_gato_ID7_Ciclo9_1",
        "rbf_gato_ID7_Ciclo9_2",
        "rbf_gato_ID7_Ciclo10_1",
        "rbf_gato_ID7_Ciclo10_2",
        "rbf_passaro_ID2_Ciclo7",
        "rbf_passaro_ID3_Ciclo1_1",
        "rbf_passaro_ID3_Ciclo1_2",
        "rbf_passaro_ID3_Ciclo5_1",
        "rbf_passaro_ID3_Ciclo5_2",
        "rbf_passaro_ID7_Ciclo6_1",
        "rbf_passaro_ID7_Ciclo6_2",
        "rbf_pinguim_ID2_Ciclo5",
        "rbf_pinguim_ID2_Ciclo8",
        "rbf_pinguim_ID3_Ciclo0_1",
        "rbf_pinguim_ID3_Ciclo0_2",
        "rbf_pinguim_ID7_Ciclo6_1",
        "rbf_pinguim_ID7_Ciclo6_2",
        "rbf_pinguim_ID7_Ciclo7_1",
        "rbf_pinguim_ID7_Ciclo7_2",
        "rbf_unicornio_ID2_Ciclo0",
        "rbf_unicornio_ID2_Ciclo3",
        "rbf_unicornio_ID2_Ciclo11",
        "rbf_unicornio_ID3_Ciclo1_1",
        "rbf_unicornio_ID3_Ciclo1_2",
        "rbf_unicornio_ID7_Ciclo8_1",
        "rbf_unicornio_ID7_Ciclo8_2",
        "rbf_unicornio_ID7_Ciclo9_1",
        "rbf_unicornio_ID7_Ciclo9_2",
        "rbf_unicornio_ID7_Ciclo10_1",
        "rbf_unicornio_ID7_Ciclo10_2"

    };


    // double radius[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};
    // string names[] = {"rbf_ID2_Ciclo3"};


    // string names[] = {""};

    std::string outFile = "tempos.txt";
    std::ofstream fOut;
    fOut.open(outFile.c_str());

    QTime t;
    t.start();


    int i = 0;
    for(int i = 0; i < 75 ; i++)
    {

        t.restart();


        cout << "Nome do arquivo DATA de entrada (sem extensao): ";

        string baseName;// =  string(argv[1]);
        baseName = string(names[i]);
        // cin >> baseName;
        cout << "*************************************" << endl;
        cout << "Mesh: " << baseName << endl;


        //  char rchar[20];
        // sprintf(rchar,"%f",radius[i]);

        string rString = "";//string(rchar);

        string coeffName = "../coeffs/"+baseName + rString+".bin";
        string offName = "../off/"+baseName + rString +".off";
        string dataName = "../data/" + baseName+".data";
        string vtkName = "../vtk/"+baseName+".vtk";
        // HERE
        MeshData m(dataName.c_str());

        cout << "npoints " << m.numPoints << endl;
        cout << "nnormals " << m.numNormals << endl;
        cout << "ntans: " << m.numTangents << endl;

        //radius in 0... 1
        rbf->radius = 3;//radius[i] ;//radius[pos];

        cout << "radius: " << rbf->radius << endl;
        HBRBF hb(rbf,&m, usePoly);
        hb.run(coeffName.c_str());

        //TO HERE

        HBRBFEval e(rbf,coeffName.c_str());

        SurfacePolygonizer sp(&e);
        sp.polygonize(offName.c_str(),3);

        fOut << baseName << " "<< m.numPoints << " " << m.numNormals << " " << pow(m.numPoints + (m.numNormals*3) + 4, 2)  << " " <<  t.elapsed() <<  std::endl;


        cout << "npoints " << m.numPoints << endl;
        cout << "nnormals " << m.numNormals << endl;
        cout << pow(m.numPoints + (m.numNormals*3) + 4, 2) << endl;

        qDebug ("Tempo de Execucao: %d milissegundos", t.elapsed());


        //         exit(2);
        //         //exit(2);
        //         //Export to vtk
        //        VTKExport vtk(&e,128);
        //        vtk.toVTK(vtkName.c_str());
        //         exit(9);




    }

    fOut.close();

    return 0;

}
