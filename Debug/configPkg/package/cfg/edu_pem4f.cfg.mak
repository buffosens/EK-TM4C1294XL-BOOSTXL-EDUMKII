# invoke SourceDir generated makefile for edu.pem4f
edu.pem4f: .libraries,edu.pem4f
.libraries,edu.pem4f: package/cfg/edu_pem4f.xdl
	$(MAKE) -f C:\workspaceCCSv8\Edu/src/makefile.libs

clean::
	$(MAKE) -f C:\workspaceCCSv8\Edu/src/makefile.libs clean

