# Loic Guitaut, 2005
# GPL license (see COPYING)

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
Simple detection for FOX
"""

from SCons.Options import Options
import os

def exists(env):
	return true

def generate(env):
	# Detect the FOX
	optionfile = env['CACHEDIR']+'fox1.4.cache.py'
        opts = Options(optionfile)
	min_ver = "1.4.10"
	lib_config = ["fox-config","fox-config-1.4"]

        opts.AddOptions(
		( 'FOX_FLAGS', 'compilation flags for FOX' ),
		( 'FOX_LDFLAGS', 'link flags for FOX' ),
		( 'FOXISCONFIGURED', 'configuration succeeded' ),
        )
        opts.Update(env)
	if env['HELP']: return

	# this condition is used to check when to redetect the configuration (do not remove)
	if not env['HELP'] and (env['_CONFIGURE'] or not env.has_key('FOXISCONFIGURED')):
		print "Checking for LibFox 1.4      : ",
		
		if env.has_key('FOXISCONFIGURED'): env.__delitem__('FOXISCONFIGURED')

		# clear options set previously
		if env.has_key('FOX_FLAGS'): env.__delitem__('FOX_FLAGS')
		if env.has_key('FOX_LDFLAGS'): env.__delitem__('FOX_LDFLAGS')

		haslib = '';
		for prog in lib_config:
			haslib = os.popen('command -v '+prog+' 2>/dev/null').read().strip()
			if len(haslib) >= 1:
				break
		if len(haslib) < 1:
			env.pprint('RED','[failed] library not found !')
			env.Exit(1)

		lib_version = os.popen(haslib+' --version').read().strip()
		if lib_version < min_ver:
			env.pprint('RED','[failed] found ' + lib_version + ' version but >= ' + min_ver + ' is required.')
			env.Exit(1)

		env['FOX_FLAGS'] = os.popen(haslib+' --cflags').read().strip()
		env['FOX_LDFLAGS'] = os.popen(haslib+' --libs').read().strip()

		# success
		env['FOXISCONFIGURED']=1

		env.pprint('GREEN', '[  ok  ] '+lib_version)

		# save the options
		opts.Save(optionfile, env)

	# the configuration is done - at this point FOX_*FLAGS are defined

	# load the variables detected into the environment
	#if env.has_key('FOX_FLAGS'): env.AppendUnique( CXXFLAGS = env['FOX_FLAGS'] )
	#if env.has_key('FOX_LDFLAGS'): env.AppendUnique( LINKFLAGS = env['FOX_LDFLAGS'] )

