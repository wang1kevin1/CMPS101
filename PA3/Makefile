#------------------------------------------------------------------------------
# 
#  Kevin Wang
#  kwang43@ucsc.edu
#  PA_3
#  
#  Makefile - Compiles all .java files in the current directory and creates 
#  an executable jar file called Sparse.
#
#------------------------------------------------------------------------------ 

MAINCLASS	=	Sparse
JAVAC  		=	javac 
MATRIXTEST 	=	MatrixTest
LISTTEST  	=	ListTest
JAVASRC		=	$(wildcard *.java)
SOURCES		=	$(JAVASRC) Makefile README
CLASSES		=	$(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES	=	$(patsubst %.class, %*.class, $(CLASSES))
JARFILE		=	$(MAINCLASS) 

all: $(JARFILE)
	
$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(JARCLASSES)
	chmod +x $(JARFILE)
	rm Manifest
	
%.class: %.java
	$(JAVAC) $<

clean:
	rm -f *.class $(JARFILE)
