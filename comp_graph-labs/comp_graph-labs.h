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

// Класс Решение
class solution{
private:
	std::ifstream ifs;
	std::ofstream ofs;
public:
	solution(const std::string ifile,const std::string ofile);
	~solution();
	void parse_input();
	// task-specific methods
	void vect_size();
	void line_by2p();
	//TODO: изучить все типы входных структур. Создать соответствующие методы разбора и поля для сохранениея этих структур.
};

typedef void(solution::* task_handler)();

// Связь номера задания и обработчика
task_handler id_funx_map[12] = {
	&(solution::vect_size),
	&(solution::line_by2p)
};
// Класс Задание
class task{
private:
	int id;
public:
	task(const conf& cfg);
	~task();
	void show_help();
	void resolve();
};

///////////////////////////////////
// SOLUTION class IMPLEMENTATION //
///////////////////////////////////

solution::solution(const std::string ifile,const std::string ofile){
	//ifs = std::ifstream(ifile.c_str());
	//ofs = std::ofstream(ofile.c_str());
}

solution::~solution(){
	
}


void solution::vect_size(){
	
}


void solution::line_by2p(){
	
}

///////////////////////////////
// TASK class IMPLEMENTATION //
///////////////////////////////

task::task(const conf& cfg){
	id = cfg.id;
	solution active_sol(cfg.ifile,cfg.ofile);
}

void task::resolve(){
	id_funx_map[id];
}

task::~task(){

}