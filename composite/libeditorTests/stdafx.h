// stdafx.h: включаемый файл для стандартных системных включаемых файлов
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <sstream>

#define BOOST_TEST_INCLUDED
#define D_SCL_SECURE_NO_WARNINGS

#pragma warning (push, 3)
#pragma warning (disable:4456 4702 4996)
#include <boost/test/unit_test.hpp>
#pragma warning (pop)

#include <boost/range/algorithm/copy.hpp>
#include <boost/algorithm/cxx11/all_of.hpp>

#include <algorithm>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <boost/optional/optional_io.hpp>
#include <memory>
#include <boost/range/algorithm/for_each.hpp>