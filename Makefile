DAYS=$(wildcard ./day*)

.PHONY: all $(DAYS) clean


all: $(DAYS)

$(DAYS):
	$(MAKE) -C $@

clean:
	for d in $(DAYS); do \
		$(MAKE) -C $$d clean; \
	done
