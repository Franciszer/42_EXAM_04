/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tmicroshell.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:04:49 by frthierr          #+#    #+#             */
/*   Updated: 2021/03/04 11:44:45 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "microshell.h"

TEST(FIRST_TEST, FUNC) {
	EXPECT_EQ(ret1(), 1);
}

TEST(FIRST_TEST, TEST_TRUE) {
	EXPECT_TRUE(true);
}

// class	VectorTests: public ::testing::Test {
// 	public:
// 		VectorTests() {}
// 	protected:
// 			ft::vector<std::string>		ft_vec;
// 			std::vector<std::string>	std_vec;
// 			int i = 0;
// 			int j = 0;
// 		virtual void	SetUp() {

// 		}

// 		virtual void	TearDown() {
// 			ft_vec.clear();
// 			std_vec.clear();
// 		}
// };

// TEST_F(VectorTests, VTEST_SIZE) {
// 	ft_vec.push_back("hello world");
// 	std_vec.push_back("hello world");
// 	EXPECT_EQ(ft_vec.size(), std_vec.size());
// }

// TEST_F(VectorTests, VTEST_TRUE) {
// 	EXPECT_TRUE(true);
// }
