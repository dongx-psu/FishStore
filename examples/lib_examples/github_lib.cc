// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#include <cstdio>
#include <iostream>
#include <vector>
#ifdef _WIN32
#define LIBEXPORT_MACROS extern "C" __declspec(dllexport)
#else
#define LIBEXPORT_MACROS extern "C"
#endif
#include "core/psf.h"
#include "simdjson_adaptor.h"

typedef fishstore::adaptor::SIMDJsonAdaptor adaptor_t;
using namespace fishstore::core;

LIBEXPORT_MACROS NullableInt cpp_pr(const std::vector<adaptor_t::field_t>& fields) {
  auto type = fields[0].GetAsStringRef();
  auto language = fields[1].GetAsStringRef();
  if(type.HasValue() && strcmp("PullRequestEvent", type.Value().Data()) == 0 &&
     language.HasValue() && strcmp("C++", language.Value().Data()) == 0)
    return NullableInt{false, 1};
  else
    return NullableInt{true, 0};
}

LIBEXPORT_MACROS NullableInt opened_issue(const std::vector<adaptor_t::field_t>& fields) {
  auto type = fields[0].GetAsStringRef();
  auto payload_action = fields[1].GetAsStringRef();
  if(type.HasValue() && strcmp("IssuesEvent", type.Value().Data()) == 0 &&
      payload_action.HasValue() && strcmp("opened", payload_action.Value().Data()) == 0) {
    return NullableInt{false, 1};
  } else
    return NullableInt{true, 0};
}

LIBEXPORT_MACROS NullableInt int_projection(const std::vector<adaptor_t::field_t>& fields) {
  auto ref = fields[0].GetAsInt();
  if (ref.HasValue()) {
    return NullableInt{ false, ref.Value() };
  }
  else {
    return NullableInt{ true, 0 };
  }
}