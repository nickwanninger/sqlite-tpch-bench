
SCALE_FACTOR?=1
TABLES = customer lineitem nation orders partsupp part region supplier
TABLE_FILES = $(foreach table, $(TABLES), tpch-dbgen/$(table).tbl)

TPC-H.db: $(TABLE_FILES)
	./create_db.sh $(TABLES)

$(TABLE_FILES): tpch-dbgen/dbgen
	cd tpch-dbgen && ./dbgen -v -f -s $(SCALE_FACTOR)
	chmod +r $(TABLE_FILES)

tpch-dbgen/makefile:
	git clone https://github.com/lovasoa/tpch-dbgen.git tpch-dbgen --depth 1

tpch-dbgen/dbgen: tpch-dbgen/makefile
	cd tpch-dbgen && $(MAKE)

clean:
	rm -rf sqlite TPC-H.db $(TABLE_FILES) tpch-dbgen/dbgen

sqlite: driver.c sqlite3.c
	gcc -o $@ $^
