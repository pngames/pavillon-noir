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
Simple detection for SDL
"""

from SCons.Options import Options
import os

def exists(env):
	return true

def generate(env):
	# Detect the SDL
	optionfile = env['CACHEDIR']+'sdl.cache.py'
        opts = Options(optionfile)
	min_ver = "1.2.0"
	lib_config = "sdl-config"

        opts.AddOptions(
		( 'SDL_FLAGS', 'compilation flags for SDL' ),
		( 'SDL_LDFLAGS', 'link flags for SDL' ),
		( 'SDLISCONFIGURED', 'configuration succeeded' ),
        )
        opts.Update(env)
	if env['HELP']: return

	# this condition is used to check when to redetect the configuration (do not remove)
	if not env['HELP'] and (env['_CONFIGURE'] or not env.has_key('SDLISCONFIGURED')):
		print "Checking for SDL             : ",
		
		if env.has_key('SDLISCONFIGURED'): env.__delitem__('SDLISCONFIGURED')

		# clear options set previously
		if env.has_key('SDL_FLAGS'): env.__delitem__('SDL_FLAGS')
		if env.has_key('SDL_LDFLAGS'): env.__delitem__('SDL_LDFLAGS')

		haslib = os.popen('command -v '+lib_config+' 2>/dev/null').read().strip()
		if len(haslib) < 1:
			env.pprint('RED','[failed] library not found !')
			env.Exit(1)

		lib_version = os.popen(lib_config+' --version').read().strip()
		if lib_version < min_ver:
			env.pprint('RED','[failed] found ' + lib_version + ' version but >= ' + min_ver + ' is required.')
			env.Exit(1)

		env['SDL_FLAGS'] = os.popen(lib_config+' --cflags').read().strip()
		env['SDL_LDFLAGS'] = os.popen(lib_config+' --libs').read().strip()

		# success
		env['SDLISCONFIGURED']=1

		env.pprint('GREEN', '[  ok  ] '+lib_version)

		# save the options
		opts.Save(optionfile, env)

	# the configuration is done - at this point SDL_*FLAGS are defined

	# load the variables detected into the environment
	#if env.has_key('SDL_FLAGS'): env.AppendUnique( CXXFLAGS = env['SDL_FLAGS'] )
	#if env.has_key('SDL_LDFLAGS'): env.AppendUnique( LINKFLAGS = env['SDL_LDFLAGS'] )

