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
Simple detection for Lua 5.0
"""

from SCons.Options import Options
import os

def exists(env):
	return true

def generate(env):
	# Detect the Lua 5.0
	optionfile = env['CACHEDIR']+'lua50.cache.py'
        opts = Options(optionfile)
	lib_config = "lua-config"

        opts.AddOptions(
		( 'LUA50_FLAGS', 'compilation flags for LUA50' ),
		( 'LUA50_LDFLAGS', 'link flags for LUA50' ),
		( 'LUA50ISCONFIGURED', 'configuration succeeded' ),
        )
        opts.Update(env)
	if env['HELP']: return

	# this condition is used to check when to redetect the configuration (do not remove)
	if not env['HELP'] and (env['_CONFIGURE'] or not env.has_key('LUA50ISCONFIGURED')):
		print "Checking for Lua 5.0         : ",
		
		if env.has_key('LUA50ISCONFIGURED'): env.__delitem__('LUA50ISCONFIGURED')

		# clear options set previously
		if env.has_key('LUA50_FLAGS'): env.__delitem__('LUA50_FLAGS')
		if env.has_key('LUA50_LDFLAGS'): env.__delitem__('LUA50_LDFLAGS')

		haslib = os.popen('command -v '+lib_config+' 2>/dev/null').read().strip()
		if len(haslib) < 1:
			env.pprint('RED','[failed] library not found !')
			env.Exit(1)

		env['LUA50_FLAGS'] = os.popen(lib_config+' --include').read().strip()
		env['LUA50_LDFLAGS'] = os.popen(lib_config+' --libs').read().strip()

		# success
		env['LUA50ISCONFIGURED']=1

		env.pprint('GREEN', '[  ok  ] ')

		# save the options
		opts.Save(optionfile, env)

	# the configuration is done - at this point LUA50_*FLAGS are defined

	# load the variables detected into the environment
	#if env.has_key('LUA50_FLAGS'): env.AppendUnique( CXXFLAGS = env['LUA50_FLAGS'] )
	#if env.has_key('LUA50_LDFLAGS'): env.AppendUnique( LINKFLAGS = env['LUA50_LDFLAGS'] )

