all: null

null:
	@echo No target specified

fm:
	@sudo chvt 8
	@sudo libs/x86/aroma_filemanager 1 1 aromafm_generic.zip
	@sudo chvt 7

in:
	@sudo chvt 8
	@sudo libs/x86/aroma_installer 1 1 aroma_installer-3.00b1.zip
	@sudo chvt 7
