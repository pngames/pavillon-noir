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
Simple detection for FastDelegate
"""

from SCons.Options import Options
import os

def exists(env):
	return true

def generate(env):
	# Detect the FastDelegate
	optionfile = env['CACHEDIR']+'fastdelegate.cache.py'
        opts = Options(optionfile)

        opts.AddOptions(
		( 'FastDelegate_FLAGS', 'compilation flags for FastDelegate' ),
		( 'FastDelegateISCONFIGURED', 'configuration succeeded' ),
        )
        opts.Update(env)
	if env['HELP']: return

	# this condition is used to check when to redetect the configuration (do not remove)
	if not env['HELP'] and (env['_CONFIGURE'] or not env.has_key('FastDelegateISCONFIGURED')):
		print "Checking for FastDelegate    : ",
		
		if env.has_key('FastDelegateISCONFIGURED'): env.__delitem__('FastDelegateISCONFIGURED')

		# clear options set previously
		if env.has_key('FastDelegate_FLAGS'): env.__delitem__('FastDelegate_FLAGS')
	
		fd_path = env.Dir('#./__library/common/').abspath
		hasfd = os.path.exists(fd_path)
		if hasfd != True:
			env.pprint('RED','[failed]')
			env.Exit(1)

		env['FastDelegate_FLAGS'] = '-I'+fd_path

		# success
		env['FastDelegateISCONFIGURED']=1

		env.pprint('GREEN', '[  ok  ] path is ' + fd_path)

		# save the options
		opts.Save(optionfile, env)

	# the configuration is done - at this point FastDelegate_*FLAGS are defined

	# load the variables detected into the environment
	#if env.has_key('FastDelegate_FLAGS'): env.AppendUnique( CXXFLAGS = env['FastDelegate_FLAGS'] )
