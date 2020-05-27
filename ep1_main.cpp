#include <cekeikon.h>
#include <string>
#include <sstream>
#include <iostream>
#include <math.h>

void transformaVermelho(Mat_<COR> a,Mat_<FLT> &b){
    COR vermelho(30,30,140);

    for(int l = 0;l < a.rows;l++){
        for(int c = 0;c < a.cols;c++){
            if(distancia(vermelho,a(l,c)) < 70){
                b(l,c) = 255;
            }
            else{
                b(l,c) = 0;
            }
        }
    }
}

int main(){
    Mat_<COR> a;
    le(a,"01.jpg");
    Mat_<FLT> b(a.rows,a.cols);
    std::stringstream ss;
    std::string arquivo;
    float maxCorr;
    int argMax,argCounter;
    Mat_<FLT> C(1,24);
    Mat_<FLT> A(1,24);

    transformaVermelho(a,b); // obter as componentes vermelhas medias da imagem

    for(int i = 0;i < 11;i++){
        Mat_<FLT> t;
        ss << "modelo_placa_resized_" << i << ".jpg";
        arquivo = ss.str();
        le(t,arquivo);
        cout << "Arquivo: " << arquivo << "\n";

        Mat_<FLT> corr = matchTemplateSame(b,t,CV_TM_CCOEFF_NORMED);

        maxCorr = 0;
        argMax = 0;
        argCounter = 0;

        imp(corr,"teste.jpg");

        for(int l = 0;l < corr.rows;l++){
            for(int c = 0;c < corr.cols;c++){
                if(corr(l,c) > maxCorr){
                    maxCorr = corr(l,c);
                    argMax = argCounter;
                    C(1,i) = maxCorr;
                    A(1,i) = argMax;
                }
                argCounter = argCounter + 1;
            }
        }
        ss.str("");
        arquivo.clear();
    }
}