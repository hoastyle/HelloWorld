#!/usr/bin/python
# $Id: build_libs.py 31348 2015-06-09 14:38:16Z sfernan $
###############################################################################
# Copyright (c), 2009 - Analog Devices Inc. All Rights Reserved.
# 3 Technology Way, Norwood, MA, 02062, USA
# This software is PROPRIETARY & CONFIDENTIAL to Analog Devices, Inc.
# and its licensors.
###############################################################################
#
# Title: Build RTOS related Libraries
#
# Description:
#   This script runs through all the .project contain in the installation and builds
#   the libraries.
#
#
""" <build_libs.py>
   This script runs through all the .project contain in the installation and builds
   the libraries.
"""


import os
import re
import sys
import time
import shutil
import subprocess
import win32pdhutil
#import win32api
import win32con
# import VisualDSP
from optparse import OptionParser
from progressbar import progressBar
from timeout import timed_out, TimeoutError



##
# Constant: __version__
# Modify this to reflect the version of this module
#
# Format:
# major.minor.patch
#
__version__ = "2.0"

##
# Constant: BUILD_TIMEOUT
# Build times out after 5mn  (timeout in seconds)
#
BUILD_TIMEOUT = 300

##
# Constant: MAX_RETRIES
# only retry to build MAX_RETRIES times if IDDE crashes.
#
MAX_RETRIES = 3


verbose = False
quiet   = False
visible = False
debug   = False
rebuild = False

def print_verbose(message):
    if verbose:
        print(message)
        sys.stdout.flush()


def GetListProjectFiles(root_dir, filter_in=None, filter_out=None):
    """
       Returns a list of project files *.project
       It will also allow the user to define a regular expressions to filter files 
       to be either included (filter_in) or excluded (filter_out) if they match the 
       regexp
       The file is automatically removed if it end with the string 'auto.dpj' because 
       Those libraries are not built by the build process.
    """
    
    # case where the user writes the path with a trailing '\', DOS prompt will add the following " character (\")
    root_dir = root_dir.rstrip('\"')

    
    print_verbose("Extracting project files from '%s'..."%root_dir)
    project_files_list = []
    
    if filter_in is not None:
        searchpattern_in = re.compile(filter_in)
    if filter_out is not None:
        searchpattern_out = re.compile(filter_out)

    # loop through the files
    for root, dirs, files in os.walk(root_dir):
		for dirname in dirs:
			# apply filtering
			full_name = os.path.join(root, dirname)
			if filter_out is not None and searchpattern_out.search(full_name):
				continue
			if filter_in is not None and not searchpattern_in.search(full_name):
				continue
			files =  os.listdir(full_name)
			for filename in files:
				filename = filename.replace('/','\\')
				root = root.replace('/','\\')
				if (filename == '.project'):
					# Don't build any of the auto libraries, we don't release them and they have a
					# name collision with the "none" files we *do* release.
					if filename.endswith('auto.dpj'):
						continue
					project_files_list.append(full_name)
					print full_name
                
    print_verbose("found %d files.\n"%len(project_files_list))
    
    return(project_files_list)

	
# 5 minutes timeout, it should be long enough to build a library (unless IDDE Crashed, which is what we're trying to catch.
@timed_out(BUILD_TIMEOUT)
def BuildProject(headless_build_path, root_dir, project_dir):
    """
        Builds all configurations (Debug/Release) of the given project file, and timeout if not complete after 5 minutes.
    """
    build_errors = 0
	
    # reset at the start of each project build
    # VisualDSP.KillInstances()

	# build using headless build
    filebase = os.path.basename(project_dir)
    print_verbose( "   * %s"%filebase)

    outdir = root_dir
    while (os.path.basename(outdir) != "temp"):
      (outdir, filename) = os.path.split(outdir)

    outdir = os.path.join(outdir, "build")

    if os.path.isdir(outdir) == False:
        os.mkdir(outdir)

    projtype = ""
    if project_dir.find("noos") >= 0:
        projtype = projtype + "_noos"

    if project_dir.find("osal") >= 0:
        projtype = projtype + "_osal"
		
    if project_dir.find("micrium") >= 0:
        projtype = projtype + "_micrium"

    if project_dir.find("ucos-III") >= 0:
        projtype = projtype + "_ucos-III"

    if project_dir.find("uC-CPU") >= 0:
        projtype = projtype + "_uC-CPU"

    if project_dir.find("uC-LIB") >= 0:
        projtype = projtype + "_uC-LIB"
		
    outdir = os.path.join(outdir, projtype.lstrip("_"))

    if os.path.isdir(outdir) == False:
        os.mkdir(outdir)
        
    outdir = os.path.join(outdir, filebase)

    if os.path.isdir(outdir):
        shutil.rmtree(outdir, ignore_errors=True)
    
    os.mkdir(outdir)

	# headless build command
    cmd = '"%s" -nosplash --launcher.suppressErrors -application %s -data "%s" -import "%s" -cleanBuild %s -build %s -vmargs -Declipse.exitdata=""'%(headless_build_path, "org.eclipse.cdt.managedbuilder.core.headlessbuild", outdir, project_dir, "all", "all")
    print 'cmd: ', cmd

    file_new = os.path.join(outdir, "build.log")
    fh1 = open(file_new, 'w')
    p1 = subprocess.Popen(cmd, stdout=fh1)
    p1.wait()
    fh1.close()

    # search build.log for compile errors
    fh1 = open(file_new, 'r')
    text = fh1.read()
    fh1.close()

    index = text.find("error: ")
    if index >= 0:
      build_errors = 1

    index = text.find("Compilation failed")
    if index >= 0:
      build_errors = 1

    index = text.find("*** No rule to make target")
    if index >= 0:
      build_errors = 1

    index = text.find("make: *** ")
    if index >= 0:
      build_errors = 1

    return build_errors




def BuildLibs(headless_build_path, root_dir, filter_in=None, filter_out=None):
    "Builds all the project files *.project that are in the root_dir and its subfolders"

    root_dir = root_dir.replace('/','\\')

    # Get the list of project files
    Files = GetListProjectFiles(root_dir, filter_in, filter_out)    

    if len(Files) == 0:
        return(0)
    
    build_error = 0

    # if verbose is not selected, print a progress bar
    if not verbose and not quiet:
        pbar = progressBar(0, len(Files), 50)
        pbar_files = 0

    
    # Go and build libraries one by one
    print_verbose("Building libraries:")
    for filename in Files:

        if not verbose and not quiet:
            pbar_files += 1
            pbar(pbar_files)
            
        try:
            # re-try to build N times
            timeout_num = 0
            build_success = False
            while( not build_success):
                try:
                    build_error += BuildProject(headless_build_path, root_dir, filename)
                    build_success = True;           # if the previous call did not hang
                except TimeoutError, v:
                    print_verbose("timeout %d"%timeout_num)
                    timeout_num += 1
                if timeout_num >= MAX_RETRIES:
                    raise TimeoutError
                 
        except Exception, v:
            build_error += 1
            
        if build_error > 0:
            print "[Error] ***build failure: %s \n--------\n\n"%(filename)

    print_verbose("Done building OSAL libraries")
    return build_error



if __name__ == "__main__":

    #
    # Main
    #

    if sys.version_info < (2, 5, 0, 0):
        sys.exit("[Error] This script requires Python version 2.5 or above")
        
    if os.name is not 'nt':
        sys.exit("[Error] This script can only be run on a Windows XP Platform")
    
    parser = OptionParser(usage = "usage: %prog", version="%prog "+"%s"%(__version__))
    parser.add_option("-v", "--verbose", help="Verbose output", action="store_true", dest="verbose", default=False)
    parser.add_option("-q", "--quiet", help="quiet output", action="store_true", dest="quiet", default=False)
    parser.add_option("--visible", help="Shows IDDE GUI when running", action="store_true", dest="visible", default=False)
    parser.add_option("-k", "--kill-idde", help="Kill running idde instances", action="store_true", dest="killidde", default=False)
    parser.add_option("-r", "--rebuild", help="Rebuild all objects every time", action="store_true", dest="rebuild", default=False)
    parser.add_option("--headless-build-exe-path", help="The script will execute the headless build exe", dest="headless_build_path", metavar="HEADLESS_BUILD_PATH", default="C:\Analog Devices\Crosscore Embedded Studio 2.0.0\Eclipse\ccesc.exe")
    parser.add_option("-p", "--projects-path", help="The script will build all the projects found within this path", dest="projects_path", metavar="PROJECTS_PATH", default="C:\Analog Devices\Crosscore Embedded Studio 2.0.0")
    parser.add_option("--filter-in-regexp", help="the file is only added to the list if the specified regular expression matches", 
                      dest="filter_in", metavar="FILTER_IN_REGEXP", default=None)
    parser.add_option("--filter-out-regexp", help="the file is removed from the list if the specified regular expression matches",
                      dest="filter_out", metavar="FILTER_OUT_REGEXP", default=None)
        
    (options, args) = parser.parse_args()

    visible = options.visible
    verbose = options.verbose
    quiet   = options.quiet
    rebuild = options.rebuild

    #if options.killidde:
    #    VisualDSP.KillInstances()

    print "==Library Build Log==\n\n"
    # Log start of the Build
    print "Build started on:", time.strftime( "%I:%M%p EDT   %B %d, %Y")

    build_errors = BuildLibs(options.headless_build_path, options.projects_path, options.filter_in, options.filter_out)
    
    if build_errors==0:
        print "\n[PASS] All libraries built successfully"
    else:
        print "\n[FAIL] %d errors while building libraries"%build_errors
    
    sys.exit(build_errors)
    
    
