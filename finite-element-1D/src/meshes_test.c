#include "meshes_seg.h"
#include "simple_dim.h"
#include <cassert>
#include <vector>

void test_Segment()
{
    assert(Seg::Nb() == 0);
    Seg S1 = Seg();
    assert(Seg::Nb() == 1);
    R1 P1 = R1(0.3);
    R1 P2 = R1(0);
    Seg S2 = Seg(P1,P2);
    assert(Seg::Nb() == 2);
    Seg S3 = Seg(S2);
    assert(Seg::Nb() == 3);
    S1 = S2;
    Seg * S4 = new Seg();
    assert(Seg::Nb() == 4);
    delete S4;
    assert(Seg::Nb() == 3);

    // Testing the values of the nodes
    assert(S1[0]->get() == 0.3 && S1[1]->get() ==0.);
    assert(S2[0]->get() == 0.3 && S2[1]->get() ==0.);
    assert(S3[0]->get() == 0.3 && S3[1]->get() ==0.);
    assert((S3.get(0))->get() ==0.3  && (S3.get(1))->get() ==0.);
    // Testing the addresses of the nodes
    assert( (S3[0] ==  S2[0])  && (S3[1] ==  S2[1]));
    assert( (S1[0] ==  S2[0])  && (S1[1] ==  S2[1]));

    cout << "Affichage du segment P1(0.3) P2(0.)" <<endl;
    S1.show();
    S1.showRaw();
    R1 P3 = R1(5.);
    S2.set(1,P3);
    cout << "Affichage  du segment P1(0.3,1.3) P2(5.)" << S2 <<endl;
}

void test_loadNodes()
{
    try{
        loadNodes("test_mes.msh");   
    }
    catch(std::exception &exce){
        assert(((string) exce.what()).compare("Impossible d'ouvrir le fichier: test_mes.msh") ==0);
    }
    vector<R1> arrayNodes = loadNodes("test_mesh.msh");
    int sizeA = arrayNodes.size();
    assert(sizeA ==  101);

    for (int i = 0; i<sizeA; i++  )
    {
        assert( fabs(arrayNodes[i].get() - 0.01*i)<0.000001 );  
    }
    return;
}
void test_loadSeg()
{
    vector<R1> arrayNodes = loadNodes("test_mesh.msh");
    vector<Seg> arraySeg;
    vector<vector<Seg*> >  segInNodes;
    try{
        loadSeg("test_mes.msh",arrayNodes,arraySeg,segInNodes);   
    }
    catch(std::exception &exce){
        assert(((string) exce.what()).compare("Impossible d'ouvrir le fichier: test_mes.msh") ==0);
    }

    loadSeg("test_mesh.msh",arrayNodes,arraySeg,segInNodes);
    int segSize = arraySeg.size(), nodeSize = arrayNodes.size(), stockSize=100 ;
    assert(arraySeg.size() == 100);

    for (int i = 0; i<segSize; i++  )
    {
        assert(fabs(arraySeg[i][0]->get()-0.01*i)<0.00001);
        assert(fabs(arraySeg[i][1]->get()-0.01*(i+1))<0.00001);
    }

    for (int i = 0; i<nodeSize; i++)
    {
        stockSize = (segInNodes[i]).size();
        for(int j=0; j<stockSize; j++)
        {
           
            assert( (  (*((segInNodes[i])[j]))[0] ==   &(arrayNodes[i])  ) || (  (*((segInNodes)[i][j]))[1] ==   &(arrayNodes[i]) ) ) ;
        }
    }
    return;
}
void test_Orthogonal_Mesh_1D()
{
    Orthogonal_Mesh_1D lineMesh("test_mesh.msh");
    lineMesh.make_Rigidity_Matrix();
    vector<double> value;
    vector<int> col_ind, row_ptr;
    lineMesh.get_Rigidity_Matrix(value,col_ind,row_ptr);
    assert(col_ind.size() ==  value.size());
    assert(col_ind.size() ==  101);
    assert(row_ptr.size() == 102);
    int Rsize = col_ind.size();
    for(int i = 0; i<Rsize; i++)
    {
        assert(col_ind[i]== i);
        assert(row_ptr[i] == i);
        if(i!=0 && i != Rsize-1)
        {
            assert(fabs(value[i]-0.02)<0.0000000001 );
        }
        else
        {
            assert( fabs(value[i]-0.01)<0.000000000001);
        }
    }
    assert(row_ptr[101]==101);
}

void test_P1_Lapl_Mesh_1D()
{
    P1_Lapl_Mesh_1D lineMesh("test_mesh.msh");
    lineMesh.make_Rigidity_Matrix();
    vector<double> value;
    vector<int> col_ind, row_ptr;
    lineMesh.get_Rigidity_Matrix(value,col_ind,row_ptr);
    assert(col_ind.size() ==  value.size());
    assert(col_ind.size() == 301);
    assert(row_ptr.size() == 102);
    int Rsize = col_ind.size();
    for(int i = 0; i<Rsize; i++)
    {

        if(i>1 && i < Rsize-2)
        {
            assert(col_ind[i]== (i+1)/3 +(i+1)%3-1);
            assert(row_ptr[(i+1)/3] == i -((i+1)%3));
            assert(fabs(value[i]+0.01-0.03*((i%3) ==0) )<0.0000000001 );
        }
    


    } 
    assert(col_ind[0] == 0);    
    assert(col_ind[1] == 1);         
    assert(row_ptr[0] == 0);
    assert( fabs(value[0]-0.01)<0.000000000001);
    assert( fabs(value[1]+0.01)<0.000000000001);

    assert(col_ind[299] ==  99);
    assert(col_ind[300] ==  100);
    assert(row_ptr[101] == 301);
    assert( fabs(value[299]+0.01)<0.000000000001);
    assert( fabs(value[300]-0.01)<0.000000000001);
}
void gnuPlot()
{
    vector<vector<Seg*> >  segInNodes;
    vector<R1> arrayNodes = loadNodes("test_mesh.msh");
    vector<Seg> arraySeg;
    loadSeg("test_mesh.msh",arrayNodes,arraySeg,segInNodes);
    exportGnuPlot(arraySeg);
}

int main()
{
   cout << "Test classe segment" << endl;
   test_Segment();
   cout << "Test reading mesh" << endl;
   test_loadNodes();
   cout << "Test Segment construction" << endl;
   test_loadSeg();
   cout << "Test Orthogonal rigidity matrix construction" <<endl;
   test_Orthogonal_Mesh_1D();
   cout << "Test P1 rigidity matrix construction" << endl;
   test_P1_Lapl_Mesh_1D();
   cout << "Test well performed" <<endl;
   gnuPlot();
}

