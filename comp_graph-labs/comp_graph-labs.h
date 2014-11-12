//TODO: обработка ошибок
#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

const std::string DATA_STRUCT_ERR_TMPL = "Data structure error: %s\n";
const std::string BAD_IFSTREAM = "Bad input stream provided\n";
const std::string BAD_OFSTREAM = "Bad output stream provided\n";

struct conf{
	int id;
	std::string ifile;
	std::string ofile;
};

void notice_error(std::string msg, bool do_exit = 0){
	std::cout << msg << std::endl;
	if (do_exit){
		exit(1);
	}
}

std::string input_file = "";
std::string output_file = "";

/////////////////////////////////////
// Класс-родитель для всех парсеров входных данных
class data_parser{
protected:
	std::ifstream ifs;
	FILE * ofh;
public:
	int counter;
	data_parser(std::string ipath,std::string opath);
	~data_parser();
	void parse(std::vector<float>& data);
	void put_data(char* format,...){
		va_list vargs;
		va_start(vargs,format);
		vfprintf(ofh,format,vargs);
		va_end(vargs);
	};
};

/////////////////////////////////////
// Обработчики заданий
void vect_size(){
	double size = 0;
	double curr = 0;
	data_parser parser(input_file,output_file);
	std::vector<float> data;
	parser.parse(data);
	for(std::vector<float>::iterator it = data.begin(); it != data.end(); ++it){
		curr = *it;
		size += pow(curr,2);
	}
	parser.put_data("%d",size);
}
void line_by2p(){
	printf("A line will soon be found!\n");
	data_parser parser(input_file,output_file);
	std::vector<float> data;
	parser.parse(data);
	std::cout << "--" << data.size() << std::endl;
}

void circle(){
	data_parser parser(input_file,output_file);
	std::vector<float> data;
	parser.parse(data);
	double radius = data[0];
	double diam = radius*2;
	double len = diam*M_PI;
	double sq = M_PI*(radius*radius);
	parser.put_data("%.3f, %.3f, %.3f, ", diam, len, sq);
}

void vect_sum(){
	data_parser parser(input_file,output_file);
	std::vector<float> data;
	parser.parse(data);
	int i = 0;
	int size = data[i++];
	for(i = 1; i <= size; i++){
		float p = data[i]+data[size+i];
		parser.put_data("%.3f ",p);
	}
}

void product(){
	data_parser parser(input_file,output_file);
	std::vector<float> data;
	parser.parse(data);
	int i = 0;
	int size = data[i++];
	for(i = 1; i <= size; i++){
		float p = data[i]*data[size+i];
		parser.put_data("%.3f ",p);
	}
}

void triangle(){
	data_parser parser(input_file,output_file);
	std::vector<float> data;
	parser.parse(data);
	int size = data[0];
	float p1 = data[1]+data[size+1];
	float p2 = data[2]+data[size+2];
	for(std::vector<float>::iterator it = data.begin(); it != data.end(); ++it){
	
	}
	parser.put_data("%d",1);
}

void twoc(){
	data_parser parser(input_file,output_file);
	std::vector<float> data;
	parser.parse(data);
	int size = data[0];
	float p1 = data[1]+data[size+1];
	float p2 = data[2]+data[size+2];
	for(std::vector<float>::iterator it = data.begin(); it != data.end(); ++it){
	
	}
	parser.put_data("%d",1);
}

void triangles(){
	data_parser parser(input_file,output_file);
	std::vector<float> data;
	parser.parse(data);
	int size = data[0];
	float p1 = data[1]+data[size+1];
	float p2 = data[2]+data[size+2];
	for(std::vector<float>::iterator it = data.begin(); it != data.end(); ++it){
	
	}
	parser.put_data("%d",1);
}

void maxdist(){
	data_parser parser(input_file,output_file);
	std::vector<float> data;
	parser.parse(data);
	int size = data[0];
	float p1 = data[1]+data[size+1];
	float p2 = data[2]+data[size+2];
	for(std::vector<float>::iterator it = data.begin(); it != data.end(); ++it){
	
	}
	parser.put_data("%d",1);
}

void trianglep(){
	data_parser parser(input_file,output_file);
	std::vector<float> data;
	parser.parse(data);
	int size = data[0];
	float p1 = data[1]+data[size+1];
	float p2 = data[2]+data[size+2];
	for(std::vector<float>::iterator it = data.begin(); it != data.end(); ++it){
	
	}
	parser.put_data("%d",1);
}

void pifagor(){
	data_parser parser(input_file,output_file);
	std::vector<float> data;
	parser.parse(data);
	int size = data[0];
	float p1 = data[1]+data[size+1];
	float p2 = data[2]+data[size+2];
	for(std::vector<float>::iterator it = data.begin(); it != data.end(); ++it){
	
	}
	parser.put_data("%d",1);
}

void pack(){
	data_parser parser(input_file,output_file);
	std::vector<float> data;
	parser.parse(data);
	int size = data[0];
	float p1 = data[1]+data[size+1];
	float p2 = data[2]+data[size+2];
	for(std::vector<float>::iterator it = data.begin(); it != data.end(); ++it){
	
	}
	parser.put_data("%d",1);
}

/////////////////////////////////////
// Связь номера задания и обработчика
// 1. Определяем тип указателя на обработчик
typedef void(*task_handler_t)();
// 2. Определяем массив указателей на обработчики вышеозначенного типа
task_handler_t id_funx_map[13] = {
	&(vect_size),
	&(vect_size),
	&(line_by2p),
	&(circle),
	&(vect_sum),
	&(product),
	&(twoc),
	&(triangles),
	&(maxdist),
	&(trianglep),
	&(vect_sum),
	&(pifagor),
	&(pack),
};
/////////////////////////////////////

/////////////////////////////////////
// Класс Задание
class task{
private:
	int id;
	task_handler_t* task_handler;
public:
	task(const conf& cfg);
	~task();
	void show_help();
	/*
	1)	Набор чисел через пробел
	2)	1-я строка: N (определяет кол-во чисел в следующих строках)
		2-я строка: N чисел через пробел
		3-я строка: N чисел через пробел
	3)	1-я строка: N (определяет кол-во чисел в следующих строках)
		2-я строка: 2N чисел через пробел
	4)	1-я строка: N (определяет количество последующих строк)
		2-я строка: 2 числа через пробел
		...
		N-я строка: 2 числа через пробел
	5)	1-я строка: N (определяет количество последующих строк x2)
		2-я строка: 6 чисел через пробел
		3-я строка: 2 числа через пробел
		...
		(2N-1)-я строка: 6 чисел через пробел
		(2N)-я   строка: 2 числа через пробел
	*/
};
/////////////////////////////////////

///////////////////////////////
// TASK class IMPLEMENTATION //
///////////////////////////////

task::task(const conf& cfg){
	id = cfg.id;
	task_handler = id_funx_map;
	(*task_handler[id])();
}

task::~task(){
	printf("\nTask #%d complete\n", id);
}

//////////////////////////////////////
// DATA_PARSER class IMPLEMENTATION //
//////////////////////////////////////

data_parser::data_parser(std::string ipath,std::string opath): ifs(ipath.c_str()){
	if (!ifs){
		notice_error(BAD_IFSTREAM,1);
	}
	ofh = fopen(opath.c_str(),"a+");
	if (!ofh){
		notice_error(BAD_OFSTREAM,1);
	}
}

data_parser::~data_parser(){
	if(ifs) ifs.close();
	if(ofh) fclose(ofh);
};

void data_parser::parse(std::vector<float>& data){
	if (ifs && !ifs.eof()){
		int i = 0;
		float val = 0;
		while (!ifs.eof()){
			ifs >> val;
			//std::cout << "Value : \"" << val << "\"" << std::endl;
			data.push_back(val);
		}
		for (std::vector<float>::iterator it = data.begin(); it != data.end(); ++it){
			std::cout << *it << std::endl;
		}
	} else {
		notice_error(BAD_IFSTREAM,1);
	}
}