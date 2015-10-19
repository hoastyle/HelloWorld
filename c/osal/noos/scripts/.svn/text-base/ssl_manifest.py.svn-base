#!/usr/bin/python
# $Idhschnit $
###############################################################################
# Copyright (c), 2009 - Analog Devices Inc. All Rights Reserved.
# 3 Technology Way, Norwood, MA, 02062, USA
# This software is PROPRIETARY & CONFIDENTIAL to Analog Devices, Inc.
# and its licensors.
###############################################################################
#
# Title: SSL/DD Manifest parser
#
# Description:
#   This script defines a class that processes a SSL manifest file. 
#   
###############################################################################

""" <ssl_manifest.py>
    This script defines a class that processes a SSL manifest file. 
"""

import os
import sys
import xml.dom.minidom as xmlparser
from optparse import OptionParser


##
# Constant: __version__
# Modify this to reflect the version of this module
#
# Format:
# major.minor.patch
#
__version__ = "1.0.0"



#
# The manifest file format is assumed to be the following:
#
# <manifest>  </manifest>  delimiters around the whole file.
# each file entry uses the following syntax where 'p' field is the path
#  <f p="path to the file" />
# 
# directories can be excluded using the following syntax
# <excluded dir="path to the directory to be excluded" />
#
 

class Manifest(object):
    """Object that describes a manifest file in the form of a Set(). The manifest file is given as a filename.
    """   
    __version__ = "1.0.0"
    
    __manifest_file = None
    __verbose = False
    __antmode = False

    # create empty sets to contain the list of files in the manifest and the stage area
    __manifest_set = set([])
    __exclude_set = set([])
    __internal_set = set([])
    __generated_set = set([])
        
    debug = False
    
    def __init__(self, manifest_filename="manifest.xml"):
        self.__manifest_file = manifest_filename
        
        # process manifest file
        try:
            fd = open(self.__manifest_file, 'r')
            manifest_data = fd.read()
            fd.close()
            manifest_doc = xmlparser.parseString(manifest_data)
            
            if manifest_doc.documentElement.tagName != "ssl_manifest":
                print "ERROR: The manifest file '%s' does NOT seem to be a SSL manifest file  [<%s> instead of <ssl_manifest>]\n"%(self.__manifest_file, manifest_doc.documentElement.tagName) 
                sys.exit(1)
            
            self.__processTag(manifest_doc.documentElement, 'excluded', self.__processManifestExcludedFileNode, {'root':'', 'exclude_list':self.__exclude_set})
            self.__processTag(manifest_doc.documentElement, 'internal', self.__processManifestInternalFileNode, {'root':'', 'internal_list':self.__internal_set})
            self.__processTag(manifest_doc.documentElement, 'generated', self.__processManifestGeneratedFileNode, {'root':'', 'generated_list':self.__generated_set})
            self.__processTag(manifest_doc.documentElement, 'f', self.__processManifestFileNode, {'fileSet':self.__manifest_set, 'root':'', 'exclude_list':self.__exclude_set})
                
            if self.debug:
                print "M:", self.__manifest_set
                
        except IOError, v:
            print "ERROR: Could not open the manifest file '%s' :\n %s"%(self.__manifest_file,v) 
            if self.__verbose:
                print "\n\n----------------- TRACEBACK ---------------------"
                raise
        
    def SetVerbose(self, verbose=True):
        self.__verbose=verbose    
                
    def SetAntMode(self, antmode=True):
        self.__ant=antmode
        
    def AntifyPath(self, path):
        if self.__ant:
            (n, ex) = os.path.splitext(path)
            # since files are just entries in the manifest, it is difficult to know
            # if they are folders or just files.
            if (ex == ''):
                path = os.path.join(path, '**')
                path = path.replace('\\','/')

        return path
                
    def __processTag(self, rootElement,tagName,processFunc,args={}):
        for node in rootElement.getElementsByTagName(tagName):
            processFunc(node,args)

    def __processManifestInternalFileNode(self, fNode,args):
        root          = args['root']
        internal_list = args['internal_list']
        path          = fNode.getAttribute('p')

        path = path.replace('\\','/')
        path = os.path.join(root,path)
        
        internal_list.add(path.strip())
    
    def __processManifestGeneratedFileNode(self, fNode,args):
        root          = args['root']
        generated_list = args['generated_list']
        path          = fNode.getAttribute('p')

        path = path.replace('\\','/')
        path = os.path.join(root,path)
        
        generated_list.add(path.strip())
    
    def __processManifestExcludedFileNode(self, fNode,args):
        root         = args['root']
        exclude_list = args['exclude_list']
        path         = fNode.getAttribute('p')

        path = path.replace('\\','/')
        path = os.path.join(root,path)
        
        exclude_list.add(path.strip())
    

    def __processManifestFileNode(self, fNode,args):
        xmlFileSet   = args['fileSet']
        root         = args['root']
        path         = fNode.getAttribute('p')

        path = path.replace('\\','/')
        path = os.path.join(root,path)
                
        xmlFileSet.add(path.strip())    


    def GetFiles(self):
        return self.__manifest_set

    def GetExclusions(self):
        return self.__exclude_set

    def GetInternals(self):
        return self.__internal_set

    def GetGeneratedFiles(self):
        return self.__generated_set

    def print_verbose(self, message):
        if self.__verbose:
            print(message)




if __name__ == "__main__":

    #
    # Main
    #
    
    

    if sys.version_info < (2, 5, 0, 0):
        sys.exit("This script requires Python version > 2.5")
    
    parser = OptionParser(usage = "usage: %prog", version="%prog "+"%s"%(__version__))
    parser.add_option("-v", "--verbose", help="Verbose output", action="store_true", dest="verbose", default=False)
    parser.add_option("-m", "--manifest", help="Indicates where is MANIFEST file", dest="manifest", metavar="MANIFEST", default="manifest.xml")
    parser.add_option("-x", "--list-excluded", help="Outputs the list of excluded files from the manifest", action="store_true", dest="list_excluded", default=False)
    parser.add_option("-i", "--list-internal", help="Outputs the list of internal files from the manifest", action="store_true", dest="list_internal", default=False)
    parser.add_option("-g", "--list-generated", help="Outputs the list of generated files (generated by the build) from the manifest", action="store_true", dest="list_generated", default=False)
    parser.add_option("-a", "--list-all", help="Outputs the list of files from the manifest", action="store_true", dest="list_all", default=False)
    parser.add_option("--ant", help="Outputs the list of folders using the ant syntax (folder/**)", action="store_true", dest="ant_mode", default=False)
    
    
    (options, args) = parser.parse_args()

    m = Manifest(options.manifest)
    m.SetVerbose(options.verbose)
    m.SetAntMode(options.ant_mode)
    
    if options.list_all:
        m.print_verbose("List All Files:\n")
        for f in m.GetFiles():
            print m.AntifyPath(f)
        sys.exit(0)        

    if options.list_excluded:
        m.print_verbose("List Excluded Files:\n")
        for f in m.GetExclusions():
            print m.AntifyPath(f)
            
    if options.list_internal:
        m.print_verbose("List Internal files:\n")
        for f in m.GetInternals():
            print m.AntifyPath(f)
            
    if options.list_generated:
        m.print_verbose("List Generated files:\n")
        for f in m.GetGeneratedFiles():
            print m.AntifyPath(f)
            
            