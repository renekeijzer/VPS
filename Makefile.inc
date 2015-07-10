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
		INCLUDES 	+=
		LDFLAGS		+= -LDeps/lib/opencv/Windows/lib
		LDLIBS 		+= -lopencv_highgui2411 -lopencv_imgproc2411 -lopencv_legacy2411 -lopencv_ml2411 -lopencv_nonfree2411 -lopencv_objdetect2411 -lopencv_ocl2411 -lopencv_photo2411 -lopencv_stitching2411 -lopencv_superres2411 -lopencv_ts2411 -lopencv_video2411 -lopencv_videostab2411 -lopencv_calib3d2411 -lopencv_contrib2411 -lopencv_core2411 -lopencv_features2d2411 -lopencv_flann2411 -lopencv_gpu2411
		CXXFLAGS	+= 
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
