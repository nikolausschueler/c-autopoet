#!/usr/bin/env ruby

# Little demo showing that this C lib is indeed usable from ruby.

require 'poet'

text = "I wear this crown of shit upon my liars chair. You are someone else, but i am still right here"

poet = Poet.Poet_new(text, 2)
result = Poet.Poet_output(poet)

print result, "\n"
