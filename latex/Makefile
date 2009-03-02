# Latex with lilypond Makefile
# Amiel Martin
# 2009-03-02
#
# for one file this Makefile will run pdflatex
# if a running bibtex is needed it will do so
# if rerunning pdflatex is needed to get cross-references, it will do so
#
# if the file has the extension .lilytex, then lilypond-book will be run before pdflatex


TEXFILE = rameau # put the name of your file (without extension) here

.PHONY: all clean lily-book

all: ${TEXFILE}

${TEXFILE}: lily-book
	pdflatex ${TEXFILE}
	@if ( egrep "No file.*\.bbl|Citation.*undefined"	\
			${TEXFILE}.log > /dev/null ); then		\
		bibtex ${TEXFILE}; \
	fi; true
	@while ( grep "Rerun to get cross-references" 	\
			${TEXFILE}.log > /dev/null ); do		\
		echo '** Re-running LaTeX **';		\
		pdflatex ${TEXFILE};				\
	done


lily-book:
	if [ -f ${TEXFILE}.lilytex ]; then \
		lilypond-book ${TEXFILE}.lilytex -f latex --pdf; \
	fi

clean-junk:
	rm -rf 3f 8a
	rm -f *.log
	rm -f *.aux
	rm -f ${TEXFILE}.dep
	rm -f snippet-{map,names}-*.ly

clean: clean-junk
	rm -f ${TEXFILE}.pdf
	

