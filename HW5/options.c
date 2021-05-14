#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <immintrin.h>
#include <stdbool.h>
#include "./options.h"


void optionProcess(int argc, char **argv, struct opts* opts)
{
	opts->valid = false;
	opts->block = -1;
	int opt;

  	while ((opt = getopt(argc, argv, "o:i:")) != -1) 
  	{
    	switch(opt) 
    	{
      	case 'i':
			if (strcmp("rdrand", optarg) == 0)
			{
				opts->input = RDRAND;
			}
			else if (strcmp("mrand48_r", optarg) == 0)
			{
				opts->input = MRAND48_R;
			}
			else if ('/' == optarg[0]) 
			{         
			  opts->input = SLASH_F;
			  opts->r_src = optarg;  
			}
			else
			{
			  fprintf(stderr, "Invalid operand for option \n");
			  break;
			}
			opts->valid = true;
			break;
		  case 'o':
			if(strcmp("stdio", optarg) == 0) 
			{
				opts->output = STDIO;
			}
			else 
			{
				opts->output = N;
				opts->block = atoi(optarg);
			}
			opts->valid = true;
			break;

		  case ':':       /* -i or -o without operand */
			  fprintf(stderr,
			  	"Option -%c requires an operand\n", optopt);
			  break;
		  case '?':
			  fprintf(stderr,
                "Unrecognized option: '-%c'\n", optopt);
			  break;
		}
	  }

	  if (optind >= argc)
		return;
	
	  /*char *endptr;
	  errno = 0;
	  opts->nbytes = strtoll (argv[optind], &endptr, 10);
	  if (errno) { 
		perror (argv[optind]);
		return false;
	  }

	  return !*endptr && 0 <= opts->nbytes;*/
	  opts->nbytes = atol(argv[optind]);
	  if(opts->nbytes >= 0) {
    	opts->valid = true;
    	}

	}