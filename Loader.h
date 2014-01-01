/*
 * Loader.h
 * This file is part of loaderPlugin
 *
 * Copyright (C) 2014 - Giacomo Bergami
 *
 * socialsim is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * socialsim is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with socialsim; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */

#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <dlfcn.h>

/**
 * MAKE_PLUGIN:
 * This macro creates the caller
 * @arg T:     is the plugin's class
 * @arg Super: is the superclass of T
 */
#define MAKE_PLUGIN(T,Super) extern "C" Super* create() { return new T(); }

template <typename T>  class Loader {

	std::map<std::string,void*> map_handler;
	std::map<std::string,std::shared_ptr<T>> map_plugin; 
	

	public:
		Loader() {};
		~Loader() {
			for(std::map<std::string, void*>::iterator iterator = map_handler.begin(); 
					iterator != map_handler.end(); iterator++) {
				dlclose(iterator->second);
			}
		}
		std::shared_ptr<T> load(std::string path);
};


template<typename T> std::shared_ptr<T> Loader<T>::load(std::string path) {
	using std::cout;
    using std::cerr;
    
	typename std::map<std::string,std::shared_ptr<T>>::iterator it = map_plugin.find(path);
	if (it != map_plugin.end()) {
		cout << "Got!" << std::endl;
		return it->second;
	}

    // load the triangle library
    void* handler = dlopen(path.c_str(), RTLD_LAZY);
    if (!handler) {
        cerr << "Cannot load library: " << dlerror() << '\n';
        std::shared_ptr<T> toret{nullptr};
    	return toret;
    }

    // reset errors
    dlerror();
    typedef T* plugin_create_t();
    
    // load the symbols
    plugin_create_t* constructor = (plugin_create_t*) dlsym(handler, "create");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol create: " << dlsym_error << '\n';
        std::shared_ptr<T> toret{nullptr};
    	return toret;
    }
    

    // create an instance of the class
    map_handler[path] = handler;
    std::shared_ptr<T> toret{constructor()};
    map_plugin[path] = toret;
    
    return toret;
}


