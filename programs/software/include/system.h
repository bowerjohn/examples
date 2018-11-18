#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<Eigen/Dense>
#include<string>
#include<vector>
#include "coshfunc.h"

void Mkdir(char folder[100]);
void MkdirLoop(std::string folder, int start, int finish);
void Touch(char file[100]);

bool BothAreSpaces(char lhs, char rhs);
void RemoveSpaces(std::string& str);

void PrintFile(std::string filename);
void PrintFormattedFile(std::string filename,std::string delimiter);

void LoadFile(std::string filename, Eigen::MatrixXd &Matrix,std::string delimiter);
void LoadParamFile(std::string filename, std::vector<std::string> &Names, Eigen::MatrixXd &Matrix,std::string delimiter);
void LoadDataFile(std::string folder, std::string filename, std::string delimiter, int start, int finish, int column, Eigen::MatrixXd &Matrix);
void LoadDataFiles(std::string folder, std::vector<std::string> filenames, std::string delimiter, int start, int finish, int column, std::vector<Eigen::MatrixXd> &Matrix);

void WriteFile(std::string filename, Eigen::MatrixXd &Matrix,std::string delimiter);
void WriteParamFile(std::string fileName, std::vector<std::string> &header, std::string delimiter, Eigen::MatrixXd &file);
void WriteParamFileLoop(std::string filename, std::string folder, int start, std::vector<std::string> &header, std::string delimiter, Eigen::MatrixXd &matrix);
void WriteParameterFiles(std::string rangename, std::string foldername, std::string filename, std::string delimiter, int start, int finish, int ab);
void WriteParameterFiles(std::string rangename, std::string foldername, std::string filename, std::string delimiter, int start, int finish, int ab, Eigen::MatrixXd &Parameters);

void LHCSampling(Eigen::MatrixXd &hypercube, int samples, int ab, Eigen::MatrixXd range);

#endif
