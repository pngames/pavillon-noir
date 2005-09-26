# Loic Guitaut, 2005
# GPL License (see COPYING)

"""
This is a simple bksys module that detects the availability
of an include and sets the flags properly

The configuration is done in several steps :

	declare variables to get trom a file (opts = Options(optionfile))
	check if we need to configure (configuration requested or missing mandatory options)
	if configuration is needed:
		clear the variables set previously
		stop the configuration if necessary (something missing ..)
		set the variables as declared previously
		save the configuration to the option file
	now that the configuration is done,
	load the configuration variables into the environment
"""

"""
Simple detection for Boost
"""

from SCons.Options import Options
import os

def exists(env):
	return true

def generate(env):
	# Detect the Boost
	optionfile = env['CACHEDIR']+'boost.cache.py'
        opts = Options(optionfile)

        opts.AddOptions(
		( 'Boost_FLAGS', 'compilation flags for Boost' ),
		( 'Boost_LDFLAGS', 'link flags for Boost' ),
		( 'BoostISCONFIGURED', 'configuration succeeded' ),
        )
        opts.Update(env)
	if env['HELP']: return

	# this condition is used to check when to redetect the configuration (do not remove)
	if not env['HELP'] and (env['_CONFIGURE'] or not env.has_key('BoostISCONFIGURED')):
		print "Checking for Boost           : ",
		
		if env.has_key('BoostISCONFIGURED'): env.__delitem__('BoostISCONFIGURED')

		# clear options set previously
		if env.has_key('Boost_FLAGS'): env.__delitem__('Boost_FLAGS')
		if env.has_key('Boost_LDFLAGS'): env.__delitem__('Boost_LDFLAGS')

		boost_includes = """/usr/include
/usr/local/include
/opt/include
/mingw/include
/usr/include/boost-1_33
/usr/local/include/boost-1_33
/opt/include/boost-1_33
/mingw/include/boost-1_33
""".split()
		boost_include = '';
		for include_path in boost_includes:
			if os.path.exists(include_path+'/boost/any.hpp'):
				boost_include = include_path
				break
		if boost_include == '':
			env.pprint('RED','[failed] includes not found !')
			env.Exit(1)
		
		boost_libs = """/usr/lib
/usr/local/lib
/opt/lib
/mingw/lib""".split()

		boost_lib = ''
		for lib_path in boost_libs:
			if os.path.exists(lib_path+'/libboost_filesystem.so') and os.path.exists(lib_path+'/libboost_thread.so'):
				boost_lib = lib_path

		if boost_lib == '':
			env.pprint('RED','[failed] libraries not found !')
			env.Exit(1)

		env['Boost_FLAGS'] = "-I"+boost_include
		env['Boost_LDFLAGS'] = "-lboost_filesystem -lboost_thread"

		# success
		env['BoostISCONFIGURED']=1

		env.pprint('GREEN', '[  ok  ]')

		# save the options
		opts.Save(optionfile, env)

	# the configuration is done - at this point Boost_*FLAGS are defined

	# load the variables detected into the environment
	#if env.has_key('Boost_FLAGS'): env.AppendUnique( CXXFLAGS = env['Boost_FLAGS'] )
	#if env.has_key('Boost_LDFLAGS'): env.AppendUnique( LINKFLAGS = env['Boost_LDFLAGS'] )
