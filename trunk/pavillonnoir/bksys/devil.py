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
Simple detection for DevIL
"""

from SCons.Options import Options
import os

def exists(env):
	return true

def generate(env):
	# Detect DevIL
	optionfile = env['CACHEDIR']+'devil.cache.py'
        opts = Options(optionfile)

        opts.AddOptions(
		( 'DEVIL_FLAGS', 'compilation flags for DEVIL' ),
		( 'DEVIL_LDFLAGS', 'link flags for DEVIL' ),
		( 'DEVILISCONFIGURED', 'configuration succeeded' ),
        )
        opts.Update(env)
	if env['HELP']: return

	# this condition is used to check when to redetect the configuration (do not remove)
	if not env['HELP'] and (env['_CONFIGURE'] or not env.has_key('DEVILISCONFIGURED')):
		print "Checking for DevIL           : ",
		
		if env.has_key('DEVILISCONFIGURED'): env.__delitem__('DEVILISCONFIGURED')

		# clear options set previously
		if env.has_key('DEVIL_FLAGS'): env.__delitem__('DEVIL_FLAGS')
		if env.has_key('DEVIL_LDFLAGS'): env.__delitem__('DEVIL_LDFLAGS')

		includes_path = """/usr/include
/usr/local/include
/opt/include
/mingw/include
""".split()
		include = '';
		for inc in includes_path:
			if os.path.exists(inc+'/IL/il.h'):
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
			if os.path.exists(lib+'/libIL.so') and os.path.exists(lib+'/libILU.so') and os.path.exists(lib+'/libILUT.so'):
				library = lib

		if library == '':
			env.pprint('RED','[failed] libraries not found !')
			env.Exit(1)

		env['DEVIL_FLAGS'] = "-I"+include
		env['DEVIL_LDFLAGS'] = "-lIL -lILU -lILUT"

		# success
		env['DEVILISCONFIGURED']=1

		env.pprint('GREEN', '[  ok  ]')

		# save the options
		opts.Save(optionfile, env)

	# the configuration is done - at this point DEVIL_*FLAGS are defined

	# load the variables detected into the environment
	#if env.has_key('DEVIL_FLAGS'): env.AppendUnique( CXXFLAGS = env['DEVIL_FLAGS'] )
	#if env.has_key('DEVIL_LDFLAGS'): env.AppendUnique( LINKFLAGS = env['DEVIL_LDFLAGS'] )
