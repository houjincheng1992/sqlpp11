/*
 * Copyright (c) 2015-2015, Roland Bock
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

#ifndef SQLPP_DAY_POINT_PARAMETER_TYPE_H
#define SQLPP_DAY_POINT_PARAMETER_TYPE_H

#include <sqlpp11/data_types/parameter_value.h>
#include <sqlpp11/data_types/day_point/data_type.h>
#include <sqlpp11/data_types/day_point/wrap_operand.h>
#include <sqlpp11/data_types/day_point/operand.h>
#include <sqlpp11/tvin.h>

namespace sqlpp
{
  template <>
  struct parameter_value_t<day_point>
  {
    using _value_type = day_point;
    using _cpp_value_type = typename _value_type::_cpp_value_type;

    parameter_value_t() : _value{}, _is_null(true)
    {
    }

    explicit parameter_value_t(const _cpp_value_type& val) : _value(val), _is_null(false)
    {
    }

    parameter_value_t& operator=(const _cpp_value_type& val)
    {
      _value = val;
      _is_null = false;
      return *this;
    }

    parameter_value_t& operator=(const tvin_t<wrap_operand_t<_cpp_value_type>>& t)
    {
      if (t._is_trivial())
      {
        _value = _cpp_value_type{};
        _is_null = true;
      }
      else
      {
        _value = t._value._t;
        _is_null = false;
      }
      return *this;
    }

    void set_null()
    {
      _value = _cpp_value_type{};
      _is_null = true;
    }

    bool is_null() const
    {
      return _is_null;
    }

    const _cpp_value_type& value() const
    {
      return _value;
    }

    operator _cpp_value_type() const
    {
      return _value;
    }

    template <typename Target>
    void _bind(Target& target, size_t index) const
    {
      target._bind_date_parameter(index, &_value, _is_null);
    }

  private:
    _cpp_value_type _value;
    bool _is_null;
  };
}
#endif
