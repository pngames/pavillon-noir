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
Simple detection for CEGUI
"""

from SCons.Options import Options
import os

def exists(env):
	return true

def generate(env):
	# Detect the CEGUI
	optionfile = env['CACHEDIR']+'cegui.cache.py'
        opts = Options(optionfile)
	min_ver = "0.4.0"
	lib_name = "CEGUI-OPENGL"

        opts.AddOptions(
		( 'CEGUI_FLAGS', 'compilation flags for CEGUI' ),
		( 'CEGUI_LDFLAGS', 'link flags for CEGUI' ),
		( 'CEGUIISCONFIGURED', 'configuration succeeded' ),
        )
        opts.Update(env)
	if env['HELP']: return

	# this condition is used to check when to redetect the configuration (do not remove)
	if not env['HELP'] and (env['_CONFIGURE'] or not env.has_key('CEGUIISCONFIGURED')):
		print "Checking for CEGUI-OPENGL    : ",
		
		if env.has_key('CEGUIISCONFIGURED'): env.__delitem__('CEGUIISCONFIGURED')

		# clear options set previously
		if env.has_key('CEGUI_FLAGS'): env.__delitem__('CEGUI_FLAGS')
		if env.has_key('CEGUI_LDFLAGS'): env.__delitem__('CEGUI_LDFLAGS')

		pkgconfig = os.popen('command -v pkg-config 2>/dev/null').read().strip()
		if len(pkgconfig) < 1:
			env.pprint('RED','[failed] pkg-config not found ! Check your installation.')
			env.Exit(1)

		haslib = os.system('pkg-config --exists '+lib_name)
		if haslib != 0:
			env.pprint('RED','[failed] library not found !')
			env.Exit(1)

		lib_version = os.popen('pkg-config --modversion '+lib_name).read().strip()
		if lib_version < min_ver:
			env.pprint('RED','[failed] found ' + lib_version + ' version but >= ' + min_ver + ' is required.')
			env.Exit(1)

		env['CEGUI_FLAGS'] = os.popen('pkg-config --cflags '+lib_name).read().strip()
		env['CEGUI_LDFLAGS'] = os.popen('pkg-config --libs '+lib_name).read().strip()

		# success
		env['CEGUIISCONFIGURED']=1

		env.pprint('GREEN', '[  ok  ] '+lib_version)

		# save the options
		opts.Save(optionfile, env)

	# the configuration is done - at this point CEGUI_*FLAGS are defined

	# load the variables detected into the environment
	#if env.has_key('CEGUI_FLAGS'): env.AppendUnique( CXXFLAGS = env['CEGUI_FLAGS'] )
	#if env.has_key('CEGUI_LDFLAGS'): env.AppendUnique( LINKFLAGS = env['CEGUI_LDFLAGS'] )

