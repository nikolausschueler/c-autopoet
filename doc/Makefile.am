EXTRA_DIST = apidoc-stub.xml entities.xml poet.xml poetarticle.xml

#??? This is quite hardcoded. Make it more flexible.
all: index.html

index.html: poetarticle.xml
	/usr/local/jdk1.3/bin/java com.icl.saxon.StyleSheet $< ~/work/cvscontrolled/nik/xml/stylesheets/html/nik.xsl > $@

clean:
	rm -f index.html