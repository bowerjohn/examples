#ifndef __ANALYSIS_H__
#define __ANALYSIS_H__

#include<Eigen/Dense>
#include<vector>
#include<iostream>

void AverageColumns(Eigen::VectorXd &average, Eigen::MatrixXd matrix);
void AverageRows(Eigen::VectorXd &average, Eigen::MatrixXd matrix);
void TildeFunction(Eigen::MatrixXd &tilde, Eigen::VectorXd mean, Eigen::VectorXd error, Eigen::MatrixXd matrix);
void CovarianceFunction(Eigen::MatrixXd &cov, Eigen::MatrixXd matrix);
void EigenSolve(Eigen::VectorXd &eigenvalues, Eigen::MatrixXd &eigenvectors, Eigen::MatrixXd matrix);
void FindMax(Eigen::VectorXd vector, int &index, double &max);
void FindMax(Eigen::MatrixXd vector, int &index, double &max);
void EigenSort(Eigen::VectorXd &eigval, Eigen::MatrixXd &eigvec);

void ZerothMoment(Eigen::MatrixXd Function, double &Moment);
void FirstMoment(Eigen::MatrixXd Function, double &Moment);
void SecondMoment(Eigen::MatrixXd Function, double &Moment);
void MatrixMoments(std::vector<Eigen::MatrixXd> Matrix, Eigen::VectorXd DelX, Eigen::MatrixXd &Obs);

#endif
