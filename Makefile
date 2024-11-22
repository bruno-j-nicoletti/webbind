.PHONY : webBind
webBind :
	if [ ! -d build ] ; then mkdir build; fi
	emcmake cmake -B build .
	cd build; make
