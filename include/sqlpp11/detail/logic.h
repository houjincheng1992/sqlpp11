/*
 * Copyright (c) 2013, Roland Bock
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
			struct all_impl;

		template<>
			struct all_impl<>
			{
				static constexpr bool value = true;
			};

		template<bool... Rest>
			struct all_impl<true, Rest...>
			{
				static constexpr bool value = all_impl<Rest...>::value;
			};

		template<bool... Rest>
			struct all_impl<false, Rest...>
			{
				static constexpr bool value = false;
			};

		template<template<typename> class Predicate, typename... T>
			using all_t = all_impl<Predicate<T>::value...>;

		template<bool... b>
			struct any_impl;

		template<>
			struct any_impl<>
			{
				static constexpr bool value = false;
			};

		template<bool... Rest>
			struct any_impl<false, Rest...>
			{
				static constexpr bool value = any_impl<Rest...>::value;
			};

		template<bool... Rest>
			struct any_impl<true, Rest...>
			{
				static constexpr bool value = true;
			};

		template<template<typename> class Predicate, typename... T>
			using any_t = any_impl<Predicate<T>::value...>;

	}
}


#endif