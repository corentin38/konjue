## Makefile.am for konjue

# this is the program that gets installed.  it's name is used for all
# of the other Makefile.am variables
bin_PROGRAMS = konjue konjue_client

# set the include path for X, qt and KDE
INCLUDES = -I/usr/include/verbiste-0.1/ -I/usr/local/include/verbiste-0.1/ \
	-I/usr/include/libxml2/ $(all_includes)

# the library search path. 
konjue_LDFLAGS = $(KDE_RPATH) $(all_libraries)

# the libraries to link against.
konjue_LDADD = -lverbiste-0.1 -lxml2 $(LIB_KFILE) $(LIB_KDEPRINT)

# which sources should be compiled for konjue
konjue_SOURCES = main.cpp konjue.cpp konjueiface.skel searchtoolbar.cpp \
	conjugator.cpp

# these are the headers for your project
noinst_HEADERS = konjue.h searchtoolbar.h conjugator.h

# client stuff
konjue_client_LDFLAGS = $(KDE_RPATH) $(all_libraries)
konjue_client_LDADD   = $(LIB_KDECORE)
konjue_client_SOURCES = konjue_client.cpp

# let automoc handle all of the meta source files (moc)
METASOURCES = AUTO

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/konjue.pot

KDE_ICON = konjue

# this is where the kdelnk file will go 
kdelnkdir = $(kde_appsdir)/Edutainment/Languages
kdelnk_DATA = konjue.desktop

# this is where the XML-GUI resource file goes
rcdir = $(kde_datadir)/konjue
rc_DATA = konjueui.rc
AM_CXXFLAGS = -DHASH_MAP_HEADER=\<ext/hash_map\> -DHASH_MAP_NAMESPACE=__gnu_cxx
