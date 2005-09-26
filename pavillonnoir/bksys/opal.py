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
Simple detection for Opal
"""

from SCons.Options import Options
import os

def exists(env):
	return true

def generate(env):
	# Detect Opal
	optionfile = env['CACHEDIR']+'opal.cache.py'
        opts = Options(optionfile)

        opts.AddOptions(
		( 'OPAL_FLAGS', 'compilation flags for OPAL' ),
		( 'OPAL_LDFLAGS', 'link flags for OPAL' ),
		( 'OPALISCONFIGURED', 'configuration succeeded' ),
        )
        opts.Update(env)
	if env['HELP']: return

	# this condition is used to check when to redetect the configuration (do not remove)
	if not env['HELP'] and (env['_CONFIGURE'] or not env.has_key('OPALISCONFIGURED')):
		print "Checking for Opal            : ",
		
		if env.has_key('OPALISCONFIGURED'): env.__delitem__('OPALISCONFIGURED')

		# clear options set previously
		if env.has_key('OPAL_FLAGS'): env.__delitem__('OPAL_FLAGS')
		if env.has_key('OPAL_LDFLAGS'): env.__delitem__('OPAL_LDFLAGS')

		includes_path = """/usr/include
/usr/local/include
/opt/include
/mingw/include
""".split()
		include = '';
		for inc in includes_path:
			if os.path.exists(inc+'/opal/opal.h'):
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
			if os.path.exists(lib+'/libopal-ode.so'):
				library = lib

		if library == '':
			env.pprint('RED','[failed] libraries not found !')
			env.Exit(1)

		env['OPAL_FLAGS'] = "-I"+include
		env['OPAL_LDFLAGS'] = "-lopal-ode"

		# success
		env['OPALISCONFIGURED']=1

		env.pprint('GREEN', '[  ok  ]')

		# save the options
		opts.Save(optionfile, env)

	# the configuration is done - at this point OPAL_*FLAGS are defined

	# load the variables detected into the environment
	#if env.has_key('OPAL_FLAGS'): env.AppendUnique( CXXFLAGS = env['OPAL_FLAGS'] )
	#if env.has_key('OPAL_LDFLAGS'): env.AppendUnique( LINKFLAGS = env['OPAL_LDFLAGS'] )
