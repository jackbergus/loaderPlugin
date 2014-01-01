/*
 * test_main.cpp
 * This file is part of LoaderPlugin
 *
 * Copyright (C) 2014 - Giacomo Bergami
 *
 * LoaderPlugin is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * LoaderPlugin is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LoaderPlugin; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */
 
 


#include "test_Plugin.h"
#include "Loader.h"
#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <dlfcn.h>

// Compile with 				g++ -std=c++11  maintest.cpp  -ldl -o maintest
// Compile plugin with			g++ -std=c++11 -shared -fPIC testplugin.cpp -o testplugin.o

int main() {
	
	{
	Loader<Plugin> l;
    std::shared_ptr<Plugin> h = l.load("./testplugin.o");
    std::cout << h->next() << std::endl;
    std::shared_ptr<Plugin> i = l.load("./testplugin.o");
     std::cout << i->next() << std::endl;
	}
	
    // unload the triangle library
    
}
