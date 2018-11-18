#include "system.h"

void Mkdir(char folder[100]){
  char command[150];
  sprintf(command,"if [ ! -d %s ]; then mkdir -p %s; fi",folder,folder);
  system (command);
}
void MkdirLoop(std::string folder,int start, int finish){
  char command[150],fold[120];
  for(int i=start;i<finish;i++){
    sprintf(fold,"%s/run%04d",folder.c_str(),i);
    sprintf(command,"if [ ! -d %s ]; then mkdir -p %s; fi",fold,fold);
    system (command);
  }
}
void Touch(char file[100]){
  char command[150];
  sprintf(command,"if [ ! -f %s ]; then touch %s; fi",file,file);
  system (command);
}

bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }
void RemoveSpaces(std::string& str){
  std::string::iterator new_end = std::unique(str.begin(), str.end(), BothAreSpaces);
  str.erase(new_end, str.end()); 
}
void PrintFile(std::string filename){
  std::string line;
  std::fstream myfile(filename,std::ios::in);
  if(myfile.is_open()){
    while(getline(myfile,line)){
      printf("%s\n",line.c_str());
    }
    myfile.close();
  }else{
    printf("Unable to open file.\n");
  }
}
void PrintFormattedFile(std::string filename,std::string delimiter){
  std::string line;
  std::fstream myfile(filename,std::ios::in);
  if(myfile.is_open()){
    while(getline(myfile,line)){
      if(line[0]!='#' && line!="\0"){
	RemoveSpaces(line);
	if(line.length()<delimiter.length()){
	}else{
	  if(line.substr(line.length()-delimiter.length(),line.length()) != delimiter){
	    line.append(delimiter);
	  }
	}
	if(line.find(delimiter) == 0){
	  line.erase(0,delimiter.length());
	}
	printf("%s\n",line.c_str());
      }
    }
    myfile.close();
  }else{
    printf("Unable to open file.\n");
  }
}
void LoadFile(std::string filename, Eigen::MatrixXd &Matrix,std::string delimiter){
  std::string line,
    number;
  std::size_t pos,length;
  std::ifstream myfile(filename);
  int rows=0,row=0,
    cols=0,col=0,
    max=0;

  if(myfile.is_open()){
    while(getline(myfile,line)){
      cols=0;
      if( line[0]!='#' && line!="\0" ){
	RemoveSpaces(line);
	if(line.length()<delimiter.length()){
	}else{
	  if(line.substr(line.length()-delimiter.length(),line.length()) != delimiter){
	    line.append(delimiter);
	  }
	}
	if(line.find(delimiter) == 0){
	  line.erase(0,delimiter.length());
	}
	while( (pos=line.find(delimiter)) != std::string::npos){
	  line.erase(0,pos+delimiter.length());
	  cols++;
	}
	if(cols>max){
	  max=cols;
	}
	rows++;
      }
      cols=max;
    }
    myfile.close();
  }else{
    printf("Unable to open file.\n");
  }

  Matrix = Eigen::MatrixXd::Zero(rows,cols);
  myfile.open(filename);
  if(myfile.is_open()){
    while(getline(myfile,line)){
      if(line[0]!='#' && line!="\0"){
	RemoveSpaces(line);
	if(line.length()<delimiter.length()){
	}else{
	  if(line.substr(line.length()-delimiter.length(),line.length()) != delimiter){
	    line.append(delimiter);
	  }
	}
	if(line.find(delimiter) == 0){
	  line.erase(0,delimiter.length());
	}
	col=0;
	while( (pos=line.find(delimiter)) != std::string::npos){
	  number=line.substr(0,pos+delimiter.length());
	  Matrix(row,col) = std::stof( number );
	  line.erase(0,pos+delimiter.length());
	  col++;
	}
	row++;
      }
    }
    myfile.close();
  }else{
    printf("Unable to open file.\n");
  }
}
void LoadParamFile(std::string filename, std::vector<std::string> &Names, Eigen::MatrixXd &Matrix,std::string delimiter){
  std::string line,
    number;
  std::size_t pos,length;
  std::ifstream myfile(filename);
  int rows=0,row=0,
    cols=0,col=0,
    max=0;

  if(myfile.is_open()){
    while(getline(myfile,line)){
      cols=0;
      if( line[0]!='#' && line!="\0" ){
	RemoveSpaces(line);
	if(line.length()<delimiter.length()){
	}else{
	  if(line.substr(line.length()-delimiter.length(),line.length()) != delimiter){
	    line.append(delimiter);
	  }
	}
	if(line.find(delimiter) == 0){
	  line.erase(0,delimiter.length());
	}
	while( (pos=line.find(delimiter)) != std::string::npos){
	  line.erase(0,pos+delimiter.length());
	  cols++;
	}
	if(cols>max){
	  max=cols;
	}
	rows++;
      }
      cols=max;
    }
    myfile.close();
  }else{
    printf("Unable to open file.\n");
  }

  Names = std::vector<std::string>(rows);
  Matrix = Eigen::MatrixXd::Zero(rows,cols-2);
  myfile.open(filename);
  if(myfile.is_open()){
    while(getline(myfile,line)){
      if(line[0]!='#' && line!="\0"){
	RemoveSpaces(line);
	if(line.length()<delimiter.length()){
	}else{
	  if(line.substr(line.length()-delimiter.length(),line.length()) != delimiter){
	    line.append(delimiter);
	  }
	}
	if(line.find(delimiter) == 0){
	  line.erase(0,delimiter.length());
	}
	col=0;
	while( (pos=line.find(delimiter)) != std::string::npos){
	  number=line.substr(0,pos);
	  if(col==0){
	  } else if(col==1){
	    Names[row] = number;
	  } else{
	    Matrix(row,col-2) = std::stof( number );
	  }
	  line.erase(0,pos+delimiter.length());
	  col++;
	}
	row++;
      }
    }
    myfile.close();
  }else{
    printf("Unable to open file.\n");
  }
}
void LoadDataFile(std::string folder, std::string filename, std::string delimiter, int start, int finish, int column, Eigen::MatrixXd &Matrix){
  Eigen::MatrixXd matrix;
  char buffer[100];
  std::fstream fileOpen;
  std::string line,
    file;

  sprintf(buffer,"%s/run%04d/%s",folder.c_str(),start,filename.c_str());
  file=buffer;
  LoadFile(file,matrix,delimiter);

  int rows=matrix.rows(),
    cols=finish-start;
  Matrix=Eigen::MatrixXd::Zero(rows,cols);

  for(int i=0;i<cols;i++){
    sprintf(buffer,"%s/run%04d/%s",folder.c_str(),i+start,filename.c_str());
    file=buffer;
    LoadFile(file,matrix,delimiter);
    for(int j=0;j<rows;j++){
      Matrix(j,i) = matrix(j,column);
    }	
  }
}
void LoadDataFiles(std::string folder, std::vector<std::string> filenames, std::string delimiter, int start, int finish, int column, std::vector<Eigen::MatrixXd> &Matrix){
  int files=filenames.size();
  Matrix = std::vector<Eigen::MatrixXd> (files);
  for(int file=0;file<files;file++){
    LoadDataFile(folder, filenames[file], delimiter, start, finish, column, Matrix[file]);
  }
}
void WriteFile(std::string filename, Eigen::MatrixXd &Matrix,std::string delimiter){
  std::string line;
  int rows = Matrix.rows(),
    cols = Matrix.cols();
  std::fstream ofile(filename,std::ios::out);
  if(ofile.is_open()){
    for(int row=0;row<rows;row++){
      for(int col=0;col<cols;col++){
	ofile << Matrix(row,col) << delimiter;
      }
      ofile << "\n";
    }
    ofile.close();
  }else{
    printf("Unable to open %s.\n",filename.c_str());
  }  
}
void WriteParamFile(std::string fileName, std::vector<std::string> &header, std::string delimiter, Eigen::MatrixXd &file){
  int rows = file.rows();
  int cols = file.cols();
  std::fstream ofile(fileName,std::ios::out);
  if(ofile.is_open()){
    for(int i=0;i<cols;i++){
      ofile << header[i] << delimiter;
      for(int j=0;j<rows;j++){
	ofile << file(j,i) << delimiter;
      }
      ofile << '\n';
    }
    ofile.close();
  }else{
    printf("Unable to open %s.\n",fileName.c_str());
  }
}
void WriteParamFileLoop(std::string filename, std::string folder, int start,std::vector<std::string> &header, std::string delimiter, Eigen::MatrixXd &matrix){
  int rows = matrix.rows();
  int cols = matrix.cols();
  std::fstream ofile;
  char file[100];
  for(int row=0;row<rows;row++){
    sprintf(file,"%s/run%04d/%s",folder.c_str(),row+start,filename.c_str());
    ofile.open(file,std::ios::out);
    if(ofile.is_open()){
      for(int col=0;col<cols;col++){
	ofile << header[col] << delimiter << matrix(row,col) << delimiter << '\n';
      }
      ofile.close();
    }else{
      printf("Unable to open %s\n",file);
    }
  }
}
void WriteParameterFiles(std::string rangename, std::string foldername, std::string filename, std::string delimiter, int start, int finish, int ab){
  std::vector<std::string> Name;
  Eigen::MatrixXd range,matrix;
  
  LoadParamFile(rangename,Name,range,delimiter);
  LHCSampling(matrix,finish-start,ab,range);
  MkdirLoop(foldername,start,finish);
  WriteParamFileLoop(filename,foldername,start,Name,delimiter,matrix);
}
void WriteParameterFiles(std::string rangename, std::string foldername, std::string filename, std::string delimiter, int start, int finish, int ab, Eigen::MatrixXd &Parameters){
  std::vector<std::string> Name;
  Eigen::MatrixXd range;
  
  LoadParamFile(rangename,Name,range,delimiter);
  LHCSampling(Parameters,finish-start,ab,range);
  MkdirLoop(foldername,start,finish);
  WriteParamFileLoop(filename,foldername,start,Name,delimiter,Parameters);
}
void LHCSampling(Eigen::MatrixXd &hypercube, int samples, int ab, Eigen::MatrixXd range){
  int parameters = range.rows();
  int nmax = parameters/ab - 2;
  CCosh dist(nmax);
  Eigen::VectorXd G = Eigen::VectorXd::Zero(ab);
  std::vector<int> hyperlist;
  hypercube = Eigen::MatrixXd::Zero(samples,parameters);

  for(int i=0;i<samples;i++){
    hyperlist.push_back(i);
  }

  for(int i=0;i<parameters;i++){
    std::random_shuffle(hyperlist.begin(),hyperlist.end());
    for(int j=0;j<samples;j++){
      hypercube(j,i) = hyperlist[j];
    }
  }

  float init,final,dx;
  for(int i=0;i<parameters;i++){
    init = range(i,0);
    final = range(i,1);
    dx = (final-init)/(samples-1);
    for(int j=0;j<samples;j++){
      hypercube(j,i) = init + dx*hypercube(j,i);
    }
  }

  for(int i=0;i<samples;i++){
    for(int j=0;j<ab;j++){
      hypercube(i,j*(nmax+2)+1) = 1.0/hypercube(i,j*(nmax+2));
      for(int k=1;k<nmax+1;k++){
        hypercube(i,j*(nmax+2)+1) -= hypercube(i,j*(nmax+2)+k+1)*dist.Z(k);
      }
      hypercube(i,j*(nmax+2)+1) /= (dist.Z(0));
    }
  }
}
