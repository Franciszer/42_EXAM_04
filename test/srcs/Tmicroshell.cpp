/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tmicroshell.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:04:49 by frthierr          #+#    #+#             */
/*   Updated: 2021/03/31 13:08:19 by frthierr         ###   ########.fr       */
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
extern char	**environ;

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
				delete [] args[i];
			delete [] args;
		}
		void			set_args(vector<string> &v) {
			args = new char*[v.size() + 1];
			args[v.size()] = NULL;
			for (pair<size_t, vector<string>::const_iterator> p(0, v.begin()) ;\
				p.second != v.end() ; p.first++, p.second++) {
					args[p.first] = new char[p.second->size() + 1];
					args[p.first][p.second->size()] = '\0';
					args[p.first] = strcpy(args[p.first], p.second->c_str());
				}
		}
		inline void		eq_command_handler(const int begin, const int next_pipe,\
			const int next_sep, const int end_args) {
			EXPECT_EQ(begin, current.begin);
			EXPECT_EQ(next_pipe, current.next_pipe);
			EXPECT_EQ(next_sep, current.next_sep);
			EXPECT_EQ(end_args, current.end_args);
		}
		static inline void	print_command_handler(t_command_handler &current) {
			std::cout << "begin: " << current.begin << std::endl;
			std::cout << "next_pipe: " << current.next_pipe << std::endl;
			std::cout << "next_sep: " << current.next_sep << std::endl;
			std::cout << "end_args: " << current.end_args << std::endl;
		}
				
};

TEST_F(TMicroshell, find_next) {
	
	INIT_ARGS({"cd"});
	INIT_COMMAND_HANDLER(current, (const char**)args, environ);
	find_next(&current);
	eq_command_handler(0, NOT_SET, NOT_SET, 1);
	TearDown();
	
	INIT_ARGS("cd", ";", "ls", "|", "pwd");
	INIT_COMMAND_HANDLER(current, (const char**)args, environ);
	EXPECT_TRUE(find_next(&current));
	eq_command_handler(0, NOT_SET, 1, 1);
	EXPECT_TRUE(find_next(&current));
	eq_command_handler(2, 3, NOT_SET, 3);
	EXPECT_TRUE(find_next(&current));
	eq_command_handler(4, NOT_SET, NOT_SET, 5);
	EXPECT_FALSE(find_next(&current));
}

TEST_F(TMicroshell, copy_args) {
	INIT_ARGS("/bin/ls", "hello", "world");
	INIT_COMMAND_HANDLER(current, (const char**)args, environ);
	find_next(&current);

	size_t	test_size = 0;
	for (size_t i = 0; args[i]; i++)
		test_size++;
	ASSERT_EQ(0, current.begin);
	ASSERT_EQ(3, current.end_args);
	EXPECT_EQ(3, test_size);
	EXPECT_EQ(string(args[0]), "/bin/ls");
	EXPECT_EQ(string(args[1]), "hello");
	EXPECT_EQ(string(args[2]), "world");	
}
