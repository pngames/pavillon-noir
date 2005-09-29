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
Simple detection for ElectricFence
"""

from SCons.Options import Options
import os

def exists(env):
	return true

def generate(env):
	if env['DEBUG'] == 0: return

	# Detect ElectricFence
	optionfile = env['CACHEDIR']+'efence.cache.py'
        opts = Options(optionfile)

        opts.AddOptions(
		( 'EFENCE_LDFLAGS', 'link flags for EFENCE' ),
		( 'EFENCEISCONFIGURED', 'configuration succeeded' ),
        )
        opts.Update(env)
	if env['HELP']: return

	# this condition is used to check when to redetect the configuration (do not remove)
	if not env['HELP'] and (env['_CONFIGURE'] or not env.has_key('EFENCEISCONFIGURED')):
		print "Checking for ElectricFence   : ",
		
		if env.has_key('EFENCEISCONFIGURED'): env.__delitem__('EFENCEISCONFIGURED')

		# clear options set previously
		if env.has_key('EFENCE_LDFLAGS'): env.__delitem__('EFENCE_LDFLAGS')

		libs_path = """/usr/lib
/usr/local/lib
/opt/lib
/mingw/lib""".split()

		library = ''
		for lib in libs_path:
			if os.path.exists(lib+'/libefence.so'):
				library = lib

		if library == '':
			env.pprint('RED','[failed] library not found !')
			env.Exit(1)

		env['EFENCE_LDFLAGS'] = "-lefence"

		# success
		env['EFENCEISCONFIGURED']=1

		env.pprint('GREEN', '[  ok  ]')

		# save the options
		opts.Save(optionfile, env)

	# the configuration is done - at this point EFENCE_*FLAGS are defined

	# load the variables detected into the environment
	#if env.has_key('EFENCE_FLAGS'): env.AppendUnique( CXXFLAGS = env['EFENCE_FLAGS'] )
	#if env.has_key('EFENCE_LDFLAGS'): env.AppendUnique( LINKFLAGS = env['EFENCE_LDFLAGS'] )
