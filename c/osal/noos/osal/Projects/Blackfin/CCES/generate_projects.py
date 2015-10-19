#!/usr/bin/python
###############################################################################
# Copyright (c) 2009-2010 - Analog Devices Inc. All Rights Reserved.
# This software is proprietary & confidential to Analog Devices, Inc.
# and its licensors.
###############################################################################
# $Revision: 9847 $
# $Date: 2011-03-03 01:03:21 +0800 (Thu, 03 Mar 2011) $
#
# Title: VDSP Project Generator
#
# Description:
# This modules uses a template file in order to generate VDSP project files
#
###############################################################################

import ConfigParser
import os
import string
import sys
import shutil
from optparse import OptionParser


#
# Format is major.minor.patch
#
# Note that the SVN revision number may be suffixed within the code, as required,
# to make a full version number
#
__version__ = '1.0.0'




help_keywords = """
Any keyword can be used in the template and config file.
The following ones are examples of valid keywords:
PROC        - target processor
               ==> 548, 527, ...
REVISION    - processor revision
               ==> 'auto', 'any', 'none', '0.1', '0.2',...
TEMPLATE1,TEMPLATE2   - project template files 
LIBNAME     - name of the library
"""

#
# Some standard-class overrides
#

# override ConfigParser in order to keep the Config option case-sensitive
class VDSPProjGenConfigParser(ConfigParser.ConfigParser):
    def optionxform(self, optionstr):
        return optionstr.strip()

# override the delimiters in string.Template to be '#' because '$' is already used for $(ADI_DSP)
class VDSPProjGenTemplateClass(string.Template):
    delimiter = '#'




#
# Function: ParseControlFile
#
# This function parses the control file in order to find what needs to be done
# it creates a dictionary and returns it
#
# Arguments:
#   ctrlfile  - name of the control file
#   verbose   - if true, print more information about the processing
#
# Returns:
#    a Dictionary where the keys are the section (libraries) and the values another dictionary whose
#    keys/values are the configuration options and their values
#
def ParseControlFile(ctrlfile, verbose=False):
    
    # we use a overridden version of ConfigParser.ConfigParser so that the options 
    # remain case-sensitive
    parser = VDSPProjGenConfigParser()
    parser.read(ctrlfile)
    
    # start an empty dictionary to hold the options
    # each key will be a different library target : configuration file section
    # values will be the values in that configuration file section 
    libs = dict()
    
    sections = parser.sections()
    
    if verbose:
        print "Control file options:"
        
    for lib in sections:
        if lib == 'general':
            # skip the general section
            continue

        if verbose:
            print "   * ", lib
            
        libopt = parser.items(lib)
        
        if parser.has_section('general'):
            try:
                # Add the values in general and expand them using the keys from the specific section
                genopt = parser.items('general', 0, dict(libopt))
            except ConfigParser.InterpolationMissingOptionError, v:
                print "\nERROR: Section '%s' in file '%s' does not contain valid entries!\n"%(lib, ctrlfile)
                raise
    
        optdic = dict(genopt)
 
        if verbose:            
            for config in optdic:
                print "      - %s = %s"%(config, optdic[config])
        
        libs[str(lib)]=optdic
        
    return libs



#
# Function: generate_project_file
#
# This function generates a porject file based on the given template and keywords
#
# Arguments:
#   liboptions - dictionary as given by ParseControlFile()
#   target     - if not None, only generate the specified target section 
#   verbose  - if true, print more information about the processing
#
# Returns:
#    a file is generated based on the template file and the keys given in the config file.
#

descstr = """
Project File Generation:
------------------------
Output filename = %s
Template = %s
Keywords = %s
"""
def generate_project_file(liboptions, target=None, proc=None, revision=None, verbose=False):
    
    print "Generating:"
    
    for libkey in liboptions:
        
        try:
            if (target is not None) and (target not in libkey):
                continue
                
            libopt = liboptions[libkey]

            if (proc is not None) and (proc != libopt['PROC']):
                continue
                
            if (revision is not None) and (revision != libopt['REVISION']):
                continue
            
            outfolder = libopt['PROJFOLDER']
            tmp_outfile1 = libopt['PROJNAME1']
            tmp_outfile2 = libopt['PROJNAME2']
            outfile1 = outfolder + "/" + tmp_outfile1
            outfile2 = outfolder + "/" + tmp_outfile2
            template1 = libopt['TEMPLATE1']
            template2 = libopt['TEMPLATE2']
            keywords = libopt
            
            # special case for 'auto', it needs to be translated to 'Automatic'
            if keywords.has_key('REVISION') and keywords['REVISION'] == 'auto':
                keywords['REVISION'] = 'Automatic'
                
            if not os.path.exists(outfolder):
            	os.mkdir(outfolder)
        except KeyError:
            print "Warning: Section '%s' has missing entries, SKIPPED!"%str(libkey)
            continue
        
        if verbose:
            print descstr%(outfile1, template1, keywords)
            print descstr%(outfile2, template2, keywords)
        else:
            print outfile1
            print outfile2

        # Actually do the keyword substitution on the template
        try:
            fout = open(outfile1, 'w')
            fin = open(template1, 'r')
            inputstr = fin.read()
            templateobj = VDSPProjGenTemplateClass(inputstr)
            outstr = templateobj.substitute(keywords);
            fout.write(outstr)
        
        except IOError, v:
            print "ERROR opening files: %s"%v

        try:
            fout = open(outfile2, 'w')
            fin = open(template2, 'r')
            inputstr = fin.read()
            templateobj = VDSPProjGenTemplateClass(inputstr)
            outstr = templateobj.substitute(keywords);
            fout.write(outstr)
        
        except IOError, v:
            print "ERROR opening files: %s"%v

# Function: generate_build_folders
#
# This function generates a porject file based on the given template and keywords
#
# Arguments:
#   liboptions - dictionary as given by ParseControlFile()
#   target     - if not None, only generate the specified target section 
#   verbose  - if true, print more information about the processing
#
# Returns:
#    a file is generated based on the template file and the keys given in the config file.
#
descstr = """
Output Build Folder Generation:
------------------------
Output filename = %s
Template = %s
Keywords = %s
"""
def generate_build_folders(liboptions, target=None, proc=None, revision=None, verbose=False):
    
    print "Generating:"
    
    for libkey in liboptions:
        
        try:
            if (target is not None) and (target not in libkey):
                continue
                
            libopt = liboptions[libkey]

            if (proc is not None) and (proc != libopt['PROC']):
                continue
                
            if (revision is not None) and (revision != libopt['REVISION']):
                continue
            
            outfolder = libopt['OUT_FOLDER']
            if not os.path.exists("Build"):
            	os.mkdir("Build")

            build_outfolder = "Build/"+ outfolder 
            build_outfolder1 = "Build/" + outfolder + "/debug" 
            keywords = libopt
            
            if not os.path.exists(build_outfolder):
            	os.mkdir(build_outfolder)

            if not os.path.exists(build_outfolder1):
            	os.mkdir(build_outfolder1)

        except KeyError:
            print "Warning: Section '%s' has missing entries, SKIPPED!"%str(libkey)
            continue
        
        if verbose:
            print descstr%(build_outfolder1, keywords)
        else:
            print build_outfolder1

if __name__ == '__main__':

    #
    # Main
    #
    
    desc = """
Automatically generates VisualDSP project files for the specified DSP type and revisions
It is based on a template project files and definitions come from a control file.
"""  +  help_keywords

    parser = OptionParser(usage = "%prog [options] control_file",
                          description=desc,
                          version="%prog "+"- %s"%__version__)
    parser.add_option("-v", "--verbose", help="Verbose output", action="store_true", dest="verbose")
    parser.add_option("-t", "--target",  help="only generate for the specified target name", dest="target", metavar="TARGET", default=None)
    parser.add_option("-p", "--proc",    help="only generate for the specified processor", dest="proc", metavar="PROC", default=None)
    # TODO : add a callback to check the validity of the revision 
    parser.add_option("-r", "--procrev", help="only generate for the specified processor revision", dest="rev", metavar="PROCREV", default=None)
    
    (options, args) = parser.parse_args()
  
    if len(args) < 1:
        parser.print_help()
        sys.exit("\n\nERROR: No control file, you need to provide a test control file\n\n")
    else:
        ctrlfile = args[0]
  
    try:    
        libraries_options = ParseControlFile(ctrlfile, verbose=options.verbose)
    except Exception, v:
        # error message already printed out.
        print "ERROR:", v
        sys.exit(1)
        
    generate_project_file(libraries_options, target=options.target, proc=options.proc, revision=options.rev, verbose=options.verbose)
    generate_build_folders(libraries_options, target=options.target, proc=options.proc, revision=options.rev, verbose=options.verbose)

#
#
# EOF: $URL: https://dspeng.spd.analog.com/svn/swe/rtos/trunk/noos/osal/Projects/Blackfin/CCES/generate_projects.py $
#
#
