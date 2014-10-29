#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct conf{
	int id;
	std::string ifile;
	std::string ofile;
};

void notice_error(std::string msg, bool do_exit){
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

//typedef void(solution::* task_handler_t)();
typedef void(*task_handler_t)();
// —в€зь номера задани€ и обработчика
task_handler_t id_funx_map[13] = {
	&(vect_size),
	&(vect_size),
	&(line_by2p)
};

//task_handler_t* task_handler = id_funx_map;
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
	//TODO: —оздать методы разбора и пол€ дл€ сохранение€ структур данных, соответствующие описанию ниже.
	/*
	1)	Ќабор чисел через пробел
	2)	1-€ строка: N
		2-€ строка: N чисел через пробел
		3-€ строка: N чисел через пробел
	3)	1-€ строка: N
		2-€ строка: N пар чисел через пробел
	4)	1-€ строка: N
		2-€ строка: 2 числа через пробел
		...
		N-€ строка: 2 числа через пробел
	5)	1-€ строка: N
		2-€ строка: 6 чисел через пробел
		3-€ строка: 2 числа через пробел
		...
		(2N-1)-€ строка: 6 чисел через пробел
		(2N)-€   строка: 2 числа через пробел
	6)	

	*/
};

///////////////////////////////
// TASK class IMPLEMENTATION //
///////////////////////////////

task::task(const conf& cfg){
	id = cfg.id;
	//TODO: —оздавать входной и выходной потоки
	task_handler = id_funx_map;
	(*task_handler[id])();
}

task::~task(){

}