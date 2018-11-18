#include<iostream>
#include<Eigen/Dense>
#include<string>
#include<vector>
#include<stdlib.h>
#include "system.h"
#include "analysis.h"
#include "coshfunc.h"

int main(int argc, char* argv[]){
  std::vector<std::string> modelfilenames={"I211_J211.dat","I2212_J2212.dat","I321_J2212.dat","I321_J321.dat"},
    expfilenames={"star_pipi.dat","star_ppbar.dat","star_pK.dat","star_KK.dat"};

  std::string foldername="model_output",
    writefilename="parameters.dat",
    rangename=foldername+"/parameter_priors.dat",
    delimiter=" ",
    infilename=foldername+"/moments_parameters.dat",
    outfilename=foldername+"/wave.dat";

  int start=0,
    finish=1000,
    column=1,
    ab=4,
    n=500,
    nmax=4,
    modelfiles = modelfilenames.size(),
    expfiles = expfilenames.size();
  int samples=finish-start;
  double x=8;

  std::vector<Eigen::MatrixXd> ModelMatrix(modelfiles),
    ExpMatrix(expfiles);
  Eigen::MatrixXd Dy,ModelObs,ExpObs,Parameters,GAB;
  Eigen::VectorXd modeldy, expdy;

  //Load Data
  LoadDataFile(foldername, modelfilenames[0], delimiter, 0, 1, 0, Dy);
  modeldy = Dy.col(0);
  LoadDataFile(foldername, expfilenames[0], delimiter, 0, 1, 0, Dy);
  expdy = Dy.col(0);

  //Write Parameters files
  WriteParameterFiles(rangename, foldername, writefilename, delimiter, start, finish, ab,Parameters);
  WriteFile(infilename,Parameters,delimiter);

  //Construct gab functions
  CDistCosh
    dist;
  LoadFile(infilename, Parameters, delimiter);
  dist.FunctionSet(n,x,samples,ab,nmax,Parameters,GAB);
  WriteFile(outfilename,GAB,delimiter);

  //Run Scott's program 
  //-- Note the program run by script.sh has been removed
  //   for the purposes of this example code, but the 
  //   code output has been kept in their respective run
  //   folders
  //system("./run.sh 0 1000");

  //Conduct Observables Analysis
  double er=0.1;
  Eigen::VectorXd Error,
    Mean,
    EigenValues;
  Eigen::MatrixXd ModelTilde,
    ExpTilde,
    Covariance,
    EigenVectors,
    ModelZ,
    ExpZ;

  LoadDataFiles(foldername, modelfilenames, delimiter, start, finish, column, ModelMatrix);
  LoadDataFiles(foldername, expfilenames, delimiter, 0, 1, column, ExpMatrix);
  MatrixMoments(ModelMatrix,modeldy,ModelObs);
  MatrixMoments(ExpMatrix,expdy,ExpObs);
  Error = er*ExpObs.col(0);

  AverageRows(Mean,ModelObs);
  TildeFunction(ModelTilde,Mean,Error,ModelObs);
  TildeFunction(ExpTilde,Mean,Error,ExpObs);

  CovarianceFunction(Covariance,ModelObs);
  EigenSolve(EigenValues,EigenVectors,Covariance);
  EigenSort(EigenValues,EigenVectors);
  ModelZ = ModelObs.transpose()*EigenVectors;
  ExpZ = ExpObs.transpose()*EigenVectors;


  /****************************************
       Choose what you'd like to output:
   ****************************************/   

  //std::cout << "Parameters:\n" << Parameters << std::endl;  
  //std::cout << "ModelObs:\n" << ModelObs << std::endl;
  //std::cout << "ExpObs:\n" << ExpObs << std::endl;
  //std::cout << "Error:\n" << Error << std::endl;
  //std::cout << "Mean:\n" << Mean << std::endl;
  //std::cout << "ModelTilde:\n" << ModelTilde << std::endl;
  //std::cout << "ExpTilde:\n" << ExpTilde << std::endl;
  //std::cout << "Covariance:\n" << Covariance << std::endl;
  //std::cout << "EV:\n" << EigenValues << std::endl;
  //std::cout << "EV:\n" << EigenVectors << std::endl;
  //std::cout << "----------------\n" << std::endl;
  //std::cout << "ModelZ:\n" << ModelZ << std::endl;
  AverageColumns(Mean,ModelZ);
  //std::cout << "MMean:\n" << Mean.transpose() << std::endl;
  //std::cout << "ExpZ:\n" << ExpZ << std::endl;

  return 0;
}
