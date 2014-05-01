/*
 * Copyright (c) 2013-2014, Roland Bock
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 *   Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 *   Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SQLPP_DETAIL_LOGIC_H
#define SQLPP_DETAIL_LOGIC_H

#include <type_traits>

namespace sqlpp
{
	namespace detail
	{
		template<bool... b>
			struct all_helper;

		template<template<typename> class Predicate, typename... T>
			using all_t = std::is_same<all_helper<Predicate<T>::value...>, all_helper<(true or Predicate<T>::value)...>>;

		template<template<typename> class Predicate, typename... T>
			using any_t = typename std::conditional<std::is_same<all_helper<Predicate<T>::value...>, all_helper<(false and Predicate<T>::value)...>>::value,
						std::false_type,
						std::true_type
							>::type;

		template<bool>
			struct not_impl;

		template<> 
			struct not_impl<true>
		{
			using type = std::false_type;
		};

		template<> 
			struct not_impl<false>
		{
			using type = std::true_type;
		};


		template<template<typename> class Predicate, typename... T>
			using not_t = typename not_impl<Predicate<T>::value...>::type;


		template<typename T>
			using identity_t = T;
	}
}


#endif
