#include "comp_graph-labs.h"
#include "getopt.h"

///////////////////////////////////////////////////////
const std::string WRONG_TASK_NUM = "Wrong task number.";
const std::string IFILE_NOT_SET  = "Input file is not set.";
const std::string OFILE_NOT_SET  = "Output file is not set.";
///////////////////////////////////////////////////////


const struct option longopts[] =
	{
		{"task",	required_argument,		0, 't'},
		{"help",	optional_argument,		0, 'h'},
		{"ifile",	required_argument,		0, 'i'},
		{"ofile",	required_argument,		0, 'o'},
		{0,0,0,0},
	};

bool check_consist(const conf& ts){
	int sum = 0;
	if (ts.id){
		sum++;
	} else {
		notice_error(WRONG_TASK_NUM,0);
	}
	if (ts.ifile.length() > 0){
		sum++;
	} else {
		notice_error(IFILE_NOT_SET,0);
	}
	if (ts.ofile.length() > 0){
		sum++;
	} else {
		notice_error(OFILE_NOT_SET,0);
	}
	return !(sum%3);
}

void main(int argc, char* argv[])
{
	int opt = 0;
	int option_index;
	conf cfg;
	while( (opt = getopt_long(argc,argv,"t:h::i:o:",longopts,&option_index)) != -1){
		switch(opt){
			case 't':
				cfg.id = atoi(optarg);
				if (cfg.id < 0 || cfg.id > 11) {
					notice_error(WRONG_TASK_NUM,true);
				}
				break;
			case 'h':

				break;
			case 'i':
				if (optarg) {
					cfg.ifile = optarg;
				}
				break;
			case 'o':
				if (optarg) {
					cfg.ofile = optarg;
				}
				break;
		}
	}
	if (check_consist(cfg)){
		task active_task(cfg);
	}
	
}

