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
Simple detection for XML
"""

from SCons.Options import Options
import os

def exists(env):
	return true

def generate(env):
	# Detect the XML
	optionfile = env['CACHEDIR']+'libxml.cache.py'
        opts = Options(optionfile)
	min_ver = "2.6.16"
	lib_config = "xml2-config"

        opts.AddOptions(
		( 'XML_FLAGS', 'compilation flags for XML' ),
		( 'XML_LDFLAGS', 'link flags for XML' ),
		( 'XMLISCONFIGURED', 'configuration succeeded' ),
        )
        opts.Update(env)
	if env['HELP']: return

	# this condition is used to check when to redetect the configuration (do not remove)
	if not env['HELP'] and (env['_CONFIGURE'] or not env.has_key('XMLISCONFIGURED')):
		print "Checking for Libxml2         : ",
		
		if env.has_key('XMLISCONFIGURED'): env.__delitem__('XMLISCONFIGURED')

		# clear options set previously
		if env.has_key('XML_FLAGS'): env.__delitem__('XML_FLAGS')
		if env.has_key('XML_LDFLAGS'): env.__delitem__('XML_LDFLAGS')

		haslib = os.popen('command -v '+lib_config+' 2>/dev/null').read().strip()
		if len(haslib) < 1:
			env.pprint('RED','[failed] library not found !')
			env.Exit(1)

		lib_version = os.popen(lib_config+' --version').read().strip()
		if lib_version < min_ver:
			env.pprint('RED','[failed] found ' + lib_version + ' version but >= ' + min_ver + ' is required.')
			env.Exit(1)

		env['XML_FLAGS'] = os.popen(lib_config+' --cflags').read().strip()
		env['XML_LDFLAGS'] = os.popen(lib_config+' --libs').read().strip()

		# success
		env['XMLISCONFIGURED']=1

		env.pprint('GREEN', '[  ok  ] '+lib_version)

		# save the options
		opts.Save(optionfile, env)

	# the configuration is done - at this point XML_*FLAGS are defined

	# load the variables detected into the environment
	#if env.has_key('XML_FLAGS'): env.AppendUnique( CXXFLAGS = env['XML_FLAGS'] )
	#if env.has_key('XML_LDFLAGS'): env.AppendUnique( LINKFLAGS = env['XML_LDFLAGS'] )

