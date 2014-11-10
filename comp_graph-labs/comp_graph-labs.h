
// TODO: ќпределить все парсеры.
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

// ќбработчики заданий
void vect_size(){
	printf("Vector size will soon be found!\n");
}
void line_by2p(){
	printf("A line will soon be found!\n");
}

/////////////////////////////////////
// —в€зь номера задани€ и обработчика
// 1. ќпредел€ем тип указател€ на обработчик
typedef void(*task_handler_t)();
// 2. ќпредел€ем массив указателей на обработчики вышеозначенного типа
task_handler_t id_funx_map[13] = {
	&(vect_size),
	&(vect_size),
	&(line_by2p)
};
/////////////////////////////////////

/////////////////////////////////////
//  ласс-родитель дл€ всех парсеров входных данных
class data_parser{
protected:
	std::ifstream ifs;
public:
	int counter;
	data_parser(std::ifstream str);
	~data_parser();
	int* parse(int data[]);
};
class data_parser_2lines : public data_parser{};
class data_parser_3lines : public data_parser{};
class data_parser_N_sim_lines : public data_parser{};
class data_parser_2N_lines : public data_parser{};
/////////////////////////////////////

/////////////////////////////////////
//  ласс «адание
class task{
private:
	int id;
	task_handler_t* task_handler;
	std::ifstream ifs;
	std::ofstream ofs;
public:
	task(const conf& cfg);
	~task();
	void show_help();
	/*
	1)	Ќабор чисел через пробел
	2)	1-€ строка: N (определ€ет кол-во чисел в следующих строках)
		2-€ строка: N чисел через пробел
		3-€ строка: N чисел через пробел
	3)	1-€ строка: N (определ€ет кол-во чисел в следующих строках)
		2-€ строка: 2N чисел через пробел
	4)	1-€ строка: N (определ€ет количество последующих строк)
		2-€ строка: 2 числа через пробел
		...
		N-€ строка: 2 числа через пробел
	5)	1-€ строка: N (определ€ет количество последующих строк x2)
		2-€ строка: 6 чисел через пробел
		3-€ строка: 2 числа через пробел
		...
		(2N-1)-€ строка: 6 чисел через пробел
		(2N)-€   строка: 2 числа через пробел
	*/
};
/////////////////////////////////////

///////////////////////////////
// TASK class IMPLEMENTATION //
///////////////////////////////

task::task(const conf& cfg):ifs(cfg.ifile.c_str()), ofs(cfg.ofile.c_str()){
	id = cfg.id;
	task_handler = id_funx_map;
	(*task_handler[id])();
}

task::~task(){

}

//////////////////////////////////////
// DATA_PARSER class IMPLEMENTATION //
//////////////////////////////////////

data_parser::data_parser(std::ifstream str): ifs(str){}

data_parser::parse(int data[]){
	if (ifs && !ifs.eof()){
		//std::string counter;
		ifs >> counter;
		int i = 0;
		while (!ifs.eof()){
			ifs >> data[i];
			i++;
		}
	} else {
		notice_error(BAD_IFSTREAM,1);
	}
}
