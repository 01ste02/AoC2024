DAYS=$(wildcard ./day*)

.PHONY: all $(DAYS) clean test


all: $(DAYS)

$(DAYS):
	$(MAKE) -C $@

clean:
	for d in $(DAYS); do \
		$(MAKE) -C $$d clean; \
	done

test:
	for d in $(DAYS); do \
		$(MAKE) -C $$d test; \
	done

