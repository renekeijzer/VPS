include Makefile.inc

.PHONY : vps clean

vps : $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)
	
	
clean : 
	for prefix in $(MODULES); do \
		rm -f "$$prefix"*.o; \
		rm -f "$$prefix"*.d; \
		rm -f "$$prefix"ui_*.h; \
		rm -f "$$prefix"moc_*.cpp; \
	done
	rm -f *.exe

-include $(OBJ:.o=.d)
