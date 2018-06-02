all: UP_Span

objUPSpan =utils.o project.o mining1Episode.o miningSimultHUE.o miningSerialHUE.o UP_span.o EWU.o dataFormat.o validate.o read.o  main.o 
$(objUPSpan): %.o : %.cc
	$(CC) -c $(CFLAGS) $< -o $@

UP_Span: $(objUPSpan)  head.h
	$(CC) $(CFLAGS) -o UP_Span $(objUPSpan)

CC = g++
CFLAGS = -g #-pg 
clean:
	rm *.o

%.d: %.cc
	@set -e; rm -f $@; \
         $(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

#%.d: %.cc
#	@set -e; rm -f $@; \
#		$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
#		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
#		rm -f $@.$$$$
#

#include $(objUPSpan:.o=.d)
