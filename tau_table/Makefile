.PHONY: all clean

all: tau_table.hh

tau_table.hh: calculated.csv
	./format_tau_table.pl < $^ > $@

calculated.csv: formula.csv
# Open `formula.csv` by LibreOffice Calc 5.3.4.2 etc.
# Save as `formula.ods` once.
# Open `formula.ods` by LibreOffice Calc.
# Save as `calculated.csv`.
	touch $@

clean:
	-rm -fr *~ tau_table.hh
