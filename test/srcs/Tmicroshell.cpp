/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tmicroshell.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:04:49 by frthierr          #+#    #+#             */
/*   Updated: 2021/03/29 15:11:39 by frthierr         ###   ########.fr       */
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



class	TMicroshell: public ::testing::Test {
	public:
		TMicroshell() {}
	protected:
		t_command_handler	current;
		char			**args;
		virtual void	SetUp() {
			args = NULL;
		}

		virtual void	TearDown() {
			if (args)
				free_args();
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
		inline void		expect_vals(const int x, const int y, const int z) {
			EXPECT_EQ(x, current.begin);
			EXPECT_EQ(y, current.next_pipe);
			EXPECT_EQ(z, current.next_sep);
		}
				
};

TEST_F(TMicroshell, current_init) {
	vector<string>	init_args({"cd"});
	set_args(init_args);
	INIT_COMMAND_HANDLER(current, (const char**)args, environ);
	find_next(&current);
	expect_vals(0, NOT_SET, NOT_SET);
}


