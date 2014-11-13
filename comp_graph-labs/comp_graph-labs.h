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
void line(){
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
	int width = (int)data[0];
	int height = (int)data[1];
	
	parser.put_data("%d",1);
}

void twoc(){
	data_parser parser(input_file,output_file);
	std::vector<float> data;
	parser.parse(data);
	
	float x1 = data[0];
	float y1 = data[1];
	float x2 = data[2];
	float y2 = data[3];
	float r1 = data[4];
	float r2 = data[5];
	std::string msg = "";
	// расстояние между центрами окр-тей
	float d = sqrt(pow((x1-x2),2) + pow((y1-y2),2));
	if( d == (r1+r2) ){
		msg = "Tangent: output";
	} else if (d > (r1+r2)) {
		msg = "Too far";
	} else {//if (d < (r1+r2) ) {
		if(d < abs(r1-r2) ) {
			if (r1 > r2) {
				msg = "2 inside 1";
			} else if (r1 < r2) {
				msg = "1 inside 2";
			}
		} else if (d > abs(r1 - r2) ) {
			msg = "Intersect";
		} else {
			if (r1 > r2) {
				msg = "Tangent: 2 in 1";
			} else if (r1 < r2) {
				msg = "Tangent: 2 in 1";
			} else {
				msg = "Full congruence";
			}
		}
	}
	printf("%s\n",msg.c_str());
	parser.put_data("%s",msg.c_str());
}

void triangles(){
	// вспомогательная структура для фиксирования нужных данных
	struct triangle_min{
		float perimeter;
		int point1;
		int point2;
		int point3;
	};
	triangle_min tm;

	data_parser parser(input_file,output_file);
	std::vector<float> data;
	parser.parse(data);
	
	int points_c = data[0]; // количество точек
	// квадратная симметричная матрица, где на главной диагонали указаны номера точек, 
	// расстояние до которых (и от которых) минимально для текущей точки
	float **lengths = new float*[points_c];
	//
	bool found_points = false;
	int p1,p2,p3;
	float perimeter_temp;
	// инициализируем мин.длину реальным значением
	float min_len = sqrt(pow((data[1] - data[3]), 2) + pow( (data[2] - data[4]), 2));
	for(int i = 1; i < points_c; i++){
		p1 = i-1;
		while(found_points){
			// по выходе из цикла имеем минимальное расстояние от текущей точки и номер второй точки
			for(int j = 1; j < points_c; j++){
				if( (data[i] != data[j]) &&  (data[i+1] != data[j+1])){
					float len = sqrt(pow((data[i] - data[j]), 2) + pow( (data[i+1] - data[j+1]), 2));
					lengths[i-1][j-1] = lengths[j-1][i-1] = len;
					if (min_len > len){
						min_len = len;
						lengths[i-1][i-1] = j;
					}
				}
			}
			p2 = lengths[i-1][i-1];
			i = lengths[i-1][i-1];
			// по выходе из цикла имеем минимальное расстояние от второй точки и номер третьей точки
			for(int j = 1; j < points_c; j++){
				if( (data[i] != data[j]) &&  (data[i+1] != data[j+1])){
					float len = sqrt(pow((data[i] - data[j]), 2) + pow( (data[i+1] - data[j+1]), 2));
					lengths[i-1][j-1] = lengths[j-1][i-1] = len;
					if (min_len < len){
						min_len = len;
						lengths[i-1][i-1] = j;
					}
				}
			}
			p3 = lengths[i-1][i-1];
			perimeter_temp = lengths[p1][(int)lengths[p1][p1]] + lengths[p2][(int)lengths[p2][p2]] + lengths[p3][p1];
			found_points = true;
		}
		if (perimeter_temp < tm.perimeter){
			tm.perimeter = perimeter_temp;
			tm.point1 = p1+1;
			tm.point2 = p2+1;
			tm.point3 = p3+1;
		}
		i+=2;
	}
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
	&(vect_size), //0
	&(vect_size), // 1
	&(line),      // 2
	&(circle),    // 3
	&(vect_sum),  // 4
	&(product),   // 5
	&(triangle),  // 6
	&(twoc),      // 7
	&(triangles), // 8
	&(maxdist),   // 9
	&(trianglep), // 10
	&(pifagor),   // 11
	&(pack),      // 12
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