// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // »сключите редко используемые компоненты из заголовков Windows
#pragma warning (disable: 4996)


// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы
#include <memory>
#include <sstream>
#include <chrono>
#include <boost\filesystem.hpp>
#include <boost\format.hpp>
#include <boost\signals2.hpp>
#include <boost\bind.hpp>
#include <list>
#include <algorithm>