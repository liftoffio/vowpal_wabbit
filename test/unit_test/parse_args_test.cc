// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#include "parse_args.h"

#include "memory.h"
#include "vw/config/options_cli.h"

#include <boost/mpl/vector.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>
#include <string>
#include <vector>

using namespace VW::config;

using option_types = boost::mpl::vector<options_cli>;

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_from_header_strings_no_opts_skip, T, option_types)
{
  const std::vector<std::string> strings;
  auto opts = VW::make_unique<options_cli>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, true, *opts, is_ccb_model);

  int int_opt = -1;
  bool bool_opt;

  option_group_definition arg_group("");
  arg_group.add(make_option("int_opt", int_opt));

  arg_group.add(make_option("bool_opt", bool_opt));

  BOOST_CHECK_NO_THROW(opts->add_and_parse(arg_group));

  BOOST_CHECK_EQUAL(2, opts->get_all_options().size());

  BOOST_CHECK_EQUAL(false, opts->was_supplied("int_opt"));
  BOOST_CHECK_EQUAL(-1, int_opt);
  BOOST_CHECK_EQUAL(false, opts->was_supplied("bool_opt"));
  BOOST_CHECK_EQUAL(false, bool_opt);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_from_header_strings_no_opts_noskip, T, option_types)
{
  const std::vector<std::string> strings;
  auto opts = VW::make_unique<options_cli>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, false, *opts, is_ccb_model);

  int int_opt = -1;
  bool bool_opt;

  option_group_definition arg_group("");
  arg_group.add(make_option("int_opt", int_opt));

  arg_group.add(make_option("bool_opt", bool_opt));

  BOOST_CHECK_NO_THROW(opts->add_and_parse(arg_group));

  BOOST_CHECK_EQUAL(2, opts->get_all_options().size());

  BOOST_CHECK_EQUAL(false, opts->was_supplied("int_opt"));
  BOOST_CHECK_EQUAL(-1, int_opt);
  BOOST_CHECK_EQUAL(false, opts->was_supplied("bool_opt"));
  BOOST_CHECK_EQUAL(false, bool_opt);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_from_header_strings_bool_opt_skip, T, option_types)
{
  const std::vector<std::string> strings{"--bool_opt"};
  auto opts = VW::make_unique<T>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, true, *opts, is_ccb_model);

  int int_opt = -1;
  bool bool_opt;

  option_group_definition arg_group("");
  arg_group.add(make_option("int_opt", int_opt));

  arg_group.add(make_option("bool_opt", bool_opt));

  BOOST_CHECK_NO_THROW(opts->add_and_parse(arg_group));

  BOOST_CHECK_EQUAL(2, opts->get_all_options().size());

  BOOST_CHECK_EQUAL(false, opts->was_supplied("some_opt"));
  BOOST_CHECK_EQUAL(-1, int_opt);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt"));
  BOOST_CHECK_EQUAL(true, bool_opt);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_from_header_strings_bool_opt_noskip, T, option_types)
{
  const std::vector<std::string> strings{"--bool_opt"};
  auto opts = VW::make_unique<T>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, false, *opts, is_ccb_model);

  int int_opt = -1;
  bool bool_opt;

  option_group_definition arg_group("");
  arg_group.add(make_option("int_opt", int_opt));

  arg_group.add(make_option("bool_opt", bool_opt));

  BOOST_CHECK_NO_THROW(opts->add_and_parse(arg_group));

  BOOST_CHECK_EQUAL(false, opts->was_supplied("int_opt"));
  BOOST_CHECK_EQUAL(-1, int_opt);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt"));
  BOOST_CHECK_EQUAL(true, bool_opt);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_from_header_strings_int_opt_skip, T, option_types)
{
  const std::vector<std::string> strings{"--int_opt", "3"};
  auto opts = VW::make_unique<T>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, true, *opts, is_ccb_model);

  int int_opt = -1;
  bool bool_opt;

  option_group_definition arg_group("");
  arg_group.add(make_option("int_opt", int_opt));

  arg_group.add(make_option("bool_opt", bool_opt));

  BOOST_CHECK_NO_THROW(opts->add_and_parse(arg_group));

  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt"));
  BOOST_CHECK_EQUAL(3, int_opt);
  BOOST_CHECK_EQUAL(false, opts->was_supplied("bool_opt"));
  BOOST_CHECK_EQUAL(false, bool_opt);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_from_header_strings_int_opt_noskip, T, option_types)
{
  const std::vector<std::string> strings{"--int_opt", "3"};
  auto opts = VW::make_unique<T>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, false, *opts, is_ccb_model);

  int int_opt = -1;
  bool bool_opt;

  option_group_definition arg_group("");
  arg_group.add(make_option("int_opt", int_opt));

  arg_group.add(make_option("bool_opt", bool_opt));

  BOOST_CHECK_NO_THROW(opts->add_and_parse(arg_group));

  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt"));
  BOOST_CHECK_EQUAL(3, int_opt);
  BOOST_CHECK_EQUAL(false, opts->was_supplied("bool_opt"));
  BOOST_CHECK_EQUAL(false, bool_opt);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_from_header_strings_bool_int_opt_skip, T, option_types)
{
  const std::vector<std::string> strings{"--bool_opt", "--int_opt", "3"};
  auto opts = VW::make_unique<T>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, true, *opts, is_ccb_model);

  int int_opt = -1;
  bool bool_opt;

  option_group_definition arg_group("");
  arg_group.add(make_option("int_opt", int_opt));

  arg_group.add(make_option("bool_opt", bool_opt));

  BOOST_CHECK_NO_THROW(opts->add_and_parse(arg_group));

  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt"));
  BOOST_CHECK_EQUAL(3, int_opt);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt"));
  BOOST_CHECK_EQUAL(true, bool_opt);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_from_header_strings_bool_int_opt_noskip, T, option_types)
{
  const std::vector<std::string> strings{"--bool_opt", "--int_opt", "3"};
  auto opts = VW::make_unique<T>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, false, *opts, is_ccb_model);

  int int_opt = -1;
  bool bool_opt;

  option_group_definition arg_group("");
  arg_group.add(make_option("int_opt", int_opt));

  arg_group.add(make_option("bool_opt", bool_opt));

  BOOST_CHECK_NO_THROW(opts->add_and_parse(arg_group));

  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt"));
  BOOST_CHECK_EQUAL(3, int_opt);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt"));
  BOOST_CHECK_EQUAL(true, bool_opt);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_from_header_strings_int_bool_opt_skip, T, option_types)
{
  const std::vector<std::string> strings{"--int_opt", "3", "--bool_opt"};
  auto opts = VW::make_unique<T>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, true, *opts, is_ccb_model);

  int int_opt = -1;
  bool bool_opt;

  option_group_definition arg_group("");
  arg_group.add(make_option("int_opt", int_opt));

  arg_group.add(make_option("bool_opt", bool_opt));

  BOOST_CHECK_NO_THROW(opts->add_and_parse(arg_group));

  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt"));
  BOOST_CHECK_EQUAL(3, int_opt);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt"));
  BOOST_CHECK_EQUAL(true, bool_opt);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_from_header_strings_int_bool_opt_noskip, T, option_types)
{
  const std::vector<std::string> strings{"--int_opt", "3", "--bool_opt"};
  auto opts = VW::make_unique<T>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, false, *opts, is_ccb_model);

  int int_opt = -1;
  bool bool_opt;

  option_group_definition arg_group("");
  arg_group.add(make_option("int_opt", int_opt));

  arg_group.add(make_option("bool_opt", bool_opt));

  BOOST_CHECK_NO_THROW(opts->add_and_parse(arg_group));

  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt"));
  BOOST_CHECK_EQUAL(3, int_opt);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt"));
  BOOST_CHECK_EQUAL(true, bool_opt);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_from_header_strings_bool_int_interaction_bool_int_opt_skip, T, option_types)
{
  const std::vector<std::string> strings{
      "--bool_opt1", "--int_opt1", "3", "--interactions", "::", "--bool_opt2", "--int_opt2", "4"};
  auto opts = VW::make_unique<T>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, true, *opts, is_ccb_model);

  int int_opt1 = -1;
  bool bool_opt1;
  std::string interactions = "NONE";
  int int_opt2 = -1;
  bool bool_opt2;

  option_group_definition arg_group("");
  arg_group.add(make_option("int_opt1", int_opt1));
  arg_group.add(make_option("bool_opt1", bool_opt1));
  arg_group.add(make_option("interactions", interactions));
  arg_group.add(make_option("int_opt2", int_opt2));
  arg_group.add(make_option("bool_opt2", bool_opt2));

  BOOST_CHECK_NO_THROW(opts->add_and_parse(arg_group));

  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt1"));
  BOOST_CHECK_EQUAL(3, int_opt1);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt1"));
  BOOST_CHECK_EQUAL(true, bool_opt1);
  BOOST_CHECK_EQUAL(false, opts->was_supplied("interactions"));
  BOOST_CHECK_EQUAL("NONE", interactions);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt2"));
  BOOST_CHECK_EQUAL(4, int_opt2);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt2"));
  BOOST_CHECK_EQUAL(true, bool_opt2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_from_header_strings_bool_int_interaction_bool_int_opt_noskip, T, option_types)
{
  const std::vector<std::string> strings{
      "--bool_opt1", "--int_opt1", "3", "--interactions", "::", "--bool_opt2", "--int_opt2", "4"};
  auto opts = VW::make_unique<T>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, false, *opts, is_ccb_model);

  int int_opt1 = -1;
  bool bool_opt1;
  std::string interactions = "NONE";
  int int_opt2 = -1;
  bool bool_opt2;

  option_group_definition arg_group("");
  arg_group.add(make_option("int_opt1", int_opt1));
  arg_group.add(make_option("bool_opt1", bool_opt1));
  arg_group.add(make_option("interactions", interactions));
  arg_group.add(make_option("int_opt2", int_opt2));
  arg_group.add(make_option("bool_opt2", bool_opt2));

  BOOST_CHECK_NO_THROW(opts->add_and_parse(arg_group));

  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt1"));
  BOOST_CHECK_EQUAL(3, int_opt1);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt1"));
  BOOST_CHECK_EQUAL(true, bool_opt1);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("interactions"));
  BOOST_CHECK_EQUAL("::", interactions);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt2"));
  BOOST_CHECK_EQUAL(4, int_opt2);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt2"));
  BOOST_CHECK_EQUAL(true, bool_opt2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_from_header_strings_bool_int_interaction_int_bool_opt_skip, T, option_types)
{
  const std::vector<std::string> strings{
      "--bool_opt1", "--int_opt1", "3", "--interactions", "::", "--int_opt2", "4", "--bool_opt2"};
  auto opts = VW::make_unique<T>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, true, *opts, is_ccb_model);

  int int_opt1 = -1;
  bool bool_opt1;
  std::string interactions = "NONE";
  int int_opt2 = -1;
  bool bool_opt2;

  option_group_definition arg_group("");
  arg_group.add(make_option("int_opt1", int_opt1));
  arg_group.add(make_option("bool_opt1", bool_opt1));
  arg_group.add(make_option("interactions", interactions));
  arg_group.add(make_option("int_opt2", int_opt2));
  arg_group.add(make_option("bool_opt2", bool_opt2));

  BOOST_CHECK_NO_THROW(opts->add_and_parse(arg_group));

  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt1"));
  BOOST_CHECK_EQUAL(3, int_opt1);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt1"));
  BOOST_CHECK_EQUAL(true, bool_opt1);
  BOOST_CHECK_EQUAL(false, opts->was_supplied("interactions"));
  BOOST_CHECK_EQUAL("NONE", interactions);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt2"));
  BOOST_CHECK_EQUAL(4, int_opt2);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt2"));
  BOOST_CHECK_EQUAL(true, bool_opt2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_from_header_strings_bool_int_interaction_int_bool_opt_noskip, T, option_types)
{
  const std::vector<std::string> strings{
      "--bool_opt1", "--int_opt1", "3", "--interactions", "::", "--int_opt2", "4", "--bool_opt2"};
  auto opts = VW::make_unique<T>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, false, *opts, is_ccb_model);

  int int_opt1 = -1;
  bool bool_opt1;
  std::string interactions = "NONE";
  int int_opt2 = -1;
  bool bool_opt2;

  option_group_definition arg_group("");
  arg_group.add(make_option("int_opt1", int_opt1));
  arg_group.add(make_option("bool_opt1", bool_opt1));
  arg_group.add(make_option("interactions", interactions));
  arg_group.add(make_option("int_opt2", int_opt2));
  arg_group.add(make_option("bool_opt2", bool_opt2));

  BOOST_CHECK_NO_THROW(opts->add_and_parse(arg_group));

  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt1"));
  BOOST_CHECK_EQUAL(3, int_opt1);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt1"));
  BOOST_CHECK_EQUAL(true, bool_opt1);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("interactions"));
  BOOST_CHECK_EQUAL("::", interactions);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt2"));
  BOOST_CHECK_EQUAL(4, int_opt2);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt2"));
  BOOST_CHECK_EQUAL(true, bool_opt2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_from_header_strings_int_bool_interaction_bool_int_opt_skip, T, option_types)
{
  const std::vector<std::string> strings{
      "--int_opt1", "3", "--bool_opt1", "--interactions", "::", "--bool_opt2", "--int_opt2", "4"};
  auto opts = VW::make_unique<T>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, true, *opts, is_ccb_model);

  int int_opt1 = -1;
  bool bool_opt1;
  std::string interactions = "NONE";
  int int_opt2 = -1;
  bool bool_opt2;

  option_group_definition arg_group("");
  arg_group.add(make_option("int_opt1", int_opt1));
  arg_group.add(make_option("bool_opt1", bool_opt1));
  arg_group.add(make_option("interactions", interactions));
  arg_group.add(make_option("int_opt2", int_opt2));
  arg_group.add(make_option("bool_opt2", bool_opt2));

  BOOST_CHECK_NO_THROW(opts->add_and_parse(arg_group));

  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt1"));
  BOOST_CHECK_EQUAL(3, int_opt1);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt1"));
  BOOST_CHECK_EQUAL(true, bool_opt1);
  BOOST_CHECK_EQUAL(false, opts->was_supplied("interactions"));
  BOOST_CHECK_EQUAL("NONE", interactions);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt2"));
  BOOST_CHECK_EQUAL(4, int_opt2);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt2"));
  BOOST_CHECK_EQUAL(true, bool_opt2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_from_header_strings_int_bool_interaction_bool_int_opt_noskip, T, option_types)
{
  const std::vector<std::string> strings{
      "--int_opt1", "3", "--bool_opt1", "--interactions", "::", "--bool_opt2", "--int_opt2", "4"};
  auto opts = VW::make_unique<T>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, false, *opts, is_ccb_model);

  int int_opt1 = -1;
  bool bool_opt1;
  std::string interactions = "NONE";
  int int_opt2 = -1;
  bool bool_opt2;

  option_group_definition arg_group("");
  arg_group.add(make_option("int_opt1", int_opt1));
  arg_group.add(make_option("bool_opt1", bool_opt1));
  arg_group.add(make_option("interactions", interactions));
  arg_group.add(make_option("int_opt2", int_opt2));
  arg_group.add(make_option("bool_opt2", bool_opt2));

  BOOST_CHECK_NO_THROW(opts->add_and_parse(arg_group));

  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt1"));
  BOOST_CHECK_EQUAL(3, int_opt1);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt1"));
  BOOST_CHECK_EQUAL(true, bool_opt1);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("interactions"));
  BOOST_CHECK_EQUAL("::", interactions);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt2"));
  BOOST_CHECK_EQUAL(4, int_opt2);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt2"));
  BOOST_CHECK_EQUAL(true, bool_opt2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_from_header_strings_int_bool_interaction_int_bool_opt_skip, T, option_types)
{
  const std::vector<std::string> strings{
      "--int_opt1", "3", "--bool_opt1", "--interactions", "::", "--int_opt2", "4", "--bool_opt2"};
  auto opts = VW::make_unique<T>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, true, *opts, is_ccb_model);

  int int_opt1 = -1;
  bool bool_opt1;
  std::string interactions = "NONE";
  int int_opt2 = -1;
  bool bool_opt2;

  option_group_definition arg_group("");
  arg_group.add(make_option("int_opt1", int_opt1));
  arg_group.add(make_option("bool_opt1", bool_opt1));
  arg_group.add(make_option("interactions", interactions));
  arg_group.add(make_option("int_opt2", int_opt2));
  arg_group.add(make_option("bool_opt2", bool_opt2));

  BOOST_CHECK_NO_THROW(opts->add_and_parse(arg_group));

  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt1"));
  BOOST_CHECK_EQUAL(3, int_opt1);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt1"));
  BOOST_CHECK_EQUAL(true, bool_opt1);
  BOOST_CHECK_EQUAL(false, opts->was_supplied("interactions"));
  BOOST_CHECK_EQUAL("NONE", interactions);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt2"));
  BOOST_CHECK_EQUAL(4, int_opt2);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt2"));
  BOOST_CHECK_EQUAL(true, bool_opt2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_from_header_strings_int_bool_interaction_int_bool_opt_noskip, T, option_types)
{
  const std::vector<std::string> strings{
      "--int_opt1", "3", "--bool_opt1", "--interactions", "::", "--int_opt2", "4", "--bool_opt2"};
  auto opts = VW::make_unique<T>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, false, *opts, is_ccb_model);

  int int_opt1 = -1;
  bool bool_opt1;
  std::string interactions = "NONE";
  int int_opt2 = -1;
  bool bool_opt2;

  option_group_definition arg_group("");
  arg_group.add(make_option("int_opt1", int_opt1));
  arg_group.add(make_option("bool_opt1", bool_opt1));
  arg_group.add(make_option("interactions", interactions));
  arg_group.add(make_option("int_opt2", int_opt2));
  arg_group.add(make_option("bool_opt2", bool_opt2));

  BOOST_CHECK_NO_THROW(opts->add_and_parse(arg_group));

  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt1"));
  BOOST_CHECK_EQUAL(3, int_opt1);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt1"));
  BOOST_CHECK_EQUAL(true, bool_opt1);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("interactions"));
  BOOST_CHECK_EQUAL("::", interactions);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("int_opt2"));
  BOOST_CHECK_EQUAL(4, int_opt2);
  BOOST_CHECK_EQUAL(true, opts->was_supplied("bool_opt2"));
  BOOST_CHECK_EQUAL(true, bool_opt2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_options_from_ccb_header, T, option_types)
{
  const std::vector<std::string> strings{"--dsjson", "--epsilon", "0.2", "--ccb_explore_adf"};
  auto opts = VW::make_unique<T>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, false, *opts, is_ccb_model);

  BOOST_CHECK_EQUAL(true, is_ccb_model);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(merge_option_from_cb_header, T, option_types)
{
  const std::vector<std::string> strings{"--dsjson", "--epsilon", "0.2", "--cb_explore_adf"};
  auto opts = VW::make_unique<T>(std::vector<std::string>());

  bool is_ccb_model = false;
  merge_options_from_header_strings(strings, false, *opts, is_ccb_model);

  BOOST_CHECK_EQUAL(false, is_ccb_model);
}