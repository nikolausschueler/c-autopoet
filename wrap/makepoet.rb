# This script builds and installs my C poet stuff as a ruby module. It uses
# swig (http://www.swig.org).

headerpath = "/usr/local/include"
nikheaderdir = "nik"
headerdir = "#{headerpath}/#{nikheaderdir}"

# Check if one of my basic headers is there
if(!File.exists?("#{headerdir}/poet.h"))
  print "This needs the headers from my C poet package. But they are either not\n"
  print "installed under #{headerdir} or not installed at all.\n"
  print "If they are installed under a different directory, change the variables\n"
  print "in this script.\n"
  print "If they are not installed at all, get my C poet package from\n"
  print "\n"
  print "http://www.drnik.org\n"
  print "\n"
  print "and install it.\n"
  exit
end

headers = [
  "nikdefs.h",
  "poet.h"]

print "Writing swig file\n"

# Make interface file for swig.
#
iffile = File.open("poet.i", "w")
iffile.write("// File is automatically generated. Do not mess with it.\n")
iffile.write("%module poet\n\n")
iffile.write("%{\n")
headers.each { |h| iffile.write("\#include \"#{headerdir}/#{h}\"\n") }
iffile.write("%}\n\n")
headers.each do |h| 
  text = File.open("#{headerdir}/#{h}", "r").read
  iffile.write(text)
end
# Important. Else following commands work on an open file and crash.
iffile.close

print "Writing extconf file\n"

extconf = File.open("extconf.rb", "w")
extconf.write("# File is automatically generated. Do not mess with it.\n")
extconf.write("require 'mkmf'\n")
extconf.write("\n")
extconf.write("# Same phenomenon as in autoconf:\n")
extconf.write("# !! This is extremly important. \"configure\" checks for libraries by trying to\n")
extconf.write("# link a little code sample against them. libPhylC needs libfl and if you\n")
extconf.write("# dont provide the check for libfl, linking to libPhylC fails, creating the\n")
extconf.write("# wrong impression that libPhylC would not be there at all!\n")
extconf.write("#\n")
extconf.write("have_library(\"poet\")\n")
extconf.write("create_makefile(\"poet\")\n")
extconf.close

system "swig -ruby poet.i"
system "ruby extconf.rb"
system "make"

print "\nLibrary is now made, install it with 'make install'. (Must be done by"
print " user 'root' on many systems.)\n\n"
