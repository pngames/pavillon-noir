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
Simple detection for GLEW
"""

from SCons.Options import Options
import os

def exists(env):
	return true

def generate(env):
	# Detect GLEW
	optionfile = env['CACHEDIR']+'glew.cache.py'
        opts = Options(optionfile)

        opts.AddOptions(
		( 'GLEW_FLAGS', 'compilation flags for GLEW' ),
		( 'GLEW_LDFLAGS', 'link flags for GLEW' ),
		( 'GLEWISCONFIGURED', 'configuration succeeded' ),
        )
        opts.Update(env)
	if env['HELP']: return

	# this condition is used to check when to redetect the configuration (do not remove)
	if not env['HELP'] and (env['_CONFIGURE'] or not env.has_key('GLEWISCONFIGURED')):
		print "Checking for GLEW            : ",
		
		if env.has_key('GLEWISCONFIGURED'): env.__delitem__('GLEWISCONFIGURED')

		# clear options set previously
		if env.has_key('GLEW_FLAGS'): env.__delitem__('GLEW_FLAGS')
		if env.has_key('GLEW_LDFLAGS'): env.__delitem__('GLEW_LDFLAGS')

		includes_path = """/usr/include
/usr/local/include
/opt/include
/mingw/include
""".split()
		include = '';
		for inc in includes_path:
			if os.path.exists(inc+'/GL/glew.h'):
				include = inc
				break
		if include == '':
			env.pprint('RED','[failed] includes not found !')
			env.Exit(1)

		libs_path = """/usr/lib
/usr/local/lib
/opt/lib
/mingw/lib""".split()

		library = ''
		for lib in libs_path:
			if os.path.exists(lib+'/libGLEW.so'):
				library = lib

		if library == '':
			env.pprint('RED','[failed] libraries not found !')
			env.Exit(1)

		env['GLEW_FLAGS'] = "-I"+include
		env['GLEW_LDFLAGS'] = "-lGLEW"

		# success
		env['GLEWISCONFIGURED']=1

		env.pprint('GREEN', '[  ok  ]')

		# save the options
		opts.Save(optionfile, env)

	# the configuration is done - at this point GLEW_*FLAGS are defined

	# load the variables detected into the environment
	#if env.has_key('GLEW_FLAGS'): env.AppendUnique( CXXFLAGS = env['GLEW_FLAGS'] )
	#if env.has_key('GLEW_LDFLAGS'): env.AppendUnique( LINKFLAGS = env['GLEW_LDFLAGS'] )
