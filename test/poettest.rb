#!/usr/bin/env ruby

require 'runit/testcase'
require 'poet'

class BifurTreeTest < RUNIT::TestCase
  
  #??? Make that run.
  def testWordlen
    text = "Hello laal"
    f = IO.popen("../app/poet -w 4", "r+")
    f.puts(text)
    #lines = f.readlines
    #print lines
    f.close
  end

end

#--- main program ----
if __FILE__ == $0
  require 'runit/cui/testrunner'
  RUNIT::CUI::TestRunner.run(BifurTreeTest.suite)
end
