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
Simple detection for OPAL
"""

from SCons.Options import Options
import os

def exists(env):
	return true

def generate(env):
	# Detect OPAL
	optionfile = env['CACHEDIR']+'opal.cache.py'
        opts = Options(optionfile)

        opts.AddOptions(
		( 'OPAL_FLAGS', 'compilation flags for OPAL' ),
		( 'OPAL_LDFLAGS', 'link flags for OPAL'),
		( 'OPALISCONFIGURED', 'configuration succeeded' ),
        )
        opts.Update(env)
	if env['HELP']: return

	# this condition is used to check when to redetect the configuration (do not remove)
	if not env['HELP'] and (env['_CONFIGURE'] or not env.has_key('OPALISCONFIGURED')):
		print "Checking for OPAL            : ",
		
		if env.has_key('OPALISCONFIGURED'): env.__delitem__('OPALISCONFIGURED')

		# clear options set previously
		if env.has_key('OPAL_FLAGS'): env.__delitem__('OPAL_FLAGS')
		if env.has_key('OPAL_LDFLAGS'): env.__delitem__('OPAL_LDFLAGS')
	
		fd_path = env.Dir('#./__library/common/opal').abspath
		hasfd = os.path.exists(fd_path)
		if hasfd != True:
			env.pprint('RED','[failed] include not found !')
			env.Exit(1)

		env['OPAL_FLAGS'] = '-I'+env.Dir('#./__library/common').path
		
		fd_path = env.File('#./__library/linux/lib/opal/libopal-ode.so').abspath
		hasfd = os.path.exists(fd_path)
		if hasfd != True:
			env.pprint('RED','[failed] library not found !')
			env.Exit(1)

		env['OPAL_LDFLAGS'] = '-L' + env.Dir('#./__library/linux/lib/opal').path + ' -lopal-ode'

		# success
		env['OPALISCONFIGURED']=1

		env.pprint('GREEN', '[  ok  ]')

		# save the options
		opts.Save(optionfile, env)

	# the configuration is done - at this point OPAL_*FLAGS are defined

	# load the variables detected into the environment
	#if env.has_key('OPAL_FLAGS'): env.AppendUnique( CXXFLAGS = env['OPAL_FLAGS'] )
