include Makefile.local
include TargetMakefiles/Makefile.modules

CXX 							= g++
CXXFLAGS						= -std=c++11
INCLUDES 						= 
LDLIBS							=
LDFLAGS							= 
SRC 							= 
UI 								= 
UI_HEADERS						=
MODULES 						= 

ifeq ($(OS),Windows_NT)
	CXXFLAGS 	+= -DWIN32 -fPIC
	MOC			= $(QT_BIN_DIR)/moc.exe
	UIC			= $(QT_BIN_DIR)/uic.exe
endif

ifeq ($(MAKECMDGOALS),vps)
	ifeq ($(OS),Windows_NT)
		INCLUDES 	+= -IDeps/incl/opencv
		LDLIBS 		+= -LDeps/lib/opencv/Windows/lib
		CXXFLAGS	+= -lopencv_ts300 -lopencv_world300
	else
		INCLUDES 	+= -IDeps/incl/opencv
		LDFLAGS		+= -LDeps/lib/opencv/Linux/x86
		LDLIBS 		+= -lopencv_core -lopencv_highgui -lopencv_imgproc -lpthread -lrt
	endif
	include TargetMakefiles/Makefile.vps
endif
ifeq ($(MAKECMDGOALS),clean)
	include TargetMakefiles/Makefile.clean
else
	INCLUDES 		+= $(patsubst %, -I%, $(MODULES))
	include $(MODULES:=module.mk)
	UI_HEADERS 		+= $(UI:.ui=.h)
	OBJ 			+= $(SRC:.cpp=.o)
endif


%.d : %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MM -MT"$@" $< -MF $@
	
%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<
	
moc_%.cpp : %.h
	$(MOC) $< -o $@
	
ui_%.h : %.ui
	$(UIC) $< -o $@