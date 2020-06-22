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


//        "rbf_pinguim_corpo_ID7_Ciclo4_2",
//        "rbf_pinguim_corpo_ID7_Ciclo4_1",
//        "rbf_pinguim_corpo_ID7_Ciclo3_2",
//        "rbf_pinguim_corpo_ID7_Ciclo3_1",
//        "rbf_pinguim_corpo_ID2_Ciclo5"

//        "rbf_pinguim_cabeca_ID3_Ciclo0_2",
//        "rbf_pinguim_cabeca_ID3_Ciclo0_1",
//        "rbf_pinguim_cabeca_ID2_Ciclo2"

        "rbf_peixe_ID3_Ciclo3_2",
        "rbf_peixe_ID3_Ciclo3_1",
        "rbf_peixe_ID3_Ciclo1_2",
        "rbf_peixe_ID3_Ciclo1_1",
        "rbf_peixe_ID2_Ciclo5"


//        "cromossomo"
//        "exportData0",
//        "exportData1",
//        "exportData2",
//        "exportData3",
//        "exportData4",
//        "exportData5",
//        "exportData6",
//        "exportData7",
//        "exportData8"
//        "exportData9",
//        "exportData10",
//        "exportData11",
//        "exportData12",
//        "exportData13",
//        "exportData14",
//        "exportData15",
//        "exportData16",
//        "exportData17",
//        "exportData18",
//        "exportData19",
//        "exportData20",
//        "exportData21",
//        "exportData22",
//        "exportData23",
//        "exportData24",
//        "exportData25",
//        "exportData26",
//        "exportData27",
//        "exportData28",
//        "exportData29",
//        "exportData30",
//        "exportData31",
//        "exportData32",
//        "exportData33",
//        "exportData34",
//        "exportData35",
//        "exportData36",
//        "exportData37",
//        "exportData38",
//        "exportData39",
//        "exportData40",
//        "exportData41",
//        "exportData42",
//        "exportData43",
//        "exportData44",
//        "exportData45",
//        "exportData46",
//        "exportData47",
//        "exportData48",
//        "exportData49",
//        "exportData50",
//        "exportData51",
//        "exportData52",
//        "exportData53",
//        "exportData54",
//        "exportData55",
//        "exportData56",
//        "exportData57",
//        "exportData58",
//        "exportData59",
//        "exportData60",
//        "exportData61",
//        "exportData62",
//        "exportData63",
//        "exportData64",
//        "exportData65",
//        "exportData66",
//        "exportData67",
//        "exportData68",
//        "exportData69",
//        "exportData70",
//        "exportData71",
//        "exportData72",
//        "exportData73",
//        "exportData74",
//        "exportData75",
//        "exportData76",
//        "exportData77",
//        "exportData78",
//        "exportData79",
//        "exportData80",
//        "exportData81",
//        "exportData82",
//        "exportData83",
//        "exportData84",
//        "exportData85",
//        "exportData86",
//        "exportData87",
//        "exportData88",
//        "exportData89",
//        "exportData90",
//        "exportData91",
//        "exportData92",
//        "exportData93",
//        "exportData94",
//        "exportData95",
//        "exportData96",
//        "exportData97",
//        "exportData98",
//        "exportData99"


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
    for(int i = 0; i < 100 ; i++)
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
