`pythonic++` - A small `C++` convenience library
================================================

`pythonic++` brings some python-style programming to `C++` for ease, fun and
more expressive code (see examples below).

`enumerate()`
-------------

The `enumerate(Container [, start])` function can be used to count the
iterations over an STL conform container. Optionally, the value to start counting
from can be provided.

	#include <vector>
	#include <iostream>
	#include "pythonic/enumerate.h"
	using namespace pythonic;
	
	// ...
	
	typedef std::vector<int> vec;
	
	for (auto v : enumerate(vec {0, -1337, 42}))
	{
	  std::cout << v.first << " " << v.second << std::endl;
	}
	
	// ...


`zip()`
-------

The `zip([Container, ...])` function can be used to iterate over several
containers in lockstep. The number of iterations is determined by the length
of the shortest container.

	#include <vector>
	#include <map>
	#include "pythonic/zip.h"
	using namespace pythonic;
	
	// ...
	
	std::map<int, float> m;
	
	// ...
	
	std::vector<int>   keys(m.size());
	std::vector<float> values(m.size());
	
	for (auto v : zip(m, keys, values))
	{
	  std::get<1>(v) = std::get<0>(v).first;
	  std::get<2>(v) = std::get<0>(v).second;
	}
	
	// ...

In the example, two vectors are filled with the keys and values from a map.


Requirements
------------

The library requires a modern compiler supporting `C++11`.


Licensing
---------
Copyright (c) 2013, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)

Distributed under the terms of the GPLv2 or newer.
