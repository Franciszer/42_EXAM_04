/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tmicroshell.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:04:49 by frthierr          #+#    #+#             */
/*   Updated: 2021/03/29 15:58:50 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <cstdlib>
#include <vector>
#include <string.h>
#include <string>

extern "C" {
	#include "microshell.h"
}

using 				std::vector;
using				std::string;
using				std::pair;
extern const char	**environ;

# define INIT_ARGS(init_list...)\
	vargs.assign({init_list});\
	set_args(vargs);

class	TMicroshell: public ::testing::Test {
	public:
		TMicroshell() {}
	protected:
		t_command_handler	current;
		char				**args;

		vector<string>	vargs;
		virtual void	SetUp() {
			args = NULL;
		}

		virtual void	TearDown() {
			if (args)
				free_args();
			args = NULL;
		}
		void			free_args() {
			for (int i = 0 ; args[i] ; i++)
				delete args[i];
			delete [] args;
		}
		void			set_args(vector<string> &v) {
			args = new char*[v.size() + 1];
			args[v.size()] = NULL;
			for (pair<size_t, vector<string>::const_iterator> p(0, v.begin()) ;\
				p.second != v.end() ; p.second++) {
					args[p.first] = new char[p.second->size()];
					args[p.first] = strcpy(args[p.first], p.second->c_str());
				}
		}
		inline void		eq_command_handler(const int begin, const int next_pipe,\
			const int next_sep) {
			EXPECT_EQ(begin, current.begin);
			EXPECT_EQ(next_pipe, current.next_pipe);
			EXPECT_EQ(next_sep, current.next_sep);
		}
				
};

TEST_F(TMicroshell, find_next) {
	
	INIT_ARGS({"cd"});
	INIT_COMMAND_HANDLER(current, (const char**)args, environ);
	find_next(&current);
	eq_command_handler(0, NOT_SET, NOT_SET);
	TearDown();
	
	INIT_ARGS("cd", ";", "ls", "|", "pwd");
	INIT_COMMAND_HANDLER(current, (const char**)args, environ);
	std::cout << "BEFORE" << std::endl;
	find_next(&current);
	std::cout << "AFTER" << std::endl;
	eq_command_handler(0, NOT_SET, 1);
}

